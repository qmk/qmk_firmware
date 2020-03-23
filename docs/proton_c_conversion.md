# Converting a board to use the Proton C

Since the Proton C is a drop-in replacement for a Pro Micro we've made it easy to use. This page documents a handy automated process for converting keyboards, as well as documenting the manual process if you'd like to make use of Proton C features that aren't available on Pro Micros.

## Automatic Conversion

If a board currently supported in QMK uses a Pro Micro (or compatible board) and you want to use the Proton C, you can generate the firmware by appending `CONVERT_TO_PROTON_C=yes` (or `CTPC=yes`) to your make argument, like this:

    make 40percentclub/mf68:default CTPC=yes

You can add the same argument to your keymap's `rules.mk`, which will accomplish the same thing.

This exposes the `CONVERT_TO_PROTON_C` flag that you can use in your code with `#ifdef`s, like this:

```c
#ifdef CONVERT_TO_PROTON_C
    // Proton C code
#else
    // Pro Micro code
#endif
```

If you get errors about `PORTB/DDRB`, etc not being defined, so you'll need to convert the keyboard's code to use the [GPIO Controls](internals_gpio_control.md) that will work for both ARM and AVR. This shouldn't affect the AVR builds at all.

The Proton C only has one on-board LED (C13), and by default, the TXLED (D5) is mapped to it. If you want the RXLED (B0) mapped to it instead, add this like to your `config.h`:

    #define CONVERT_TO_PROTON_C_RXLED

## Feature Conversion

These are defaults based on what has been implemented for ARM boards.

| Feature                             | Notes                                                                                                            |
|-------------------------------------|------------------------------------------------------------------------------------------------------------------|
| [Audio](feature_audio.md)           | Enabled                                                                                                          |  
| [RGB Lighting](feature_rgblight.md) | Disabled                                                                                                         |
| [Backlight](feature_backlight.md)   | Forces [task driven PWM](feature_backlight.md#software-pwm-driver) until ARM can provide automatic configuration |
| USB Host (e.g. USB-USB converter)   | Not supported (USB host code is AVR specific and is not currently supported on ARM)                              |
| [Split keyboards](feature_split_keyboard.md) | Not supported yet                                                                                       |

## Manual Conversion

To use the Proton C natively, without having to specify `CTPC=yes`, you need to change the `MCU` line in `rules.mk`:

```
MCU = STM32F303
```

Remove these variables if they exist:

* `BOOTLOADER`
* `EXTRA_FLAGS`

Finally convert all pin assignments in `config.h` to the stm32 equivalents.

| Pro Micro Left | Proton C Left | | Proton C Right | Pro Micro Right |
|-----------|----------|-|----------|-----------|
| `D3` | `A9` | | 5v | RAW (5v) |
| `D2` | `A10` | | GND | GND |
| GND | GND | | FLASH | RESET |
| GND | GND | | 3.3v | VCC <sup>1</sup> |
| `D1` | `B7` | | `A2` | `F4` |
| `D0` | `B6` | | `A1` | `F5` |
| `D4` | `B5` | | `A0` | `F6` |
| `C6` | `B4` | | `B8` | `F7` |
| `D7` | `B3` | | `B13` | `B1` |
| `E6` | `B2` | | `B14` | `B3` |
| `B4` | `B1` | | `B15` | `B2` |
| `B5` | `B0` | | `B9` | `B6` |
| `B0` (RX LED) | `C13` <sup>2</sup> | | `C13` <sup>2</sup> | `D5` (TX LED) |

You can also make use of several new pins on the extended portion of the Proton C:

| Left | | Right | 
|------|-|-------|
| `A4`<sup>3</sup> | | `B10` |
| `A5`<sup>4</sup> | | `B11` |
| `A6` | | `B12` |
| `A7` | | `A14`<sup>5</sup> (SWCLK) |
| `A8` | | `A13`<sup>5</sup> (SWDIO) |
| `A15` | | RESET<sup>6</sup> |

Notes:

1. On a Pro Micro VCC can be 3.3v or 5v.
2. A Proton C only has one onboard LED, not two like a Pro Micro. The Pro Micro has an RX LED on `D5` and a TX LED on `B0`.
3. `A4` is shared with the speaker.
4. `A5` is shared with the speaker.
5. `A13` and `A14` are used for hardware debugging (SWD). You can also use them for GPIO, but should use them last.
6. Short RESET to 3.3v (pull high) to reboot the MCU. This does not enter bootloader mode like a Pro Micro, it only resets the MCU.
