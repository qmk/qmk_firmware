# ut47

![ut47](https://i.imgur.com/ZDKZQaj.jpg)

Somewhere between ortholinear and standard offset. Created to have all the same functions on a Planck in a keyboard but with a more conventional keyboard row stagger.

* Keyboard Maintainer: [filoxo](https://github.com/filoxo), [network_operations]
* Hardware Supported: [PCB design](http://www.40percent.club/2016/10/gnap-20-plateless.html), Arduino Pro Micro
* Hardware Availability: [How to order](http://www.40percent.club/2017/03/ordering-pcb.html)

### Instructions

To flash the UT47 without LEDs (single controller), run:

    make 40percentclub/ut47:default

To enable the UT47 LEDs (dual controller), run this for the main controller:

    make 40percentclub/ut47:default LED_ENABLE=yes

Or you can add `LED_ENABLE = yes` to *rules.mk*

And then flash [led_controls.ino](led_controls.ino) to the second controller using [Arduino IDE](https://www.arduino.cc/en/Main/Software) or similar. NOTE: Arduino IDE will require importing additional libraries to compile.

<small>The reason this is an "opt-in" feature is to prevent sending serial communication over the pin, in case it ends up being used for something else (like RGB underglow).</small>

### Layout

Go to the [default layout README](keymaps/default/readme.md) for more information.

### Additional info

Credit: Forked from [di0ib TMK version](https://github.com/di0ib/tmk_keyboard/tree/master/keyboard/gnap)

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

### Build Guide

[u/network_operations' build guide thread](https://www.reddit.com/r/MechanicalKeyboards/comments/7wqktu/gnap_the_cheap_40/)
