# funsize

![funsize](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [D0hnut5](https://github.com/D0hnut5)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make funsize:default

Flashing example for this keyboard:

    make funsize:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## holding place for encoder pins

	"encoder": {
		"rotary": [
			{"pin_a": "B5", "pin_b": "B6"},
			{"pin_a": "B4", "pin_b": "B2"},
            {"pin_a": "B3", "pin_b": "E6"},
            {"pin_a": "B2", "pin_b": "B4"}
		]
    },