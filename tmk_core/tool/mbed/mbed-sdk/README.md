mbed SDK
========

[![Build Status](https://travis-ci.org/mbedmicro/mbed.png)](https://travis-ci.org/mbedmicro/mbed/builds)

The mbed Software Development Kit (SDK) is a C/C++ microcontroller software platform relied upon by tens of thousands of
developers to build projects fast.

The SDK is licensed under the permissive Apache 2.0 licence, so you can use it in both commercial and personal projects
with confidence.

The mbed SDK has been designed to provide enough hardware abstraction to be intuitive and concise, yet powerful enough
to build complex projects. It is built on the low-level ARM CMSIS APIs, allowing you to code down to the metal if needed.
In addition to RTOS, USB and Networking libraries, a cookbook of hundreds of reusable peripheral and module libraries
have been built on top of the SDK by the mbed Developer Community.

Documentation
-------------
* [Tools](http://developer.mbed.org/handbook/mbed-tools): how to setup and use the build system.
* [mbed library internals](http://developer.mbed.org/handbook/mbed-library-internals)
* [Adding a new target microcontroller](http://developer.mbed.org/handbook/mbed-SDK-porting)

Supported Microcontrollers and Boards
-------------------------------------
View all on the [mbed Platforms](https://developer.mbed.org/platforms/) page.

NXP:
* [mbed LPC1768](http://developer.mbed.org/platforms/mbed-LPC1768/) (Cortex-M3)
* [u-blox C027 LPC1768](http://developer.mbed.org/platforms/u-blox-C027/) (Cortex-M3)
* [mbed LPC11U24](http://developer.mbed.org/platforms/mbed-LPC11U24/) (Cortex-M0)
* [EA LPC11U35](http://developer.mbed.org/platforms/EA-LPC11U35/) (Cortex-M0)
* mbed LPC2368 (ARM7TDMI-S)
* LPC810 (Cortex-M0+)
* [LPC812](http://developer.mbed.org/platforms/NXP-LPC800-MAX/) (Cortex-M0+)
* [EA LPC4088](http://developer.mbed.org/platforms/EA-LPC4088/) (Cortex-M4F)
* [EA LPC4088 DM](http://developer.mbed.org/platforms/EA-LPC4088-Display-Module/) (Cortex-M4F)
* LPC4330 (Cortex-M4F + Cortex-M0)
* [LPC1347](http://developer.mbed.org/platforms/DipCortex-M3/) (Cortex-M3)
* [LPC1114](http://developer.mbed.org/platforms/LPC1114FN28/) (Cortex-M0)
* LPC11C24 (Cortex-M0)
* [LPC1549](https://developer.mbed.org/platforms/LPCXpresso1549/) (Cortex-M3)
* [LPC800-MAX](https://developer.mbed.org/platforms/NXP-LPC800-MAX/) (Cortex-M0+)
* [DipCortex-M0](https://developer.mbed.org/platforms/DipCortex-M0/) (Cortex-M0)
* [DipCortex-M3](https://developer.mbed.org/platforms/DipCortex-M3/) (Cortex-M3)
* [BlueBoard-LPC11U24](https://developer.mbed.org/platforms/BlueBoard-LPC11U24/) (Cortex-M0)
* LPCCAPPUCCINO (Cortex-M0)
* [Arch](https://developer.mbed.org/platforms/Seeeduino-Arch/) (Cortex-M0)
* [Arch GPRS](https://developer.mbed.org/platforms/Seeed-Arch-GPRS/) (Cortex-M0)
* [Arch Pro](https://developer.mbed.org/platforms/Seeeduino-Arch-Pro/) (Cortex-M3)

Freescale:
* [FRDM-KL05Z](https://developer.mbed.org/platforms/FRDM-KL05Z/) (Cortex-M0+)
* [FRDM-KL25Z](http://developer.mbed.org/platforms/KL25Z/) (Cortex-M0+)
* FRDM-KL43Z (Cortex-M0+)
* [FRDM-KL46Z](https://developer.mbed.org/platforms/FRDM-KL46Z/) (Cortex-M0+)
* [FRDM-K20D50M](https://developer.mbed.org/platforms/FRDM-K20D50M/) (Cortex-M4)
* [FRDM-K22F](https://developer.mbed.org/platforms/FRDM-K22F/) (Cortex-M4F)
* [FRDM-K64F](https://developer.mbed.org/platforms/FRDM-K64F/) (Cortex-M4F)

STMicroelectronics:
* [Nucleo-F030R8](https://developer.mbed.org/platforms/ST-Nucleo-F030R8/) (Cortex-M0)
* [Nucleo-F072RB](https://developer.mbed.org/platforms/ST-Nucleo-F072RB/) (Cortex-M0)
* [Nucleo-L053R8](https://developer.mbed.org/platforms/ST-Nucleo-L053R8/) (Cortex-M0+)
* [Nucleo-F103RB](https://developer.mbed.org/platforms/ST-Nucleo-F103RB/) (Cortex-M3)
* [Nucleo-L152RE](https://developer.mbed.org/platforms/ST-Nucleo-L152RE/) (Cortex-M3)
* [Nucleo-F302R8](https://developer.mbed.org/platforms/ST-Nucleo-F302R8/) (Cortex-M4F)
* [Nucleo-F334R8](https://developer.mbed.org/platforms/ST-Nucleo-F334R8/) (Cortex-M4F)
* [Nucleo-F401RE](https://developer.mbed.org/platforms/ST-Nucleo-F401RE/) (Cortex-M4F)
* [Nucleo-F411RE](https://developer.mbed.org/platforms/ST-Nucleo-F411RE/) (Cortex-M4F)
* STM32F4XX (Cortex-M4F)
* STM32F3XX (Cortex-M4F)
* STM32F0-Discovery (Cortex-M0)
* STM32VL-Discovery (Cortex-M3)
* STM32F3-Discovery (Cortex-M4F)
* STM32F4-Discovery (Cortex-M4F)
* STM32F429-Discovery (Cortex-M4F)
* STM32L0-Discovery (Cortex-M0+)
* [Arch Max](https://developer.mbed.org/platforms/Seeed-Arch-Max/) (Cortex-M4F)


Nordic:
* [nRF51822-mKIT](https://developer.mbed.org/platforms/Nordic-nRF51822/) (Cortex-M0)
* [Arch BLE](https://developer.mbed.org/platforms/Seeed-Arch-BLE/) (Cortex-M0)

Renesas:
* [RZ-A1H](http://developer.mbed.org/platforms/Renesas-GR-PEACH/) (Cortex-A9)


Supported Toolchains and IDEs
-----------------------------
* GCC ARM: [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded/4.7/4.7-2012-q4-major)
* ARMCC (standard library and MicroLib): [uVision](http://www.keil.com/uvision/)
* IAR: [IAR Embedded Workbench](http://www.iar.com/en/Products/IAR-Embedded-Workbench/ARM/)
* GCC code_red: [Red Suite](http://www.code-red-tech.com/)
* GCC CodeSourcery: [Sourcery CodeBench](http://www.mentor.com/embedded-software/codesourcery)
* GCC ARM: [Em::Blocks](http://www.emblocks.org/web/)
* GCC ARM: [CooCox CoIDE](http://www.coocox.org/)

API Documentation
-----------------
* [RTOS API](http://developer.mbed.org/handbook/RTOS)
* [TCP/IP Socket API](http://developer.mbed.org/handbook/Socket) (Transports: Ethernet, WiFi, 3G)
* [USB Device API](http://developer.mbed.org/handbook/USBDevice)
* [USB Host API](http://developer.mbed.org/handbook/USBHost)
* [DSP API](http://developer.mbed.org/users/mbed_official/code/mbed-dsp/docs/tip/)
* Flash File Systems: [SD](http://developer.mbed.org/handbook/SDFileSystem), [USB MSD](http://developer.mbed.org/handbook/USBHostMSD), [semihosted](http://developer.mbed.org/handbook/LocalFileSystem)
* [Peripheral Drivers API](http://developer.mbed.org/handbook/Homepage)

Community
---------
For discussing the development of the mbed SDK itself (Addition/support of microcontrollers/toolchains, build and test system, Hardware Abstraction Layer API, etc) please join our [mbed-devel mailing list](https://groups.google.com/forum/?fromgroups#!forum/mbed-devel).

For every topic regarding the use of the mbed SDK, rather than its development, please post on the [mbed.org forum](http://mbed.org/forum/), or the [mbed.org Q&A](http://mbed.org/questions/).

For reporting issues in the mbed libraries please open a ticket on the issue tracker of the relevant [mbed official library](http://mbed.org/users/mbed_official/code/).
