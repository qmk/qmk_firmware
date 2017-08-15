USB to USB keyboard protocol converter
======================================
Original code from Hasu's TMK firmware. Ported to QMK by Coloneljesus.

This port has been tested only on the Pro Micro variant described in the next section.

See for detail and discussion.
https://geekhack.org/index.php?topic=69169.0


Hardware requirement
--------------------
There are two options.

### TMK USB-USB Converter
You can buy a fully assembled converter from me here.

    https://geekhack.org/index.php?topic=69169.0

### Arduino Leonardo + Circuit@Home USB Host Shield 2.0
Buying Arduino Leonardo and USB Host Shield 2.0(from Circuit@home) will be better, you won't need even soldering iron.

    http://arduino.cc/en/Main/ArduinoBoardLeonardo 
    https://www.circuitsathome.com/products-page/arduino-shields/usb-host-shield-2-0-for-arduino-assembled/

Other compatible boards like Arduino's Shield will also work well but I think Sparkfun's needs to be modified.

    http://arduino.cc/en/Main/ArduinoUSBHostShield
    https://www.sparkfun.com/products/9947

Also Pro Micro 3.3V(not Mini) or Teensy with mini host shield will work with some fixes on signal/power routing.

    https://www.circuitsathome.com/products-page/arduino-shields/usb-host-shield-for-arduino-pro-mini
    https://www.sparkfun.com/products/12587
    https://www.pjrc.com/teensy/td_libs_USBHostShield.html



Build firmware
--------------
Follow normal QMK build instructions to get a binary file. Flashing depends on you hardware.

Limitation
----------
Only supports 'HID Boot protocol'.

Note that the converter can host only USB "boot protocol" keyboard(6KRO), not NKRO, it is possible to support NKRO keyboard but you will need to write HID report parser for that. Every NKRO keyboard can have different HID report and it is difficult to support all kind of NKRO keyboards in the market.



Keymap editor
-------------
You can editor keymap and download firmware with web brwoser.

- http://www.tmk-kbd.com/tmk_keyboard/editor/unimap/?usb_usb



Update
------
2014/12/11  Added Hub support(confirmed with HHKB pro2)
2016/09/10  Unimap editor support
2016/10/18  Fix LED state at startup
2017/08/16  Port to QMK


Resource
--------
USB Host Sheild 2.0
    https://www.circuitsathome.com/products-page/arduino-shields/usb-host-shield-2-0-for-arduino
    https://www.circuitsathome.com/products-page/arduino-shields/usb-host-shield-for-arduino-pro-mini
USB Host Sheild 2.0 source
    https://github.com/felis/USB_Host_Shield_2.0
Arduino USB Host Shield(with bootst converter)
    http://arduino.cc/en/Main/ArduinoUSBHostShield
Arduino source
    https://github.com/arduino/Arduino/hardware/arduino/{cores,variants}
Initial release of TMK USB-USB converter
    https://geekhack.org/index.php?topic=33057.msg653549#msg653549
    http://deskthority.net/workshop-f7/is-remapping-a-usb-keyboard-using-teensy-possible-t2841-30.html#p74854
Arduino-based hardware keyboard remapper - Colemak forum
    http://forum.colemak.com/viewtopic.php?id=1561
Teensy + Host Shield
    http://www.pjrc.com/teensy/td_libs_USBHostShield.html
