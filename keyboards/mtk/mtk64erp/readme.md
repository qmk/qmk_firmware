# mtk/mtk64erp

![mtk/mtk64erp](https://github.com/mentako-ya/mtk64erp/blob/main/image/mtk64erp_top.jpg?raw=true)

mtk64erp is homebrew keyboard with thumb operated trackball & rotary encoder.

* Keyboard Maintainer: [mentako-ya](https://github.com/mentako-ya)
* Hardware Supported:
    MCU     : RP2040
    OLED    : SSD1306 128X64 
    Trackball sensor : PMW3389
    Encoder : EC12D
* Hardware Availability: https://jp.mercari.com/search?keyword=mentako-ya

## Firmware
https://github.com/mentako-ya/mtk64erp/blob/main/firmware/mtk_mtk64erp_via.uf2

## via.json
[mtk64erp_via.json](keymaps/via/mtk64erp_via.json)

### Source code
https://github.com/mentako-ya/qmk_firmware/keyboards/mtk/mtk64erp/

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb mtk/mtk64erp -km via

Flashing example for this keyboard:

    qmk flash -kb mtk/mtk64erp -km via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. 
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Press the reset button twice briefly
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
