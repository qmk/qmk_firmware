# keyten kt356 Mini

Replacement PCB for the OTD (and UTD) 356 Mini keyboard.

![kt356 Mini image](https://live.staticflickr.com/65535/54907825962_65a650ce4c_b.jpg)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: keyten kt356 Mini
* Hardware Availability: private GB

Make example for this keyboard (after setting up your build environment):

    make keyten/kt356_mini:default
	
Flashing example for this keyboard:

	make keyten/kt356_mini:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to `QK_BOOT` if it is available
* Physical reset button: Hold the button on the back of the PCB
