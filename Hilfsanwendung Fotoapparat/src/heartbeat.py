import time
from pyb import LED
import config

redLed = LED(1)
redLed.off()
oldTime = 0
timeToEnableLed = config.HEARTBEAT_CYCLE_MILLIS-config.HEARTBEAT_ON_TIME_MILLIS

def runHeartbeat():
    global oldTime

    currentTime = time.ticks_ms()
    timeDifference = currentTime - oldTime
    if timeDifference > timeToEnableLed:
        redLed.on()
    if timeDifference > config.HEARTBEAT_CYCLE_MILLIS:
        redLed.off()
        oldTime = currentTime


