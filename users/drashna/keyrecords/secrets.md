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
