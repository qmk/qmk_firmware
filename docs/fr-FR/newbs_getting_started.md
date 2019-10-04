# Introduction

Your computer keyboard has a processor inside of it, not unlike the one inside your computer. This processor runs software that is responsible for detecting button presses and sending reports about the state of the keyboard when buttons are pressed or released. QMK fills the role of that software, detecting button presses and passing that information on to the host computer. When you build your custom keymap, you are creating the equivalent of an executable program for your keyboard.

QMK tries to put a lot of power into your hands by making easy things easy, and hard things possible. You don't have to know how to program to create powerful keymaps — you only have to follow a few simple syntax rules.

# Getting Started

Before you can build keymaps, you need to install some software and set up your build environment. This only has to be done once no matter how many keyboards you plan to compile firmware for. 

If you would prefer a more graphical user interface approach, please consider using the online [QMK Configurator](https://config.qmk.fm). Please refer to [Building Your First Firmware using the online GUI](newbs_building_firmware_configurator.md). 


## Download Software

### Text Editor

You'll need a program that can edit and save **plain text** files. If you're on Windows you can make do with Notepad, and on Linux you can use gedit. Both of these are simple but functional text editors. On macOS, be careful with the default TextEdit app: it will not save plain text files unless you explicitly select _Make Plain Text_ from the _Format_ menu.

You can also download and install a dedicated text editor like [Sublime Text](https://www.sublimetext.com/) or [VS Code](https://code.visualstudio.com/). This is probably the best way to go regardless of platform, as these programs are specifically made for editing code.

?> Not sure which text editor to use? Laurence Bradford wrote [a great introduction](https://learntocodewith.me/programming/basics/text-editors/) to the subject.

### QMK Toolbox

QMK Toolbox is an optional graphical program for Windows and macOS that allows you to both program and debug your custom keyboard. You will likely find it invaluable for easily flashing your keyboard and viewing debug messages that it prints.

[Download the latest release here.](https://github.com/qmk/qmk_toolbox/releases/latest)

* For Windows: `qmk_toolbox.exe` (portable) or `qmk_toolbox_install.exe` (installer)
* For macOS: `QMK.Toolbox.app.zip` (portable) or `QMK.Toolbox.pkg` (installer)

## Set Up Your Environment

We've tried to make QMK as easy to set up as possible. You only have to prepare your Linux or Unix environment, then let QMK install the rest.

?> If you haven't worked with the Linux/Unix command line before, there are a few basic concepts and commands you should learn. These resources will teach you enough to be able to work with QMK:<br>
[Must Know Linux Commands](https://www.guru99.com/must-know-linux-commands.html)<br>
[Some Basic Unix Commands](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

You will need to install MSYS2 and Git.

* Follow the installation instructions on the [MSYS2 homepage](http://www.msys2.org).
* Close any open MSYS2 terminals and open a new MSYS2 MinGW 64-bit terminal.
* Install Git by running this command: `pacman -S git`.

### macOS

You will need to install Homebrew. Follow the instructions on the [Homebrew homepage](https://brew.sh).

After Homebrew is installed, continue with _Set Up QMK_. In that step you will run a script that will install other packages.

### Linux

You will need to install Git. It's very likely that you already have it, but if not, one of the following commands should install it:

* Debian / Ubuntu / Devuan: `apt-get install git`
* Fedora / Red Hat / CentOS: `yum install git`
* Arch: `pacman -S git`

?> Docker is also an option on all platforms. [Click here for details.](getting_started_build_tools.md#docker)

## Set Up QMK

Once you have set up your Linux/Unix environment, you are ready to download QMK. We will do this by using Git to "clone" the QMK repository. Open a Terminal or MSYS2 MinGW window and leave it open for the remainder of this guide. Inside that window run these two commands:

```shell
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

?> If you already know [how to use GitHub](getting_started_github.md), we recommend that you create and clone your own fork instead. If you don't know what that means, you can safely ignore this message.

QMK comes with a script to help you set up the rest of what you'll need. You should run it now by typing in this command:

    util/qmk_install.sh

## Test Your Build Environment

Now that your QMK build environment is set up, you can build a firmware for your keyboard. Start by trying to build the keyboard's default keymap. You should be able to do that with a command in this format:

    make <keyboard>:default

For example, to build a firmware for a Clueboard 66% you would use:

    make clueboard/66/rev3:default

When it is done you should have a lot of output that ends similar to this:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# Creating Your Keymap

You are now ready to create your own personal keymap! Move on to [Building Your First Firmware](newbs_building_firmware.md) for that.
