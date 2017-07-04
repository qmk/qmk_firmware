# QMK HHKB Keymap: blakedietz

<!-- TODO: Link to Hasu's geekhack page from his name -->
<!-- TODO: Link to the ergodox ez layout in this repository -->

This is my (Blake Dietz's) own take on a QMK keymap for the Happy Hacking Keyboard Pro 2 alternate controller made by Hasu. A lot of the
 functionality was inspired by the ergodox ez default layout. 

## Dependencies

### macOS

```bash
brew tap osx-cross/avr
brew install avr-libc
brew install dfu-programmer
```

### Windows/Linux

[Build Environment Setup](https://github.com/jackhumbert/qmk_firmware/wiki#build-environment-setup)

## Flashing

You will need to make sure that you have something that you can use to press the button on the alternate controller in
order to put it into boot mode.

From the hhkb directory run the following:

```bash
make clean
make hhkb-blakedietz-dfu
```

Press the button on the alternate controller to put the board into boot mode.

You'll see an output similar to the following:

```bash
make hhkb-blakedietz-dfu

Making hhkb with keymap blakedietz and target dfu

avr-gcc (GCC) 6.2.0
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Size before:
   text    data     bss     dec     hex filename
      0   22162       0   22162    5692 hhkb_blakedietz.hex

Compiling: keyboards/hhkb/keymaps/blakedietz/keymap.c                                               [OK]
Compiling: ./tmk_core/common/command.c                                                              [OK]
Linking: .build/hhkb_blakedietz.elf                                                                 [OK]
Creating load file for Flash: .build/hhkb_blakedietz.hex                                            [OK]

Size after:
   text    data     bss     dec     hex filename
      0   22162       0   22162    5692 hhkb_blakedietz.hex

dfu-programmer: no device present.
Error: Bootloader not found. Trying again in 5s.
dfu-programmer: no device present.
Error: Bootloader not found. Trying again in 5s.
Bootloader Version: 0x00 (0)
Erasing flash...  Success
Checking memory from 0x0 to 0x6FFF...  Empty.
Checking memory from 0x0 to 0x56FF...  Empty.
0%                            100%  Programming 0x5700 bytes...
[>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
0%                            100%  Reading 0x7000 bytes...
[>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>]  Success
Validating...  Success
0x5700 bytes written into 0x7000 bytes memory (77.68%).
```

### Layers 

#### Default

##### A more "standard" layout

This layout places tilde in the standard location. Backspace is moved to the two upper-right-most keys and pipe
is put back where it belongs (where backspace is on the default hhkb2 keymapping).

##### Hyper key

<!-- TODO: Link to Brett's article about the thyper key -->

This layout throws out the HHKB's control key in favor of a Hyper key. Ctrl is instead placed on the z and / keys and
can be activated with a long press. I find that this is far more ergonomic as it's less of a reach and it allows you to
alternate to either hand when you need to use `ctrl` as a modifier.

The hyper key can be held for hyper and tapped for escape. You'll find that this is quite nice for vim.

Enter is also a hyper key. This allows for symmetry between control and enter. Hold for hyper, tap for enter.

##### Tap to Hold

###### CTL, ALT, GUI

Since the HHKB does not have three super/meta keys, these keys were moved to pinky, ring and middle finger for ctrl, alt/
 option and super respectively. This is closer to home row which I've found causes less strain.
 
The Alt and Super keys are instead replaced with layer toggle keys to go to dev and mouse mode respectively.

###### Space

Hold space to switch to dev mode. This will put you on a layer to have vim like arrow functionality on h,j,k and l. Use
this in editors that don't have vim keybindings.

### Dev 

The Dev layer can be activated holding space or hitting the HHKB's Alt key. This will put you in a mode
where all function keys are available and left, right, up and down are mapped to their vim equivalents. The function
 keys are mapped in such a way that you can use them for debugging. Typically I map debugging functions in all IDEs to
 the following for a seamless debugging experience (e.g. jumping from Intellij to chrome dev tools and back):
 
 - f1 -> step over
 - f2 -> step into
 - f3 -> step out
 - f4 -> continue
 - f5 -> set break point on current line

### Media

The media layer can be activated by pressing and holding the semi-colon. I've also placed the play and pause key on the
apostrophe key in the media layer. This allows you to easily roll your pinky from the media toggle (semi-colon) to the
play/pause key in one fluid motion.

I've also tried to logically map next/previous track along with volume up/down vim behavior. In vim since middle finger
goes up on k and index finger goes down on j, next/prev track is k/j respectively. ,/m changes volume up/down
respectively while toggled to the media layer.
