# Corne Keyboard (CRKBD)

Also known (incorrectly) as the `HeliDox`. 

![Crkbd](https://user-images.githubusercontent.com/736191/40575636-6fba63a4-6123-11e8-9ca0-3f990f1f9f4c.jpg)

![Crkbd](https://user-images.githubusercontent.com/736191/40887871-0eead5dc-678a-11e8-9518-e3ad9e5d2bac.png)

A split keyboard with 3x6 vertically staggered keys and 3 thumb keys.

Keyboard Maintainer: [foostan](https://github.com/foostan/) [@foostan](https://twitter.com/foostan)  
Hardware Supported: Crkbd PCB, Pro Micro  
Hardware Availability: [PCB & Case Data](https://github.com/foostan/crkbd)

Make example for this keyboard (after setting up your build environment):

```sh
make crkbd:default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The Corne PCBs have a reset button next to the TRRS jack to enter in to the bootloader.

Additionally, if you hold down the "Q" or "P" buttons when plugging in that half of the keyboard (per the default QWERTY layout), this will jump to the bootloader and reset the EEPROM (persistent storage).  This would normally be the very top corner-most position, but due to the breakaway column, it's left at Q and P for compatibility. 

## RGB Matrix 
The Corne Keyboard also supports using the RGB Matrix feature, in place of RGB Light.  This provids a better experience when using the keyboard, as it supports a number of per key effects properly.  If you're not using the in switch LEDs, then you may want to pass on doing this. 

In your keymap's `rules.mk` file, add the following: 

```make
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
```

And in your `config.h` file, add the following:

```c

#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#   define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash. 
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

/* Disable the animations you don't want/need.  You will need to disable a good number of these    *
 * because they take up a lot of space.  Disable until you can successfully compile your firmware. */
// #   define DISABLE_RGB_MATRIX_ALPHAS_MODS
// #   define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #   define DISABLE_RGB_MATRIX_BREATHING
// #   define DISABLE_RGB_MATRIX_CYCLE_ALL
// #   define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #   define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
// #   define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
// #   define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #   define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #   define DISABLE_RGB_MATRIX_DUAL_BEACON
// #   define DISABLE_RGB_MATRIX_RAINBOW_BEACON
// #   define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #   define DISABLE_RGB_MATRIX_RAINDROPS
// #   define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #   define DISABLE_RGB_MATRIX_TYPING_HEATMAP
// #   define DISABLE_RGB_MATRIX_DIGITAL_RAIN
// #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE
// #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #   define DISABLE_RGB_MATRIX_SPLASH
// #   define DISABLE_RGB_MATRIX_MULTISPLASH
// #   define DISABLE_RGB_MATRIX_SOLID_SPLASH
// #   define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
```

After this is done, you should be able to use the normal RGB keycodes, but you'll see the RGB Matrix effects in use, giving a much better experience. 
