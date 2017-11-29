# How To Customize Your Keyboard's Behavior

For a lot of people a custom keyboard is about more than sending button presses to your computer. You want to be able to do things that are more complex than simple button presses and macros. QMK has hooks that allow you to inject code, override functionality, and otherwise customize how your keyboard behaves in different situations. 

This page does not assume any special knowledge about QMK, but reading [Understanding QMK](understanding_qmk.html) will help you understand what is going on at a more fundamental level.

## A Word on Core vs Keyboards vs Keymap

We have structured QMK as a hierarchy:

* Core (`_quantum`)
  * Keyboard/Revision (`_kb`)
    * Keymap (`_user`)

Each of the functions described below can be defined with a `_kb()` suffix or a `_user()` suffix. We intend for you to use the `_kb()` suffix at the Keyboard/Revision level, while the `_user()` suffix should be used at the Keymap level.

When defining functions at the Keyboard/Revision level it is important that your `_kb()` implementation call `_user()` before executing anything else- otherwise the keymap level function will never be called.

# Custom Keycodes

By far the most common task is to change the behavior of an existing keycode or to create a new keycode. From a code standpoint the mechanism for each is very similar.

## Defining a New Keycode

The first step to creating your own custom keycode(s) is to enumerate them. This means both naming them and assigning a unique number to that keycode. Rather than limit custom keycodes to a fixed range of numbers QMK provides the `SAFE_RANGE` macro. You can use `SAFE_RANGE` when enumerating your custom keycodes to guarantee that you get a unique number.


Here is an example of enumerating 2 keycodes. After adding this block to your `keymap.c` you will be able to use `FOO` and `BAR` inside your keymap.

```
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

## Programming The Behavior Of Any Keycode

When you want to override the behavior of an existing key, or define the behavior for a new key, you should use the `process_record_kb()` and `process_record_user()` functions. These are called by QMK during key processing before the actual key event is handled. If these functions return `true` QMK will process the keycodes as usual. That can be handy for extending the functionality of a key rather than replacing it. If these functions return `false` QMK will skip the normal key handling, and it will be up you to send any key up or down events that are required.

These function are called every time a key is pressed or released.

### Example `process_record_user()` implementation

This example does two things. It defines the behavior for a custom keycode called `FOO`, and it supplements our Enter key by playing a tone whenever it is pressed.

```
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      if (record->event.pressed) {
        // Do something when pressed
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case KC_ENTER:
      // Play a tone when enter is pressed
      if (record->event.pressed) {
        PLAY_NOTE_ARRAY(tone_qwerty);
      }
      return true; // Let QMK send the enter press/release events
  }
}
```

### `process_record_*` Function documentation

* Keyboard/Revision: `bool process_record_kb(uint16_t keycode, keyrecord_t *record)` 
* Keymap: `bool process_record_user(uint16_t keycode, keyrecord_t *record)`

The `keycode` argument is whatever is defined in your keymap, eg `MO(1)`, `KC_L`, etc. You should use a `switch...case` block to handle these events.

The `record` argument contains infomation about the actual press:

```
keyrecord_t record {
+-keyevent_t event {
| +-keypos_t key {
| | +-uint8_t col
| | +-uint8_t row
| | }
| +-bool     pressed
| +-uint16_t time
| }
}
```

# LED Control

This allows you to control the 5 LED's defined as part of the USB Keyboard spec. It will be called when the state of one of those 5 LEDs changes.

* `USB_LED_NUM_LOCK`
* `USB_LED_CAPS_LOCK`
* `USB_LED_SCROLL_LOCK`
* `USB_LED_COMPOSE`
* `USB_LED_KANA`

### Example `led_set_kb()` implementation

```
void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        PORTB |= (1<<0);
    } else {
        PORTB &= ~(1<<0);
    }
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        PORTB |= (1<<1);
    } else {
        PORTB &= ~(1<<1);
    }
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        PORTB |= (1<<2);
    } else {
        PORTB &= ~(1<<2);
    }
    if (usb_led & (1<<USB_LED_COMPOSE_LOCK)) {
        PORTB |= (1<<3);
    } else {
        PORTB &= ~(1<<3);
    }
    if (usb_led & (1<<USB_LED_KANA_LOCK)) {
        PORTB |= (1<<4);
    } else {
        PORTB &= ~(1<<4);
    }
}
```

### `led_set_*` Function documentation

* Keyboard/Revision: `void led_set_kb(uint8_t usb_led)` 
* Keymap: `void led_set_user(uint8_t usb_led)`

# Matrix Initialization Code

Before a keyboard can be used the hardware must be initialized. QMK handles initialization of the keyboard matrix itself, but if you have other hardware like LED's or i&#xb2;c controllers you will need to set up that hardware before it can be used.

### Example `matrix_init_kb()` implementation

This example, at the keyboard level, sets up B1, B2, and B3 as LED pins.

```
void matrix_init_kb(void) {
  // Call the keymap level matrix init.
  matrix_init_user();

  // Set our LED pins as output
  DDRB |= (1<<1);
  DDRB |= (1<<2);
  DDRB |= (1<<3);
}
```

### `matrix_init_*` Function documentation

* Keyboard/Revision: `void matrix_init_kb(void)` 
* Keymap: `void matrix_init_user(void)`

# Matrix Scanning Code

Whenever possible you should customize your keyboard by using `process_record_*()` and hooking into events that way, to ensure that your code does not have a negative performance impact on your keyboard. However, in rare cases it is necessary to hook into the matrix scanning. Be extremely careful with the performance of code in these functions, as it will be called at least 10 times per second.

### Example `matrix_scan_*` implementation

This example has been deliberately omitted. You should understand enough about QMK internals to write this without an example before hooking into such a performance sensitive area. If you need help please [open an issue](https://github.com/qmk/qmk_firmware/issues/new) or [chat with us on gitter](https://gitter.im/qmk/qmk_firmware).

### `matrix_scan_*` Function documentation

* Keyboard/Revision: `void matrix_scan_kb(void)`
* Keymap: `void matrix_scan_user(void)`

This function gets called at every matrix scan, which is basically as often as the MCU can handle. Be careful what you put here, as it will get run a lot.

You should use this function if you need custom matrix scanning code. It can also be used for custom status output (such as LED's or a display) or other functionality that you want to trigger regularly even when the user isn't typing.
