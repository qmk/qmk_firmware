# Macros

Macros allow you to send multiple keystrokes when pressing just one key. QMK has a number of ways to define and use macros. These can do anything you want: type common phrases for you, copypasta, repetitive game movements, or even help you code.

::: warning
**Security Note**: While it is possible to use macros to send passwords, credit card numbers, and other sensitive information it is a supremely bad idea to do so. Anyone who gets a hold of your keyboard will be able to access that information by opening a text editor.
:::

## Using Macros In JSON Keymaps

You can define up to 32 macros in a `keymap.json` file, as used by [Configurator](newbs_building_firmware_configurator), and `qmk compile`. You can define these macros in a list under the `macros` keyword, like this:

```json
{
    "keyboard": "handwired/my_macropad",
    "keymap": "my_keymap",
    "macros": [
        [
            {"action":"down", "keycodes": ["LSFT"]},
            "hello world1",
            {"action": "up","keycodes": ["LSFT"]}
        ],
        [
            {"action":"tap", "keycodes": ["LCTL", "LALT", "DEL"]}
        ],
        [
            "ding!",
            {"action":"beep"}
        ],
        [
            {"action":"tap", "keycodes": ["F1"]},
            {"action":"delay", "duration": 1000},
            {"action":"tap", "keycodes": ["PGDN"]}
        ]
    ],
    "layout": "LAYOUT_all",
    "layers": [
        ["QK_MACRO_0", "QK_MACRO_1", "QK_MACRO_2", "QK_MACRO_3"]
    ]
}
```

### Selecting Your Host Keyboard Layout

If you type in a language other than English, or use a non-QWERTY layout like Colemak, Dvorak, or Workman, you may have set your computer's input language to match this layout. This presents a challenge when creating macros - you may need to type different keys to get the same letters! To address this you can add the `host_language` key to your `keymap.json`, like so:

```json
{
    "keyboard": "handwired/my_macropad",
    "keymap": "my_keymap",
    "host_language": "dvorak",
    "macros": [
        ["Hello, World!"]
    ],
    "layout": "LAYOUT_all",
    "layers": [
        ["QK_MACRO_0"]
    ]
}
```

The current list of available languages is:

| belgian | bepo | br_abnt2 | canadian_multilingual |
|:-------:|:----:|:--------:|:---------------------:|
| **colemak** | **croatian** | **czech** | **danish** |
| **dvorak_fr** | **dvorak** | **dvp** | **estonian** |
| **finnish** | **fr_ch** | **french_afnor** | **french** |
| **french_osx** | **german_ch** | **german** | **german_osx** |
| **hungarian** | **icelandic** | **italian** | **italian_osx_ansi** |
| **italian_osx_iso** | **jis** | **latvian** | **lithuanian_azerty** |
| **lithuanian_qwerty** | **norman** | **norwegian** | **portuguese** |
| **portuguese_osx_iso** | **romanian** | **serbian_latin** | **slovak** |
| **slovenian** | **spanish_dvorak** | **spanish_latin_america** | **spanish** |
| **swedish** | **turkish_f** | **turkish_q** | **uk** |
| **us_international** | **workman** | **workman_zxcvm** |

### Macro Basics

Each macro is an array consisting of strings and objects (dictionaries). Strings are typed to your computer while objects allow you to control how your macro is typed out.

#### Object Format

All objects have one required key: `action`. This tells QMK what the object does. There are currently 5 actions: beep, delay, down, tap, up

Only basic keycodes (prefixed by `KC_`) are supported. Do not include the `KC_` prefix when listing keycodes.

* `beep`
    * Play a bell if the keyboard has [audio enabled](features/audio).
    * Example: `{"action": "beep"}`
* `delay`
    * Pause macro playback. Duration is specified in milliseconds (ms).
    * Example: `{"action": "delay", "duration": 500}`
* `down`
    * Send a key down event for one or more keycodes.
    * Example, single key: `{"action":"down", "keycodes": ["LSFT"]}`
    * Example, multiple keys: `{"action":"down", "keycodes": ["CTRL", "LSFT"]}`
* `tap`
    * Type a chord, which sends a down event for each key followed by an up event for each key.
    * Example, single key: `{"action":"tap", "keycodes": ["F13"]}`
    * Example, multiple keys: `{"action":"tap", "keycodes": ["CTRL", "LALT", "DEL"]}`
* `up`
    * Send a key up event for one or more keycodes.
    * Example, single key: `{"action":"up", "keycodes": ["LSFT"]}`
    * Example, multiple keys: `{"action":"up", "keycodes": ["CTRL", "LSFT"]}`

## Using Macros in C Keymaps

### `SEND_STRING()` & `process_record_user`

See also: [Send String](features/send_string)

Sometimes you want a key to type out words or phrases. For the most common situations, we've provided `SEND_STRING()`, which will type out a string (i.e. a sequence of characters) for you. All ASCII characters that are easily translatable to a keycode are supported (e.g. `qmk 123\n\t`).

Here is an example `keymap.c` for a two-key keyboard:

```c
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {QMKBEST, KC_ESC},
        // ...
    },
};
```

What happens here is this:
We first define a new custom keycode in the range not occupied by any other keycodes.
Then we use the `process_record_user` function, which is called whenever a key is pressed or released, to check if our custom keycode has been activated.
If yes, we send the string `"QMK is the best thing ever!"` to the computer via the `SEND_STRING` macro (this is a C preprocessor macro, not to be confused with QMK macros).
We return `true` to indicate to the caller that the key press we just processed should continue to be processed as normal (as we didn't replace or alter the functionality).
Finally, we define the keymap so that the first button activates our macro and the second button is just an escape button.

?>It is recommended to use the SAFE_RANGE macro as per [Customizing Functionality](custom_quantum_functions).

You might want to add more than one macro.
You can do that by adding another keycode and adding another case to the switch statement, like so:

```c
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    MY_OTHER_MACRO,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("QMK is the best thing ever!");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case QMKURL:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            SEND_STRING("https://qmk.fm/\n");
        } else {
            // when keycode QMKURL is released
        }
        break;

    case MY_OTHER_MACRO:
        if (record->event.pressed) {
           SEND_STRING(SS_LCTL("ac")); // selects all and copies
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {MY_CUSTOM_MACRO, MY_OTHER_MACRO},
        // ...
    },
};
```

::: tip
An enumerated list of custom keycodes (`enum custom_keycodes`) must be declared before `keymaps[]` array, `process_record_user()` and any other function that use the list for the compiler to recognise it.
:::

#### Advanced Macros

In addition to the `process_record_user()` function, is the `post_process_record_user()` function. This runs after `process_record` and can be used to do things after a keystroke has been sent.  This is useful if you want to have a key pressed before and released after a normal key, for instance.

In this example, we modify most normal keypresses so that `F22` is pressed before the keystroke is normally sent, and release it __only after__ it's been released.

```c
static uint8_t f22_tracker;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_F21: //notice how it skips over F22
    case KC_F23 ... KC_EXSEL: //exsel is the last one before the modifier keys
      if (record->event.pressed) {
        register_code(KC_F22); //this means to send F22 down
        f22_tracker++;
        register_code(keycode);
        return false;
      }
      break;
  }
  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_F21: //notice how it skips over F22
    case KC_F23 ... KC_EXSL: //exsel is the last one before the modifier keys
      if (!record->event.pressed) {
        f22_tracker--;
        if (!f22_tracker) {
            unregister_code(KC_F22); //this means to send F22 up
        }
      }
      break;
  }
}
```


#### TAP, DOWN and UP

You may want to use keys in your macros that you can't write down, such as `Ctrl` or `Home`.
You can send arbitrary keycodes by wrapping them in:

* `SS_TAP()` presses and releases a key.
* `SS_DOWN()` presses (but does not release) a key.
* `SS_UP()` releases a key.

For example:

```c
SEND_STRING(SS_TAP(X_HOME));
```

Would tap `KC_HOME` - note how the prefix is now `X_`, and not `KC_`. You can also combine this with other strings, like this:

```c
SEND_STRING("VE"SS_TAP(X_HOME)"LO");
```

Which would send "VE" followed by a `KC_HOME` tap, and "LO" (spelling "LOVE" if on a newline).

Delays can be also added to the string:

* `SS_DELAY(msecs)` will delay for the specified number of milliseconds.

For example:

```c
SEND_STRING("VE" SS_DELAY(1000) SS_TAP(X_HOME) "LO");
```

Which would send "VE" followed by a 1-second delay, then a `KC_HOME` tap, and "LO" (spelling "LOVE" if on a newline, but delayed in the middle).

There's also a couple of mod shortcuts you can use:

* `SS_LCTL(string)`
* `SS_LSFT(string)`
* `SS_LALT(string)` or `SS_LOPT(string)`
* `SS_LGUI(string)`, `SS_LCMD(string)` or `SS_LWIN(string)`
* `SS_RCTL(string)`
* `SS_RSFT(string)`
* `SS_RALT(string)`, `SS_ROPT(string)` or `SS_ALGR(string)`
* `SS_RGUI(string)`, `SS_RCMD(string)` or `SS_RWIN(string)`

These press the respective modifier, send the supplied string and then release the modifier.
They can be used like this:

```c
SEND_STRING(SS_LCTL("a"));
```

Which would send Left Control+`a` (Left Control down, `a`, Left Control up) - notice that they take strings (eg `"k"`), and not the `X_K` keycodes.

#### Alternative Keymaps

By default, it assumes a US keymap with a QWERTY layout; if you want to change that (e.g. if your OS uses software Colemak), include this somewhere in your keymap:

```c
#include "sendstring_colemak.h"
```

#### Strings in Memory

If for some reason you're manipulating strings and need to print out something you just generated (instead of being a literal, constant string), you can use `send_string()`, like this:

```c
char my_str[4] = "ok.";
send_string(my_str);
```

The shortcuts defined above won't work with `send_string()`, but you can separate things out to different lines if needed:

```c
char my_str[4] = "ok.";
SEND_STRING("I said: ");
send_string(my_str);
SEND_STRING(".."SS_TAP(X_END));
```


### Advanced Macro Functions

There are some functions you may find useful in macro-writing. Keep in mind that while you can write some fairly advanced code within a macro, if your functionality gets too complex you may want to define a custom keycode instead. Macros are meant to be simple.

::: tip
You can also use the functions described in [Useful function](ref_functions) and [Checking modifier state](feature_advanced_keycodes#checking-modifier-state) for additional functionality. For example, `reset_keyboard()` allows you to reset the keyboard as part of a macro and `get_mods() & MOD_MASK_SHIFT` lets you check for the existence of active shift modifiers.
:::

#### `record->event.pressed`

This is a boolean value that can be tested to see if the switch is being pressed or released. An example of this is

```c
    if (record->event.pressed) {
        // on keydown
    } else {
        // on keyup
    }
```

#### `register_code(<kc>);`

This sends the `<kc>` keydown event to the computer. Some examples would be `KC_ESC`, `KC_C`, `KC_4`, and even modifiers such as `KC_LSFT` and `KC_LGUI`.

#### `unregister_code(<kc>);`

Parallel to `register_code` function, this sends the `<kc>` keyup event to the computer. If you don't use this, the key will be held down until it's sent.

#### `tap_code(<kc>);`

Sends `register_code(<kc>)` and then `unregister_code(<kc>)`. This is useful if you want to send both the press and release events ("tap" the key, rather than hold it).

If `TAP_CODE_DELAY` is defined (default 0), this function waits that many milliseconds before calling `unregister_code(<kc>)`. This can be useful when you are having issues with taps (un)registering.

If the keycode is `KC_CAPS`, it waits `TAP_HOLD_CAPS_DELAY` milliseconds instead (default 80), as macOS prevents accidental Caps Lock activation by waiting for the key to be held for a certain amount of time.

#### `tap_code_delay(<kc>, <delay>);`

Like `tap_code(<kc>)`, but with a `delay` parameter for specifying arbitrary intervals before sending the unregister event.

#### `register_code16(<kc>);`, `unregister_code16(<kc>);`, `tap_code16(<kc>);` and `tap_code16_delay(<kc>, <delay>);`

These functions work similar to their regular counterparts, but allow you to use modded keycodes (with Shift, Alt, Control, and/or GUI applied to them).

Eg, you could use `register_code16(S(KC_5));` instead of registering the mod, then registering the keycode.

#### `clear_keyboard();`

This will clear all mods and keys currently pressed.

#### `clear_mods();`

This will clear all mods currently pressed.

#### `clear_keyboard_but_mods();`

This will clear all keys besides the mods currently pressed.

### Advanced Example:

#### Super ALT↯TAB

This macro will register `KC_LALT` and tap `KC_TAB`, then wait for 1000ms. If the key is tapped again, it will send another `KC_TAB`; if there is no tap, `KC_LALT` will be unregistered, thus allowing you to cycle through windows.

```c
bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
```
