# [LAYOUT_60_ansi_arrow and Sendy YK's Keymap](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)
`LAYOUT_60_ansi_arrow` with RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator.

## [LAYOUT_60_ansi_arrow](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

![LAYOUT_60_ansi_arrow](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/kbdfans_tofu_60_keyboard/assets/dz60_layout_60_ansi_arrow.png)

## [Sendy YK's Keymap](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

### [Default Layer [0]](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

![Default Layer [0]](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/kbdfans_tofu_60_keyboard/assets/dz60_mrsendyyk_0.png)

### [Fn Layer [1]](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

Press and hold *right* **Ctrl** key.

![Fn Layer [1]](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/kbdfans_tofu_60_keyboard/assets/dz60_mrsendyyk_1.png)

### [Fn Layer [2]](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

Press and hold *right* **Alt** key.

![Fn Layer [2]](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/kbdfans_tofu_60_keyboard/assets/dz60_mrsendyyk_2.png)

## [RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

### [Caps Lock Indicator](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

```c
/* Caps Lock Indicator */
   if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
     writePinLow(B2);
     rgblight_setrgb(100, 255, 100);
   }
```

### [Num Lock Indicator](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

```c
/* Num Lock Indicator */
   if (host_keyboard_led_state().num_lock) {
     rgblight_setrgb(225, 8, 0);
   }
```

### [Scroll Lock Indicator](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)
```c
/* Scroll Lock Indicator */
   if (host_keyboard_led_state().scroll_lock) {
     rgblight_setrgb(241, 190, 72);
   }
```

### [Layer Indicator](https://github.com/mrsendyyk/my_qmk/tree/master/kbdfans_tofu_60_keyboard)

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
