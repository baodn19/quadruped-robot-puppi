import cv2
import numpy as np
import time

frame_width = 640
frame_height = 480

capture = cv2.VideoCapture(0)
capture.set(3, frame_width)
capture.set(4, frame_height)
time.sleep(2)  # Allow camera to warm up

def empty(a):
    pass

# Create track bars for HSV values
cv2.namedWindow("HSV")
cv2.resizeWindow("HSV", 640, 240)
cv2.createTrackbar("HUE Min", "HSV", 0, 179, empty)
cv2.createTrackbar("HUE Max", "HSV", 179, 179, empty)
cv2.createTrackbar("SAT Min", "HSV", 0, 255, empty)
cv2.createTrackbar("SAT Max", "HSV", 255, 255, empty)
cv2.createTrackbar("VAL Min", "HSV", 0, 255, empty)
cv2.createTrackbar("VAL Max", "HSV", 255, 255, empty)

while True:
    ret, image = capture.read()
    
    # Set resolution *before* checking if the camera is opened
    capture.set(cv2.CAP_PROP_FRAME_WIDTH, frame_width)
    capture.set(cv2.CAP_PROP_FRAME_HEIGHT, frame_height)

    # IMPORTANT: Check if the camera is actually opened
    if not ret:
        print("Error: Could not open video stream.")
        exit()

    print(f"Attempting to set resolution to: {frame_width}x{frame_height}")
    print(f"Actual resolution after setting: {capture.get(cv2.CAP_PROP_FRAME_WIDTH)}x{capture.get(cv2.CAP_PROP_FRAME_HEIGHT)}")

    image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # Read HSV values from track bars
    hue_min = cv2.getTrackbarPos("HUE Min", "HSV")
    hue_max = cv2.getTrackbarPos("HUE Max", "HSV")
    sat_min = cv2.getTrackbarPos("SAT Min", "HSV")
    sat_max = cv2.getTrackbarPos("SAT Max", "HSV")
    val_min = cv2.getTrackbarPos("VAL Min", "HSV")
    val_max = cv2.getTrackbarPos("VAL Max", "HSV")

    lower_hsv = np.array([hue_min, sat_min, val_min])
    upper_hsv = np.array([hue_max, sat_max, val_max])
    mask = cv2.inRange(image_hsv, lower_hsv, upper_hsv)

    image_result = cv2.bitwise_and(image, image, mask=mask) # Join the mask with the original image

    # Stack images horizontally
    mask = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR) # Convert mask to BGR which is same as original image and image_result
    stacked_images = np.hstack([image, image_result, mask])
    cv2.imshow("HSV Panel", stacked_images)

    # Exit on 'q' key press
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

capture.release()
cv2.destroyAllWindows()