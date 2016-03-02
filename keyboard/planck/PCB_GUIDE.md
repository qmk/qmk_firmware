# Planck Firmware Guide

## Setting up the environment

### Windows

Options
1. Vagrant (overkill, lack of trust, no driver concerns)
2. Chocolatey / dfu-programmer (more dev work required)
3. Chocolatey / flip
4. Write a batch script that installs dfu-programmer on the path, installs make with MinGW, and uses pnputil to install the proper driver https://technet.microsoft.com/en-us/library/cc732377%28v=ws.10%29.aspx?f=255&MSPPError=-2147217396#BKMK_Anchor2
4. Look up altenatives (

* Install [MHV AVR Tools](https://github.com/jackhumbert/qmk_firmware). Disable smatch, but be sure to leave the option to add the tools to the PATH checked.
* Install the latest version of [the Atmel AVR **8-bit** toolchain](http://www.atmel.com/tools/atmelavrtoolchainforwindows.aspx)
* Install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). During installation, uncheck the option to install a graphical user interface. **DO NOT change the default installation folder.** The script depends on the default location.
* Right-click on the setup-path-win batch script at the root of the project and select "Run as administrator". Press the spacebar to dismiss the success message.
* 

1. Install [Chocolatey](https://chocolatey.org/). It's a package manager for Windows that will make it easy to set up the complete build environment. To install Chocolatey, run the following command in a command line window with administrator privileges (search for command prompt, right-click on it, and select "Run as administrator"). `@powershell -NoProfile -ExecutionPolicy Bypass -Command "iex ((new-object net.webclient).DownloadString('https://chocolatey.org/install.ps1'))" && SET PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin`
2. Install DFU-Programmer by running (the -win one).
3. Start DFU bootloader on the chip first time you will see 'Found New Hardware Wizard' to install driver. If you install device driver properly you can find chip name like 'ATmega32U4' under 'LibUSB-Win32 Devices' tree on 'Device Manager'. If not you will need to update its driver on 'Device Manager' to the `dfu-programmer` driver.

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
1. Clone the following repository: https://github.com/jackhumbert/qmk_firmware
2. Open a Terminal and `cd` into `qmk_firmware/keyboard/planck`
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

## Quantum MK Firmware

### Keymap

Unlike the other keymaps, prefixing the keycodes with `KC_` is required. A full list of the keycodes is available [here](https://github.com/jackhumbert/qmk_firmware/blob/master/tmk_core/doc/keycode.txt). For the keycodes available only in the extended keymap, see this [header file](https://github.com/jackhumbert/qmk_firmware/blob/master/quantum/keymap_common.h).

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

The function actions are unchanged, and you can see the full list of them [here](https://github.com/jackhumbert/tmk_keyboard/blob/master/common/action_code.h). They are explained in detail [here](https://github.com/jackhumbert/tmk_keyboard/blob/master/doc/keymap.md#2-action).

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
