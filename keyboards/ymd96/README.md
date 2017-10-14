YMD96 
==========================

This is a port of the QMK firmware for boards that are based on the
ps2avrGB firmware, like the [ps2avrGB
keyboard](https://www.keyclack.com/product/gb-ps2avrgb/), for use on the YMD96. 

Note that this is a complete replacement for the firmware, so you won't be
using Bootmapper Client to change any keyboard settings, since not all the
USB report options are supported.  

Here is the default layout, it is fairly simple with a few function keys: 
![YMD96 Layout](https://i.imgur.com/qCwE2ns.png)  
If you have a different layout (since there were many options during the GB), please feel free to contribute!  

Keyboard maintainer: [Andrew](https://github.com/sparkyman215)  
Hardware Supported: YMD96 with the ATmega32a chip.  
Hardware Availability: The GB was run June 2017, [in this thread](https://www.reddit.com/r/mechmarket/comments/6hu3yx/vendor_ymd96_gb_is_now_live_68_an_universal_and/). The vendor has stated that they plan on selling more rounds.

## Finding your specific matrix

This firmware was modified from [ps2avrGB](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ps2avrGB), also found on this qmk repo, to work with the YMD96 keyboard. However, I only have one board to test with, which might have a different layout than yours. To get qmk working with your specific layout, you'll need to follow these steps:  

1. Follow the [guide here](https://www.massdrop.com/talk/1392/programming-kbd-keyboards-via-bootmapper-client) to get Bootmapper Client setup. While you won't need it after you get qmk working, you need to use Bootmapper Client to figure out how the matrix is laid out. In the end, here's an example of what it should look like: ![BMC](https://i.imgur.com/wNihDwn.png)  
2. Next is the tricky part: editing the `ymd96.h` file. Here, you have to figure out how the keys are laid out physically and assign each key the right keycode. Study how the codes in brackets correspond to the BMC columns. Consider the first column: K000 corresponds to Col 1 Row 1, and K100 corresponds to Col 2 Row 1. K111 = Col 2 Row 10.  
3. First, you need to define the codes that are actually used in the brackets. KC_NO is used whenever a cell isn't used, such as col 1 row 4-6 in BMC.  
4. Once you have all those set up, you need to put the keycodes where they physically are in the KEYMAP( area. Since the columns aren't all uniform (e.g. col2row6 is B, but col2row7 is the numpad 1), the keycodes will be all over the place.  
5. Finally! Hard part is pretty much done. Next, you simply have to edit the `keymap.c` file to actually assign the keycodes to do something. You essentially replace the keycodes (e.g. K000) with actual codes that do something, e.g. KC_ENTER. Modify these to your hearts content, and of course this is where all the extra functionality of QMK shines. I won't get into it here, but hopefully you've made it this far!

## Installing and Building

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

Build the keyboard with  
```
$ make ymd96:default  
```  
If you make your own layout, change the `default` word to whatever your layout is.  

## Troubleshooting

From my experience, it's really hard to brick these boards. But these
tricks have been useful when it got stuck in a weird scenario.

1. Try plugging the board in while pressing `L_Ctrl`. This will force it
   to boot only the bootloader without loading the firmware. Once this is
   done, just reflash the board with the original firmware.
2. Sometimes USB hubs can act weird, so try connecting the board directly
   to your computer or plugging/unplugging the USB hub.
