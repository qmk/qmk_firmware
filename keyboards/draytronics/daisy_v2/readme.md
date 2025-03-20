# DAISY V2
![daisy](https://i.imgur.com/42p02KD.png)  

An open source macro pad with a rotary encoder and OLED panel, this is an alternative version to the original through hole Daisy kit. More info / PCB designs available at [draytronics.co.uk/daisyV2](https://www.draytronics.co.uk/daisyV2)

* Keyboard Maintainer: [Blake Drayson](https://github.com/ghostseven)
* Hardware Supported: DAISY PCB V2 / STM32F072
* Hardware Availability: [draytronics.co.uk](https://draytronics.co.uk)

Make example for this keyboard (after setting up your build environment):

    make draytronics/daisy_v2:default

Flashing example for this keyboard:

    make draytronics/daisy_v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the rotary encoder button and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
