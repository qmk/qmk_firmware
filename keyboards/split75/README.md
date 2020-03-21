split75 ps2avrGB keyboard firmware
==========================

This is a port of the QMK firmware for the split75 keyboard, also known as the ve.a taobao split clone. It runs on
ps2avrGB firmware, like the [ps2avrGB keyboard](https://www.keyclack.com/product/gb-ps2avrgb/) or the ones sold
by [Winkeyless](http://winkeyless.kr/product/ps2avrgb-parts/).

https://a.aliexpress.com/_BT9raf

Original work performed by https://github.com/walkerstop/qmk_firmware/tree/split75/keyboards/wheatfield/split75 All credit goes to him. I've tidied up the keymap (removed 3 extra keys), a couple of functions and this Readme.

Note that this is a complete replacement for the firmware, so you won't be
using Bootmapper Client to change any keyboard settings, since not all the
USB report options are supported.

This is an example based on the b.mini keyboard for making other keyboards
compatible with QMK; fully supported boards have their own directory.


## Compling

No additional instructions required, simply make as any other firmware:
```
make split75:default
```


## Flashing

To enther the bootloader mode, hold the Left Control key while plugging in your keyboard. The LEDs should blink if the keyboard is not in the bootloader now and you'll be able to flash your firmware.

To flash the keyboard, get the latest distribution from https://github.com/robertgzr/bootloadHID , either by clicking the green `Clone or Download` button or via `git clone https://github.com/robertgzr/bootloadHID.git` command in your terminal. You'll only care about the `bootloadHID-master.zip\bootloadHID-master\commandline\bootloadHID.exe` from the archive - extract it somewhere convenient

Then flash your firmware using
```
.\bootloadHID -r  PATH_TO_FOLDER\split75_default.hex
```

## Troubleshooting

From my experience, it's really hard to brick these boards. But these
tricks have been useful when it got stuck in a weird scenario.

1. Try plugging the board in while holding the bootloader key. This will force
   it to boot only the bootloader without loading the firmware. Once this is
   done, just reflash the board with the original firmware.
2. Sometimes USB hubs can act weird, so try connecting the board directly
   to your computer or plugging/unplugging the USB hub.