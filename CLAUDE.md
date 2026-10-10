This fork of QMK is for the local development of the following keyboards:
- `mechboards/sofle/pro`
- `sofle/rev1`
- `preonic/rev3_drop`
- `ferris/sweep`

The 2 sofle boards share a keymap. See the `users/ninjaPixel` directory for more information.

The sofle layout is mainly complete and the next stages of this project are to port the keymaps to the other boards.
The Ferris Sweep port lives at `keyboards/ferris/sweep/keymaps/ninjaPixel/` and is now a multi-layer layout (`_COLEMAK`, `_LAYER_PICKER`, `_NUMBERS`, `_FN_KEYS`, `_SECONDARY`), using tap dances, mod-taps, and a one-shot layer picker. A possible future step is moving it into `users/ninjaPixel/`, as the sofle boards do.
The base layout is for MacOS, using the Colemak layout. The layout is designed to also work with Windows, and there are additional layers to deal with the 
Windows operating system; these layers are mainly transparent keys (which fall through to the lower Mac layer) but some keys declare Windows-centric shortcuts / keys etc.

You should write verbose comments with any code you write .

# Hardware
## Sofle V1
- 2 x elite-c (v4) microcontroller
- ATmega32u4 controller

## Sofle Pro
- Rotary encoders
- OLED Screens
- RP2040 USB-C Controllers

## Ferris Sweep
- 34-key split: 3x5 columnar keys + 2 thumb keys per half
- Direct-pin matrix (no diodes); serial split comms on pin `D2`
- Generic **RP2040 Pro Micro** (USB-C) controllers (silkscreen "ProMicro", sold as "RP2040 Pro-Micro USB-C") — *not* a SparkFun board

### Important build / flash note
The stock `ferris/sweep` definition targets an **AVR** Pro Micro (`"development_board": "promicro"` in `keyboards/ferris/sweep/keyboard.json`), so by default it builds a `.hex` and flashes over the `caterina` serial bootloader. Our physical board is **RP2040** — it builds a `.uf2` and mounts as an `RPI-RP2` mass-storage drive (the caterina serial port never appears, so a plain `qmk flash` hangs "waiting for USB serial port").

The fix is a per-keymap `keymap.json` containing `{"converter": "rp2040_ce"}` — the "Community Edition" RP2040 Pro Micro pinout, the same converter the Sofle Pro uses. The converter remaps the AVR Pro Micro pin names (direct matrix pins + the `D2` serial pin) onto the equivalent RP2040 GPIOs. Do **not** use the deprecated `promicro_rp2040` converter — that targets the specific SparkFun board (for the Sweep the two are electrically identical, but `rp2040_ce` is the correct, non-deprecated choice).

A single `qmk flash` programs **both** halves: the Sweep defines no handedness method (no `EE_HANDS` / `SPLIT_HAND_PIN`), so QMK's default runtime handedness lets one firmware image serve both sides — unlike the Sofle, which is flashed per-half.
