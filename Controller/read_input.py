from evdev import InputDevice, categorize, ecodes
import time

# Find the controller device (usually /dev/input/event0 or event1)
gamepad = InputDevice('/dev/input/event5')

print(f"Connected to: {gamepad.name}")

# Read controller events
for event in gamepad.read_loop():
    if event.type == ecodes.EV_KEY and event.value == 1:
        print(f"Button {event.code} pressed")
    elif event.type == ecodes.EV_ABS:
        print(f"Analog input {event.code}: {event.value}")