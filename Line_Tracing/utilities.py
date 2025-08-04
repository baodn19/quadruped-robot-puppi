import cv2
import numpy as np

def nothing(a):
    pass

def threshold(image):
    """
    Description: converts an image to HSV and applies a threshold to isolate white colors.
    Parameters:
    - image: Input image in BGR format.
    """

    image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # Define thresholds for white color in HSV
    lower_white = np.array([80, 0, 0])
    upper_white = np.array([255, 160, 255])
    # lower_white = np.array([92, 0, 16])
    # upper_white = np.array([148, 255, 126])
    mask_white = cv2.inRange(image_hsv, lower_white, upper_white)

    return mask_white

def perspective_warp(image, points, width, height):
    """
    Description: Applies a perspective warp to the image based on the given points.
    Parameters:
    - image: Input image in BGR format.
    - points: List of four points defining the region to warp.
    - width: Width of the output image.
    - height: Height of the output image.
    """

    source_points = np.float32(points)
    destination_points = np.float32([[0, 0], [width, 0], [0, height], [width, height]])

    matrix = cv2.getPerspectiveTransform(source_points, destination_points)
    warped_image = cv2.warpPerspective(image, matrix, (width, height))

    return warped_image

def initialize_trackbars(trackbar_value, width_target=480, height_target=240):
    """
    Description: Initializes trackbars for HSV values.
    Parameters:
    - trackbar_value: Initial value for the trackbars.
    - width_target: Target width for the perspective warp.
    - height_target: Target height for the perspective warp.
    """

    cv2.namedWindow("Perspective Warp")
    cv2.resizeWindow("Perspective Warp", width_target, height_target)
    
    cv2.createTrackbar("Width Top", "Perspective Warp", trackbar_value[0], width_target // 2, nothing)
    cv2.createTrackbar("Height Top", "Perspective Warp", trackbar_value[1], height_target, nothing)
    cv2.createTrackbar("Width Bottom", "Perspective Warp", trackbar_value[2], width_target // 2, nothing)
    cv2.createTrackbar("Height Bottom", "Perspective Warp", trackbar_value[3], height_target, nothing)

def trackbars_value(width_target=480, height_target=240):
    """
    Description: Retrieves the current values from the trackbars.
    Parameters:
    - width_target: Target width for the perspective warp.
    - height_target: Target height for the perspective warp.
    """

    width_top = cv2.getTrackbarPos("Width Top", "Perspective Warp")
    height_top = cv2.getTrackbarPos("Height Top", "Perspective Warp")
    width_bottom = cv2.getTrackbarPos("Width Bottom", "Perspective Warp")
    height_bottom = cv2.getTrackbarPos("Height Bottom", "Perspective Warp")

    points = np.float32([
        [width_top, height_top], 
        [width_target - width_top, height_top], 
        [width_bottom, height_bottom], 
        [width_target - width_bottom, height_bottom]
    ])

    return points

def draw_points(image, points):
    """
    Description: Draws the points on the image for visualization.
    Parameters:
    - image: Input image in BGR format.
    - points: List of four points to draw.
    """
    image = image.copy()

    for i in range(4):
        cv2.circle(image, (int(points[i][0]), int(points[i][1])), 15, (0, 255, 0), cv2.FILLED)

    return image

def histogram_analysis(image, minimum_percentage=0.1, display_chart=False, percentage_region_analyzed=1):
    """
    Description: Analyzes the histogram of the image to find the lane lines.
    Parameters:
    - image: Input warped image
    - minimum_percentage: Minimum percentage of pixels to consider a lane line.
    - display_chart: Whether to display the histogram chart.
    """

    if percentage_region_analyzed == 1:
        histogram_values = np.sum(image, axis=0)
    else:
        histogram_values = np.sum(image[int(image.shape[0] * percentage_region_analyzed):, :], axis=0)

    max_value = np.max(histogram_values)
    minimum_value = max_value * minimum_percentage

    line_index = np.where(histogram_values >= minimum_value)
    base_point = int(np.average(line_index))
    
    if display_chart:
        image_histogram = np.zeros((image.shape[0], image.shape[1], 3), dtype=np.uint8)
        for i, intensity in enumerate(histogram_values):
            cv2.line(image_histogram, (i, image.shape[0]), (i, int(image.shape[0] - intensity // 255 * percentage_region_analyzed)), (255, 0, 0), 1)
            cv2.circle(image_histogram, (base_point, image.shape[0]), 20, (0, 255, 0), cv2.FILLED)

        return base_point, image_histogram
    
    return base_point