# Anne Pro

![Anne Pro](https://i.imgur.com/wF7mz7u.jpg)

*QMK firmware port for the Anne Pro 60% keyboard produced by [Obins](http://en.obins.net)*

* Keyboard Maintainers: [Michiel Visser](https://github.com/msvisser), [Joel Beckmeyer](https://github.com/TinfoilSubmarine/)
* Hardware Supported: Anne Pro (the original, not the _Anne Pro 2_)  
* Hardware Availability: Discontinued

Make example for this keyboard (after setting up your build environment):

    make anne_pro:default

Flashing the firmware can easily be done when the keyboard is in DFU mode:

    make anne_pro:default:flash

The default Arrows and macOS keyboard layouts are also included and can be used with `arrow` or `macos` instead of `default`.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
If your keyboard has stock firmware, the only way to enter the bootloader is by first unplugging the keyboard. Hold down the Esc key and while holding it down, briefly press the button on the bottom of the keyboard using a paperclip or some other small object. You can then release the Esc key, at which point it will enter the bootloader. You can now plug the keyboard back in.

If you have previously flashed QMK firmware, you can enter the bootloader with a long press of the QK_REBOOT keycode (mapped to ANNE+Esc in the included keymaps).

## Firmware requirements for LED backlight
To get functioning backlighting for the Anne Pro the original LED firmware is required. This should be the version v1.40, which is available on the [Hexcore website](https://service.hexcore.xyz/manual/annepro/#42-anne-pro-firmware). __The backlight will not work with the newer ObinsKit firmware!__ This firmware can be installed by following the update guide on the same Hexcore website, or using `dfu-util` if you know what you are doing.

## Bluetooth pairing
The Bluetooth setup is similar to the original Anne Pro firmware. After pressing `Fn + B` the Bluetooth layer shows up. By pressing the `+` key Bluetooth is enabled. You can now pair your computer. Once the computer asks for the pairing code the lights on the keyboard should turn off. You can now simply enter the pairing code and hit connect on the computer, this should pair the device.

## Known problems
- Capslock indicator light is not working. This is the results of buggy lighting firmware by Obins, which means that the complete backlight would turn on if the capslock was toggled.
- Sending macros over Bluetooth is limited to about 20 keypresses, this is because the transmit buffer is limited and only starts sending after all keypresses are put in the buffer.
