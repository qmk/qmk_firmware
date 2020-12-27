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

## 2. Prepare Your Build Environment :id=set-up-your-environment

We've tried to make QMK as easy to set up as possible. You only have to prepare your Linux or Unix environment, then let QMK install the rest.

?> If you haven't worked with the Linux/Unix command line before, there are a few basic concepts and commands you should learn. These resources will teach you enough to be able to work with QMK:<br>
[Must Know Linux Commands](https://www.guru99.com/must-know-linux-commands.html)<br>
[Some Basic Unix Commands](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

<!-- tabs:start -->

### ** Windows **

#### Prerequisites

You will need to install MSYS2, Git and Python. Follow the installation instructions on https://www.msys2.org.

Once MSYS2 is installed, close any open MSYS terminals and open a new MinGW 64-bit terminal.

!> **NOTE:** The MinGW 64-bit terminal is *not* the same as the MSYS terminal that opens when installation is completed. Your prompt should say "MINGW64" in purple text, rather than "MSYS". See [this page](https://www.msys2.org/wiki/MSYS2-introduction/#subsystems) for more information on the differences.

Then run the following command:

    pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip

#### Installation

Install the QMK CLI by running:

    python3 -m pip install qmk

### ** macOS **

QMK maintains a Homebrew tap and formula which will automatically install the CLI and all necessary dependencies.

#### Prerequisites

You will need to install Homebrew. Follow the instructions on https://brew.sh.

#### Installation

Install the QMK CLI by running:

    brew install qmk/qmk/qmk

### ** Linux/WSL **

#### Prerequisites

You will need to install Git and Python. It's very likely that you already have both, but if not, one of the following commands should install them:

* Debian / Ubuntu / Devuan: `sudo apt install -y git python3-pip`
* Fedora / Red Hat / CentOS: `sudo yum -y install git python3-pip`
* Arch / Manjaro: `sudo pacman --needed --noconfirm -S git python-pip libffi`
* Void: `sudo xbps-install -y git python3-pip`
* Solus: `sudo eopkg -y install git python3`
* Sabayon: `sudo equo install dev-vcs/git dev-python/pip`
* Gentoo: `sudo emerge dev-vcs/git dev-python/pip`

#### Installation

Install the QMK CLI by running:

    python3 -m pip install --user qmk

On Arch-based distros you can also try the `qmk` package from AUR (**NOTE**: this package is maintained by a community member, and at the time of writing marks some dependencies as optional that should not be):

    yay -S qmk

###  ** FreeBSD **

#### Prerequisites

You will need to install Git and Python. It's possible that you already have both, but if not, run the following commands to install them:

    pkg install git python3

Make sure that `$HOME/.local/bin` is added to your `$PATH` so that locally installed Python packages are available.

#### Installation

Install the QMK CLI by running:

    python3 -m pip install --user qmk

<!-- tabs:end -->

## 3. Run QMK Setup :id=set-up-qmk

<!-- tabs:start -->

### ** Windows **

After installing QMK you can set it up with this command:

    qmk setup

In most situations you will want to answer `y` to all of the prompts.

### ** macOS **

After installing QMK you can set it up with this command:

    qmk setup

In most situations you will want to answer `y` to all of the prompts.

### ** Linux/WSL **

After installing QMK you can set it up with this command:

    qmk setup

In most situations you will want to answer `y` to all of the prompts.

?>**Note on Debian, Ubuntu and their derivatives**:
It's possible, that you will get an error saying something like: `bash: qmk: command not found`.
This is due to a [bug](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=839155) Debian introduced with their Bash 4.4 release, which removed `$HOME/.local/bin` from the PATH. This bug was later fixed on Debian and Ubuntu.
Sadly, Ubuntu reitroduced this bug and is [yet to fix it](https://bugs.launchpad.net/ubuntu/+source/bash/+bug/1588562).
Luckily, the fix is easy. Run this as your user: `echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc`

###  ** FreeBSD **

After installing QMK you can set it up with this command:

    qmk setup

In most situations you will want to answer `y` to all of the prompts.

?>**Note on FreeBSD**:
It is suggested to run `qmk setup` as a non-`root` user to start with, but this will likely identify packages that need to be installed to your
base system using `pkg`. However the installation will probably fail when run as an unprivileged user.
To manually install the base dependencies, run `./util/qmk_install.sh` either as `root`, or with `sudo`.
Once that completes, re-run `qmk setup` to complete the setup and checks.

<!-- tabs:end -->

?> If you already know [how to use GitHub](getting_started_github.md), we recommend that you create your own fork and use `qmk setup <github_username>/qmk_firmware` to clone your personal fork. If you don't know what that means you can safely ignore this message.

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

You can also set your default keymap name. Most people use their GitHub username here, and we recommend that you do too.

    qmk config user.keymap=<github_username>

After this you can leave those arguments off and compile your keyboard like this:

    qmk compile

# Creating Your Keymap

You are now ready to create your own personal keymap! Move on to [Building Your First Firmware](newbs_building_firmware.md) for that.
