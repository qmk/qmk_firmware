# hl6095

A 60% multi-layout keyboard (there are 95 keys in total) with 1 RGB in capslock key.
This keyboard use 25mhz HSE and STM32F411 as MCU.

- Keyboard Maintainer: https://github.com/KeyMagicHorse/qmk_firmware
- Hardware Supported: hl6095
- Hardware Availability: 
Make example for this keyboard (after setting up your build environment):
    ```
    make keymagichorse/hl6095:default
    ```
    ```
    make keymagichorse/hl6095:ble
    ```
See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
