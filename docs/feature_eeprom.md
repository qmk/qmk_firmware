# Persistent Configuration (EEPROM)

This allows you to configure persistent settings for your keyboard.  These settings are stored in the EEPROM of your controller, and are retained even after power loss.

Keep in mind that EEPROM has a limited number of writes. While this is very high, it's not the only thing writing to the EEPROM, and if you write too often, you can potentially drastically shorten the life of your MCU.

::: tip
If you don't understand the examples, then you may want to avoid using this feature, as it is rather complicated.
:::

## Basic

The settings can be read with `eeconfig_read_kb` and `eeconfig_read_user`, and can be written to using `eeconfig_update_kb` and `eeconfig_update_user`. This is useful for features that you want to be able to toggle (like toggling rgb layer indication).  Additionally, you can use `eeconfig_init_kb` and `eeconfig_init_user` to set the default values for the EEPROM.

The complicated part here, is that there are a bunch of ways that you can store and access data via EEPROM, and there is no "correct" way to do this.  However, you only have a DWORD (4 bytes) for each function.

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
    rgblight_sethsv_noeeprom(HSV_CYAN);
    rgblight_mode_noeeprom(1);
  }
}
```
The above function will use the EEPROM config immediately after reading it, to set the default layer's RGB color. The "raw" value of it is converted in a usable structure based on the "union" that you created above.

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom(HSV_MAGENTA); rgblight_mode_noeeprom(1); }
        break;
    case _LOWER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom(HSV_RED); rgblight_mode_noeeprom(1); }
        break;
    case _PLOVER:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom(HSV_GREEN); rgblight_mode_noeeprom(1); }
        break;
    case _ADJUST:
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom(HSV_WHITE); rgblight_mode_noeeprom(1); }
        break;
    default: //  for any other layers, or the default layer
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom(HSV_CYAN); rgblight_mode_noeeprom(1); }
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
            PLAY_SONG(tone_qwerty);
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
        return false;
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // For any of the RGB codes (see quantum_keycodes.h, L400 for reference)
        if (record->event.pressed) { //This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
            if (user_config.rgb_layer_change) {        // only if this is enabled
                user_config.rgb_layer_change = false;  // disable it, and
                eeconfig_update_user(user_config.raw); // write the settings to EEPROM
            }
        }
        return true; break;
    default:
      return true; // Process all other keycodes normally
  }
}
```
And lastly, you want to add the `eeconfig_init_user` function, so that when the EEPROM is reset, you can specify default values, and even custom actions. To force an EEPROM reset, use the `EE_CLR` keycode or [Bootmagic](features/bootmagic) functionality. For example, if you want to set rgb layer indication by default, and save the default valued.

```c
void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;
  user_config.rgb_layer_change = true; // We want this enabled by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable(); // Enable RGB by default
  rgblight_sethsv(HSV_CYAN);  // Set it to CYAN by default
  rgblight_mode(1); // set to solid by default
}
```

And you're done.  The RGB layer indication will only work if you want it to. And it will be saved, even after unplugging the board. And if you use any of the RGB codes, it will disable the layer indication, so that it stays on the mode and color that you set it to.

### Basic API

* Keyboard/Revision: `void eeconfig_init_kb(void)`, `uint32_t eeconfig_read_kb(void)` and `void eeconfig_update_kb(uint32_t val)`
* Keymap: `void eeconfig_init_user(void)`, `uint32_t eeconfig_read_user(void)` and `void eeconfig_update_user(uint32_t val)`

The `val` is the value of the data that you want to write to EEPROM.  And the `eeconfig_read_*` function return a 32 bit (DWORD) value from the EEPROM.

## Datablock {#datablock}

An extended form exists that allows larger blocks of data to be allocated.

::: info
When using datablock, the [basic API](#eeconfig-function-documentation) is unavailable.
:::

:::::tabs

==== keyboard

In `config.h`, define the size required, and optionally a version number:

| Define                       | Default                   | Description                                                      |
|------------------------------|---------------------------|------------------------------------------------------------------|
| `EECONFIG_KB_DATA_SIZE`      | `0`                       | Size in bytes for the persistent block of data                   |
| `EECONFIG_KB_DATA_VERSION`   | `EECONFIG_KB_DATA_SIZE`   | Version number that can be incremented to invalidate stored data |

Which exposes the following API:

```c
bool     eeconfig_is_kb_datablock_valid(void);
uint32_t eeconfig_read_kb_datablock(void *data, uint32_t offset, uint32_t length) __attribute__((nonnull));
uint32_t eeconfig_update_kb_datablock(const void *data, uint32_t offset, uint32_t length) __attribute__((nonnull));
void     eeconfig_init_kb_datablock(void);
#    define eeconfig_read_kb_datablock_field(__object, __field) eeconfig_read_kb_datablock(&(__object.__field), offsetof(typeof(__object), __field), sizeof(__object.__field))
#    define eeconfig_update_kb_datablock_field(__object, __field) eeconfig_update_kb_datablock(&(__object.__field), offsetof(typeof(__object), __field), sizeof(__object.__field))
```

==== keymap

In `config.h`, define the size required, and optionally a version number:

| Define                       | Default                   | Description                                                      |
|------------------------------|---------------------------|------------------------------------------------------------------|
| `EECONFIG_USER_DATA_SIZE`    | `0`                       | Size in bytes for the persistent block of data                   |
| `EECONFIG_USER_DATA_VERSION` | `EECONFIG_USER_DATA_SIZE` | Version number that can be incremented to invalidate stored data |

Which exposes the following API:

```c
bool     eeconfig_is_user_datablock_valid(void);
uint32_t eeconfig_read_user_datablock(void *data, uint32_t offset, uint32_t length) __attribute__((nonnull));
uint32_t eeconfig_update_user_datablock(const void *data, uint32_t offset, uint32_t length) __attribute__((nonnull));
void     eeconfig_init_user_datablock(void);
#    define eeconfig_read_user_datablock_field(__object, __field) eeconfig_read_user_datablock(&(__object.__field), offsetof(typeof(__object), __field), sizeof(__object.__field))
#    define eeconfig_update_user_datablock_field(__object, __field) eeconfig_update_user_datablock(&(__object.__field), offsetof(typeof(__object), __field), sizeof(__object.__field))
```

:::::

### Example

This is an example of how to add settings, and read and write it. We're using the user keymap for the example here.

In your `config.h` add:

```c
#define EECONFIG_USER_DATA_SIZE 8
```

In your keymap.c file, add:

```c
#include "debug.h"
#include "timer.h"
#include "eeconfig.h"

typedef struct my_config_t {
    uint64_t data;
} my_config_t;

static my_config_t config;

void keyboard_post_init_user(void) {
    if (!eeconfig_is_user_datablock_valid()) {
        eeconfig_init_user_datablock();
    }

    eeconfig_read_user_datablock(&config, 0, sizeof(my_config_t));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        config.data += 1;
        eeconfig_update_user_datablock(&config, 0, sizeof(my_config_t));
    }

    return true;
}

void housekeeping_task_user(void) {
    static uint32_t last_sync = 0;
    if (timer_elapsed32(last_sync) > 1000) {
        last_sync = timer_read32();

        dprintf("Config: %ld\n", config.data);
    }
}
```
