# Converters

Since many drop-in replacement controllers now exist, we've done our best to make them easy to use in existing designs.

This page documents the handy automated process for converting keyboards.

### Supported Converters

Currently the following converters are available:

| From       | To                |
|------------|-------------------|
| `promicro` | `proton_c`        |
| `promicro` | `kb2040`          |
| `promicro` | `promicro_rp2040` |
| `promicro` | `blok`            |
| `promicro` | `bit_c_pro`       |

See below for more in depth information on each converter.

## Overview

Each converter category is broken down by its declared `pin compatibility`.
This ensures that only valid combinations are attempted.

You can generate the firmware by appending `-e CONVERT_TO=<target>` to your compile/flash command. For example:

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

## Pro Micro

If a board currently supported in QMK uses a [Pro Micro](https://www.sparkfun.com/products/12640) (or compatible board), the supported alternative controllers are:

| Device                                                                 | Target            |
|------------------------------------------------------------------------|-------------------|
| [Proton C](https://qmk.fm/proton-c/)                                   | `proton_c`        |
| [Adafruit KB2040](https://learn.adafruit.com/adafruit-kb2040)          | `kb2040`          |
| [SparkFun Pro Micro - RP2040](https://www.sparkfun.com/products/18288) | `promicro_rp2040` |
| [Blok](https://boardsource.xyz/store/628b95b494dfa308a6581622)         | `blok`            |
| [Bit-C PRO](https://nullbits.co/bit-c-pro)                             | `bit_c_pro`       |

Converter summary:

| Target            | Argument                        | `rules.mk`                   | Condition                           |
|-------------------|---------------------------------|------------------------------|-------------------------------------|
| `proton_c`        | `-e CONVERT_TO=proton_c`        | `CONVERT_TO=proton_c`        | `#ifdef CONVERT_TO_PROTON_C`        |
| `kb2040`          | `-e CONVERT_TO=kb2040`          | `CONVERT_TO=kb2040`          | `#ifdef CONVERT_TO_KB2040`          |
| `promicro_rp2040` | `-e CONVERT_TO=promicro_rp2040` | `CONVERT_TO=promicro_rp2040` | `#ifdef CONVERT_TO_PROMICRO_RP2040` |
| `blok`            | `-e CONVERT_TO=blok`            | `CONVERT_TO=blok`            | `#ifdef CONVERT_TO_BLOK`            |
| `bit_c_pro`       | `-e CONVERT_TO=bit_c_pro`       | `CONVERT_TO=bit_c_pro`       | `#ifdef CONVERT_TO_BIT_C_PRO`       |

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

### SparkFun Pro Micro - RP2040, Blok, and Bit-C PRO :id=promicro_rp2040 

Currently identical to  [Adafruit KB2040](#kb2040).
