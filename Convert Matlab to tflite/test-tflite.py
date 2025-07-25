import ml
import gc


print("trying to load")
print("Free mem before loading model:", gc.mem_free());
try:
    net = ml.Model("/sdcard/models/sign-classifier.tflite", load_to_fb=True)
    print("loaded")
except Exception as e:
    print(e)
print("Free mem before loading model:", gc.mem_free());
labels = ['Klasse 0', 'Klasse 1']

