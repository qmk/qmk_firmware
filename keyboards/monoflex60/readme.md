# Monoflex 60

Monoflex 60 is a 60% keyboard with leafsping plate. The project failed because of a stupid runner (SantiGo Customs) who didn't know how to manage money.

Case designed by [Bizunow](https://github.com/Bizunow) and PCB designed by [keyten](https://github.com/key10iq). Also [ILWrites](https://github.com/pikeeb) helped with PCBs production.

![Monoflex 60 image](https://i.imgur.com/ip3J0y6l.jpeg)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: Monoflex 60 PCB
* Hardware Availability: [GB](https://geekhack.org/index.php?topic=110738.0)

Make example for this keyboard (after setting up your build environment):

    make monoflex60:default
	
Flashing example for this keyboard:

    make monoflex60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to `QK_BOOT` if it is available
* Physical reset button: Press the button on the back of the PCB
