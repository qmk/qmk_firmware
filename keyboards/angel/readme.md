# Angel

![Angel](https://raw.githubusercontent.com/jamessa/Angel/master/attachments/handwire.jpeg)

Angel is a minimalist symmetrical stagger keyboard with thumb position in mind. Layout and hand wire guide is on [Github](https://github.com/jamessa/Angel).

* Keyboard Maintainer: [James Sa](https://github.com/jamessa)
* Hardware Supported: Hand wire
* Hardware Availability: Send me an email, I'll help you to make one.

To build the firmware.

    qmk compile -kb angel -km default
or

    make angel:default

To flash the Pro Micro board, short `RESET` pin and run following command.

     avrdude -p atmega32u4 -c avr109 -U flash:w:angel_default.hex:i -P /dev/tty.usbmodem14201

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools), the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide), and the [hand-wiring guide](https://docs.qmk.fm/#/hand_wire) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
