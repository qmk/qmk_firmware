# keyten kt60-M

60% MX PCB with a minimum number of required layouts.

![kt60-M image](https://i.imgur.com/ZAdGKmQl.jpg)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: keyten kt60-M
* Hardware Availability: [GB](https://www.reddit.com/r/mechmarket/comments/s4jvsc/gb_kt60m_60_universal_pcb_with_a_minimum_number)

Make example for this keyboard (after setting up your build environment):

    make keyten/kt60_m:default
	
Flashing example for this keyboard:

	make keyten/kt60_m:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to RESET if it is available
* Physical reset button: Press the button on the back of the PCB
