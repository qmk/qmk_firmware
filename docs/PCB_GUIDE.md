# Planck Firmware Guide

## Setting up the environment

### Windows
1. Install [MHV AVR Tools](https://infernoembedded.com/sites/default/files/project/MHV_AVR_Tools_20131101.exe). Disable smatch, but **be sure to leave the option to add the tools to the PATH checked**.
2. Install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). During installation, uncheck the option to install a graphical user interface. **DO NOT change the default installation folder.** The scripts depend on the default location.
3. Clone this repository. [This link will download it as a zip file, which you'll need to extract.](https://github.com/qmk/qmk_firmware/archive/master.zip) Open the extracted folder in Windows Explorer.
4. Right-click on the 1-setup-path-win batch script, select "Run as administrator", and accept the User Account Control prompt. Press the spacebar to dismiss the success message in the command prompt that pops up.
5. Right-click on the 2-setup-environment-win batch script, select "Run as administrator", and accept the User Account Control prompt. This part may take a couple of minutes, and you'll need to approve a driver installation, but once it finishes, your environment is complete!


### Mac

If you're using homebrew, you can use the following commands:

    brew tap osx-cross/avr
    brew install avr-libc
    brew install dfu-programmer

Otherwise, these instructions will work:

1. Install Xcode from the App Store.
2. Install the Command Line Tools from `Xcode->Preferences->Downloads`.
3. Install [DFU-Programmer][dfu-prog].

### Linux
1. Install AVR GCC with your favorite package manager.
2. Install [DFU-Programmer][dfu-prog].

Note that, since it will be directly accessing USB hardware, the
`dfu-programmer` program needs to be run as root.

## Verify Your Installation
1. Clone the following repository: https://github.com/qmk/qmk_firmware
2. Open a Terminal and `cd` into `qmk_firmware/keyboards/planck`
3. Run `make`. This should output a lot of information about the build process.

## Using the built-in functions

Here is a list of some of the functions available from the command line:

* `make clean`: clean the environment - may be required in-between builds
* `make`: compile the code
* `make KEYMAP=<keymap>`: compile with the extended keymap file `extended_keymaps/extended_keymap_<keymap>.c`
* `make dfu`: build and flash the layout to the PCB
* `make dfu-force`: build and force-flash the layout to the PCB (may be require for first flash)

Generally, the instructions to flash the PCB are as follows:

1. Make changes to the appropriate keymap file
2. Save the file
3. `make clean`
4. Press the reset button on the PCB/press the key with the `RESET` keycode
5. `make <arguments> dfu` - use the necessary `KEYMAP=<keymap>` and/or `COMMON=true` arguments here.

## Troubleshooting
If you see something like this

          0 [main] sh 13384 sync_with_child: child 9716(0x178) died before initialization with status code 0xC0000142
        440 [main] sh 13384 sync_with_child: *** child state waiting for longjmp
    /usr/bin/sh: fork: Resource temporarily unavailable

after running 'make' on Windows than you are encountering a very popular issue with WinAVR on Windows 8.1 and 10.
You can easily fix this problem by replacing msys-1.0.dll in WinAVR/utils/bin with [this one](http://www.madwizard.org/download/electronics/msys-1.0-vista64.zip).
Restart your system and everything should work fine!


If you see this

    dfu-programmer atmega32u4 erase
    process_begin: CreateProcess(NULL, dfu-programmer atmega32u4 erase, ...) failed.
    make (e=2): The system cannot find the file specified.
    make: *** [dfu] Error 2

when trying to 'make dfu' on Windows you need to copy the dfu-programmer.exe to qmk_firmware/keyboards/planck.


## Quantum MK Firmware

### Keymap

Unlike the other keymaps, prefixing the keycodes with `KC_` is required. A full list of the keycodes is available [here](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/doc/keycode.txt). For the keycodes available only in the extended keymap, see this [header file](https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_common.h).

You can use modifiers with keycodes like this:

    LCTL(KC_C)
    
Which will generate Ctrl+c. These are daisy-chainable, meaning you can do things like:

    LCTL(LALT(KC_C))
    
That will generate Ctrl+Alt+c. The entire list of these functions is here:

* `LCTL()`: Left control
* `LSFT()` / `S()`: Left shift
* `LALT()`: Left alt/opt
* `LGUI()`: Left win/cmd
* `RCTL()`: Right control
* `RSFT()`: Right shift
* `RALT()`: Right alt/opt
* `RGUI()`: Right win/cmd

`S(KC_1)`-like entries are useful in writing keymaps for the Planck.

### Other keycodes

A number of other keycodes have been added that you may find useful:

* `CM_<key>`: the Colemak equivalent of a key (in place of `KC_<key>`), when using Colemak in software (`CM_O` generates `KC_SCLN`)
* `RESET`: jump to bootloader for flashing (same as press the reset button)
* `BL_STEP`: step through the backlight brightnesses
* `BL_<0-15>`: set backlight brightness to 0-15
* `BL_DEC`: lower the backlight brightness
* `BL_INC`: raise the backlight brightness
* `BL_TOGG`: toggle the backlight on/off

### Function layers

The extended keymap extends the number of function layers from 32 to the near-infinite value of 256. Rather than using `FN<num>` notation (still available, but limited to `FN0`-`FN31`), you can use the `FUNC(<num>)` notation. `F(<num>)` is a shortcut for this.

The function actions are unchanged, and you can see the full list of them [here](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/action_code.h). They are explained in detail [here](keymap.md#2-action).

### Macros

Macros have been setup in the `keymaps/keymap_default.c` file so that you can use `M(<num>)` to access a macro in the `action_get_macro` section on your keymap. The switch/case structure you see here is required, and is setup for `M(0)` - you'll need to copy and paste the code to look like this (e.g. to support `M(3)`):

    switch(id) {
      case 0:
        return MACRODOWN(TYPE(KC_A), END);
        break;
      case 1:
        return MACRODOWN(TYPE(KC_B), END);
        break;
      case 2:
        return MACRODOWN(TYPE(KC_C), END);
        break;
      case 3:
        return MACRODOWN(TYPE(KC_D), END);
        break;
    } 
    return MACRO_NONE;

`MACRODOWN()` is a shortcut for `(record->event.pressed ? MACRO(__VA_ARGS__) : MACRO_NONE)` which tells the macro to execute when the key is pressed. Without this, the macro will be executed on both the down and up stroke.

[cygwin]:       https://www.cygwin.com/
[mingw]:        http://www.mingw.org/
[mhv]:          https://infernoembedded.com/products/avr-tools
[winavr]:       http://winavr.sourceforge.net/
[crosspack]:    http://www.obdev.at/products/crosspack/index.html
[dfu-prog]:     http://dfu-programmer.sourceforge.net/
