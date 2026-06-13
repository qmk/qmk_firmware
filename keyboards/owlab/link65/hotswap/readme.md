# LINK65 - Hotswap PCB

![LINK65](https://i.imgur.com/tbeeWsph.jpeg)

A 65% keyboard made by Owlab.

* Keyboard Maintainer: [Owlab](https://github.com/owlab-git)
* Hardware Supported: LINK65 Hotswap PCB
* Hardware Availability: https://owlab.store

Make example for this keyboard (after setting up your build environment):

    make owlab/link65/hotswap:default

Flashing example for this keyboard:

    make owlab/link65/hotswap:default:flash

**Bootloader:** This PCB uses the stm32duino bootloader with firmware starting at address `0x08006000`. To enter bootloader mode, hold the `B` key while plugging in USB.

> ⚠️ **QMK Toolbox is not supported.** It flashes to the wrong address (`0x08000000`) and will overwrite the bootloader, bricking the board. Use `qmk flash` or `dfu-util` directly with `-s 0x08006000:leave`.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
