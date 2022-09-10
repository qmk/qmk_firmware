Vinta
=========

[Vinta](https://i.imgur.com/huX3lff.jpg)


This is an ARM-powered 65% keyboard PCB with USB Mini B connector and breakout for optional RGB underglow.

Keyboard Maintainer: [Coarse](https://github.com/coarse)  
Hardware Supported: Vinta with STM32F042K6T6  
Hardware Availability: Private Groupbuy

Make example for this keyboard (after setting up your build environment):

    make coarse/vinta:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

#### Developer's Note

STM32F042xx chips does not allow jumping to bootloader without BOOT0 being set to high, therefore it is impossible to enter the bootloader from sending a `QK_BOOT` keycode nor using bootmagic or bootmagic lite.  
The only way to enter bootloader is to hold the BOOT0 button while the keyboard is powering up or after a power reset (done by pressing the reset switch or sending a `QK_BOOT` keycode).
