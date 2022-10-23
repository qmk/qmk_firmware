# Adding Default Keymaps to QMK Configurator :id=adding-default-keymaps

This page covers how to add a default keymap for a keyboard to QMK Configurator.


## Technical Information :id=technical-information

QMK Configurator uses JSON as its native file format for keymaps. As much as possible, these should be kept such that they behave the same as running `make <keyboard>:default` from `qmk_firmware`.

Keymaps in this directory require four key-value pairs:

* `keyboard` (string)
  * This is the name of the keyboard, the same as would be used when running a compile job through `make` (e.g. `make 1upkeyboards/1up60rgb:default`).
* `keymap` (string)
  * Should be set to `default`.
* `layout` (string)
  * This is the layout macro used by the default keymap.
* `layers` (array)
  * The keymap itself. This key should contain one array per layer, which themselves should contain the keycodes that make up that layer.

Additionally, most keymaps contain a `commit` key. This key is not consumed by the API that back-stops QMK Configurator, but is used by Configurator's maintainers to tell which version of a keymap was used to create the JSON keymap in this repository. The value is the SHA of the last commit to modify a board's default `keymap.c` in the `qmk_firmware` repository. The SHA is found by checking out [the `master` branch of the `qmk/qmk_firmware` repository](https://github.com/qmk/qmk_firmware/tree/master/) and running `git log -1 --pretty=oneline -- keyboards/<keyboard>/keymaps/default/keymap.c` (use `keymap.json` if the keyboard in question has this file instead), which should return something similar to:

```
f14629ed1cd7c7ec9089604d64f29a99981558e8 Remove/migrate action_get_macro()s from default keymaps (#5625)
```

In this example, `f14629ed1cd7c7ec9089604d64f29a99981558e8` is the value that should be used for `commit`.


## Example :id=example

If one wished to add a default keymap for the H87a by Hineybush, one would run the `git log` command above against the H87a's default keymap in `qmk_firmware`:

```
user ~/qmk_firmware (master)
$ git log -1 --pretty=oneline master -- keyboards/hineybush/h87a/keymaps/default/keymap.c
ef8878fba5d3786e3f9c66436da63a560cd36ac9 Hineybush h87a lock indicators (#8237)
```

Now that we have the commit hash, we need the keymap (edited for readability):

```c
...
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_all(
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,              KC_PSCR, KC_SCRL, KC_PAUS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_DEL,  KC_END,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_TRNS,                      KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RGUI, KC_RCTL,             KC_LEFT, KC_DOWN, KC_RGHT),

  [1] = LAYOUT_all(
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI,             BL_TOGG, BL_DEC,  BL_INC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_VOLU,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_MPLY, KC_MNXT, KC_VOLD,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_TRNS, KC_TRNS, KC_TRNS),

};
```

The default keymap uses the `LAYOUT_all` macro, so that will be the value of the `layout` key. Compiled to a QMK Configurator JSON keymap, our resulting file should be:

```json
{
  "keyboard": "hineybush/h87a",
  "keymap": "default",
  "commit": "ef8878fba5d3786e3f9c66436da63a560cd36ac9",
  "layout": "LAYOUT_all",
  "layers": [
    [
      "KC_ESC",             "KC_F1",   "KC_F2",   "KC_F3",   "KC_F4",   "KC_F5",   "KC_F6",   "KC_F7",   "KC_F8",   "KC_F9",   "KC_F10",  "KC_F11",  "KC_F12",                "KC_PSCR", "KC_SCRL", "KC_PAUS",
      "KC_GRV",  "KC_1",    "KC_2",    "KC_3",    "KC_4",    "KC_5",    "KC_6",    "KC_7",    "KC_8",    "KC_9",    "KC_0",    "KC_MINS", "KC_EQL",  "KC_BSPC", "KC_BSPC",    "KC_INS",  "KC_HOME", "KC_PGUP",
      "KC_TAB",  "KC_Q",    "KC_W",    "KC_E",    "KC_R",    "KC_T",    "KC_Y",    "KC_U",    "KC_I",    "KC_O",    "KC_P",    "KC_LBRC", "KC_RBRC", "KC_BSLS",               "KC_DEL",  "KC_END",  "KC_PGDN",
      "KC_CAPS", "KC_A",    "KC_S",    "KC_D",    "KC_F",    "KC_G",    "KC_H",    "KC_J",    "KC_K",    "KC_L",    "KC_SCLN", "KC_QUOT", "KC_NUHS", "KC_ENT",
      "KC_LSFT", "KC_NUBS", "KC_Z",    "KC_X",    "KC_C",    "KC_V",    "KC_B",    "KC_N",    "KC_M",    "KC_COMM", "KC_DOT",  "KC_SLSH", "KC_RSFT", "KC_TRNS",                          "KC_UP",
      "KC_LCTL", "KC_LGUI", "KC_LALT",                                  "KC_SPC",                                   "KC_RALT", "MO(1)",   "KC_RGUI", "KC_RCTL",               "KC_LEFT", "KC_DOWN", "KC_RGHT"
    ],
    [
      "KC_TRNS",            "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "RGB_TOG", "RGB_MOD", "RGB_HUD", "RGB_HUI", "RGB_SAD", "RGB_SAI", "RGB_VAD", "RGB_VAI",               "BL_TOGG", "BL_DEC",  "BL_INC",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",    "KC_TRNS", "KC_TRNS", "KC_VOLU",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "QK_BOOT", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",               "KC_MPLY", "KC_MNXT", "KC_VOLD",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",
      "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",                          "KC_TRNS",
      "KC_TRNS", "KC_TRNS", "KC_TRNS",                                  "KC_TRNS",                                  "KC_TRNS", "KC_TRNS", "KC_TRNS", "KC_TRNS",               "KC_TRNS", "KC_TRNS", "KC_TRNS"
    ]
  ]
}
```

The white space in the `layers` arrays have no effect on the functionality of the keymap, but are used to make these files easier for humans to read.


## Caveats :id=caveats

### Layers can only be referenced by number :id=layer-references

A common QMK convention is to name layers using a series of `#define`s, or an `enum` statement:

```c
enum layer_names {
    _BASE,
    _MEDIA,
    _FN
};
```

This works in C, but for Configurator, you *must* use the layer's numeric index – `MO(_FN)` would need to be `MO(2)` in the above example.

### No support for custom code of any kind :id=custom-code

Features that require adding functions to the keymap.c file, such as Tap Dance or Unicode, can not be compiled in Configurator **at all**. Even setting `TAP_DANCE_ENABLE = yes` in the `qmk_firmware` repository at the keyboard level will prevent Configurator from compiling **any** firmware for that keyboard. This is limited both by the API and the current spec of our JSON keymap format.

### Limited Support for Custom keycodes :id=custom-keycodes

There is a way to support custom keycodes: if the logic for a custom keycode is implemented at the keyboard level instead of the keymap level in qmk_firmware, that keycode *can* be used in Configurator and it *will* compile and work. Instead of using the following in your `keymap.c`:

```c
enum custom_keycodes {
    MACRO_1 = SAFE_RANGE,
    MACRO_2,
    MACRO_3
};
...
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MACRO_1:
            if (record->event.pressed) {
                SEND_STRING("This is macro #1.");
            }
            return false;
        case MACRO_2:
            if (record->event.pressed) {
                SEND_STRING("This is macro #2.");
            }
            return false;
        case MACRO_3:
            if (record->event.pressed) {
                SEND_STRING("This is macro #3.");
            }
            return false;
    }
    return true;
};
```

... add the keycode `enum` block to your keyboard's header file (`<keyboard>.h`) as follows (note that the `enum` is named `keyboard_keycodes` here):

```c
enum keyboard_keycodes {
    MACRO_1 = SAFE_RANGE,
    MACRO_2,
    MACRO_3,
    NEW_SAFE_RANGE  // Important!
};
```

... then the logic to your `<keyboard>.c` through `process_record_kb()`:

```c
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MACRO_1:
            if (record->event.pressed) {
                SEND_STRING("This is macro #1.");
            }
            return false;
        case MACRO_2:
            if (record->event.pressed) {
                SEND_STRING("This is macro #2.");
            }
            return false;
        case MACRO_3:
            if (record->event.pressed) {
                SEND_STRING("This is macro #3.");
            }
            return false;
    }
    return process_record_user(keycode, record);
};
```

Note the call to `process_record_user()` at the end. Additionally, users of the keyboard will need to use `NEW_SAFE_RANGE` instead of `SAFE_RANGE` if they wish to add their own custom keycodes at keymap level, beyond what is provided by the keyboard.


## Additional Reading :id=additional-reading

For QMK Configurator to support your keyboard, your keyboard must be present in the `master` branch of the `qmk_firmware` repository. For instructions on this, please see [Supporting Your Keyboard in QMK Configurator](reference_configurator_support.md).
