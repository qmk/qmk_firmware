# Repeat Key

The Repeat Key performs the action of the last pressed key. Tapping the Repeat
Key after tapping the <kbd>Z</kbd> key types another "`z`." This is useful for
typing doubled letters, like the `z` in "`dazzle`": a double tap on <kbd>Z</kbd>
can instead be a roll from <kbd>Z</kbd> to <kbd>Repeat</kbd>, which is
potentially faster and more comfortable. The Repeat Key is also useful for
hotkeys, like repeating Ctrl + Shift + Right Arrow to select by word. 

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
alias `QK_REP`). Optionally, use the keycode `QK_ALT_REPEAT_KEY` (short alias
`QK_AREP`) on another key.

## Keycodes

|Keycode                |Aliases  |Description                          |
|-----------------------|---------|-------------------------------------|
|`QK_REPEAT_KEY`        |`QK_REP` |Repeat the last pressed key          |
|`QK_ALT_REPEAT_KEY`    |`QK_AREP`|Perform alternate of the last key    |

## Alternate Repeating

The Alternate Repeat Key performs the "alternate" action of the last pressed key
if it is defined. By default, Alternate Repeat is defined for navigation keys to
act in the reverse direction. When the last key is the common "select by word"
hotkey Ctrl + Shift + Right Arrow, the Alternate Repeat Key performs Ctrl +
Shift + Left Arrow, which together with the Repeat Key enables convenient
selection by words in either direction.

Alternate Repeat is enabled with the Repeat Key by default. Optionally, to
reduce firmware size, Alternate Repeat may be disabled by adding in config.h:

```c
#define NO_ALT_REPEAT_KEY
```

The following alternate keys are defined by default. See
`get_alt_repeat_key_keycode_user()` below for how to change or add to these
definitions. Where it makes sense, these definitions also include combinations 
with mods, like Ctrl + Left &harr; Ctrl + Right Arrow.

**Navigation** 

|Keycodes                           |Description                        |
|-----------------------------------|-----------------------------------|
|`KC_LEFT` &harr; `KC_RGHT`         | Left &harr; Right Arrow           |
|`KC_UP` &harr; `KC_DOWN`           | Up &harr; Down Arrow              |
|`KC_HOME` &harr; `KC_END`          | Home &harr; End                   |
|`KC_PGUP` &harr; `KC_PGDN`         | Page Up &harr; Page Down          |
|`MS_LEFT` &harr; `MS_RGHT`         | Mouse Cursor Left &harr; Right    |
|`MS_UP`   &harr; `MS_DOWN`         | Mouse Cursor Up &harr; Down       |
|`MS_WHLL` &harr; `MS_WHLR`         | Mouse Wheel Left &harr; Right     |
|`MS_WHLU` &harr; `MS_WHLD`         | Mouse Wheel Up &harr; Down        |

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
|mod + `KC_O` &harr; mod + `KC_I`   | Vim jump list Older &harr; Newer  |
|`KC_J` &harr; `KC_K`               | Down &harr; Up                    |
|`KC_H` &harr; `KC_L`               | Left &harr; Right                 |
|`KC_W` &harr; `KC_B`               | Forward &harr; Backward by Word   |

(where above, "mod" is Ctrl, Alt, or GUI)


## Defining alternate keys

Use the `get_alt_repeat_key_keycode_user()` callback to define the "alternate"
for additional keys or override the default definitions. For example, to define
Ctrl + Y as the alternate of Ctrl + Z, and vice versa, add the following in
keymap.c:

```c
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    if ((mods & MOD_MASK_CTRL)) {  // Was Ctrl held?
        switch (keycode) {
            case KC_Y: return C(KC_Z);  // Ctrl + Y reverses to Ctrl + Z.
            case KC_Z: return C(KC_Y);  // Ctrl + Z reverses to Ctrl + Y.
        }
    }

    return KC_TRNS;  // Defer to default definitions.
}
```

The `keycode` and `mods` args are the keycode and mods that were active with the
last pressed key. The meaning of the return value from this function is:

* `KC_NO` &ndash; do nothing (any predefined alternate key is not used);
* `KC_TRNS` &ndash; use the default alternate key if it exists;
* anything else &ndash; use the specified keycode. Any keycode may be returned
  as an alternate key, including custom keycodes.

Another example, defining Shift + Tab as the alternate of Tab, and vice versa:

```c
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    bool shifted = (mods & MOD_MASK_SHIFT);  // Was Shift held?
    switch (keycode) {
        case KC_TAB:
            if (shifted) {        // If the last key was Shift + Tab,
                return KC_TAB;    // ... the reverse is Tab.
            } else {              // Otherwise, the last key was Tab,
                return S(KC_TAB); // ... and the reverse is Shift + Tab.
            }
    }

    return KC_TRNS;
}
```

#### Eliminating SFBs

Alternate Repeat can be configured more generally to perform an action that
"complements" the last key. Alternate Repeat is not limited to reverse
repeating, and it need not be symmetric. You can use it to eliminate cases of
same-finger bigrams in your layout, that is, pairs of letters typed by the same
finger. The following addresses the top 5 same-finger bigrams in English on
QWERTY, so that for instance "`ed`" may be typed as <kbd>E</kbd>, <kbd>Alt
Repeat</kbd>.

```c
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_E: return KC_D;  // For "ED" bigram.
        case KC_D: return KC_E;  // For "DE" bigram.
        case KC_C: return KC_E;  // For "CE" bigram.
        case KC_L: return KC_O;  // For "LO" bigram.
        case KC_U: return KC_N;  // For "UN" bigram.
    }

    return KC_TRNS;
}
```

#### Typing shortcuts

A useful possibility is having Alternate Repeat press [a
macro](../feature_macros). This way macros can be used without having to
dedicate keys to them. The following defines a couple shortcuts.

* Typing <kbd>K</kbd>, <kbd>Alt Repeat</kbd> produces "`keyboard`," with the
  initial "`k`" typed as usual and the "`eybord`" produced by the macro. 
* Typing <kbd>.</kbd>, <kbd>Alt Repeat</kbd> produces "`../`," handy for "up
  directory" on the shell. Similary, <kbd>.</kbd> types the initial "`.`" and 
  "`./`" is produced by the macro.

```c
enum custom_keycodes {
    M_KEYBOARD = SAFE_RANGE,
    M_UPDIR,
    // Other custom keys...
};

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_K: return M_KEYBOARD;
        case KC_DOT: return M_UPDIR;
    }

    return KC_TRNS;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case M_KEYBOARD: SEND_STRING(/*k*/"eyboard"); break;
        case M_UPDIR: SEND_STRING(/*.*/"./"); break;
    }
    return true;
}
```

## Ignoring certain keys and mods

In tracking what is "the last key" to be repeated or alternate repeated,
modifier and layer switch keys are always ignored. This makes it possible to set
some mods and change layers between pressing a key and repeating it. By default,
all other (non-modifier, non-layer switch) keys are remembered so that they are
eligible for repeating. To configure additional keys to be ignored, define
`remember_last_key_user()` in your keymap.c.

#### Ignoring a key

The following ignores the Backspace key:

```c
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case KC_BSPC:
            return false;  // Ignore backspace.
    }

    return true;  // Other keys can be repeated.
}
```

Then for instance, the Repeat key in <kbd>Left Arrow</kbd>,
<kbd>Backspace</kbd>, <kbd>Repeat</kbd> sends Left Arrow again instead of
repeating Backspace.

The `remember_last_key_user()` callback is called on every key press excluding
modifiers and layer switches. Returning true indicates the key is remembered,
while false means it is ignored.

#### Filtering remembered mods

The `remembered_mods` arg represents the mods that will be remembered with
this key. It can be modified to forget certain mods. This may be
useful to forget capitalization when repeating shifted letters, so that "Aaron"
does not becom "AAron":

```c
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    // Forget Shift on letter keys when Shift or AltGr are the only mods.
    switch (keycode) {
        case KC_A ... KC_Z:
            if ((*remembered_mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
                *remembered_mods &= ~MOD_MASK_SHIFT;
            }
            break;
    }

    return true;
}
```

#### Further conditions

Besides checking the keycode, this callback could also make conditions based on
the current layer state (with `IS_LAYER_ON(layer)`) or mods (`get_mods()`). For
example, the following ignores keys on layer 2 as well as key combinations
involving GUI:

```c
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    if (IS_LAYER_ON(2) || (get_mods() & MOD_MASK_GUI)) {
        return false;  // Ignore layer 2 keys and GUI chords.
    }

    return true;  // Other keys can be repeated.
}
```

::: tip
See [Layer Functions](../feature_layers#functions) and [Checking Modifier State](../feature_advanced_keycodes#checking-modifier-state) for further details.
:::

## Handle how a key is repeated

By default, pressing the Repeat Key will simply behave as if the last key
were pressed again. This also works with macro keys with custom handlers,
invoking the macro again. In case fine-tuning is needed for sensible repetition,
you can handle how a key is repeated with `get_repeat_key_count()` within
`process_record_user()`. 

The `get_repeat_key_count()` function returns a signed count of times the key
has been repeated or alternate repeated. When a key is pressed as usual,
`get_repeat_key_count()` is 0. On the first repeat, it is 1, then the second
repeat, 2, and so on. Negative counts are used similarly for alternate
repeating. For instance supposing `MY_MACRO` is a custom keycode used in the
layout:

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

## Handle how a key is alternate repeated

Pressing the Alternate Repeat Key behaves as if the "alternate" of the last
pressed key were pressed, if an alternate is defined. To define how a particular
key is alternate repeated, use the `get_alt_repeat_key_keycode_user()` callback
as described above to define which keycode to use as its alternate. Beyond this,
`get_repeat_key_count()` may be used in custom handlers to fine-tune behavior
when alternate repeating.

The following example defines `MY_MACRO` as its own alternate, and specially
handles repeating and alternate repeating:

```c
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case MY_MACRO: return MY_MACRO;  // MY_MACRO is its own alternate.
    }
    return KC_TRNS;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MY_MACRO:
            if (get_repeat_key_count() > 0) {        // Repeating.
                if (record->event.pressed) {
                    SEND_STRING("repeat!");    
                }
            } else if (get_repeat_key_count() < 0) { // Alternate repeating.
                if (record->event.pressed) {
                    SEND_STRING("alt repeat!");
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

| Function                       | Description                                                            |
|--------------------------------|------------------------------------------------------------------------|
| `get_last_keycode()`           | The last key's keycode, the key to be repeated.                        |
| `get_last_mods()`              | Mods to apply when repeating.                                          |
| `set_last_keycode(kc)`         | Set the keycode to be repeated.                                        |
| `set_last_mods(mods)`          | Set the mods to apply when repeating.                                  |
| `get_repeat_key_count()`       | Signed count of times the key has been repeated or alternate repeated. |
| `get_alt_repeat_key_keycode()` | Keycode to be used for alternate repeating.                            |
 

## Additional "Alternate" keys

By leveraging `get_last_keycode()` in macros, it is possible to define
additional, distinct "Alternate Repeat"-like keys. The following defines two
keys `ALTREP2` and `ALTREP3` and implements ten shortcuts with them for common
English 5-gram letter patterns, taking inspiration from
[Stenotype](stenography):


| Typing                           | Produces | Typing                           | Produces |
|----------------------------------|----------|----------------------------------|----------|
| <kbd>A</kbd>, <kbd>ALTREP2</kbd> | `ation`  | <kbd>A</kbd>, <kbd>ALTREP3</kbd> | `about`   |
| <kbd>I</kbd>, <kbd>ALTREP2</kbd> | `ition`  | <kbd>I</kbd>, <kbd>ALTREP3</kbd> | `inter`   |
| <kbd>S</kbd>, <kbd>ALTREP2</kbd> | `ssion`  | <kbd>S</kbd>, <kbd>ALTREP3</kbd> | `state`   |
| <kbd>T</kbd>, <kbd>ALTREP2</kbd> | `their`  | <kbd>T</kbd>, <kbd>ALTREP3</kbd> | `there`   |
| <kbd>W</kbd>, <kbd>ALTREP2</kbd> | `which`  | <kbd>W</kbd>, <kbd>ALTREP3</kbd> | `would`   |

```c
enum custom_keycodes {
    ALTREP2 = SAFE_RANGE,
    ALTREP3,
};

// Use ALTREP2 and ALTREP3 in your layout...

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case ALTREP2:
        case ALTREP3:
            return false;  // Ignore ALTREP keys.
    }

    return true;  // Other keys can be repeated.
}

static void process_altrep2(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_A: SEND_STRING(/*a*/"tion"); break;
        case KC_I: SEND_STRING(/*i*/"tion"); break;
        case KC_S: SEND_STRING(/*s*/"sion"); break;
        case KC_T: SEND_STRING(/*t*/"heir"); break;
        case KC_W: SEND_STRING(/*w*/"hich"); break;
    }
}

static void process_altrep3(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_A: SEND_STRING(/*a*/"bout"); break;
        case KC_I: SEND_STRING(/*i*/"nter"); break;
        case KC_S: SEND_STRING(/*s*/"tate"); break;
        case KC_T: SEND_STRING(/*t*/"here"); break;
        case KC_W: SEND_STRING(/*w*/"ould"); break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case ALTREP2: 
            if (record->event.pressed) {
                process_altrep2(get_last_keycode(), get_last_mods());
            }
            return false;

        case ALTREP3:
            if (record->event.pressed) {
                process_altrep3(get_last_keycode(), get_last_mods());
            }
            return false;
    }

    return true;
}
```

