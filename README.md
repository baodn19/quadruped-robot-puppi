# My WAVEGO essential information
- SSH into Raspberry Pi: `ssh baodn19@<IP>`
- Control address: 192.168.4.1

# Core Functions
## Control basic movement with ESP32:
- In loop() of `WAVEGO.ino`:
    - Front: moveFB = 1;
    - Back: moveFB = -1;
    - Right: moveLR = 1;
    - Left: moveLR = -1;

## Control basic movement with Raspberry Pi:
- In `__main__` of `robot.py`:
``` cpp
<action>()
time.sleep(<duration>)
<stopAction>()
```

## Startup the camera: [Camera Sofware](https://www.raspberrypi.com/documentation/computers/camera_software.html#building-libcamera-and-rpicam-apps)

## Setup virtual environment:
- Create: `python3.11 -m venv --system-site-packages <name>`
- Activate: `source <name>/bin/activate`


# Potential application
## Manual control with PS4
## Follow line via object detection