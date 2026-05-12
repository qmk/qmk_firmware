# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## About this repo

This is a fork of [QMK firmware](https://qmk.fm/) — keyboard firmware for Atmel AVR and ARM controllers. The custom work here is Hans Ole Gjerdrum's keymaps for two Lily58 split keyboards.

## Build and flash commands

Source the shortcuts file first to get convenience aliases:

```bash
source shortcuts
```

**Ergomech (Lily58 with RP2040 conversion):**
```bash
ergomech-compile   # qmk compile -kb lily58 -km hansogj -e CONVERT_TO=promicro_rp2040
ergomech-deploy    # copies .uf2 to /media/hansogj/RPI-RP2/ (put keyboard in bootloader mode first)
```

**Splitkb Aurora Lily58:**
```bash
splitkb-compile    # qmk compile -kb splitkb/aurora/lily58/rev1 -km hansogj
splitkb-deploy     # qmk flash -kb splitkb/aurora/lily58/rev1 -km hansogj (waits 5s for bootloader)
```

Raw QMK CLI equivalents:
```bash
qmk compile -kb <keyboard> -km <keymap>
qmk flash -kb <keyboard> -km <keymap>
```

## Custom keymap locations

| Keyboard | Path |
|----------|------|
| Ergomech (Lily58) | `keyboards/lily58/keymaps/hansogj/` |
| Splitkb Aurora Lily58 | `keyboards/splitkb/aurora/lily58/keymaps/hansogj/` |

Both keymaps are intentionally kept in sync — changes to one typically need to be mirrored in the other.

## Keymap architecture

Both keymaps use the same 4-layer structure and identical custom keycodes:

**Layers** (defined in `enum layer_number`):
- `_QWERTY` (0) — base layer with Norwegian characters (Å/Ø/Æ)
- `_LOWER` — function keys (F1–F12), numpad, VDI window controls
- `_RAISE` — symbols, navigation (arrows/Home/End/PgUp/PgDn)
- `_ADJUST` — activated by holding LOWER+RAISE simultaneously via `update_tri_layer_state`

**Custom keycodes** (defined in `enum custom_keycodes`, starting at `SAFE_RANGE`):

| Keycode | Behavior |
|---------|----------|
| `VDI_HOME` | Exits VDI fullscreen (Ctrl+Alt+Pause), then moves to next virtual desktop |
| `LAYER_CYCLE` | Cycles through all 4 layers as the default layer |
| `VOL_TOGGLE` | Volume up; Shift+VOL_TOGGLE = volume down |
| `TILDE` | Outputs `~~` (two tildes, works around Norwegian layout dead-key) |
| `SPREAD` | Types `{...}` with cursor placed inside (JS spread template) |
| `TEMPLATE` | Types `-${}-` with cursor inside (template literal snippet) |
| `CODEMON` | Types `------\n\n------` with cursor on middle line (code separator) |
| `DOT_DOT_SLASH` | Types `../` |

**Norwegian layout note:** The keymaps include `keymap_norwegian.h`. Physical key positions map differently than US layout — `KC_LBRC` → Å, `KC_SCLN` → Ø, `KC_QUOT` → Æ, etc. `SS_RALT("7")` produces `{`, `SS_RALT("0")` produces `}`.

## Ergomech-specific: OLED display

`rules.mk` for the ergomech keymap enables OLED and pulls in custom source files from `lib/`:
- `lib/layer_state_reader.c` — shows active layer on master OLED
- `lib/keylogger.c` — shows last keypresses on master OLED
- `lib/logo_reader.c` — shows logo on secondary half OLED
- `lib/rgb_state_reader.c` — RGB status (currently unused in display)

The splitkb keymap has no `rules.mk` (uses keyboard defaults) and no OLED code.

## QMK concepts relevant to this codebase

- `process_record_user()` — called for every keypress; return `false` to consume the key, `true` to let QMK handle it
- `SEND_STRING` / `tap_code` / `register_code` + `unregister_code` — three ways to send keys in macros
- `MO(_LAYER)` — momentary layer activation (held)
- `DF(_LAYER)` — set default layer persistently
- `_______` — transparent key (falls through to lower layer)
- `LTO_ENABLE = yes` in `rules.mk` reduces firmware size; required on AVR for complex keymaps
