# The Default Helix Layout
## Layout

### Qwerty

```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
 `-------------------------------------------------------------------------------------------------'
```

### Colemak
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Tab  |   Q  |   W  |   F  |   P  |   G  |             |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   R  |   S  |   T  |   D  |             |   H  |   N  |   E  |   I  |   O  |  '   |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   K  |   M  |   ,  |   .  |   /  |Enter |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
 `-------------------------------------------------------------------------------------------------'
```

### Dvorak
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  /   |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 | Shift|   ;  |   Q  |   J  |   K  |   X  |   [  |   ]  |   B  |   M  |   W  |   V  |   Z  |Enter |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
 `-------------------------------------------------------------------------------------------------'
```

## Layers

|Priority|number|name|description|
| ---- | ---- | --- | --- |
|high|16|Adjust|Functions|
||4|Raise|Numeric charactors|
||3|Lower|Other charactors|
||2|Dvorak|Dvorak leyout|
||1|Colemak|Colemak leyout|
|low|0|Qwerty|QWERTY leyout(base)|

### Lower
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   _  |   +  |   {  |   }  |  |   |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |  F7  |  F8  |  F9  |  F10 |  F11 |  (   |   )  |  F12 |      |      | Home | End  |      |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 `-------------------------------------------------------------------------------------------------'
```

### Raise
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |  F12 |      |      |PageDn|PageUp|      |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 `-------------------------------------------------------------------------------------------------'
```

### Adjust (Lower + Raise)
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      | Reset|RGBRST|      |      |      |             |      |      |      |      |      |  Del |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |Aud on|Audoff| Mac  |             | Win  |Qwerty|Colemk|Dvorak|      |      |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
 `-------------------------------------------------------------------------------------------------'
```

## Customize

see `qmk_firmware/keyboards/helix/rev2/keymaps/default/rules.mk`

```
# Helix Spacific Build Options
# you can uncomment and edit follows 8 Variables
#  jp: 以下の8つの変数を必要に応じて編集し、コメントアウトをはずします。
# HELIX_ROWS = 5              # Helix Rows is 4 or 5
# OLED_ENABLE = no            # OLED_ENABLE
# LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
# LED_BACK_ENABLE = no        # LED backlight (using quantum/rgblight.c)
# LED_UNDERGLOW_ENABLE = no   # LED underglow (using quantum/rgblight.c)
# LED_ANIMATIONS = yes        # LED animations (quantum/rgblight.c's option)
# LED_RGBBACK_ENABLE = no     # LED rgb matrix (using quantum/rgb_matrix.c)
# IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
```
## Compile

go to qmk top directory.
```
$ cd qmk_firmware
```

build
```
$ make helix:default
$ make helix/rev2/back:default               # with backlight
$ make HELIX=no_ani helix/rev2/back:default  # with backlight without animation
$ make helix/rev2/under:default              # with underglow
$ make helix/rev2/rgbback:default            # with RGB matrix backlight
$ make helix/rev2/oled:default               # with oled
$ make helix/rev2/oled/back:default          # with oled and backlight
$ make helix/rev2/oled/under:default         # with oled and underglow
```

flash to keyboard
```
$ make helix:default:flash
$ make helix/rev2/back:default:flash               # with backlight
$ make HELIX=no_ani helix/rev2/back:default:flash  # with backlight without animation
$ make helix/rev2/under:default:flash              # with underglow
$ make helix/rev2/rgbback:default:flash            # with RGB matrix backlight
$ make helix/rev2/oled:default:flash               # with oled
$ make helix/rev2/oled/back:default:flash          # with oled and backlight
$ make helix/rev2/oled/under:default:flash         # with oled and underglow
```

## RGB Lighting

The Helix Keyboard supports using the RGB Light feature.

* [RGB Light Configuration](/docs/config_options.md#rgb-light-configuration)
* [RGB Light Effect and Animation Selection](/docs/feature_rgblight.md#effect-and-animation-toggles)

### build with RGB Lighting
```
$ make helix/rev2/back:default               # with backlight
$ make HELIX=no_ani helix/rev2/back:default  # with backlight without animation
$ make helix/rev2/under:default              # with underglow
```

### flash to keyboard with RGB Lighting
```
$ make helix/rev2/back:default:flash               # with backlight
$ make HELIX=no_ani helix/rev2/back:default:flash  # with backlight without animation
$ make helix/rev2/under:default:flash              # with underglow
```

## RGB Matrix

The Helix Keyboard also supports using the RGB Matrix feature, in place of RGB
Light. This provids a better experience when using the keyboard, as it supports
a number of per key effects properly.  If you're not using the in switch LEDs,
then you may want to pass on doing this.

### build with RGB Matrix
```
$ make helix/rev2/rgbback:default            # with RGB matrix backlight
```

### flash to keyboard with RGB Matrix
```
$ make helix/rev2/rgbback:default:flash      # with RGB matrix backlight
```

After this is done, you should be able to use the normal RGB keycodes, but
you'll see the RGB Matrix effects in use, giving a much better experience. 

If you want to change the default settings, add the following to your `config.h` and edit it.

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

## Link
* more detail wrote in Japanese [helix/Doc/firmware_jp.md](https://github.com/MakotoKurauchi/helix/blob/master/Doc/firmware_jp.md)
* [Helix top](https://github.com/MakotoKurauchi/helix)

