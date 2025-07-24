import cv2
import numpy as np
import utilities as ut

def get_lane_curve(image):

    image_threshold = ut.thresholding(image)

    cv2.imshow("Thresholded Image", image_threshold)

    return None

if __name__ == "__main__":
    capture = cv2.VideoCapture("vid1.mp4")
    while True:
        success, image = capture.read()
        image = cv2.resize(image, (480, 240))
        get_lane_curve(image) 

        cv2.imshow("Video", image)
        cv2.waitKey(1)