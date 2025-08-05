import ml
import gc
import sensor, image, time

print("trying to load")
print("Free mem before loading model:", gc.mem_free());
model = None
try:
    model = ml.Model("/sdcard/models/sign-classifier.tflite", load_to_fb=True)
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

    img = sensor.snapshot()

    # Bild für das Modell vorbereiten (48x48)
    # Du kannst auch andere Ausschnitte wählen, z. B. center crop
    roi = (img.width()//2 - 24, img.height()//2 - 24, 48, 48)
    small_img = img.crop(
        roi=roi
    )

    # Modell ausführen
    image_array=small_img.to_ndarray(dtype="b").reshape((1, 48, 48, 3))
    try:
        output = model.predict([image_array])
        pass
    except Exception as e:
        print(e)

    # Ergebnisse anzeigen
    if output:
        scores = output[0][0][0][0]

        print("Klassifikation:", scores)

    # Optionale Visualisierung
