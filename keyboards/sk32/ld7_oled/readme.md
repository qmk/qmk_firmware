# LD7 (LD7_OLED)

A 7-key macropad (one GPIO per key) with a 7-LED WS2812 strip and a 128x32
SSD1306 OLED, built around the **3Think SK32F077** Cortex-M0 MCU (registers
compatible with the STM32F072). Like the W17PAD port, this is fully native:
the SK32 platform in `lib/chibios-contrib` provides every low-level driver
(PAL, GPT, I2C, USB, EFL flash, the vendor SLED RGB peripheral and the KBCU
keyboard controller) and does **not** link any shared STM32 driver.

* Keyboard Maintainer: [NUTWANG](https://oshwhub.com/morempty)
* Hardware Supported: LD7 (3Think SK32F077, 64/128 KB)

## Bootloader

Custom **sk32duino** DFU bootloader at `0x08000000` (16 KB), VID:PID `1EAF:0003`,
the application lives at `0x08004000` and is served by **DFU alternative 2**.
Enter DFU by holding matrix key `[0][0]` (PB12) while resetting the board.

The bootloader source is maintained separately:
<https://github.com/dadato/sk32duino>.  It must be flashed once over SWD
(DAPLink/OpenOCD) before the first DFU update.

## Features

* 7 directly wired keys (KEY1..KEY7 = PB12 PB11 PB10 PB2 PB1 PB0 PC5)
* 128x32 SSD1306 OLED on I2C1 (SDA PA3 / SCL PA2, fast mode 400 kHz), with
  no-display auto-detection so the board enumerates without the OLED fitted
* RGB Matrix over WS2812 on the native SLED peripheral (7 LEDs, PC0/AF14)
* EEPROM persistence via the native wear-leveling driver on the last 2 KB flash page

## Build

```sh
qmk compile -kb sk32/ld7_oled -km default
```

See the [default keymap readme](./keymaps/default/readme.md).
