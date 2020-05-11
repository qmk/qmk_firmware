## Core Changes

### Converting V-USB usbdrv to a submodule

[#8321](https://github.com/qmk/qmk_firmware/pull/8321) and [qmk_compiler#62](https://github.com/qmk/qmk_compiler/pull/62).

These PRs move the V-USB driver code out of the qmk_firmware repository and into a submodule pointed at https://github.com/obdev/v-usb. This will make it easier to update the codebase if needed, while applying any potential QMK-specific modifications by forking it to the QMK GitHub organization.

### Unify Tap Hold functions and documentation

[#8348](https://github.com/qmk/qmk_firmware/pull/8348)

Updates all of the per key tap-hold functions to pass the `keyrecord_t` structure, and include documentation changes.

Any remaining versions or code outside of the main repo will need to be converted: 
| Old function                                         | New Function                                                              |
|------------------------------------------------------|---------------------------------------------------------------------------|
|`uint16_t get_tapping_term(uint16_t keycode)`         |`uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)`         |
|`bool get_ignore_mod_tap_interrupt(uint16_t keycode)` |`bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record)` |

### Python Required In The Build Process

[#9000](https://github.com/qmk/qmk_firmware/pull/9000)

This is the last release of QMK that will work without having Python 3.6 (or later) installed. If your environment is not fully setup you will get a warning instructing you to set it up.

After the next breaking change you will not be able to build if `bin/qmk hello` does not work.

### [#8269]

### Fixed RGB_DISABLE_AFTER_TIMEOUT to be seconds based & small internals cleanup

[#6480](https://github.com/qmk/qmk_firmware/pull/6480)

- Changes `RGB_DISABLE_AFTER_TIMEOUT` to be based on milliseconds instead of ticks.
- Includes a code cleanup, resulting in a savings of 100 bytes, depending on features used.
- Fixed issues with timeouts / suspending at the wrong time not turning off all LEDs in some cases.

The `RGB_DISABLE_AFTER_TIMEOUT` definition is now deprecated, and has been superseded by `RGB_DISABLE_TIMEOUT`. To use the new definition, rename `RGB_DISABLE_AFTER_TIMEOUT` to `RGB_DISABLE_TIMEOUT` in your `config.h` file, and multiply the value set by 1200.

Before: `#define RGB_DISABLE_AFTER_TIMEOUT 100`  
After: `#define RGB_DISABLE_TIMEOUT 120000`

### Switch to qmk forks for everything

[#9019](https://github.com/qmk/qmk_firmware/pull/9019)

Fork all QMK submodules to protect against upstream repositories disappearing.

### code cleanup regarding deprecated macro PLAY_NOTE_ARRAY by replacing it with PLAY_SONG

[#8484](https://github.com/qmk/qmk_firmware/pull/8484)

### fixing wrong configuration of AUDIO feature

[#8903](https://github.com/qmk/qmk_firmware/pull/8903)

`audio_avr.c` does not default to any pin; there has to be a #define XX_AUDIO in config.h at some level for Audio to actually work. Otherwise, the Audio code ends up cluttering the firmware, possibly breaking builds because the maximum allowed firmware size is exceeded.

These changes fix this by disabling Audio on keyboards that have the feature misconfigured, and therefore non-functional.
