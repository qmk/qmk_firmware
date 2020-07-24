# Anne Pro

![Anne Pro](https://i.imgur.com/wF7mz7u.jpg)

QMK firmware port for the Anne Pro 60% keyboard produced by [Obins](http://en.obins.net).

__This firmware is not created or supported by the creator of this keyboard!__

Keyboard Maintainer: [Michiel Visser](https://github.com/msvisser)  
Hardware Supported: Anne Pro (this means no support for the _Anne Pro 2_)  
Hardware Availability: Discontinued, [possible vendors](https://www.reddit.com/r/AnnePro/wiki/vendors)

Make sure you check out the correct branch for this keyboard and initialize the submodules!

    git checkout anne_pro
    make git-submodule

Make example for this keyboard (after setting up your build environment):

    make anne_pro:default

Flashing the firmware can easily be done when the keyboard is in DFU mode:

    make anne_pro:default:flash

The default Arrows and macOS keyboard layouts are also included and can be used with `arrow` or `macos` instead of `default`.

To convert the `bin` file to a `dfu` file the following script can be used

    ./keyboards/anne_pro/dfuse-pack.py -b 0x08004000:anne_pro_default.bin anne_pro_default.dfu

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Firmware requirements for LED backlight
To get functioning backlighting for the Anne Pro the original LED firmware is required. This should be the version v1.40, which is available on the [Obins website](http://en.obins.net/firmware#1). __The backlight will not work with the newer ObinsKit firmware!__ This firmware can be installed by following the update guide on the Obins website, or using `dfu-util` if you know what you are doing.

## Bluetooth pairing
The Bluetooth setup is similar to the original Anne Pro firmware. After pressing `Fn + B` the Bluetooth layer shows up. By pressing the `+` key Bluetooth is enabled. You can now pair your computer. Once the computer asks for the pairing code the lights on the keyboard should turn off. You can now simply enter the pairing code and hit connect on the computer, this should pair the device.

## Known problems
- Capslock indicator light is not working. This is the results of buggy lighting firmware by Obins, which means that the complete backlight would turn on if the capslock was toggled.
- Sending macros over Bluetooth is limited to about 20 keypresses, this is because the transmit buffer is limited and only starts sending after all keypresses are put in the buffer.
