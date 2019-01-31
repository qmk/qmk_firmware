# How to Customize Your Keyboard's Behavior

For a lot of people a custom keyboard is about more than sending button presses to your computer. You want to be able to do things that are more complex than simple button presses and macros. QMK has hooks that allow you to inject code, override functionality, and otherwise customize how your keyboard behaves in different situations.

This page does not assume any special knowledge about QMK, but reading [Understanding QMK](understanding_qmk.md) will help you understand what is going on at a more fundamental level.

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

```c
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

## Programming the Behavior of Any Keycode

When you want to override the behavior of an existing key, or define the behavior for a new key, you should use the `process_record_kb()` and `process_record_user()` functions. These are called by QMK during key processing before the actual key event is handled. If these functions return `true` QMK will process the keycodes as usual. That can be handy for extending the functionality of a key rather than replacing it. If these functions return `false` QMK will skip the normal key handling, and it will be up to you to send any key up or down events that are required.

These function are called every time a key is pressed or released.

### Example `process_record_user()` Implementation

This example does two things. It defines the behavior for a custom keycode called `FOO`, and it supplements our Enter key by playing a tone whenever it is pressed.

```c
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
    default:
      return true; // Process all other keycodes normally
  }
}
```

### `process_record_*` Function Documentation

* Keyboard/Revision: `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* Keymap: `bool process_record_user(uint16_t keycode, keyrecord_t *record)`

The `keycode` argument is whatever is defined in your keymap, eg `MO(1)`, `KC_L`, etc. You should use a `switch...case` block to handle these events.

The `record` argument contains information about the actual press:

```c
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

# LED Control

QMK provides methods to read the 5 LEDs defined as part of the HID spec:

* `USB_LED_NUM_LOCK`
* `USB_LED_CAPS_LOCK`
* `USB_LED_SCROLL_LOCK`
* `USB_LED_COMPOSE`
* `USB_LED_KANA`

These five constants correspond to the positional bits of the host LED state.
There are two ways to get the host LED state:

* by implementing `led_set_user()`
* by calling `host_keyboard_leds()`

## `led_set_user()`

This function will be called when the state of one of those 5 LEDs changes. It receives the LED state as a parameter.
Use the `IS_LED_ON(usb_led, led_name)` and `IS_LED_OFF(usb_led, led_name)` macros to check the LED status.

!> `host_keyboard_leds()` may already reflect a new value before `led_set_user()` is called.

### Example `led_set_user()` Implementation

```c
void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        PORTB |= (1<<0);
    } else {
        PORTB &= ~(1<<0);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        PORTB |= (1<<1);
    } else {
        PORTB &= ~(1<<1);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        PORTB |= (1<<2);
    } else {
        PORTB &= ~(1<<2);
    }
    if (IS_LED_ON(usb_led, USB_LED_COMPOSE)) {
        PORTB |= (1<<3);
    } else {
        PORTB &= ~(1<<3);
    }
    if (IS_LED_ON(usb_led, USB_LED_KANA)) {
        PORTB |= (1<<4);
    } else {
        PORTB &= ~(1<<4);
    }
}
```

### `led_set_*` Function Documentation

* Keyboard/Revision: `void led_set_kb(uint8_t usb_led)`
* Keymap: `void led_set_user(uint8_t usb_led)`

## `host_keyboard_leds()`

Call this function to get the last received LED state. This is useful for reading the LED state outside `led_set_*`, e.g. in [`matrix_scan_user()`](#matrix-scanning-code).
For convenience, you can use the `IS_HOST_LED_ON(led_name)` and `IS_HOST_LED_OFF(led_name)` macros instead of calling and checking `host_keyboard_leds()` directly.

## Setting Physical LED State

Some keyboard implementations provide convenience methods for setting the state of the physical LEDs.

### Ergodox Boards

The Ergodox implementations provide `ergodox_right_led_1`/`2`/`3_on`/`off()` to turn individual LEDs on or off, as well as `ergodox_right_led_on`/`off(uint8_t led)` to turn them on or off by their index.

In addition, it is possible to specify the brightness level of all LEDs with `ergodox_led_all_set(uint8_t n)`; of individual LEDs with `ergodox_right_led_1`/`2`/`3_set(uint8_t n)`; or by index with `ergodox_right_led_set(uint8_t led, uint8_t n)`.

Ergodox boards also define `LED_BRIGHTNESS_LO` for the lowest brightness and `LED_BRIGHTNESS_HI` for the highest brightness (which is the default).

# Matrix Initialization Code

Before a keyboard can be used the hardware must be initialized. QMK handles initialization of the keyboard matrix itself, but if you have other hardware like LEDs or i&#xb2;c controllers you will need to set up that hardware before it can be used.


### Example `matrix_init_user()` Implementation

This example, at the keyboard level, sets up B1, B2, and B3 as LED pins.

```c
void matrix_init_user(void) {
  // Call the keymap level matrix init.

  // Set our LED pins as output
  DDRB |= (1<<1);
  DDRB |= (1<<2);
  DDRB |= (1<<3);
}
```

### `matrix_init_*` Function Documentation

* Keyboard/Revision: `void matrix_init_kb(void)`
* Keymap: `void matrix_init_user(void)`

# Matrix Scanning Code

Whenever possible you should customize your keyboard by using `process_record_*()` and hooking into events that way, to ensure that your code does not have a negative performance impact on your keyboard. However, in rare cases it is necessary to hook into the matrix scanning. Be extremely careful with the performance of code in these functions, as it will be called at least 10 times per second.

### Example `matrix_scan_*` Implementation

This example has been deliberately omitted. You should understand enough about QMK internals to write this without an example before hooking into such a performance sensitive area. If you need help please [open an issue](https://github.com/qmk/qmk_firmware/issues/new) or [chat with us on Discord](https://discord.gg/Uq7gcHh).

### `matrix_scan_*` Function Documentation

* Keyboard/Revision: `void matrix_scan_kb(void)`
* Keymap: `void matrix_scan_user(void)`

This function gets called at every matrix scan, which is basically as often as the MCU can handle. Be careful what you put here, as it will get run a lot.

You should use this function if you need custom matrix scanning code. It can also be used for custom status output (such as LEDs or a display) or other functionality that you want to trigger regularly even when the user isn't typing.


# Keyboard Idling/Wake Code

If the board supports it, it can be "idled", by stopping a number of functions.  A good example of this is RGB lights or backlights.   This can save on power consumption, or may be better behavior for your keyboard.

This is controlled by two functions: `suspend_power_down_*` and `suspend_wakeup_init_*`, which are called when the system is board is idled and when it wakes up, respectively.


### Example suspend_power_down_user() and suspend_wakeup_init_user() Implementation

This example, at the keyboard level, sets up B1, B2, and B3 as LED pins.

```c
void suspend_power_down_user(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void)
{
    rgb_matrix_set_suspend_state(false);
}

```

### `keyboard_init_*` Function Documentation

* Keyboard/Revision: `void suspend_power_down_kb(void)` and `void suspend_wakeup_init_user(void)`
* Keymap: `void suspend_power_down_kb(void)` and `void suspend_wakeup_init_user(void)`

# Layer Change Code

This runs code every time that the layers get changed.  This can be useful for layer indication, or custom layer handling.

### Example `layer_state_set_*` Implementation

This example shows how to set the [RGB Underglow](feature_rgblight.md) lights based on the layer, using the Planck as an example

```c
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _RAISE:
        rgblight_setrgb (0x00,  0x00, 0xFF);
        break;
    case _LOWER:
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    case _PLOVER:
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;
    case _ADJUST:
        rgblight_setrgb (0x7A,  0x00, 0xFF);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0x00,  0xFF, 0xFF);
        break;
    }
  return state;
}
```
### `layer_state_set_*` Function Documentation

* Keyboard/Revision: `void uint32_t layer_state_set_kb(uint32_t state)`
* Keymap: `uint32_t layer_state_set_user(uint32_t state)`

The `state` is the bitmask of the active layers, as explained in the [Keymap Overview](keymap.md#keymap-layer-status)


# Persistent Configuration (EEPROM)

This allows you to configure persistent settings for your keyboard.  These settings are stored in the EEPROM of your controller, and are retained even after power loss. The settings can be read with `eeconfig_read_kb` and `eeconfig_read_user`, and can be written to using `eeconfig_update_kb` and `eeconfig_update_user`. This is useful for features that you want to be able to toggle (like toggling rgb layer indication).  Additionally, you can use `eeconfig_init_kb` and `eeconfig_init_user` to set the default values for the EEPROM. 

The complicated part here, is that there are a bunch of ways that you can store and access data via EEPROM, and there is no "correct" way to do this.  However, you only have a DWORD (4 bytes) for each function.

Keep in mind that EEPROM has a limited number of writes. While this is very high, it's not the only thing writing to the EEPROM, and if you write too often, you can potentially drastically shorten the life of your MCU.

* If you don't understand the example, then you may want to avoid using this feature, as it is rather complicated. 

### Example  Implementation

This is an example of how to add settings, and read and write it. We're using the user keymap for the example here.  This is a complex function, and has a lot going on.  In fact, it uses a lot of the above functions to work! 


In your keymap.c file, add this to the top:
```
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;
```

This sets up a 32 bit structure that we can store settings with in memory, and write to the EEPROM. Using this removes the need to define variables, since they're defined in this structure. Remember that `bool` (boolean) values use 1 bit, `uint8_t` uses 8 bits, `uint16_t` uses up 16 bits.  You can mix and match, but changing the order can cause issues, as it will change the values that are read and written. 

We're using `rgb_layer_change`, for the `layer_state_set_*` function, and use `matrix_init_user` and `process_record_user` to configure everything. 

Now, using the `matrix_init_user` code above, you want to add `eeconfig_read_user()` to it, to populate the structure you've just created. And you can then immediately use this structure to control functionality in your keymap.  And It should look like: 
```
void matrix_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set default layer, if enabled
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_cyan(); 
    rgblight_mode_noeeprom(1);
  }
}
```
The above function will use the EEPROM config immediately after reading it, to set the default layer's RGB color. The "raw" value of it is converted in a usable structure based on the "union" that you created above. 

```
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _RAISE:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_magenta(); rgblight_mode_noeeprom(1); }
        break;
    case _LOWER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_red(); rgblight_mode_noeeprom(1); }
        break;
    case _PLOVER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_green(); rgblight_mode_noeeprom(1); }
        break;
    case _ADJUST:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); }
        break;
    default: //  for any other layers, or the default layer
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1); }
        break;
    }
  return state;
}
```
This will cause the RGB underglow to be changed ONLY if the value was enabled.  Now to configure this value, create a new keycode for `process_record_user` called `RGB_LYR` and `EPRM`. Additionally, we want to make sure that if you use the normal RGB codes, that it turns off  Using the example above, make it look this:
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
    case EPRM:
        if (record->event.pressed) {
            eeconfig_init(); // resets the EEPROM to default
        }
        return false;
    case RGB_LYR:  // This allows me to use underglow as layer indication, or as normal
        if (record->event.pressed) { 
            user_config.rgb_layer_change ^= 1; // Toggles the status
            eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
            if (user_config.rgb_layer_change) { // if layer state indication is enabled, 
                layer_state_set(layer_state);   // then immediately update the layer color
            }
        }
        return false; break;
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // For any of the RGB codes (see quantum_keycodes.h, L400 for reference)
        if (record->event.pressed) { //This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
            if (user_config.rgb_layer_change) {        // only if this is enabled 
                user_config.rgb_layer_change = false;  // disable it, and 
                eeconfig_update_user(user_config.raw); // write the setings to EEPROM
            }
        }
        return true; break;
    default:
      return true; // Process all other keycodes normally
  }
}
```
And lastly, you want to add the `eeconfig_init_user` function, so that when the EEPROM is reset, you can specify default values, and even custom actions. For example, if you want to set rgb layer indication by default, and save the default valued. 

```
void eeconfig_init_user(void) {  // EEPROM is getting reset! 
  user_config.rgb_layer_change = true; // We want this enabled by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv_cyan();  // Set it to CYAN by default
  rgblight_mode(1); // set to solid by default
}
```

And you're done.  The RGB layer indication will only work if you want it to. And it will be saved, even after unplugging the board. And if you use any of the RGB codes, it will disable the layer indication, so that it stays on the mode and color that you set it to. 

### 'EECONFIG' Function Documentation

* Keyboard/Revision: `void eeconfig_init_kb(void)`, `uint32_t eeconfig_read_kb(void)` and `void eeconfig_update_kb(uint32_t val)`
* Keymap: `void eeconfig_init_user(void)`, `uint32_t eeconfig_read_user(void)` and `void eeconfig_update_user(uint32_t val)`

The `val` is the value of the data that you want to write to EEPROM.  And the `eeconfig_read_*` function return a 32 bit (DWORD) value from the EEPROM. 
