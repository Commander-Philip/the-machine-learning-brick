import os
import numpy as np
from PIL import Image
import tensorflow as tf
# Dein MATLAB-Converter-Package
import tf_model

# 0 = alle Logs; 1 = INFO unterdrücken; 2 = WARNING unterdrücken; 3 = ERROR unterdrücken
os.environ["TF_CPP_MIN_LOG_LEVEL"] = "2"
# schaltet die oneDNN-Hinweise aus
os.environ["TF_ENABLE_ONEDNN_OPTS"] = "0"
# optional: auch das Python-Logging von TF auf ERROR setzen
tf.get_logger().setLevel("ERROR")


# Modell instanziieren und Gewichte laden
model = tf_model.load_model(load_weights=True, debug=False)

# Prüfen, was das Modell erwartet
print("Eingabe-Shape (inkl. Batch):", model.input_shape)
#print(model.summary())

# Ordner mit Testbildern
image_folder = "Quantisierungsbilder"

# Extrahiere Höhe, Breite, Kanäle aus model.input_shape
_, height, width, channels = model.input_shape  
print(height, width, channels)
for fname in os.listdir(image_folder):
    if not (fname.lower().endswith(".jpg") or fname.lower().endswith(".png")):
        continue

    # 1) Bild laden und in den richtigen Farbmodus bringen
    img = Image.open(os.path.join(image_folder, fname))
    if channels == 1:
        img = img.convert("L")
    else:
        img = img.convert("RGB")

    width1, height1 = img.size
    pixel_anzahl1 = width * height
    farbmodus1 = img.mode  # z. B. "RGB", "RGBA", "L", etc.

    print(f"Breite: {width1} Pixel")
    print(f"Höhe: {height1} Pixel")
    print(f"Gesamtanzahl der Pixel: {pixel_anzahl1}")
    print(f"Farbmodus: {farbmodus1}")


    # 2) Auf 48×48 skalieren
    img = img.resize((width, height))
    img.save(os.path.join(image_folder, "neu_gespeichert.jpg"))

    # 3) In Array & normalisieren
    arr = np.array(img, dtype=np.float32) 
    if channels == 1:
        arr = np.expand_dims(arr, axis=-1)

    # 4) Batch-Dimension hinzufügen
    batch = np.expand_dims(arr, axis=0)

    # 5) Vorhersage
    preds = model.predict(batch)           # Form: [[p_class0, p_class1]]
    class_idx = np.argmax(preds, axis=1)[0]

    print(f"{fname} → Wahrscheinlichkeiten={preds[0]}, Vorhergesagte Klasse={class_idx}")