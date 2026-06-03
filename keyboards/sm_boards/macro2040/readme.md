# SM Boards Macro2040

![SM Boards Macro2040](https://raw.githubusercontent.com/sjb-dev/MacroPad/Macro2040_version_1/Macro2040.jpg)

A 7-key macropad with a magnetic rotary encoder, RGB lighting and a small OLED display, powered by an RP2040.

* Keyboard Maintainer: [sjb-dev](https://github.com/sjb-dev)
* Hardware Supported: SM Boards Macro2040 PCB
* Hardware Availability: [github.com/sjb-dev/MacroPad](https://github.com/sjb-dev/MacroPad)

## Features

* **MCU**: Raspberry Pi RP2040 (dual-core ARM Cortex-M0+)
* **Keys**: 6 hot-swap mechanical switches (SW3..SW8) plus a small tactile button (SW9)
* **Encoder**: AS5600 magnetic rotary encoder (contactless, infinite rotation) on I2C0
* **RGB Lighting**: 7 × WS2812B per-key/underglow LEDs on GP17 (via level shifter), 44 RGB Matrix animations enabled
* **Switch indicator LEDs**: 6 blue LEDs embedded in the switches, driven by 2 NPN transistors (GP12 / GP13)
* **User LED**: 1 blue LED (D6) on GP25 used as a "device alive" / layer-change blink indicator
* **OLED**: SSD1306 0.91" 128 × 32 display on I2C1 (custom driver — see `oled_custom.c`)
* **Connectivity**: USB-C 2.0
* **Firmware**: QMK with VIA support

## Layout

```
+---------+---+---+---+
|         |SW3|SW5|SW7|
| ENCODER +---+---+---+
|         |SW4|SW6|SW8|
+---+-----+---+---+---+
|SW9|
+---+
```

* SW3..SW8 form the 2×3 main key matrix.
* SW9 is a small tactile button. The default keymap binds it to a layer-cycle (`TO()` chain).

## Keymap

The included `default` keymap is a minimal 4-layer keymap (media / editing / zoom / navigation). SW9 cycles layers with standard `TO()` keycodes. No VIA, no custom keycodes. The keyboard-level OLED shows board name + active layer + the last-pressed key's label.

A VIA-remappable variant is maintained in the [VIA QMK Userspace](https://github.com/the-via/qmk_userspace_via). A full-featured variant with on-board games and a Pomodoro timer lives in the maintainer's repo at [github.com/sjb-dev/MacroPad](https://github.com/sjb-dev/MacroPad).

## Compiling and Flashing

```
make sm_boards/macro2040:default      # add :flash to flash after build
```

## Bootloader

Enter the bootloader in any of these ways:

* **Bootmagic reset**: Hold SW3 (matrix `[0,0]`) and plug in the keyboard
* **Physical reset**: Hold the BOOT button on the PCB and press the RESET button
* **Keycode**: Press a key bound to `QK_BOOT` if you have one in your layout

## Architecture notes

The board ships with several **keyboard-level** files (in `keyboards/sm_boards/macro2040/`) so every keymap gets a working knob, OLED and matrix for free:

* **`matrix.c`** — overrides QMK's default `matrix_read_cols_on_row()` with a copy that adds `wait_us(100)` between driving a row LOW and reading the columns. The RP2040 default `GPIO_INPUT_PIN_DELAY` is only ~250 ns, which is too short for row 3 (GP11) on this PCB to settle — without this override, SW9 is never detected.
* **`macro2040.c`** — reads the AS5600 angle over I2C0 and synthesises A/B quadrature pulses on GP20 / GP21, which are physically wired back to the encoder input pins GP22 / GP23. QMK's standard encoder driver then sees them like any other encoder. The same file initialises the OLED and renders a basic *board + layer + last-key label* view; keymaps that define their own `housekeeping_task_user()` re-render on top.
* **`oled_custom.c` / `.h`** — small SSD1306 driver on I2C1. We don't use QMK's built-in OLED feature because it would have to share `i2c_master`'s bus with the AS5600.
* **`keycode_label.c` / `.h`** — shared "keycode → short readable label" helper used by the basic OLED renderer; keymaps can override `keycode_label_user()` (weak default) to label custom keycodes.

I²C bus assignments:

* **I2C0** (GP4 / GP5) — owned by QMK's `i2c_master`; talks to the AS5600 magnetic encoder.
* **I2C1** (GP18 / GP19) — owned by `oled_custom.c`; drives the SSD1306 OLED.

See the [QMK build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more.
