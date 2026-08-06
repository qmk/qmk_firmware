# CorePad V1

![CorePad V1](imgur.com image replace me)

A 3-key macropad built on the Seeed XIAO RP2040, with a direct (diodeless)
matrix and a 0.91" SSD1306 OLED (128x32, I2C) showing the CorePad logo.

* Keyboard Maintainer: [albertphu07](https://github.com/albertphu07)
* Hardware Supported: Seeed XIAO RP2040
* Hardware Availability: [link to where it can be bought/built]

Make example for this keyboard (after setting up your build environment):

    make corepad_technologies_inc/corepad_v1:default

Flashing example for this keyboard:

    make corepad_technologies_inc/corepad_v1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for
more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down SW1 (matrix position 0,0) and plug in the keyboard.
* **Physical reset button**: Double-tap the RESET button on the XIAO RP2040.

## Pin mapping

| Signal   | Header pin | XIAO name | RP2040 GPIO |
|----------|-----------:|-----------|-------------|
| SW1      | 11         | D10       | GP3         |
| SW2      | 10         | D9        | GP4         |
| SW3      | 9          | D8        | GP2         |
| OLED SDA | 5          | D4        | GP6 (I2C1)  |
| OLED SCL | 6          | D5        | GP7 (I2C1)  |

All three switches share a common GND return - no diodes needed since each
switch has its own dedicated GPIO.

## Onboard RGB LED

The XIAO RP2040's onboard WS2812 LED (GP12) sits behind a power load-switch
on GP11 that must be driven high before it will light. This is handled in
`keyboard_pre_init_kb()`. On every power-up it flashes red -> green -> blue
-> white (150ms each), then settles into whatever effect/color was last
saved; the flash never overwrites a saved lighting setting, it's purely a
startup indicator.
