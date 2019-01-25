ps2avrGB keyboard firmware
==========================

This is a port of the QMK firmware for boards that are based on the
ps2avrGB firmware, like the [ps2avrGB
keyboard](https://www.keyclack.com/product/gb-ps2avrgb/) or the ones sold
by [Winkeyless](http://winkeyless.kr/product/ps2avrgb-parts/).

Note that this is a complete replacement for the firmware, so you won't be
using Bootmapper Client to change any keyboard settings, since not all the
USB report options are supported.

This is an example based on the b.mini keyboard for making other keyboards
compatible with QMK; fully supported boards have their own directory.

## Supported Boards

- [b.fake](https://github.com/qmk/qmk_firmware/tree/master/keyboards/bfake)
- [b.mini](https://github.com/qmk/qmk_firmware/tree/master/keyboards/bmini)
- [b.face](https://github.com/qmk/qmk_firmware/tree/master/keyboards/bface)
- [pearl](https://github.com/qmk/qmk_firmware/tree/master/keyboards/pearl)

## Installing

First, install the requirements. These commands are for OSX, but all you
need is the AVR toolchain and `bootloadHID` for flashing:

```
$ brew cask install crosspack-avr
$ brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
```

In order to use the `./program` script, which can reboot the board into
the bootloader, you'll need Python 2 with PyUSB installed:

```
$ pip install pyusb
```

Then, with the keyboard plugged in, simply run this command from the
`qmk_firmware` directory:

```
$ make ps2avrGB:program
```

If you prefer, you can just build it and flash the firmware directly with
`bootloadHID` if you boot the board while holding down `L_Ctrl` to keep it
in the bootloader:

```
$ make ps2avrGB
$ bootloadHID -r ps2avrGB_default.hex
```

## Setting the board to bootloader mode

If you're lucky, the programming script does this automagically for you. If
however this doesn't work for you, you need to enter the bootloader mode manually
by plugging the keyboard in while holding the bootloader key. If you did this
correctly the LEDs will blink and you'll be able to flash your firmware.

The bootloader key is the top left key of your matrix. For a standard board
from winkeyless.kr this is `L_Ctrl`, but for some custom boards running ps2avrGB
this might be different. For the Pearl it's `Esc`, for a b.fake it is `q`. If 
you're unsure you should be able to see the key in the bootmapper client.


## Troubleshooting

From my experience, it's really hard to brick these boards. But these
tricks have been useful when it got stuck in a weird scenario.

1. Try plugging the board in while holding the bootloader key. This will force 
   it to boot only the bootloader without loading the firmware. Once this is
   done, just reflash the board with the original firmware.
2. Sometimes USB hubs can act weird, so try connecting the board directly
   to your computer or plugging/unplugging the USB hub.
