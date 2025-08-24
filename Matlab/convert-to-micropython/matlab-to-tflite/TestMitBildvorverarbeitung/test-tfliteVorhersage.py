import ml
import gc
import sensor, image, time
za=0

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

# Kamera initialisieren
sensor.reset()
sensor.set_pixformat(sensor.RGB565)  # Modell erwartet RGB
sensor.set_framesize(sensor.QVGA)    # 320x240 (größer als nötig)
sensor.set_hmirror(True)
sensor.set_vflip(True)
sensor.skip_frames(time = 2000)      # Warte auf Stabilisierung
clock = time.clock()

while(True):
    clock.tick()
    sensor.flush()
    img = sensor.snapshot()
    sensor.flush()
    print(sensor.width(),sensor.height())
    print("neuesBild")
    time.sleep_ms(2000)

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

        # ROI berechnen
        roi = (x - 24, y - 24, 48, 48)
        if (roi[0] < 0 or roi[1] < 0 or
            roi[0] + roi[2] > img.width() or
            roi[1] + roi[3] > img.height()):
            continue  # Ausschnitt außerhalb, überspringen
        time.sleep_ms(2000)
        # 4.1 Crop & Array erstellen
        small = img.crop(roi=roi)
        image_array = small.to_ndarray(dtype="b").reshape((1, 48, 48, 3))
        time.sleep_ms(2000)
        try:
            output = model.predict([image_array])
            scores = output[0][0][0][0]
            print("Klassifikation:", scores)
            pass
        except Exception as e:
            print(e)


