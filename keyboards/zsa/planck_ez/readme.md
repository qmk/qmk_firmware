# Planck EZ

![Planck EZ](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/planck/ez/neat-planck-banner.png)

A variant of the Planck featuring a 2u spacebar and per-key RGB backlighting.

Keyboard Maintainer: [Jack Humbert](https://github.com/jackhumbert), [Drashna Jael're](https://github.com/drashna)
Hardware Supported: Planck EZ  
Hardware Availability: [ZSA](https://www.zsa.io/planck/) (discontinued)

Make example for this keyboard (after setting up your build environment):

    make zsa/planck_ez/base:default

For the per key RGB version of this keyboard, you want to use the "glow" subdirectory. For example: 

    make zsa/planck_ez/glow:default
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Planck EZ Configuration (from Oryx)

To enable the features from Oryx (ZSA's Configurator), either compile the the `oryx` keymap, or add `#define ORYX_CONFIGURATOR` to your `config.h` file.  

This enables the front Indicator LEDs, and the `TOGGLE_LAYER_COLOR`, and `LED_LEVEL` keycodes.  The `TOGGLE_LAYER_COLOR` keycode toggles the customized LED map configured on Oryx. The `LED_LEVEL` cycles through the brightness levels for the front "teeth" LEDs.

### Indicator LEDs

The two front "teeth" LED indicators are PWM controlled.   If you have `ORYX_CONFIGURATOR` defined in your keymap's `config.h`, you can use the `LED_LEVEL` to cycle through preset vales (0, 25%, 50%, 75%, 100%), and will be saved to EEPROM (persistent storage)

Alternatively, you can set the brightness by calling the following functions:

```c
void planck_ez_right_led_level(uint8_t level);
void planck_ez_left_led_level(uint8_t level);
```

These settings are not persistent, so you'd need to reset it every time the board starts.

These are on a 0-255 scale

#### Layer indication

By default, the indicator lights are used for layer indication, expecting the specific layers used in the default keymap.  However, this may not work for you.  And if that is the case, you can add `#define PLANCK_EZ_USER_LEDS` to your `config.h` file.

This will remove the default behavior for changing the LEDs based on layer, and allow you to control them manually.

Alternatively, you can use the following defines in your keymap's `config.h` to control which layers are used, as long as you have `ORYX_CONFIGURATOR` defined in your keymap's `config.h` file, as well.

```c
#define PLANCK_EZ_LED_LOWER 3
#define PLANCK_EZ_LED_RAISE 4
#define PLANCK_EZ_LED_ADJUST 6
```

This will allow you to change the layers that are used, without having to add anything code to your `keymap.c`

### RGB Matrix Features

If you're using the Smart LED (layer indication) feature from the Oryx Configurator, you want to make sure that you enable these options by adding `#define ORYX_CONFIGURATOR` to your keymap's `config.h`.

This changes the `RGB_TOG` keycode so that it will toggle the lights on and off, in a way that will allow the Smart LEDs to continue to work, even with the rest of the LEDs turned off.

Additionally, a new keycode has been added to toggle the Smart LEDs.  Use `TOGGLE_LAYER_COLOR`, if you aren't already.  
