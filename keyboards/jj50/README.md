JJ50
==========================

This is a port of the QMK firmware for boards that are based on the
ps2avrGB firmware, like the [ps2avrGB keyboard](https://www.keyclack.com/product/gb-ps2avrgb/), for use on the JJ50, a preonic-like board.

Most of the code was taken and amended from YMD96, which in itself was taken from ps2avrGB and amended by Andrew Novak.

Note that this is a complete replacement for the firmware, so you won't be
using Bootmapper Client to change any keyboard settings, since not all the
USB report options are supported.  

Hardware Supported: JJ50 with the ATmega32a chip.  
Hardware Availability: [KPrepublic on AliExpress](https://www.aliexpress.com/item/jj50-v1-0-Custom-Mechanical-Keyboard-50-PCB-programmed-50-preonic-layouts-bface-firmware-with-rgb/32848915277.html)

This version by [Wayne K. Jones](github.com/WarmCatUK).


## Installing and Building

Make example for this keyboard (after setting up your build environment):

```
$ make jj50:default:program
```
It should detect the keyboard and set it to bootloader mode automatically, prior to flashing firmware.

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

Note that this is a complete replacement for the firmware, so you won't be
using Bootmapper Client to change any keyboard settings, since not all the
USB report options are supported.
In addition you may need the AVR toolchain and `bootloadHID` for flashing:

```
$ brew cask install crosspack-avr
$ brew install --HEAD https://raw.githubusercontent.com/robertgzr/homebrew-tap/master/bootloadhid.rb
```

In order to use the `././util/atmega32a_program.py` script, which can reboot the board into
the bootloader, you'll need Python 2 with PyUSB installed:

```
$ pip install pyusb
```

If you prefer, you can just build it and flash the firmware directly with
`bootloadHID` if you boot the board while holding down `Backspace` (`key below top right key`) to keep it
in the bootloader:

```
$ make jj50
$ bootloadHID -r jj50_default.hex
```
I dont use windows personally, but the following is from ymd96 regarding flashing the atmega32a:

Since the JJ50 uses an ATmega32a chip instead of the 32u4, you need to download [HIDBootFlash v.1.0](http://vusb.wikidot.com/project:hidbootflash) for Windows. If anyone knows of a Linux/Mac bootflasher that works, edit this readme!
On Windows, I use [MINGw](http://www.mingw.org/) to compile the keymaps. On Linux or OSX you can simply use the terminal.

Once you have those two pieces of software:
Build the keyboard with  
```
$ make jj50:default
```  
If you make your own layout, change the `default` word to whatever your layout is.  

And flash the compiled hex file with `HIDBootFlash`. Simply put the board in flashing mode by plugging it in while holding the key below the top right key, and click `find device`. Then you can specify the .hex file and flash it to the device.


## Troubleshooting

1. Try plugging the board in while pressing `Backspace` (`Key below the top right key`). This will force it to boot only the bootloader without loading the firmware. Once this is done, just reflash the board with the original firmware.
2. Sometimes USB hubs can act weird, so try connecting the board directly to your computer or plugging/unplugging the USB hub.
3. If you get an error such as "Resource Unavailable" when attemting to flash on Linux, you may want to compile and run `tools/usb_detach.c`. See `tools/README.md` for more info.
4. I was occasionally finding that I wasn't flashing changes that I was making to my keymap. If that happens, remove the previous build and simply force rebuild by making with:
```
$ rm jj50_default.hex
$ make -B jj50:default
$ make -B jj50:default:program
```



