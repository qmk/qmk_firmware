# 60 ANSI Arrow 7U Keymap by [Sendy YK](https://mr.sendyyk.com)

With RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator.

## Default Layer

```c
    /*
     * [_BASE] Default Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │Esc│1  │2  │3  │4  │5  │6  │7  │8  │9  │0  │-  │+  │Bspc   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │Tab  │Q  │W  │E  │R  │T  │Y  │U  │I  │O  │P  │[  │]  │\    │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │Caps  │A  │S  │D  │F  │G  │H  │J  │K  │L  │;  │'  │Enter   │
     * ├──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───────┤
     * │Shift  │Z  │X  │C  │V  │B  │N  │M  │,  │.  │/  │↑  │Shift  │
     * ├─────┬─┴─┬─┴───┼───┴───┴───┴───┴───┴───┴───┼───┼───┼───┬───┤
     * │Ctl  │OS │Alt  │Space                      │←  │↓  │→  │Fn │
     * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
     */
```

## Fn Layer

```c
    /*
     * [[_FN]] Fn Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │`  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Delete │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │Bri U│   │   │End│Rst│   │   │   │Ins│   │PSc│   │   │Eject│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │Bri D │   │SLc│   │   │   │Hom│   │   │   │   │   │Mute    │
     * ├──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───────┤
     * │Vol +  │   │   │Cal│   │   │NLc│Mai│   │   │MSt│PgU│Pause  │
     * ├─────┬─┴─┬─┴───┼───┴───┴───┴───┴───┴───┴───┼───┼───┼───┬───┤
     * │Vol -│Rwd│FFd  │Play/Pause                 │Prv│PgD│Nxt│   │
     * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
     */
```

## RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator

### Caps Lock Indicator

```c
    // Caps Lock Indicator
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(B2);
        rgblight_setrgb(255, 110, 0);
    }
```

### Num Lock Indicator

```c
    // Num Lock Indicator
    if (host_keyboard_led_state().num_lock) {
        rgblight_setrgb(225, 8, 0);
    }
```

### Scroll Lock Indicator
```c
    // Scroll Lock Indicator
    if (host_keyboard_led_state().scroll_lock) {
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 2);
    }
```

### Layer Indicator

```c
    // Layer Indicator
    else {
        switch (get_highest_layer(layer_state)) {
            // Fn Layer Indicator
            case _FN:
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 1);
                break;
            // Default Layer Indicator
            case _BASE:
                rgblight_setrgb(100, 255, 100);
                break;
        }
        update_led();
    }
```

## Build The Firmware

Make example for keyboard (after setting up your build environment):

    make <keyboard_folder>:mrsendyyk FORCE_LAYOUT=60_ansi_arrow_7u

More information:
* [Setting Up Your QMK Environment](https://docs.qmk.fm/#/getting_started_build_tools)
* [More Detailed make Instructions](https://docs.qmk.fm/#/getting_started_make_guide)
* [The Complete Newbs Guide To QMK](https://docs.qmk.fm/#/newbs)
