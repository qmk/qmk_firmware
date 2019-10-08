# Table of Contents
1. [Overview](#overview)[[documentation](https://docs.qmk.fm/#/feature_userspace)]
2. [Keyboard Layout Templates](#keyboard-layout-templates)
3. [Custom Keycodes](#custom-keycodes) [[documentation](https://docs.qmk.fm/#/feature_macros?id=the-new-way-send_string-amp-process_record_user)]
4. [Tap Dances](#tap-dances) [[documentation](https://docs.qmk.fm/#/feature_tap_dance)]
5. [Encoders](#encoders) [[documentation](https://docs.qmk.fm/#/feature_encoders)]
6. [Leader Key](#leader-key) [[documentation](https://docs.qmk.fm/#/feature_leader_key)]
7. [Unicode](#unicode) [[documentation](https://docs.qmk.fm/#/feature_unicode)]
8. [Combo Keys](#combo-keys) [[documentation](https://docs.qmk.fm/#/feature_combo)]
9. [Secret Macros](#secret-macros) [[documentation](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/readme_secrets.md)]

# [Overview](#overview)
Thanks to [drashna](https://github.com/drashna) and the people of the discord server and everyone else in the qmk_firmware/users/ directory :)

## [Keyboard Layout Templates](#keyboard-layout-temple)
This borrows from [jola5](https://github.com/jola5)'s "Not quite neo" code. The code of the userspace is shared between all keyboards, so that one can maintain functionality of all keyboards at once by modifying a few files in a central location.

This makes adding tap/hold mods, or other special keycodes or functions to all keyboards super easy, as it's done to all of them at once.

The caveat here is that the keymap needs a processor/wrapper, as it doesn't like the substitutions. However, this is as simple as just pushing it through a define. For instance:

`#define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)`

Once that's been done and you've switched the keymaps to use the "wrapper", it will read the substitution blocks just fine.

Credit goes to [jola5](https://github.com/jola5) for first implementing this awesome idea.

## [Custom Keycodes](#custom-keycodes)
Declared in `process_records.h` and `template.h` and defined in `process_record_user` in template.c 

## [Tap Dances](#tap-dances)
To enable set `TAP_DANCE_ENABLE = yes` in *rules.mk*. See file *tap_dances.{c,h}*

TODO: Command-line movement stuff is a pain when typing normally

TODO: Make use of `TD_SPC` and `TD_QT{1..3}`

## [Leader Key](#leader-key)
To enable set `LEADER_ENABLE = yes` in file *rules.mk*

|LEADER_DICTIONARY()|program| description |
|---|---|---|
| W |vim/tmux| save file, switch pane and repeat last command   |
| T |tmux| send default prefix |
| A |tmux| switch pane|
|T + T|tmux| send default prefix to a nested session |
|T + R|tmux| switch pane and repeat last command |
|V + Z|vim | zoom current split|
|V + R|vim | search and replace|
|V + T|vim | move current split to its own tab|
|3x Backspace|keyboard| Reset Keyboard |

`LEADER_DICTIONARY()` is defined in *leader.c*

## [Combo Keys](#combo-keys)
To enable set `COMBO_ENABLE = yes` in file *rules.mk*.
Number of combos and timeout are defined in *config.h*

Press key chord to use. 

|Combo|description   | 
|---|---|
| CV | Paste   |
| XC | Cut  |
| ZV | Copy  |
| QP | KC_SLEEP  |

Combos are defined in *combo.h* and *combo.c*

## [Unicode](#unicode)
To enable set `UNICODE_ENABLE = yes` or `UNICODEMAP_ENABLE = yes` in file *rules.mk*

## [Encoders](#encoders)
To enable set `ENCODER_ENABLE = yes` in *rules.mk*.

In the keyboard's *config.h* adjust according to your keyboard:

```c
// Example ProMicro
#define ENCODERS_PAD_A { F4 } //PIN A3
#define ENCODERS_PAD_B { F5 } //PIN A2
```

Check the [documentation](https://docs.qmk.fm/#/feature_encoders) for more information
The first rotary encoder is configured such as:

|Modifier|description|
|---|---|
| None | General navigation. Page up/down |
| SHIFT | Fast navigation. Home/end |
| CTRL | Vertical navigation. Up/down |
| CTRL+SHIFT | Horizontal navigation. Left/right |
| ALT | Audio volume control. |
| GUI | Browser navigation(windows). Forward/backward |
| ALT+SHIFT | Form navigation. Tab up/down |
| ALT+CTRL | Media control. (Play|pause)/mute |
| HYPER | Media navigation. Next/prev track |

Key codes are stored as `uint16_t encoder_actions[2][9]` in *encoder.c*


## Diablo Layer
Currently not in use.
[Back to Top](#table-of-contents)

# [Secret Macros](#secret-macros)
To enable set `NO_SECRETS = yes` in *rules.mk*.

With help from gitter and Colinta, this adds the ability to add hidden macros from other users.  

First, I have several files that are hidden/excluded from Git/GitHub.  These contain everything needed for the macros. To hide these files, open *.git/info/exclude* and add `secrets.c` and  `secrets.h` to that file, below the comments.

And this requires `KC_SECRET_1` through `KC_SECRET_5` to be defined in your *<name>.h* file to define the keycodes for the new macros. 


### .git/info/exclude

```console
# git ls-files --others --exclude-from=.git/info/exclude
# Lines that start with '#' are comments.
# For a project mostly in C, the following would be a good set of
# exclude patterns (uncomment them if you want to use them):
# *.[oa]
# *~
/users/<name>/secrets.c
/users/<name>/secrets.h
```

Then you can create these files:

### secrets.c

```c
#include "<name>.h"  // replace <name> with your keymap's "h" file, or whatever file stores the keycodes

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
static const char * const secret[] = {
  "test1",
  "test2",
  "test3",
  "test4",
  "test5"
};
#endif

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SECRET_1 ... KC_SECRET_5: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        send_string_with_delay(secret[keycode - KC_SECRET_1], MACRO_TIMER);
      }
      return false;
      break;
  }
  return true;
}
```

### secrets.h

```c
static const char * const secrets[] = {
  "secret1",
  "secret2",
  "secret3",
  "secret4",
  "secret5"
};
```

Replacing the strings with the codes that you need.

### name.c

In the *<name>.c* file, you will want to add this to the top:

```c
__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}
```

This is so that the function can be called here, and replaced in the `secrets.c` file, and so it won't error out if it doesn't exist.

And then, in the `process_record_user` function, assuming you have `return process_record_keymap(keycode, record)` here,  you'll want to replace the "final" return with the following. Otherwise, you want to replace the `return true;` with `return process_record_secrets(keycode, record);`

```c
  return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
}
```

### rules.mk

Here, you want your */users/<name>/rules.mk* file to "detect" the existence of the *secrets.c* file, and only add it if the file exists.  To do so, add this block:

```make
ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
  SRC += secrets.c
endif
```

Additionally, if you want to make sure that you can disable the function without messing with the file, you need to add this to your */users/<name>/rules.mk*, so that it catches the flag:

```make
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
```

Then, if you run `make keyboard:name NO_SECRETS=yes`, it will default to the test strings in your *<name>.c* file, rather than reading from your file.
[Back to Top](#table-of-contents)
