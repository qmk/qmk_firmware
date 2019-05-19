# Userspace: Sharing Code Between Keymaps

If you use more than one keyboard with a similar keymap, you might see the benefit in being able to share code between them. Create your own folder in `users/` named the same as your keymap (ideally your github username, `<name>`) with the following structure:

* `/users/<name>/` (added to the path automatically)
  * `readme.md` (optional, recommended)
  * `rules.mk` (included automatically)
  * `config.h` (included automatically)
  * `<name>.h` (optional)
  * `<name>.c` (optional)
  * `cool_rgb_stuff.c` (optional)
  * `cool_rgb_stuff.h` (optional)


All this only happens when you build a keymap named `<name>`, like this:

    make planck:<name>

For example,

    make planck:jack

Will include the `/users/jack/` folder in the path, along with `/users/jack/rules.mk`.  

!> This `name` can be [overridden](#override-default-userspace), if needed.  

## `Rules.mk`

The `rules.mk` is one of the two files that gets processed automatically.  This is how you add additional source files (such as  `<name>.c`) will be added when compiling.

It's highly recommended that you use `<name>.c` as the default source file to be added. And to add it, you need to add it the SRC in `rules.mk` like this:

    SRC += <name>.c

Additional files may be added in the same way - it's recommended you have one named `<name>`.c/.h to start off with, though. 

The `/users/<name>/rules.mk` file will be included in the build _after_ the `rules.mk` from your keymap. This allows you to have features in your userspace `rules.mk` that depend on individual QMK features that may or may not be available on a specific keyboard. 

For example, if you have RGB control features shared between all your keyboards that support RGB lighting, you can add support for that if the RGBLIGHT feature is enabled:
```make
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  # Include my fancy rgb functions source here
  SRC += cool_rgb_stuff.c
endif
```

Alternatively, you can `define RGB_ENABLE` in your keymap's `rules.mk` and then check for the variable in your userspace's `rules.mk` like this:
```make
ifdef RGB_ENABLE
  # Include my fancy rgb functions source here
  SRC += cool_rgb_stuff.c
endif
```

### Override default userspace

By default the userspace used will be the same as the keymap name. In some situations this isn't desirable. For instance, if you use the [layout](feature_layouts.md) feature you can't use the same name for different keymaps (e.g. ANSI and ISO). You can name your layouts `mylayout-ansi` and `mylayout-iso` and add the following line to your layout's `rules.mk`:

```
USER_NAME := mylayout
```

This is also useful if you have multiple different keyboards with different features physically present on the board (such as one with RGB Lights, and one with Audio, or different number of LEDs, or connected to a different PIN on the controller).

## Configuration Options (`config.h`)

Additionally, `config.h` here will be processed like the same file in your keymap folder.  This is handled separately from the `<name>.h` file.

The reason for this, is that `<name>.h` won't be added in time to add settings (such as `#define TAPPING_TERM 100`), and including the `<name.h>` file in any `config.h` files will result in compile issues.

!>You should use the `config.h` for [configuration options](config_options.md), and the `<name>.h` file for user or keymap specific settings (such as the enum for layer or keycodes)


## Readme (`readme.md`)

Please include authorship (your name, github username, email), and optionally [a license that's GPL compatible](https://www.gnu.org/licenses/license-list.html#GPLCompatibleLicenses).

You can use this as a template: 
```
Copyright <year> <name> <email> @<github_username>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```

You'd want to replace the year, name, email and github username with your info. 

Additionally, this is a good place to document your code, if you wish to share it with others. 

# Examples

For a brief example, checkout [`/users/_example/`](https://github.com/qmk/qmk_firmware/tree/master/users/drashna).  
For a more complicated example, checkout [`/users/drashna/`](https://github.com/qmk/qmk_firmware/tree/master/users/drashna)'s userspace.


## Customized Functions

QMK has a bunch of [functions](custom_quantum_functions.md) that have [`_quantum`, `_kb`, and `_user` versions](custom_quantum_functions.md#a-word-on-core-vs-keyboards-vs-keymap) that you can use.  You will pretty much always want to use the user version of these functions.  But the problem is that if you use them in your userspace, then you don't have a version that you can use in your keymap. 

However, you can actually add support for keymap version, so that you can use it in both your userspace and your keymap! 


For instance, let's look at the `layer_state_set_user()` function.  You can enable the [Tri Layer State](ref_functions.md#olkb-tri-layers) functionality on all of your boards, while also retaining the Tri Layer functionality in your `keymap.c` files. 

In your `<name.c>` file, you'd want to add this: 
```c
__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

uint32_t layer_state_set_user (uint32_t state) {
  state = update_tri_layer_state(state, 2, 3, 5);
  return layer_state_set_keymap (state);
}
```
The `__attribute__ ((weak))` part tells the compiler that this is a placeholder function that can then be replaced by a version in your `keymap.c`.  That way, you don't need to add it to your `keymap.c`, but if you do, you won't get any conflicts because the function is the same name. 

The `_keymap` part here doesn't matter, it just needs to be something other than `_quantum`, `_kb`, or `_user`, since those are already in use. So you could use `layer_state_set_mine`, `layer_state_set_fn`, or anything else.

You can see a list of this and other common functions in [`template.c`](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/template.c) in [`users/drashna`](https://github.com/qmk/qmk_firmware/tree/master/users/drashna).

## Custom Features

Since the Userspace feature can support a staggering number of boards, you may have boards that you want to enable certain functionality for, but not for others. And you can actually create "features" that you can enable or disable in your own userspace.  

For instance, if you wanted to have a bunch of macros available, but only on certain boards (to save space), you could "hide" them being a `#ifdef MACROS_ENABLED`, and then enable it per board.  To do this, add this to your rules.mk
```make
ifeq ($(strip $(MACROS_ENABLED)), yes)
    OPT_DEFS += -DMACROS_ENABLED
endif
```
The `OPT_DEFS` setting causes `MACROS_ENABLED` to be defined for your keyboards (note the `-D` in front of the name), and you could use `#ifdef MACROS_ENABLED` to check the status in your c/h files, and handle that code based on that. 

Then you add `MACROS_ENABLED = yes` to the `rules.mk` for you keymap to enable this feature and the code in your userspace.

And in your `process_record_user` function, you'd do something like this: 
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
#ifdef MACROS_ENABLED
  case MACRO1:
    if (!record->event.pressed) {
      SEND_STRING("This is macro 1!");
    }
    break;
  case MACRO2:
    if (!record->event.pressed) {
      SEND_STRING("This is macro 2!");
    }
    break;
#endif
  }
  return true;
}
```


## Consolidated Macros

If you wanted to consolidate macros and other functions into your userspace for all of your keymaps, you can do that.  This builds upon the [Customized Functions](#customized-functions) example above. This lets you maintain a bunch of macros that are shared between the different keyboards, and allow for keyboard specific macros, too. 

First, you'd want to go through all of your `keymap.c` files and replace `process_record_user` with `process_record_keymap` instead.   This way, you can still use keyboard specific codes on those boards, and use your custom "global" keycodes as well.   You'll also want to replace `SAFE_RANGE` with `NEW_SAFE_RANGE` so that you wont have any overlapping keycodes

Then add `#include <name.h>` to all of your keymap.c files.  This allows you to use these new keycodes without having to redefine them in each keymap.

Once you've done that, you'll want to set the keycode definitions that you need to the `<name>.h`  file. For instance:
```c
#pragma once

#include "quantum.h"
#include "action.h"
#include "version.h"

// Define all of
enum custom_keycodes {
  KC_MAKE = SAFE_RANGE,
  NEW_SAFE_RANGE  //use "NEW_SAFE_RANGE" for keymap specific codes
};
```

Now you want to create the `<name>.c` file, and add this content to it:

```c
#include "<name>.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            uint8_t temp_osm = get_oneshot_mods();
            clear_mods(); clear_oneshot_mods();
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    #ifndef FLASH_BOOTLOADER
            if ( (temp_mod | temp_osm) & MOD_MASK_SHIFT ) 
    #endif
            { // 
                #if defined(__arm__)  // only run for ARM boards
                    SEND_STRING(":dfu-util");
                #elif defined(BOOTLOADER_DFU) // only run for DFU boards
                    SEND_STRING(":dfu");
                #elif defined(BOOTLOADER_HALFKAY) // only run for teensy boards
                    SEND_STRING(":teensy");
                #elif defined(BOOTLOADER_CATERINA) // only run for Pro Micros
                    SEND_STRING(":avrdude");
                #endif // bootloader options
            }
            if ( (temp_mod | temp_osm) & MOD_MASK_CTRL) { 
                SEND_STRING(" -j8 --output-sync"); 
            }
            SEND_STRING(SS_TAP(X_ENTER));
            set_mods(temp_mod);
        }
        break;

  }
  return process_record_keymap(keycode, record);
}
```

For boards that may not have a shift button (such as on a macro pad), we need a way to always include the bootloader option.  To do that, add the following to the `rules.mk` in your userspace folder: 

```make 
ifeq ($(strip $(FLASH_BOOTLOADER)), yes)
    OPT_DEFS += -DFLASH_BOOTLOADER
endif
```

This will add a new `KC_MAKE` keycode that can be used in any of your keymaps.  And this keycode will output `make <keyboard>:<keymap>`, making frequent compiling easier.  And this will work with any keyboard and any keymap as it will output the current boards info, so that you don't have to type this out every time.

Also, holding `shift` will add the appropriate flashing command (`:dfu`, `:teensy`, `:avrdude`, `:dfu-util`) for a majority of keyboards.  Holding `control` will add some commands that will speed up compiling time by processing multiple files at once. 

And for the boards that lack a shift key, or that you want to always attempt the flashing part, you can add `FLASH_BOOTLOADER = yes` to the `rules.mk` of that keymap.

?> This should flash the newly compiled firmware automatically, using the correct utility, based on the bootloader settings (or default to just generating the HEX file). However, it should be noted that this may not work on all systems. AVRDUDE doesn't work on WSL, namely. And this doesn't support BootloadHID or mdloader. 
