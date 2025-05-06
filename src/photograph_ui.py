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
import random
import machine
from pyb import Timer
import micropython
micropython.alloc_emergency_exception_buf(128)

class ClientClosedStreamException(Exception):
    message = "Client closed the Stream!"
    def __init__(self):
        super().__init__(self.message)

    def __str__(self):
        return self.message

class MjpegStream:
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

    def runFrame(self):
        # Stream images
        # NOTE: Disable IDE preview to increase streaming FPS.
        framerateClock.tick()  # Track elapsed milliseconds between snapshots().
        frame = sensor.snapshot()
        cframe = frame.to_jpeg(quality=35, copy=True)
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
        finally:
            print(f"Framerate: {framerateClock.fps()}")


SSID = "switch2"  # Network SSID
KEY = "hellebarde"  # Network key
HOST = ""  # Use first available interface
PORT = 8080  # Arbitrary non-privileged port
handleOneConnectionOnNextIteration = False
command = ""
client: socket.socket = None
addr = 0
stream: MjpegStream = None
debug = True

print(f"Frequenz {machine.freq()}")

# Init sensor
sensor.reset()
sensor.set_framesize(sensor.QVGA)
sensor.set_pixformat(sensor.RGB565)

# FPS clock
framerateClock = time.clock()
wifiHandlingClock = time.clock()

# Init wlan module and connect to network
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, KEY)

print(f"Wlan.isconnected:  {wlan.isconnected()}")
while not wlan.isconnected():
    print('Trying to connect to "{:s}"...'.format(SSID))
    time.sleep_ms(1000)


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

def sendWebsite(client: socket.socket):
    client.sendall(
        "HTTP/1.1 200 OK\r\n"
        "Server: OpenMV\r\n"
        "Content-Type: text/html\r\n"
        "Cache-Control: no-cache\r\n"
        "Pragma: no-cache\r\n\r\n"
    )

    page = (
    '<html>'
        '<head></head>'
        '<body>'
            '<img src="/stream" alt="MJpeg-Stream">'
            '<button onclick="savePicture()">Bild aufnehmen!</button>'
            '<script>'
              'function savePicture() {'
                'fetch("/picture");'
              '}'
            '</script>'
        '</body>'
    '</html>')


    client.sendall(page)
    client.close()


def takePictures(client: socket.socket):
    print("Requested to take Snapshots and save them!")
    sensor.snapshot().save("snapshot-%d.jpg" % random.getrandbits(32)) # Codezeile aus snapshot_on_face_detection
    client.sendall("HTTP/1.1 200 OK\r\n")
    client.close()

def handleOneRequest():
    wifiHandlingClock.tick()
    try:
        global command
        global client
        global addr
        global sock

        # print("Checking for waiting connections...")
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
        elif path == "/picture":
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
    finally:
        print(f"Wifi Handler took {wifiHandlingClock.avg()} milliseconds")


def runBackgroundLoop(s):
    global stream
    global handleOneConnectionOnNextIteration
    global command
    global client
    global addr

    if(handleOneConnectionOnNextIteration):
        handleOneRequest()
        handleOneConnectionOnNextIteration = False

    if(not client is None):
        if command == "SEND_WEBSITE":
            sendWebsite(client);

        elif command == "TAKE_PICTURES":
            takePictures(client)

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

def oneSecondInterrupt(timer):
    global handleOneConnectionOnNextIteration
    handleOneConnectionOnNextIteration = True

# setup timer interrupt
try:
    Timer(3).init(freq=1,callback=oneSecondInterrupt, mode=Timer.UP)
except Exception as e:
    print(f"Error with Timer setup: {e}")

while True:
    try:
        runBackgroundLoop(sock)
    except OSError as e:
        command = ""
        print("socket error: ", e)
        # sys.print_exception(e)
