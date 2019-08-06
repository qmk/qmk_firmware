# qmk userspace for kuchosauronad0
Thanks to drashna and everyone else in the qmk_firmware/users/ directory :)

# Overview

## Keyboard Layout Templates
This borrows from @jola5's "Not quite neo" code. This allows me to maintain blocks of keymaps in the userspace, so that I can modify the userspace, and this is reflected in all of the keyboards that use it, at once.

This makes adding tap/hold mods, or other special keycodes or functions to all keyboards super easy, as it's done to all of them at once.

The caveat here is that the keymap needs a processor/wrapper, as it doesn't like the substitutions. However, this is as simple as just pushing it through a define. For instance:

`#define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)`

Once that's been done and you've switched the keymaps to use the "wrapper", it will read the substitution blocks just fine.

Credit goes to @jola5 for first implementing this awesome idea.

## Custom Keycodes
Declared in `process_records.h` and `template.h` and defined in `process_record_user` in template.c 

## Tap Dances
Set `TAP_DANCE_ENABLE = yes` in rules.mk. See file tap_dances.{c,h}

## Leader Key
Set `LEADER_ENABLE = yes` in rules.mk.
TODO: document tmux / vim / os

## Unicode
TODO: Set `idk` in `idc`

## Diablo Layer
Currently not in use.

# Secret Macros
Set `NO_SECRETS = yes` in rules.mk.

With help from gitter and Colinta, this adds the ability to add hidden macros from other users.  

First, I have several files that are hidden/excluded from Git/GitHub.  These contain everything needed for the macros. To hide these files, open `.git/info/exclude` and add `secrets.c` and  `secrets.h` to that file, below the comments.

And this requires `KC_SECRET_1` through `KC_SECRET_5` to be defined in your `<name>.h` file to define the keycodes for the new macros. 


### .git/info/exclude

```
# git ls-files --others --exclude-from=.git/info/exclude
# Lines that start with '#' are comments.
# For a project mostly in C, the following would be a good set of
# exclude patterns (uncomment them if you want to use them):
# *.[oa]
# *~
/users/kuchosauronad0/secrets.c
/users/kuchosauronad0/secrets.h
```

Then you can create these files:

### secrets.c

```c
#include "kuchosauronad0.h"  // replace with your keymap's "h" file, or whatever file stores the keycodes

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

In the `<name>.c` file, you will want to add this to the top:

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

Here, you want your `/users/<name>/rules.mk` file to "detect" the existence of the `secrets.c` file, and only add it if the file exists.  To do so, add this block:

```make
ifneq ("$(wildcard $(USER_PATH)/secrets.c)","")
  SRC += secrets.c
endif
```

Additionally, if you want to make sure that you can disable the function without messing with the file, you need to add this to your `/users/<name>/rules.mk`, so that it catches the flag:

```make
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
```

Then, if you run `make keyboard:name NO_SECRETS=yes`, it will default to the test strings in your `<name>.c` file, rather than reading from your file.
