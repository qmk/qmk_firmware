# User Pointing Device customization

To disable the customized pointing device code and implement it at the keymap, add `CUSTOM_POINTING_DEVICE = no` to your `rules.mk`.

## Automatic Mouse Layer

Movement on the optical sensor triggers a layer that has all of the mouse keys on that layer.  After a set time, the layer will automatically turn itself off after 650ms.

Also, using mousekeys will extend the amount of time that the layer will stay active. 

Additionally, layer keys for the mouse layer will lock the layer on.

# Caps Word

This is taken from [Pascal Getreuer's implemenation](https://getreuer.info/posts/keyboards/caps-word/index.html), with a number of modifications. 

To enable Caps Word, add `CAPS_WORD_ENABLE = yes` to your `rules.mk`.

This is mostly a reproduction of Pascal's docs:

## Overview

All-caps identifiers like “MOD_MASK_ALT” are awkward to type.

Caps Lock would be the standard solution to this problem, but it is awkward: it needs a dedicated key to toggle it (an imposition on smaller keyboards), and we need to remember to toggle it off after typing the word. Or with normal shifting, we either perform finger gymnastics or need to stop typing in the middle of the word to release shift with one hand to switch to holding shift with the other hand. In my experience, this is a nuisance especially if your shift keys are mod-taps, as in home row mods.

Caps Word, implemented here, is a modern alternative to Caps Lock:

* Caps Word is activated by pressing the left and right shift keys at the same time. This way you don’t need a dedicated key for using Caps Word.
* Caps Word automatically disables itself at the end of the word.

**Compatibility**: I’ve tested that this implementation works with one-shot mods and Space Cadet Shift, and it predictably handles key repeating.

Unlike some other QMK Caps Word implementations, this library does not use the Caps Lock (KC_CAPS) keycode. It works even if the OS remaps Caps Lock to Ctrl or something else, as Emacs and Vim users often do.

## Using Caps Word
With the above flashed to your keyboard:

1. **Activating**: Press and release both left and right shift keys at the same time. If your shift keys are mod-taps, activate Caps Word by holding both shift mod-tap keys until the tapping term, then release them.
2. Then begin typing to get capitalized letters.
3. **Disabling**: Caps Word disables itself when the next word breaking key is typed.

If you want to explicitly stop Caps Word, press and release Ctrl or another non-shift modifier or layer key. This also disables Caps Word.

## Explanation
The code checks the mod bits on each key event, enabling Caps Word when both left and right shifts are active.

While enabled, Caps Word automatically presses and releases left shift (KC_LSFT) as needed so that letters are shifted and other keys are not. The word continues while typing a–z, 0–9, -, _, and backspace. Any other key is considered “word breaking” and disables Caps Word. You can edit the switch statement at the end of the process_caps_word() function to adjust which keys count as word breaking.

# Secret Macros

With help from gitter and Colinta, this adds the ability to add hidden macros from other users.  

First, I have several files that are hidden/excluded from Git/GitHub.  These contain everything needed for the macros. To hide these files, open `.git/info/exclude` and add `secrets.c` and `secrets.h` to that file, below the comments.

And this requires `KC_SECRET_1` through `KC_SECRET_5` to be added in your keycode enum (usually in your `<name>.h` file) the keycodes for the new macros. 

## Git Exclusion 

To prevent `git` from seeing, or committing the secret files, you can exclude them.   What's the point of having secrets if they're posted on GitHub for everyone to see!?!

You can do this with the `.git/info/exclude` file, so that it's only ignored locally.  Unfortunately, that means it's not consistently handled on each system. 

However, if you create a `.gitignore` file in the same folder, you keep things consistent between every system that the code is checked out on. 

```c
secrets.c
secrets.h
```

## secrets.c

Here is the magic. This handles including the "secrets", and adding the custom macros to send them. 

```c
#include "drashna.h"  // replace with your keymap's "h" file, or whatever file stores the keycodes

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

## secrets.h

Now, for the actual secrets!  The file needs to look like 

```c
static const char *  secrets[] = {
  "secret1",
  "secret2",
  "secret3",
  "secret4",
  "secret5"
};
```

Replacing the strings with the codes that you need.

## Process Record

In whichever file you have your `process_record_*` function in, you will want to add this to the top:

```c
__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}
```

This is so that the function can be called here, and replaced in the `secrets.c` file, and so it won't error out if it doesn't exist.

And then, in the `process_record_user` function, assuming you have `return process_record_keymap(keycode, record)` here,  you'll want to replace the "final" return with the following. Otherwise, you want to replace the `return true;` with `return process_record_secrets(keycode, record);`

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // your existing macro code here. 
    return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
}
```

## rules.mk

Here, you want your `/users/<name>/rules.mk` file to "detect" the existence of the `secrets.c` file, and only add it if the file exists.  

Additionally, to ensure that it's not added or processed in any way, it checks to see if `NO_SECRETS` is set. This way, if you run `make keyboard:name NO_SECRETS=yes`, it will remove the feature altogether. 

```make
ifneq ($(strip $(NO_SECRETS)), yes)
    ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
        SRC += secrets.c
    endif
endif
```

Alternately, if you want to make sure that you can disable the function without messing with the file, you need to add this to your `/users/<name>/rules.mk`, so that it catches the flag:

```make
ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
  SRC += secrets.c
endif

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
```

## Extras

Additionally, because this file isn't present in the repo at all, you could add additional functionality that nobody else will see. 
