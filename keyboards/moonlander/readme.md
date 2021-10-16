# Moonlander

![Moonlander](https://zsa.io/static/gallery-white-case-7a2ef555f8f7f4ce1b9030477b16e517.png)

A next-gen split, ergonomic keyboard with an active left side, USB type C, integrated wrist rest, and a thumb cluster that can move.


* Keyboard Maintainer: [drashna](https://github.com/drashna), [ZSA](https://github.com/zsa/)
* Hardware Supported: Moonlander MK 1 (STM32F303xC)
* Hardware Availability: [ZSA Store](https://zsa.io/moonlander/)

Make example for this keyboard (after setting up your build environment):

    make moonlander:default

Flashing example for this keyboard:

    make moonlander:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Moonlander Customization

### Indicator LEDs

There are 6 functions for enabling and disabling the LEDs on the top of the boards. The functions are `ML_LED_1(bool)` through `ML_LED_6(bool)`, with the first LED being the left most LED on the left hand, and the sixth LED being the right most LED on the right side. 

By default, the Indicator LEDs are used to indicate the layer state for the keyboard.  If you wish to change this (and indicate caps/num/scroll lock status instead), then define `MOONLANDER_USER_LEDS` in your `config.h` file. 


### Oryx Configuration

To enable the features from Oryx (ZSA's Configurator), either compile the the `default` keymap, or add `#define ORYX_CONFIGURATOR` to your `config.h` file.  

This enables the front Indicator LEDs, and the `TOGGLE_LAYER_COLOR` keycode.  The `TOGGLE_LAYER_COLOR` keycode toggles the customized LED map configured on Oryx. 

### RGB Matrix Features

If you're using the Smart LED (layer indication) feature from the Oryx Configurator, you want to make sure that you enable these options by adding `#define ORYX_CONFIGURATOR` to your keymap's `config.h`. 

This changes the `RGB_TOG` keycode so that it will toggle the lights on and off, in a way that will allow the Smart LEDs to continue to work, even with the rest of the LEDs turned off. 

Additionally, a new keycode has been added to toggle the Smart LEDs.  Use `TOGGLE_LAYER_COLOR`, if you aren't already.  
