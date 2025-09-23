import evdev

# List all input devices
devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
for device in devices:
    print(f"{device.path}: {device.name}")
