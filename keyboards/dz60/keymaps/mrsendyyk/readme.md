# Sendy YK's 60% ANSI Arrow Layout and Keymap

This is Sendy YK's [60% ANSI Arrow Layout](https://github.com/qmk/qmk_firmware/blob/master/layouts/default/60_ansi_arrow/info.json) and [Keymap (with RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator)](https://github.com/qmk/qmk_firmware/blob/master/layouts/community/60_ansi_arrow/mrsendyyk/keymap.c).

## 60% ANSI Arrow Layout

![LAYOUT_60_ansi_arrow](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/kbdfans_tofu_60_keyboard/assets/dz60_layout_60_ansi_arrow.png)

## Keymap

### Default Layer [0]

![Default Layer [0]](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/kbdfans_tofu_60_keyboard/assets/dz60_mrsendyyk_0.png)

### Fn Layer [1]

Press and hold *right* **Ctrl** key.

![Fn Layer [1]](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/kbdfans_tofu_60_keyboard/assets/dz60_mrsendyyk_1.png)

### Fn Layer [2]

Press and hold *right* **Alt** key.

![Fn Layer [2]](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/kbdfans_tofu_60_keyboard/assets/dz60_mrsendyyk_2.png)

### RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator

#### Caps Lock Indicator

```c
/* Caps Lock Indicator */
   if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
     writePinLow(B2);
     rgblight_setrgb(100, 255, 100);
   }
```

#### Num Lock Indicator

```c
/* Num Lock Indicator */
   if (host_keyboard_led_state().num_lock) {
     rgblight_setrgb(225, 8, 0);
   }
```

#### Scroll Lock Indicator
```c
/* Scroll Lock Indicator */
   if (host_keyboard_led_state().scroll_lock) {
     rgblight_setrgb(241, 190, 72);
   }
```

#### Layer Indicator

```c
/* Layer Indicator */
   else {          
     switch (get_highest_layer(layer_state)) {
     /* Fn Layer [1] Indicator */
        case 1:
          rgblight_setrgb(255, 110, 0);
          break;
     /* Fn Layer [2] Indicator */
        case 2:
          rgblight_setrgb(255, 110, 0);
          break;
     /* Default Layer [0] Indicator */
        default:
          rgblight_setrgb(0, 0, 0);
          break;
     }
     update_led();
   }
```

## Build The Firmware

You will need to build the firmware. To do so go to your terminal window and run the compile command:

    qmk compile -kb dz60 -km mrsendyyk

See [The Complete Newbs Guide To QMK](https://docs.qmk.fm/#/newbs).
