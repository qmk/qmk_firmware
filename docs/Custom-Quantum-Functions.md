A custom keyboard is about more than sending button presses to your computer. QMK has designed hooks to allow you to inject code, override functionality, and otherwise customize how your keyboard responds in different situations. 

## A Word on Keyboards vs Keymap

We have structured QMK as a hierarchy:

* Core (`_quantum`)
  * Keyboard/Revision (`_kb`)
    * Keymap (`_user`)

Each of the functions described below can be defined with a `_kb()` suffix or an `_user()` suffix. We intend for you to use the `_kb()` suffix at the Keyboard/Revision level, while the `_user()` suffix should be used at the Keymap level.

When defining functions at the Keyboard/Revision level it is important that your `_kb()` implementation call `_user()` before executing anything else- otherwise the keymap level function will never be called.

## Matrix Initialization Code

* Keyboard/Revision: `void matrix_init_kb(void)` 
* Keymap: `void matrix_init_user(void)`

This function gets called when the matrix is initiated. You should use this function to initialize any custom hardware you may have, such as speakers, LED drivers, or other features which need to be setup after the keyboard powers on.

### Example

```
void matrix_init_kb(void) {
        // put your keyboard start-up code here
        // runs once when the firmware starts up
        matrix_init_user();

        // JTAG disable for PORT F. write JTD bit twice within four cycles.
        MCUCR |= (1<<JTD);
        MCUCR |= (1<<JTD);

        // * Set our LED pins as output
        DDRB |= (1<<0);
        DDRB |= (1<<1);
        DDRB |= (1<<2);
        DDRB |= (1<<3);
        DDRB |= (1<<4);
}
```

## Matrix Scanning Code

* Keyboard/Revision: `void matrix_scan_kb(void)`
* Keymap: `void matrix_scan_user(void)`

This function gets called at every matrix scan, which is basically as often as the MCU can handle. Be careful what you put here, as it will get run a lot.

You should use this function if you need custom matrix scanning code. It can also be used for custom status output (such as LED's or a display) or other functionality that you want to trigger regularly even when the user isn't typing.

## Hook Into Key Presses

* Keyboard/Revision: `bool process_record_kb(uint16_t keycode, keyrecord_t *record)` 
* Keymap: `bool process_record_user(uint16_t keycode, keyrecord_t *record)`

This function gets called every time a key is pressed or released. This is particularly useful when defining custom keys or overriding the behavior of existing keys.

The return value is whether or not QMK should continue processing the keycode - returning `false` stops the execution.

The `keycode` variable is whatever is defined in your keymap, eg `MO(1)`, `KC_L`, etc. and can be switch-cased to execute code whenever a particular code is pressed.

The `record` variable contains infomation about the actual press:

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

The conditional `if (record->event.pressed)` can tell if the key is being pressed or released, and you can execute code based on that.

## LED Control

* Keyboard/Revision: `void led_set_kb(uint8_t usb_led)` 
* Keymap: `void led_set_user(uint8_t usb_led)`

This allows you to control the 5 LED's defined as part of the USB Keyboard spec. It will be called when the state of one of those 5 LEDs changes.

* `USB_LED_NUM_LOCK`
* `USB_LED_CAPS_LOCK`
* `USB_LED_SCROLL_LOCK`
* `USB_LED_COMPOSE`
* `USB_LED_KANA`

### Example:

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
