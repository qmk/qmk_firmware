# Numeric Keypad IIe

![Numeric Keypad IIe](https://upload.wikimedia.org/wikipedia/commons/3/3b/Apple_Numeric_Keypad_IIe.jpg)

This is a conversion project for the Numeric Keypad IIe, model A2M2003. This was an external keypad that connected to the Apple //e's motherboard (and as such, it lacked any kind of onboard controller).

The reference conversion setup uses the keyboard's DB15 (VGA) fixed cable connected to a DB15 wiring terminal with breakout board ([this one](https://www.amazon.com/gp/product/B07437293Y/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1), specifically) and wired to an [Arduino Micro](https://store.arduino.cc/usa/arduino-micro).

Keyboard Maintainer: [Adam Newbold](https://github.com/newbold)  
Hardware Supported: Internal Numeric Keypad IIe PCB (Apple part 820.0081.c), ATmega32U4 microcontroller

Make example for this keyboard (after setting up your build environment):

    make converter/numeric_keypad_iie:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
