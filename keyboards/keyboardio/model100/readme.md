# Keyboardio Model 100

A split keyboard.

* Keyboard Maintainer: QMK Community
* Hardware Supported: Keyboardio Model 100
* Hardware Availability: [Keyboardio](https://shop.keyboard.io)

Make example for this keyboard (after setting up your build environment):

    make keyboardio/model100:default

Flashing example for this keyboard:

    make keyboardio/model100:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The Model 100 ships Keyboardio's DAPBoot DFU bootloader. To enter it, press the
`Prog` key (upper left) or hold it while plugging the keyboard in.

DAPBoot reserves the first 8 KB of flash and expects the application's vector
table at `0x08002000`. We link there by naming the stm32duino offset linker
script (`MCU_LDSCRIPT = STM32F103x8_stm32duino` in `rules.mk`) while declaring
`"board": "STM32_F103_STM32DUINO"` in `keyboard.json` — rather than setting
`"bootloader": "stm32duino"`, which would force the Maple-default DFU
identifiers and clobber ours.

In DFU mode the Model 100 enumerates as `3496:0005` (the application enumerates
as `3496:0006`), so `rules.mk` sets `DFU_ARGS`/`DFU_SUFFIX_ARGS` accordingly.
DAPBoot is a plain-DFU (non-DfuSe) bootloader, so it takes no `-s <addr>`
specifier; `make keyboardio/model100:default:flash` drives dfu-util as:

    dfu-util -d 3496:0005 -a 0 -R -D <firmware>.bin

It is *very* hard to brick a Model 100 short of overwriting the bootloader
region itself, which requires specialised hardware, so experimentation is safe.

> **Note:** software-triggered bootloader entry via `QK_BOOT` issues
> `NVIC_SystemReset()`; DAPBoot has its own entry condition, so a bare reset is
> not guaranteed to drop into DFU. The physical `Prog`-key method (hold while
> plugging in) is the reliable fallback.

## Porting notes

The Model 100 is architecturally almost identical to the Model 01: both halves
are ATtiny key scanners that the main MCU talks to over I2C, using the same wire
protocol (`wire-protocol-constants.h`), the same scanner addresses, and the same
64-LED (4 banks x 8, per hand) layout.

What differs is the **main MCU**:

| Function              | Model 01 (ATmega32U4) | Model 100 (GD32F303CG) |
| --------------------- | --------------------- | ---------------------- |
| MCU family            | AVR                   | ARM Cortex-M4          |
| Scanner power enable  | `C7`, push-pull, HIGH | `B9`, open-drain, LOW  |
| Power-sense inputs    | `B4`                  | `B14`, `B15`           |
| I2C to scanners       | AVR TWI               | I2C1 = `B6` / `B7`     |
| USB D+ pull-up        | built-in              | GPIO `A8` (active-high)|

The GD32F303 is register-compatible enough with the STM32F103 high-density line
that ChibiOS's existing STM32F1 HAL drives it. We build it as `STM32F103` with
`board.h` selecting the high-density (`STM32F103xE`) variant, following the
precedent set by `keyboards/mlego/m65/rev2`. No dedicated GD32 ChibiOS port is
needed (the in-tree `GD32VF103` support is the unrelated RISC-V part).

Three Model-100-specific details were needed to bring it up on real hardware:

* **Clock:** the board has no usable HSE crystal (its DAPBoot runs on HSI), so
  `mcuconf.h` runs the MCU from the internal HSI oscillator (HSI/2 x 12 = 48 MHz
  sysclk, giving a valid 48 MHz USB clock). A stock HSE config hangs at boot
  waiting for `HSERDY`.
* **USB pull-up:** the D+ pull-up is gated by GPIO `A8` (active-high), not a
  fixed resistor, so `board.h` overrides `usb_lld_connect_bus`/`disconnect_bus`
  to drive `A8`. Without it the host never sees the device.
* **Scanner I2C:** ChibiOS's STM32 I2C driver is DMA-based and does not work on
  the GD32's I2C peripheral, so `matrix.c` drives I2C1 with a small polled
  (register-level) implementation, which `leds.c` shares via `i2c_poll_write()`.

Pin assignments and the DFU/HSI/pull-up details were taken from the Kaleidoscope
Model 100 hardware plugin (`kaleidoscope/device/keyboardio/Model100.cpp`), the
`ArduinoCore-GD32-Keyboardio` `keyboardio_model_100` variant, and Keyboardio's
DAPBoot fork (`gd32-bootloader-dfu-dapboot`).

The `Prog` key is at matrix `[0, 7]` (upper left), the same position as on the
Model 01, and the default keymap places `QK_BOOT` there.

## Features

This implements the standard keymap, including mousekeys.

It doesn't do cursor warping - QMK does not support absolute mouse positioning.

RGB matrix is supported (per-key, both hands). LED colour data is sent to the
scanners bank-by-bank, interleaved between the two hands to avoid overrunning
the ATtiny controllers. Gamma compensation and the hardware's high-speed batch
LED update functions are not implemented.
