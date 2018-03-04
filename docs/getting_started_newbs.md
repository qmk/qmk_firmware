# The Compelete Newbs Guide To QMK

QMK is a powerful Open Source firmware for your mechanical keyboard. You can use QMK to customize your keyboard in ways both simple and powerful. People of all skill levels, from complete newbie to master programmer, have successfully used QMK to customize their keyboard. This guide aims to help you do the same, no matter your skill level.

There are 4 main sections to this guide:

* [Getting Started](#getting-started)
* [Building Your First Firmware](#building-your-first-firmware)
* [Flashing Firmware](#flashing-firmware)
* [Testing and Debugging](#testing-and-debugging)

This guide is not trying to be comprehensive. There are alternative methods for many of the procedures below, and we support many of those alternatives. However, these are the recommended procedures. You should use the methods outlined here unless you have a good reason to do otherwise.

## Overview

Your computer keyboard has a processor inside of it, not unlike the one inside your computer. This processor runs software that is responsible for detecting button presses and sending reports about the state of the keyboard when they are pressed or released. QMK fills the role of that software, detecting button presses and passing that information on to the host computer. When you build your custom layout you are creating the equivalent of an .exe for your keyboard.

QMK tries to put a lot of power into your hands by making easy things easy, and hard things possible. You don't have to know how to program to create powerful layouts, you only have to follow a few simple syntax rules. 

# Getting Started

Before you can build keymaps you need to setup your build environment. This only has to be done one time no matter how many keyboards you want to compile firmware for.

## Environment Setup

We've tried to make QMK as easy to setup as possible. You only have to prepare your Linux or Unix environment and let QMK install the rest.

### Windows

You will need to install msys2 and git.

* Follow the installation instructions on the msys2 homepage: http://www.msys2.org
* Close any open msys2 terminals, and open a new terminal
* Install git by running this command: `pacman -S git`

### macOS

You will need to install homebrew. Follow the instructions on the homebrew homepage: https://brew.sh

### Linux

You will need to install git. It's extremely likely you already have it, but if not one of the following commands should install it:

* Debian/Ubuntu/Devuan: `apt-get install git`
* Fedora/Redhat/Centos: `yum install git`
* Arch: `pacman -S git`

## Download QMK

Once you have setup your Linux/Unix environment you are ready to download QMK. We will do this by using git to "clone" the QMK repository. Open a Terminal or MSYS2 Console window and leave it open for the remainder of this guide. Inside that window run these two commands:

* `git clone https://github.com/qmk/qmk_firmware.git`
* `cd qmk_firmware`

{% hint style='info' %}
If you already know how to use GitHub we recommend you create and clone your own fork instead. If you don't know what that means you can safely ignore this message.
{% endhint %}

## Setup QMK

QMK comes with a script to help you setup the rest of what you'll need. You should run it now:

* `./util/qmk_install.sh`

## Test Your Build Environment

Now that your QMK build environment is setup you can build a firmware for your keyboard. Start by trying to build the default layout for your keyboard. You should be able to do that with a command in this format:

* `make <keyboard>:default`

For example, to build a firmware for a Clueboard 66% use:

* `make clueboard/66:default`

When it is done you should have a lot of output that ends similar to this:

```
Linking: .build/clueboard_66_rev2_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev2_default.hex                               [OK]
Copying clueboard_66_rev2_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev2_default.hex                                                 [OK]
 * File size is fine - 25174/28672
```

# Building Your First Firmware

Now that you have setup your build environment you are ready to start building custom firmware. For this section of the guide we will bounce between 3 programs- your file manager, your text editor, and your terminal window. Keep all 3 open until you are done and happy with your keyboard firmware.

If you have closed and reopened your terminal window since following the first part of the guide, don't forget to `cd qmk_firmware` so that your terminal is in the correct directory.

## Navigate To Your Keymaps Folder

Start by navigating to the `keymaps` folder for your keyboard.

{% hint style='info' %}
If you are on macOS or Windows there are commands you can use to easily open the `keymaps` folder.

macOS:

    open keyboards/<keyboard_folder>/keymaps

Windows:

    start keyboards/<keyboard_folder>/keymaps
{% endhint %}

## Create a Copy Of The `default` Keymap

Once you have the `keymaps` folder open you will want to create a copy of the `default` folder. We highly recommend you name your folder the same as your github username, but you can use any name you want as long as it contains only lower case letters, numbers, and the underscore character.

## Open `keymap.c` In Your Favorite Text Editor

Inside the `keymap.c` file you'll find the structure that controls how your keyboard behaves. At the top there may be some defines and enums that make the keymap easier to read. Farther down you'll find a line that looks like this:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

This line indicates the start of the list of Layers. Below that you'll find lines containing either `LAYOUT` or `KEYMAP`, and these lines indicate the start of a layer. Below that line is the list of keys that comprise a that particular layer.

{% hint style='warning' %}
When editing your keymap file be careful not to add or remove any commas. If you do you will prevent your firmware from compiling and it may not be easy to figure out where the extra, or missing, comma is.
{% endhint %}

## Customize The Layout To Your Liking

This step is entirely up to you. Make the one change that's been bugging you, or completely rework everything. You can remove layers if you don't need all of them, or add layers up to a total of 32. Check the following documentation to find out what you can define here:

* [Keycodes](keycodes.md)

# Flashing Firmware

# Testing And Debugging
