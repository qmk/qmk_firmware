# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repo context

This is a fork of QMK Firmware (github.com/qmk/qmk_firmware). It is used to build custom firmware for a **Corne V4.1** split keyboard (`keyboards/crkbd/rev4_1/standard`), a 3x6 PCB (36 keys + 3 thumb keys per side) on an RP2040 microcontroller. The PCB supports 2 extra keys per half (`LAYOUT_split_3x6_3_ex2`) but they are **not wired** on this build — the keymap uses the plain `LAYOUT` (aliased to `LAYOUT_split_3x6_3`), which excludes them.

- Primary development branch: `raph`
- `master` tracks the upstream/official QMK repo — don't develop directly on it, only use it as a merge/rebase base when syncing upstream changes.
- Nearly all custom work lives under `keyboards/crkbd/rev4_1/standard/keymaps/raphaelsmadja/` (`keymap.c`, `rules.mk`). Treat this as the actual "project" directory; the rest of the tree is upstream QMK vendored code that should rarely need edits.

## Key naming convention

When discussing this keymap, keys are referred to by these names instead of raw matrix/column coordinates. Each half has 6 columns x 3 rows plus 3 thumb keys; the naming splits the 6 columns into a 5-wide "querty" block and a 1-wide "pinky" column per side, plus the 3-key "thumb" cluster.

**Querty keys** — the standard QWERTY letters and punctuation (`;` `,` `.` `/`), i.e. left columns 1-5 and right columns 0-4 of each row:
- Row 0: `Q W E R T` / `Y U I O P`
- Row 1 (home row, has the F/J home-row shift mods): `A S D F G` / `H J K L ;`
- Row 2: `Z X C V B` / `N M , . /`

**Pinky keys** — the outer column of each half (left column 0, right column 5), 3 per side named by row. Each also has a 3-letter acronym (Pinky/Left-Right/Up-Middle-Down):
| | Gauche (left) | Droite (right) |
|---|---|---|
| **Haut** (top) | `PLU` = `LALT_T(KC_TAB)` — Tab tap / Alt hold | `PRU` = `TD(TD_PRU)` — Escape tap / toggle mouse layer (layer 4) on double-tap; on layer 4 itself, `PRU` is overridden to `TO(0)` so a single tap exits back to layer 0 |
| **Milieu** (home row) | `PLM` = `KC_LCTL` | `PRM` = `KC_QUOT` — the `'` key |
| **Bas** (bottom) | `PLD` = `KC_LSFT` | `PRD` = `KC_RSFT` |

**Thumb keys** — the 3-key mod cluster per side, named by distance from the keyboard's center gap. Each also has a 3-letter acronym (Thumb/Left-Right/Inner-Middle-Outer):
| | Gauche (left) | Droit (right) |
|---|---|---|
| **Extérieur** (outermost, away from center) | `TLO` = `OSM(MOD_HYPR)` | `TRO` = `KC_BSPC` |
| **Milieu** | `TLM` = `MO(1)` | `TRM` = `LT(2, KC_SPC)` |
| **Intérieur** (innermost, next to center) | `TLI` = `LGUI_T(KC_ENT)` | `TRI` = `KC_SPC` |

These names describe layer 0 (the base layer); the same position names apply on other layers even when the keycode there differs (e.g. "pinky droite haut" is `QK_BOOT` on layer 3, `KC_ESC` on layer 0).

## Build / compile

The `qmk` CLI (Python) is not installed in this environment (`pip install -r requirements.txt` would provide it). Without it, the top-level `Makefile` still works directly:

```sh
# Build the firmware for this keymap
make crkbd/rev4_1/standard:raphaelsmadja

# Verbose build (see full compiler output)
make crkbd/rev4_1/standard:raphaelsmadja VERBOSE=true

# Clean build artifacts
make clean
```

The output is a `.uf2` file (RP2040 bootloader format) at the repo root, named like `crkbd_rev4_1_standard_raphaelsmadja.uf2`. Flashing requires physical access to the keyboard (put it in bootloader mode, then copy the `.uf2` to the mass-storage device) — this can't be done from this environment.

There is no build step needed to just edit the keymap; only run `make` to verify the firmware compiles after changes to `keymap.c` or `rules.mk`.

## Tests

Core QMK has its own unit test suite (C++ tests under `tests/`, plus Python tests under `lib/python/qmk/tests` run via `nose2`/`nose2.cfg`). These test core QMK behavior (tap-dance, tap-hold, combos, etc.), not this specific keymap — there is no dedicated test target for a single keymap's `keymap.c`. Compiling successfully (`make crkbd/rev4_1/standard:raphaelsmadja`) is the practical correctness check for changes in this repo.

If a change touches shared/core QMK code (rare — normally out of scope here), run the relevant test target, e.g.:

```sh
make test:tap_dance
```

## Keymap architecture (`keyboards/crkbd/rev4_1/standard/keymaps/raphaelsmadja/`)

- `keymap.c` defines a 5-layer `keymaps[]` array using the `LAYOUT()` macro (36 main keys + 6 thumb keys, split 18/18 + 3/3):
  - Layer 0: base QWERTY layer with home-row mods (`LALT_T`, `LSFT_T`/`RSFT_T` on F/J, `LGUI_T` on Enter) and a Hyper one-shot mod (`OSM(MOD_HYPR)`).
  - Layer 1: symbols/numbers (accessed via `MO(1)` on layer 0).
  - Layer 2: navigation/media/screenshot keys (accessed via `LT(2, KC_SPC)`, i.e. hold space).
  - Layer 3: reached automatically when layers 1+2 are both active (tri-layer) — bootloader entry (`QK_BOOT`), RGB matrix controls, and window-management arrow keys.
  - Layer 4: mouse keys layer, entered by double-tapping `PRU` on layer 0 (locked on via `layer_invert(4)`) and exited with a single tap of `PRU` (overridden to `TO(0)` on this layer, instead of falling through to the layer-0 tap-dance); `TRM`/`TRI` are left click (`MS_BTN1`) and `TRO` is right click (`MS_BTN2`) while on this layer.
  - Two tap-dances: `TD_BSPC` (tap = backspace, double-tap = Option+Backspace/word delete) and `TD_PRU` (tap = Escape, double-tap = toggle/lock layer 4 via `layer_invert(4)` — done manually since `TG()` can't be passed to the simple tap-dance macros).
- `layer_state_set_user()` wires up the tri-layer behavior (`update_tri_layer_state(state, 1, 2, 3)`), making layer 3 accessible by holding both layer-1 and layer-2 triggers together.
- `get_hold_on_other_key_press()` customizes "hold on other key press" behavior for tap-hold keys: the space/layer-2 key (`LT(2, KC_SPC)`) resolves to hold immediately on another keypress, while the F/J home-row shift mods do not (favoring fast typing over eager modifier activation).
- `rules.mk` enables `MOUSEKEY_ENABLE`, `RGB_MATRIX_ENABLE`, and `TAP_DANCE_ENABLE` for this keymap specifically.

Keyboard-level config (matrix pins, RGB matrix LED positions, split/handedness config, available `LAYOUT_*` macros) lives one level up in `keyboards/crkbd/rev4_1/standard/keyboard.json` and `keyboards/crkbd/rev4_1/info.json` — only touch these if changing the physical hardware config (not needed for keymap/layer/behavior changes).

## Contributing back upstream

`.github/copilot-instructions.md` documents QMK's own PR review checklist (branch targeting, `info.json` requirements, license headers, keymap conventions, etc.). It's only relevant if opening a PR against the official `qmk/qmk_firmware` repo — not needed for personal changes on `raph`.
