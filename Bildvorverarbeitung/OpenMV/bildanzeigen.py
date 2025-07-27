import sensor, image, os, time

# 1) Sensor für IDE-Framebuffer einrichten
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

# 1) Blackboard-Canvas holen (QVGA Framebuffer)
fb = sensor.snapshot()  # liefert Framebuffer-Image in 320×240

# 3) Verzeichnisinhalt checken und Pfad anpassen
pfad = "/sdcard/Quantisierungsbilder/Geschwindigkeitsbegrenzung_30_100.jpg"                   # Name deines Bildes hier

# 4) Bild von der SD-Karte laden
img = image.Image(pfad)
w, h = img.width(), img.height()

fb.draw_image(img, 0, 0, roi=[0,0,320,240])



#6) Framebuffer an die IDE senden
sensor.flush()
print("test3")
# 7) 2 Sekunden anhalten
time.sleep(2)

