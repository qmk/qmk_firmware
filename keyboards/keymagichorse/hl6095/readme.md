  # HL6095

  A 60% mechanical keyboard with Tsangan bottom row layout, using STM32F411 MCU.

  * Keyboard Maintainer: [KeyMagicHorse](https://github.com/JohnLiu-cloud/qmk_firmware_jh)
  * Hardware Supported: HL6095 (wired version, STM32F411)
  * Hardware Availability: [keymagichorse.com](https://github.com/JohnLiu-cloud/qmk_firmware_jhm)

  Make example for this keyboard (after setting up your build environment):

      make keymagichorse/hl6095:default

  Flashing example for this keyboard:

      make keymagichorse/hl6095:default:flash


  ## Bootloader

  Enter the bootloader in 3 ways:

  * **Bootmagic reset**: Hold down the Escape key and plug in the keyboard
  * **Physical reset button**: Press the reset button on the PCB
  * **Keycode in layout**: Press the key mapped to `QK_BOOT` if available

