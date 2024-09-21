# Little Big Scroll 4

![lsb4](https://i.imgur.com/MMGSDz2h.jpeg)

* A simple 4-key or 2-key plus OLED macropad with a clickable scrollwheel, for media controls and whatever else you can imagine.*

* Keyboard Maintainer: [Markus Knutsson](https://github.com/TweetyDaBird/)
* Hardware Supported: LBS4 PCB plus Pro Micro or pin compatible
* Hardware Availability: https://lectronz.com/stores/tweetys-wild-thinking
* Hardware Design: https://github.com/TweetyDaBird/Little-Big-Scroll


Make example for this keyboard (after setting up your build environment):

    make tweetydabird/lbs4:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. 
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset**: Briefly short the marked pads on PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if mapped (not in default keymap)