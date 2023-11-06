# geekboards/macropad_v2

![Geekboards Macropad v2](https://github.com/ruddy17/my_files/blob/main/macropad_v2.jpg)

8-keys macropad with CNC aluminium case, RGB LEDs for both backlight and switches, hot-swap connectors.

Keyboard Maintainer: [ruddy17](https://github.com/ruddy17)  
Hardware Supported: Geekboards Macropad v2, STM32F072C8T6  
Hardware Availability: https://geekboards.ru

Compile instruction for this keyboard (after setting up your build environment):

    make geekboards/macropad_v2:via

## Update firmware
### Enter bootloader
1. Press and hold leftmost button on top row (where ESC usually is)
2. Plug in USB
3. Keep holding the button for 3 more seconds
4. Release the button

Alternatively:
1. Remove bottom cover
1. On the pcb short together two contacts labeled BOOT0
2. Plug in USB
3. Release BOOT0

### Flash

    make geekboards/macropad_v2:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
