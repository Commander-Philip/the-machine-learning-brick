import sensor
import image
import time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)  # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.HD)  # Set frame size to HD (1280x720)
sensor.set_hmirror(True)
sensor.set_vflip(True)
sensor.skip_frames(time=2000)  # Wait for settings take effect.


old = time.ticks_ms()
old_2 = old
sigma = 2
max_sign_radius = 60
drawDebugVisuals = False

def changeSigma():
    global old_2
    global sigma
    maxSigma = 3
    now = time.ticks_ms()
    if(now-old_2>4000 and sigma <maxSigma):
        sigma = sigma+1
        if(sigma == maxSigma):
            sigma = 1
        print(sigma)
        old_2 = now


def crop_circle_images(image_to_crop: image.Image, circles): # circles: List[circles]
    detected_signs = []

    for circle in circles:
        if drawDebugVisuals:
            picture_rgb.draw_circle(circle.x(), circle.y(), circle.r(), color=(0, 0, 255), thickness=4, fill=False)
            picture_rgb.draw_cross(circle.x(),circle.y(),color=(255,0,0), thickness=4)
        try:
            detected_signs.append(
                picture_rgb.crop(# 200 200 3
                    roi=(int(circle.x()-100),
                    int(circle.y()-100),
                    200,
                    200
                )
            )
        )
        except Exception as e:
            print(f"Fehler beim Zuschneiden: {e}")

    return detected_signs


while True:
    cycle_begin_ms = time.ticks_ms()

    picture_rgb = sensor.snapshot()
    circles = picture_rgb.find_circles(
        roi=(0,240,1280,360),
        threshold=3400, x_margin=25,
        y_margin=30,
        r_margin=30,
        r_min=26,
        r_max=max_sign_radius,
        r_step=2
    )

    detected_signs = crop_circle_images(picture_rgb, circles)
    print(f"Anzahl erkannter Kreise: {len(detected_signs)}")

    print(f"Zykluszeit: {time.ticks_ms()-cycle_begin_ms}")
    old = cycle_begin_ms



# MATLAB Code:

#grayImage = rgb2gray(I);

#grayImagefilter = imgaussfilt(grayImage, 2); % Rauschentfernung

#edges = edge(grayImage, 'Canny'); % Verwendung des Canny-Algorithmus

#binaryImg = imbinarize(grayImage);

#Test Kreiserkennung
#[centers, radii] = imfindcircles(I, [15, 50], 'Sensitivity', 0.90)
#viscircles(centers, radii,'EdgeColor','b');
#imshow(grayImage);
#[centers, radii] = imfindcircles(grayImage, [15, 50], 'Sensitivity', 0.9)
#viscircles(centers, radii,'EdgeColor','b');

