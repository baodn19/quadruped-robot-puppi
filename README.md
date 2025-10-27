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
    <td><a href="https://youtube.com/shorts/zSF6cKLQlCA?feature=share" title="PupPi Showcasing"><img src="https://github.com/commaai/openpilot/assets/8762862/2f7112ae-f748-4f39-b617-fabd689c3772"></a></td>
    <td><a href="https://youtu.be/VHKyqZ7t8Gw" title="Video By Logan LeGrand"><img src="https://github.com/commaai/openpilot/assets/8762862/92351544-2833-40d7-9e0b-7ef7ae37ec4c"></a></td>
    <td><a href="https://youtu.be/SUIZYzxtMQs" title="A drive to Taco Bell"><img src="https://github.com/commaai/openpilot/assets/8762862/05ceefc5-2628-439c-a9b2-89ce77dc6f63"></a></td>
  </tr>
</table>

- SSH into Raspberry Pi: `ssh baodn19@<IP>`

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
