# Nuxroskb +84 Classic TKL

A Nuxroskb tenkeyless keyboard with ANSI/ISO, split Backspace, split right
Shift, and split left Shift support, using a 7u Tsangan bottom row. The PCB is
manufactured by HMC Studio and uses an APM32F103CBT6 MCU through the
STM32F103-compatible QMK platform, a 16 MHz external crystal, the uf2boot
bootloader, and 32 underside WS2812 RGB LEDs.

* Keyboard Maintainer: [Hiiwwy](https://github.com/Hiiwwy)
* Hardware Supported: HMC Studio +84 Classic TKL
* Hardware Availability: [Nuxroskb +84 Classic TKL](https://geekhack.org/index.php?topic=125674.0)

Make example for this keyboard (after setting up your build environment):

    make hmc/nuxroskb/plus_84_classic_tkl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in one of the following ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Double-tap the reset button on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
