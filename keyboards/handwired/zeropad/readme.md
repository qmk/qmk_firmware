#ZeroPad

ZeroPad:
![ZeroPad](https://github.com/user-attachments/assets/224aa55a-045b-4bb9-b6e9-34f092ced5c4)


*This keyboard is inspired by the scotto9 from Joe Scotto. This keyboard is compatible with via and has 4 layers of keybinds (24 keybinds - 4x8 + 1 per layer for changing the layer).*
* Keyboard Maintainer: [Leons Sieber](https://github.com/diffrentGuesser)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make %KEYBOARD%:default

Flashing example for this keyboard:

    make %KEYBOARD%:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
