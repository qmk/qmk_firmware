# Squeezing the most out of AVR

First, death to AVR.  It's old, it's slow, it's past time to retire it.  The only issue with migrating away is the shortage. 

If you need to reduce the compiled size of your firmware, there are a number of options to do so. 

## `rules.mk` Settings
First and foremost is enabling link time optimization.  To do so, add this to your rules.mk: 
```make
LTO_ENABLE = yes
```
This will cause the final step to take longer, but should get you a smaller compiled size.  This also disables Action Functions, and Action Macros, both of which are deprecated.
This will get you the most savings, in most situations. 

From there, disabling extraneous systems will help.  Eg: 
```make
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
```
This disables some of the functionality that you may not need.  But note that extrakeys disables stuff like the media keys and system volume control.

If that doesn't help, then there are some additional features that you can disable: 
```make
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no
```
These features are enabled by default, but may not be needed.  Double check to make sure, though.  
Biggest is "magic", as this is the magic keycodes, that control things like NKRO toggling, GUI and ALT/CTRL swapping, etc.  Disabling it will disable those functions. 

## `config.h` Settings

If you've done all of that, and you don't want to disable featuse like RGB, Audio, OLEDs, etc, there are some additional options that you can add to your config.h that can help. 

Starting with Lock Key support.  If you have an Cherry MX Lock switch (lucky you!), you don't want to do this.  But chances are, you don't.  In that case, add this to your `config.h`:
```c
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
```


Oneshots.  If you're not using these, you can disable the feature by adding this to your `config.h`: 
```c
#define NO_ACTION_ONESHOT
```
The same with tapping keys (mod tap, layer tap, etc)
```c
#define NO_ACTION_TAPPING
```
## Audio Settings

If you're using the Audio feature, by default that includes the music mode feature.  This tranlates matrix positions into notes.  It's neat for sure, but most likely, you're not using it.  You can disable it by adding this to your `config.h`:
```c
#define NO_MUSIC_MODE
```
And by adding this to your `rules.mk`
```make
MUSIC_ENABLE = no
```

## Layers

There are also some options for layers.  For instance, you can outright remove them, by adding this to your config.h: 
```c
#define NO_ACTION_LAYER
```
Or, probably better, you can limit the number of layers that the firmware uses -- if you're using less than 8 layers in total:
```c
#define LAYER_STATE_8BIT
```
or if you require up to 16 layers instead:
```c
#define LAYER_STATE_16BIT
```

## RGB Settings

If you're using RGB on your board, both RGB Light (Underglow) and RGB Matrix (per key RGB) now require defines to enable different animations.  For RGB Light: 
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

For RGB Matrix, these need to be  explicitly enabled, as well:
To disable a specific animation: 
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
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
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

If you've done all of this, and your firmware is still too large, then it's time.  It's time to consider making the switch to ARM.  Unfortunately, right now is the worst possible time for that, due to the silicon shortage, and supply chain issues. Getting an ARM chip is difficult, at best, and significantly overpriced, at worst. 
 -- Drashna

That said, there are a number of Pro Micro replacements with ARM controllers: 
* [Proton C](https://qmk.fm/proton-c/) (out of stock)
* [Bonsai C](https://github.com/customMK/Bonsai-C) (Open Source, DIY/PCBA)
* [Raspberry Pi 2040](https://www.sparkfun.com/products/18288) (not currently supported, no ETA)

There are other, non-Pro Micro compatible boards out there. The most popular being: 
* [WeAct Blackpill F411](https://www.aliexpress.com/item/1005001456186625.html) (~$6 USD)
