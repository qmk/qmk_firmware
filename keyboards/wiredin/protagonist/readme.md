# WiredIn Protagonist

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: proprietary PCB using STM32F411 microcontroller;
* Hardware Availability: the Protagonist entered Group Buy in february 2024 and as of april 2025 there were no more public sales.

The Protagonist is a 60% keyboard designed by WiredIn and PCB designed by [Gondolindrim](http://github.com/Gondolindrim), who is also the firwmare maintainer.

## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (escape in the default keymap) and plug in the keyboard;
* **Physical reset button**: press the button on the back of the PCB and hold it for 5 seconds;
* **Keycode in layout**: Press the key mapped to `RESET`; in the default layout, that is top left key ('escape') in layer 1.

### How to compile and flash

The Protagonist has two PCB versions: PRO-S (solderable) and PRO-H (hotswap). After checking what PCB you own and setting up your build environment, you can compile the default keymap by using one of the options below.

    make wiredin/protagonist/<version>:default

Where `<version>` can be `pro_s` or `pro_h`. And use dfu-util in the command line or through a GUI like QMK toolbox to upload the firmware to the PCB. To directly flash the PCB after it is put into a DFU state, use:

    make wiredin/protagonist/<version>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
