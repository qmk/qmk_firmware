# keyten kt60HS-T V3

60% MX Hot-Swap Tsangan PCB

![kt60HS-T image](https://live.staticflickr.com/65535/54942233930_c83933dd23_b.jpg)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: keyten kt60HS-T V3
* Hardware Availability: private GB

Make example for this keyboard (after setting up your build environment):

    make keyten/kt60hs_t/v3:default
	
Flashing example for this keyboard:

    make keyten/kt60hs_t/v3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to `QK_BOOT` if it is available
* Physical reset button: Hold the button on the back of the PCB
