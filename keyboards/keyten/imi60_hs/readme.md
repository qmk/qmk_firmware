# keyten imi60-HS

imi60-HS - 60% Hot-Swap PCB compatible with keyboards by La-Versa: Animi, Mirimi, Otsukimi and Abyss

![imi60-HS](https://live.staticflickr.com/65535/54904885051_339dbff9d8_b.jpg)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: keyten imi60-HS
* Hardware Availability: private GB

Make example for this keyboard (after setting up your build environment):

    make keyten/imi60_hs:default
	
Flashing example for this keyboard:

    make keyten/imi60_hs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to `QK_BOOT` if it is available
* Physical reset button: Hold the button on the back of the PCB
