# 60 ANSI Arrow Keymap by [Sendy YK](https://mr.sendyyk.com)

With RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator.

## Default Layer

![_BASE](https://raw.githubusercontent.com/mrsendyyk/qmk_firmware/development/images/60_ansi_arrow_keymap_base.png)

## Fn Layer

![_FN](https://raw.githubusercontent.com/mrsendyyk/qmk_firmware/development/images/60_ansi_arrow_keymap_fn.png)

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

    make <keyboard_folder>:mrsendyyk

More information:
* [Setting Up Your QMK Environment](https://docs.qmk.fm/#/getting_started_build_tools)
* [More Detailed make Instructions](https://docs.qmk.fm/#/getting_started_make_guide)
* [The Complete Newbs Guide To QMK](https://docs.qmk.fm/#/newbs)
