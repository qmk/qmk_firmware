# Dactyl Manuform 6x6 — `mquentin` keymap

French AZERTY layout for the handwired Dactyl Manuform 6x6 (Pro Micro / ATmega32u4).

## Compile

```
qmk compile -kb handwired/dactyl_manuform/6x6 -km mquentin
```

## Flash

### Manually (qmk CLI)

```
qmk flash -kb handwired/dactyl_manuform/6x6 -km mquentin
```

Then reset the board (see [To reset](#to-reset)).

### QMK Toolbox

**If not installed:**

1. `brew install --cask qmk-toolbox`
2. Enable it in macOS security (Apple's intended GUI path):
   1. System Settings → Privacy & Security.
   2. Scroll to the Security section — you'll see "QMK Toolbox was blocked to protect your Mac." with an **Open Anyway** button (it appears only after you've tried to open the app once).
   3. Click **Open Anyway** and authenticate with Touch ID / password.
   4. Launch again; if it prompts once more, click **Open Anyway**.
3. Run it.

**If already installed:**

1. Run it.
2. Load the compiled hex file `handwired_dactyl_manuform_6x6_promicro_mquentin.hex` (in the repo root).
3. Pick the **atmega32u4** processor (cf. `keyboards/handwired/dactyl_manuform/6x6/promicro/keyboard.json`).
4. Reset the board.
5. Click **Flash**.

![Screenshot 2024-09-17 at 13 02 43](https://github.com/user-attachments/assets/04d2a01a-2a45-474e-b7f4-aad5498d784f)

## Mouse layer

Hold the **left-thumb Enter** (`ENT_MOUSE = LT(MOUSE, KC_ENTER)` — a tap still types Enter) to turn the right hand into a mouse. Movement lives in two spots at once: the home-row `I J K L` inverted-T, and the right-thumb keys that sit exactly where your arrow keys are.

```text
              ╔═══════════════════════════════════════════════╗
              ║  MOUSE layer — hold the LEFT-THUMB Enter (⏎)   ║
              ╚═══════════════════════════════════════════════╝

  LEFT HAND · speed                 RIGHT HAND · move / scroll / click
  (hold while moving)
                                              ┌─────┐
                                              │  I  │  ▲ up
                                        ┌─────┼─────┼─────┐
   ┌─────┬─────┬─────┐                  │  J  │  K  │  L  │
   │  S  │  D  │  F  │                  │ ◀   │  ▼  │   ▶ │
   │ACL2 │ACL1 │ACL0 │                  └─────┴─────┴─────┘
   │fast │ med │slow │                    left  down  right
   └─────┴─────┴─────┘
                                   wheel:   U ▲    O ▼    , ◀    : ▶

              RIGHT THUMB                arrows = 2nd move cluster,
              ┌─────┬─────┐              same layout as your arrow keys
              │  ▲  │  ▶  │
              ├─────┼─────┤              Bksp  = left   click
              │  ◀  │  ▼  │              Enter = right  click
              └─────┴─────┘              RAlt  = middle click
```

- **Move**: `I`=up, `J`=left, `K`=down, `L`=right (home row) — or the right-thumb arrows.
- **Scroll**: `U`/`O` = wheel up/down, `,`/`:` = wheel left/right.
- **Click**: right thumb — `Bksp` left, `Enter` right, `RAlt` middle.
- **Speed** (live, hold while moving): left home row `S`/`D`/`F` = fast / medium / slow (`MS_ACL2`/`1`/`0`).

## To reset

With the current layout, to reset: press and hold `ESC_RSTA`, then `KC_ENTER`, then `KC_LGUI`.

![PXL_20240917_105940414~2](https://github.com/user-attachments/assets/96e63271-b1fd-4585-aab9-2037f34e923a)

## Scan rate (refresh rate)

Measured **~1124 Hz**, steady, with both halves linked (default split serial speed). That's already above the 1000 Hz USB report rate, so the matrix scan is **not** the bottleneck — there's no practical gain from pushing it higher. Debounce uses the eager `sym_eager_pk` algorithm (registers on the first edge, ~0 added latency).

Notes:

- Both halves **must run identical firmware** — the split serial timing has to match. Flashing only one half breaks the link (constant `Failed to execute slave_matrix`).
- `SELECT_SOFT_SERIAL_SPEED 0` (faster serial) broke the half-to-half link on this handwired build, so it's left disabled in `config.h`.

To measure it yourself, temporarily add:

- `#define DEBUG_MATRIX_SCAN_RATE` to `config.h`
- `CONSOLE_ENABLE = yes` to `rules.mk`
- `void keyboard_post_init_user(void) { debug_enable = true; }` to `keymap.c`

(the rate prints via `dprintf`, which needs runtime debug enabled — and this keymap has no Right Shift to toggle it via the Command feature). Then run `qmk console` and watch the `matrix scan frequency:` lines. Remove all three afterwards.
