import picamera2 as pc2
import time

def initialize_camera(width=640, height=480):
    """
    Description: Initializes the camera module.
    Parameters:
    - width: Width of the camera frame.
    - height: Height of the camera frame.
    Returns:
    - camera: Initialized camera object.
    """
    camera = pc2.Picamera2()
    camera.configure(camera.create_preview_configuration(main={"size": (640, 480)}))
    camera.start()
    time.sleep(2)  # Allow camera to warm up
    
    return camera