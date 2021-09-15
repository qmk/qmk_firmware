# PR checklists

This is a non-exhaustive checklist of what the QMK Collaborators will be checking when reviewing submitted PRs.

If there are any inconsistencies with these recommendations, you're best off [creating an issue](https://github.com/qmk/qmk_firmware/issues/new) against this document, or getting in touch with a QMK Collaborator on [Discord](https://discord.gg/Uq7gcHh).

## General PRs

- PR should be submitted using a non-`master` branch on the source repository
    - this does not mean you target a different branch for your PR, rather that you're not working out of your own master branch
    - if submitter _does_ use their own `master` branch, they'll be given a link to the ["how to git"](https://docs.qmk.fm/#/newbs_git_using_your_master_branch) page after merging -- (end of this document will contain the contents of the message)
- newly-added directories and filenames must be lowercase
    - this rule may be relaxed if upstream sources originally had uppercase characters (e.g. ChibiOS, or imported files from other repositories etc.)
    - if there is enough justification (i.e. consistency with existing core files etc.) this can be relaxed
        - a board designer naming their keyboard with uppercase letters is not enough justification
- valid license headers on all `*.c` and `*.h` source files
    - GPL2/GPL3 recommended for consistency
    - other licenses are permitted, however they must be GPL-compatible and must allow for redistribution. Using a different license will almost certainly delay a PR getting merged.
- QMK Codebase "best practices" followed
    - this is not an exhaustive list, and will likely get amended as time goes by
    - `#pragma once` instead of `#ifndef` include guards in header files
    - no "old-school" GPIO/I2C/SPI functions used -- must use QMK abstractions unless justifiable (and laziness is not valid justification)
    - timing abstractions should be followed too:
        - `wait_ms()` instead of `_delay_ms()` (remove `#include <util/delay.h>` too)
        - `timer_read()` and `timer_read32()` etc. -- see [timer.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/timer.h) for the timing APIs
    - if you think a new abstraction is useful, you're encouraged to:
        - prototype it in your own keyboard until it's feature-complete
        - discuss it with QMK Collaborators on Discord
        - refactor it as a separate core change
        - remove your specific copy in your board
- rebase and fix all merge conflicts before opening the PR (in case you need help or advice, reach out to QMK Collaborators on Discord)

## Keymap PRs

- `#include QMK_KEYBOARD_H` preferred to including specific board files
- prefer layer `enum`s to `#define`s
- require custom keycode `enum`s to `#define`s, first entry must have ` = SAFE_RANGE`
- terminating backslash (`\`) in lines of LAYOUT macro parameters is superfluous
- some care with spacing (e.g., alignment on commas or first char of keycodes) makes for a much nicer-looking keymap

## Keyboard PRs

Closed PRs (for inspiration, previous sets of review comments will help you eliminate ping-pong of your own reviews):
https://github.com/qmk/qmk_firmware/pulls?q=is%3Apr+is%3Aclosed+label%3Akeyboard

- `info.json`
    - valid URL
    - valid maintainer
    - displays correctly in Configurator (press Ctrl+Shift+I to preview local file, turn on fast input to verify ordering)
- `readme.md`
    - standard template should be present
    - flash command has `:flash` at end
    - valid hardware availability link (unless handwired) -- private groupbuys are okay, but one-off prototypes will be questioned. If open-source, a link to files should be provided.
    - clear instructions on how to reset the board into bootloader mode
    - a picture about the keyboard and preferably about the PCB, too
- `rules.mk`
    - removed `MIDI_ENABLE`, `FAUXCLICKY_ENABLE` and `HD44780_ENABLE`
    - modified `# Enable Bluetooth with the Adafruit EZ-Key HID` -> `# Enable Bluetooth`
    - no `(-/+size)` comments related to enabling features
    - remove the list of alternate bootloaders if one has been specified
    - no re-definitions of the default MCU parameters if same value, when compared to the equivalent MCU in [mcu_selection.mk](https://github.com/qmk/qmk_firmware/blob/master/quantum/mcu_selection.mk)
- keyboard `config.h`
    - don't repeat `MANUFACTURER` in the `PRODUCT` value
    - no `#define DESCRIPTION`
    - no Magic Key Options, MIDI Options or HD44780 configuration
    - user preference configurable `#define`s need to be moved to keymap `config.h`
    - "`DEBOUNCE`" instead of "`DEBOUNCING_DELAY`"
    - bare minimum required code for a board to boot into QMK should be present
        - initialisation code for the matrix and critical devices
        - mirroring existing functionality of a commercial board (like custom keycodes and special animations etc.) should be handled through non-`default` keymaps
    - Vial-related files or changes will not be accepted, as they are not used by QMK firmware (no Vial-specific core code has been submitted or merged)
- `keyboard.c`
    - empty `xxxx_xxxx_kb()` or other weak-defined default implemented functions removed
    - commented-out functions removed too
    - `matrix_init_board()` etc. migrated to `keyboard_pre_init_kb()`, see: [keyboard_pre_init*](https://docs.qmk.fm/#/custom_quantum_functions?id=keyboard_pre_init_-function-documentation)
    - prefer `CUSTOM_MATRIX = lite` if custom matrix used, allows for standard debounce, see [custom matrix 'lite'](https://docs.qmk.fm/#/custom_matrix?id=lite)
    - prefer LED indicator [Configuration Options](https://docs.qmk.fm/#/feature_led_indicators?id=configuration-options) to custom `led_update_*()` implementations where possible
- `keyboard.h`
    - `#include "quantum.h"` appears at the top
    - `LAYOUT` macros should use standard definitions if applicable
        - use the Community Layout macro names where they apply (preferred above `LAYOUT`/`LAYOUT_all`)
- keymap `config.h`
    - no duplication of `rules.mk` or `config.h` from keyboard
- `keymaps/default/keymap.c`
    - `QMKBEST`/`QMKURL` removed (sheesh)
    - if using `MO(_LOWER)` and `MO(_RAISE)` keycodes or equivalent, and the keymap has an adjust layer when holding both keys -- if the keymap has no "direct-to-adjust" keycode (such as `MO(_ADJUST)`) then you should prefer to write...
        ```
        layer_state_t layer_state_set_user(layer_state_t state) {
          return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
        }
        ```
        ...instead of manually handling `layer_on()`, `update_tri_layer()` inside the keymap's `process_record_user()`.
- default (and via) keymaps should be "pristine"
    - bare minimum to be used as a "clean slate" for another user to develop their own user-specific keymap
    - standard layouts preferred in these keymaps, if possible
    - default keymap should not enable VIA -- the VIA integration documentation requires a keymap called `via`
- submitters can have a personal (or bells-and-whistles) keymap showcasing capabilities in the same PR but it shouldn't be embedded in the 'default' keymap
- submitters can also have a "manufacturer-matching" keymap that mirrors existing functionality of the commercial product, if porting an existing board
- Do not include VIA json files in the PR. These do not belong in the QMK repository as they are not used by QMK firmware -- they belong in the [VIA Keyboard Repo](https://github.com/the-via/keyboards)


Also, specific to ChibiOS:
- **strong** preference to using existing ChibiOS board definitions.
    - a lot of the time, an equivalent Nucleo board can be used with a different flash size or slightly different model in the same family
        - example: For an STM32L082KZ, given the similarity to an STM32L073RZ, you can use `BOARD = ST_NUCLEO64_L073RZ` in rules.mk
    - QMK is migrating to not having custom board definitions if at all possible, due to the ongoing maintenance burden when upgrading ChibiOS
- if a board definition is unavoidable, `board.c` must have a standard `__early_init()` (as per normal ChibiOS board defs) and an empty `boardInit()`:
    - see Arm/ChibiOS [early initialization](https://docs.qmk.fm/#/platformdev_chibios_earlyinit?id=board-init)
    - `__early_init()` should be replaced by either `early_hardware_init_pre()` or `early_hardware_init_post()` as appropriate
    - `boardInit()` should be migrated to `board_init()`

## Core PRs

- must now target `develop` branch, which will subsequently be merged back to `master` on the breaking changes timeline
- other notes TBD
    - core is a lot more subjective given the breadth of posted changes

---

## Notes

For when people use their own `master` branch, post this after merge:
```
For future reference, we recommend against committing to your `master` branch as you've done here, because pull requests from modified `master` branches can make it more difficult to keep your QMK fork updated. It is highly recommended for QMK development – regardless of what is being done or where – to keep your master updated, but **NEVER** commit to it. Instead, do all your changes in a branch (branches are basically free in Git) and issue PRs from your branches when you're developing.

There are instructions on how to keep your fork updated here:

[**Best Practices: Your Fork's Master: Update Often, Commit Never**](https://docs.qmk.fm/#/newbs_git_using_your_master_branch)

[Fixing Your Branch](https://docs.qmk.fm/#/newbs_git_resynchronize_a_branch) will walk you through fixing up your `master` branch moving forward. If you need any help with this just ask.

Thanks for contributing!
```

## Review Process

In general, we want to see two (or more) approvals that are meaningful (e.g. that have inspected code) before a PR will be considered for merge. These reviews are not limited to collaborators -- any community member willing to put in the time is welcomed (and encouraged). The only difference is that your checkmark won't be green, and that's fine! 

Additionally, PR reviews are something that is done in our free time. We are not paid nor compensated for the time we spend reviewing, as it is a labor of love. As such, this means that it can take time for us to get to your Pull Request.  Things like family, or life can get in the way of us getting to PRs, and burnout is a serious concern. The QMK firmware repository averages 200 PRs opened and 200 PRs merged every month, so please have patience.
