import numpy as np
import os
import tensorflow as tf
from PIL import Image
import tf_model as tf_model

model_dir = "my_saved_model"

model = tf_model.load_model()
model.export(model_dir)

image_dir="Quantisierungsbilder"
# img = Image.open("Quantisierungsbilder/Geschwindigkeitsbegrenzung_30_3.jpg").convert("RGB")
# img = img.resize((48, 48), box=(img.width/2-24, img.height/2-24, 48, 48))
# img.save("test.jpg")

imgSize=48
# Lade 100 Bilder für die Quantisierung
def load_images_from_folder(folder, image_size=(imgSize, imgSize), max_images=100):
    images = []
    count = 0
    for filename in os.listdir(folder):
        if filename.lower().endswith((".png", ".jpg", ".jpeg", ".bmp")):
            img_path = os.path.join(folder, filename)
            img = Image.open(img_path).convert("RGB")
            img = img.resize(image_size)
            img = np.asarray(img).astype(np.float32) / 255.0  # Normalisierung
            print("Bild geladen mit Shape:", img.shape)
            images.append(img)
            count += 1
            if count >= max_images:
                break
    return images

dataset = load_images_from_folder(image_dir)

def representative_dataset():
    for image in dataset:
        image = np.expand_dims(image, axis=0)  # [1, 200, 200, 3]
        if image.shape != (1, imgSize, imgSize, 3):
            print("❌ Falsche Bildform:", image.shape)
            continue
        yield [image.astype(np.float32)]

# Load saved model
converter = tf.lite.TFLiteConverter.from_saved_model(model_dir)

# Enable Quantization
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset= representative_dataset
converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
converter._experimental_lower_tensor_list_ops = False
converter.inference_type = tf.int8
converter.inference_input_type = tf.int8
converter.inference_output_type = tf.int8

tflite_model = converter.convert()
with open("sign-classifier.tflite", 'wb') as f:
    f.write(tflite_model)

print("Quantisiertes TensorFlow Lite model wurde erfolgreich gespeichert!")
