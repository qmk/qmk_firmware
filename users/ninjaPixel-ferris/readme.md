# ninjaPixel — Ferris Sweep userspace

A custom keymap for the **Ferris Sweep** (a 34-key column-staggered split).
It is built fresh for the Ferris rather than ported from the Sofle, because the
Sofle has roughly twice as many keys — but it follows the same structure as the
Sofle keymap in [`users/ninjaPixel/`](../ninjaPixel/): the keymap data and
shared code live here in the userspace, and a tiny wrapper keymap lives under
the keyboard.

## How it fits together

```
users/ninjaPixel-ferris/              ← this userspace (the real keymap)
├── config.h                          ← home-row-mod tuning (tapping term, etc.)
├── rules.mk                          ← compiles ninjaPixel_ferris.c
├── ninjaPixel_ferris.h               ← layer enum + shared declarations
├── ninjaPixel_ferris.c               ← shared callbacks (custom-keycode hook)
├── ninjaPixel_ferris_keymap.h        ← the `keymaps` array (all four layers)
└── readme.md                         ← you are here

keyboards/ferris/keymaps/ninjaPixel/  ← thin wrapper that the build targets
├── keymap.c                          ← #include "ninjaPixel_ferris_keymap.h"
└── rules.mk                          ← USER_NAME := ninjaPixel-ferris
```

The split exists because QMK's introspection must see the `keymaps` array inside
the keymap compilation unit, so the array is kept in a header
(`ninjaPixel_ferris_keymap.h`) that the wrapper `keymap.c` includes directly,
while everything else (callbacks, config) is shared the normal userspace way.

## Layers

Base is **Colemak-DH**. The three other layers are each held via a thumb key.

```
 ┌─────────────────────────── 0: BASE (Colemak-DH) ───────────────────────────┐
   Q       W       F       P       B         J       L       U       Y       ;
   A/GUI   R/Alt   S/Ctl   T/Sft   G         M       N/Sft   E/Ctl   I/Alt   O/GUI
   Z       X       C       D       V         K       H       ,       .       /
                   FN/Esc  NAV/Spc           SYM/Bsp Sft/Ent
   (home row = Mod-Tap: tap = letter, hold = modifier, GACS order)

 ┌──────────────────────── 1: NAV (hold left inner thumb) ────────────────────┐
   1       2       3       4       5         6       7       8       9       0
   GUI     Alt     Ctrl    Shift   `         ←       ↓       ↑       →       Del
   ·       ·       ·       ·       ·         Home    PgDn    PgUp    End     ·
   (left home row repeats the mods so you can chord Shift+Arrow, Cmd+Arrow, …)

 ┌──────────────────────── 2: SYM (hold right inner thumb) ───────────────────┐
   !       @       #       $       %         ^       &       *       (       )
   `       ~       -       _       +         =       [       ]       {       }
   |       \       /       <       >         ?       ;       :       '       "

 ┌──────────────────────── 3: FN (hold left outer thumb) ─────────────────────┐
   F1      F2      F3      F4      F5        F6      F7      F8      F9      F10
   GUI     Alt     Ctrl    Shift   F11       F12     ⏮       ⏯       ⏭       CapsWord
   BOOT    ·       ·       ·       ·         ·       Mute    Vol-    Vol+    BOOT
```

Thumb keys on the base layer (left-outer, left-inner | right-inner, right-outer):

| Thumb        | Tap        | Hold              |
|--------------|------------|-------------------|
| Left outer   | `Esc`      | **FN** layer      |
| Left inner   | `Space`    | **NAV** layer     |
| Right inner  | `Backspace`| **SYM** layer     |
| Right outer  | `Enter`    | `Shift`           |

## Build & flash

```sh
make ferris/sweep:ninjaPixel                      # compile
make ferris/sweep:ninjaPixel:avrdude-split-left   # flash LEFT half (reset it first)
make ferris/sweep:ninjaPixel:avrdude-split-right  # flash RIGHT half (reset it first)
```

(Or `QK_BOOT` on the FN layer / bootmagic to enter the bootloader — see the
wrapper readme for details.) Building requires the AVR toolchain (`avr-gcc`);
install it with `qmk setup` or your package manager if `make` reports it missing.

## Customizing

- **Don't like home-row mods?** In `ninjaPixel_ferris_keymap.h`, change the base
  home row from e.g. `LGUI_T(KC_A)` back to plain `KC_A`, and move the modifiers
  onto a layer or the thumbs. Then you can also relax the settings in `config.h`.
- **Tune the feel:** `TAPPING_TERM`, `PERMISSIVE_HOLD`, and `QUICK_TAP_TERM` in
  `config.h` control how readily a held key becomes a modifier. Comments there
  explain each one.
- **Add a layer:** add an entry to `enum ferris_layers` in `ninjaPixel_ferris.h`,
  add a matching `[_NEW] = LAYOUT(...)` block in `ninjaPixel_ferris_keymap.h`,
  and point a thumb key at it with `LT(_NEW, KC_…)` or `MO(_NEW)`.
- **Add a macro / custom keycode:** declare it in an enum in
  `ninjaPixel_ferris.h` and handle it in `process_record_user()` in
  `ninjaPixel_ferris.c` (there is a commented template there).
- **Tap dance, OS detection, Mac/Windows split, etc.:** these aren't wired up yet
  to keep the seed small — port them from `users/ninjaPixel/` when you're ready,
  remembering to enable the matching feature in the wrapper `rules.mk`.
