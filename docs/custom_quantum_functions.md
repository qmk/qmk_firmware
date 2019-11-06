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

QMK provides methods to read 5 of the LEDs defined in the HID spec:

* Num Lock
* Caps Lock
* Scroll Lock
* Compose
* Kana

There are two ways to get the lock LED state:

* by implementing `bool led_update_kb(led_t led_state)` or `_user(led_t led_state)`; or
* by calling `led_t host_keyboard_led_state()`

!> `host_keyboard_led_state()` may already reflect a new value before `led_update_user()` is called.

Two more deprecated functions exist that provide the LED state as a `uint8_t`:

* `uint8_t led_set_kb(uint8_t usb_led)` and `_user(uint8_t usb_led)`
* `uint8_t host_keyboard_leds()`

## `led_update_user()`

This function will be called when the state of one of those 5 LEDs changes. It receives the LED state as a struct parameter.

You must return either `true` or `false` from this function, depending on whether you want to override the keyboard-level implementation.

?> Because the `led_set_*` functions return `void` instead of `bool`, they do not allow for overriding the keyboard LED control, and thus it's recommended to use `led_update_*` instead.

### Example `led_update_kb()` Implementation

```c
bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        if (led_state.num_lock) {
            writePinLow(B0);
        } else {
            writePinHigh(B0);
        }
        if (led_state.caps_lock) {
            writePinLow(B1);
        } else {
            writePinHigh(B1);
        }
        if (led_state.scroll_lock) {
            writePinLow(B2);
        } else {
            writePinHigh(B2);
        }
        if (led_state.compose) {
            writePinLow(B3);
        } else {
            writePinHigh(B3);
        }
        if (led_state.kana) {
            writePinLow(B4);
        } else {
            writePinHigh(B4);
        }
        return true;
    }
}
```

### Example `led_update_user()` Implementation

```c
bool led_update_user(led_t led_state) {
    if (led_state.num_lock) {
        writePinLow(B0);
    } else {
        writePinHigh(B0);
    }
    if (led_state.caps_lock) {
        writePinLow(B1);
    } else {
        writePinHigh(B1);
    }
    if (led_state.scroll_lock) {
        writePinLow(B2);
    } else {
        writePinHigh(B2);
    }
    if (led_state.compose) {
        writePinLow(B3);
    } else {
        writePinHigh(B3);
    }
    if (led_state.kana) {
        writePinLow(B4);
    } else {
        writePinHigh(B4);
    }
    return true;
}
```

### `led_update_*` Function Documentation

* Keyboard/Revision: `bool led_update_kb(led_t led_state)`
* Keymap: `bool led_update_user(led_t led_state)`

## `host_keyboard_led_state()`

Call this function to get the last received LED state as a `led_t`. This is useful for reading the LED state outside `led_update_*`, e.g. in [`matrix_scan_user()`](#matrix-scanning-code).

## Setting Physical LED State

Some keyboard implementations provide convenience methods for setting the state of the physical LEDs.

### Ergodox Boards

The Ergodox implementations provide `ergodox_right_led_1`/`2`/`3_on`/`off()` to turn individual LEDs on or off, as well as `ergodox_right_led_on`/`off(uint8_t led)` to turn them on or off by their index.

In addition, it is possible to specify the brightness level of all LEDs with `ergodox_led_all_set(uint8_t n)`; of individual LEDs with `ergodox_right_led_1`/`2`/`3_set(uint8_t n)`; or by index with `ergodox_right_led_set(uint8_t led, uint8_t n)`.

Ergodox boards also define `LED_BRIGHTNESS_LO` for the lowest brightness and `LED_BRIGHTNESS_HI` for the highest brightness (which is the default).

# Keyboard Initialization Code

There are several steps in the keyboard initialization process.  Depending on what you want to do, it will influence which function you should use.

These are the three main initialization functions, listed in the order that they're called.

* `keyboard_pre_init_*` - Happens before most anything is started. Good for hardware setup that you want running very early.
* `matrix_init_*` - Happens midway through the firmware's startup process. Hardware is initialized, but features may not be yet.
* `keyboard_post_init_*` - Happens at the end of the firmware's startup process. This is where you'd want to put "customization" code, for the most part.

!> For most people, the `keyboard_post_init_user` function is what you want to call.  For instance, this is where you want to set up things for RGB Underglow.

## Keyboard Pre Initialization code

This runs very early during startup, even before the USB has been started. 

Shortly after this, the matrix is initialized.

For most users, this shouldn't be used, as it's primarily for hardware oriented initialization. 

However, if you have hardware stuff that you need initialized, this is the best place for it (such as initializing LED pins).

### Example `keyboard_pre_init_user()` Implementation

This example, at the keyboard level, sets up B0, B1, B2, B3, and B4 as LED pins.

```c
void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(B0);
  setPinOutput(B1);
  setPinOutput(B2);
  setPinOutput(B3);
  setPinOutput(B4);
}
```

### `keyboard_pre_init_*` Function Documentation

* Keyboard/Revision: `void keyboard_pre_init_kb(void)`
* Keymap: `void keyboard_pre_init_user(void)`

## Matrix Initialization Code

This is called when the matrix is initialized, and after some of the hardware has been set up, but before many of the features have been initialized. 

This is useful for setting up stuff that you may need elsewhere, but isn't hardware related nor is dependant on where it's started. 


### `matrix_init_*` Function Documentation

* Keyboard/Revision: `void matrix_init_kb(void)`
* Keymap: `void matrix_init_user(void)`


## Keyboard Post Initialization code

This is ran as the very last task in the keyboard initialization process. This is useful if you want to make changes to certain features, as they should be initialized by this point.


### Example `keyboard_post_init_user()` Implementation

This example, running after everything else has initialized, sets up the rgb underglow configuration.

```c
void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}
```

### `keyboard_post_init_*` Function Documentation

* Keyboard/Revision: `void keyboard_post_init_kb(void)`
* Keymap: `void keyboard_post_init_user(void)`

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

This is controlled by two functions: `suspend_power_down_*` and `suspend_wakeup_init_*`, which are called when the system board is idled and when it wakes up, respectively.


### Example suspend_power_down_user() and suspend_wakeup_init_user() Implementation


```c
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
```

### Keyboard suspend/wake  Function Documentation

* Keyboard/Revision: `void suspend_power_down_kb(void)` and `void suspend_wakeup_init_user(void)`
* Keymap: `void suspend_power_down_kb(void)` and `void suspend_wakeup_init_user(void)`

# Layer Change Code

This runs code every time that the layers get changed.  This can be useful for layer indication, or custom layer handling.

### Example `layer_state_set_*` Implementation

This example shows how to set the [RGB Underglow](feature_rgblight.md) lights based on the layer, using the Planck as an example

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
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

* Keyboard/Revision: `layer_state_t layer_state_set_kb(layer_state_t state)`
* Keymap: `layer_state_t layer_state_set_user(layer_state_t state)`


The `state` is the bitmask of the active layers, as explained in the [Keymap Overview](keymap.md#keymap-layer-status)


# Persistent Configuration (EEPROM)

This allows you to configure persistent settings for your keyboard.  These settings are stored in the EEPROM of your controller, and are retained even after power loss. The settings can be read with `eeconfig_read_kb` and `eeconfig_read_user`, and can be written to using `eeconfig_update_kb` and `eeconfig_update_user`. This is useful for features that you want to be able to toggle (like toggling rgb layer indication).  Additionally, you can use `eeconfig_init_kb` and `eeconfig_init_user` to set the default values for the EEPROM. 

The complicated part here, is that there are a bunch of ways that you can store and access data via EEPROM, and there is no "correct" way to do this.  However, you only have a DWORD (4 bytes) for each function.

Keep in mind that EEPROM has a limited number of writes. While this is very high, it's not the only thing writing to the EEPROM, and if you write too often, you can potentially drastically shorten the life of your MCU.

* If you don't understand the example, then you may want to avoid using this feature, as it is rather complicated. 

### Example Implementation

This is an example of how to add settings, and read and write it. We're using the user keymap for the example here.  This is a complex function, and has a lot going on.  In fact, it uses a lot of the above functions to work! 


In your keymap.c file, add this to the top:
```c
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;
```

This sets up a 32 bit structure that we can store settings with in memory, and write to the EEPROM. Using this removes the need to define variables, since they're defined in this structure. Remember that `bool` (boolean) values use 1 bit, `uint8_t` uses 8 bits, `uint16_t` uses up 16 bits.  You can mix and match, but changing the order can cause issues, as it will change the values that are read and written. 

We're using `rgb_layer_change`, for the `layer_state_set_*` function, and use `keyboard_post_init_user` and `process_record_user` to configure everything. 

Now, using the `keyboard_post_init_user` code above, you want to add `eeconfig_read_user()` to it, to populate the structure you've just created. And you can then immediately use this structure to control functionality in your keymap.  And It should look like: 
```c
void keyboard_post_init_user(void) {
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

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
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
This will cause the RGB underglow to be changed ONLY if the value was enabled.  Now to configure this value, create a new keycode for `process_record_user` called `RGB_LYR`. Additionally, we want to make sure that if you use the normal RGB codes, that it turns off  Using the example above, make it look this:
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
And lastly, you want to add the `eeconfig_init_user` function, so that when the EEPROM is reset, you can specify default values, and even custom actions. To force an EEPROM reset, use the `EEP_RST` keycode or [Bootmagic](feature_bootmagic.md) functionallity. For example, if you want to set rgb layer indication by default, and save the default valued. 

```c
void eeconfig_init_user(void) {  // EEPROM is getting reset! 
  user_config.raw = 0;
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

# Custom Tapping Term

By default, the tapping term is defined globally, and is not configurable by key.  For most users, this is perfectly fine.  But in come cases, dual function keys would be greatly improved by different timeouts than `LT` keys, or because some keys may be easier to hold than others.  Instead of using custom key codes for each, this allows for per key configurable `TAPPING_TERM`.

To enable this functionality, you need to add `#define TAPPING_TERM_PER_KEY` to your `config.h`, first.  


## Example `get_tapping_term` Implementation

To change the `TAPPING TERM` based on the keycode, you'd want to add something like the following to your `keymap.c` file: 

```c
uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case SFT_T(KC_SPC):
      return TAPPING_TERM + 1250;
    case LT(1, KC_GRV):
      return 130;
    default:
      return TAPPING_TERM;
  }
}
```

### `get_tapping_term` Function Documentation

Unlike many of the other functions here, there isn't a need (or even reason) to have a quantum or keyboard level function. Only a user level function is useful here, so no need to mark it as such.
