# keyten kt3700

Replacement pcb for Cherry G80-3700.

![kt3700 image](https://i.imgur.com/s5NhDAbl.png)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: keyten kt3700
* Hardware Availability: [GB](https://t.me/keytenspcb/44)

Make example for this keyboard (after setting up your build environment):

    make keyten/kt3700:default
	
Flashing example for this keyboard:

    make keyten/kt3700:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to RESET if it is available
* Physical reset button: Hold down the BOOT0 button on the back of the PCB for a couple of seconds, then hold down the RESET button for a second
