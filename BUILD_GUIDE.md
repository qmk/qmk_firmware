# Build Guide

## Build Environment Setup

### Windows
1. Install [MHV AVR Tools](https://infernoembedded.com/sites/default/files/project/MHV_AVR_Tools_20131101.exe). Disable smatch, but **be sure to leave the option to add the tools to the PATH checked**.
2. Install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). During installation, uncheck the option to install a graphical user interface. **DO NOT change the default installation folder.** The scripts depend on the default location.
3. Clone this repository. [This link will download it as a zip file, which you'll need to extract.](https://github.com/jackhumbert/qmk_firmware/archive/master.zip) Open the extracted folder in Windows Explorer.
4. Right-click on the 1-setup-path-win batch script, select "Run as administrator", and accept the User Account Control prompt. Press the spacebar to dismiss the success message in the command prompt that pops up.
5. Right-click on the 2-setup-environment-win batch script, select "Run as administrator", and accept the User Account Control prompt. This part may take a couple of minutes, and you'll need to approve a driver installation, but once it finishes, your environment is complete!

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
Install AVR GCC and dfu-progammer with your favorite package manager.

Debian/Ubuntu example: 

    sudo apt-get update
    sudo apt-get install gcc-avr dfu-programmer

### Vagrant
If you have any problems building the firmware, you can try using a tool called Vagrant. It will set up a virtual computer with a known configuration that's ready-to-go for firmware building. OLKB does NOT host the files for this virtual computer. Details on how to set up Vagrant are in the [VAGRANT_GUIDE file](VAGRANT_GUIDE.md).

## Verify Your Installation
1. If you haven't already, obtain this repository ([https://github.com/jackhumbert/qmk_firmware](https://github.com/jackhumbert/qmk_firmware)). You can either download it as a zip file and extract it, or clone it using the command line tool git or the Github Desktop application. 
2. Open up a terminal or command prompt and navigate to the qmk_firmware folder using the `cd` command. The command prompt will typically open to your home directory. If, for example, you cloned the repository to your Documents folder, then you would type `cd Documents/qmk_firmware`. If you extracted the file from a zip, then it may be named `qmk_firmware-master` instead. 
3. To confirm that you're in the correct location, you can display the contents of your current folder using the `dir` command on Windows, or the `ls` command on Linux or Mac. You should see several files, including `README.md` and a `quantum` folder. From here, you need to navigate to the appropriate folder under `keyboard/`. For example, if you're building for a Planck, run `cd keyboard/planck`.
4. Once you're in the correct keyboard-specific folder, run the `make` command. This should output a lot of information about the build process.

## Customizing, Building, and Deploying Your Firmware
1. Running the `make` command from your keyboard's folder will generate a .hex file based on the default keymap. All keymaps for a particular keyboard live in the `keymaps` folder in that keyboard's folder. To create your own keymap, copy `keymaps/default/keymap.c` to the `keymaps` folder, and rename it with your name, for example jack.c. Or, if you don't care about the ability to share your keymap with the community via GitHub, you can just modify the default keymap itself. Details on how to program keymap files can be found in other guides.
2. To build a keymap other than the default, type `KEYMAP=<name>` after `make`. So if I've named my keymap jack.c, the full command would be `make KEYMAP=jack`.
3. How you deploy the firmware will depend on whether you are using a PCB or a Teensy. In both cases, you'll need to put the keyboard in bootloader mode, either by pressing a button on the PCB/Teensy or pressing the key with the `RESET` keycode. Then, if you're using a PCB, just run `make KEYMAP=<name> dfu` to both build and deploy the firmware. If you're using a Teensy, you'll probably need to take the <keyboardname>.hex file that make produces in the keyboard's folder, and deploy it using the [Teensy Loader.](https://www.pjrc.com/teensy/loader.html)

## Helpful Tips
1. On Linux or OS X, you can run `sleep 5; make KEYMAP=<name> dfu` to delay building/deploying the firmware until for 5 seconds, giving you a chance to put the firmware into bootloader mode. You can change the 5 to any number of seconds.

## Troubleshooting
1. Try running `make clean` if the make command fails.

	WIP