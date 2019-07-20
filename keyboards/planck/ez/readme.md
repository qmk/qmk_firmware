# Planck EZ

![Planck EZ](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/planck/ez/neat-planck-banner.png)

A variant of the Planck featuring a 2u spacebar and per-key RGB backlighting.

Keyboard Maintainer: [Jack Humbert](https://github.com/jackhumbert)  
Hardware Supported: Planck EZ  
Hardware Availability: [ergodox-ez.com](https://ergodox-ez.com/pages/planck)

Make example for this keyboard (after setting up your build environment):

    make planck/ez:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Spacebar LEDs

If you don't want to use the default behavior for the 2 LEDs under the spacebar, you can disable the normal handling, and implement your own.  This allows for better customization, or disabling of the LEDs.

To do so, add `#define PLANCK_EZ_CUSTOM_LEDS` in your keymap's `config.h` file.

If you want them disabled, this is all you need to do!  Nothing more.

However, if you want to customize the behavior, you will want to add something like this to your `keymap.c` file:

    layer_state_t layer_state_set_user(layer_state_t state) {
        // clear LEDs
        palClearPad(GPIOB, 8);
        palClearPad(GPIOB, 9);

        switch (biton32(state)) {
            case _LOWER:
                palSetPad(GPIOB, 9);
                break;
            case _RAISE:
                palSetPad(GPIOB, 8);
                break;
            case _ADJUST:
                palSetPad(GPIOB, 9);
                palSetPad(GPIOB, 8);
                break;
            default:
                break;
        }
        return state;
    }


This will allow you to customize the LED state based on your needs.
