# Rev1

This readme describes the specifics of using the rev1 design

## First Time Setup

Clone the `qmk_firmware` repo and navigate to its top level directory. [Once your build environment is setup](https://docs.qmk.fm/getting_started_build_tools.html), you'll be able to generate the default .hex using the [build/compile instructions](https://docs.qmk.fm/build-compile-instructions) in the docs

If everything worked correctly you will see a file:

```bash
lets_split_vitamins_rev1_YOUR_KEYMAP_NAME.hex
```

If you want, you can flash the hex file to the keyboard right after compilation, by adding `:avrdude` to the end of the make command like so:

```bash
make lets_split_vitamins/rev1:default:avrdude
```

This will both compile the hex, and flash the connected half.

For more information on customizing keymaps, take a look at the primary documentation for [Customizing Your Keymap](/readme.md##customizing-your-keymap) in the main readme.md.

## Entering bootloader

If the keyboard isn't new, and has been flashed before, you need to enter bootloader.
To enter bootloader, either use the assigned keys on the keymap, or if none have been put in the keymap, quickly short the reset to gnd twice. (Bottom pins of programming header, see image) ![Reset pins](https://i.imgur.com/LCXlv9W.png)

If using the default keymap, there's a reset key-combination on each half:  
***Lower (SW23) and left-shift (SW13)*** on the left half, or  
***Raise(SW44) and Enter(SW42)***  on the right half  
It is recommended to add such reset keys to any custom keymaps. It shouldn't be necesarry to have one on each half, but the default layout has that.

The board exits bootloader mode after 8 seconds, if you haven't started flashing.

## EEPROM

If this is the first time you're flashing the boards, you have to flash EEPROM

0. If your keyboard is plugged in, unplug it
1. Open a terminal, and navigate to the qmk_firmware folder
1. Run `ls /dev | grep tty` Note down which ports you see
1. Plug the keyboard in, if it's new, it should enter bootloader, if it's not new, see **Entering bootloader** on how to enter bootloader mode
1. Right after entering bootloader, run `ls /dev | grep tty` again. There should be a new tty, this is the bootloader TTY, note it down. If nothing shows see **Entering bootloader** on how to enter bootloader mode
1. For the left hand side, run  `avrdude -c avr109 -p m32u4 -P /dev/ttyS1 -U eeprom:w:"./quantum/split_common/eeprom-lefthand.eep":a`
Replace ***/dev/ttyS1*** with the port you noted down earlier. If you're on windows using msys2, replace ***/dev/ttyS1*** with COM2, note that the number is one higher than the tty number.  
Do the same For the right hand, but change the file to ***eeprom-righthand.eep***

Your EEPROM should be flashed :)

In the future, you shouldn't need to flash EEPROM (it will in fact wear the eeprom memory, so don't)

## Flashing

If you haven't flashed EEPROM before, do that first.  

To flash keymaps onto the keyboard, use:

```bash
make lets_split_vitamins/rev1:[KEYMAP]:avrdude
```

from the qmk_firmware folder. Default being the default keymap.

## Cases

The keyboard is supplied with some simple plate cases, alternatively a 3D model for the left half is available [here](https://cad.onshape.com/documents/c6e5ae250d1e24fe46c9ef6c/w/d69f7049c0921df3d2b241f9/e/ecc2b176ab52a6d77bc55051).

Alternatively the flat case for the Rev2 works for the rev1 kit as well, however one of the supports collide with a diode. If printed in thermo-plastics this can be heated and pressed to form a recess for the diode.

## WS2812 RGB

If you wish to add RGB LED strips to your board, then the boards have breakouts for these.  
You can either have each halfcontrol it's own strip of LEDs, or, if you're using a TRRS cable, you can have one half control the LEDs in both halves.

To add RGB LEDs to the board, solder the + and - of the >WS2812 headers to the LED strips. Then if you want each half to control it's own set of LEDs seperately, solder the D pad to Din on the strips.

If you instead want to syncronize the halves over a TRRS cable, solder the D pad to Din in the side you want to control the strips, either will work so flip a coin, and then solder the Dout pad to the WS2812> pad on the board. On the other half, solder the WS2812> pad to Din.

![pad legend](https://i.imgur.com/g6ane0Q.jpg)
