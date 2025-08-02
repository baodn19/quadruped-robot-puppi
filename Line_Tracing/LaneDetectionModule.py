import cv2
import numpy as np
import utilities as ut

def get_lane_curve(image):

    image_threshold = ut.threshold(image)

    height, width = image.shape[:2]
    points = ut.trackbars_value()
    image_warped = ut.perspective_warp(image, points, width, height)
    image_points = ut.draw_points(image, points)

    base_point, image_histogram = ut.histogram_analysis(image_warped, display_chart=True)

    # cv2.imshow("Thresholded Image", image_threshold)
    # cv2.imshow("Warped Image", image_warped)
    # cv2.imshow("Pointed Image", image_points)
    cv2.imshow("Histogram", image_histogram)

    return None

if __name__ == "__main__":
    capture = cv2.VideoCapture("vid1.mp4")

    initial_trackbar_values = [53, 204, 78, 131]  # Initial values for the trackbars
    ut.initialize_trackbars(initial_trackbar_values)
    frame_counter = 0

    while True:
        frame_counter += 1
        if capture.get(cv2.CAP_PROP_FRAME_COUNT) == frame_counter:
            capture.set(cv2.CAP_PROP_POS_FRAMES, 0)
            frame_counter = 0

        success, image = capture.read()
        image = cv2.resize(image, (480, 240))
        get_lane_curve(image) 

        cv2.imshow("Video", image)
        cv2.waitKey(1)