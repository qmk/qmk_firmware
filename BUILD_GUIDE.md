# Build Guide

## Build Environment Setup

### Windows
What these instructions look like depends on whether NoahAndrews's setup scripts get merged

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

### Vagrant
If you have any problems building the firmware, you can try using a tool called Vagrant. It will set up a virtual computer with a known configuration that's ready-to-go for firmware building. OLKB does NOT host the files for this virtual computer. Details on how to set up Vagrant are in the [VAGRANT_GUIDE file](VAGRANT_GUIDE.md).