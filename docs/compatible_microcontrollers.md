# Compatible Microcontrollers

QMK runs on any USB-capable AVR or ARM microcontroller with enough flash space - generally 32kB or more, though it will *just* squeeze into 16kB with most features disabled.

## Atmel AVR

The following use [LUFA](https://www.fourwalledcubicle.com/LUFA.php) as the USB stack:

* [ATmega16U2](https://www.microchip.com/wwwproducts/en/ATmega16U2) / [ATmega32U2](https://www.microchip.com/wwwproducts/en/ATmega32U2)
* [ATmega16U4](https://www.microchip.com/wwwproducts/en/ATmega16U4) / [ATmega32U4](https://www.microchip.com/wwwproducts/en/ATmega32U4)
* [AT90USB64](https://www.microchip.com/wwwproducts/en/AT90USB646) / [AT90USB128](https://www.microchip.com/wwwproducts/en/AT90USB1286)

Certain MCUs which do not have native USB will use [V-USB](https://www.obdev.at/products/vusb/index.html) instead:

* [ATmega32A](https://www.microchip.com/wwwproducts/en/ATmega32A)
* [ATmega328P](https://www.microchip.com/wwwproducts/en/ATmega328P)
* [ATmega328](https://www.microchip.com/wwwproducts/en/ATmega328)

## ARM

You can also use any ARM chip with USB that [ChibiOS](http://www.chibios.org) supports. Most have plenty of flash. Known to work are:

### STMicroelectronics (STM32)

 * [STM32F0x2](https://www.st.com/en/microcontrollers-microprocessors/stm32f0x2.html)
 * [STM32F103](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html)
 * [STM32F303](https://www.st.com/en/microcontrollers-microprocessors/stm32f303.html)

### NXP (Kinetis)

 * [MKL26Z64](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/kl-series-cortex-m0-plus/kinetis-kl2x-72-96-mhz-usb-ultra-low-power-microcontrollers-mcus-based-on-arm-cortex-m0-plus-core:KL2x)
 * [MK20DX128](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/k-series-cortex-m4/k2x-usb/kinetis-k20-50-mhz-full-speed-usb-mixed-signal-integration-microcontrollers-based-on-arm-cortex-m4-core:K20_50)
 * [MK20DX256](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/k-series-cortex-m4/k2x-usb/kinetis-k20-72-mhz-full-speed-usb-mixed-signal-integration-microcontrollers-mcus-based-on-arm-cortex-m4-core:K20_72)

## Atmel ATSAM

There is limited support for one of Atmel's ATSAM microcontrollers, that being the [ATSAMD51J18A](https://www.microchip.com/wwwproducts/en/ATSAMD51J18A) used by the [Massdrop keyboards](https://github.com/qmk/qmk_firmware/tree/master/keyboards/massdrop).
