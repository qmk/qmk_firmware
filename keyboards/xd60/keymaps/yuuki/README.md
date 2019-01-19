# yuuki's Layout

Customized xd60 keymap with inspirations from HHKB and the layout I used on my Vortex Core (a 40% keyboard).

## Programming Instructions

Change the layout in `keymap.c` then run `make xd60:yuuki`. The compiled file will be located in `.build/xd60_yuuki.hex` relative to the project root. To flash it onto your keyboard, use whatever program works on your OS. I personally use `dfu-programmer`, and run:

* reset keyboard by pressing the reset button on the back of the PCB
* `sudo dfu-programmer atmega32u4 erase`
* `sudo dfu-programmer atmega32u4 flash .build/xd60_yuuki.hex`
* `sudo dfu-programmer atmega32u4 start`

## Layout

![Keyboard Layout](https://github.com/cideM/cidem.github.io/blob/master/keyboard-layout.png "Layout")

Upper row is default layer, bottom row is function layer. I Didn't include the symbols, such as @,# or $, as their placement is just as you'd expect it.

## Summary of Changes

| Key                        | Function                           |
| -------------------------- | ---------------------------------- |
| Capslock | Forward Slash when tapped and Left Control when held |
| Left Control | Temporarily activate function layer |
| FN + ESC | Grave |
| Space Cadet Shift | Left Shift tapped writes ( and Right Shift tapped writes )  |
| FN + HJKL | Arrow Keys |
| Rightmost key in second row from bottom | Temporarily activate function layer |
| FN + C | ^ |
| FN + V | & (both for convenience as I use these keys a lot with VIM navigation and I find them hard reach) |
