# Quantum Mechanical Keyboard Firmware for POK3R

This repository contains keyboard firmware based on the [qmk\_firmware](http://github.com/qmk/qmk_firmware) project for a number of Holtek MCU-based keyboards. See below for supported and planned keyboards.

# Building

    make vortex/pok3r:default vortex/pok3r_rgb:default vortex/core:default

# Installation

WARNING: This firmware only works on [unlocked](https://github.com/pok3r-custom/pok3r_re_firmware/wiki/HT32-Unlocking) keyboards.
On not-unlocked keyboards, the firmware will hard fault at boot, requiring a JTAG programmer to reprogram.

    ./pok3rtool -t pok3r flash "QMK_POK3R" <path_to_qmk_pok3r>/vortex_pok3r_default.bin

## Supported Keyboards

* [Vortex POK3R](/keyboards/vortex/pok3r/)
* [Vortex POK3R RGB](/keyboards/vortex/pok3r_rgb/)
* [Vortex Core](/keyboards/vortex/core/)
* Vortex RACE3 (planned)
* Vortex ViBE (planned)
* KBP V60 (planned)
* KBP V80 (planned)
