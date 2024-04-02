# Aperture

Aperture is a 65% keyboard with low height of the first row of switches.

Case designed by [Bizunow](https://github.com/Bizunow) ans PCB designed by [keyten](https://github.com/key10iq).

![Aperture image](https://i.imgur.com/L4Z9c96l.jpg)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: Aperture PCB
* Hardware Availability: [GB](https://t.me/gvalchcasciops)

Make example for this keyboard (after setting up your build environment):

    make aperture:default
	
Flashing example for this keyboard:

	make aperture:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to `QK_BOOT` if it is available
* Physical reset button: Press the button on the back of the PCB
