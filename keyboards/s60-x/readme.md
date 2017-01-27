S60-x keyboard firmware
======================
DIY compact keyboard designed by VinnyCordeiro for Sentraq. Most of the keymaps are based on GH60 code. This is a port from TMK to QMK based on the [original S60-X Repo](https://github.com/VinnyCordeiro/tmk_keyboard).

## S60X Resources
- [Massdrop page](https://www.massdrop.com/buy/sentraq-60-diy-keyboard-kit?mode=guest_open)

## Quickstart

If you just want to test a few layouts, the archive [s60-x_precompiled.zip](s60-x_precompiled.zip) contains pre-compiled .hex-files for all available keymaps. Not all of them are tested.
You only need to flash them onto your keyboard, which is explained below, there's no need to setup a build environment. For a full list 

## Flashing your keyboard
The recommended programs for flashing your keyboard are [Atmel FLIP](http://www.atmel.com/tools/FLIP.aspx) (Windows) and [dfu-programmer](http://dfu-programmer.sourceforge.net/) (Linux/Windows).

[QMK Firmware Flasher](https://github.com/qmk/qmk_firmware_flasher/releases) may work, as the S60-X keyboard uses the ATMega32U4 microcontroller, but it is untested. Use at your own risk.

[Easy AVR USB Keyboard Firmware](https://deskthority.net/wiki/Easy_AVR_USB_Keyboard_Firmware) also supports S60-X, but it is completely unrelated to TMK firmware. Use at your own risk.

**Programming the firmware (Windows)**

1. download and install FLIP (http://www.atmel.com/tools/FLIP.aspx)
2. connect the keyboard, press the program button on the underside of the board (S1) and wait until it enumerates (you'll hear the "disconnect" and "connect" sound)
3. go to device manager, find the atmega32u4 chip and click "update driver"
4. choose location manually: folder named "usb" inside the installation directory of FLIP
5. once the driver is installed, run flip
6. Device -> Select: choose ATMega32U4
7. Settings -> Communication -> USB, FLIP should show the signature at this point (58 1E 95 87)
8. File -> Load HEX file: choose the hex firmware: <firmware>.hex
9. click "Run"
10. after programming is done, disconnect the device from USB and connect again.


**Programming the firmware (Linux)**

1. Download and install/compile/unpack dfu-programmer from http://dfu-programmer.sourceforge.net/.
2. Issue the following commands in the command prompt after connecting the device and pressing the programming button (S1). You may need root permissions or udev rules to do that.
  1. `sudo dfu-programmer atmega32u4 erase`
  2. `sudo dfu-programmer atmega32u4 flash <firmware>.hex`
  3. `sudo dfu-programmer atmega32u4 start`
3. The keyboard should start working. If it doesn't, reconnect the cable.

## Building the firmware

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

    $ make [custom|poker|poker_set|poker_bit|plain|hasu|spacefn|hhkb|<name>]

For a more detailed explanation of the build process and the environment setup, see the ["Getting Started" section](/readme.md#getting-started).

## List of included Keymaps

Several versions of keymaps are available in advance but you are recommended to define your favorite layout yourself. 
To define your own keymap, copy the [default keymap template](/quantum/template/keymaps/default) directory into the `keymaps` directory and start modifying the `keymap.c` file. Some options might require you to change the `config.h` or `Makefile` as well, refer to the main documentation for more information on those.
If you want to later merge your finalised keymap into this repository to make it available for everyone, make sure to also modify the `readme.md` in your keymap directory to show a visual version of your keymap.

Here's a list of the standard layouts that are provided with the precompiled .hex-files.

### 0  Initial explanations
The █████ blocks on the layouts hides the switch positions that do not exist physically on the PCB. If you feel like hacking the keyboard and adding new keys, those are the positions that can be used. You'll have to modify the [keymap_common.h](keymap_common.h) file for that.

The ▒▒▒▒▒ blocks hides switch positions not used on this particular layout, but they do exist on the PCB.

There is no LED support on the PCB at the moment, but I'll let the code for that untouched.


### 1  [Standard - ANSI (default layout)](keymaps/default/keymap.c)
The standard keymap is the one that is pre-flashed on the S60-X.

#### 1.0 Default layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │ ESC │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │▒▒▒▒▒│BKSPC│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │ TAB │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │CAPSL│  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │▒▒▒▒▒│ENTER│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │LSHFT│▒▒▒▒▒│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│RSHFT│▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │LCTRL│L_GUI│L_ALT│█████│█████│█████│ SPC │█████│█████│█████│R_ALT│ FN0 │ APP │RCTRL│█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
#### 1.1 Fn layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │GRAVE│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │ Up  │     │     │     │     │     │PGUP │PGDWN│PRTSC│SCLCK│PAUSE│     │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │Left │Down │Right│     │     │     │     │     │     │     │     │▒▒▒▒▒│     │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │     │█████│█████│█████│     │█████│█████│█████│     │     │     │     │█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘


### 2  [Standard - ISO](keymaps/iso/keymap.c)
The same as the standard keymap, but with additional ISO keys.


#### 2.0 Default layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │ ESC │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │▒▒▒▒▒│BKSPC│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │ TAB │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │▒▒▒▒▒│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │CAPSL│  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │NUHS │ENTER│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │LSHFT│  \  │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│RSHFT│▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │LCTRL│L_GUI│L_ALT│█████│█████│█████│ SPC │█████│█████│█████│R_ALT│ FN0 │ APP │RCTRL│█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
#### 2.1 Fn layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │GRAVE│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │ Up  │     │     │     │     │     │PGUP │PGDWN│PRTSC│SCLCK│PAUSE│▒▒▒▒▒│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │Left │Down │Right│     │     │     │     │     │     │     │     │     │     │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │     │█████│█████│█████│     │█████│█████│█████│     │     │     │     │█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘

    
### 3  Poker
[The poker keymap](keymaps/poker/keymap.c) emulates original Vortex Poker layers
while both [poker_bit](keymaps/poker_bit/keymap.c) and [poker_set](keymap/poker_set/keymap.c) implement the same layout in a slightly different way, fix a minor issue of the original poker Layout and enhance arrow keys.

    Fn + Esc = `
    Fn + {left, down, up, right}  = {home, pgdown, pgup, end}

#### 3.0 Default layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │▒▒▒▒▒│BkSpc│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Caps │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │▒▒▒▒▒│Enter│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Shift│▒▒▒▒▒│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│Shift│▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Ctrl │ Gui │ Alt │█████│█████│█████│Space│█████│█████│█████│ Fn  │ Gui │ App │Ctrl │█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
#### 3.1 Poker Fn layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │ Esc │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │ FnQ │ Up  │     │     │     │     │     │     │ Cal │     │Home │ Ins │     │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │Left │Down │Right│     │     │ Psc │ Slk │Pause│     │ Tsk │ End │▒▒▒▒▒│     │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │▒▒▒▒▒│ Del │     │ Web │Mute │ VoU │ VoD │     │PgUp │PgDwn│ Del │▒▒▒▒▒│ Up  │▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │     │█████│█████│█████│ FnS │█████│█████│█████│ Fn  │Left │Down │Right│█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘


### 4. [Plain](keymaps/plain/keymap.c)
Without any Fn layer this will be useful if you want to use key remapping tool like AHK on host.

#### 4.0 Plain Default layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │ Esc │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │▒▒▒▒▒│BkSpc│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Caps │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │▒▒▒▒▒│Enter│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Shift│▒▒▒▒▒│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│Shift│▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Ctrl │ Gui │ Alt │█████│█████│█████│Space│█████│█████│█████│ Alt │ Gui │ App │Ctrl │█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘


### 5. [Hasu](keymaps/hasu/keymap.c)
This is Hasu's favorite keymap with HHKB Fn, Vi cursor and Mousekey layer.

(Hasu is the creator of the TMK firmware, for those who do not know that.)


### 6. [SpaceFN](keymaps/spacefn/keymap.c)
This layout proposed by spiceBar uses space bar to change layer with using Dual role key technique. Check the sourcefile and [SpaceFN discussion](http://geekhack.org/index.php?topic=51069.0) for more information.

#### 6.0 Default layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │ Esc │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │▒▒▒▒▒│BkSpc│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Caps │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │▒▒▒▒▒│Enter│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Shift│▒▒▒▒▒│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│Shift│▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Ctrl │ Gui │ Alt │█████│█████│████ Space/Fn ███│█████│█████│ Alt │ Gui │ App │Ctrl │█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
#### 6.1 SpaceFN layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │  `  │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│ Del │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │     │     │     │     │     │Home │ Up  │ End │ Psc │ Slk │Pause│ Ins │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │     │     │     │     │PgUp │Left │Down │Right│     │     │▒▒▒▒▒│     │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │▒▒▒▒▒│     │     │     │     │Space│PgDwn│  `  │  ~  │     │     │▒▒▒▒▒│     │▒▒▒▒▒│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │     │     │█████│█████│█████│ Fn  │█████│█████│█████│ Alt │ Gui │ App │Ctrl │█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘


### 7. [HHKB](keymap/hhkb/keymap.c)
The HHKB keymap emulates original HHKB layers.
#### 7.0: Default layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │ Esc │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │  \  │  `  │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │BkSpc│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Ctrl │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │ Fn3 │  '  │▒▒▒▒▒│Enter│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Shift│▒▒▒▒▒│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│Shift│ Fn  │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │▒▒▒▒▒│ Gui │ Alt │█████│█████│█████│Space│█████│█████│█████│▒▒▒▒▒│ Alt │ Gui │▒▒▒▒▒│█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
#### 7.1: HHKB Fn layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │ Pwr │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │ Ins │ Del │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Caps │     │     │     │     │     │     │     │ Psc │ Slk │ Pus │ Up  │     │     │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │ VoD │ VoU │ Mut │ Ejc │     │  *  │  /  │Home │PgUp │Left │Right│▒▒▒▒▒│Enter│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │     │▒▒▒▒▒│     │     │     │     │     │  +  │  -  │ End │PgDwn│Down │▒▒▒▒▒│     │     │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │▒▒▒▒▒│     │     │█████│█████│█████│     │█████│█████│█████│▒▒▒▒▒│     │     │▒▒▒▒▒│█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘

    
### 8  [Custom](keymaps/custom/keymap.c)
The custom keymap is where I tested all the switches, not being concerned with a specific layout or layers. It's a plain layout option with the extra keys used on ISO & HHKB layouts being assigned some other keys.

#### 8.0 Default layer
    ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
    │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │PgUp │BkSpc│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  │█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Caps │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │PgDwn│Enter│█████│
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Shift│Home │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │ End │Shift│  Up │
    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
    │Ctrl │ Gui │ Alt │█████│█████│█████│Space│█████│█████│█████│ Alt │ Gui │ App │Ctrl │█████│
    └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘

### 9. [ANSI_QWERTZ](keymaps/ansi_qwertz/keymap.c)

This keymap was designed for inputting characters with diacritics with ANSI keycaps. 
It provides toggleable SpaceFn functionality, a dedicated arrow cluster and a microphone mute key on the function layer as well as a bootloader reset key.

For more info, [check here](keymaps/ansi_qwertz/readme.md).
