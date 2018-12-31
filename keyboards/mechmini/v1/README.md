Mechmini V1
===========

A 40% ortholinear/staggered keyboard, that was originally bootmapper and can be ported to QMK following this readme.  This version is no longer in production [More info on MECHKEYS](https://mechkeys.ca).

Keyboard Maintainer: QMK Community 
Hardware Supported: Mechmini 1 PCB  
Hardware Availability: Version 1 (Bootmapper) no longer in production [MECHKEYS](https://mechkeys.ca)

Make example for this keyboard (after setting up your build environment):

    make mechmini/v1:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

## Mechmini Notes

Note that this is a complete replacement for the firmware, so you won't be
using Bootmapper Client to change any keyboard settings, since not all the
USB report options are supported.

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
$ make mechmini:program
```

If you prefer, you can just build it and flash the firmware directly with
`bootloadHID` if you boot the board while holding down `L_Ctrl` to keep it
in the bootloader:

```
$ make mechmini
$ bootloadHID -r mechmini_default.hex
```

## Troubleshooting

From my experience, it's really hard to brick these boards. But these
tricks have been useful when it got stuck in a weird scenario.

1. Try plugging the board in while pressing `L_Ctrl`. This will force it
   to boot only the bootloader without loading the firmware. Once this is
   done, just reflash the board with the original firmware.
2. Sometimes USB hubs can act weird, so try connecting the board directly
   to your computer or plugging/unplugging the USB hub.
3. If errors happen with 
`./tmk_core/common/avr/suspend.c` it is likely you implemented a RGB underglow sleep setting previously.  Simply comment out the following code found under `void suspend_wakeup_init(void)`:
```
ifdef RGBLIGHT_ANIMATIONS
    rgblight_timer_enable();
    _delay_ms(50);
    rgblight_set();
#endif
```
So that the resulting code should know reflect:
```
/*#ifdef RGBLIGHT_ANIMATIONS
    rgblight_timer_enable();
    _delay_ms(50);
    rgblight_set();
#endif*/
```


