# Viendi8L PCB firmware

![8L_image](https://imgur.com/z4cuSYJh.png)

The 8L 80% (60% plus southpaw numpad) keyboard designed by Viendi, with PCB by Gondolindrim.

* Keyboard Maintainer: [Gondolindrim](https://github.com/gondolindrim)
* Hardware Availability: proprietary PCB
* Website: [Viendi](https://viendi.co/)

## How to flash

### Enter bootloader

* **Bootmagic reset**: hold down the key at (0,0) in the matrix (the encoder push) and plug in the keyboard, waiting for five seconds
* **Physical reset button**: press the button on the front of the PCB or use pliers to short the reset contacts, for at least five seconds
* **Keycode in layout**: press the key mapped to `RESET` if it is available (ESC key at layer 1 in the default layout)

## Compile firmware

After accessing the DFU state in your PCB, build the default layout using:

    make viendi8l:default

Then download the resulting binary `*bin` file using `dfu-util` or QMK Toolbox.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
