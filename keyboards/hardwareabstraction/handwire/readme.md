# Hardware Abstraction Handwire

![handwire](https://i.imgur.com/PK5HfM3h.jpg)

A hotswap 60% keyboard with an arrow key cluster. Board features support for an OLED screen, push pull solenoid, and an active buzzer. 

* Keyboard Maintainer: [Andy Tsai](https://github.com/cgmandy)
* Hardware Supported: ATMEGA32U4, Push-Pull Solenoid, Active Buzzer, SSD1306 128x32 OLED
* Hardware Availability: https://hardwareabstraction.com

Make example for this keyboard (after setting up your build environment):

    make hardwareabstraction/handwire:default

Flashing example for this keyboard:

    make hardwareabstraction/handwire:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the top left side of the PCB. You can alternatively short the two pads vertically with a pair of tweezers. 
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available. This can be configured in VIA or on the QMK configurator. 
