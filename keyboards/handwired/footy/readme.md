# Footy

![Footy Foot Pedal](https://i.imgur.com/ZdvlgRB.jpeg)

*Footy is a foot pedal intended to be used with a speech to text application like 'handy' or superwhisper. Initially developed as an assistive technology device for those with limited typing abilities.*

* Keyboard Maintainer: [CJ Pais](https://github.com/cjpais)
* Hardware Supported: [Keebio Stampy](https://keeb.io/products/stampy-rp2040-usb-c-controller-board-for-handwiring)
* Hardware Availability: [3D printed case](https://makerworld.com/en/models/1185240-footy)

Make example for this keyboard (after setting up your build environment):

    make handwired/footy:default

Flashing example for this keyboard (enter the bootloader first):

    make handwired/footy:default:flash
    
or drag and drop .uf2 file on the removable storage

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Physical reset button**: Briefly double press the button on the back of the PCB

## Keymaps

Right now there are two primary keymaps, one for 'handy' and one for 'superwhisper'.

Handy's default keymap is for the center switch to be RCTRL + RGUI.

Superwhisper's default keymap is for the center switch to be LOPT + SPACE.

You can build either of these firmware images by running the following commands:

```
make handwired/footy:handy
make handwired/footy:superwhisper
```