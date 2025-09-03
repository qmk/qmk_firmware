# falsonix/fx19

![falsonix/fx19](https://i.imgur.com/UGExzJl.png)

A small, 18-key number pad for use with modern computers. (Yes, the name says 19 and this is due to me miscounting the keys and realizing only after I'd named everything in firmware and hardware). Includes RGB for maximum performance.

* Keyboard Maintainer: [falsonix](https://github.com/falsonix)
* Hardware Supported: *FX19 Numpads*
* Hardware Availability: *DIY by the enduser*

Make example for this keyboard (after setting up your build environment):

    make falsonix/fx19:default

Flashing example for this keyboard:

    make falsonix/fx19:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the front of the PCB
