# Setting Up Your QMK Environment

Before you can build keymaps, you need to install some software and set up your build environment. This only has to be done once no matter how many keyboards you plan to compile firmware for.

## 1. Download Software

There are a few pieces of software you'll need to get started.

### Text Editor

You'll need a program that can edit and save **plain text** files. If you're on Windows you can make do with Notepad, and on Linux you can use gedit. Both of these are simple but functional text editors. On macOS, be careful with the default TextEdit app: it will not save plain text files unless you explicitly select _Make Plain Text_ from the _Format_ menu.

You can also download and install a dedicated text editor like [Sublime Text](https://www.sublimetext.com/) or [VS Code](https://code.visualstudio.com/). This is probably the best way to go regardless of platform, as these programs are specifically made for editing code.

?> Not sure which text editor to use? Laurence Bradford wrote [a great introduction](https://learntocodewith.me/programming/basics/text-editors/) to the subject.

### QMK Toolbox

QMK Toolbox is an optional graphical program for Windows and macOS that allows you to both program and debug your custom keyboard. You will likely find it invaluable for easily flashing your keyboard and viewing debug messages that it prints.

[Download the latest release here.](https://github.com/qmk/qmk_toolbox/releases/latest)

* For Windows: `qmk_toolbox.exe` (portable) or `qmk_toolbox_install.exe` (installer)
* For macOS: `QMK.Toolbox.app.zip` (portable) or `QMK.Toolbox.pkg` (installer)

### A Unix-like Environment

Linux and macOS come with unix shells you can execute already. You will only need to setup your build environment.

On Windows you will need to install MSYS2 or WSL and use those environments. Instructions for setting up MSYS2 are provided below.

## 2. Prepare Your Build Environment

We've tried to make QMK as easy to set up as possible. You only have to prepare your Linux or Unix environment, then let QMK install the rest.

?> If you haven't worked with the Linux/Unix command line before, there are a few basic concepts and commands you should learn. These resources will teach you enough to be able to work with QMK:<br>
[Must Know Linux Commands](https://www.guru99.com/must-know-linux-commands.html)<br>
[Some Basic Unix Commands](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

You will need to install MSYS2, Git, and the QMK CLI.

* Follow the installation instructions on the [MSYS2 homepage](http://www.msys2.org).
* Close any open MSYS2 terminals and open a new MSYS2 MinGW 64-bit terminal.

After opening a new MSYS2 MinGW 64-bit terminal run these commands:

    pacman -S git python3-pip
    python3 -m pip install qmk

### macOS

You will need to install Homebrew. Follow the instructions on the [Homebrew homepage](https://brew.sh).

After Homebrew is installed run these commands:

    brew tap qmk/qmk
    brew install qmk

### Linux

You will need to install Git and Python. It's very likely that you already have both, but if not, one of the following commands should install them:

* Debian / Ubuntu / Devuan: `apt-get install git python3 && python3 -m pip install qmk`
* Fedora / Red Hat / CentOS: `yum install git python3 && python3 -m pip install qmk`
* Arch: `pacman -S qmk`

## 3. Run QMK Setup

After installing QMK you can set it up with this command:

    qmk setup

In most situations you will want to answer Yes to all of the prompts.

?> If you already know [how to use GitHub](getting_started_github.md), we recommend that you create your own fork and use `qmk setup <github_username>` to clone your personal fork. If you don't know what that means you can safely ignore this message.

## 4. Test Your Build Environment

Now that your QMK build environment is set up, you can build a firmware for your keyboard. Start by trying to build the keyboard's default keymap. You should be able to do that with a command in this format:

    qmk compile -kb <keyboard> -km default

For example, to build a firmware for a Clueboard 66% you would use:

    qmk compile -kb clueboard/66/rev3 -km default

When it is done you should have a lot of output that ends similar to this:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

## 5. Configure Your Build Environment (Optional)

You can configure your build environment to set the defaults and make working with QMK less tedious. Let's do that now!

Most people new to QMK only have 1 keyboard. You can set this keyboard as your default with the `qmk config` command. For example, to set your default keyboard to `clueboard/66/rev4`:

    qmk config user.keyboard=clueboard/66/rev4

You can also set your default keymap name. Most people use their github username here, and we recommend that you do too.

    qmk config user.keymap=<github_username>

After this you can leave those arguments off and compile your keyboard like this:

    qmk compile

# Creating Your Keymap

You are now ready to create your own personal keymap! Move on to [Building Your First Firmware](newbs_building_firmware.md) for that.
