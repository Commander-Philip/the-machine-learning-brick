import subprocess
import sys
from zipfile import ZipFile
from glob import glob
import re

def listSignCategorieFolder(path):
    folders = glob(path+"/[1-5]*")
    # print(folders)
    return folders

def extractGivenPathFromSysArgs():
    args = sys.argv[1:0]
    givenPath = ""
    if len(args) == 0:
        givenPath = "./"
    else:
        givenPath = args[0]

    print(f"Working with {givenPath}")
    return givenPath

def main():
    """
    Ordner sind in folgende Variablen aufgeteilt:\n
        Kategorisiert nach Form                         => shapeFolders bzw. shapeFolder\n
        Sortiert nach Schildart                         => signFolders bzw. signFolder\n
        Orte, die aus dem Speicherpfad entfernt werden  => places bzw. place\n
        Die einzelnen Bilder                            => pictures bzw. picture
    """
    givenPath = extractGivenPathFromSysArgs()

    path = f"{givenPath.replace("/","",1)}"
    print(path)
    zipPath = path + "/Trainingsdaten.zip"
    print(zipPath)
    print("\n")

    shapeFolders = listSignCategorieFolder(path)

    sumOfPictures = 0    
    with ZipFile(zipPath, "w") as zip:
        for shapeFolder in shapeFolders:
            # print(folder)
            signFolders = glob(shapeFolder+"/*")

            for signFolder in signFolders:
                fileNumber = 0
                # print(f"{subfolder}")
                places = glob(signFolder+"/*")
                for place in places:
                    # print(place)
                    pictures = glob(place+"/*.jpg")
                    for picture in pictures:
                        # print(picture)
                        pathFragments = picture.split("/")
                        pathFragments.pop(-2)
                        pathWithoutPlace = "/".join(pathFragments)
                        pathForPictureInZipFile = re.sub(".*/(?=Trainingsdaten)", "",pathWithoutPlace)
                        fileNumber += 1
                        pathForPictureInZipFile = re.sub("[0-9]+\.jpg", f"{fileNumber}.jpg", pathForPictureInZipFile)
                        # print(pathForPictureInZipFile)
                        # print(f"Picture: {picture} PLACED IN {pathForPictureInZipFile}")
                        zip.write(picture, pathForPictureInZipFile)
                print(f"Für {signFolder} gibt es {fileNumber} Bilder")
                sumOfPictures += fileNumber
            # print("\n")
    print(f"\nInsgesamt {sumOfPictures} Bilder gezippt\n")
    countOfRoundSigns = int(subprocess.run(["find ./1_Runde_Schilder -type f | wc -l"], capture_output=True, shell=True, text=True).stdout.strip())
    countOfTriangularSigns = int(subprocess.run(["find ./2_Dreieckige_Schilder -type f | wc -l"], capture_output=True, shell=True, text=True).stdout.strip())
    countOfRectangleSigns = int(subprocess.run(["find ./3_Rechteckige_Schilder -type f | wc -l"], capture_output=True, shell=True, text=True).stdout.strip())
    countOfTrafficLights = int(subprocess.run(["find ./4_Ampel -type f | wc -l"], capture_output=True, shell=True, text=True).stdout.strip())
    countOfPolgyonSigns = int(subprocess.run(["find ./5_Polygon_Schilder -type f | wc -l"], capture_output=True, shell=True, text=True).stdout.strip())
    sumOfPicturesNonZipped = countOfRoundSigns + countOfTriangularSigns + countOfRectangleSigns + countOfTrafficLights + countOfPolgyonSigns
    print(f"Es fehlen {sumOfPicturesNonZipped-sumOfPictures} Bilder")

main()