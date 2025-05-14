import time
import socket
import sensor
from measurement_functions import timed_function

class ClientClosedStreamException(Exception):
    message = "Client closed the Stream!"
    def __init__(self):
        super().__init__(self.message)

    def __str__(self):
        return self.message

class MjpegStream:
    lastFrameMillis = time.ticks_ms()

    def __init__(self, client: socket.socket, initializedSensor: sensor):
        self.streamingClient: socket.socket
        self.startStream(client)
        self.sensor = initializedSensor

    def startStream(self, client):
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

        if(now - self.lastFrameMillis > 80):
            self.lastFrameMillis = now
            frame = self.sensor.snapshot()
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
