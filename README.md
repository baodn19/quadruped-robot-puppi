<div align="center" style="text-align: center;">

<h1>PupPi</h1>

<p>
  <b>PupPi is a quadruped robot dog that I used to learn computer vision and SLAM.</b>
</p>

[![LinkedIn](https://img.shields.io/badge/LinkedIn-blue)](www.linkedin.com/in/bao-dinh-usf)
[![Portfolio](https://img.shields.io/badge/Portfolio-white)](https://baodn19.weebly.com/)

</div>

<table>
  <tr>
    <td><a href="https://youtube.com/shorts/zSF6cKLQlCA?feature=share" title="PupPi Showcasing"><img src="https://github.com/baodn19/quadruped-robot-puppi/blob/main/Asset/PupPi_showcase.jpg"></a></td>
  </tr>
</table>

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
