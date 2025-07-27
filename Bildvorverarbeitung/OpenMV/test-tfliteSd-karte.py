import ml
import gc
import sensor, image, time
za=0

import os

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

pfad = "/sdcard/Quantisierungsbilder"
dateien = os.listdir(pfad)
bilder = [f for f in dateien if f.endswith(".jpg") or f.endswith(".png")]
fb = sensor.snapshot()
print("trying to load")
print("Free mem before loading model:", gc.mem_free());
model = None
try:
    model = ml.Model("/sdcard/models/sign-classifier.tflite", load_to_fb=False)
except Exception as e:
    print(e)
print("loaded")
print("Free mem before loading model:", gc.mem_free());
labels = ['Klasse 0', 'Klasse 1']


while(True):

    for datei in bilder:
        pfad_zum_bild = pfad + "/" + datei
        sd_img = image.Image(pfad_zum_bild)  # Bild laden
        img = sd_img.to_rgb565(copy_to_fb=True)
        print("Verarbeite:", datei)
        circles = img.find_circles(threshold=2500, x_margin=10, y_margin=10, r_margin=10,
                                   r_min=2, r_max=45, r_step=2)
        if not circles:
            continue
        print("Suche Kreis… Gefundene Kreise:", len(circles))
        za=0
        # 2) Sobald circles nicht leer ist, springt das Programm hierher:
        print("Kreis gefunden! Zeichne ein.")
        for c in circles:
            za = za + 1
            print("Kreis ", za)
            x, y, r = c.x(), c.y(), c.r()
            # Kreis rot einzeichnen
            img.draw_circle(x, y, r, color=(255, 0, 0))
            sensor.flush()
            time.sleep_ms(1000)
            # ROI berechnen
            roi = (x - 24, y - 24, 48, 48)
            if (roi[0] < 0 or roi[1] < 0 or
                roi[0] + roi[2] > img.width() or
                roi[1] + roi[3] > img.height()):
                print("roi")
                continue  # Ausschnitt außerhalb, überspringen


        # Bild vorverarbeiten (je nach Modellvorgabe)
            print("bild verarbeiten")
            small = img.crop(roi=roi)
            image_array = small.to_ndarray(dtype="b").reshape((1, 48, 48, 3))
            print("bild neu")
            # Dann an dein Klassifikationsmodell übergeben:
            try:
                output = model.predict([image_array])
                pass
            except Exception as e:
                print(e)
            scores = output[0][0][0][0]  # oder flatten wie vorher besprochen
            print("Klassifikationsergebnis:", scores)

            # Ergebnisse anzeigen
            if output:
                print("Klassifikation:", scores)
                print("Typ von output:", type(output))
                print("Output-Inhalt:", output)

                time.sleep_ms(2000)
