# 互換性のあるマイクロコントローラ

<!---
  original document: 0.9.19:docs/compatible_microcontrollers.md
  git diff 0.9.19 HEAD -- docs/compatible_microcontrollers.md | cat
-->

QMK は十分な容量のフラッシュメモリを備えた USB 対応 AVR または ARM マイクロコントローラで実行されます - 一般的に 32kB 以上ですが、ほとんどの機能を無効にすると*ほんの* 16kB に詰め込むことができます。

## Atmel AVR

以下は、USB スタックとして [LUFA](https://www.fourwalledcubicle.com/LUFA.php) を使います:

* [ATmega16U2](https://www.microchip.com/wwwproducts/en/ATmega16U2) / [ATmega32U2](https://www.microchip.com/wwwproducts/en/ATmega32U2)
* [ATmega16U4](https://www.microchip.com/wwwproducts/en/ATmega16U4) / [ATmega32U4](https://www.microchip.com/wwwproducts/en/ATmega32U4)
* [AT90USB64](https://www.microchip.com/wwwproducts/en/AT90USB646) / [AT90USB128](https://www.microchip.com/wwwproducts/en/AT90USB1286)
* [AT90USB162](https://www.microchip.com/wwwproducts/en/AT90USB162)

組み込みの USB インターフェースを持たない、いくつかの MCU は代わりに [V-USB](https://www.obdev.at/products/vusb/index.html) を使います:

* [ATmega32A](https://www.microchip.com/wwwproducts/en/ATmega32A)
* [ATmega328P](https://www.microchip.com/wwwproducts/en/ATmega328P)
* [ATmega328](https://www.microchip.com/wwwproducts/en/ATmega328)

## ARM

[ChibiOS](https://www.chibios.org) がサポートする USB 付きの ARM チップを使うこともできます。ほとんどのチップには十分な容量のフラッシュメモリがあります。動作するとわかっているのは:

### STMicroelectronics (STM32)

* [STM32F0x2](https://www.st.com/en/microcontrollers-microprocessors/stm32f0x2.html)
* [STM32F103](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html)
* [STM32F303](https://www.st.com/en/microcontrollers-microprocessors/stm32f303.html)
* [STM32F401](https://www.st.com/en/microcontrollers-microprocessors/stm32f401.html)
* [STM32F411](https://www.st.com/en/microcontrollers-microprocessors/stm32f411.html)
* [STM32F446](https://www.st.com/en/microcontrollers-microprocessors/stm32f446.html)
* [STM32G431](https://www.st.com/en/microcontrollers-microprocessors/stm32g4x1.html)
* [STM32G474](https://www.st.com/en/microcontrollers-microprocessors/stm32g4x4.html)
* [STM32L433](https://www.st.com/en/microcontrollers-microprocessors/stm32l4x3.html)
* [STM32L443](https://www.st.com/en/microcontrollers-microprocessors/stm32l4x3.html)

### NXP (Kinetis)

* [MKL26Z64](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/kl-series-cortex-m0-plus/kinetis-kl2x-72-96-mhz-usb-ultra-low-power-microcontrollers-mcus-based-on-arm-cortex-m0-plus-core:KL2x)
* [MK20DX128](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/k-series-cortex-m4/k2x-usb/kinetis-k20-50-mhz-full-speed-usb-mixed-signal-integration-microcontrollers-based-on-arm-cortex-m4-core:K20_50)
* [MK20DX256](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/k-series-cortex-m4/k2x-usb/kinetis-k20-72-mhz-full-speed-usb-mixed-signal-integration-microcontrollers-mcus-based-on-arm-cortex-m4-core:K20_72)

## Atmel ATSAM

Atmel の ATSAM マイクロコントローラの一つである、[Massdrop keyboards](https://github.com/qmk/qmk_firmware/tree/master/keyboards/massdrop) で使用されている [ATSAMD51J18A](https://www.microchip.com/wwwproducts/en/ATSAMD51J18A) には限定的なサポートがあります。
