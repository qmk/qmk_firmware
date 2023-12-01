# Raw HID :id=raw-hid

The Raw HID feature allows for bidirectional communication between QMK and the host computer over an HID interface. This has many potential use cases, such as switching keymaps on the fly or sending useful metrics like CPU/RAM usage.

In order to communicate with the keyboard using this feature, you will need to write a program that runs on the host. As such, some basic programming skills are required - more if you intend to implement complex behaviour.

## Usage :id=usage

Add the following to your `rules.mk`:

```make
RAW_ENABLE = yes
```

## Basic Configuration :id=basic-configuration

By default, the HID Usage Page and Usage ID for the Raw HID interface are `0xFF60` and `0x61`. However, they can be changed if necessary by adding the following to your `config.h`:

|Define          |Default |Description                            |
|----------------|--------|---------------------------------------|
|`RAW_USAGE_PAGE`|`0xFF60`|The usage page of the Raw HID interface|
|`RAW_USAGE_ID`  |`0x61`  |The usage ID of the Raw HID interface  |

## Sending Data to the Keyboard :id=sending-data-to-the-keyboard

To send data to the keyboard, you must first find a library for communicating with HID devices in the programming language of your choice. Here are some examples:

* **Node.js:** [node-hid](https://github.com/node-hid/node-hid)
* **C/C++:** [hidapi](https://github.com/libusb/hidapi)
* **Java:** [purejavahidapi](https://github.com/nyholku/purejavahidapi) and [hid4java](https://github.com/gary-rowe/hid4java)
* **Python:** [pyhidapi](https://pypi.org/project/hid/)

Please refer to these libraries' own documentation for instructions on usage. Remember to close the device once you are finished with it!

Next, you will need to know the USB Vendor and Product IDs of the device. These can easily be found by looking at your keyboard's `info.json`, under the `usb` object (alternatively, you can also use Device Manager on Windows, System Information on macOS, or `lsusb` on Linux). For example, the Vendor ID for the Planck Rev 6 is `0x03A8`, and the Product ID is `0xA4F9`.

It's also a good idea to narrow down the list of potential HID devices the library may give you by filtering on the usage page and usage ID, to avoid accidentally opening the interface on the same device for the keyboard, or mouse, or media keys, etc.

Once you are able to open the HID device and send reports to it, it's time to handle them on the keyboard side. Implement the following function in your `keymap.c` and start coding:

```c
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Your code goes here
    // `data` is a pointer to the buffer containing the received HID report
    // `length` is the length of the report - always `RAW_EPSIZE`
}
```

!> Because the HID specification does not support variable length reports, all reports in both directions must be exactly `RAW_EPSIZE` (currently 32) bytes long, regardless of actual payload length. However, variable length payloads can potentially be implemented on top of this by creating your own data structure that may span multiple reports.

## Receiving Data from the Keyboard :id=receiving-data-from-the-keyboard

If you need the keyboard to send data back to the host, simply call the `raw_hid_send()` function. It requires two arguments - a pointer to a 32-byte buffer containing the data you wish to send, and the length (which should always be `RAW_EPSIZE`).

The received report can then be handled in whichever way your HID library provides.

## Simple Example :id=simple-example

The following example reads the first byte of the received report from the host, and if it is an ASCII "A", responds with "B". `memset()` is used to fill the response buffer (which could still contain the previous response) with null bytes.

```c
void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t response[length];
    memset(response, 0, length);
    response[0] = 'B';

    if(data[0] == 'A') {
        raw_hid_send(response, length);
    }
}
```

On the host side (here we are using Python and the `pyhidapi` library), the HID device is opened by enumerating the interfaces on the USB device, then filtering on the usage page and usage ID. Then, a report containing a single ASCII "A" (hex `0x41`) is constructed and sent.

For demonstration purposes, the manufacturer and product strings of the device, along with the request and response, are also printed.

```python
import sys
import hid

vendor_id     = 0x4335
product_id    = 0x0002

usage_page    = 0xFF60
usage         = 0x61
report_length = 32

def get_raw_hid_interface():
    device_interfaces = hid.enumerate(vendor_id, product_id)
    raw_hid_interfaces = [i for i in device_interfaces if i['usage_page'] == usage_page and i['usage'] == usage]

    if len(raw_hid_interfaces) == 0:
        return None

    interface = hid.Device(path=raw_hid_interfaces[0]['path'])

    print(f"Manufacturer: {interface.manufacturer}")
    print(f"Product: {interface.product}")

    return interface

def send_raw_report(data):
    interface = get_raw_hid_interface()

    if interface is None:
        print("No device found")
        sys.exit(1)

    request_data = [0x00] * (report_length + 1) # First byte is Report ID
    request_data[1:len(data) + 1] = data
    request_report = bytes(request_data)

    print("Request:")
    print(request_report)

    try:
        interface.write(request_report)

        response_report = interface.read(report_length, timeout=1000)

        print("Response:")
        print(response_report)
    finally:
        interface.close()

if __name__ == '__main__':
    send_raw_report([
        0x41
    ])
```

## API :id=api

### `void raw_hid_receive(uint8_t *data, uint8_t length)` :id=api-raw-hid-receive

Callback, invoked when a raw HID report has been received from the host.

#### Arguments :id=api-raw-hid-receive-arguments

 - `uint8_t *data`  
   A pointer to the received data. Always 32 bytes in length.
 - `uint8_t length`  
   The length of the buffer. Always 32.

---

### `void raw_hid_send(uint8_t *data, uint8_t length)` :id=api-raw-hid-send

Send an HID report.

#### Arguments :id=api-raw-hid-send-arguments

 - `uint8_t *data`  
   A pointer to the data to send. Must always be 32 bytes in length.
 - `uint8_t length`  
   The length of the buffer. Must always be 32.
