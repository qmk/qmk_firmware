Vinta
=========

[Vinta](https://i.imgur.com/huX3lff.jpg)


This is an ARM-powered 65% keyboard PCB with USB Mini B connector and breakout for optional RGB underglow.

Keyboard Maintainer: [Peioris](http://peioris.space/) and on [github](https://github.com/coarse)  
Hardware Supported: Vinta with STM32F042K6T6  
Hardware Availability: http://groupbuys.mechboards.co.uk/shop/hs60-hotswap-60-pcb/

Make example for this keyboard (after setting up your build environment):

    make vinta:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

#### Developer's Note

It is impossible to enter DFU mode from pressing a `RESET` keycode on this PCB. It's a known issue on STM32F042 chips.  
The only way to enter DFU mode is to hold the BOOT0 button while the keyboard is powering up or after a power reset (either through the reset button or the `RESET` keycode).