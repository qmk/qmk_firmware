# KeyCraftPro QMK Firmware Design

**Date:** 2026-07-31  
**Status:** Implemented (default keymap)  
**Keyboard path:** `keyboards/key_craft_pro`

## Goal

Ship a working default QMK configuration for the handwired KeyCraftPro macropad: 12 keys, dual encoders, vertically mounted SSD1306 OLED, with desk-productivity bindings, layer navigation, and a Mac/Windows mode toggle on the right encoder click.

## Hardware (from wiring diagram + photo)

| Item | Detail |
|------|--------|
| MCU | Arduino Pro Micro (`development_board: promicro`) |
| Matrix | 3 rows × 5 cols, diodes assumed **COL2ROW** |
| Keys | 12 switches in a physical 4×3 grid |
| Encoder buttons | In matrix at `[0][4]` and `[2][4]` |
| Encoder 1 (left / small) | A=`C6` (pin 5), B=`D4` (pin 4); button row0/col4 |
| Encoder 2 (right / large) | A=`F6` (A1), B=`F5` (A2); button row2/col4 |
| OLED | SSD1306 128×64 I2C on SDA=`D1` (pin 2), SCL=`D0` (pin 3); mounted **vertically** |
| Reset | Dedicated reset button to GND (hardware only) |

### Pro Micro pin map used

| Function | Arduino pin | AVR pin |
|----------|-------------|---------|
| ROW1 | 8 | `B4` |
| ROW2 | 7 | `E6` |
| ROW3 | 6 | `D7` |
| COL1 | 10 | `B6` |
| COL2 | 16 | `B2` |
| COL3 | 14 | `B3` |
| COL4 | 15 | `B1` |
| COL5 | A0 | `F7` |
| Enc1 A/B | 5 / 4 | `C6` / `D4` |
| Enc2 A/B | A1 / A2 | `F6` / `F5` |

### Physical → matrix mapping

Schematic is electrical **3×4** keys (+ encoder switches on col5). Photo is physical **4×3**. Assumed fill order left-to-right, top-to-bottom across the 3×4 matrix:

```
Physical          Matrix
F1  F2  F3     →  [0,0] [0,1] [0,2]
F4  F5  F6     →  [0,3] [1,0] [1,1]
F7  F8  F9     →  [1,2] [1,3] [2,0]
INS HOME PGUP  →  [2,1] [2,2] [2,3]

Left enc click →  [0,4]
Right enc click→  [2,4]
[1,4]          →  KC_NO (no switch)
```

If a first flash has shifted keys, only the `LAYOUT` matrix indices need correction — no rewiring.

Encoder left/right assignment follows schematic “top” = left small, “bottom” = right large. If rotation direction is inverted, swap `pin_a`/`pin_b` or invert in `encoder_update_user`.

## Architecture

**Approach B — logical layers + OS mode flag (approved).**

- Layers describe *what the pad is doing* (Base / Media / Stub).
- A persistent boolean `is_mac` (default `true`) selects Mac vs Windows chords for OS-aware custom keycodes.
- Right encoder **click** toggles `is_mac` (does not change layer).
- OLED shows layer name + `MAC`/`WIN`.

```
┌─────────────┐     layer nav      ┌──────────┐
│  BASE /     │ ←───────────────→  │  MEDIA   │ ←──→ LAYER2 stub
│  Productivity│   INS/HOME/PGUP   └──────────┘
└──────┬──────┘
       │ right enc click
       ▼
  is_mac ? Mac chords : Win chords
```

## File layout

```
keyboards/key_craft_pro/
  keyboard.json          # matrix, encoder, OLED, features, LAYOUT
  config.h               # OLED rotation / size if needed
  key_craft_pro.c        # OLED task, optional encoder helpers
  readme.md              # flash instructions + pin table
  keymaps/default/
    keymap.c             # layers, custom keycodes, OS toggle, encoders
    rules.mk             # only if keymap needs extra flags
```

Photos (`1.JPEG`, `Wiring Diagram.png`) stay in the folder for reference; they are not build inputs.

## Features enabled

- `extrakey` — media / volume
- `encoder` — dual EC11
- `oled` — SSD1306
- `mousekey` — right encoder scroll via `MS_WH_UP` / `MS_WH_DOWN` (or `tap_code` equivalents)
- `bootmagic` — lite/default as QMK current default for recoverability
- `nkro` — optional; default 6KRO is fine for a macropad

## Layers

| Index | Name | Purpose |
|------:|------|---------|
| 0 | `BASE` | Desk productivity (default) |
| 1 | `MEDIA` | Playback / mic mute helpers |
| 2 | `LAYER2` | Blank stub (`XXXXXXX` / `_______`) for future use |

Layer count is intentionally small so more layers can be added later without redesign.

### Layer navigation (bottom row, all layers)

| Keycap | Code | Behavior |
|--------|------|----------|
| INS | `LYR_PREV` (custom) | Previous layer (wrap) |
| HOME | `LYR_HOME` (custom → layer 0) | Jump to default layer 0 |
| PGUP | `LYR_NEXT` (custom) | Next layer (wrap) |

Custom next/prev keep OS mode untouched and wrap within `0 .. LAYER_COUNT-1`.

## Default keymap — BASE (productivity)

OS-aware keys are custom keycodes (`OS_COPY`, etc.) that emit Mac or Windows sequences based on `is_mac`.

| Pos | Keycap | Mac | Windows |
|-----|--------|-----|---------|
| F1 | Copy | ⌘C | Ctrl+C |
| F2 | Paste | ⌘V | Ctrl+V |
| F3 | Cut | ⌘X | Ctrl+X |
| F4 | Undo | ⌘Z | Ctrl+Z |
| F5 | Redo | ⌘⇧Z | Ctrl+Y |
| F6 | Select All | ⌘A | Ctrl+A |
| F7 | Screenshot region | ⌘⇧4 | Win+Shift+S |
| F8 | Mission Control / Task View | Ctrl+↑ | Win+Tab |
| F9 | App switcher | ⌘Tab | Alt+Tab |
| INS | Prev layer | — | — |
| HOME | Default layer | — | — |
| PGUP | Next layer | — | — |

## Default keymap — MEDIA

Mostly OS-agnostic consumer keys; mic mute may differ:

| Pos | Mac | Windows |
|-----|-----|---------|
| F1 | Play/Pause | Play/Pause |
| F2 | Prev track | Prev track |
| F3 | Next track | Next track |
| F4 | Mute | Mute |
| F5 | Vol Down | Vol Down |
| F6 | Vol Up | Vol Up |
| F7 | Mic mute (⌘⇧M / Teams-style optional) | Win mic mute helper or same media mute |
| F8 | Brightness Down | Brightness Down |
| F9 | Brightness Up | Brightness Up |
| Bottom | Same layer nav | Same layer nav |

Exact F7 mic binding: prefer `KC_F20` / OS mute where available; document as “best effort” in readme (OS/app dependent).

## LAYER2 stub

All positions `XXXXXXX` except bottom-row layer nav keys, so the pad remains navigable while empty.

## Encoders

| Encoder | Rotate | Click |
|---------|--------|-------|
| Left (index 0) | `KC_VOLU` / `KC_VOLD` | `KC_MUTE` |
| Right (index 1) | Mouse wheel up/down | Toggle `is_mac` |

Encoder map (modern QMK `ENCODER_MAP_ENABLE`) can bind volume on all layers for the left knob. Right click handled in `process_record_user` as `OS_TOGGLE` matrix keycode at `[2][4]` (and/or encoder button position in LAYOUT).

Left encoder button sits at matrix `[0][4]` → `KC_MUTE` on every layer.

## OS mode

```c
bool is_mac = true; // default macOS; restored from eeconfig on boot

// On OS_TOGGLE press:
is_mac = !is_mac;
eeconfig_update_user(...); // persist across reboot
```

- Persist OS mode in EEPROM (`eeconfig` user data) so reboot keeps last choice.
- OLED updates immediately on toggle.

Custom keycodes:

`OS_TOGGLE`, `OS_COPY`, `OS_PASTE`, `OS_CUT`, `OS_UNDO`, `OS_REDO`, `OS_SELL`, `OS_SS`, `OS_DESK`, `OS_APP`, `LYR_NEXT`, `LYR_PREV`, `LYR_HOME`

## OLED (vertical SSD1306)

- Enable OLED feature; 128×64 SSD1306 I2C (QMK defaults for Pro Micro I2C pins).
- Rotation: `OLED_ROTATION_90` or `OLED_ROTATION_270` — pick the one that matches the physical mount (flip if upside down on first flash).
- Render (compact, vertical-friendly):
  1. Product line: `KeyCraft`
  2. Layer name: `BASE` / `MEDIA` / `LYR2`
  3. OS: `MAC` or `WIN`
- Optional: master/slave not applicable (single-side board).

## Build / flash

```bash
qmk compile -kb key_craft_pro -km default
qmk flash -kb key_craft_pro -km default
```

Bootloader: Pro Micro Caterina (reset button or short RST–GND twice).

## Risks / first-flash checklist

1. **Key order wrong** → adjust LAYOUT matrix indices only.  
2. **Encoders swapped or inverted** → swap encoder entries or A/B pins.  
3. **OLED upside down / mirrored** → try the other 90° rotation.  
4. **No keys register** → verify COL2ROW vs ROW2COL against diode orientation on the PCB.  
5. **Diode direction** assumed COL2ROW from typical EasyEDA hobby wiring; confirm on board if matrix dead.

## Out of scope (this pass)

- VIA/Vial JSON  
- RGB / underglow  
- Additional filled layers beyond Media + stub  
- QMK upstream PR polish (maintainer line, license headers can be minimal)

## Success criteria

1. All 12 keys report correctly in a keyboard tester.  
2. Left encoder adjusts volume; click mutes.  
3. Right encoder scrolls; click toggles OLED `MAC`↔`WIN` and changes OS-aware shortcuts.  
4. INS / HOME / PGUP move layers; OLED layer label updates.  
5. BASE productivity chords work on macOS by default; Windows chords work after toggle.
