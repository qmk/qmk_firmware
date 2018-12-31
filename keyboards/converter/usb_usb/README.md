USB to USB keyboard protocol converter
======================================
A small device to connect between your USB keyboard and your PC that makes (almost) every keyboard fully programmable.
Original code from the [TMK firmware](https://github.com/tmk/tmk_keyboard/tree/master/converter/usb_usb). Ported to QMK by [Balz Guenat](https://github.com/BalzGuenat).

Keyboard Maintainer: [Balz Guenat](https://github.com/BalzGuenat)  
Hardware Supported: [Hasu's USB-USB converter](https://geekhack.org/index.php?topic=69169.0), [Pro Micro + USB Host Shield](https://geekhack.org/index.php?topic=80421.0), maybe more  
Hardware Availability: [GH thread](https://geekhack.org/index.php?topic=72052.0), self-built

Make example for this keyboard (after setting up your build environment):

    make converter/usb_usb:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

Note that you have to choose the right hardware variant as your subproject, otherwise you will probably have issues.

Troubleshooting & Known Issues
------------------------------
If something doesn't work, it's probably because of the CPU clock. 
Be sure to select the correct subproject (the middle part of the `make` argument) according to your hardware. 
If you are sure you have this correct, try changeing the default in `usb_usb/rules.mk` or overriding the value in the `rules.mk` of your keymap.

The Pro Micro variant uses a 3.3V Pro Micro and thus runs at 8MHz, hence the following line in `usb_usb/pro_micro/rules.mk`:
`F_CPU = 8000000`
The converter sold by Hasu runs at 16MHz and so the corresponding line in `usb_usb/hasu/rules.mk` is:
`F_CPU = 16000000`

Getting the Hardware
--------------------
There are two options to get a converter: You can buy one from Hasu or build one yourself.

### Buy a Converter
You can buy a fully assembled converter from me here:
https://geekhack.org/index.php?topic=69169.0

### Build one yourself using Arduino Leonardo + Circuit@Home USB Host Shield 2.0
Buying Arduino Leonardo and USB Host Shield 2.0(from Circuit@home) will be better, you won't need even soldering iron.
http://arduino.cc/en/Main/ArduinoBoardLeonardo
https://www.circuitsathome.com/arduino_usb_host_shield_projects/

Other compatible boards like Arduino's Shield will also work well but I think Sparkfun's needs to be modified.
http://arduino.cc/en/Main/ArduinoUSBHostShield
https://www.sparkfun.com/products/9947

Also Pro Micro 3.3V(not Mini) or Teensy with mini host shield will work with some fixes on signal/power routing.
[Build guide](https://geekhack.org/index.php?topic=80421.0)
https://www.circuitsathome.com/arduino_usb_host_shield_projects/
https://www.sparkfun.com/products/12587
https://www.pjrc.com/teensy/td_libs_USBHostShield.html

Limitations
----------
Only supports 'HID Boot protocol'.
Note that the converter can host only USB "boot protocol" keyboard(6KRO), not NKRO, it is possible to support NKRO keyboard but you will need to write HID report parser for that. Every NKRO keyboard can have different HID report and it is difficult to support all kind of NKRO keyboards in the market.

Resources
--------
Hasu's main thread for the converter
    https://geekhack.org/index.php?topic=69169.0
Build guide for the Pro Micro variant
    https://geekhack.org/index.php?topic=80421.0
Original TMK version of the converter
    https://github.com/tmk/tmk_keyboard/tree/master/converter/usb_usb
USB Host Shield 2.0
    https://www.circuitsathome.com/arduino_usb_host_shield_projects/
USB Host Shield 2.0 source
    https://github.com/felis/USB_Host_Shield_2.0
Arduino USB Host Shield (with bootst converter)
    http://arduino.cc/en/Main/ArduinoUSBHostShield
Arduino source
    https://github.com/arduino/Arduino
Initial release of TMK USB-USB converter
    https://geekhack.org/index.php?topic=33057.msg653549#msg653549
    http://deskthority.net/workshop-f7/is-remapping-a-usb-keyboard-using-teensy-possible-t2841-30.html#p74854
Arduino-based hardware keyboard remapper - Colemak forum
    http://forum.colemak.com/viewtopic.php?id=1561
Teensy + Host Shield
    http://www.pjrc.com/teensy/td_libs_USBHostShield.html
