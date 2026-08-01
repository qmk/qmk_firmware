# KeyCraftPro

Handwired QMK macropad: **12 keys** (4×3), **dual EC11 encoders**, **vertical SSD1306 OLED** (128×32), **Arduino Pro Micro** (ATmega32U4 / Caterina bootloader).

Based on the [Anefecious Key Craft Pro](https://makerworld.com/en/models/410460-keycraft-pro-qmk-macropad#profileId-312425) case.

| Resource | File |
|----------|------|
| Wiring diagram (verified) | [`keycraft-wiring.png`](keycraft-wiring.png) · [`keycraft-wiring.svg`](keycraft-wiring.svg) |
| Build photo | [`1.JPEG`](1.JPEG) |

This folder is a **drop-in QMK keyboard**. Copy it into any normal `qmk_firmware` checkout under `keyboards/key_craft_pro/`.

---

## What’s in this folder

```
key_craft_pro/
├── keyboard.json          # matrix pins, encoders, OLED, LAYOUT, COL2ROW
├── config.h               # encoder button pins, OLED 128×32, timeout
├── key_craft_pro.c        # OLED rotation 270°, button GPIO pull-ups
├── readme.md              # this file
├── keycraft-wiring.png    # official wiring diagram
├── keycraft-wiring.svg
├── 1.JPEG                 # finished pad photo
└── keymaps/
    ├── default/           # daily driver (Mac/Win, layers, OLED face)
    └── test/              # alphabet wiring test (keep for bring-up / debug)
```

---

## 1. Install QMK (once)

Official guide: https://docs.qmk.fm/newbs_getting_started

Typical macOS:

```bash
brew install qmk/qmk/qmk
brew tap osx-cross/avr
brew install avr-gcc@9 avrdude
# Apple Silicon example — put avr-gcc 9 on PATH:
export PATH="/opt/homebrew/opt/avr-gcc@9/bin:$PATH"

qmk setup
qmk --version
qmk doctor
```

QMK home is usually `~/qmk_firmware`.

---

## 2. Add KeyCraftPro

```bash
cp -R key_craft_pro ~/qmk_firmware/keyboards/
```

Path must be exactly:

```text
<qmk_firmware>/keyboards/key_craft_pro/
```

Keyboard id = folder name: **`key_craft_pro`**.

---

## 3. Compile

```bash
cd ~/qmk_firmware
qmk compile -kb key_craft_pro -km default   # daily driver
qmk compile -kb key_craft_pro -km test      # wiring debug
```

Hex lands at:

```text
key_craft_pro_default.hex          # also copied to QMK home
.build/key_craft_pro_default.hex
key_craft_pro_test.hex             # when building -km test
```

---

## 4. Flash (Pro Micro / Caterina)

Caterina stays in bootloader only **~2–3 seconds**. Prefer QMK Toolbox or a wait-and-flash loop.

### QMK Toolbox

1. Open [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases).
2. Load `key_craft_pro_default.hex` (or `_test.hex`).
3. Double-tap **reset** (or short **RST–GND** twice).
4. When you see `Caterina device connected: … /dev/cu.usbmodem…`, flash immediately.

### CLI

```bash
cd ~/qmk_firmware
qmk flash -kb key_craft_pro -km default
```

Manual `avrdude` while the bootloader port exists:

```bash
avrdude -p atmega32u4 -c avr109 -P /dev/cu.usbmodemXXXX \
  -U flash:w:key_craft_pro_default.hex:i
```

After a good flash, macOS shows USB product name **KeyCraftPro**.

---

## 5. Default keymap (`default`)

### Layers

Cycle with bottom-row **Prev** / **Next**:

**BASE** → **MEDIA** → **NUMS** → (wrap)

| Layer | OLED name | Purpose |
|-------|-----------|---------|
| BASE | `BASE` | Copy/paste productivity chords |
| MEDIA | `MEDIA` | Transport, volume, brightness, mic |
| NUMBERS | `NUMS` | Numpad 1–9, tap `0` / hold → BASE |

macOS shortcuts are the EEPROM default. Right encoder **click** toggles **Mac ↔ Windows** (saved).

### BASE

| | Col 0 | Col 1 | Col 2 |
|---|-------|-------|-------|
| Row 0 | Copy | Paste | Cut |
| Row 1 | Undo | Redo | Select All |
| Row 2 | Screenshot | Mission Control / Task View | App switcher |
| Row 3 | Prev layer | Jump to BASE | Next layer |

### MEDIA

| | Col 0 | Col 1 | Col 2 |
|---|-------|-------|-------|
| Row 0 | Play/Pause | Prev track | Next track |
| Row 1 | Mute | Vol − | Vol + |
| Row 2 | Mic mute chord | Brightness − | Brightness + |
| Row 3 | Prev layer | Jump to BASE | Next layer |

### NUMS (Numbers)

| | Col 0 | Col 1 | Col 2 |
|---|-------|-------|-------|
| Row 0 | 1 | 2 | 3 |
| Row 1 | 4 | 5 | 6 |
| Row 2 | 7 | 8 | 9 |
| Row 3 | Prev layer | Tap `0` · hold ~400ms → BASE | Next layer |

### Encoders

| Control | Action |
|---------|--------|
| Left rotate | Volume − / + |
| Left click | Mute (debounced) |
| Right rotate | Mouse wheel |
| Right click | Mac ↔ Windows toggle (debounced + 450ms cooldown, EEPROM) |

Encoder **buttons** are GPIO→GND (`B4` / `B5`), **not** in the key matrix. Firmware debounces them so OS toggle does not double-fire.

### Screenshot (BASE F7)

Armed for 60 seconds:

1. **First press** — start capture (`⌘⇧4` Mac / `Win+Shift+S` Windows); OLED `>SHOT`
2. **Second press** — send `Esc` to cancel; OLED `>ESC`

### OLED (vertical 128×32)

- Driver size: `#define OLED_DISPLAY_128X32` in `config.h` (**required** for this panel)
- Rotation: `OLED_ROTATION_270` in `key_craft_pro.c` (try `90` if upside down)
- Usable width when rotated: **5 characters**  
  (128×64 mode was tried; `KeyCraft` clipped to `KeyCr` and the right eye vanished — confirmed 128×32)

```text
KCPro
          ← blank gap between status rows
BASE      ← or MEDIA / NUMS
MAC       ← or WIN
>SCR+     ← last key / encoder action
...
O   O     ← slow-blink eyes (alert face after a press)
O   O
 ---      ← mouth
```

Status lines are padded to `oled_max_chars()` **without** a trailing `\n` after a full row (a full line + `\n` skips a blank row and scrambles the layout on 5-char-wide panels).

---

## 6. Debug / wiring test (`test` keymap)

Keep `keymaps/test` for bring-up and hardware debugging. It maps every switch and encoder to a unique letter so a wrong wire shows up immediately in any text field.

### Flash the test keymap

```bash
cd ~/qmk_firmware
qmk flash -kb key_craft_pro -km test
```

OLED should show `TEST` / `v2` / `A-N`.

### Expected map (front view)

```text
EncL click = A          EncR click = B

C  D  E
F  G  H
I  J  K
L  M  N

Left rotate  = O / P
Right rotate = Q / R
```

Open a blank note / TextEdit and press each control once. You should get exactly those letters — no duplicates, no missing keys.

### Debug checklist

1. **Flash `test`**, not `default`, so every input is a distinct letter.
2. **No letters at all, encoders dead too**
   - USB / Pro Micro power, reset, reflash
   - Confirm you are on `key_craft_pro`, not another keyboard id
3. **Encoders work, all matrix keys dead**
   - Diode direction wrong → must be **COL2ROW** (cathode / stripe toward **ROW**)
   - ROW2COL was tried during bring-up and made the whole matrix dead
4. **Only some keys work / wrong letters**
   - Compare the letter you get to the map above
   - Trace that switch’s ROW and COL to the Pro Micro pins in the table below
   - Remember: electrical **ROW** = physical key **column**; electrical **COL** = physical key **row**
5. **Encoder rotation wrong way**
   - Swap that encoder’s `pin_a` / `pin_b` in `keyboard.json`
6. **Encoder click does nothing**
   - Button must be GPIO → **GND** (not in matrix)
   - Pins: left `B4` (Arduino 8), right `B5` (Arduino 9)
7. **Encoder works but letters are wrong (e.g. only right encoder ghosts)**
   - Confirm **R1B = A2 (`F5`)**, **R2A = A1 (`F6`)** — do **not** wire A3
8. **OLED blank**
   - SDA = Arduino 2 (`D1`), SCL = Arduino 3 (`D0`), shared I²C address `0x3C`
   - Check `OLED_DISPLAY_128X32` and rotation
9. **When wiring looks good**
   - Reflash `default` and use the pad normally:

```bash
qmk flash -kb key_craft_pro -km default
```

### Lessons from bring-up (do not repeat)

| Mistake | Result | Fix |
|---------|--------|-----|
| Trusting old EasyEDA “back view” pinouts | Dead keys / wrong columns | Use [`keycraft-wiring.png`](keycraft-wiring.png) as source of truth |
| Diodes ROW2COL | Matrix dead | COL2ROW, stripe to ROW |
| Encoder on A3 | Wrong / ghosted encoder | Keep A2 / A1 as in the pin table |
| `OLED_DISPLAY` 128×64 on this module | Clipped text, missing right eye | Keep `OLED_DISPLAY_128X32` |
| OLED line = 5 chars **plus** `\n` | White bar, wrap garbage | Pad to width only; no extra `\n` |
| Raw GPIO encoder buttons, no debounce | OS toggle flips twice (“switches back”) | Debounce + cooldown in `default` keymap |

---

## 7. Wiring reference (Pro Micro)

| Function | Arduino | AVR |
|----------|---------|-----|
| ROW0 / ROW1 / ROW2 | 14 / 16 / 10 | `B3` / `B2` / `B6` |
| COL0 / COL1 / COL2 / COL3 | 7 / 6 / 5 / 4 | `E6` / `D7` / `C6` / `D4` |
| Left enc A / B / button | TX0 / A2 / 8 | `D3` / `F5` / `B4` |
| Right enc A / B / button | A1 / 15 / 9 | `F6` / `B1` / `B5` |
| OLED SDA / SCL | 2 / 3 | `D1` / `D0` |

Rules:

- Diodes: **COL2ROW** (cathode / stripe toward ROW)
- Encoder buttons: GPIO → GND (not in matrix); firmware enables pull-ups
- Electrical ROW = physical key **column**; electrical COL = physical key **row**
- Do not reassign encoder pins to A3

Full diagram: [`keycraft-wiring.png`](keycraft-wiring.png)

---

## 8. Troubleshooting (quick)

| Symptom | Fix |
|---------|-----|
| Keys dead, encoders work | COL2ROW diodes; flash `test` and map letters |
| Wrong key / letter | Trace ROW/COL; remember ROW↔physical column swap |
| Encoder direction reversed | Swap `pin_a` / `pin_b` in `keyboard.json` |
| OS toggle flips then snaps back | Fixed in `default` (debounce + cooldown); reflash latest |
| OLED upside down | `OLED_ROTATION_90` instead of `270` in `key_craft_pro.c` |
| OLED garbled / white bar | `OLED_DISPLAY_128X32`; ≤5 chars/line; no full-line+`\n` |
| Text clipped (`KeyCr`) / one eye missing | You are on 128×64 mode — restore `OLED_DISPLAY_128X32` |
| Flash never starts | Double-tap reset; Toolbox Auto-Flash; avoid flaky hubs |
| `avr-gcc: command not found` | `brew install avr-gcc@9` (`osx-cross/avr`) + PATH |
| Wrong folder name | Must be `keyboards/key_craft_pro` (underscore) |

---

## License

GPL-2.0-or-later (QMK). Hardware design credit: Anefecious / Key Craft Pro.
