# Macros

Macros allow you to send multiple keystrokes when pressing just one key. QMK has a number of ways to define and use macros. These can do anything you want: type common phrases for you, copypasta, repetitive game movements, or even help you code.

!> **Security Note:** While it is possible to use macros to send passwords, credit card numbers and other sensitive information, it is a supremely bad idea to do so. Anyone who gets a hold of your keyboard will be able to access that information by opening a text editor.


## The New Way: `SEND_STRING()` & `process_record_user`

Sometimes you want a key to type out words or phrases. For the most common situations we've provided `SEND_STRING()`, which will type out your string (i.e. a sequence of characters) for you. All ASCII characters that are easily translated to a keycode are supported (e.g. `\n\t`).

?> For sending Unicode strings, check out the [Unicode feature](feature_unicode.md) and, specifically, [`send_unicode_string()`](feature_unicode.md#send_unicode_string).

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

### Advanced Macros

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
    case KC_F23 ... KC_EXSEL: //exsel is the last one before the modifier keys
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


### TAP, DOWN and UP

You may want to use keys in your macros that you can't write down, such as `Ctrl` or `Home`.
You can send arbitrary keycodes by wrapping them in:

* `SS_TAP()` presses and releases a key.
* `SS_DOWN()` presses (but does not release) a key.
* `SS_UP()` releases a key.

For example:

    SEND_STRING(SS_TAP(X_HOME));

Would tap `KC_HOME` - note how the prefix is now `X_`, and not `KC_`. You can also combine this with other strings, like this:

    SEND_STRING("VE"SS_TAP(X_HOME)"LO");

Which would send "VE" followed by a `KC_HOME` tap, and "LO" (spelling "LOVE" if on a newline).

Delays can be also added to the string:

* `SS_DELAY(msecs)` will delay for the specified number of milliseconds.

For example:

    SEND_STRING("VE" SS_DELAY(1000) SS_TAP(X_HOME) "LO");

Which would send "VE" followed by a 1-second delay, then a `KC_HOME` tap, and "LO" (spelling "LOVE" if on a newline, but delayed in the middle).

There's also a couple of mod shortcuts you can use:

* `SS_LCTL(string)`
* `SS_LSFT(string)`
* `SS_LALT(string)`
* `SS_LGUI(string)`, `SS_LCMD(string)` or `SS_LWIN(string)`
* `SS_RCTL(string)`
* `SS_RSFT(string)`
* `SS_RALT(string)` or `SS_ALGR(string)`
* `SS_RGUI(string)`, `SS_RCMD(string)` or `SS_RWIN(string)`

These press the respective modifier, send the supplied string and then release the modifier.
They can be used like this:

    SEND_STRING(SS_LCTL("a"));

Which would send Left Control+`a` (Left Control down, `a`, Left Control up) - notice that they take strings (eg `"k"`), and not the `X_K` keycodes.

### Alternative Keymaps

By default, it assumes a US keymap with a QWERTY layout; if you want to change that (e.g. if your OS uses software Colemak), include this somewhere in your keymap:

    #include <sendstring_colemak.h>

### Strings in Memory

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


## Advanced Macro Functions

There are some functions you may find useful in macro-writing. Keep in mind that while you can write some fairly advanced code within a macro, if your functionality gets too complex you may want to define a custom keycode instead. Macros are meant to be simple.

?> You can also use the functions described in [Useful function](ref_functions.md) for additional functionality. For example `reset_keyboard()` allows you to reset the keyboard as part of a macro.

### `record->event.pressed`

This is a boolean value that can be tested to see if the switch is being pressed or released. An example of this is

```c
    if (record->event.pressed) {
        // on keydown
    } else {
        // on keyup
    }
```

### `register_code(<kc>);`

This sends the `<kc>` keydown event to the computer. Some examples would be `KC_ESC`, `KC_C`, `KC_4`, and even modifiers such as `KC_LSFT` and `KC_LGUI`.

### `unregister_code(<kc>);`

Parallel to `register_code` function, this sends the `<kc>` keyup event to the computer. If you don't use this, the key will be held down until it's sent.

### `tap_code(<kc>);`

This will send `register_code(<kc>)` and then `unregister_code(<kc>)`. This is useful if you want to send both the press and release events ("tap" the key, rather than hold it).

If you're having issues with taps (un)registering, you can add a delay between the register and unregister events by setting `#define TAP_CODE_DELAY 100` in your `config.h` file. The value is in milliseconds.

### `register_code16(<kc>);`, `unregister_code16(<kc>);` and `tap_code16(<kc>);`

These functions work similar to their regular counterparts, but allow you to use modded keycodes (with Shift, Alt, Control, and/or GUI applied to them).

Eg, you could use `register_code16(S(KC_5));` instead of registering the mod, then registering the keycode.

### `clear_keyboard();`

This will clear all mods and keys currently pressed.

### `clear_mods();`

This will clear all mods currently pressed.

### `clear_keyboard_but_mods();`

This will clear all keys besides the mods currently pressed.

## Advanced Example:

### Super ALT↯TAB

This macro will register `KC_LALT` and tap `KC_TAB`, then wait for 1000ms. If the key is tapped again, it will send another `KC_TAB`; if there is no tap, `KC_LALT` will be unregistered, thus allowing you to cycle through windows.

```c
bool is_alt_tab_active = false;    # ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        # we will be using them soon.

enum custom_keycodes {             # Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               # This will do most of the grunt work with the keycodes.
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

void matrix_scan_user(void) {     # The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
```

---

##  **(DEPRECATED)** The Old Way: `MACRO()` & `action_get_macro`

!> This is inherited from TMK, and hasn't been updated - it's recommended that you use `SEND_STRING` and `process_record_user` instead.

By default QMK assumes you don't have any macros. To define your macros you create an `action_get_macro()` function. For example:

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LSFT), T(H), U(LSFT), T(I), D(LSFT), T(1), U(LSFT), END);
            case 1:
                return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
        }
    }
    return MACRO_NONE;
};
```

This defines two macros which will be run when the key they are assigned to is pressed. If instead you'd like them to run when the key is released you can change the if statement:

    if (!record->event.pressed) {

### Macro Commands

A macro can include the following commands:

* I() change interval of stroke in milliseconds.
* D() press key.
* U() release key.
* T() type key(press and release).
* W() wait (milliseconds).
* END end mark.

### Mapping a Macro to a Key

Use the `M()` function within your keymap to call a macro. For example, here is the keymap for a 2-key keyboard:

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        M(0), M(1)
    ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LSFT), T(H), U(LSFT), T(I), D(LSFT), T(1), U(LSFT), END);
            case 1:
                return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
        }
    }
    return MACRO_NONE;
};
```

When you press the key on the left it will type "Hi!" and when you press the key on the right it will type "Bye!".

### Naming Your Macros

If you have a bunch of macros you want to refer to from your keymap while keeping the keymap easily readable you can name them using `#define` at the top of your file.

```c
#define M_HI M(0)
#define M_BYE M(1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        M_HI, M_BYE
    ),
};
```


## Advanced Example:

### Single-Key Copy/Paste

This example defines a macro which sends `Ctrl-C` when pressed down, and `Ctrl-V` when released.

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch(id) {
        case 0: {
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(C), U(LCTL), END  );
            } else {
                return MACRO( D(LCTL), T(V), U(LCTL), END  );
            }
            break;
        }
    }
    return MACRO_NONE;
};
```
