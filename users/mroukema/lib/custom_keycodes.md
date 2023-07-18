# Custom Keycodes

Some C macro magic to make adding new keycodes with customizable base and shift charaters easy and done with a single source of truth: `custom_shiftable_keycodes.def`
Users are resposible for adding a call to the function `process_custom_shifted_keys(keycode, record);` within their `keymap.c`.

For example:
```C
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return process_custom_shifted_keys(keycode, record);
    }
};
```

There are three macros available:
* `CUSTOM_KEYCODE(keycode_name)`
    Adds defintion of a new keycode within custom_keycodes enum only.
* `CUSTOM_SHIFTABLE_KEYCODE(keycode_name, base_code, shifted_code)`
    Adds new keycode thant will output base_code by default and shifted_code when shift is held
* `CUSTOM_SHIFTABLE_MOD_KEYCODE(mod_tap_modifier, keycode_name, base_code, shifted_code)`
    Same as `CUSTOM_SHIFTABLE_KEYCODE` but when new keycode will be used in combination with a mod-tap key

Example Usage:
```
// Only defined here; custom impl in keycode.c
CUSTOM_KEYCODE(KC_KP_DOT_COMMA)

// dot that shift to exclemation mark
CUSTOM_SHIFTABLE_KEYCODE(   KC_DTEX,                // CUSTOM KEYCODE
                            KC_DOT,                 // BASE KEYCODE
                            KC_EXLM                 // SHIFTED KEYCODE
)

// Parens/braces that shift to thier mirror
CUSTOM_SHIFTABLE_MOD_KEYCODE(   LGUI_T,                 // MOD KEY OVERLAPPING WITH CUSTOM KEYCODE
                                KC_TG_LPRN,             // CUSTOM KEYCODE
                                KC_LPRN,                // BASE KEYCODE
                                KC_RPRN                 // SHIFTED KEYCODE
)
```
