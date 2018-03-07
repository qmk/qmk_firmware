# Introduction

Your computer keyboard has a processor inside of it, not unlike the one inside your computer. This processor runs software that is responsible for detecting button presses and sending reports about the state of the keyboard when they are pressed or released. QMK fills the role of that software, detecting button presses and passing that information on to the host computer. When you build your custom layout you are creating the equivalent of an .exe for your keyboard.

QMK tries to put a lot of power into your hands by making easy things easy, and hard things possible. You don't have to know how to program to create powerful layouts, you only have to follow a few simple syntax rules. 

# Getting Started

Before you can build keymaps you need to install some software and setup your build environment. This only has to be done one time no matter how many keyboards you want to compile firmware for.

## Download Software

### Text Editor

You'll need a program that can edit and save **plain text** files. If you are on Windows you can make due with Notepad, and on Linux you can use Gedit, both of which are simple but functional text editors. On macOS you can not use TextEdit.app, it will not save plain text files. You will need to install another program such as Sublime Text.

{% hint style='info' %}
Not sure which text editor to use? Laurence Bradford wrote [a great introduction](https://learntocodewith.me/programming/basics/text-editors/) to the subject.
{% endhint %}

### QMK Toolbox

QMK Toolbox is a Windows and macOS program that allows you to both program and debug your custom keyboard. You will want to install it so that you can easily flash your keyboard and receive the debugging messages that your keyboard will print.

* [Newest Release](https://github.com/qmk/qmk_toolbox/releases/latest)
* [Source Code](https://github.com/qmk/qmk_toolbox/)

## Environment Setup

We've tried to make QMK as easy to setup as possible. You only have to prepare your Linux or Unix environment and let QMK install the rest.

{% hint style="info" %}
If you haven't worked with the Linux/Unix command line before there are a few basic concepts and commands you should learn. These resources will teach you enough to work with QMK:

* [Must Know Linux Commands](https://www.guru99.com/must-know-linux-commands.html)
* [Some Basic Unix Commands](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)
{% endhint %}

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

    git clone https://github.com/qmk/qmk_firmware.git
    cd qmk_firmware

{% hint style='info' %}
If you already know [how to use GitHub](getting_started_github.md) we recommend you create and clone your own fork instead. If you don't know what that means you can safely ignore this message.
{% endhint %}

## Setup QMK

QMK comes with a script to help you setup the rest of what you'll need. You should run it now by typing in this command:

    ./util/qmk_install.sh

## Test Your Build Environment

Now that your QMK build environment is setup you can build a firmware for your keyboard. Start by trying to build the default layout for your keyboard. You should be able to do that with a command in this format:

    make <keyboard>:default

For example, to build a firmware for a Clueboard 66% use:

    make clueboard/66/rev3:default

When it is done you should have a lot of output that ends similar to this:

```
Linking: .build/clueboard_66_rev2_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev2_default.hex                               [OK]
Copying clueboard_66_rev2_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev2_default.hex                                                 [OK]
 * File size is fine - 25174/28672
```

## Creating Your Layout

Now you are ready to create your own personal layout. Move on to [Building Your First Firmware](newbs_building_firmware.md) for that.
