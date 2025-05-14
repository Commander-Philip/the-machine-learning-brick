import sensor
from measurement_functions import timed_function
import os

debug = False

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

    @timed_function
    def writeFile(self, filenamePrefix: str = None, dateOfPicture: str = None):
        previousFolder = os.getcwd()
        try:
            os.mkdir(self._outputFolder)
        except OSError:
            pass
        os.chdir(self._outputFolder)
        if debug:
            print(f"Current Folder: {os.getcwd()}")

        filename = self.createFileName(filenamePrefix, dateOfPicture)
        if debug:
            print(f"Saving snapshot {filename} on SD-Card...")

        self._sensor.snapshot().save(filename) # Codezeile aus snapshot_on_face_detection

        os.chdir(previousFolder)

        return filename

    def createFileName(self, filenamePrefix: str = None, dateInfix: str = None):
        frontalFilename: str

        if (not self.isStringNullOrBlank(filenamePrefix) and not self.isStringNullOrBlank(dateInfix)):
            frontalFilename = f"{filenamePrefix}-{dateInfix}__"
        elif (self.isStringNullOrBlank(filenamePrefix) and not self.isStringNullOrBlank(dateInfix)):
            frontalFilename = f"snapshot-{dateInfix}__"
        elif (not self.isStringNullOrBlank(filenamePrefix) and self.isStringNullOrBlank(dateInfix)):
            frontalFilename = f"{filenamePrefix}__"
        else:
            frontalFilename = "snapshot-"

        self.lastFileNumber = self.findBiggestFileNumber(frontalFilename)

        self.lastFileNumber+=1
        return f"{frontalFilename}{self.lastFileNumber}{self._FILE_ENDING}"

    def isStringNullOrBlank(self, stringToCheck: str):
        return stringToCheck is None or stringToCheck.strip() == ""

    def findBiggestFileNumber(self, frontalFilename: str):
        fileNumber = 0

        for fileName in os.listdir(self._outputFolder):
            if fileName.startswith(frontalFilename) and fileName.endswith(self._FILE_ENDING):
                currentNumber = int(fileName[len(frontalFilename):-len(self._FILE_ENDING)])

                if currentNumber > fileNumber:
                    fileNumber = currentNumber

        return fileNumber
