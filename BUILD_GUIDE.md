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