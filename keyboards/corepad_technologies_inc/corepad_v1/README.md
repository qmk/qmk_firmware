# corepad v1.0

3-key macropad, Seeed XIAO RP2040, no diode matrix (direct pins), 0.91" SSD1306
OLED (128x32, I2C) showing the corepad logo.

## Pin mapping used (confirmed from schematic)

| Signal          | Header pin | XIAO name | RP2040 GPIO |
|-----------------|-----------:|-----------|-------------|
| SW1             | 11         | D10       | GP3         |
| SW2             | 10         | D9        | GP4         |
| SW3             | 9          | D8        | GP2         |
| OLED SDA        | 5          | D4        | GP6 (I2C1)  |
| OLED SCL        | 6          | D5        | GP7 (I2C1)  |

All three switches share a common GND return (as drawn) — no diodes needed
since each switch has its own dedicated GPIO.

## Folder layout (matters for this vial-qmk version)

```
corepad/
├── keyboard.json          hardware definition (pins, features, USB IDs)
├── config.h               I2C/OLED/WS2812 hardware config - NO Vial macros here
├── rules.mk                hardware build flags - NO VIA/VIAL_ENABLE here
├── lib/logo.h              OLED splash bitmap
└── keymaps/
    ├── default/
    │   └── keymap.c         plain keymap, no VIA/Vial
    └── vial/
        ├── keymap.c         same 3-key layout + OLED/RGB code
        ├── rules.mk          VIA_ENABLE / VIAL_ENABLE  <- Vial only turns on here
        ├── config.h          VIAL_KEYBOARD_UID / unlock combo
        └── vial.json         Vial GUI keyboard definition
```

This vial-qmk version rejects `VIAL_ENABLE`, `VIAL_KEYBOARD_UID`, and the
unlock-combo defines if they're placed in the keyboard-root `rules.mk`/
`config.h` ("no longer a valid option" errors) — they have to live inside
`keymaps/vial/` specifically, since only that keymap needs them.

## IMPORTANT: two different firmware trees are needed

- **VIA only** (mainline QMK, `qmk/qmk_firmware`): drop this `corepad/`
  folder into `keyboards/corepad/` in mainline QMK and build the
  `default` keymap. Mainline QMK doesn't understand `vial.json` or
  `VIAL_ENABLE` at all, but since those now live under `keymaps/vial/`
  only, building `-km default` there is unaffected.
- **Vial** (`vial-kb/vial-qmk` fork): drop this `corepad/` folder into
  `keyboards/corepad/` inside a clone of `vial-qmk`, *not* mainline QMK,
  and build the `vial` keymap. This is what you want if you're using the
  Vial GUI app.

You can't get Vial support by enabling `VIAL_ENABLE` in mainline QMK —
the Vial protocol additions live only in the vial-qmk fork.

## Build (from inside the vial-qmk clone)

```
qmk compile -kb corepad -km vial
```

Flash: hold SW1 while plugging in USB (BOOTMAGIC via SW1, matrix position
0,0) to drop into the RP2040 UF2 bootloader, then drag the resulting
`.uf2` file onto the RPI-RP2 drive that appears.

## Onboard RGB LED

The XIAO RP2040's onboard WS2812 LED (GP12) is wired up as RGB Lighting:

- **Vial GUI** exposes color/brightness/effect controls for it directly
  (Lighting tab) since `vial.json` sets `"lighting": "qmk_rgblight"`.
- **Boot-up flash**: on every power-up, it flashes red -> green -> blue ->
  white (150ms each), then settles into whatever effect/color you last saved
  from Vial. It never overwrites your saved lighting setting - the flash is
  purely a startup indicator.
- The LED sits behind a power load-switch on this board that needs GP11
  driven high before it'll light - that's handled automatically in
  `keyboard_pre_init_user()`, you don't need to do anything.

## Vial unlock combo

Hold **SW1 + SW3** together to unlock Vial's secure/reflash features from
the Vial GUI (defined in `config.h` as `VIAL_UNLOCK_COMBO_ROWS/COLS`).

## OLED logo

`lib/logo.h` contains the corepad wordmark converted to a 128x32 1-bit
bitmap (packed in SSD1306 page-column format) and is drawn full-screen as
a static splash by `oled_task_user()` in the keymap. If you'd rather it
show live keycode/layer info instead of a static logo, that's a keymap.c
change, not a hardware one — just ask.

## Notes / things worth double-checking before you flash

- Confirm your OLED module is actually 128x32 (standard for "0.91 1x
  I2C" panels) and not a 128x64 variant — if it's 128x64 the logo bitmap
  and `OLED_DISPLAY_HEIGHT`/driver settings need to change.
- `VIAL_KEYBOARD_UID` in `config.h` was randomly generated for this
  project — don't copy it into a different keyboard design, and don't
  worry about it colliding with anyone else's.
