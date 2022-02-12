# Keyball61

![Keyball61](https://raw.githubusercontent.com/Yowkees/keyball/f24aaa449eee3eb635794630aac0181600e94af0/keyball61/doc/rev1/images/kb61_001.jpg)

A split keyboard with 61 vertically staggered keys and 34mm track ball.

* Keyboard Maintainer: [@Yowkees](https://twitter.com/Yowkees)
* Hardware Supported: Keyball61 PCB, ProMicro
* Hardware Availability:
  * <https://shirogane-lab.com/>

Make example for this keyboard (after setting up your build environment):

    make keyball/keyball61:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Special keycodes

Keycode    |Description
-----------|------------------------------------------------------------------
`KBC_RST`  |Reset Keyball configuration
`KBC_SAVE` |Persist Keyball configuration to EEPROM
`CPI_I100` |Increase 100 CPI (max 12000)
`CPI_I1K`  |Increase 1000 CPI (max 12000)
`CPI_D100` |Decrease 100 CPI (min 100)
`CPI_D1K`  |Decrease 1000 CPI (min 100)
`SCRL_TO`  |Toggle scroll mode
`SCRL_MO`  |Enable scroll mode when pressing
`SCRL_DVI` |Increase scroll divider (max 7 = 1/128)
`SCRL_DVD` |Decrease scroll divider (min 0 = 1/1)
