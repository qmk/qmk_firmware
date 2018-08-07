YMD75 / MT84
==========================

This is a port of the QMK firmware for boards that are based on the
ps2avrGB firmware, like the [ps2avrGB keyboard] (https://www.keyclack.com/product/gb-ps2avrgb/), for use on the YMD75, from YMDK. YMDK sell the board and name it "YMD75", however the PCB has "MT84" printed on both sides.

Most of the code was taken and amended from YMD96 and my port JJ50, which in itself was taken from ps2avrGB and amended by Andrew Novak.

Note that this is a complete replacement for the firmware, so you won't be
using Bootmapper Client to change any keyboard settings, since not all the
USB report options are supported.  

Hardware Supported: YMD75/MT84 with the ATmega32a chip.
Hardware Availability: The YMD75/MT84 PCB is available from YMDK on AliExpress and suchlike.

This version by Wayne K Jones (github.com/WarmCatUK)

## Installing and Building

Make example for this keyboard (after setting up your build environment):

```
$ make ymd75:default:program
```
It should detect the keyboard and set it to bootloader mode automatically, prior to flashing firmware.
I've found that I need to remove the previous build/file before making a new one as it doesn't overwrite it; but this might just be my personal experience.

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

Note that this is a complete replacement for the firmware, so you won't be
using Bootmapper Client to change any keyboard settings, since not all the
USB report options are supported.
In addition you may need the AVR toolchain and `bootloadHID` for flashing:

```
$ brew cask install crosspack-avr
$ brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
```

In order to use the `./program` script, which can reboot the board into
the bootloader, you'll need Python 2 with PyUSB installed:

```
$ pip install pyusb
```

If you prefer, you can just build it and flash the firmware directly with
`bootloadHID` if you boot the board while holding down `Left Control` to keep it
in the bootloader:

```
$ make ymd75
$ bootloadHID -r ymd75_default.hex
```
I dont use windows personally, but the following is from ymd96 regarding flashing the atmega32a:

Since the YMD75/MT84 uses an ATmega32a chip instead of the 32u4, you need to download [HIDBootFlash v.1.0](http://vusb.wikidot.com/project:hidbootflash) for Windows. If anyone knows of a Linux/Mac bootflasher that works, edit this readme!
On Windows, I use [MINGw](http://www.mingw.org/) to compile the keymaps. On Linux or OSX you can simply use the terminal.

Once you have those two pieces of software:
Build the keyboard with  
```
$ make ymd75:default
```  
If you make your own layout, change the `default` word to whatever your layout is.  

And flash the compiled hex file with `HIDBootFlash`. Simply put the board in flashing mode by plugging it in while holding the key below the top right key, and click `find device`. Then you can specify the .hex file and flash it to the device.


## Troubleshooting

1. Try plugging the board in while pressing `Backspace` (`Key below the top right key`). This will force it to boot only the bootloader without loading the firmware. Once this is done, just reflash the board with the original firmware.
2. Sometimes USB hubs can act weird, so try connecting the board directly to your computer or plugging/unplugging the USB hub.
3. If you get an error such as "Resource Unavailable" when attemting to flash on Linux, you may want to compile and run `tools/usb_detach.c`. See `tools/README.md` for more info.
4. I was occasionally finding that I wasn't flashing changes that I was making to my keymap. If that happens, remove the previous build and simply force rebuild by making with:
```
$ rm ymd75_default.hex
$ make -B ymd75:default
$ make -B ymd75:default:program
```



