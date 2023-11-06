# Redragon K617 (QMK ported)

<iframe src="https://drive.google.com/file/d/1CCUMS5K3tSH-BuMOKQoJzFx8rPs3vShe/preview" width="640" height="480" allow="autoplay"></iframe>

*Firmware for Redragon K617 keyboard to be used with promicro after porting*

* Keyboard Maintainer: *[abhijithabhiakl](https://github.com/abhijithabhiakl)*
* Hardware Supported: *Redragon K617, Pro micro, Atmega32u4*
* Hardware Availability: *[Redragon K617](https://redragon.in/products/fizz-k617-60-wired-mechanical-keyboard-white-and-grey-red-switches)*

Make example for this keyboard (after setting up your build environment):

    make rd_61_qmk:default

Flashing example for this keyboard:

    make rd_61_qmk:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Hardware details: 

#### Matrix layout
<iframe src="https://drive.google.com/file/d/12UHowKXnNG-REDD3FefsG3IrP9qF-Fgm/preview" width="640" height="480" allow="autoplay"></iframe>

#### Schematic


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
