# pi60_hse

The pi60 HSE is the update to the original 1up Keyboards 60% HSE. This keyboard features a multi layout hot swap PCB with options for split backspace, split right shift, and 6.25u and 7u space bottom rows. The controller is a Raspberry Pi rp2040 microcontroller.

* Keyboard Maintainer: [ziptyze](https://github.com/ziptyze)
* Hardware Availability: (https://1upkeyboards.com/shop/controllers/1upkeyboards-pi60hse-60-pcb/)

Make example for this keyboard (after setting up your build environment):

    make 1upkeyboards/pi60_hse:default

Flashing example for this keyboard:

    make 1upkeyboards/pi60_hse:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Bootloader button**: Hold the button on the back of the PCB and plug in the keyboard
