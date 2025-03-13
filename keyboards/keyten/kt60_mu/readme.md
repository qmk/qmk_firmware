# keyten kt60-MU

PCB supporting multiple 60% keyboards.
Outline is compatible with:

* All common O-Ring mount keyboards
* Polaris V2 (In theory. At the time of PCB design, this keyboard is in IC stage)

Supports two Type-C connector position:

* Standard left position
* Central position like Aksara 60

Supports three JST connector position like the following PCBs or keyboards:

* hiney h60
* Singa Unikorn
* Polaris V2

![kt60-MU](https://i.imgur.com/72uSWLx.jpg)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: keyten kt60-MU
* Hardware Availability: private GB

Make example for this keyboard (after setting up your build environment):

    make keyten/kt60_mu:default
	
Flashing example for this keyboard:

    make keyten/kt60_mu:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to `QK_BOOT` if it is available
* Physical reset button: Hold the button on the back of the PCB
