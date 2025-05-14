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
from streaming import MjpegStream, ClientClosedStreamException
from file_processing import PictureWriter
import config
from heartbeat import runHeartbeat

debug = True

print(f"Frequenz {machine.freq()}")
if debug:
    micropython.alloc_emergency_exception_buf(128)

# Init wlan module and connect to network
network.hostname("fotoapparat")
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(config.SSID, config.WIFI_PASSWORD)

while not wlan.isconnected():
    print('Trying to connect to "{:s}"...'.format(config.SSID))
    wlan.connect(config.SSID, config.WIFI_PASSWORD)
    time.sleep_ms(1000)

# Init sensor
sensor.reset()
sensor.set_framesize(sensor.QVGA)
sensor.set_pixformat(sensor.RGB565)

# FPS clock
framerateClock = time.clock()

handleOneConnectionOnNextIteration = False
command = ""
commandArgs: dict[str,str] = {}
client: socket.socket = None
addr = 0
stream: MjpegStream = None
wifiInterruptTimer: Timer

# We should have a valid IP now via DHCP
print("WiFi Connected ", wlan.ifconfig())

# Create server socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)

# Bind and listen
sock.bind([config.HOST, config.PORT])
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
        with open(config.WEBSITE_PATH, "r") as website:
            html = website.read()
            client.sendall(html)
    except Exception as e:
        print(f"Exception {e} of type {type(e)} occured in sendWebsite!")


def takePictures(client: socket.socket, filenamePrefix: str = None, dateOfPicture: str = None):
    writtenFileName = pictureWriter.writeFile(filenamePrefix, dateOfPicture)

    client.sendall(
        "HTTP/1.1 201 Created\r\n"
        "Content-Type: text/plain\r\n"
        f"Content-Length: {len(writtenFileName)}\r\n"
        "\r\n"
        f"{writtenFileName}\r\n"
    )

def parseUrlAndQueryString(requestUri:str):
    if("?" in requestUri):
        path, queryString = requestUri.split("?", 1)
        queryParamDict = extractQueryParamDict(queryString)
    else:
        path = requestUri
        queryParamDict = {}

    return (path, queryParamDict)

def extractQueryParamDict(queryString: str) -> dict[str]:
    queryParamDict = {}
    if("=" in queryString):
        for param in queryString.split("&"):
            key, value = param.split("=", 1)
            queryParamDict[key] = value

    return queryParamDict

def handleOneRequest():
    try:
        global command
        global commandArgs
        global client
        global addr
        global sock

        if debug:
            print("Checking for waiting connections...")
        client, addr = sock.accept()
        if debug:
            print("Connected to " + addr[0] + ":" + str(addr[1]))

        # Read request from client
        data = client.recv(256)
        if(not data):
            print("client closed the connection!")
            client.close()
        # Should parse client request here
        if debug:
            print("data from client: {}".format(data))

        method, requestUri, version = data.decode().split("\r\n")[0].split()
        path, commandArgs = parseUrlAndQueryString(requestUri)
        if debug:
            print(f"request: {method} {path} {commandArgs} {version}")

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
    global commandArgs
    global client
    global addr
    global wifiInterruptTimer

    if(handleOneConnectionOnNextIteration):
        handleOneConnectionOnNextIteration = False
        wifiInterruptTimer.callback(None)
        handleOneRequest()
        wifiInterruptTimer.callback(timedInterrupt)

    if(not client is None):
        if command == "SEND_WEBSITE":
            sendWebsite(client);
            client.close()

        elif command == "TAKE_PICTURES":
            takePictures(client, commandArgs.get("filename-prefix"), commandArgs.get("date-of-picture"))
            client.close()

        elif command == "START_STREAM" and stream is None:
            if(debug):
                print("Starte Stream...")
            stream = MjpegStream(client, sensor)
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
    commandArgs = {}
    if(not client is None):
        if(debug):
            print(f"closing connection to client: {addr}")
        client.close()
        client = None
    time.sleep_ms(0)

def timedInterrupt(timer):
    global handleOneConnectionOnNextIteration
    handleOneConnectionOnNextIteration = True

# setup timer interrupt
try:
    wifiInterruptTimer = Timer(3)
    wifiInterruptTimer.init(freq=50, callback=timedInterrupt, mode=Timer.UP)
except Exception as e:
    print(f"Error with Timer setup: {e}")

while True:
    try:
        runHeartbeat()
        runBackgroundLoop()
    except OSError as e:
        command = ""
        print("socket error: ", e)
        # sys.print_exception(e)
