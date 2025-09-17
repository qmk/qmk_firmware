# SZR35 - A 36-Key Split Keyboard 

## Introduction
The **SZR35** is a minimalist 36-key split keyboard. It follows the popular 3x5+3 layout and is aimed at users who value ergonomic typing, portability, and open-source firmware flexibility. It ships with Vial-compatible firmware and is built around an STM32 microcontroller.

## Features
- 36-key (3x5 grid + 3 thumb keys per side)
- Split ergonomic design
- USB-C connectivity on both halves
- Fully programmable with QMK and Vial
- Per-key RGB backlighting
- Vial-compatible firmware for live remapping
- STM32 DFU bootloader support

## Hardware

- **Microcontroller:** STM32F401RBT6 (Cortex-M4, 256KB Flash, 64KB RAM)
- **PCB Color:** Purple
- **Switches:** Leobog Graywood V4 Linear
- **Keycaps:** _mystery_
- **Backlighting:** Addressable RGB (WS2812 or similar)
- **Connection:** USB-C on both halves, TRS jack for interconnect

## Bootloader & Flashing Behavior

- Each half can enter DFU mode by holding a key while plugging in the USB cable. `Q` for the left, `P` for the right.
- Both halves can also enter bootloader mode by shorting the reset pads while plugging in. Useful if you flash a misbehaving firmware. The reset pads are a pair of pads with holes marked within a white rectangle. Not the ones at the edge oposing the USB connectors but about 2 or 3 centimeters from that edge.
- **Both halves must be flashed individually**, using the **same `.bin` file**.

## Photos

![SZR35 Keyboard](https://i.ibb.co/ccbnBkRq/photos.png)

## Firmware

The SZR35 comes with **QMK firmware** that supports full **Vial** functionality. This project aims to make it easy to extend or customize.

### Building the Firmware

#### Requirements

- [QMK CLI](https://docs.qmk.fm/#/newbs/getting_started)
- This code in `keyboards/szr35` inside the `qmk_firmware` folder of your QMK installation

You can verify this location by finding the `QMK_FIRMWARE` environment variable using:

```bash
qmk env
```

#### Compiling

To build the firmware using QMK CLI:

```bash
qmk setup
qmk compile -kb szr35 -km default
```

You may also create your own keymap folder (e.g. `miryoku`) and compile:

```bash
qmk compile -kb szr35 -km miryoku
```

### Flashing the Firmware

#### Requirements

- `dfu-util` installed (or use [QMK Toolbox](https://qmk.fm/toolbox/))
- Board in **DFU mode**

#### Back up the factory firmware

It's a good idea to back up the factory firmware in case you want to return to it in the future.

We can use `dfu-util` to read the microcontroller memory banks.

```bash
dfu-util --upload flash0_a.bin --alt 0 -s 0x08000000
dfu-util --upload flash0_b.bin --alt 0 -s 0x08010000
dfu-util --upload flash0_c.bin --alt 0 -s 0x08020000
```

#### Flashing via CLI

```bash
qmk flash -kb szr35 -km default
```

If you see a line like the one below, don't worry. Apparently it is a bug with `dfu-util`.

```
DFU state(10) = dfuERROR, status(10) = Device's firmware is corrupt. It cannot return to run-time (non-DFU) operations
```

### Flashing via QMK Toolbox

1. Open QMK Toolbox
2. Load your compiled `.bin` file
3. Plug in one half while holding the boot key (Q on left, P on right)
4. Toolbox should auto-detect the DFU device
5. Click “Flash”
6. Repeat 3 to 5 with the other half

### Restore the factory firmware backup

Repeat the following commands for each half in dfu mode.

```bash
dfu-util --download flash0_a.bin --alt 0 -s 0x08000000
dfu-util --download flash0_b.bin --alt 0 -s 0x08010000
dfu-util --download flash0_c.bin --alt 0 -s 0x08020000
```

## Keymap Customization

You can customize your layout by editing:

```
keyboards/szr35/keymaps/your_keymap/keymap.c
```

## RGB Led Animation Effects

You can enable or disable effects or change the default one by modifying the `rgb_matrix` section of `keyboard.json`.

## Troubleshooting

- **Only one half responds when plugged in**  
  Flash both halves individually using the same firmware. 

- **DFU device not detected**  
  Use a data-capable USB-C cable and confirm VID:PID `0483:df11` with `dfu-util -l`.

## Contributing

Contributions are welcome! You can:

- Improve the firmware
- Port the board to QMK mainline
- Clean up the code or add bootloader features 
- Add configurator, VIA, or VIAL support

Please fork and submit a pull request to make this board more accessible to the community!

## License

This project and firmware source files are subject to the terms of the [GPLv2 License](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html), in accordance with QMK and Vial licensing.

## Notes

- This project is based on [Milan Stojanovic's repo](https://github.com/milan-stoj/qmk_firmware).
- Milan thanks SZRKBD for providing the firmware source. I found the [discord forum](https://discord.com/channels/440868230475677696/1374995064962551839) where he discusses his findings. 
- The manufacturer provided firware is available [here](https://drive.google.com/file/d/11vr05nHRo689eNY6s_pMMc2oECNGn-m8/view). I think it is the same that was flashed from factory, as it has the same bugs (wrong rgb matrix) but with USB Identification "SZRKBD SZR35" instead of "Hardtochooseone SZR35" as the firware that came with my device.
- I bought this keyboard in amazon from a seller named HardToChooseOne, [here](https://www.amazon.com/gp/product/B0DD69RGHK). There is a [website](https://hardtochooseone.com). I tried to find information about SZRKBD but wasn't able to find much except other keyboards with that brand on various stores.
- This project is community driven and not affiliated with any manufacturer. It's main goal is to provide people who bought the keyboard with a way to customize and enhance it.
