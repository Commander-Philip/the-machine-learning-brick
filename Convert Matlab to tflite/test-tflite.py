import sensor, time
import ml
import gc


print("trying to load")
print("Free mem before loading model:", gc.mem_free());
try:
    net = ml.Model("models/sign-classifier.tflite", load_to_fb=False)
except Exception as e:
    print(e)
print("Free mem before loading model:", gc.mem_free());
print("loaded")
labels = ['Klasse 0', 'Klasse 1']


#sensor.reset()
#sensor.set_pixformat(sensor.RGB565)
#sensor.set_framesize(sensor.QVGA)
#sensor.skip_frames(time=2000)

clock = time.clock()
while(True):
    clock.tick()
    img = sensor.snapshot()
    try:
        #out = tf.classify("/models/sign-classifier.tflite",img)
        pass
    except Exception as e:
        print(e)
   # print('Prediction:', labels[out[0].output()])
