# ano

95 key custom keyboard made as DIY project

* Keyboard Maintainer: [keebnewb](https://github.com/sauvehoo)
* Hardware Supported: Proton C
* Hardware Availability: Not available

Make example for this keyboard (after setting up your build environment):

    make ano:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Bootloader

Enter the bootloader in 2 ways:

* Physical reset button: Briefly press the button on the back of the PCB - or short reset and ground pins
* Keycode in layout: Press the key mapped to `QK_BOOT`.  By default this is done by pressing RALT to access second layer and pressing rotary encoder down. 