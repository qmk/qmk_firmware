# keyten imi60

imi60 - 60% PCB compatible with keyboards by La-Versa: Animi, Mirimi and Otsukimi

![imi60](https://i.imgur.com/s37K4wY.png)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: keyten imi60
* Hardware Availability: private GB

Make example for this keyboard (after setting up your build environment):

    make keyten/imi60:default
	
Flashing example for this keyboard:

    make keyten/imi60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to `QK_BOOT` if it is available
* Physical reset button: Hold the button on the back of the PCB
