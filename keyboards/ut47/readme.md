# ut47

![ut47](https://i.imgur.com/ZDKZQaj.jpg)

A short description of the keyboard/project

Keyboard Maintainer: [filoxo](https://github.com/filoxo), [network_operations]  
Hardware Supported: [PCB design](http://www.40percent.club/2016/10/gnap-20-plateless.html), Arduino Pro Micro
Hardware Availability: [How to order](http://www.40percent.club/2017/03/ordering-pcb.html)

To flash the UT47 without LEDs (single controller), run:

    make ut47:default

To enable the UT47 LEDs (dual controller), run this for the main controller:

    make ut47:default LED_ENABLE=yes

Or you can add `#define LED_ENABLE` to *rules.mk*

And then flash [LED_controls.ino](LED_controls.ino) to the second controller using [Arduino IDE](https://www.arduino.cc/en/Main/Software) or similar. NOTE: Arduino IDE will require importing additional libraries to compile. 

The reason this is an "opt-in" feature is to prevent sending serial communication over the pin, in case it ends up being used for something else (like RGB underglow).

### Layout

Go to the [default layout README](keymaps/default/readme.md) for more information.

### Additional help
See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

### Build Guide

[u/network_operations' build guide thread](https://www.reddit.com/r/MechanicalKeyboards/comments/7wqktu/gnap_the_cheap_40/)

### Credit

Forked from [di0ib TMK version](https://github.com/di0ib/tmk_keyboard/tree/master/keyboard/gnap)
