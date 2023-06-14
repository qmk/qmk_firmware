# PR checklists

This is a non-exhaustive checklist of what the QMK Collaborators will be checking when reviewing submitted PRs.

If there are any inconsistencies with these recommendations, you're best off [creating an issue](https://github.com/qmk/qmk_firmware/issues/new) against this document, or getting in touch with a QMK Collaborator on [Discord](https://discord.gg/Uq7gcHh).

## Requirements for all PRs

- PR should be submitted using a non-`master` branch on the source repository
    - this does not mean you target a different branch for your PR, rather that you're not working out of your own master branch
    - if submitter _does_ use their own `master` branch, they'll be given a link to the ["how to git"](newbs_git_using_your_master_branch.md) page after merging -- (end of this document will contain the contents of the message)
- PRs should contain the smallest amount of modifications required for a single change to the codebase
    - multiple keyboards at the same time is not acceptable
        - exception: keymaps for a single user targeting multiple keyboards and/or userspace is acceptable
    - **the smaller the PR, the higher likelihood of a quicker review, higher likelihood of quicker merge, and less chance of conflicts**
- newly-added directories and filenames must be lowercase
    - the lowercase requirement may be relaxed if upstream sources originally had uppercase characters (e.g. LUFA, ChibiOS, or imported files from other repositories etc.)
    - if there is valid justification (i.e. consistency with existing core files etc.) this can be relaxed
        - a board designer naming their keyboard with uppercase letters is not enough justification
- valid license headers on all `*.c` and `*.h` source files
    - GPL2/GPL3 recommended for consistency
    - an example GPL2+ license header may be copied (and author modified) from the bottom of this document
    - other licenses are permitted, however they must be GPL-compatible and must allow for redistribution. Using a different license will almost certainly delay a PR getting merged
    - missing license headers will prevent PR merge due to ambiguity with license compatibility
        - simple assignment-only `rules.mk` files should not need a license header - where additional logic is used in an `*.mk` file a license header may be appropriate
- QMK Codebase "best practices" followed
    - this is not an exhaustive list, and will likely get amended as time goes by
    - `#pragma once` instead of `#ifndef` include guards in header files
    - no "old-school" or other low-level GPIO/I2C/SPI functions may be used -- must use QMK abstractions unless justifiable (and laziness is not valid justification)
    - timing abstractions should be followed too:
        - `wait_ms()` instead of `_delay_ms()` (remove `#include <util/delay.h>` too)
        - `timer_read()` and `timer_read32()` etc. -- see [timer.h](https://github.com/qmk/qmk_firmware/blob/master/platforms/timer.h) for the timing APIs
    - if you think a new abstraction is useful, you're encouraged to:
        - prototype it in your own keyboard until it's feature-complete
        - discuss it with QMK Collaborators on Discord
        - refactor it as a separate core change
        - remove your specific copy in your board
- fix all merge conflicts before opening the PR (in case you need help or advice, reach out to QMK Collaborators on Discord)
    - PR submitters will need to keep up-to-date with their base branch, resolving conflicts along the way

## Keymap PRs

- `#include QMK_KEYBOARD_H` preferred to including specific board files
- prefer layer `enum`s to `#define`s
- require custom keycode `enum`s to `#define`s, first entry must have ` = SAFE_RANGE`
- terminating backslash (`\`) in lines of LAYOUT macro parameters is superfluous and should be removed
- some care with spacing (e.g., alignment on commas or first char of keycodes) makes for a much nicer-looking keymap

## Keyboard PRs

Closed PRs (for inspiration, previous sets of review comments will help you eliminate ping-pong of your own reviews):
https://github.com/qmk/qmk_firmware/pulls?q=is%3Apr+is%3Aclosed+label%3Akeyboard

- keyboard moves within the repository *must* go through the `develop` branch instead of `master`, so as to ensure compatibility for users
    - `data/mappings/keyboard_aliases.hjson` must be updated to reflect the move, so users with pre-created configurator keymap.json files continue to detect the correct keyboard
- keyboard updates and refactors (eg. to data driven) *must* go through `develop` to reduce `master` -> `develop` merge conflicts
- PR submissions from a `kbfirmware` export (or equivalent) will not be accepted unless converted to new QMK standards -- try `qmk import-kbfirmware` first
- `info.json`
    - With the move to [data driven](https://docs.qmk.fm/#/data_driven_config) keyboard configuration, we encourage contributors to utilise as many features as possible of the info.json [schema](https://github.com/qmk/qmk_firmware/blob/master/data/schemas/keyboard.jsonschema).
    - the mandatory elements for a minimally complete `info.json` at present are:
        - valid URL
        - valid maintainer
        - valid USB VID/PID and device version
        - displays correctly in Configurator (press Ctrl+Shift+I to preview local file, turn on fast input to verify ordering)
        - `layout` definitions must include matrix positions, so that `LAYOUT` macros can be generated at build time
            - should use standard definitions if applicable
            - use the Community Layout macro names where they apply (preferred above `LAYOUT`/`LAYOUT_all`)
            - If the keyboard only has a single electrical/switch layout:
                - use `LAYOUT` as your macro name, unless a community layout already exists
            - If the keyboard has multiple electrical/switch layouts:
                - include a `LAYOUT_all` which specifies all possible layout positions in the electrical matrix
                - use alternate layout names for all other possible layouts, preferring community layout names if an equivalent is available (e.g. `LAYOUT_tkl_ansi`, `LAYOUT_ortho_4x4` etc.)
        - Microcontroller and bootloader
        - Diode Direction (if not using direct pins)
    - the following are required to be configured in `info.json` if necessary
      - Direct pin configuration
      - Backlight Configuration (where applicable)
      - Split keyboard configuration (where applicable)
      - Encoder Configuration
      - Bootmagic Configuration
      - LED Indicator Configuration
- `readme.md`
    - must follow the [template](https://github.com/qmk/qmk_firmware/blob/master/data/templates/keyboard/readme.md)
    - flash command is present, and has `:flash` at end
    - valid hardware availability link (unless handwired) -- private groupbuys are okay, but one-off prototypes will be questioned. If open-source, a link to files should be provided.
    - clear instructions on how to reset the board into bootloader mode
    - a picture about the keyboard and preferably about the PCB, too
        - images are not to be placed in the `qmk_firmware` repository
        - images should be uploaded to an external image hosting service, such as [imgur](https://imgur.com/).
        - if imgur is used, images should be resized appropriately: append "h" to the image url i.e. [https://i.imgur.com/vqgE7Ok.jpg](https://i.imgur.com/vqgE7Ok.jpg) becomes [https://i.imgur.com/vqgE7Ok**h**.jpg](https://i.imgur.com/vqgE7Okh.jpg)
        - image links should link directly to the image, not a "preview" -- i.e. [https://imgur.com/vqgE7Ok](https://imgur.com/vqgE7Ok) should be [https://i.imgur.com/vqgE7Okh.jpg](https://i.imgur.com/vqgE7Okh.jpg) when using imgur
- `rules.mk`
    - removed `MIDI_ENABLE`, `FAUXCLICKY_ENABLE` and `HD44780_ENABLE`
    - modified `# Enable Bluetooth with the Adafruit EZ-Key HID` -> `# Enable Bluetooth`
    - no `(-/+size)` comments related to enabling features
    - remove the list of alternate bootloaders if one has been specified
    - no re-definitions of the default MCU parameters if same value, when compared to the equivalent MCU in [mcu_selection.mk](https://github.com/qmk/qmk_firmware/blob/master/builddefs/mcu_selection.mk)
    - no "keymap only" features enabled
      - `COMBO_ENABLE`
      - `ENCODER_MAP_ENABLE`
- keyboard `config.h`
    - no `#define DESCRIPTION`
    - no Magic Key Options, MIDI Options or HD44780 configuration
    - user preference configurable `#define`s need to be moved to keymap `config.h`
    - default values should not be redefined, such as `DEBOUNCE`, RGB related settings, etc.
      - feature specific documentation contains most default values
      - `grep` or alternative tool can be used to search for default values in core directories (e.g. `grep -r "define DEBOUNCE" quantum`)
    - no copy/pasted comment blocks explaining a feature and/or its caveats -- this is what the docs are for
      - `Force NKRO to be enabled ... toggled again during a power-up`
      - commented-out unused defines, such as RGB effects
    - no `#include "config_common.h`
    - no `#define MATRIX_ROWS/COLS`, unless necessary (e.g. a keyboard with a custom matrix)
    - bare minimum required code for a board to boot into QMK should be present
        - initialisation code for the matrix and critical devices
        - mirroring existing functionality of a commercial board (like custom keycodes and special animations etc.) should be handled through non-`default` keymaps
    - Vial-related files or changes will not be accepted, as they are not used by QMK firmware (no Vial-specific core code has been submitted or merged)
- `<keyboard>.c`
    - empty `xxxx_xxxx_kb()` or other weak-defined default implemented functions removed
    - empty `xxxx_xxxx_user()` or other user-level functions are disallowed at the keyboard level and must be moved to keymaps
    - commented-out functions removed too
    - `matrix_init_board()` etc. migrated to `keyboard_pre_init_kb()`, see: [keyboard_pre_init*](custom_quantum_functions.md?id=keyboard_pre_init_-function-documentation)
    - prefer `CUSTOM_MATRIX = lite` if custom matrix used, allows for standard debounce, see [custom matrix 'lite'](custom_matrix.md?id=lite)
    - prefer LED indicator [Configuration Options](feature_led_indicators.md?id=configuration-options) to custom `led_update_*()` implementations where possible
    - hardware that's enabled at the keyboard level and requires configuration such as OLED displays or encoders should have basic functionality implemented here
- `<keyboard>.h`
    - `#include "quantum.h"` appears at the top
    - `LAYOUT` macros are no longer accepted and should instead be moved to `info.json`
- keymap `config.h`
    - no duplication of `rules.mk` or `config.h` from keyboard
- `keymaps/default/keymap.c`
    - `QMKBEST`/`QMKURL` example macros removed
    - if using `MO(1)` and `MO(2)` keycodes together to access a third layer, the [Tri Layer](https://docs.qmk.fm/#/feature_tri_layer) feature should be used, rather than manually implementing this using `layer_on/off()` and `update_tri_layer()` functions in the keymap's `process_record_user()`.
- default (and via) keymaps should be "pristine"
    - bare minimum to be used as a "clean slate" for another user to develop their own user-specific keymap
    - standard layouts preferred in these keymaps, if possible
    - should use [encoder map feature](https://docs.qmk.fm/#/feature_encoders?id=encoder-map), rather than `encoder_update_user()`
    - default keymap should not enable VIA -- the VIA integration documentation requires a keymap called `via`
- submitters can have a personal (or bells-and-whistles) keymap showcasing capabilities in the same PR but it shouldn't be embedded in the 'default' keymap
- submitters can also have a "manufacturer-matching" keymap that mirrors existing functionality of the commercial product, if porting an existing board
- Do not include VIA json files in the PR. These do not belong in the QMK repository as they are not used by QMK firmware -- they belong in the [VIA Keyboard Repo](https://github.com/the-via/keyboards)
- Do not include KLE json files in the PR. These have no use within QMK.
- Do not include source files from another keyboard or vendors keyboard folder. Including core files is fine.
  - For instance, only `wilba_tech` boards shall include `keyboards/wilba_tech/wt_main.c` and  `keyboards/wilba_tech/wt_rgb_backlight.c`. But including `drivers/sensors/pmw3360.c` is absolutely fine for any and all boards that require it.
  - Code that needs to be used by multiple boards is a candidate for core code changes, and should be separated out.

Also, specific to ChibiOS:
- **strong** preference to using existing ChibiOS board definitions.
    - a lot of the time, an equivalent Nucleo board can be used with a different flash size or slightly different model in the same family
        - example: For an STM32L082KZ, given the similarity to an STM32L073RZ, you can use `BOARD = ST_NUCLEO64_L073RZ` in rules.mk
    - QMK is migrating to not having custom board definitions if at all possible, due to the ongoing maintenance burden when upgrading ChibiOS
- New board definitions must not be embedded in a keyboard PR
    - See [Core PRs](#core-pr) below for the procedure for adding a new board to QMK
- if a board definition is unavoidable, `board.c` must have a standard `__early_init()` (as per normal ChibiOS board defs) and an empty `boardInit()`:
    - see Arm/ChibiOS [early initialization](platformdev_chibios_earlyinit.md?id=board-init)
    - `__early_init()` should be replaced by either `early_hardware_init_pre()` or `early_hardware_init_post()` as appropriate
    - `boardInit()` should be migrated to `board_init()`

## Core PRs :id=core-pr

- all core PRs must now target `develop` branch, which will subsequently be merged back to `master` on the breaking changes timeline
- as indicated above, the smallest set of changes to core components should be included in each PR
    - PRs containing multiple areas of change will be asked to be split up and raised separately
    - keyboard and keymap changes should only be included if they affect base keyboard builds, or the default-like `default`, `via`, `default_????` keymaps etc.
        - keymap modifications for anything other than the default-like keymaps **should not be included in the initial PR** in order to simplify the review process
        - the core PR submitter should submit a followup PR affecting other keymaps after initial PR merge
        - large-scale refactoring or consolidation PRs that affect other keymaps (such as renaming keycodes) should always be raised separately
- any new boards adding support for new hardware now requires a corresponding test board under `keyboards/handwired/onekey`
    - for new MCUs, a new "child" keyboard should be added that targets your newly-added MCU, so that builds can be verified
    - for new hardware support such as display panels, core-side matrix implementations, or other peripherals, an associated keymap should be provided
    - if an existing keymap exists that can leverage this functionality this may not be required (e.g. a new RGB driver chip, supported by the `rgb` keymap) -- consult with the QMK Collaborators on Discord to determine if there is sufficient overlap already
- any features adding `_kb`/`_user` callbacks must return a `bool`, to allow for user override of keyboard-level callbacks.
- where relevant, unit tests are strongly recommended -- they boost the confidence level that changes behave correctly
    - critical areas of the code -- such as the keycode handling pipeline -- will almost certainly require unit tests accompanying them to ensure current and future correctness
    - you should not be surprised if a QMK collaborator requests unit tests to be included in your PR if it's critical functionality
- other requirements are at the discretion of QMK collaborators
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

## Example GPLv2 Header

```
/* Copyright 2021 Your Name (@yourgithub)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
```

Or, optionally, using [SPDX identifier](https://spdx.org/licenses/) instead:

```
// Copyright 2021 Your Name (@yourgithub)
// SPDX-License-Identifier: GPL-2.0-or-later
```
