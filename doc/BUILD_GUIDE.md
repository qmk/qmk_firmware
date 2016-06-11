# Build Guide

## Build Environment Setup

### Windows (Vista and later)
1. If you have ever installed WinAVR, uninstall it.
2. Install [MHV AVR Tools](https://infernoembedded.com/sites/default/files/project/MHV_AVR_Tools_20131101.exe). Disable smatch, but **be sure to leave the option to add the tools to the PATH checked**.
3. Install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). During installation, uncheck the option to install a graphical user interface. **DO NOT change the default installation folder.** The scripts depend on the default location.
4. Clone this repository. [This link will download it as a zip file, which you'll need to extract.](https://github.com/jackhumbert/qmk_firmware/archive/master.zip) Open the extracted folder in Windows Explorer.
5. Double-click on the 1-setup-path-win batch script to run it. You'll need to accept a User Account Control prompt. Press the spacebar to dismiss the success message in the command prompt that pops up.
6. Right-click on the 2-setup-environment-win batch script, select "Run as administrator", and accept the User Account Control prompt. This part may take a couple of minutes, and you'll need to approve a driver installation, but once it finishes, your environment is complete!
7. Future build commands should be run from the standard Windows command prompt, which you can find by searching for "command prompt" from the start menu or start screen. Ignore the "MHV AVR Shell".

### Mac
If you're using [homebrew,](http://brew.sh/) you can use the following commands:

    brew tap osx-cross/avr
    brew install avr-libc
    brew install dfu-programmer

This is the recommended method. If you don't have homebrew, [install it!](http://brew.sh/) It's very much worth it for anyone who works in the command line.

You can also try these instructions:

1. Install Xcode from the App Store.
2. Install the Command Line Tools from `Xcode->Preferences->Downloads`.
3. Install [DFU-Programmer][dfu-prog].

### Linux
Install AVR GCC, AVR libc, and dfu-progammer with your favorite package manager.

Debian/Ubuntu example: 

    sudo apt-get update
    sudo apt-get install gcc-avr avr-libc dfu-programmer

### Vagrant
If you have any problems building the firmware, you can try using a tool called Vagrant. It will set up a virtual computer with a known configuration that's ready-to-go for firmware building. OLKB does NOT host the files for this virtual computer. Details on how to set up Vagrant are in the [VAGRANT_GUIDE file](VAGRANT_GUIDE.md).

## Verify Your Installation
1. If you haven't already, obtain this repository ([https://github.com/jackhumbert/qmk_firmware](https://github.com/jackhumbert/qmk_firmware)). You can either download it as a zip file and extract it, or clone it using the command line tool git or the Github Desktop application. 
2. Open up a terminal or command prompt and navigate to the `qmk_firmware` folder using the `cd` command. The command prompt will typically open to your home directory. If, for example, you cloned the repository to your Documents folder, then you would type `cd Documents/qmk_firmware`. If you extracted the file from a zip, then it may be named `qmk_firmware-master` instead. 
3. To confirm that you're in the correct location, you can display the contents of your current folder using the `dir` command on Windows, or the `ls` command on Linux or Mac. You should see several files, including `README.md` and a `quantum` folder. From here, you need to navigate to the appropriate folder under `keyboard/`. For example, if you're building for a Planck, run `cd keyboard/planck`.
4. Once you're in the correct keyboard-specific folder, run the `make` command. This should output a lot of information about the build process. More information about the `make` command can be found below.

## Customizing, Building, and Deploying Your Firmware

### The Make command

The `make` command is how you compile the firmware into a .hex file, which can be loaded by a dfu programmer (like dfu-progammer via `make dfu`) or the [Teensy loader](https://www.pjrc.com/teensy/loader.html) (only used with Teensys). You can run `make` from the root (`/`), your keyboard folder (`/keyboard/<keyboard>/`), or your keymap folder (`/keyboard/<keyboard>/keymaps/<keymap>/`) if you have a `Makefile` there (see the example [here](/doc/keymap_makefile_example.mk)).
 
By default, this will generate a <keyboard>_<keymap>.hex file in whichever folder you run make from. These files are ignored by git, so don't worry about deleting them when committing/creating pull requests. You .hex file will also be copied into your keymap folder as `compiled.hex`, which isn't ignore by git - this is included in case first-time users are having trouble compiling, and just want to flash a layout via `make dfu-no-build`.

* The "root" (`/`) folder is the qmk_firmware folder, in which are `doc`, `keyboard`, `quantum`, etc.
* The "keyboard" folder is any keyboard project's folder, like `/keyboard/<keyboard>`
* The "keymap" folder is any keymap's folder, like `/keyboard/<keyboard>/keymaps/<keymap>/`

Below is a list of the useful `make` commands in QMK:

* `make` - cleans automatically and builds your keyboard and keymap depending on which folder you're in. This defaults to the "default" layout (unless in a keymap folder), and Planck keyboard in the root folder
  * `make keyboard=<keyboard>` - specifies the keyboard (only to be used in root)
  * `make keymap=<keymap>` - specifies the keymap (only to be used in root and keyboard folder - not needed when in keymap folder)
* `make quick` - skips the clean step (only use when modifying .c code in the same project - at least one `make` is required)
* `make dfu` - (requires dfu-programmer) builds and flashes the keymap to your keyboard once placed in reset/dfu mode (button or press KC_RESET).
  * `keyboard=` and `keymap=` are compatible with this
* `make dfu-no-build` - (requires dfu-programmer) same as `make dfu`, but doesn't build and uses the included `compiled.hex` to flash the keyboard
* `make all-keyboards` - builds all keymaps for all keyboards and outputs status of each (use in root)
* `make all-keyboards-default` - builds all default keymaps for all keyboards and outputs status of each (use in root)
* `make all-keymaps [keyboard=<keyboard>]` - builds all of the keymaps for whatever keyboard folder you're in, or specified by `<keyboard>`

Other, less useful functionality:

* `make COLOR=false` - turns off color output
* `make SILENT=true` - turns off output besides errors/warnings
* `make VERBOSE=true` - outputs all of the avr-gcc stuff (not interesting)

### The Makefile

There are 3 different `make` and `Makefile` locations: 

* root (`/`)
* keyboard (`/keyboard/<keyboard>/`)
* keymap (`/keyboard/<keyboard>/keymaps/<keymap>/`)

The root contains all of the automatic keymap/keyboard stuff, is static, and shouldn't be modified. The keyboard one will contain the MCU set-up and default settings for your keyboard, and shouldn't be modified unless you are the producer of that keyboard. The keymap Makefile can be modified by users, and is optional. It is included automatically if it exists. You can see an example [here](/doc/keymap_makefile_example.mk) - the last few lines are the most important. The settings you set here will override any defaults set in the keyboard Makefile. It is required if you want to run `make` in the keymap folder.

### The `config.h` file

There are 2 `config.h` locations:

* keyboard (`/keyboard/<keyboard>/`)
* keymap (`/keyboard/<keyboard>/keymaps/<keymap>/`)

The keyboard `config.h` is included only if the keymap one doesn't exist. It's possible to included both by using this code at the top of your keymap's `config.h`:

    #include "../../config.h"
    
You can then overwrite any settings, rather than having to copy and paste the whole thing. You may need to `undefine` things to prevent warnings.


## Helpful Tips
1. On Linux or OS X, you can run `sleep 5; make keymap=<keymap> dfu` to delay building/deploying the firmware until for 5 seconds, giving you a chance to put the firmware into bootloader mode. You can change the 5 to any number of seconds.

## Troubleshooting

	WIP
