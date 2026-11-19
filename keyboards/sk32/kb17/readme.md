# W17PAD (KB17)

A 17-key numpad built around the **3Think SK32F077**, a Cortex-M0 MCU (registers
compatible with the STM32F072).  This port is fully native: the SK32 platform in
`lib/chibios-contrib` provides every low-level driver (PAL, GPT, USART, I2C,
SPI, ADC, USB, EFL flash, the vendor SLED RGB peripheral and the KBCU keyboard
controller) and does **not** link any shared STM32 driver.

* Keyboard Maintainer: [NUTWANG](https://oshwhub.com/morempty)
* Hardware Supported: W17PAD (3Think SK32F077, 64/128 KB — SK32F077R8Q6/RBQ6 QFN64, SK32F077C8Q6/CBQ6 QFN48)

## Bootloader

Custom **sk32duino** DFU bootloader at `0x08000000` (16 KB), VID:PID `1EAF:0003`,
the application lives at `0x08004000` and is served by **DFU alternative 2**.
Enter DFU by holding matrix key `[0][0]` (PB2 * PB12) while resetting the board.

The bootloader source is maintained separately:
<https://github.com/dadato/sk32duino>.  It must be flashed once over SWD
(DAPLink/OpenOCD) before the first DFU update.

## Features

* 5x4 matrix (ROW2COL): rows `PB2 PB1 PB0 PC5 PC4`, cols `PB12 PB11 PB10 PB13`
* USB NKRO, mouse keys and system/media keys
* RGB Matrix over WS2812 on the native SLED peripheral (17 LEDs, PC0/AF14)
* VIA / dynamic keymap with per-key lighting
* EEPROM persistence via the native wear-leveling driver on the last 2 KB flash page

## Build

```sh
qmk compile -kb sk32/kb17 -km default
```

## Flash (Windows)

Enter DFU mode, then run:

```sh
dfu-util -a 2 -D .build/sk32_kb17_default.bin
```

See the [default keymap readme](./keymaps/default/readme.md).
