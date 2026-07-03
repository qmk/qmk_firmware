#!/usr/bin/env python3

import usb

USB_INTERFACE_CLASS_HID = 0x03

def usb_device_spec(spec):
    major = spec >> 8
    minor = (spec >> 4) & 0xF
    return f"{major}.{minor}"

def usb_device_speed(speed):
    if speed == 1:
        return "Low-speed"
    elif speed == 2:
        return "Full-speed"
    elif speed == 3:
        return "High-speed"
    elif speed == 4:
        return "SuperSpeed"
    elif speed == 5:
        return "SuperSpeed+"

    return "Speed unknown"

def usb_hid_interface_subclass(subclass):
    if subclass == 0x00:
        return "None"
    elif subclass == 0x01:
        return "Boot"
    else:
        return f"Unknown (0x{subclass:02X})"

def usb_hid_interface_protocol(subclass, protocol):
    if subclass == 0x00 and protocol == 0x00:
        return "None"
    elif subclass == 0x01:
        if protocol == 0x00:
            return "None"
        elif protocol == 0x01:
            return "Keyboard"
        elif protocol == 0x02:
            return "Mouse"

    return f"Unknown (0x{protocol:02X})"

def usb_interface_polling_rate(speed, interval):
    if speed >= 3:
        return f"{interval * 125} μs ({8000 // interval} Hz)"
    else:
        return f"{interval} ms ({1000 // interval} Hz)"

if __name__ == '__main__':
    devices = usb.core.find(find_all=True)

    for device in devices:
        try:
            configuration = device.get_active_configuration()
        except NotImplementedError:
            continue

        hid_interfaces = []
        for interface in configuration.interfaces():
            if interface.bInterfaceClass == USB_INTERFACE_CLASS_HID:
                hid_interfaces.append(interface)

        if len(hid_interfaces) > 0:
            print(f"{device.manufacturer} {device.product} ({device.idVendor:04X}:{device.idProduct:04X}:{device.bcdDevice:04X}), {usb_device_spec(device.bcdUSB)} {usb_device_speed(device.speed)}")

            for interface in hid_interfaces:
                print(f"└─ HID Interface {interface.bInterfaceNumber}")
                subclass = interface.bInterfaceSubClass
                protocol = interface.bInterfaceProtocol
                print(f"   ├─ Subclass: {usb_hid_interface_subclass(subclass)}")
                print(f"   ├─ Protocol: {usb_hid_interface_protocol(subclass, protocol)}")

                for endpoint in interface.endpoints():
                    endpoint_address = endpoint.bEndpointAddress & 0xF
                    endpoint_direction = "IN" if endpoint.bEndpointAddress & 0x80 else "OUT"
                    print(f"   └─ Endpoint {endpoint_address} {endpoint_direction}")
                    print(f"      ├─ Endpoint Size: {endpoint.wMaxPacketSize} bytes")
                    print(f"      └─ Polling Rate: {usb_interface_polling_rate(device.speed, endpoint.bInterval)}")
