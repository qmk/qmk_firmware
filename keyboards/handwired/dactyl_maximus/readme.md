# Dactyl Maximus

![KeycapLess](https://i.imgur.com/OJs3bkWh.jpg)  
*Thanks to [unit-5370](https://github.com/unit-5370) for image*

The largest [Dactyl](/keyboards/handwired/dactyl/) variation available from a Dactyl generator. This variation is electronically more similar to the [Dactyl (Pro Micro)](/keyboards/handwired/dactyl_promicro/) as it requires two micro controllers, one per half, instead of the *Dactyl's* original implementation of one microcontroller and an I/O expander.

* Keyboard Maintainer: [Duncan Sutherland](https://github.com/dunk2k)
* Hardware Supported: Pro Micro controller, of clone of
* Case Files: [Dactyl Generator](https://ryanis.cool/dactyl/#original)

'Keys' settings for *Dactyl Generator* link:
* Number of Columns: 7 
* Use Number Row: true
* Use Bottom Row: true
* Thumb Key Count: 8

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_maximus:default

Flashing example for this keyboard:

    make handwired/dactyl_maximus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
