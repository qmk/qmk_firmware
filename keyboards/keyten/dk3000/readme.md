# Reuters DK3000

The Reuters DK3000 was a keyboard for the Reuters 3000 Xtra electronic trading platform.
The top rows work only with this system. The rest of the keyboard works with the PC via the included KVM switch.

![DK3000 image](https://live.staticflickr.com/65535/55108703214_8ee2892105_b.jpg)

A custom PCB with QMK support was designed to fully support modern PCs.
Some original features, such as the ability to connect a branded keypad and audio, have been removed.

![DK3000 PCB image](https://live.staticflickr.com/65535/55108453031_61cf8a219d_b.jpg)

* Keyboard Maintainer: [keyten](https://github.com/key10iq)
* Hardware Supported: Reuters DK3000
* Hardware Availability: Private GB

Make example for this keyboard (after setting up your build environment):

    make keyten/dk3000:default
	
Flashing example for this keyboard:

	make keyten/dk3000:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* Keycode in layout: Press the key mapped to `QK_BOOT` if it is available
* Physical reset button: Press the button on the back of the PCB
