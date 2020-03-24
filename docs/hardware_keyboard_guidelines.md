# QMK Keyboard Guidelines

Since starting, QMK has grown by leaps and bounds thanks to people like you who contribute to creating and maintaining our community keyboards. As we've grown we've discovered some patterns that work well, and ask that you conform to them to make it easier for other people to benefit from your hard work.


## Naming Your Keyboard/Project

All keyboard names are in lower case, consisting only of letters, numbers, and underscore (`_`). Names may not begin with an underscore. Forward slash (`/`) is used as a sub-folder separation character.

The names `test`, `keyboard`, and `all` are reserved for make commands and may not be used as a keyboard or subfolder name.

Valid Examples:

* `412_64`
* `chimera_ortho`
* `clueboard/66/rev3`
* `planck`
* `v60_type_r`

## Sub-folders

QMK uses sub-folders both for organization and to share code between revisions of the same keyboard. You can nest folders up to 4 levels deep:

    qmk_firmware/keyboards/top_folder/sub_1/sub_2/sub_3/sub_4

If a sub-folder has a `rules.mk` file it will be considered a compilable keyboard. It will be available in QMK Configurator and tested with `make all`. If you are using a folder to organize several keyboards from the same maker you should not have a `rules.mk` file.

Example:

Clueboard uses sub-folders for both purposes, organization and keyboard revisions.

* [`qmk_firmware`](https://github.com/qmk/qmk_firmware/tree/master)
  * [`keyboards`](https://github.com/qmk/qmk_firmware/tree/master/keyboards)
    * [`clueboard`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard)  &larr; This is the organization folder, there's no `rules.mk` file
      * [`60`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/60)  &larr; This is a compilable keyboard, it has a `rules.mk` file
      * [`66`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66) &larr; This is also compilable- it uses `DEFAULT_FOLDER` to specify `rev3` as the default revision
        * [`rev1`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev1) &larr; compilable: `make clueboard/66/rev1`
        * [`rev2`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev2) &larr; compilable: `make clueboard/66/rev2`
        * [`rev3`](https://github.com/qmk/qmk_firmware/tree/master/keyboards/clueboard/66/rev3) &larr; compilable: `make clueboard/66/rev3` or `make clueboard/66`

## Keyboard Folder Structure

Your keyboard should be located in `qmk_firmware/keyboards/` and the folder name should be your keyboard's name as described in the previous section. Inside this folder should be several files:

* `readme.md`
* `info.json`
* `config.h`
* `rules.mk`
* `<keyboard_name>.c`
* `<keyboard_name>.h`

### `readme.md`

All projects need to have a `readme.md` file that explains what the keyboard is, who made it and where it's available. If applicable, it should also contain links to more information, such as the maker's website. Please follow the [published template](documentation_templates.md#keyboard-readmemd-template).

### `info.json`

This file is used by the [QMK API](https://github.com/qmk/qmk_api). It contains the information [QMK Configurator](https://config.qmk.fm/) needs to display a representation of your keyboard. You can also set metadata here. For more information see the [reference page](reference_info_json.md).

### `config.h`

All projects need to have a `config.h` file that sets things like the matrix size, product name, USB VID/PID, description and other settings. In general, use this file to set essential information and defaults for your keyboard that will always work.

The `config.h` files can also be placed in sub-folders, and the order in which they are read is as follows

* `keyboards/top_folder/config.h`
  * `keyboards/top_folder/sub_1/config.h`
    * `keyboards/top_folder/sub_1/sub_2/config.h`
      * `keyboards/top_folder/sub_1/sub_2/sub_3/config.h`
        * `keyboards/top_folder/sub_1/sub_2/sub_3/sub_4/config.h`
          * `users/a_user_folder/config.h`
          * `keyboards/top_folder/keymaps/a_keymap/config.h`
        * `keyboards/top_folder/sub_1/sub_2/sub_3/sub_4/post_config.h`
      * `keyboards/top_folder/sub_1/sub_2/sub_3/post_config.h`
    * `keyboards/top_folder/sub_1/sub_2/post_config.h`
  * `keyboards/top_folder/sub_1/post_config.h`
* `keyboards/top_folder/post_config.h`

The `post_config.h` file is for additional post-processing depending on what is specified in the `config.h` file.

For example, if you define the `IOS_DEVICE_ENABLE` macro in the `keymaps/a_keymap/config.h` file as follows, you can configure the detailed settings accordingly in the `post_config.h` file.

* `keyboards/top_folder/keymaps/a_keymap/config.h`
  ```c
  #define IOS_DEVICE_ENABLE
  ```
* `keyboards/top_folder/post_config.h`
  ```c
  #ifndef IOS_DEVICE_ENABLE
    // USB_MAX_POWER_CONSUMPTION value for this keyboard
    #define USB_MAX_POWER_CONSUMPTION 400
  #else
    // fix iPhone and iPad power adapter issue
    // iOS device need lessthan 100
    #define USB_MAX_POWER_CONSUMPTION 100
  #endif
  
  #ifdef RGBLIGHT_ENABLE
    #ifndef IOS_DEVICE_ENABLE
      #define RGBLIGHT_LIMIT_VAL 200
      #define RGBLIGHT_VAL_STEP 17
    #else
      #define RGBLIGHT_LIMIT_VAL 35
      #define RGBLIGHT_VAL_STEP 4
    #endif
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
  #endif
  ```

### `rules.mk`

The presence of this file means that the folder is a keyboard target and can be used in `make` commands. This is where you setup the build environment for your keyboard and configure the default set of features.

### `<keyboard_name.c>`

This is where you will write custom code for your keyboard. Typically you will write code to initialize and interface with the hardware in your keyboard. If your keyboard consists of only a key matrix with no LEDs, speakers, or other auxiliary hardware this file can be blank.

The following functions are typically defined in this file:

* `void matrix_init_kb(void)`
* `void matrix_scan_kb(void)`
* `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
* `void led_set_kb(uint8_t usb_led)`

### `<keyboard_name.h>`

This file is used to define the matrix for your keyboard. You should define at least one C macro which translates an array into a matrix representing the physical switch matrix for your keyboard. If it's possible to build your keyboard with multiple layouts you should define additional macros.

If you have only a single layout you should call this macro `LAYOUT`.

When defining multiple layouts you should have a base layout, named `LAYOUT_all`, that supports all possible switch positions on your matrix, even if that layout is impossible to build physically. This is the macro you should use in your `default` keymap. You should then have additional keymaps named `default_<layout>` that use your other layout macros. This will make it easier for people to use the layouts you define.

Layout macro names are entirely lowercase, except for the word `LAYOUT` at the front.

As an example, if you have a 60% PCB that supports ANSI and ISO you might define the following layouts and keymaps:

| Layout Name | Keymap Name | Description |
|-------------|-------------|-------------|
| LAYOUT_all | default | A layout that supports both ISO and ANSI |
| LAYOUT_ansi | default_ansi | An ANSI layout |
| LAYOUT_iso | default_iso | An ISO layout |

## Image/Hardware Files

In an effort to keep the repo size down we're no longer accepting binary files of any format, with few exceptions. Hosting them elsewhere (such as <https://imgur.com>) and linking them in the `readme.md` is preferred.

Hardware files (such as plates, cases, pcb) can be contributed to the [qmk.fm repo](https://github.com/qmk/qmk.fm) and they will be made available on [qmk.fm](http://qmk.fm). Downloadable files are stored in `/<keyboard>/` (name follows the same format as above) which are served at `http://qmk.fm/<keyboard>/`, and pages are generated from `/_pages/<keyboard>/` which are served at the same location (.md files are generated into .html files through Jekyll). Check out the `lets_split` folder for an example.

## Keyboard Defaults

Given the amount of functionality that QMK exposes it's very easy to confuse new users. When putting together the default firmware for your keyboard we recommend limiting your enabled features and options to the minimal set needed to support your hardware. Recommendations for specific features follow.

### Bootmagic and Command

[Bootmagic](feature_bootmagic.md) and [Command](feature_command.md) are two related features that allow a user to control their keyboard in non-obvious ways. We recommend you think long and hard about if you're going to enable either feature, and how you will expose this functionality. Keep in mind that users who want this functionality can enable it in their personal keymaps without affecting all the novice users who may be using your keyboard as their first programmable board.

By far the most common problem new users encounter is accidentally triggering Bootmagic while they're plugging in their keyboard. They're holding the keyboard by the bottom, unknowingly pressing in alt and spacebar, and then they find that these keys have been swapped on them. We recommend leaving this feature disabled by default, but if you do turn it on consider setting `BOOTMAGIC_KEY_SALT` to a key that is hard to press while plugging your keyboard in.

If your keyboard does not have 2 shift keys you should provide a working default for `IS_COMMAND`, even when you have set `COMMAND_ENABLE = no`. This will give your users a default to conform to if they do enable Command.

## Custom Keyboard Programming

As documented on [Customizing Functionality](custom_quantum_functions.md) you can define custom functions for your keyboard. Please keep in mind that your users may want to customize that behavior as well, and make it possible for them to do that. If you are providing a custom function, for example `process_record_kb()`, make sure that your function calls the `_user()` version of the call too. You should also take into account the return value of the `_user()` version, and only run your custom code if the user returns `true`.

## Non-Production/Handwired Projects

We're happy to accept any project that uses QMK, including prototypes and handwired ones, but we have a separate `/keyboards/handwired/` folder for them, so the main `/keyboards/` folder doesn't get overcrowded. If a prototype project becomes a production project at some point in the future, we'd be happy to move it to the main `/keyboards/` folder!

## Warnings as Errors

When developing your keyboard, keep in mind that all warnings will be treated as errors - these small warnings can build-up and cause larger errors down the road (and keeping them is generally a bad practice).

## Copyright Blurb

If you're adapting your keyboard's setup from another project, but not using the same code, but sure to update the copyright header at the top of the files to show your name, in this format:

    Copyright 2017 Your Name <your@email.com>

If you are modifying someone else's code and have made only trivial changes you should leave their name in the copyright statement. If you have done significant work on the file you should add your name to theirs, like so:

    Copyright 2017 Their Name <original_author@example.com> Your Name <you@example.com>

The year should be the first year the file is created. If work was done to that file in later years you can reflect that by appending the second year to the first, like so:

    Copyright 2015-2017 Your Name <you@example.com>

## License

The core of QMK is licensed under the [GNU General Public License](https://www.gnu.org/licenses/licenses.en.html). If you are shipping binaries for AVR processors you may choose either [GPLv2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html) or [GPLv3](https://www.gnu.org/licenses/gpl.html). If you are shipping binaries for ARM processors you must choose [GPL Version 3](https://www.gnu.org/licenses/gpl.html) to comply with the [ChibiOS](http://www.chibios.org) GPLv3 license.

If your keyboard makes use of the [uGFX](https://ugfx.io) features within QMK you must comply with the [uGFX License](https://ugfx.io/license.html), which requires a separate commercial license before selling a device containing uGFX.

## Technical Details

If you're looking for more information on making your keyboard work with QMK, [check out the hardware section](hardware.md)!
