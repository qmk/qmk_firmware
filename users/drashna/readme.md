Overview
========

This is my personal userspace file.  Most of my code exists here, as it's heavily shared. 

Userspace Config.h
------------------

By default, the userspace feature doesn't include a `config.h` file the way that that keyboards, revisions, keymaps and layouts handle them.  This means that if you want global configurations via userspace, it's very difficult to implement.  

The reason for using seperate files here is that the `drashna.h` file doesn't get called in such a way that will actually define QMK settings.  Additionally, attempting to add it to the `config.h` files has issues. Namely, the `drashna.h` file requires the `quantum.h` file... but including this to the `config.h` attemps to redefines a bunch of settings and breaks the firmare.  Removing the `quantum.h` include means that a number of data structures no longer get added, and the `SAFE_RANGE` value is no longer defined, as well.  So we need both a `config.h` for global config, and we need a seperate h file for local settings. 

However, the `rules.mk` file is included when building the firmware.  So we can hijack that process to "manually" add a `config.h`. To do so, you would need to add the following to the `rules.mk` in your userspace:

```
ifneq ("$(wildcard users/$(KEYMAP)/config.h)","")
    CONFIG_H += users/$(KEYMAP)/config.h
endif
```

You can replace `$(KEYMAP)` with your name, but it's not necessary. This checks for the existence of `/users/<name>/config.h`, and if it exists, includes it like every other `config.h` file, allowing you to make global `config.h` settings. 

As for the `config.h` file, you want to make sure that it has an "ifdef" in it to make sure it's only used once.  So you want something like this: 

```
#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H

// put stuff here 

#endif
```

Custom userspace handlers
-------------------------

Specifically QMK works by using customized handlers for everything. This allows for multiple levels of customization.

`matrix_scan` calls `matrix_scan_quantum`, which alls `matrix_scan_kb`, which calls `matrix_scan_user`. 
`process_record` calls a bunch of stuff, but eventually calls `process_record_kb` which calls `process_record_user`
The same goes for `matrix_init`, `layer_state_set`, `led_set`, and a few other functions.  

All (most) `_user` functions are handled here instead.  To allow keyboard specific configuration, I've created `_keymap` functions that can be called by the keymap.c files instead.

This allows for keyboard specific configuration while maintaining the ability to customize the board. 

My [Ergodox EZ Keymap](https://github.com/qmk/qmk_firmware/blob/master/keyboards/ergodox_ez/keymaps/drashna/keymap.c#L399) is a good example of this, as it uses the LEDs as modifier indicators.


Keyboard Layout Templates
-------------------------

This borrows from @jola5's "Not quite neo" code.  This allows me to maintain blocks of keymaps in the userspace, so that I can modify the userspace, and this is reflected in all of the keyboards that use it, at once. 

This makes adding tap/hold mods, or other special keycodes or functions to all keyboards super easy, as it's done to all of them at once. 

The caveat here is that the keymap needs a processor/wrapper, as it doesn't like the substitutions.  However, this is as simple as just pushing it through a define. For instance: 

`#define LAYOUT_ergodox_wrapper(...)   LAYOUT_ergodox(__VA_ARGS__)`

Once that's been done and you've switched the keymaps to use the "wrapper", it will read the substitution blocks just fine. 

Credit goes to @jola5 for first implementing this awesome idea.


Custom Keycodes
---------------

Keycodes are defined in the drashna.h file and need to be included in the keymap.c files, so that they can be used there. 

A bunch of macros are present and are only included on boards that are not the Ergodox EZ or Orthodox, as they are not needed for those boards. 

Included is a custom macro for compiling my keyboards.  This includes the bootloader target (`:teensy`, `:avrdude`, or `:dfu`), and keeps RGBLIGHT, AUDIO and/or FAUXCLICKY enabled, if it previously was (regardless of the rules file).

This also includes a modified RESET keycode as well, that sets the underglow to red. 

Layer Indication
----------------

This uses the `layer_state_set_*` command to change the layer color, to indicate which layer it is on.  This includes the default keymap, as well.

Since this is done via userspace, it is the same between all systems. 

Additionally, there is a custom keycode to toggle layer indication. And all RGB keycodes disable layer indication by default, as well.  This way, I can leave special effects doing when I want.

Also. I use `rgblight_sethsv` since it works with animation modes (that support it).


Diablo Layer
------------

This layer has some special handling.

When Tap Dances are enabled, this layer has the ability to "spam" keypresses.  

For instance, tapping the TD "1" twice causes the layer to hit "1" ever 1 second (appoximately).  This is useful for auto-hotkeying skills (such as bone armor or devour).

Tappind once disables this, and switching layers temporarily disables this, until you switch back to the layer. 

For critics that think this is cheating, search "diablo 3 num lock auto cast".  This is just a simpler method, since I no longer own a normal (non QMK) numpad. 

Secret Macros
-------------

With help from gitter and Colinta, this adds the ability to add hidden strings to be used for macros.

I have a number of long strings that I need to use that are semi-private.  This uses the `__has_include` function to check for the file. If it exists, then it includes the custom text. Otherwise, it uses some default values. 

If you would *also* like to take advantage of this feature, you'll first want to make sure your "secrets" file isn't included in the repo.  Open `.git/info/exclude` and add `secrets.h` to that file, below the comments.

###### .git/info/exclude
```
# git ls-files --others --exclude-from=.git/info/exclude
# Lines that start with '#' are comments.
# For a project mostly in C, the following would be a good set of
# exclude patterns (uncomment them if you want to use them):
# *.[oa]
# *~
/users/drashna/secrets.h
```

Then you can create this file and add your macro strings to it:

###### secrets.h
```
PROGMEM const char secret[][64] = {
  "secret1",
  "secret2",
  "secret3",
  "secret4",
  "secret5"
};
```

Replacing the strings with the codes that you need. 


These are called in the `process_record_user` function, using this block:
```
  case KC_SECRET_1 ... KC_SECRET_5:
    if (!record->event.pressed) {
      send_string_P(secret[keycode - KC_SECRET_1]);
    }
    return false;
    break;
```

And this requires `KC_SECRET_1` through `KC_SECRET_5` to be defined, as well. 
