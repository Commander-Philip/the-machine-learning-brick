# This work is licensed under the MIT license.
# Copyright (c) 2013-2023 OpenMV LLC. All rights reserved.
# https://github.com/openmv/openmv/blob/master/LICENSE
#
# MJPEG Streaming
#
# This example shows off how to do MJPEG streaming to a FIREFOX webrowser
# Chrome, Firefox and MJpegViewer App on Android have been tested.
# Connect to the IP address/port printed out from ifconfig to view the stream.

import sensor
import time
import network
import socket
import machine
from pyb import Timer
import micropython
import os

WEBSITE_PATH= "/sdcard/website/index.html"
SSID = "switch2"  # Network SSID
KEY = "hellebarde"  # Network key
HOST = ""  # Use first available interface
PORT = 8080  # Arbitrary non-privileged port
debug = False

def timed_function(f, *args, **kwargs):
    myname = str(f).split(' ')[1]
    def new_func(*args, **kwargs):
        t = time.ticks_us()
        result = f(*args, **kwargs)
        delta = time.ticks_diff(time.ticks_us(), t)
        print('Function {} Time = {:6.3f}ms'.format(myname, delta/1000))
        return result
    return new_func

class ClientClosedStreamException(Exception):
    message = "Client closed the Stream!"
    def __init__(self):
        super().__init__(self.message)

    def __str__(self):
        return self.message

class MjpegStream:
    lastFrameMillis = time.ticks_ms()

    def __init__(self, client: socket.socket):
        self.streamingClient: sock.sock
        self.startStream()

    def startStream(self):
        self.streamingClient = client

        # Send multipart header
        self.streamingClient.sendall(
            "HTTP/1.1 200 OK\r\n"
            "Server: OpenMV\r\n"
            "Content-Type: multipart/x-mixed-replace;boundary=openmv\r\n"
            "Cache-Control: no-cache\r\n"
            "Pragma: no-cache\r\n\r\n"
        )

    @timed_function
    def runFrame(self):
        now = time.ticks_ms()
        if(debug):
            print(f"Time since last Frame: {now-self.lastFrameMillis}")
        if(now - self.lastFrameMillis > 80):
            self.lastFrameMillis = now
            frame = sensor.snapshot()
            cframe = frame.to_jpeg(quality=10, copy=True)
            header = (
                "\r\n--openmv\r\n"
                "Content-Type: image/jpeg\r\n"
                "Content-Length:" + str(cframe.size()) + "\r\n\r\n"
            )
            try:
                self.streamingClient.sendall(header)
                self.streamingClient.sendall(cframe)
            except OSError as e:
                if(e.errno == 32):
                    print("Streaming client closed connection!")
                    self.streamingClient.close()
                    raise ClientClosedStreamException()
            except Exception as e:
                print(f"Error: {e}")

class PictureWriter:
    _FILE_ENDING = ".jpg"

    def __init__(self, pictureSensor: sensor, outputFolder: str):
        """
        Args:
            sensor (sensor): Der Konfigurierte Fotosensor.
            outputFolder (str): Relativer Pfad um die Fotos abzulegen. Mit führendem "/".

        Example:
            pictureWriter = PictureWriter(sensor, "/pictures")
        """
        self._outputFolder = f"/sdcard{outputFolder}"
        self._sensor = pictureSensor
        self.lastFileNumber = -1

    def writeFile(self, prefix: str):
        previousFolder = os.getcwd()
        try:
            os.mkdir(self._outputFolder)
        except OSError:
            pass
        os.chdir(self._outputFolder)
        if debug:
            print(f"Current Folder: {os.getcwd()}")

        fileName = self.createFileName(prefix)
        if debug:
            print(f"Saving snapshot {fileName} on SD-Card.")
        self._sensor.snapshot().save(fileName) # Codezeile aus snapshot_on_face_detection
        client.sendall("HTTP/1.1 200 OK\r\n")

        os.chdir(previousFolder)

    def createFileName(self, prefix: str | None):
        frontalFileName: str

        if(prefix is not None):
            frontalFileName = f"{prefix}-snapshot-"
        else:
            frontalFileName = "snapshot-"

        if self.lastFileNumber == -1:
            self.lastFileNumber = self.findBiggestFileNumber(frontalFileName)

        self.lastFileNumber+=1
        return f"{frontalFileName}{self.lastFileNumber}{self._FILE_ENDING}"

    def findBiggestFileNumber(self, frontalFileName: str):
        fileNumber = 0

        for fileName in os.listdir(self._outputFolder):
            if fileName.startswith(frontalFileName) and fileName.endswith(self._FILE_ENDING):
                currentNumber = int(fileName[len(frontalFileName):-len(self._FILE_ENDING)])

                if currentNumber > fileNumber:
                    fileNumber = currentNumber

        return fileNumber

print(f"Frequenz {machine.freq()}")
if debug:
    micropython.alloc_emergency_exception_buf(128)

# Init wlan module and connect to network
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, KEY)

while not wlan.isconnected():
    print('Trying to connect to "{:s}"...'.format(SSID))
    wlan.connect(SSID, KEY)
    time.sleep_ms(1000)

# Init sensor
sensor.reset()
sensor.set_framesize(sensor.QVGA)
sensor.set_pixformat(sensor.RGB565)

# FPS clock
framerateClock = time.clock()

handleOneConnectionOnNextIteration = False
command = ""
client: socket.socket = None
addr = 0
stream: MjpegStream = None
oneSecTimer: Timer

# We should have a valid IP now via DHCP
print("WiFi Connected ", wlan.ifconfig())

# Create server socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)

# Bind and listen
sock.bind([HOST, PORT])
sock.listen(5)
print("Socket bound and listening")

# Set server socket to blocking
sock.setblocking(False)

pictureWriter = PictureWriter(sensor, "/pictures")

def sendWebsite(client: socket.socket):
    client.sendall(
        "HTTP/1.1 200 OK\r\n"
        "Server: OpenMV\r\n"
        "Content-Type: text/html\r\n"
        "Cache-Control: no-cache\r\n"
        "Pragma: no-cache\r\n\r\n"
    )

    try:
        with open(WEBSITE_PATH, "r") as website:
            html = website.read()
            client.sendall(html)
    except Exception as e:
        print(f"Exception {e} of type {type(e)} occured in sendWebsite!")


def takePictures(client: socket.socket, prefix: str | None = None):
    print("writing File")
    pictureWriter.writeFile(prefix)

def handleOneRequest():
    try:
        global command
        global client
        global addr
        global sock

        print("Checking for waiting connections...")
        client, addr = sock.accept()
        print("Connected to " + addr[0] + ":" + str(addr[1]))

        # Read request from client
        data = client.recv(256)
        if(not data):
            print("client closed the connection!")
            client.close()
        # Should parse client request here
        print("data from client: {}".format(data))

        method, path, version = data.decode().split("\r\n")[0].split()
        print(f"request: {method} {path} {version}")

        if path == "/":
            if(debug):
                print("Webseite angefordert")
            command = "SEND_WEBSITE"
        elif path == "/favicon.ico":
            client.sendall("HTTP/1.1 404 Bad Request\r\n")
        elif path.startswith("/picture"):
            if(debug):
                print("Nehme Bilder auf...")
            command = "TAKE_PICTURES"
        elif path == "/stream":
            if(debug):
                print("Starte Stream...")
            command = "START_STREAM"

        path = ""
    except OSError as e:
        if(e.errno != 11):
            print(f"Fehler in Socket Handling: {e}, type {type(e)}")
    except Exception as e:
        print(f"Fehler in handleOneRequest: {e}")


def runBackgroundLoop():
    global stream
    global handleOneConnectionOnNextIteration
    global command
    global client
    global addr
    global oneSecTimer

    if(handleOneConnectionOnNextIteration):
        handleOneConnectionOnNextIteration = False
        oneSecTimer.callback(None)
        handleOneRequest()
        oneSecTimer.callback(oneSecondInterrupt)

    if(not client is None):
        if command == "SEND_WEBSITE":
            sendWebsite(client);
            client.close()

        elif command == "TAKE_PICTURES":
            takePictures(client)
            client.close()

        elif command == "START_STREAM" and stream is None:
            if(debug):
                print("Starte Stream...")
            stream = MjpegStream(client)
            client = None # Clear current reference so nobody closes the streaming client´

        elif command == "START_STREAM" and not stream is None:
            if(debug):
                print("Bereits ein User am Streamen")
            client.sendall("HTTP/1.1 503 Service Unavailable\r\n")
        elif command == "":
            pass
        else:
            if(debug):
                print(f"Command: {command} not found")
            client.sendall("HTTP/1.1 404 Not Found\r\n")

    if(not stream is None):
        if(debug):
            print("continue streaming")
        try:
            stream.runFrame()
        except ClientClosedStreamException as e:
            stream = None
            print(e)

    command = ""
    if(not client is None):
        if(debug):
            print(f"closing connection to client: {addr}")
        client.close()
        client = None
    time.sleep_ms(0)

def oneSecondInterrupt(timer):
    global handleOneConnectionOnNextIteration
    handleOneConnectionOnNextIteration = True

# setup timer interrupt
try:
    oneSecTimer = Timer(3)
    oneSecTimer.init(freq=50,callback=oneSecondInterrupt, mode=Timer.UP)
except Exception as e:
    print(f"Error with Timer setup: {e}")

while True:
    try:
        runBackgroundLoop()
    except OSError as e:
        command = ""
        print("socket error: ", e)
        # sys.print_exception(e)
