Ixora
=========

[Ixora](https://i.imgur.com/GqDk3XY.png)


Ixora is an ARM-powered 6-key macropad with a USB connector, hotswap sockets, and indicator LEDs.

Keyboard Maintainer: [Peioris](https://github.com/coarse)  
Hardware Supported: Ixora PCB  
Hardware Availability: [Peioris](https://github.com/coarse)

Make example for this keyboard (after setting up your build environment):

    make peiorisboards/ixora:default:dfu-util

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

#### Developer's Note

STM32F042xx chips does not allow jumping to bootloader without BOOT0 being set to high, therefore it is impossible to enter the bootloader from sending a `RESET` keycode nor using bootmagic or bootmagic lite.  
The only way to enter bootloader is to hold the BOOT0 button while the keyboard is powering up or after a power reset (done by pressing the reset switch or sending a `RESET` keycode).
