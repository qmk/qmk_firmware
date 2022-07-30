# optkb

![giri](https://i.imgur.com/7HjXotx.jpg)
![giri](https://i.imgur.com/o7rhdtJ.jpg)
![giri](https://i.imgur.com/gi0ZL6s.jpg)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Girish Palya](https://github.com/girishji)
* Hardware Supported: Black pill STM32F401

Make example for this keyboard (after setting up your build environment):

    make handwired/giri/optkb:default

Flashing example for this keyboard:

    make handwired/giri/optkb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button BOOT and then button NRST, release NRST first and then BOOT 
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Verify that it entered DFU (bootloader) mode through QMK Toolbox before
flashing.

## Wiring instructions

- On Blackpill boards, **avoid** using the following pins, since they will cause either USB enumeration or the DFU bootloader to not work correctly:
  - **USB-related pins:** `PA10`, `PA11`, `PA12` (PA11 is USB D- and PA12 is USB D+)
  - **BOOT1 pin:** `PB2` (board pulldown resistor)
  - **LED pin:** `PC13`
  - **Crystal:** `PC14` and `PC15` are connected to crystal

Note: 
- A11 and A12 are used by USB. You cannot use these, basically.
- A10 needs a pullup if you use it, to ensure that it jumps to the bootloader corretly.
- A9 has an internal pulldown resistor. It should be avoided, but can be used with a pullup resistor in a pinch.
- B2 i used by BOOT1, so is unusable.
- A0 is used by the "USER" button
- C13 is used by the led on the blackpill controller.
- C14 and C15 are usable, IIRC. But have some issues with how they should be used (C13 too, eg, it shouldn't be used for leds.... )

the rest are usable.

(https://www.reddit.com/r/ErgoMechKeyboards/comments/t0kymt/questions_about_split_blackpill_design/)
