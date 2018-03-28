TADA68
======

A compact 65% keyboard.

Keyboard Maintainer: QMK Community
Hardware Supported: TADA68 PCB
Hardware Availability: [kbdfans](https://kbdfans.myshopify.com/products/tada68-mechanical-keyboard-gateron-swtich-65-layout-dye-sub-keycaps-cherry-profils?variant=34710238797) [kbdist](http://www.kbdist.com/shop/saber-68)

Make example for this keyboard (after setting up your build environment):

    make tada68:default:bin

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

## Flashing Instructions

*Read all the instructions, there are a few warnings of things to avoid doing to avoid bricking your Tada68. _It is much too easy to do!  _

1) from the `qmk_firmware\` directory run:
```
$ make tada68:default:flashbin
```

2) Connect your keyboard to Windows computer, hit the reset button on the TADA, the lights will start flashing.

3) You'll see a new drive on your computer called TADA68. Backup the original factory `FLASH.BIN` file thats inside it.

4) Delete `FLASH.BIN` from the TADA drive and copy `tada68_default.bin` that was generated at the root of the qmk directory into the TADA drive.

5) *Do not eject the USB device.* Hit ESC on the keyboard. The lights will stop flashing and your firmware is loaded!
