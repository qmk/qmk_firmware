# SM Boards Macro2040

![SM Boards Macro2040](https://raw.githubusercontent.com/samuelmara/Macro2040_V1/main/images/macro2040.jpg)

A 7-key macropad with a magnetic rotary encoder, RGB lighting and a small OLED display, powered by an RP2040.

* Keyboard Maintainer: [sjb-dev](https://github.com/sjb-dev)
* Hardware Supported: SM Boards Macro2040 PCB
* Hardware Availability: [github.com/samuelmara/Macro2040_V1](https://github.com/samuelmara/Macro2040_V1)

## Features

* **MCU**: Raspberry Pi RP2040 (dual-core ARM Cortex-M0+)
* **Keys**: 6 hot-swap mechanical switches (SW3..SW8) plus a small tactile button (SW9)
* **Encoder**: AS5600 magnetic rotary encoder (contactless, infinite rotation) on I2C0
* **RGB Lighting**: 7 × WS2812B per-key/underglow LEDs on GP17 (via level shifter), 43 RGB Matrix animations enabled
* **Switch indicator LEDs**: 6 blue LEDs embedded in the switches, driven by 2 NPN transistors (GP12 / GP13)
* **User LED**: 1 blue LED (D6) on GP25, lit as a "device alive" indicator
* **OLED**: SSD1306 0.91" 128 × 32 display on I2C1 (QMK core OLED driver)
* **Connectivity**: USB-C 2.0
* **Firmware**: QMK

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

## Compiling and Flashing

Make example for this keyboard (after setting up your build environment):

    make sm_boards/macro2040:default

Flashing example for this keyboard:

    make sm_boards/macro2040:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in any of these ways:

* **Bootmagic reset**: Hold SW3 (matrix `[0,0]`) and plug in the keyboard
* **Physical reset**: Hold the BOOT button on the PCB and press the RESET button
* **Keycode**: Press a key bound to `QK_BOOT` if you have one in your layout

## Architecture notes

A small amount of keyboard-level glue in `macro2040.c` gives every keymap a working knob, OLED and indicator LEDs for free:

* **AS5600 encoder** — the rotary control is a magnetic angle sensor, not a quadrature encoder. `macro2040.c` reads its angle over I2C0 using the ChibiOS I2C API and synthesises A/B quadrature pulses on GP20 / GP21, which are wired back to the encoder input pins GP22 / GP23, so QMK's standard encoder driver sees a normal encoder.
* **OLED** — uses QMK's core SSD1306 driver on I2C1. `oled_task_kb()` draws a basic *board + layer + last-key* view; keymaps can override `oled_task_user()` to draw their own UI.
* **Matrix timing** — `matrix_output_select_delay()` adds a 100 µs settle delay after selecting a row, because the RP2040 default (~250 ns) is too short for the row 3 (GP11) trace on this PCB; without it SW9 is never detected.
* **Indicator LEDs** — the blue switch-LED columns (GP13 / GP12) and the D6 user LED (GP25) are switched on at the keyboard level.

I²C bus assignments:

* **I2C0** (GP4 / GP5) — AS5600 magnetic encoder, driven directly via the ChibiOS I2C API.
* **I2C1** (GP18 / GP19) — SSD1306 OLED, via QMK's core OLED driver.
