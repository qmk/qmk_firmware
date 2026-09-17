# WD66

![wd66](https://i.imgur.com/FjCnWen.jpg)

## Default Layout
![layout](https://i.imgur.com/BwjDlrh.png)

* Keyboard Maintainer: [11customs](https://github.com/11Customs)
* Hardware & Firmware by [1215](https://github.com/1215-tech)
* Hardware Supported: wd66_rev1
* Hardware Availability: PCB files for production available [here](https://github.com/11Customs/WD66-ver-0.1) 

Make example for this keyboard (after setting up your build environment):

    make wd66:default

Flashing example for this keyboard:

    make wd66:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Start with  [Complete Newbs Guide](https://docs.qmk.fm/#/newbs) if you are totally new to this

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic Lite**: Hold `Esc` (top-left) and plug the PCB in.
* **Physical reset button**: Briefly press the button on the back of the PCB near the spacebar.
* **Keycode in layout**: With the board plugged in, hold `Fn` and press `Backspace` (`QK_BOOT`).
