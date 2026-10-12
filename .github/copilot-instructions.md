---
applyTo: "keyboards/**"
excludeAgent:
  - "coding-agent"
---
# GitHub Copilot Instructions for QMK Pull Request Review
This document provides automated review guidance based on the [QMK PR Checklist](https://docs.qmk.fm/pr_checklist) and it is intended only for use by GitHub Copilot code-review agent during pull request reviews.

> **Scope**: This review applies **only to changes within the `keyboards/` folder**. Changes outside `keyboards/` (e.g., core code, quantum, platforms, drivers) must be flagged and deferred to a QMK Collaborator — do not review them.

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

---

## Keymap PR Reviews

**Scope**: These rules apply to files within `keyboards/*/keymaps/*` subdirectories.

### Note on Non-Default Keymaps
- Any keymap folder named something other than `default` (e.g., `default_clueboard`, `via`) is a non-default keymap
- **Do not review the content** of non-default keymaps — flag their presence and note that a QMK Collaborator must review them

### Keymap Code Standards
- **Includes**: `#include QMK_KEYBOARD_H` preferred over specific board files
- **Enums**: Suggest using layer enums instead of `#define`s for layers (soft suggestion only)
- **Custom Keycodes**: First entry must be `QK_USER`
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
- **Schema Validation**: Verify that `info.json` and `keyboard.json` files are valid JSON (no syntax errors, no trailing commas, properly closed brackets)
- **Mandatory Elements**:
  - `url` field is present and begins with `http://` or `https://`
  - `maintainer` field is present and non-empty
  - `usb.vid` and `usb.pid` fields are present and match the `0x` hexadecimal format (e.g. `"vid": "0x1234"`, `"pid": "0xFEED"`)
  - `usb.device_version` field is present
  - Each key entry in every `layout` array must include a `"matrix"` property (e.g. `{"label": "L01", "matrix": [0, 0], "x": 0, "y": 0}`)
  - Microcontroller and bootloader specified
  - Diode direction (if not using direct pins)
- **Layout Naming**:
  - Single layout: Must be named `LAYOUT` or match `LAYOUT_*` pattern
  - Multiple layouts: Must include `LAYOUT_all` plus at least one alternate name

### readme.md Requirements
- **Template**: Must follow [official template](https://github.com/qmk/qmk_firmware/blob/master/data/templates/keyboard/readme.md)
- **Flash Command**: Present with `:flash` at end
- **Hardware Link**: Valid availability link (unless handwired)
  - Private groupbuys acceptable
  - Open-source should link to files
- **Reset Instructions**: Bootloader reset instructions must be present (non-empty)
- **Images**: A keyboard image is preferred but not mandatory
  - If present, images must not be hosted in the repository
  - If an imgur URL is used, it must link directly to the image (i.e. `https://i.imgur.com/<id>.<ext>`), not the preview page (i.e. not `https://imgur.com/<id>`)

### rules.mk Standards
- **Removed Items**:
  - Size comments like `(-/+size)`

### config.h Standards (Keyboard Level)
- **Prohibited**:
  - `#define DESCRIPTION`
  - Comment blocks explaining features
  - Commented-out unused defines
  - `#include "config_common.h"`
- **No Vial**: Vial-related files/changes not accepted

### Keyboard Implementation Files

#### `<keyboard>.c`
- **Advanced Code Flag**: ⚠️ If a `<keyboard>.c` file is present in the PR, flag it as possible advanced code requiring QMK Collaborator review

#### `<keyboard>.h`
- **Include**: `#include "quantum.h"` at top
- **Layout Macros**: If `LAYOUT` macros are present, suggest moving them to `info.json` or `keyboard.json`

### Default Keymap Standards

**Scope**: These rules specifically apply to files within `keyboards/*/keymaps/default/` directories.

- **Pristine Requirement**: Bare minimum clean slate
  - ⚠️ If `keymap.c` contains anything beyond the `keymaps[]` array, or if the `default` keymap folder contains additional `.c` or `.h` files, flag this as possible advanced code requiring QMK Collaborator review
- **Removed Examples**: Delete `QMKBEST`/`QMKURL` macros
- **Tri Layer**: Use Tri Layer feature instead of manual `layer_on/off()` + `update_tri_layer()`
- **Encoder Map**: Use encoder map feature, `encoder_update_user()` may not be present
- **No VIA**: Default keymap should not enable VIA

### Prohibited Files
- **No VIA JSON**: Belongs in [VIA Keyboard Repo](https://github.com/the-via/keyboards)
- **No KLE JSON**: Not used within QMK
- **Single Keyboard Per PR**: A PR must not modify more than one `keyboards/<folder>/` directory
  - Flag PRs that touch multiple top-level keyboard folders (e.g., both `keyboards/mykeyboard1/` and `keyboards/mykeyboard2/`) — each keyboard must be a separate PR
- **No Cross-Keyboard Sources**: Don't include files from other keyboard vendors
  - Exception: Core files (e.g., `drivers/sensors/pmw3360.c`)
  - Use of vendor-specific code (e.g., `wilba_tech/wt_main.c`) only when keyboard exists in the same enclosing vendor folder (e.g. a `wilba_tech` keyboard)

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
- [list specific issues: `#define DESCRIPTION`, `#include "config_common.h"`, comment blocks, commented-out defines]

Please remove these and refer to [Data Driven Configuration](https://docs.qmk.fm/data_driven_config).
```

### For info.json or keyboard.json issues:
```
⚠️ info.json or keyboard.json needs attention:
- [list missing mandatory fields]
- Please run: \`qmk format-json -i path/to/info.json\` (or keyboard.json)
- Validate with: \`qmk lint -kb <keyboard_name>\`
```

### For non-pristine default keymap:
```
⚠️ Default keymap requires collaborator review:
The default `keymap.c` contains code beyond the `keymaps[]` array. The following was detected:
- [describe: extra functions/definitions in keymap.c, or additional .c/.h files in the default keymap folder]

A QMK Collaborator must review this before merging.
```

### For non-default keymaps:
```
⚠️ Non-default keymap detected: `keyboards/[path]/keymaps/[name]/`

This keymap requires a QMK Collaborator to review its content. No automated review of its code was performed.
```

### For `<keyboard>.c` detected:
```
⚠️ `<keyboard>.c` file detected: `keyboards/[path]/[keyboard].c`

This file may contain advanced hardware configuration. A QMK Collaborator must review this before merging.
```

---

## Constraints and Conduct

- **Scope**: Only review changes within the `keyboards/` folder. Flag any changes outside `keyboards/` and defer to a QMK Collaborator without reviewing them.
- Focus reviews on **objective checklist items** that can be automatically verified
- Flag **definite violations** with ❌
- Suggest improvements for **recommendations** with ⚠️
- **Provide specific file/line references** when flagging issues
- **Link to relevant QMK documentation** for each issue
- **Prioritize blocking issues** (license, merge conflicts, branch policy)
- **Be constructive**: Suggest fixes, not just problems
- **Do not review non-default keymaps** — flag their presence and defer to a QMK Collaborator
- **Do not review `<keyboard>.c` content in detail** — flag its presence and defer to a QMK Collaborator

This is meant as a **first-pass review** to catch common issues before human review. Complex architectural decisions, code quality, and subjective assessments still require human QMK Collaborator review.
