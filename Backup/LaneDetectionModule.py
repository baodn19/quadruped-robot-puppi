import cv2
import numpy as np
import utilities as ut

curve_list = []
average_curve_value = 10  # Number of frames to average the curve over

def get_lane_curve(image, display=2):
    """
    Description: This function processes an image to detect lane curves by applying a series of transformations and analyses.
    Parameters:
    - image (numpy.3darray): The input image from which lane curves are to be detected.
    - display (int): The display mode for the output. Default is 2, which shows the everything.1 shows the resulting curve, and 0 shows nothing.
    """
    image_threshold = ut.threshold(image)

    # Generate different images for perspective warp 
    height, width = image.shape[:2]
    points = ut.trackbars_value()
    image_warped = ut.perspective_warp(image_threshold, points, width, height)
    image_points = ut.draw_points(image, points)

    # Perform histogram analysis to find the lane curves
    middle_point, image_histogram = ut.histogram_analysis(image_warped, display_chart=True, minimum_percentage=0.5, percentage_region_analyzed=25)
    curve_average_point = ut.histogram_analysis(image_warped, minimum_percentage=0.9) # minimum percentage of 0.9 to find the most prominent lane line as the initial point
    raw_curve = curve_average_point - middle_point

    # Take average of the curve to smooth it out and eliminate noise
    curve_list.append(raw_curve)
    if len(curve_list) > average_curve_value:
        curve_list.pop(0)
    average_curve = int(np.mean(curve_list))

    # Display the results based on the display mode
    if display != 0:
        image_inverse_warped = utlis.warpImg(image_warped, points, width, height, inverse=True)
        image_inverse_warped = cv2.cvtColor(image_inverse_warped, cv2.COLOR_GRAY2BGR)
        image_inverse_warped[0:height // 3, 0:width] = 0, 0, 0
        image_lane_color = np.zeros_like(image)
        image_lane_color[:] = 0, 255, 0
        image_lane_color = cv2.bitwise_and(image_inverse_warped, image_lane_color)
        image_result = cv2.addWeighted(image_result, 1, image_lane_color, 1, 0)
        middle_y = 450
        cv2.putText(image_result, str(average_curve), (width // 2 - 80, 85), cv2.FONT_HERSHEY_COMPLEX, 2, (255, 0, 255), 3)
        cv2.line(image_result, (width // 2, middle_y), (width // 2 + (average_curve * 3), middle_y), (255, 0, 255), 5)
        cv2.line(image_result, ((width // 2 + (average_curve * 3)), middle_y - 25), (width // 2 + (average_curve * 3), middle_y + 25), (0, 255, 0), 5)
        for x in range(-30, 30):
            w = width // 20
            cv2.line(image_result, (w * x + int(average_curve // 50), middle_y - 10),
                     (w * x + int(average_curve // 50), middle_y + 10), (0, 0, 255), 2)
        #fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer);
        #cv2.putText(imgResult, 'FPS ' + str(int(fps)), (20, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (230, 50, 50), 3);
    if display == 2:
        image_stacked = utlis.stackImages(0.7, ([image, imgWarpPoints, image_warped],
                                             [imgHist, image_lane_color, image_result]))
        cv2.imshow('ImageStack', image_stacked)
    elif display == 1:
        cv2.imshow('Resutlt', image_result)
 
    #### NORMALIZATION
    average_curve = average_curve/100
    if average_curve>1: average_curve ==1
    if average_curve<-1:average_curve == -1
 
    return average_curve

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

        cv2.waitKey(1)