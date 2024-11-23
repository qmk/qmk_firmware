# Squeezing the most out of AVR

AVR is severely resource-constrained, and as QMK continues to grow, it is approaching a point where support for AVR may need to be moved to legacy status as newer development is unable to fit into those constraints.

However, if you need to reduce the compiled size of your firmware to fit the controller's limited flash size, there are a number of options to do so.

## `rules.mk` Settings
First and foremost is enabling link time optimization. To do so, add this to your rules.mk: 
```make
LTO_ENABLE = yes
```
This will cause the final step to take longer, but should get you a smaller compiled size. This also disables Action Functions, and Action Macros, both of which are deprecated.
This will get you the most savings, in most situations.

From there, disabling extraneous systems will help -- e.g.: 
```make
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
```
This disables some of the functionality that you may not need. But note that extrakeys disables stuff like the media keys and system volume control.

If that isn't enough to get your firmware down to size, then there are some additional features that you can disable: 
```make
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no
```
These features are enabled by default, but they may not be needed. Double check to make sure. The [Magic Keycodes](keycodes_magic) are the largest and control things like NKRO toggling, GUI and ALT/CTRL swapping, etc. Disabling them will disable those functions. See [Magic Functions](#magic-functions) for disabling related functions.

If you use `sprintf` or `snprintf` functions you can save around ~400 Bytes by enabling this option.
```make
AVR_USE_MINIMAL_PRINTF = yes
```

This will include smaller implementations from AVRs libc into your Firmware. They are [not fully featured](https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaa3b98c0d17b35642c0f3e4649092b9f1), for instance zero padding and field width specifiers are not supported. So if you use `sprintf` or `snprintf` like this:
```c
sprintf(wpm_str, "%03d", get_current_wpm());
snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c");
```

you will still need the standard implementation.

## `config.h` Settings

If you've done all of that, and you don't want to disable features like RGB, Audio, OLEDs, etc, there are some additional options that you can add to your config.h that can help.

Starting with Lock Key support. If you have a Cherry MX Lock switch (lucky you!), you don't want to do this. But chances are, you don't. In that case, add this to your `config.h`:
```c
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
```
Oneshots. If you're not using these, you can disable the feature by adding this to your `config.h`: 
```c
#define NO_ACTION_ONESHOT
```
The same with tapping keys (mod tap, layer tap, etc)
```c
#define NO_ACTION_TAPPING
```
## Audio Settings

If you're using the Audio feature, by default that includes the music mode feature. This tranlates matrix positions into notes. It's neat for sure, but most likely, you're not using it. You can disable it by adding this to your `config.h`:
```c
#define NO_MUSIC_MODE
```
And by adding this to your `rules.mk`
```make
MUSIC_ENABLE = no
```

## Layers

There are also some options for layers, that can reduce the firmware size. All of these settings are for your `config.h`.

You can limit the number of layers that the firmware uses -- if you're using up to 8 layers in total:
```c
#define LAYER_STATE_8BIT
```
or if you require up to 16 layers instead:
```c
#define LAYER_STATE_16BIT
```
Or if you're not using layers at all, you can outright remove the functionality altogether:
```c
#define NO_ACTION_LAYER
```

## Magic Functions

There are two `__attribute__ ((weak))` placeholder functions available to customize magic keycodes. If you are not using that feature to swap keycodes, such as backslash with backspace, add the following to your `keymap.c` or user space code:
```c
#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
#endif
```
Likewise, if you are not using magic keycodes to swap modifiers, such as Control with GUI, add the following to your `keymap.c` or user space code:
```c
#ifndef MAGIC_ENABLE
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif
```
Both of them will overwrite the placeholder functions with a simple return statement to reduce firmware size.

## OLED tweaks

One place you can save a bunch of space here is by not using `sprintf` or `snprintf`. This function call takes up ~1.5kB of firmware space, and can be rewritten. For instance, WPM uses this a lot.

You can convert this:
```c
    // OLD CODE
    char wpm_str[4] = {0};
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write(wpm_str, ' '), false);
```
into this:
```c
    // NEW CODE
    oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
```
which outputs `WPM:   5`. Or this: 
```c
    // NEW CODE
    oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
```
which outputs `WPM: 005`.

## RGB Settings

If you're using RGB on your board, both RGB Light (Underglow) and RGB Matrix (per key RGB) now require defines to enable different animations -- some keyboards enable a lot of animations by default, so you can generally gain back some space by disabling specific animations if you don't use them. For RGB Light you can disable these in your keymap's `config.h`:
```c
#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE
```

For RGB Matrix, these need to be explicitly enabled as well. To disable any that were enabled by the keyboard, add one or more of these to your keymap's `config.h`:
```c
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN

#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
```

# Final Thoughts

If you've done all of this, and your firmware is still too large, then it is time to consider making the switch to ARM. There are a number of Pro Micro replacements with an ARM controller:
* [Bonsai C](https://github.com/customMK/Bonsai-C) (Open Source, DIY/PCBA)
* [STeMCell](https://github.com/megamind4089/STeMCell) (Open Source, DIY/PCBA)
* [Adafruit KB2040](https://learn.adafruit.com/adafruit-kb2040)
* [SparkFun Pro Micro - RP2040](https://www.sparkfun.com/products/18288)
* [Blok](https://boardsource.xyz/store/628b95b494dfa308a6581622)
* [Elite-Pi](https://keeb.io/products/elite-pi-usb-c-pro-micro-replacement-rp2040)
* [0xCB Helios](https://keeb.supply/products/0xcb-helios) ([Open Source](https://github.com/0xCB-dev/0xCB-Helios), DIY/PCBA/Shop)
* [Liatris](https://splitkb.com/products/liatris)
* [Imera](https://splitkb.com/products/imera)
* [Michi](https://github.com/ci-bus/michi-promicro-rp2040)
* [Proton C](https://qmk.fm/proton-c/) (out of stock)

There are other, non-Pro Micro compatible boards out there. The most popular being:
* [WeAct Blackpill F411](https://www.aliexpress.com/item/1005001456186625.html) (~$6 USD)
