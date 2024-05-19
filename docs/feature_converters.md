# Converters

This page documents the automated process for converting keyboards to use drop-in replacement controllers. This process is designed to be easy to use and can be completed in a few simple steps.

## Supported Converters

The following converters are available at this time:

| From       | To                |
|------------|-------------------|
| `promicro` | `proton_c`        |
| `promicro` | `kb2040`          |
| `promicro` | `promicro_rp2040` |
| `promicro` | `blok`            |
| `promicro` | `bit_c_pro`       |
| `promicro` | `stemcell`        |
| `promicro` | `bonsai_c4`       |
| `promicro` | `rp2040_ce`       |
| `promicro` | `elite_pi`        |
| `promicro` | `helios`          |
| `promicro` | `liatris`         |
| `promicro` | `imera`           |
| `promicro` | `michi`           |
| `elite_c`  | `stemcell`        |
| `elite_c`  | `rp2040_ce`       |
| `elite_c`  | `elite_pi`        |
| `elite_c`  | `helios`          |
| `elite_c`  | `liatris`         |


## Overview

Each converter category is broken down by its declared `pin compatibility`. This ensures that only valid combinations are attempted. You can generate the firmware by appending `-e CONVERT_TO=<target>` to your compile/flash command. For example:

```sh
qmk flash -c -kb keebio/bdn9/rev1 -km default -e CONVERT_TO=proton_c
```

You can also add the same `CONVERT_TO=<target>` to your keymap's `rules.mk`, which will accomplish the same thing.

?> If you get errors about `PORTB/DDRB`, etc not being defined, you'll need to convert the keyboard's code to use the [GPIO Controls](gpio_control.md) that will work for both ARM and AVR. This shouldn't affect the AVR builds at all.

### Conditional Configuration

Once a converter is enabled, it exposes the `CONVERT_TO_<target_uppercase>` flag that you can use in your code with `#ifdef`s, For example:

```c
#ifdef CONVERT_TO_PROTON_C
    // Proton C code
#else
    // Pro Micro code
#endif
```

### Pin Compatibility

To ensure compatibility, provide validation, and enable future workflows, a keyboard should declare its `pin compatibility`. For legacy reasons, this is currently assumed to be `promicro`. The following pin compatibility interfaces are currently defined:

| Pin Compatibility | Notes                             |
|-------------------|-----------------------------------|
| `promicro`        | Includes RX/TX LEDs               |
| `elite_c`         | Includes bottom row pins, no LEDs |

To declare the base for conversions, add this line to your keyboard's `rules.mk`:

```makefile
PIN_COMPATIBLE = elite_c
```

## Pro Micro

If a board currently supported in QMK uses a [Pro Micro](https://www.sparkfun.com/products/12640) (or compatible board), the supported alternative controllers are:

| Device                                                                                   | Target            |
|------------------------------------------------------------------------------------------|-------------------|
| [Proton C](https://qmk.fm/proton-c/)                                                     | `proton_c`        |
| [Adafruit KB2040](https://learn.adafruit.com/adafruit-kb2040)                            | `kb2040`          |
| [SparkFun Pro Micro - RP2040](https://www.sparkfun.com/products/18288)                   | `promicro_rp2040` |
| [Blok](https://boardsource.xyz/store/628b95b494dfa308a6581622)                           | `blok`            |
| [Bit-C PRO](https://nullbits.co/bit-c-pro)                                               | `bit_c_pro`       |
| [STeMCell](https://github.com/megamind4089/STeMCell)                                     | `stemcell`        |
| [customMK Bonsai C4](https://shop.custommk.com/products/bonsai-c4-microcontroller-board) | `bonsai_c4`       |
| [Elite-Pi](https://keeb.io/products/elite-pi-usb-c-pro-micro-replacement-rp2040)         | `elite_pi`        |
| [0xCB Helios](https://keeb.supply/products/0xcb-helios)                                  | `helios`          |
| [Liatris](https://splitkb.com/products/liatris)                                          | `liatris`         |
| [Imera](https://splitkb.com/products/imera)                                              | `imera`           |
| [Michi](https://github.com/ci-bus/michi-promicro-rp2040)                                 | `michi`           |

Converter summary:

| Target            | Argument                        | `rules.mk`                   | Condition                           |
|-------------------|---------------------------------|------------------------------|-------------------------------------|
| `proton_c`        | `-e CONVERT_TO=proton_c`        | `CONVERT_TO=proton_c`        | `#ifdef CONVERT_TO_PROTON_C`        |
| `kb2040`          | `-e CONVERT_TO=kb2040`          | `CONVERT_TO=kb2040`          | `#ifdef CONVERT_TO_KB2040`          |
| `promicro_rp2040` | `-e CONVERT_TO=promicro_rp2040` | `CONVERT_TO=promicro_rp2040` | `#ifdef CONVERT_TO_PROMICRO_RP2040` |
| `blok`            | `-e CONVERT_TO=blok`            | `CONVERT_TO=blok`            | `#ifdef CONVERT_TO_BLOK`            |
| `bit_c_pro`       | `-e CONVERT_TO=bit_c_pro`       | `CONVERT_TO=bit_c_pro`       | `#ifdef CONVERT_TO_BIT_C_PRO`       |
| `stemcell`        | `-e CONVERT_TO=stemcell`        | `CONVERT_TO=stemcell`        | `#ifdef CONVERT_TO_STEMCELL`        |
| `bonsai_c4`       | `-e CONVERT_TO=bonsai_c4`       | `CONVERT_TO=bonsai_c4`       | `#ifdef CONVERT_TO_BONSAI_C4`       |
| `rp2040_ce`       | `-e CONVERT_TO=rp2040_ce`       | `CONVERT_TO=rp2040_ce`       | `#ifdef CONVERT_TO_RP2040_CE`       |
| `elite_pi`        | `-e CONVERT_TO=elite_pi`        | `CONVERT_TO=elite_pi`        | `#ifdef CONVERT_TO_ELITE_PI`        |
| `helios`          | `-e CONVERT_TO=helios`          | `CONVERT_TO=helios`          | `#ifdef CONVERT_TO_HELIOS`          |
| `liatris`         | `-e CONVERT_TO=liatris`         | `CONVERT_TO=liatris`         | `#ifdef CONVERT_TO_LIATRIS`         |
| `imera`           | `-e CONVERT_TO=imera`           | `CONVERT_TO=imera`           | `#ifdef CONVERT_TO_IMERA`           |
| `michi`           | `-e CONVERT_TO=michi`           | `CONVERT_TO=michi`           | `#ifdef CONVERT_TO_MICHI`           |

### Proton C :id=proton_c

The Proton C only has one on-board LED (C13), and by default, the TXLED (D5) is mapped to it. If you want the RXLED (B0) mapped to it instead, add this line to your `config.h`:

```c
#define CONVERT_TO_PROTON_C_RXLED
```

The following defaults are based on what has been implemented for STM32 boards.

| Feature                                      | Notes                                                                                                            |
|----------------------------------------------|------------------------------------------------------------------------------------------------------------------|
| [Audio](feature_audio.md)                    | Enabled                                                                                                          |
| [RGB Lighting](feature_rgblight.md)          | Disabled                                                                                                         |
| [Backlight](feature_backlight.md)            | Forces [task driven PWM](feature_backlight.md#software-pwm-driver) until ARM can provide automatic configuration |
| USB Host (e.g. USB-USB converter)            | Not supported (USB host code is AVR specific and is not currently supported on ARM)                              |
| [Split keyboards](feature_split_keyboard.md) | Partial - heavily dependent on enabled features                                                                  |

### Adafruit KB2040 :id=kb2040

The following defaults are based on what has been implemented for [RP2040](platformdev_rp2040.md) boards.

| Feature                                      | Notes                                                                                                            |
|----------------------------------------------|------------------------------------------------------------------------------------------------------------------|
| [RGB Lighting](feature_rgblight.md)          | Enabled via `PIO` vendor driver                                                                                  |
| [Backlight](feature_backlight.md)            | Forces [task driven PWM](feature_backlight.md#software-pwm-driver) until ARM can provide automatic configuration |
| USB Host (e.g. USB-USB converter)            | Not supported (USB host code is AVR specific and is not currently supported on ARM)                              |
| [Split keyboards](feature_split_keyboard.md) | Partial via `PIO` vendor driver - heavily dependent on enabled features                                          |

### SparkFun Pro Micro - RP2040, Blok, Bit-C PRO and Michi :id=promicro_rp2040 

Feature set is identical to [Adafruit KB2040](#kb2040).

### STeMCell :id=stemcell

Feature set currently identical to [Proton C](#proton_c).
There are two versions of STeMCell available, with different pinouts:
  - v1.0.0
  - v2.0.0 (pre-release v1.0.1, v1.0.2)
Default official firmware only supports v2.0.0 STeMCell.

STeMCell has support to swap UART and I2C pins to enable single-wire uart communication in STM chips. The following additional flags has to be used while compiling, based on the pin used for split communication:

| Split Pin | Compile flags |
|-----------|---------------|
| D3        | -e STMC_US=yes|
| D2        | Not needed    |
| D1        | -e STMC_IS=yes|
| D0        | Not needed    |

### Bonsai C4 :id=bonsai_c4

The Bonsai C4 only has one on-board LED (B2), and by default, both the Pro Micro TXLED (D5) and RXLED (B0) are mapped to it. If you want only one of them mapped, you can undefine one and redefine it to another pin by adding these line to your `config.h`:

```c
#undef B0
// If VBUS detection is unused, we can send RXLED to the Vbus detect pin instead
#define B0 PAL_LINE(GPIOA, 9)
```

### RP2040 Community Edition - Elite-Pi, Helios, and Liatris :id=rp2040_ce

Feature set is identical to [Adafruit KB2040](#kb2040). VBUS detection is enabled by default for superior split keyboard support. For more information, refer to the [Community Edition pinout](platformdev_rp2040.md#rp2040_ce) docs.


## Elite-C

If a board currently supported in QMK uses an [Elite-C](https://keeb.io/products/elite-c-low-profile-version-usb-c-pro-micro-replacement-atmega32u4), the supported alternative controllers are:

| Device                                                                           | Target            |
|----------------------------------------------------------------------------------|-------------------|
| [STeMCell](https://github.com/megamind4089/STeMCell)                             | `stemcell`        |
| [Elite-Pi](https://keeb.io/products/elite-pi-usb-c-pro-micro-replacement-rp2040) | `elite_pi`        |
| [0xCB Helios](https://keeb.supply/products/0xcb-helios)                          | `helios`          |
| [Liatris](https://splitkb.com/products/liatris)                                  | `liatris`         |

Converter summary:

| Target            | Argument                        | `rules.mk`                   | Condition                           |
|-------------------|---------------------------------|------------------------------|-------------------------------------|
| `stemcell`        | `-e CONVERT_TO=stemcell`        | `CONVERT_TO=stemcell`        | `#ifdef CONVERT_TO_STEMCELL`        |
| `rp2040_ce`       | `-e CONVERT_TO=rp2040_ce`       | `CONVERT_TO=rp2040_ce`       | `#ifdef CONVERT_TO_RP2040_CE`       |
| `elite_pi`        | `-e CONVERT_TO=elite_pi`        | `CONVERT_TO=elite_pi`        | `#ifdef CONVERT_TO_ELITE_PI`        |
| `helios`          | `-e CONVERT_TO=helios`          | `CONVERT_TO=helios`          | `#ifdef CONVERT_TO_HELIOS`          |
| `liatris`         | `-e CONVERT_TO=liatris`         | `CONVERT_TO=liatris`         | `#ifdef CONVERT_TO_LIATRIS`         |

### STeMCell :id=stemcell_elite

Identical to [Pro Micro - STeMCell](#stemcell) with support for the additional bottom row of pins.

### RP2040 Community Edition :id=rp2040_ce_elite

Identical to [Pro Micro - RP2040 Community Edition](#rp2040_ce) with support for the additional bottom row of pins.
