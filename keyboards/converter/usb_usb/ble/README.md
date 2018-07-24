QMK BLE Adapter
===============
A small device that reads USB keyboard input and passes it on over Bluetooth LE HID.

![Picture of Adapter](https://i.imgur.com/O3VwBBJ.png)

Hardware
--------
The hardware is relatively easy to assemble. Just follow the schematic and don't forget to [cut the VBUS jumper](https://www.pjrc.com/teensy/td_libs_USBHostShield_4a.jpg).

Schematic:
![Schematic](https://i.imgur.com/s1Ia9We.png)

Part list:
* [Adafruit Feather 32u4 Bluefruit LE](https://www.adafruit.com/product/2829)
* [USB Host Mini](https://www.circuitsathome.com/arduino_usb_host_shield_projects/)
* [Pololu 5V Step-Up Voltage Regulator U3V12F5](https://www.pololu.com/product/2115)
* [Lithium Ion Battery - 3.7v 2000mAh](https://www.adafruit.com/product/2011)
* Some sort of switch to be able to turn it off

Building and Flashing
---------------------

```
make converter-usb_usb-ble
```

```
make converter-usb_usb-ble-avrdude
```