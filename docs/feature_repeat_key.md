# Repeat Key

The Repeat Key performs the action of the last pressed key. Tapping the Repeat
Key after tapping the <kbd>Z</kbd> key types another "`z`." The Repeat Key is
useful for hotkeys, like repeating Ctrl + Shift + Right Arrow to select
by word. It can also be useful for typing doubled letters, like the `z` in
"`dazzle`": a double tap on <kbd>Z</kbd> can instead be a roll from <kbd>Z</kbd>
to <kbd>Repeat</kbd>, which is potentially faster and more comfortable. 

Repeat Key remembers mods that were active with the last key press. These mods
are combined with any additional mods while pressing the Repeat Key. If the last
press key was <kbd>Ctrl</kbd> + <kbd>Z</kbd>, then <kbd>Shift</kbd> +
<kbd>Repeat</kbd> performs Ctrl + Shift + `Z`.

## How do I enable Repeat Key

In your `rules.mk`, add:

```make
REPEAT_KEY_ENABLE = yes
```

Then pick a key in your keymap and assign it the keycode `QK_REPEAT_KEY` (short
alias `QK_REP`). Optionally, use the keycode `QK_REVERSE_REPEAT_KEY` (short
alias `QK_RREP`) on another key.

## Keycodes

|Keycode                |Aliases  |Description                          |
|-----------------------|---------|-------------------------------------|
|`QK_REPEAT_KEY`        |`QK_REP` |Repeat the last pressed key          |
|`QK_REVERSE_REPEAT_KEY`|`QK_RREP`|Perform the reverse of the last key  |

## Reverse Repeating

The Reverse Repeat Key performs the "reverse" of the last pressed key if it is
defined. When the last key is the common "select by word" hotkey Ctrl + Shift +
Right Arrow, the Reverse Repeat Key performs Ctrl + Shift + Left Arrow, which
together with the Repeat Key enables convenient selection by words in either
direction.

Reverse Repeat is enabled with the Repeat Key by default. Optionally, to reduce
firmware size, Reverse Repeat may be disabled by adding in config.h:

```c
#define NO_REVERSE_REPEAT_KEY
```

The following reverse keys are defined by default. See
`get_rev_repeat_key_keycode_user()` below for how to change or add to these
definitions. Where it makes sense, these definitions also include combinations 
with mods, like Ctrl + Left &harr; Ctrl + Right Arrow.

**Navigation** 

|Keycodes                           |Description                        |
|-----------------------------------|-----------------------------------|
|`KC_LEFT` &harr; `KC_RGHT`         | Left &harr; Right Arrow           |
|`KC_UP` &harr; `KC_DOWN`           | Up &harr; Down Arrow              |
|`KC_HOME` &harr; `KC_END`          | Home &harr; End                   |
|`KC_PGUP` &harr; `KC_PGDN`         | Page Up &harr; Page Down          |
|`KC_MS_L` &harr; `KC_MS_R`         | Mouse Cursor Left &harr; Right    |
|`KC_MS_U` &harr; `KC_MS_D`         | Mouse Cursor Up &harr; Down       |
|`KC_WH_L` &harr; `KC_WH_R`         | Mouse Wheel Left &harr; Right     |
|`KC_WH_U` &harr; `KC_WH_D`         | Mouse Wheel Up &harr; Down        |

**Misc** 

|Keycodes                           |Description                        |
|-----------------------------------|-----------------------------------|
|`KC_BSPC` &harr; `KC_DEL`          | Backspace &harr; Delete           |
|`KC_LBRC` &harr; `KC_RBRC`         | `[` &harr; `]`                    |
|`KC_LCBR` &harr; `KC_RCBR`         | `{` &harr; `}`                    |

**Media** 

|Keycodes                           |Description                        |
|-----------------------------------|-----------------------------------|
|`KC_WBAK` &harr; `KC_WFWD`         | Browser Back &harr; Forward       |
|`KC_MNXT` &harr; `KC_MPRV`         | Next &harr; Previous Media Track  |
|`KC_MFFD` &harr; `KC_MRWD`         | Fast Forward &harr; Rewind Media  |
|`KC_VOLU` &harr; `KC_VOLD`         | Volume Up &harr; Down             |
|`KC_BRIU` &harr; `KC_BRID`         | Brightness Up &harr; Down         |

**Hotkeys in Vim, Emacs, and other programs**

|Keycodes                           |Description                        |
|-----------------------------------|-----------------------------------|
|mod + `KC_F` &harr; mod + `KC_B`   | Forward &harr; Backward           |
|mod + `KC_D` &harr; mod + `KC_U`   | Down &harr; Up                    |
|mod + `KC_N` &harr; mod + `KC_P`   | Next &harr; Previous              |
|mod + `KC_A` &harr; mod + `KC_E`   | Home &harr; End                   |
|`KC_J` &harr; `KC_K`               | Down &harr; Up                    |
|`KC_H` &harr; `KC_L`               | Left &harr; Right                 |
|`KC_W` &harr; `KC_B`               | Forward &harr; Backward by Word   |

(where above, "mod" is Ctrl, Alt, or GUI)


## Customization

### Defining reverse keys

Use the `get_rev_repeat_key_keycode_user()` callback to define the "reverse" 
key for additional keys or override the default definitions.
For example, to define Ctrl + Y as the reverse of Ctrl + Z, and vice versa, add
the following in keymap.c:

```c
uint16_t get_rev_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {  // Was Ctrl held?
        switch (keycode) {
            case KC_Y: return C(KC_Z);  // Ctrl + Y reverses to Ctrl + Z.
            case KC_Z: return C(KC_Y);  // Ctrl + Z reverses to Ctrl + Y.
        }
    }

    return KC_NO;
}
```

The `keycode` and `mods` args are the keycode and mods that were active with the
last pressed key. The function returns the keycode for the reverse key, or
`KC_NO` to defer to the default definitions. Any keycode may be returned as a
reverse key, including custom keycodes.

Another example, defining Shift + Tab as the reverse of Tab, and vice versa:

```c
uint16_t get_rev_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    bool shifted = (mods & MOD_MASK_SHIFT);  // Was Shift held?
    switch (keycode) {
        case KC_TAB:
            if (shifted) {        // If the last key was Shift + Tab,
                return KC_TAB;    // ... the reverse is Tab.
            } else {              // Otherwise, the last key was Tab,
                return S(KC_TAB); // ... and the reverse is Shift + Tab.
            }
    }

    return KC_NO;
}
```


### Ignoring certain keys

By default, the Repeat Key and Reverse Repeat Key ignore modifier and layer
switch keys in tracking what the "last" key was. This enables possibly setting
some mods and changing layers between pressing a key and repeating it. To
customize which keys are ignored, define `get_repeat_key_eligible()` in your
keymap.c. The default implementation is

```c
bool get_repeat_key_eligible(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Ignore MO, TO, TG, and TT layer switch keys.
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
        // Ignore mod keys.
        case KC_LCTL ... KC_RGUI:
        case KC_HYPR:
        case KC_MEH:
        // Ignore one-shot keys.
#ifndef NO_ACTION_ONESHOT
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
#endif  // NO_ACTION_ONESHOT
            return false;

        // Ignore hold events on tap-hold keys.
#ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
#ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#endif  // NO_ACTION_LAYER
            if (record->tap.count == 0) {
                return false;
            }
            break;
#endif  // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            if (IS_SWAP_HANDS_KEYCODE(keycode) || record->tap.count == 0) {
                return false;
            }
            break;
#endif  // SWAP_HANDS_ENABLE
    }

    return true;
}
```

This callback is called on every key press. Returning true indicates the key is
eligible for repeating (or reverse repeating), while false means it is ignored.

Besides checking the keycode, this callback could also make conditions based on
the current layer state (with `IS_LAYER_ON(layer)`) or mods (`get_mods()`). For
example, the following ignores keys on layer 2 as well as key combinations
involving GUI:

```c
bool get_repeat_key_eligible(uint16_t keycode, keyrecord_t* record) {
    if (IS_LAYER_ON(2) || (get_mods() & MOD_MASK_GUI)) {
        return false;
    }

    switch (keycode) {
        // Same as above...
    }

    return true;
}
```

?> See [Layer Functions](feature_layers.md#functions) and [Checking Modifier
State](feature_advanced_keycodes.md#checking-modifier-state) for further
details.
 

### Handle how a key is repeated

By default, pressing the Repeat Key will simply behave as if the last key
were pressed again. This also works with macro keys with custom handlers,
invoking the macro again. In case fine-tuning is needed for sensible repetition,
you can handle how a key is repeated with `get_repeat_key_count()` within
`process_record_user()`. 

The `get_repeat_key_count()` function returns a signed count of times the key
has been repeated or reverse repeated. When a key is pressed as usual,
`get_repeat_key_count()` is 0. On the first repeat, it is 1, then the second
repeat, 2, and so on. Negative counts are used similarly for reverse repeating.
For instance supposing `MY_MACRO` is a custom keycode used in the layout:

```c
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MY_MACRO:
            if (get_repeat_key_count() > 0) {
                // MY_MACRO is being repeated!
                if (record->event.pressed) {
                    SEND_STRING("repeat!");    
                }
            } else {                          
                // MY_MACRO is being used normally.
                if (record->event.pressed) {  
                    SEND_STRING("macro");
                }
            }
            return false;
     
        // Other macros...
    }
    return true;
}
```

### Handle how a key is reverse repeated

Pressing the Reverse Repeat Key behaves as if the "reverse" of the last pressed
key were pressed, if a reverse is defined. To define how a particular key is
reverse repeated, use the `get_rev_repeat_key_keycode_user()` callback as
described above to define which keycode to use as its reverse. Beyond this,
`get_repeat_key_count()` may be used in custom handlers to fine-tune behavior
when reverse repeating.

The following example defines `MY_MACRO` as its own reverse, and specially
handles repeating and reverse repeating:

```c
uint16_t get_rev_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case MY_MACRO: return MY_MACRO;  // Define MY_MACRO as its own reverse.
    }
    return KC_NO;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MY_MACRO:
            if (get_repeat_key_count() > 0) {        // Repeating.
                if (record->event.pressed) {
                    SEND_STRING("repeat!");    
                }
            } else if (get_repeat_key_count() < 0) { // Reverse repeating.
                if (record->event.pressed) {
                    SEND_STRING("reverse!");    
                }
            } else {                                 // Used normally.
                if (record->event.pressed) {  
                    SEND_STRING("macro");
                }
            }
            return false;
     
        // Other macros...
    }
    return true;
}
```


## Functions

| Function                      | Description                                 |
|-------------------------------|---------------------------------------------|
| `get_repeat_key_count()`      | Signed count of times the key has been repeated or reverse repeated. |
| `get_repeat_key_keycode()`    | The last key's keycode, the key to be repeated.   |
| `get_repeat_key_mods()`       | Mods to apply when repeating.                     |
| `set_repeat_key_keycode(kc)`  | Set the keycode to be repeated.                   |
| `set_repeat_key_mods(mods)`   | Set the mods to apply when repeating.             |
|`get_rev_repeat_key_keycode()` | Keycode to be used for reverse repeating.         |

