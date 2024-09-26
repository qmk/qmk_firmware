# DE80

![deemen17/de80](https://i.imgur.com/oZvFM0G.png)

The DE80 is a portable TKL PCB that features a compact A87 form factor, dual USB Type C ports (breakable), seven JST SH 4P 1.0 ports, two FPC ports, and compatibility with both F12 and F13 footprints, making it suitable for use with a variety of TKL boards.

* Keyboard Maintainer: [Deemen17](https://github.com/Deemen17)
* Hardware Supported: DE80 R1 2024 PCB w/ STM32F103 MCU
* Hardware Availability: [Deemen17 Facebook Page](https://www.facebook.com/deemen17/), [Deemen17 Works Instagram](https://www.instagram.com/deemen17.works)

Make example for this keyboard (after setting up your build environment):

    make deemen17/de80:default

Flashing example for this keyboard:

    make deemen17/de80:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## How to flash new firmware

**Step 1:** Get the.uf2 file

**Step 2:** Enter the bootloader in 3 ways

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (ESC/Escape) and plug in the keyboard
* **Physical reset button**: Double tap the button RESET on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

**Step 3:** Flash the.uf2 file in 2 ways

A new "DEEMEN17" drive should show up for your keyboard.

* Copy and paste the uf2 file to "DEEMEN17" drive
* Simply drag and drop the UF2 file into "DEEMEN17" drive

## DE80 Hardware Information

* MCU: **STM32F103C8T6**
* Crystal: **8 Mhz**
* Caps Lock LED: **B10**
* Scroll Lock LED: **B3**
* RGB Data Pin: **B15**

### The DE80 PCB utilizes COL2ROW matrix organization.

### Column Pin Configuration

| Column | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
| -------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Pin | B14 | B13 | B12 | B2 | B1 | B0 | A7 | A6 | A5 | A4 | A3 | A2 | A1 | A0 | A15 | B7 | B6 |

### Row Pin Configuration

| Row | 0 | 1 | 2 | 3 | 4 | 5 |
| ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| Pin | A8 | A10 | A9 | B11 | C14 | C13 |
