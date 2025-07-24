import cv2
import numpy as np
#import utlis

if __name__ == "__main__":
    cap = cv2.VideoCapture("vid1.mp4")
    while True:
        success, img = cap.read()
        img = cv2.resize(img, (480, 240))
        cv2.imshow("Video", img)
        cv2.waitKey(1)