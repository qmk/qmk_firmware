# Pretty Paddy — Window Management Keymap

**Board:** Idyllic Pizza Pad (sold by MechStock AU as "Pretty Paddy")
**QMK path:** `keyboards/idyllic/pizzapad`
**MCU:** Seeed XIAO RP2040
**Layout:** 3×3 ortho (9 keys)

---

## Concept

All 9 keys map to window management commands in **Raycast** on macOS. Every key has a tap action. Seven of the nine keys also act as chord anchors — hold one, tap another to send a different command.

- **Tap** — sends a keycode directly to Raycast
- **Chord (hold anchor + tap target)** — holding an anchor key activates a layer; tapping a second key sends the chord output

Chords use `LT()` (Layer-Tap) with `HOLD_ON_OTHER_KEY_PRESS` and `PERMISSIVE_HOLD` so the hold registers the instant a second key is pressed.

---

## Physical Layout

```
[ K0 ] [ K1 ] [ K2 ]
[ K3 ] [ K4 ] [ K5 ]
[ K6 ] [ K7 ] [ K8 ]
```

---

## Base Layer — Taps

| Key | Output | Raycast target |
|-----|--------|----------------|
| K0 | Hyper+1 | Top-Left Sixth |
| K1 | Hyper+2 | Top-Center Sixth |
| K2 | Hyper+3 | Top-Right Sixth |
| K3 | F18 | Left Third |
| K4 | Hyper+5 | Center Third | (plain key — no hold) |
| K5 | F19 | Right Third |
| K6 | Hyper+7 | Bottom-Left Sixth |
| K7 | Hyper+8 | Bottom-Center Sixth |
| K8 | Hyper+9 | Bottom-Right Sixth |

---

## Chords — Hold + Tap

### Hold K3 (left anchor)

| Chord | Output | Raycast target |
|-------|--------|----------------|
| K3 + K1 | Hyper+0 | Top Half |
| K3 + K4 | F13 | Left Two-Thirds |
| K3 + K5 | Hyper+Return | Full Screen |
| K3 + K7 | F16 | Bottom Half |

### Hold K5 (right anchor)

| Chord | Output | Raycast target |
|-------|--------|----------------|
| K5 + K3 | Hyper+Return | Full Screen |
| K5 + K4 | F20 | Right Two-Thirds |

### Hold K0 or K2 (top-row anchors, shared layer)

| Chord | Output | Raycast target |
|-------|--------|----------------|
| K0 + K2 | Hyper+0 | Top Half |
| K2 + K0 | Hyper+0 | Top Half |

### Hold K6 or K8 (bottom-row anchors, shared layer)

| Chord | Output | Raycast target |
|-------|--------|----------------|
| K6 + K8 | F16 | Bottom Half |
| K8 + K6 | F16 | Bottom Half |

---

## Raycast Setup

Open **Raycast → Extensions → Window Management**, click a shortcut field, and trigger the key or chord on the pad — Raycast detects the keycode automatically.

| Raycast action | Shortcut | Trigger |
|----------------|----------|---------|
| Top-Left Sixth | Hyper+1 | Tap K0 |
| Top-Center Sixth | Hyper+2 | Tap K1 |
| Top-Right Sixth | Hyper+3 | Tap K2 |
| Left Third | F18 | Tap K3 |
| Center Third | Hyper+5 | Tap K4 |
| Right Third | F19 | Tap K5 |
| Bottom-Left Sixth | Hyper+7 | Tap K6 |
| Bottom-Center Sixth | Hyper+8 | Tap K7 |
| Bottom-Right Sixth | Hyper+9 | Tap K8 |
| Top Half | Hyper+0 | K3+K1 · K0+K2 · K2+K0 |
| Bottom Half | F16 | K3+K7 · K6+K8 · K8+K6 |
| Left Two-Thirds | F13 | K3+K4 |
| Right Two-Thirds | F20 | K5+K4 |
| Full Screen | Hyper+Return | K3+K5 · K5+K3 |

> **Hyper** = Ctrl+Shift+Alt+Cmd.

---

## Build & Flash

```bash
# Compile
qmk compile -kb idyllic/pizzapad -km matt

# Flash (enter bootloader first)
qmk flash -kb idyllic/pizzapad -km matt
```

### Entering bootloader (Seeed XIAO RP2040)

1. **Bootmagic** — hold **K0** while plugging in USB-C → board mounts as `RPI-RP2`
2. **Physical buttons** — with USB connected, press **BOOT + RESET** simultaneously
3. **Keycode** — map `QK_BOOT` to a key and press it

### Restore to default

`_backups/idyllic_pizzapad_default_RESTORE.uf2` — enter bootloader and drag onto `RPI-RP2`.

---

## Implementation Notes

### LT() + HYPR() incompatibility
`LT()` only accepts basic keycodes (≤ 0xFF) as the tap action. `HYPR(KC_x)` is a modifier-stacked keycode and gets silently stripped to a bare keycode. Keys that need to tap `HYPR+something` use an inert placeholder keycode inside `LT()`, overridden in `process_record_user()`.

| Key | Placeholder | Tap output |
|-----|-------------|------------|
| K0 | KC_F22 | Hyper+1 |
| K2 | KC_F23 | Hyper+3 |
| K6 | KC_F24 | Hyper+7 |
| K8 | KC_SCRL | Hyper+9 |

K3/K5 tap to plain F-keys (F18/F19) — no workaround needed. K1/K4/K7 are plain keys.

### Shared layers for symmetric pairs
K0 and K2 share `_TOP_HOLD`; K6 and K8 share `_BOT_HOLD`. Sharing is intentional: with `HOLD_ON_OTHER_KEY_PRESS`, if both keys target the same layer, the second key pressing doesn't activate a *new* layer — it's a no-op since that layer is already active. This prevents the second key from becoming a conflicting anchor. Separate layers caused K2 to also register as held when K0 was held, preventing any keycode from firing.

### Avoided F-keys
| F-key | Reason avoided |
|-------|---------------|
| F14 | Brightness down (macOS) |
| F15 | Brightness up (macOS) |
| F17 | Brightness (macOS, some configs) |
| F21+ | Not recognised by Raycast as recordable hotkeys |

### Layers (5 total)
| Layer | Name | Trigger |
|-------|------|---------|
| 0 | `_BASE` | Always active |
| 1 | `_LEFT_HOLD` | Hold K3 |
| 2 | `_RIGHT_HOLD` | Hold K5 |
| 3 | `_TOP_HOLD` | Hold K0 or K2 |
| 4 | `_BOT_HOLD` | Hold K6 or K8 |

### config.h
- `HOLD_ON_OTHER_KEY_PRESS` — registers hold the instant another key is pressed
- `PERMISSIVE_HOLD` — also registers hold if another key is pressed and released while the LT() key is down
