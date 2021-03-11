# ErgoDox EZ

![ErgoDox EZ](http://www.coolthings.com/wp-content/uploads/2017/05/ergodox-ez-2.jpg)

The ErgoDox EZ is a mass produced version of the original ErgoDox keyboard, with optional support for RGB Light (Shine) or RGB Matrix (Glow).

* Keyboard Maintainer: [ZSA Technology Labs Inc](https://github.com/zsa), Firmware maintained by [drashna](https://github.com/drashna)
* Hardware Supported: Original ErgoDox, ErgoDox EZ
* Hardware Availability: [ErgoDox EZ](https://ergodox-ez.com/), [ErgoDox.io](https://ergodox.io)

Make example for this keyboard (after setting up your build environment):

    make ergodox_ez:default:flash
    
For the ErgoDox EZ Shine, and Glow, use one of the following: 

    make ergodox_ez/shine:default:flash
    make ergodox_ez/glow:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Oryx Configuation

If you have `ORYX_CONFIGURATOR` defined in your keymap's `config.h`, this enables a number of the built in options from the Oryx Configurator. 

### Indicator LEDs

You can use the `LED_LEVEL` keycode to cycle through the brightness levels for the LEDs on the top right of the keyboard.  These settings are saved in eeprom (persistant memory). 

Alternatively, you can set the brightness by calling the following functions: 

```c
void ergodox_led_all_set(uint8_t level);
void ergodox_right_led_1_set(uint8_t level);
void ergodox_right_led_2_set(uint8_t level);
void ergodox_right_led_3_set(uint8_t level);
```

These settings are not persistent, so you'd need to reset it every time the board starts. 

These are on a 0-255 scale 

### RGB Matrix Features

If you're using the Smart LED (layer indication) feature from the Oryx Configurator, you want to make sure that you enable these options by adding `#define ORYX_CONFIGURATOR` to your keymap's `config.h`. 

This changes the `RGB_TOG` keycode so that it will toggle the lights on and off, in a way that will allow the Smart LEDs to continue to work, even with the rest of the LEDs turned off. 

Additionally, a new keycode has been added to toggle the Smart LEDs.  Use `TOGGLE_LAYER_COLOR`, if you aren't already.  
