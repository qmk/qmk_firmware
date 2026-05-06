---
applyTo: "**"
excludeAgent:
  - "coding-agent"
---
# GitHub Copilot Instructions for QMK Pull Request Review
This document provides automated review guidance based on the [QMK PR Checklist](https://docs.qmk.fm/pr_checklist) and it is intended only for use by GitHub Copilot code-review agent during pull request reviews.

## General PR Requirements

### Branch and Submission Standards
- **Source Branch Policy**: Verify PR is NOT submitted from submitter's own `master` branch
  - Flag if submitter is using their own `master` branch as source
  - Suggest using feature branches instead for cleaner fork management
- **Target Branch Policy**:
  - **New keyboard additions** → `master` branch (new folders under `keyboards/`)
  - **All other changes** → `develop` branch:
    - Keyboard updates, refactors, or moves
    - Core code changes
    - Data-driven configuration migrations
    - Any modifications to existing keyboards
- **PR Scope**: PRs should contain the smallest set of modifications for a single change
  - Flag PRs that modify multiple keyboards simultaneously
  - Suggest splitting large PRs into focused, incremental changes
- **Merge Conflicts**: Check for unresolved merge conflicts

### File Naming and Structure
- **Lowercase Requirement**: All new directories and filenames must be lowercase
  - Exception: Upstream sources with original uppercase (LUFA, ChibiOS)
  - Exception: Core files with valid justification
  - **Reject**: Board designer preference for uppercase is NOT valid justification

### License Headers
- **Required**: Valid license headers on all `*.c` and `*.h` files
- **Recommended**: GPL2/GPL3 for consistency
- **Format**: Check for proper GPL2+ header or SPDX identifier
  ```c
  // Copyright 2024 Your Name (@yourgithub)
  // SPDX-License-Identifier: GPL-2.0-or-later
  ```
- **Exception**: Simple assignment-only `rules.mk` files don't need headers
- **Flag**: Missing or ambiguous license headers (blocks merge)

### QMK Best Practices
- **Include Guards**: Use `#pragma once` instead of `#ifndef` guards in headers
- **Abstractions Required**: No low-level GPIO/I2C/SPI functions
  - Must use QMK abstractions (flag direct hardware access)
- **Timing Functions**:
  - Use `wait_ms()` instead of `_delay_ms()`
  - Remove `#include <util/delay.h>`
  - Use `timer_read()`, `timer_read32()` from `timer.h`
- **New Abstractions**: If proposing new abstraction, suggest:
  1. Prototype in own keyboard first
  2. Discuss with QMK Collaborators on Discord
  3. Refactor as separate core change
  4. Remove the keyboard-specific implementation from board

---

## Keymap PR Reviews

**Scope**: These rules apply to files within `keyboards/*/keymaps/*` subdirectories.

### Note on Personal Keymaps
- **Policy Change**: Personal keymap submissions no longer accepted
- **Permitted**: Vendor-specific keymaps only
  - Naming convention: `default_${vendor}` (e.g., `default_clueboard`)
  - Can be more feature-rich than stock `default` keymaps

### Keymap Code Standards
- **Includes**: `#include QMK_KEYBOARD_H` preferred over specific board files
- **Enums**: Prefer layer enums to `#define`s
- **Custom Keycodes**: First entry must be `QK_USER`
- **Formatting**: Check spacing alignment on commas and keycodes (spaces, not tabs)
- **VIA**: Keymaps should NOT enable VIA
  - VIA keymaps belong in [VIA QMK Userspace](https://github.com/the-via/qmk_userspace_via)

---

## Keyboard PR Reviews

**Scope**: These rules apply to keyboard-level files in `keyboards/*` directories, excluding files within the `keymaps/` subdirectories. This includes:
- `info.json` or `keyboard.json` (keyboard root or variant level)
- `readme.md` (keyboard level)
- `rules.mk` (keyboard level)
- `config.h` (keyboard level, not keymap level)
- `<keyboard>.c` and `<keyboard>.h` files
- Hardware configuration files (`halconf.h`, `mcuconf.h`, `chconf.h`)

### Branch Targeting
- **New Keyboards**: Target `master` branch
  - New additions to `keyboards/` folder submit to `master`
- **Keyboard Moves**: Must target `develop` branch
  - Check `data/mappings/keyboard_aliases.hjson` is updated for moves
- **Keyboard Updates/Refactors**: Must target `develop` to reduce merge conflicts
- **Data Driven Migration**: Must target `develop`

### info.json and keyboard.json Requirements
- **Data-Driven Configuration**: Encourage maximum use of `info.json` and `keyboard.json` schema features
- **Schema Validation**: All `info.json` and `keyboard.json` files must validate against `data/schemas/keyboard.jsonschema`
  - Use QMK CLI: `qmk lint -kb <keyboard_name>` to validate
  - Schema defines required fields, data types, and valid values
  - Check for schema validation errors before submitting PR
- **Mandatory Elements**:
  - Valid URL
  - Valid maintainer
  - Valid USB VID/PID and device version
  - Displays correctly in Configurator (Ctrl+Shift+I to preview)
  - `layout` definitions include matrix positions
  - Standard layout definitions where applicable
  - Community Layout macro names when applicable
  - Microcontroller and bootloader specified
  - Diode direction (if not using direct pins)
- **Layout Naming**:
  - Single layout: Use `LAYOUT` or community layout name
  - Multiple layouts: Include `LAYOUT_all` + alternate names
  - Prefer community layout names (e.g., `LAYOUT_tkl_ansi`, `LAYOUT_ortho_4x4`)
- **Configuration in info.json or keyboard.json** (when applicable):
  - Direct pin configuration
  - Backlight, Split keyboard, Encoder, Bootmagic configs
  - LED Indicator, RGB Light, RGB Matrix configs
- **Format**: Run `qmk format-json -i` before submitting

### USB VID/PID Uniqueness
VID+PID combination must be unique across all keyboards. Individual VID or PID values can be reused with different partners.
**Validation Steps:**
1. Extract VID and PID from keyboard.json/info.json in the PR
2. Search for existing usage: `grep -r '"vid".*"0xVVVV"' keyboards/ --include="*.json" | grep -l '"pid".*"0xPPPP"'`
3. If results found: Check if BOTH VID AND PID match in same file
   - Both match = **COLLISION** - request different PID
   - Only one matches = **OK** - different keyboards can share individual values
4. For keyboard variants/revisions under same keyboard folder:
   - Different PID recommended for functionally different variants
   - Same PID acceptable if revisions only differ in hardware routing/pin assignments
**Quick Reference:**
- Same PID + Different VID = Valid
- Same VID + Different PID = Valid
- Same VID + Same PID = Invalid
**Review Response:**
For collision:
```
VID+PID collision: 0xVVVV:0xPPPP already used by keyboards/[path]/file.json
+Please assign a different PID. VID can remain the same.
```
For uniqueness confirmed:
```
VID+PID validation: 0xVVVV:0xPPPP is unique (no collisions found)
```

### readme.md Requirements
- **Template**: Must follow [official template](https://github.com/qmk/qmk_firmware/blob/master/data/templates/keyboard/readme.md)
- **Flash Command**: Present with `:flash` at end
- **Hardware Link**: Valid availability link (unless handwired)
  - Private groupbuys acceptable
  - One-off prototypes will be questioned
  - Open-source should link to files
- **Reset Instructions**: Clear bootloader mode instructions
- **Images Required**:
  - Keyboard and PCB photos preferred
  - Must be hosted externally (imgur, etc.)
  - Direct image links required (not preview pages)
  - Example: `https://i.imgur.com/vqgE7Ok.jpg` not `https://imgur.com/vqgE7Ok`

### rules.mk Standards
- **Removed Items**:
  - `MIDI_ENABLE`, `FAUXCLICKY_ENABLE`, `HD44780_ENABLE`
  - Size comments like `(-/+size)`
  - Alternate bootloader lists if one specified
  - MCU parameter re-definitions matching defaults in `mcu_selection.mk`
- **Comment Updates**: Change bootloader comments to generic
- **Forbidden Features at Keyboard Level** (these belong in keymap-level `rules.mk` only):
  - `COMBO_ENABLE`
  - `ENCODER_MAP_ENABLE`

### config.h Standards (Keyboard Level)
- **Prohibited**:
  - `#define DESCRIPTION`
  - Magic Key Options, MIDI Options, HD44780 configuration
  - User preference `#define`s (belong in keymap)
  - Re-defining default values (`DEBOUNCE`, RGB settings)
  - Copy/pasted comment blocks explaining features
  - Commented-out unused defines
  - `#include "config_common.h"`
  - `#define MATRIX_ROWS/COLS` (unless custom matrix)
- **Minimal Code**: Only critical board boot code required
- **No Vial**: Vial-related files/changes not accepted

### Keyboard Implementation Files

#### `<keyboard>.c`
- **Remove Empty Functions**: Delete empty or commented-out weak-defined functions
  - `xxxx_xxxx_kb()`, `xxxx_xxxx_user()` implementations
- **Migration**: `matrix_init_board()` → `keyboard_pre_init_kb()`
- **Custom Matrix**: Use `lite` variant when possible for standard debounce
  - `CUSTOM_MATRIX = lite` preferred
  - Full custom matrix (`yes`) requires justification
- **LED Indicators**: Prefer Configuration Options over custom `led_update_*()` implementations
- **Hardware Configuration**: Basic functionality for OLED, encoders, etc. at keyboard level

#### `<keyboard>.h`
- **Include**: `#include "quantum.h"` at top
- **Layout Macros**: Move to `info.json` or `keyboard.json` (no longer in header)

### Default Keymap Standards

**Scope**: These rules specifically apply to files within `keyboards/*/keymaps/default/` directories.

- **Pristine Requirement**: Bare minimum clean slate
  - No custom keycodes
  - No advanced features (non-exhaustive list of examples: tap dance, macros)
  - Basic mod taps and home row mods acceptable when necessary
  - Standard layouts preferred -- see examples in `layouts/default/` and `layouts/community/`
- **Removed Examples**: Delete `QMKBEST`/`QMKURL` macros
- **Tri Layer**: Use Tri Layer feature instead of manual `layer_on/off()` + `update_tri_layer()`
- **Encoder Map**: Use encoder map feature, `encoder_update_user()` may not be present
- **No VIA**: Default keymap should not enable VIA
- **Additional Keymaps**: Example/bells-and-whistles keymaps acceptable in same PR (separate from default)

### Prohibited Files
- **No VIA JSON**: Belongs in [VIA Keyboard Repo](https://github.com/the-via/keyboards)
- **No KLE JSON**: Not used within QMK
- **No Cross-Keyboard Sources**: Don't include files from other keyboard vendors
  - Exception: Core files (e.g., `drivers/sensors/pmw3360.c`)
  - Use of vendor-specific code (e.g., `wilba_tech/wt_main.c`) only when keyboard exists in the same enclosing vendor folder (e.g. a `wilba_tech` keyboard)
  - Multi-board code is candidate for core refactoring when intended for use by multiple vendors

### Wireless Keyboards
- **Policy**: Wireless/Bluetooth PRs rejected without complete wireless code
  - Wireless code may not include anything resembling precompiled data such as `*.a` files or other libraries
  - Firmware blobs are not permitted in raw form or as compiled C-style arrays either.
  - GPL2+ license requires full source disclosure
  - Historically abused for VIA compatibility without releasing sources
  - PRs without wireless capability will be held indefinitely
  - Existing merged wireless boards from same vendor held until sources provided

### ChibiOS-Specific Requirements
- **Board Definitions**: Strong preference for existing ChibiOS board definitions
  - Use equivalent Nucleo boards when possible
  - Example: STM32L082KZ can use `BOARD = ST_NUCLEO64_L073RZ`
  - QMK is eliminating custom board definitions due to maintenance burden
- **New Board Definitions**:
  - Must NOT be embedded in keyboard PR
  - Submit as separate Core PR
  - `board.c` must have standard `__early_init()` and empty `boardInit()`
  	- Migrate code intended for `__early_init()` → keyboard-local `early_hardware_init_pre/post()`
    - Migrate code intended for `boardInit()` → keyboard-local `board_init()`

---

## Core PR Reviews

### Targeting and Scope
- **Branch**: All core PRs must target `develop` branch
- **Single Focus**: Smallest set of changes per PR
  - PRs with multiple areas will be asked to split
  - Keyboard/keymap changes only if affecting base builds or default-like keymaps
  - Keymap modifications (non-default) should be followup PR after core merge
  - Large refactoring PRs affecting other keymaps raised separately

### Testing Requirements
- **New Hardware Support**: Requires test keyboard under `keyboards/handwired/onekey`
  - New MCUs: Add child keyboard targeting new MCU for build verification
  - New hardware (displays, matrix, peripherals): Provide associated keymap
  - Exception: If existing keymap can leverage functionality (consult Collaborators)
- **Callbacks**: New `_kb`/`_user` callbacks must return `bool` for user override
- **Unit Tests**: Strongly recommended, may be required
  - Critical code areas (keycode pipeline) will require tests
  - Boost confidence in current and future correctness

### Code Quality
- **Subjective Review**: Other requirements at QMK Collaborators' discretion
- **Documentation**: Core changes should be well-documented

---

## Automated Review Checklist

When reviewing PRs, check the following systematically:

### File Changes Review
1. **License headers** on all C/H files (GPL2+ preferred, others must be GPL2+ compatible, SPDX format preferred)
2. **File naming** lowercase (flag exceptions needing justification)
3. **Include guards** use `#pragma once`
4. **No low-level hardware access** (GPIO, I2C, SPI direct register writes)
5. **Timing abstractions** (`wait_ms()`, `timer_read()` usage)

### info.json and keyboard.json Validation
1. **Schema Compliance**: `keyboard.json` and `info.json` files validate against `data/schemas/keyboard.jsonschema`
  - Both files are identical syntax, however the `keyboard.json` dictates a buildable target, `info.json` does not
   - Run `qmk lint -kb <keyboard>` to check schema validation
   - Check for proper data types (strings, integers, arrays, objects)
   - Verify required fields are present
   - Ensure enum values match allowed options in schema
2. All mandatory fields present and valid
3. `qmk format-json -i` has been run (formats and validates)
4. Layout macros moved from headers
5. Community layout names used where applicable

### rules.mk Cleanup
1. Deprecated features removed
2. No size comments
3. No keymap-only features at keyboard level
4. No redundant MCU parameter definitions

### config.h Cleanup
1. No `DESCRIPTION`, `config_common.h`, or prohibited includes
2. No default value re-definitions
3. No commented-out defines or feature documentation blocks
4. No user preference defines at keyboard level

### Keymap Quality
1. Default keymaps are pristine (no custom keycodes/advanced features)
2. No `QMKBEST`/`QMKURL` macros
3. Encoder map feature used instead of `encoder_update_user()`
4. Tri Layer feature used for multi-layer access
5. No VIA enabled in default keymap

### Documentation
1. readme.md follows template
2. Flash command present with `:flash`
3. Reset instructions clear
4. External image hosting (direct links)
5. Valid hardware availability link

### Code Organization
1. Empty weak-defined functions removed from `<keyboard>.c`
2. Proper migration of init functions
3. No cross-vendor source files
4. No VIA/KLE JSON files

### Branch and Scope
1. Not submitted from submitter's own `master` branch (use feature branches)
2. PR is focused on single change
3. Targets correct branch:
   - `master` for new keyboard additions
   - `develop` for keyboard updates/refactors/moves and core changes
4. No merge conflicts

---

## Review Response Templates

### For source master branch usage:
```
⚠️ This PR appears to be submitted from your own `master` branch. For future PRs, we recommend using feature branches instead of committing to your `master`. This makes it easier to keep your fork updated and manage multiple PRs.

See: [Best Practices: Your Fork's Master](https://docs.qmk.fm/newbs_git_using_your_master_branch)
```

### For incorrect target branch:
```
❌ This PR targets the wrong branch:
- **New keyboard additions** should target `master`
- **Keyboard updates/refactors/moves** should target `develop`
- **Core changes** should target `develop`

Please change the target branch accordingly.
```

### For missing license headers:
```
❌ Missing GPL-compatible license headers on the following files:
- [list files]

Please add GPL2+ headers (GPL2/GPL3 recommended). Example:
\`\`\`c
// Copyright 2024 Your Name (@yourgithub)
// SPDX-License-Identifier: GPL-2.0-or-later
\`\`\`
```

### For non-lowercase filenames:
```
❌ The following files/directories must be lowercase:
- [list files]

Exception: Only valid if from upstream sources (LUFA, ChibiOS) or justified by core consistency.
```

### For config.h violations:
```
⚠️ Found prohibited config.h elements:
- [list specific issues: DESCRIPTION, default value re-definitions, etc.]

Please remove these and refer to [Data Driven Configuration](https://docs.qmk.fm/data_driven_config).
```

### For info.json or keyboard.json issues:
```
⚠️ info.json or keyboard.json needs attention:
- [list missing mandatory fields]
- Please run: \`qmk format-json -i path/to/info.json\` (or keyboard.json)
- Validate with: \`qmk lint -kb <keyboard_name>\`
```

### For schema validation errors:
```
❌ Schema validation failed for info.json or keyboard.json:
- [list specific validation errors from schema]
- Check `data/schemas/keyboard.jsonschema` for valid field definitions
- Common issues:
  - Invalid data types (e.g., string instead of integer)
  - Missing required fields
  - Invalid enum values
  - Incorrectly formatted pin definitions
```

### For non-pristine default keymap:
```
⚠️ Default keymap should be pristine (clean slate for users):
- Remove: [custom keycodes/tap dance/macros/etc.]
- Keep it minimal with standard layouts where possible

Consider moving advanced features to a separate example keymap.
```

---

## Notes for GitHub Copilot

- Focus reviews on **objective checklist items** that can be automatically verified
- Flag **definite violations** with ❌
- Suggest improvements for **recommendations** with ⚠️
- **Provide specific file/line references** when flagging issues
- **Link to relevant QMK documentation** for each issue
- **Prioritize blocking issues** (license, merge conflicts, branch policy)
- **Be constructive**: Suggest fixes, not just problems
- **Acknowledge trade-offs**: Some guidelines have valid exceptions

This is meant as a **first-pass review** to catch common issues before human review. Complex architectural decisions, code quality, and subjective assessments still require human QMK Collaborator review.
