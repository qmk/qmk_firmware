# Compatible Microcontrollers

QMK runs on any USB-capable AVR or ARM microcontroller with enough flash space - generally 32kB+ for AVR, and 64kB+ for ARM. With significant disabling of features, QMK may *just* squeeze into 16kB AVR MCUs.

Features within QMK may or may not be compatible with every microcontroller.

## Atmel AVR

The following use [LUFA](https://www.fourwalledcubicle.com/LUFA.php) as the USB stack:

* [ATmega16U2](https://www.microchip.com/wwwproducts/en/ATmega16U2) / [ATmega32U2](https://www.microchip.com/wwwproducts/en/ATmega32U2)
* [ATmega16U4](https://www.microchip.com/wwwproducts/en/ATmega16U4) / [ATmega32U4](https://www.microchip.com/wwwproducts/en/ATmega32U4)
  * SparkFun Pro Micro (and clones)
  * PJRC Teensy 2.0
  * Adafruit Feather 32U4
* [AT90USB64](https://www.microchip.com/wwwproducts/en/AT90USB646) / [AT90USB128](https://www.microchip.com/wwwproducts/en/AT90USB1286)
  * PJRC Teensy++ 2.0
* [AT90USB162](https://www.microchip.com/wwwproducts/en/AT90USB162)

Certain MCUs which do not have native USB will use [V-USB](https://www.obdev.at/products/vusb/index.html) instead:

* [ATmega32A](https://www.microchip.com/wwwproducts/en/ATmega32A)
* [ATmega328P](https://www.microchip.com/wwwproducts/en/ATmega328P)
* [ATmega328](https://www.microchip.com/wwwproducts/en/ATmega328)

## ARM

You can also use any ARM chip with USB that [ChibiOS](https://www.chibios.org) supports. Most have plenty of flash. Known to work are:

### STMicroelectronics (STM32)

 * [STM32F0x2](https://www.st.com/en/microcontrollers-microprocessors/stm32f0x2.html)
 * [STM32F103](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html)
   * Bluepill (with STM32duino bootloader)
 * [STM32F303](https://www.st.com/en/microcontrollers-microprocessors/stm32f303.html)
   * QMK Proton-C
 * [STM32F401](https://www.st.com/en/microcontrollers-microprocessors/stm32f401.html)
   * WeAct Blackpill
 * [STM32F405](https://www.st.com/en/microcontrollers-microprocessors/stm32f405-415.html)
 * [STM32F407](https://www.st.com/en/microcontrollers-microprocessors/stm32f407-417.html)
 * [STM32F411](https://www.st.com/en/microcontrollers-microprocessors/stm32f411.html)
   * WeAct Blackpill
 * [STM32F446](https://www.st.com/en/microcontrollers-microprocessors/stm32f446.html)
 * [STM32G431](https://www.st.com/en/microcontrollers-microprocessors/stm32g4x1.html)
 * [STM32G474](https://www.st.com/en/microcontrollers-microprocessors/stm32g4x4.html)
 * [STM32H723](https://www.st.com/en/microcontrollers-microprocessors/stm32h723-733.html)
 * [STM32H733](https://www.st.com/en/microcontrollers-microprocessors/stm32h723-733.html)
 * [STM32L412](https://www.st.com/en/microcontrollers-microprocessors/stm32l4x2.html)
 * [STM32L422](https://www.st.com/en/microcontrollers-microprocessors/stm32l4x2.html)
 * [STM32L432](https://www.st.com/en/microcontrollers-microprocessors/stm32l4x2.html)
 * [STM32L433](https://www.st.com/en/microcontrollers-microprocessors/stm32l4x3.html)
 * [STM32L442](https://www.st.com/en/microcontrollers-microprocessors/stm32l4x2.html)
 * [STM32L443](https://www.st.com/en/microcontrollers-microprocessors/stm32l4x3.html)

### WestBerryTech (WB32)

 * [WB32F3G71xx](http://www.westberrytech.com)
 * [WB32FQ95xx](http://www.westberrytech.com)

### NXP (Kinetis)

 * [MKL26Z64](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/kl-series-cortex-m0-plus/kinetis-kl2x-72-96-mhz-usb-ultra-low-power-microcontrollers-mcus-based-on-arm-cortex-m0-plus-core:KL2x)
   * PJRC Teensy LC
 * [MK20DX128](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/k-series-cortex-m4/k2x-usb/kinetis-k20-50-mhz-full-speed-usb-mixed-signal-integration-microcontrollers-based-on-arm-cortex-m4-core:K20_50)
 * [MK20DX256](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/k-series-cortex-m4/k2x-usb/kinetis-k20-72-mhz-full-speed-usb-mixed-signal-integration-microcontrollers-mcus-based-on-arm-cortex-m4-core:K20_72)
   * PJRC Teensy 3.2
 * [MK64FX512](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/k-series-cortex-m4/k6x-ethernet/kinetis-k64-120-mhz-256-kb-sram-microcontrollers-mcus-based-on-arm-cortex-m4-core:K64_120)
   * PJRC Teensy 3.5
 * [MK66FX1M0](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/k-series-cortex-m4/k6x-ethernet/kinetis-k66-180-mhz-dual-high-speed-full-speed-usbs-2mb-flash-microcontrollers-mcus-based-on-arm-cortex-m4-core:K66_180)
   * PJRC Teensy 3.6

### Raspberry Pi

* [RP2040](https://www.raspberrypi.com/documentation/microcontrollers/rp2040.html)

For a detailed overview about the RP2040 support by QMK see the [dedicated RP2040 page](platformdev_rp2040.md).

## Atmel ATSAM

There is limited support for one of Atmel's ATSAM microcontrollers, that being the [ATSAMD51J18A](https://www.microchip.com/wwwproducts/en/ATSAMD51J18A) used by the [Massdrop keyboards](https://github.com/qmk/qmk_firmware/tree/master/keyboards/massdrop). However, it is not recommended to design a board with this microcontroller as the support is quite specialized to Massdrop hardware.

## RISC-V

### GigaDevice

[ChibiOS-Contrib](https://github.com/ChibiOS/ChibiOS-Contrib) has support for the GigaDevice [GD32VF103 series](https://www.gigadevice.com/products/microcontrollers/gd32/risc-v/mainstream-line/gd32vf103-series/) microcontrollers and provides configurations for the [SiPeed Longan Nano](https://longan.sipeed.com/en/) development board that uses this microcontroller. It is largely pin and feature compatible with STM32F103 and STM32F303 microcontrollers.
