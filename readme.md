# Quantum Mechanical Keyboard Firmware

[![Build Status](https://travis-ci.org/jackhumbert/qmk_firmware.svg?branch=master)](https://travis-ci.org/jackhumbert/qmk_firmware)

This is a keyboard firmware based on the [tmk_keyboard firmware](http://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR controllers, and more specifically, the [OLKB product line](http://olkb.com), the [ErgoDox EZ](http://www.ergodox-ez.com) keyboard, and the [Clueboard product line](http://clueboard.co/).

## Official website

For an easy-to-read version of this document and the repository, check out [http://qmk.fm](http://qmk.fm). Nicely formatted keyboard and keymap listings are also available there, along with the ability to download .hex files instead of having to setup a build environment and compile them.

## Included Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [Atomic](/keyboards/atomic/)
* [ErgoDox EZ](/keyboards/ergodox/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/cluepad/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). This repo used to be a fork of [TMK](https://github.com/tmk/tmk_keyboard), and we are incredibly grateful for his founding contributions to the firmware. We've had to break the fork due to purely technical reasons - it simply became too different over time, and we've had to start refactoring some of the basic bits and pieces. We are huge fans of TMK and Hasu :)

This documentation is edited and maintained by Erez Zukerman of ErgoDox EZ. If you spot any typos or inaccuracies, please [open an issue](https://github.com/jackhumbert/qmk_firmware/issues/new).

The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [Erez Zukerman](https://github.com/ezuk), and the Clueboard by [Zach White](https://github.com/skullydazed).

## Documentation roadmap

This is not a tiny project. While this is the main readme, there are many other files you might want to consult. Here are some points of interest:

* The readme for your own keyboard: This is found under `keyboards/<your keyboards's name>/`. So for the ErgoDox EZ, it's [here](keyboards/ergodox/ez/); for the Planck, it's [here](keyboards/planck/) and so on.
* The list of possible keycodes you can use in your keymap is actually spread out in a few different places:
  * [doc/keycode.txt](doc/keycode.txt) - an explanation of those same keycodes.
  * [quantum/keymap.h](quantum/keymap.h) - this is where the QMK-specific aliases are all set up. Things like the Hyper and Meh key, the Leader key, and all of the other QMK innovations. These are also explained and documented below, but `keymap.h` is where they're actually defined.
* The [TMK documentation](doc/TMK_README.md). QMK is based on TMK, and this explains how it works internally.

# Getting started

Before you are able to compile, you'll need to install an environment for AVR development. You'll find the instructions for any OS below. If you find another/better way to set things up from scratch, please consider [making a pull request](https://github.com/jackhumbert/qmk_firmware/pulls) with your changes!

## Build Environment Setup

### Windows 10

It's still recommended to use the method for Vista and later below. The reason for this is that the Windows 10 Subsystem for Linux lacks [USB support](https://wpdev.uservoice.com/forums/266908-command-prompt-console-bash-on-ubuntu-on-windo/suggestions/13355724-unable-to-access-usb-devices-from-bash), so it's not possible to flash the firmware to the keyboard. Please add your vote to the link!

That said, it's still possible to use it for compilation. And recommended, if you need to compile much, since it's much faster than at least Cygwin (which is also supported, but currently lacking documentation). I haven't tried the method below, so I'm unable to tell.

Here are the steps

1. Install the Windows 10 subsystem for Linux, following [these instructions](http://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/).
2. If you have previously cloned the repository using the normal Git bash, you will need to clean up the line endings. If you have cloned it after 20th of August 2016, you are likely fine. To clean up the line endings do the following
   1. Make sure that you have no changes you haven't committed by running `git status`, if you do commit them first
   2. From within the Git bash run `git rm --cached -r .`
   3. Followed by `git reset --hard`
3. Start the "Bash On Ubuntu On Windows" from the start menu
4. With the bash open, navigate to your Git checkout. The harddisk can be accessed from `/mnt` for example `/mnt/c` for the `c:\` drive.
5. Run `sudo util/install_dependencies.sh`.
6. After a while the installation will finish, and you are good to go

**Note** From time to time, the dependencies might change, so just run `install_dependencies.sh` again if things are not working.

**Warning:** If you edit Makefiles or shell scripts, make sure you are using an editor that saves the files with Unix line endings. Otherwise the compilation might not work.


### Windows (Vista and later)
1. If you have ever installed WinAVR, uninstall it.
2. Install [MHV AVR Tools](https://infernoembedded.com/sites/default/files/project/MHV_AVR_Tools_20131101.exe). Disable smatch, but **be sure to leave the option to add the tools to the PATH checked**.
3. If you are going to flash Infinity based keyboards you will need to install dfu-util, refer to the instructions by [Input Club](https://github.com/kiibohd/controller/wiki/Loading-DFU-Firmware).
4. Install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). During installation, uncheck the option to install a graphical user interface. **DO NOT change the default installation folder.** The scripts depend on the default location.
5. Clone this repository. [This link will download it as a zip file, which you'll need to extract.](https://github.com/jackhumbert/qmk_firmware/archive/master.zip) Open the extracted folder in Windows Explorer.
6. Double-click on the 1-setup-path-win batch script to run it. You'll need to accept a User Account Control prompt. Press the spacebar to dismiss the success message in the command prompt that pops up.
7. Right-click on the 2-setup-environment-win batch script, select "Run as administrator", and accept the User Account Control prompt. This part may take a couple of minutes, and you'll need to approve a driver installation, but once it finishes, your environment is complete!
8. Future build commands should be run from the MHV AVR Shell, which sets up an environment compatible with colorful build output. The standard Command Prompt will also work, but add `COLOR=false` to the end of all make commands when using it.

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

If you are going to flash Infinity based keyboards you will also need dfu-util

    brew install dfu-util

### Linux

To ensure you are always up to date, you can just run `sudo util/install_dependencies.sh`. That should always install all the dependencies needed.

You can also install things manually, but this documentation might not be always up to date with all requirements.

The current requirements are the following, but not all might be needed depending on what you do. Also note that some systems might not have all the dependencies available as packages, or they might be named differently.

```
build-essential
gcc
unzip
wget
zip
gcc-avr
binutils-avr
avr-libc
dfu-programmer
dfu-util
gcc-arm-none-eabi
binutils-arm-none-eabi
libnewlib-arm-none-eabi
git
```

Install the dependencies with your favorite package manager.

Debian/Ubuntu example:

    sudo apt-get update
    sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi

### Docker

If this is a bit complex for you, Docker might be the turn-key solution you need. After installing [Docker](https://www.docker.com/products/docker), run the following command at the root of the QMK folder to build a keyboard/keymap:

```bash
# You'll run this every time you want to build a keymap
# modify the keymap and keyboard assigment to compile what you want
# defaults are ergodox/default

docker run -e keymap=gwen -e keyboard=ergodox --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware

```

This will compile the targetted keyboard/keymap and leave it in your QMK directory for you to flash.

### Vagrant
If you have any problems building the firmware, you can try using a tool called Vagrant. It will set up a virtual computer with a known configuration that's ready-to-go for firmware building. OLKB does NOT host the files for this virtual computer. Details on how to set up Vagrant are in the [VAGRANT_GUIDE file](doc/VAGRANT_GUIDE.md).

## Verify Your Installation
1. If you haven't already, obtain this repository ([https://github.com/jackhumbert/qmk_firmware](https://github.com/jackhumbert/qmk_firmware)). You can either download it as a zip file and extract it, or clone it using the command line tool git or the Github Desktop application.
2. Open up a terminal or command prompt and navigate to the `qmk_firmware` folder using the `cd` command. The command prompt will typically open to your home directory. If, for example, you cloned the repository to your Documents folder, then you would type `cd Documents/qmk_firmware`. If you extracted the file from a zip, then it may be named `qmk_firmware-master` instead.
3. To confirm that you're in the correct location, you can display the contents of your current folder using the `dir` command on Windows, or the `ls` command on Linux or Mac. You should see several files, including `readme.md` and a `quantum` folder. From here, you need to navigate to the appropriate folder under `keyboards/`. For example, if you're building for a Planck, run `cd keyboards/planck`.
4. Once you're in the correct keyboard-specific folder, run the `make` command. This should output a lot of information about the build process. More information about the `make` command can be found below.

# Customizing your keymap

In every keymap folder, the following files are recommended:

* `config.h` - the options to configure your keymap
* `keymap.c` - all of your keymap code, required
* `Makefile` - the features of QMK that are enabled, required to run `make` in your keymap folder
* `readme.md` - a description of your keymap, how others might use it, and explanations of features

## The `make` command

The `make` command is how you compile the firmware into a .hex file, which can be loaded by a dfu programmer (like dfu-progammer via `make dfu`) or the [Teensy loader](https://www.pjrc.com/teensy/loader.html) (only used with Teensys).

**NOTE:** To abort a make command press `Ctrl-c`

The following instruction refers to these folders.

* The `root` (`/`) folder is the qmk_firmware folder, in which are `doc`, `keyboard`, `quantum`, etc.
* The `keyboard` folder is any keyboard project's folder, like `/keyboards/planck`.
* The `keymap` folder is any keymap's folder, like `/keyboards/planck/keymaps/default`.
* The `subproject` folder is the subproject folder of a keyboard, like `/keyboards/ergodox/ez`

### Simple instructions for building and uploading a keyboard

**Most keyboards have more specific instructions in the keyboard specific readme.md file, so please check that first**

If the `keymap` folder contains a file name `Makefile`

1. Change the directory to the `keymap` folder
2. Run `make <subproject>-<programmer>`

Otherwise, if there's no `Makefile` in the `keymap` folder

1. Enter the `keyboard` folder
2. Run `make <subproject>-<keymap>-<programmer>`

In the above commands, replace:

* `<keymap>` with the name of your keymap
* `<subproject>` with the name of the subproject (revision or sub-model of your keyboard). For example, for Ergodox it can be `ez` or `infinity`, and for Planck `rev3` or `rev4`.
  * If the keyboard doesn't have a subproject, or if you are happy with the default (defined in `rules.mk` file of the `keyboard` folder), you can leave it out. But remember to also remove the dash (`-`) from the command.
* `<programmer>` The programmer to use. Most keyboards use `dfu`, but some use `teensy`. Infinity keyboards use `dfu-util`. Check the readme file in the keyboard folder to find out which programmer to use.
  * If you  don't add `-<programmer` to the command line, the firmware will be still be compiled into a hex file, but the upload will be skipped.

**NOTE:** Some operating systems will refuse to program unless you run the make command as root for example `sudo make dfu`

### More detailed make instruction

The full syntax of the `make` command is the following, but parts of the command can be left out if you run it from other directories than the `root` (as you might already have noticed by reading the simple instructions).

`<keyboard>-<subproject>-<keymap>-<target>`, where:

* `<keyboard>` is the name of the keyboard, for example `planck`
  * Use `allkb` to compile all keyboards
* `<subproject>` is the name of the subproject (revision or sub-model of the keyboard). For example, for Ergodox it can be `ez` or `infinity`, and for Planck `rev3` or `rev4`.
  * If the keyboard doesn't have any subprojects, it can be left out
  * To compile the default subproject, you can leave it out, or specify `defaultsp`
  * Use `allsp` to compile all subprojects
* `<keymap>` is the name of the keymap, for example `algernon`
  * Use `allkm` to compile all keymaps
* `<target>` will be explained in more detail below.

**Note:** When you leave some parts of the command out, you should also remove the dash (`-`).

As mentioned above, there are some shortcuts, when you are in a:

* `keyboard` folder, the command will automatically fill the `<keyboard>` part. So you only need to type `<subproject>-<keymap>-<target>`
* `subproject` folder, it will fill in both `<keyboard>` and `<subproject>`
* `keymap` folder, then `<keyboard>` and `<keymap>` will be filled in. If you need to specify the `<subproject>` use the following syntax `<subproject>-<target>`
  * Note in order to support this shortcut, the keymap needs its own Makefile (see the example [here](/doc/keymap_makefile_example.mk))
* `keymap` folder of a `subproject`, then everything except the `<target>` will be filled in

The `<target>` means the following
* If no target is given, then it's the same as `all` below
* `all` compiles the keyboard and generates a `<keyboard>_<keymap>.hex` file in whichever folder you run `make` from. These files are ignored by git, so don't worry about deleting them when committing/creating pull requests.
* `dfu`, `teensy` or `dfu-util`, compile and upload the firmware to the keyboard. If the compilation fails, then nothing will be uploaded. The programmer to use depends on the keyboard. For most keyboards it's `dfu`, but for Infinity keyboards you should use `dfu-util`, and `teensy` for standard Teensys. To find out which command you should use for your keyboard, check the keyboard specific readme. **Note** that some operating systems needs root access for these commands to work, so in that case you need to run for example `sudo make dfu`.
* `clean`, cleans the build output folders to make sure that everything is built from scratch. Run this before normal compilation if you have some unexplainable problems.

Some other targets are supported but, but not important enough to be documented here. Check the source code of the make files for more information.

You can also add extra options at the end of the make command line, after the target

* `make COLOR=false` - turns off color output
* `make SILENT=true` - turns off output besides errors/warnings
* `make VERBOSE=true` - outputs all of the gcc stuff (not interesting, unless you need to debug)

The make command itself also has some additional options, type `make --help` for more information. The most useful is probably `-jx`, which specifies that you want to compile using more than one CPU, the `x` represents the number of CPUs that you want to use. Setting that can greatly reduce the compile times, especially if you are compiling many keyboards/keymaps. I usually set it to one less than the number of CPUs that I have, so that I have some left for doing other things while it's compiling. Note that not all operating systems and make versions supports that option.

Here are some examples commands

* `make allkb-allsp-allkm` builds everything (all keyboards, all subprojects, all keymaps). Running just `make` from the `root` will also run this.
* `make` from within a `keyboard` directory, is the same as `make keyboard-allsp-allkm`, which compiles all subprojects and keymaps of the keyboard. **NOTE** that this behaviour has changed. Previously it compiled just the default keymap.
* `make ergodox-infinity-algernon-clean` will clean the build output of the Ergodox Infinity keyboard. This example uses the full syntax and can be run from any folder with a `Makefile`
* `make dfu COLOR=false` from within a keymap folder, builds and uploads the keymap, but without color output.

## The `Makefile`

There are 5 different `make` and `Makefile` locations:

* root (`/`)
* keyboard (`/keyboards/<keyboard>/`)
* keymap (`/keyboards/<keyboard>/keymaps/<keymap>/`)
* subproject (`/keyboards/<keyboard>/<subproject>`)
* subproject keymap (`/keyboards/<keyboard>/<subproject>/keymaps/<keymap>`)

The root contains the code used to automatically figure out which keymap or keymaps to compile based on your current directory and commandline arguments. It's considered stable, and shouldn't be modified. The keyboard one will contain the MCU set-up and default settings for your keyboard, and shouldn't be modified unless you are the producer of that keyboard. The keymap Makefile can be modified by users, and is optional. It is included automatically if it exists. You can see an example [here](/doc/keymap_makefile_example.mk) - the last few lines are the most important. The settings you set here will override any defaults set in the keyboard Makefile. **The file is required if you want to run `make` in the keymap folder.**

For keyboards and subprojects, the make files are split in two parts `Makefile` and `rules.mk`. All settings can be found in the `rules.mk` file, while the `Makefile` is just there for support and including the root `Makefile`. Keymaps contain just one `Makefile` for simplicity.

### Makefile options

Set the variables to `no` to disable them, and `yes` to enable them.

`BOOTMAGIC_ENABLE`

This allows you to hold a key and the salt key (space by default) and have access to a various EEPROM settings that persist over power loss. It's advised you keep this disabled, as the settings are often changed by accident, and produce confusing results that makes it difficult to debug. It's one of the more common problems encountered in help sessions.

`MOUSEKEY_ENABLE`

This gives you control over cursor movements and clicks via keycodes/custom functions.

`EXTRAKEY_ENABLE`

This allows you to use the system and audio control key codes.

`CONSOLE_ENABLE`

This allows you to print messages that can be read using [`hid_listen`](https://www.pjrc.com/teensy/hid_listen.html). Add this to your `Makefile`, and set it to `yes`. Then put `println`, `printf`, etc. in your keymap or anywhere in the `qmk` source. Finally, open `hid_listen` and enjoy looking at your printed messages.

`COMMAND_ENABLE`

TODO

`SLEEP_LED_ENABLE`

Enables your LED to breath while your computer is sleeping. Timer1 is being used here. This feature is largely unused and untested, and needs updating/abstracting.

`NKRO_ENABLE`

This allows for n-key rollover (default is 6) to be enabled. It is off by default, but can be forced by adding `#define FORCE_NKRO` to your config.h.

`BACKLIGHT_ENABLE`

This enables your backlight on Timer1 and ports B5, B6, or B7 (for now). You can specify your port by putting this in your `config.h`:

    #define BACKLIGHT_PIN B7

`MIDI_ENABLE`

This enables MIDI sending and receiving with your keyboard. To enter MIDI send mode, you can use the keycode `MI_ON`, and `MI_OFF` to turn it off. This is a largely untested feature, but more information can be found in the `quantum/quantum.c` file.

`UNICODE_ENABLE`

This allows you to send unicode symbols via `UC(<unicode>)` in your keymap. Only codes up to 0x7FFF are currently supported.

`BLUETOOTH_ENABLE`

This allows you to interface with a Bluefruit EZ-key to send keycodes wirelessly. It uses the D2 and D3 pins.

`AUDIO_ENABLE`

This allows you output audio on the C6 pin (needs abstracting). See the [audio section](#driving-a-speaker---audio-support) for more information.

### Customizing Makefile options on a per-keymap basis

If your keymap directory has a file called `Makefile` (note the filename), any Makefile options you set in that file will take precedence over other Makefile options for your particular keyboard.

So let's say your keyboard's makefile has `BACKLIGHT_ENABLE = yes` (or maybe doesn't even list the `BACKLIGHT_ENABLE` option, which would cause it to be off). You want your particular keymap to not have the debug console, so you make a file called `Makefile` and specify `BACKLIGHT_ENABLE = no`.

You can use the `doc/keymap_makefile_example.md` as a template/starting point.

## The `config.h` file

There are 2 `config.h` locations:

* keyboard (`/keyboards/<keyboard>/`)
* keymap (`/keyboards/<keyboard>/keymaps/<keymap>/`)

The keyboard `config.h` is included only if the keymap one doesn't exist. The format to use for your custom one [is here](/doc/keymap_config_h_example.h). If you want to override a setting from the parent `config.h` file, you need to do this:

```c
#undef MY_SETTING
#define MY_SETTING 4
```

For a value of `4` for this imaginary setting. So we `undef` it first, then `define` it.

You can then override any settings, rather than having to copy and paste the whole thing.

# Going beyond the keycodes

Aside from the [basic keycodes](doc/keycode.txt), your keymap can include shortcuts to common operations.

## Quick aliases to common actions

Your keymap can include shortcuts to common operations (called "function actions" in tmk).

These functions work the same way that their `ACTION_*` functions do - they're just quick aliases. To dig into all of the tmk `ACTION_*` functions, please see the [TMK documentation](https://github.com/jackhumbert/qmk_firmware/blob/master/doc/keymap.md#2-action).

Instead of using `FNx` when defining `ACTION_*` functions, you can use `F(x)` - the benefit here is being able to use more than 32 function actions (up to 4096), if you happen to need them.

### Switching and toggling layers

`MO(layer)` - momentary switch to *layer*. As soon as you let go of the key, the layer is deactivated and you pop back out to the previous layer. When you apply this to a key, that same key must be set as `KC_TRNS` on the destination layer. Otherwise, you won't make it back to the original layer when you release the key (and you'll get a keycode sent). You can only switch to layers *above* your current layer. If you're on layer 0 and you use `MO(1)`, that will switch to layer 1 just fine. But if you include `MO(3)` on layer 5, that won't do anything for you -- because layer 3 is lower than layer 5 on the stack.

`OSL(layer)` - momentary switch to *layer*, as a one-shot operation. So if you have a key that's defined as `OSL(1)`, and you tap that key, then only the very next keystroke would come from layer 1. You would drop back to layer zero immediately after that one keystroke. That's handy if you have a layer full of custom shortcuts -- for example, a dedicated key for closing a window. So you tap your one-shot layer mod, then tap that magic 'close window' key, and keep typing like a boss. Layer 1 would remain active as long as you hold that key down, too (so you can use it like a momentary toggle-layer key with extra powers).

`LT(layer, kc)` - momentary switch to *layer* when held, and *kc* when tapped. Like `MO()`, this only works upwards in the layer stack (`layer` must be higher than the current layer).

`TG(layer)` - toggles a layer on or off. As with `MO()`, you should set this key as `KC_TRNS` in the destination layer so that tapping it again actually toggles back to the original layer. Only works upwards in the layer stack.


### Fun with modifier keys

* `LSFT(kc)` - applies left Shift to *kc* (keycode) - `S(kc)` is an alias
* `RSFT(kc)` - applies right Shift to *kc*
* `LCTL(kc)` - applies left Control to *kc*
* `RCTL(kc)` - applies right Control to *kc*
* `LALT(kc)` - applies left Alt to *kc*
* `RALT(kc)` - applies right Alt to *kc*
* `LGUI(kc)` - applies left GUI (command/win) to *kc*
* `RGUI(kc)` - applies right GUI (command/win) to *kc*
* `HYPR(kc)` - applies Hyper (all modifiers) to *kc*
* `MEH(kc)`  - applies Meh (all modifiers except Win/Cmd) to *kc*
* `LCAG(kc)` - applies CtrlAltGui to *kc*

You can also chain these, like this:

    LALT(LCTL(KC_DEL)) -- this makes a key that sends Alt, Control, and Delete in a single keypress.

The following shortcuts automatically add `LSFT()` to keycodes to get commonly used symbols. Their long names are also available and documented in `/quantum/keymap_common.h`.

    KC_TILD  ~
    KC_EXLM  !
    KC_AT    @
    KC_HASH  #
    KC_DLR   $
    KC_PERC  %
    KC_CIRC  ^
    KC_AMPR  &
    KC_ASTR  *
    KC_LPRN  (
    KC_RPRN  )
    KC_UNDS  _
    KC_PLUS  +
    KC_DQUO  "
    KC_LCBR  {
    KC_RCBR  }
    KC_LABK  <
    KC_RABK  >
    KC_PIPE  |
    KC_COLN  :

`OSM(mod)` - this is a "one shot" modifier. So let's say you have your left Shift key defined as `OSM(MOD_LSFT)`. Tap it, let go, and Shift is "on" -- but only for the next character you'll type. So to write "The", you don't need to hold down Shift -- you tap it, tap t, and move on with life. And if you hold down the left Shift key, it just works as a left Shift key, as you would expect (so you could type THE). There's also a magical, secret way to "lock" a modifier by tapping it multiple times. If you want to learn more about that, open an issue. :)

`MT(mod, kc)` - is *mod* (modifier key - MOD_LCTL, MOD_LSFT) when held, and *kc* when tapped. In other words, you can have a key that sends Esc (or the letter O or whatever) when you tap it, but works as a Control key or a Shift key when you hold it down.

These are the values you can use for the `mod` in `MT()` and `OSM()` (right-hand modifiers are not available for `MT()`):

  * MOD_LCTL
  * MOD_LSFT
  * MOD_LALT
  * MOD_LGUI
  * MOD_HYPR
  * MOD_MEH

These can also be combined like `MOD_LCTL | MOD_LSFT` e.g. `MT(MOD_LCTL | MOD_LSFT, KC_ESC)` which would activate Control and Shift when held, and send Escape when tapped.

We've added shortcuts to make common modifier/tap (mod-tap) mappings more compact:

  * `CTL_T(kc)` - is LCTL when held and *kc* when tapped
  * `SFT_T(kc)` - is LSFT when held and *kc* when tapped
  * `ALT_T(kc)` - is LALT when held and *kc* when tapped
  * `GUI_T(kc)` - is LGUI when held and *kc* when tapped
  * `ALL_T(kc)` - is Hyper (all mods) when held and *kc* when tapped. To read more about what you can do with a Hyper key, see [this blog post by Brett Terpstra](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)
  * `LCAG_T(kc)` - is CtrlAltGui when held and *kc* when tapped
  * `MEH_T(kc)` - is like Hyper, but not as cool -- does not include the Cmd/Win key, so just sends Alt+Ctrl+Shift.

## Space Cadet Shift: The future, built in

Steve Losh [described](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) the Space Cadet Shift quite well. Essentially, you hit the left Shift on its own, and you get an opening parenthesis; hit the right Shift on its own, and you get the closing one. When hit with other keys, the Shift key keeps working as it always does. Yes, it's as cool as it sounds.

To use it, use `KC_LSPO` (Left Shift, Parens Open) for your left Shift on your keymap, and `KC_RSPC` (Right Shift, Parens Close) for your right Shift.

It's defaulted to work on US keyboards, but if your layout uses different keys for parenthesis, you can define those in your `config.h` like this:

    #define LSPO_KEY KC_9
    #define RSPC_KEY KC_0

You can also choose between different rollover behaviors of the shift keys by defining:

    #define DISABLE_SPACE_CADET_ROLLOVER

in your `config.h`. Disabling rollover allows you to use the opposite shift key to cancel the space cadet state in the event of an erroneous press instead of emitting a pair of parentheses when the keys are released.

The only other thing you're going to want to do is create a `Makefile` in your keymap directory and set the following:

```
COMMAND_ENABLE   = no  # Commands for debug and configuration
```

This is just to keep the keyboard from going into command mode when you hold both Shift keys at the same time.

## The Leader key: A new kind of modifier

If you've ever used Vim, you know what a Leader key is. If not, you're about to discover a wonderful concept. :) Instead of hitting Alt+Shift+W for example (holding down three keys at the same time), what if you could hit a _sequence_ of keys instead? So you'd hit our special modifier (the Leader key), followed by W and then C (just a rapid succession of keys), and something would happen.

That's what `KC_LEAD` does. Here's an example:

1. Pick a key on your keyboard you want to use as the Leader key. Assign it the keycode `KC_LEAD`. This key would be dedicated just for this -- it's a single action key, can't be used for anything else.
2. Include the line `#define LEADER_TIMEOUT 300` somewhere in your keymap.c file, probably near the top. The 300 there is 300ms -- that's how long you have for the sequence of keys following the leader. You can tweak this value for comfort, of course.
3. Within your `matrix_scan_user` function, do something like this:

```
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      register_code(KC_S);
      unregister_code(KC_S);
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_H);
      unregister_code(KC_H);
    }
    SEQ_THREE_KEYS(KC_A, KC_S, KC_D) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
```

As you can see, you have three function. you can use - `SEQ_ONE_KEY` for single-key sequences (Leader followed by just one key), and `SEQ_TWO_KEYS` and `SEQ_THREE_KEYS` for longer sequences. Each of these accepts one or more keycodes as arguments. This is an important point: You can use keycodes from **any layer on your keyboard**. That layer would need to be active for the leader macro to fire, obviously.

## Tap Dance: A single key can do 3, 5, or 100 different things

Hit the semicolon key once, send a semicolon. Hit it twice, rapidly -- send a colon. Hit it three times, and your keyboard's LEDs do a wild dance. That's just one example of what Tap Dance can do. It's one of the nicest community-contributed features in the firmware, conceived and created by [algernon](https://github.com/algernon) in [#451](https://github.com/jackhumbert/qmk_firmware/pull/451). Here's how algernon describes the feature:

With this feature one can specify keys that behave differently, based on the amount of times they have been tapped, and when interrupted, they get handled before the interrupter.

To make it clear how this is different from `ACTION_FUNCTION_TAP`, lets explore a certain setup! We want one key to send `Space` on single tap, but `Enter` on double-tap.

With `ACTION_FUNCTION_TAP`, it is quite a rain-dance to set this up, and has the problem that when the sequence is interrupted, the interrupting key will be send first. Thus, `SPC a` will result in `a SPC` being sent, if they are typed within `TAPPING_TERM`. With the tap dance feature, that'll come out as `SPC a`, correctly.

The implementation hooks into two parts of the system, to achieve this: into `process_record_quantum()`, and the matrix scan. We need the latter to be able to time out a tap sequence even when a key is not being pressed, so `SPC` alone will time out and register after `TAPPING_TERM` time.

But lets start with how to use it, first!

First, you will need `TAP_DANCE_ENABLE=yes` in your `Makefile`, because the feature is disabled by default. This adds a little less than 1k to the firmware size. Next, you will want to define some tap-dance keys, which is easiest to do with the `TD()` macro, that - similar to `F()`, takes a number, which will later be used as an index into the `tap_dance_actions` array.

This array specifies what actions shall be taken when a tap-dance key is in action. Currently, there are three possible options:

* `ACTION_TAP_DANCE_DOUBLE(kc1, kc2)`: Sends the `kc1` keycode when tapped once, `kc2` otherwise. When the key is held, the appropriate keycode is registered: `kc1` when pressed and held, `kc2` when tapped once, then pressed and held.
* `ACTION_TAP_DANCE_FN(fn)`: Calls the specified function - defined in the user keymap - with the final tap count of the tap dance action.
* `ACTION_TAP_DANCE_FN_ADVANCED(on_each_tap_fn, on_dance_finished_fn, on_reset_fn)`: Calls the first specified function - defined in the user keymap - on every tap, the second function on when the dance action finishes (like the previous option), and the last function when the tap dance action resets.

The first option is enough for a lot of cases, that just want dual roles. For example, `ACTION_TAP_DANCE(KC_SPC, KC_ENT)` will result in `Space` being sent on single-tap, `Enter` otherwise.

And that's the bulk of it!

And now, on to the explanation of how it works!

The main entry point is `process_tap_dance()`, called from `process_record_quantum()`, which is run for every keypress, and our handler gets to run early. This function checks whether the key pressed is a tap-dance key. If it is not, and a tap-dance was in action, we handle that first, and enqueue the newly pressed key. If it is a tap-dance key, then we check if it is the same as the already active one (if there's one active, that is). If it is not, we fire off the old one first, then register the new one. If it was the same, we increment the counter and the timer.

This means that you have `TAPPING_TERM` time to tap the key again, you do not have to input all the taps within that timeframe. This allows for longer tap counts, with minimal impact on responsiveness.

Our next stop is `matrix_scan_tap_dance()`. This handles the timeout of tap-dance keys.

For the sake of flexibility, tap-dance actions can be either a pair of keycodes, or a user function. The latter allows one to handle higher tap counts, or do extra things, like blink the LEDs, fiddle with the backlighting, and so on. This is accomplished by using an union, and some clever macros.

### Examples

Here's a simple example for a single definition:

1. In your `makefile`, add `TAP_DANCE_ENABLE = yes`
2. In your `config.h` (which you can copy from `qmk_firmware/keyboards/planck/config.h` to your keymap directory), add `#define TAPPING_TERM 200`
3. In your `keymap.c` file, define the variables and definitions, then add to your keymap:

```c
//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
};

//In Layer declaration, add tap dance item in place of a key code
TD(TD_ESC_CAPS)
```

Here's a more complex example involving custom actions:

```c
enum {
 CT_SE = 0,
 CT_CLN,
 CT_EGG,
 CT_FLSH,
};

/* Have the above three on the keymap, TD(CT_SE), etc... */

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  } else {
    register_code (KC_SCLN);
  }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_SCLN);
  }
}

void dance_egg (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 100) {
    SEND_STRING ("Safety dance!");
    reset_tap_dance (state);
  }
}

// on each tap, light up one led, from right to left
// on the forth tap, turn them off from right to left
void dance_flsh_each(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    ergodox_right_led_3_on();
    break;
  case 2:
    ergodox_right_led_2_on();
    break;
  case 3:
    ergodox_right_led_1_on();
    break;
  case 4:
    ergodox_right_led_3_off();
    _delay_ms(50);
    ergodox_right_led_2_off();
    _delay_ms(50);
    ergodox_right_led_1_off();
  }
}

// on the fourth tap, set the keyboard on flash state
void dance_flsh_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 4) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

// if the flash state didnt happen, then turn off leds, left to right
void dance_flsh_reset(qk_tap_dance_state_t *state, void *user_data) {
  ergodox_right_led_1_off();
  _delay_ms(50);
  ergodox_right_led_2_off();
  _delay_ms(50);
  ergodox_right_led_3_off();
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [CT_SE]  = ACTION_TAP_DANCE_DOUBLE (KC_SPC, KC_ENT)
 ,[CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
 ,[CT_EGG] = ACTION_TAP_DANCE_FN (dance_egg)
 ,[CT_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED (dance_flsh_each, dance_flsh_finished, dance_flsh_reset)
};
```

## Temporarily setting the default layer

`DF(layer)` - sets default layer to *layer*. The default layer is the one at the "bottom" of the layer stack - the ultimate fallback layer. This currently does not persist over power loss. When you plug the keyboard back in, layer 0 will always be the default. It is theoretically possible to work around that, but that's not what `DF` does.

## Prevent stuck modifiers

Consider the following scenario:

1. Layer 0 has a key defined as Shift.
2. The same key is defined on layer 1 as the letter A.
3. User presses Shift.
4. User switches to layer 1 for whatever reason.
5. User releases Shift, or rather the letter A.
6. User switches back to layer 0.

Shift was actually never released and is still considered pressed.

If such situation bothers you add this to your `config.h`:

    #define PREVENT_STUCK_MODIFIERS

This option uses 5 bytes of memory per every 8 keys on the keyboard
rounded up (5 bits per key). For example on Planck (48 keys) it uses
(48/8)\*5 = 30 bytes.

## Macro shortcuts: Send a whole string when pressing just one key

Instead of using the `ACTION_MACRO` function, you can simply use `M(n)` to access macro *n* - *n* will get passed into the `action_get_macro` as the `id`, and you can use a switch statement to trigger it. This gets called on the keydown and keyup, so you'll need to use an if statement testing `record->event.pressed` (see keymap_default.c).

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END  ); // this sends the string 'hello' when the macro executes
      }
      break;
  }
  return MACRO_NONE;
};
```
A macro can include the following commands:

* I() change interval of stroke in milliseconds.
* D() press key.
* U() release key.
* T() type key(press and release).
* W() wait (milliseconds).
* END end mark.

So above you can see the stroke interval changed to 255ms between each keystroke, then a bunch of keys being typed, waits a while, then the macro ends.

Note: Using macros to have your keyboard send passwords for you is possible, but a bad idea.

### Advanced macro functions

To get more control over the keys/actions your keyboard takes, the following functions are available to you in the `action_get_macro` function block:

* `record->event.pressed`

This is a boolean value that can be tested to see if the switch is being pressed or released. An example of this is

```c
if (record->event.pressed) {
  // on keydown
} else {
  // on keyup
}
```

* `register_code(<kc>);`

This sends the `<kc>` keydown event to the computer. Some examples would be `KC_ESC`, `KC_C`, `KC_4`, and even modifiers such as `KC_LSFT` and `KC_LGUI`.

* `unregister_code(<kc>);`

Parallel to `register_code` function, this sends the `<kc>` keyup event to the computer. If you don't use this, the key will be held down until it's sent.

* `layer_on(<n>);`

This will turn on the layer `<n>` - the higher layer number will always take priority. Make sure you have `KC_TRNS` for the key you're pressing on the layer you're switching to, or you'll get stick there unless you have another plan.

* `layer_off(<n>);`

This will turn off the layer `<n>`.

* `clear_keyboard();`

This will clear all mods and keys currently pressed.

* `clear_mods();`

This will clear all mods currently pressed.

* `clear_keyboard_but_mods();`

This will clear all keys besides the mods currently pressed.

* `update_tri_layer(layer_1, layer_2, layer_3);`

If the user attempts to activate layer 1 AND layer 2 at the same time (for example, by hitting their respective layer keys), layer 3 will be activated. Layers 1 and 2 will _also_ be activated, for the purposes of fallbacks (so a given key will fall back from 3 to 2, to 1 -- and only then to 0).

#### Naming your macros

If you have a bunch of macros you want to refer to from your keymap, while keeping the keymap easily readable, you can just name them like so:

```
#define AUD_OFF M(6)
#define AUD_ON M(7)
#define MUS_OFF M(8)
#define MUS_ON M(9)
#define VC_IN M(10)
#define VC_DE M(11)
#define PLOVER M(12)
#define EXT_PLV M(13)
```

As was done on the [Planck default keymap](/keyboards/planck/keymaps/default/keymap.c#L33-L40)

#### Timer functionality

It's possible to start timers and read values for time-specific events - here's an example:

```c
static uint16_t key_timer;
key_timer = timer_read();
if (timer_elapsed(key_timer) < 100) {
  // do something if less than 100ms have passed
} else {
  // do something if 100ms or more have passed
}
```

It's best to declare the `static uint16_t key_timer;` outside of the macro block (top of file, etc).

#### Example: Single-key copy/paste (hold to copy, tap to paste)

With QMK, it's easy to make one key do two things, as long as one of those things is being a modifier. :) So if you want a key to act as Ctrl when held and send the letter R when tapped, that's easy: `CTL_T(KC_R)`. But what do you do when you want that key to send Ctrl-V (paste) when tapped, and Ctrl-C (copy) when held?

Here's what you do:


```
static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0: {
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO( D(LCTL), T(C), U(LCTL), END  );
                }
                else {
                    return MACRO( D(LCTL), T(V), U(LCTL), END  );
                }
            }
            break;
        }
      }
    return MACRO_NONE;
};
```

And then, to assign this macro to a key on your keyboard layout, you just use `M(0)` on the key you want to press for copy/paste.

## Dynamic macros: record and replay macros in runtime

In addition to the static macros described above, you may enable the dynamic macros which you may record while writing. They are forgotten as soon as the keyboard is unplugged. Only two such macros may be stored at the same time, with the total length of 128 keypresses.

To enable them, first add a new element to the `planck_keycodes` enum -- `DYNAMIC_MACRO_RANGE`:

    enum planck_keycodes {
      QWERTY = SAFE_RANGE,
      COLEMAK,
      DVORAK,
      PLOVER,
      LOWER,
      RAISE,
      BACKLIT,
      EXT_PLV,
      DYNAMIC_MACRO_RANGE,
    };

Afterwards create a new layer called `_DYN`:

    #define _DYN 6    /* almost any other free number should be ok */

Below these two modifications include the `dynamic_macro.h` header:

    #include "dynamic_macro.h"`

Then define the `_DYN` layer with the following keys: `DYN_REC_START1`, `DYN_MACRO_PLAY1`,`DYN_REC_START2` and `DYN_MACRO_PLAY2`. It may also contain other keys, it doesn't matter apart from the fact that you won't be able to record these keys in the dynamic macros.

    [_DYN]= {
        {_______,  DYN_REC_START1, DYN_MACRO_PLAY1, _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {_______,  DYN_REC_START2, DYN_MACRO_PLAY2, _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {_______,  _______,        _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______},
        {_______,  _______,        _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______}
    },

Add the following code to the very beginning of your `process_record_user()` function:

    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

To start recording the macro, press either `DYN_REC_START1` or `DYN_REC_START2`. To finish the recording, press the `_DYN` layer button. The handler awaits specifically for the `MO(_DYN)` keycode as the "stop signal" so please don't use any fancy ways to access this layer, use the regular `MO()` modifier. To replay the macro, press either `DYN_MACRO_PLAY1` or `DYN_MACRO_PLAY2`.

If the LED-s start blinking during the recording with each keypress, it means there is no more space for the macro in the macro buffer. To fit the macro in, either make the other macro shorter (they share the same buffer) or increase the buffer size by setting the `DYNAMIC_MACRO_SIZE` preprocessor macro (default value: 256; please read the comments for it in the header).

For the details about the internals of the dynamic macros, please read the comments in the `dynamic_macro.h` header.

## Additional keycode aliases for software-implemented layouts (Colemak, Dvorak, etc)

Everything is assuming you're in Qwerty (in software) by default, but there is built-in support for using a Colemak or Dvorak layout by including this at the top of your keymap:

   #include <keymap_colemak.h>

If you use Dvorak, use `keymap_dvorak.h` instead of `keymap_colemak.h` for this line. After including this line, you will get access to:

 * `CM_*` for all of the Colemak-equivalent characters
 * `DV_*` for all of the Dvorak-equivalent characters

These implementations assume you're using Colemak or Dvorak on your OS, not on your keyboard - this is referred to as a software-implemented layout. If your computer is in Qwerty and your keymap is in Colemak or Dvorak, this is referred to as a firmware-implemented layout, and you won't need these features.

To give an example, if you're using software-implemented Colemak, and want to get an `F`, you would use `CM_F` - `KC_F` under these same circumstances would result in `T`.

## Additional language support

In `quantum/keymap_extras/`, you'll see various language files - these work the same way as the alternative layout ones do. Most are defined by their two letter country/language code followed by an underscore and a 4-letter abbreviation of its name. `FR_UGRV` which will result in a `ù` when using a software-implemented AZERTY layout. It's currently difficult to send such characters in just the firmware (but it's being worked on - see Unicode support).

## Unicode support

You can currently send 4 hex digits with your OS-specific modifier key (RALT for OSX with the "Unicode Hex Input" layout) - this is currently limited to supporting one OS at a time, and requires a recompile for switching. 8 digit hex codes are being worked on. The keycode function is `UC(n)`, where *n* is a 4 digit hexidecimal. Enable from the Makefile.

## Backlight Breathing

In order to enable backlight breathing, the following line must be added to your config.h file.

    #define BACKLIGHT_BREATHING

The following function calls are used to control the breathing effect.

* ```breathing_enable()``` - Enable the free-running breathing effect.
* ```breathing_disable()``` - Disable the free-running breathing effect immediately.
* ```breathing_self_disable()``` - Disable the free-running breathing effect after the current effect ends.
* ```breathing_toggle()``` - Toggle the free-running breathing effect.
* ```breathing_defaults()``` - Reset the speed and brightness settings of the breathing effect.

The following function calls are used to control the maximum brightness of the breathing effect.

* ```breathing_intensity_set(value)``` - Set the brightness of the breathing effect when it is at its max value.
* ```breathing_intensity_default()``` - Reset the brightness of the breathing effect to the default value based on the current backlight intensity.

The following function calls are used to control the cycling speed of the breathing effect.

* ```breathing_speed_set(value)``` - Set the speed of the breathing effect - how fast it cycles.
* ```breathing_speed_inc(value)``` - Increase the speed of the breathing effect by a fixed value.
* ```breathing_speed_dec(value)``` - Decrease the speed of the breathing effect by a fixed value.
* ```breathing_speed_default()``` - Reset the speed of the breathing effect to the default value.

The following example shows how to enable the backlight breathing effect when the FUNCTION layer macro button is pressed:

    case MACRO_FUNCTION:
        if (record->event.pressed)
        {
            breathing_speed_set(3);
            breathing_enable();
            layer_on(LAYER_FUNCTION);
        }
        else
        {
            breathing_speed_set(1);
            breathing_self_disable();
            layer_off(LAYER_FUNCTION);
        }
        break;

The following example shows how to pulse the backlight on-off-on when the RAISED layer macro button is pressed:

    case MACRO_RAISED:
      if (record->event.pressed)
      {
        layer_on(LAYER_RAISED);
        breathing_speed_set(2);
        breathing_pulse();
        update_tri_layer(LAYER_LOWER, LAYER_RAISED, LAYER_ADJUST);
      }
      else
      {
        layer_off(LAYER_RAISED);
        update_tri_layer(LAYER_LOWER, LAYER_RAISED, LAYER_ADJUST);
      }
      break;

## Other firmware shortcut keycodes

* `RESET` - puts the MCU in DFU mode for flashing new firmware (with `make dfu`)
* `DEBUG` - the firmware into debug mode - you'll need hid_listen to see things
* `BL_ON` - turns the backlight on
* `BL_OFF` - turns the backlight off
* `BL_<n>` - sets the backlight to level *n*
* `BL_INC` - increments the backlight level by one
* `BL_DEC` - decrements the backlight level by one
* `BL_TOGG` - toggles the backlight
* `BL_STEP` - steps through the backlight levels

Enable the backlight from the Makefile.

# Custom Quantum functions

All of these functions are available in the `*_kb()` or `*_user()` variety. `kb` ones should only be used in the `<keyboard>/<keyboard>.c` file, and `user` ones should only be used in the `keymap.c`. The keyboard ones call the user ones - it's necessary to keep these calls to allow the keymap functions to work correctly.

## `void matrix_init_*(void)`

This function gets called when the matrix is initiated, and can contain start-up code for your keyboard/keymap.

## `void matrix_scan_*(void)`

This function gets called at every matrix scan, which is basically as often as the MCU can handle. Be careful what you put here, as it will get run a lot.

## `bool process_record_*(uint16_t keycode, keyrecord_t *record)`

This function gets called on every keypress/release, and is where you can define custom functionality. The return value is whether or not QMK should continue processing the keycode - returning `false` stops the execution.

The `keycode` variable is whatever is defined in your keymap, eg `MO(1)`, `KC_L`, etc. and can be switch-cased to execute code whenever a particular code is pressed.

The `record` variable contains infomation about the actual press:

```
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

The conditional `if (record->event.pressed)` can tell if the key is being pressed or released, and you can execute code based on that.

## `void led_set_*(uint8_t usb_led)`

This gets called whenever there is a state change on your host LEDs (eg caps lock, scroll lock, etc). The LEDs are defined as:

```
#define USB_LED_NUM_LOCK                0
#define USB_LED_CAPS_LOCK               1
#define USB_LED_SCROLL_LOCK             2
#define USB_LED_COMPOSE                 3
#define USB_LED_KANA                    4
```

and can be tested against the `usb_led` with a conditional like `if (usb_led & (1<<USB_LED_CAPS_LOCK))` - if this is true, you can turn your LED one, otherwise turn it off.

# Modding your keyboard

## Audio output from a speaker

Your keyboard can make sounds! If you've got a Planck, Preonic, or basically any keyboard that allows access to the C6 port, you can hook up a simple speaker and make it beep. You can use those beeps to indicate layer transitions, modifiers, special keys, or just to play some funky 8bit tunes.

The audio code lives in [quantum/audio/audio.h](/quantum/audio/audio.h) and in the other files in the audio directory. It's enabled by default on the Planck [stock keymap](/keyboards/planck/keymaps/default/keymap.c). Here are the important bits:

```
#include "audio.h"
```

Then, lower down the file:

```
float tone_startup[][2] = {
    ED_NOTE(_E7 ),
    E__NOTE(_CS7),
    E__NOTE(_E6 ),
    E__NOTE(_A6 ),
    M__NOTE(_CS7, 20)
};
```

This is how you write a song. Each of these lines is a note, so we have a little ditty composed of five notes here.

Then, we have this chunk:

```
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);

float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);
float goodbye[][2] = SONG(GOODBYE_SOUND);
```

Wherein we bind predefined songs (from [quantum/audio/song_list.h](/quantum/audio/song_list.h)) into named variables. This is one optimization that helps save on memory: These songs only take up memory when you reference them in your keymap, because they're essentially all preprocessor directives.

So now you have something called `tone_plover` for example. How do you make it play the Plover tune, then? If you look further down the keymap, you'll see this:

```
PLAY_NOTE_ARRAY(tone_plover, false, 0); // Signature is: Song name, repeat, rest style
```

This is inside one of the macros. So when that macro executes, your keyboard plays that particular chime.

"Rest style" in the method signature above (the last parameter) specifies if there's a rest (a moment of silence) between the notes.


## Recording And Playing back Music
* ```Music On``` - Turn music mode on. The default mapping is ```Lower+Upper+C```
* ```LCTL``` - start a recording
* play some tones
* ```LALT``` - stop recording, stop playing
* ```LGUI``` - play recording
* ```LALT``` - stop playing
* ```Music Off``` - Turn music mode off. The default mapping is ```Lower+Upper+V```


## MIDI functionalty

This is still a WIP, but check out `quantum/keymap_midi.c` to see what's happening. Enable from the Makefile.

## Bluetooth functionality

This requires [some hardware changes](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts), but can be enabled via the Makefile. The firmware will still output characters via USB, so be aware of this when charging via a computer. It would make sense to have a switch on the Bluefruit to turn it off at will.

## International Characters on Windows

[AutoHotkey](https://autohotkey.com) allows Windows users to create custom hotkeys among others.

The method does not require Unicode support in the keyboard itself but depends instead of AutoHotkey running in the background.

First you need to select a modifier combination that is not in use by any of your programs.
CtrlAltWin is not used very widely and should therefore be perfect for this.
There is a macro defined for a mod-tab combo `LCAG_T`.
Add this mod-tab combo to a key on your keyboard, e.g.: `LCAG_T(KC_TAB)`.
This makes the key behave like a tab key if pressed and released immediately but changes it to the modifier if used with another key.

In the default script of AutoHotkey you can define custom hotkeys.

    <^<!<#a::Send, ä
    <^<!<#<+a::Send, Ä

The hotkeys above are for the combination CtrlAltGui and CtrlAltGuiShift plus the letter a.
AutoHotkey inserts the Text right of `Send, ` when this combination is pressed.

## RGB Under Glow Mod

![Planck with RGB Underglow](https://raw.githubusercontent.com/jackhumbert/qmk_firmware/master/keyboards/planck/keymaps/yang/planck-with-rgb-underglow.jpg)

Here is a quick demo on Youtube (with NPKC KC60) (https://www.youtube.com/watch?v=VKrpPAHlisY).

For this mod, you need an unused pin wiring to DI of WS2812 strip. After wiring the VCC, GND, and DI, you can enable the underglow in your Makefile.

    RGBLIGHT_ENABLE = yes

In order to use the underglow timer functions, you need to have `#define RGBLIGHT_TIMER` in your `config.h`, and have audio disabled (`AUDIO_ENABLE = no` in your Makefile).

Please add the following options into your config.h, and set them up according your hardware configuration. These settings are for the `F4` pin by default:

    #define RGB_DI_PIN F4     // The pin your RGB strip is wired to
    #define RGBLIGHT_TIMER    // Require for fancier stuff (not compatible with audio)
    #define RGBLED_NUM 14     // Number of LEDs
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

You'll need to edit `RGB_DI_PIN` to the pin you have your `DI` on your RGB strip wired to.

The firmware supports 5 different light effects, and the color (hue, saturation, brightness) can be customized in most effects. To control the underglow, you need to modify your keymap file to assign those functions to some keys/key combinations. For details, please check this keymap. `keyboards/planck/keymaps/yang/keymap.c`

### WS2812 Wiring

![WS2812 Wiring](https://raw.githubusercontent.com/jackhumbert/qmk_firmware/master/keyboards/planck/keymaps/yang/WS2812-wiring.jpg)

Please note the USB port can only supply a limited amount of power to the keyboard (500mA by standard, however, modern computer and most usb hubs can provide 700+mA.). According to the data of NeoPixel from Adafruit, 30 WS2812 LEDs require a 5V 1A power supply, LEDs used in this mod should not more than 20.

## Safety Considerations

You probably don't want to "brick" your keyboard, making it impossible
to rewrite firmware onto it.  Here are some of the parameters to show
what things are (and likely aren't) too risky.

- If a keyboard map does not include RESET, then, to get into DFU
  mode, you will need to press the reset button on the PCB, which
  requires unscrewing some bits.
- Messing with tmk_core / common files might make the keyboard
  inoperable
- Too large a .hex file is trouble; `make dfu` will erase the block,
  test the size (oops, wrong order!), which errors out, failing to
  flash the keyboard
- DFU tools do /not/ allow you to write into the bootloader (unless
  you throw in extra fruitsalad of options), so there is little risk
  there.
- EEPROM has around a 100000 write cycle.  You shouldn't rewrite the
  firmware repeatedly and continually; that'll burn the EEPROM
  eventually.

# Porting your keyboard to QMK

If your keyboard is running an Atmega chip (atmega32u4 and others), it's pretty easy to get things setup for compiling your own firmware to flash onto your board. There is a `/util/new_project.sh <keyboard>` script to help get you started - you can simply pass your keyboard's name into the script, and all of the necessary files will be created. The components of each are described below.

## `/keyboards/<keyboard>/config.h`

The `USB Device descriptor parameter` block contains parameters are used to uniquely identify your keyboard, but they don't really matter to the machine.

Your `MATRIX_ROWS` and `MATRIX_COLS` are the numbers of rows and cols in your keyboard matrix - this may be different than the number of actual rows and columns on your keyboard. There are some tricks you can pull to increase the number of keys in a given matrix, but most keyboards are pretty straight-forward.

The `MATRIX_ROW_PINS` and `MATRIX_COL_PINS` are the pins your MCU uses on each row/column. Your schematic (if you have one) will have this information on it, and the values will vary depending on your setup. This is one of the most important things to double-check in getting your keyboard setup correctly.

For the `DIODE_DIRECTION`, most hand-wiring guides will instruct you to wire the diodes in the `COL2ROW` position, but it's possible that they are in the other - people coming from EasyAVR often use `ROW2COL`. Nothing will function if this is incorrect.

`BACKLIGHT_PIN` is the pin that your PWM-controlled backlight (if one exists) is hooked-up to. Currently only B5, B6, and B7 are supported.

`BACKLIGHT_BREATHING` is a fancier backlight feature that adds breathing/pulsing/fading effects to the backlight. It uses the same timer as the normal backlight. These breathing effects must be called by code in your keymap.

`BACKLIGHT_LEVELS` is how many levels exist for your backlight - max is 15, and they are computed automatically from this number.

## `/keyboards/<keyboard>/Makefile`

The values at the top likely won't need to be changed, since most boards use the `atmega32u4` chip. The `BOOTLOADER_SIZE` will need to be adjusted based on your MCU type. It's defaulted to the Teensy, since that's the most common controller. Below is quoted from the `Makefile`.

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=512
```

At the bottom of the file, you'll find lots of features to turn on and off - all of these options should be set with `?=` to allow for the keymap overrides. `?=` only assigns if the variable was previously undefined. For the full documenation of these features, see the [Makefile options](#makefile-options).

## `/keyboards/<keyboard>/readme.md`

This is where you'll describe your keyboard - please write as much as you can about it! Talking about default functionality/features is useful here. Feel free to link to external pages/sites if necessary. Images can be included here as well. This file will be rendered into a webpage at qmk.fm/keyboards/<keyboard>/.

## `/keyboards/<keyboard>/<keyboard>.c`

This is where all of the custom logic for your keyboard goes - you may not need to put anything in this file, since a lot of things are configured automatically. All of the `*_kb()` functions are defined here. If you modify them, remember to keep the calls to `*_user()`, or things in the keymaps might not work. You can read more about the functions [here](#custom-quantum-functions-for-keyboards-and-keymaps)

## `/keyboards/<keyboard>/<keyboard>.h`

Here is where you can (optionally) define your `KEYMAP` function to remap your matrix into a more readable format. With ortholinear boards, this isn't always necessary, but it can help to accomodate the dead spots on your matrix, where there are keys that take up more than one space (2u, staggering, 6.25u, etc). The example shows the difference between the physical keys, and the matrix design:

```
#define KEYMAP( \
    k00, k01, k02, \
      k10,  k11   \
) \
{ \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

Each of the `kxx` variables needs to be unique, and usually follows the format `k<row><col>`. You can place `KC_NO` where your dead keys are in your matrix.

# Unit Testing

If you are new to unit testing, then you can find many good resources on internet. However most of it is scattered around in small pieces here and there, and there's also many different opinions, so I won't give any recommendations.

Instead I recommend these two books, explaining two different styles of Unit Testing in detail.

* "Test Driven Development: By Example: Kent Beck"
* "Growing Object-Oriented Software, Guided By Tests: Steve Freeman, Nat Pryce"

If you prefer videos there are Uncle Bob's [Clean Coders Videos](https://cleancoders.com/), which unfortunately cost quite a bit, especially if you want to watch many of them. But James Shore has a free [Let's Play](http://www.jamesshore.com/Blog/Lets-Play) video series.

## Google Test and Google Mock
It's possible to Unit Test your code using [Google Test](https://github.com/google/googletest). The Google Test framework also includes another component for writing testing mocks and stubs, called "Google Mock". For information how to write the actual tests, please refer to the documentation on that site.

## Use of C++

Note that Google Test and therefore any test has to be written in C++, even if the rest of the QMK codebases is written in C. This should hopefully not be a problem even if you don't know any C++, since there's quite clear documentation and examples of the required C++ features, and you can write the rest of the test code almost as you would write normal C. Note that some compiler errors which you might get can look quite scary, but just read carefully what it says, and you should be ok.

One thing to remember, is that you have to append `extern "C"` around all of your C file includes.

## Adding tests for new or existing features

If you want to unit test some feature, then take a look at the existing serial_link tests, in the `quantum/serial_link/tests folder`, and follow the steps below to create a similar structure.

1. If it doesn't already exist, add a test subfolder to the folder containing the feature.
2. Create a `testlist.mk` and a `rules.mk` file in that folder.
3. Include those files from the root folder `testlist.mk`and `build_test.mk` respectively.
4. Add a new name for your testgroup to the `testlist.mk` file. Each group defined there will be a separate executable. And that's how you can support mocking out different parts. Note that it's worth adding some common prefix, just like it's done for the serial_link tests. The reason for that is that the make command allows substring filtering, so this way you can easily run a subset of the tests.
5. Define the source files and required options in the `rules.mk` file.
   * `_SRC` for source files
   * `_DEFS` for additional defines
   * `_INC` for additional include folders
6. Write the tests in a new cpp file inside the test folder you created. That file has to be one of the files included from the `rules.mk` file.

Note how there's several different tests, each mocking out a separate part. Also note that each of them only compiles the very minimum that's needed for the tests. It's recommend that you try to do the same. For a relevant video check out [Matt Hargett "Advanced Unit Testing in C & C++](https://www.youtube.com/watch?v=Wmy6g-aVgZI)

## Running the tests

To run all the tests in the codebase, type `make test`. You can also run test matching a substring by typing `make test-matchingsubstring` Note that the tests are always compiled with the native compiler of your platform, so they are also run like any other program on your computer.

## Debugging the tests

If there are problems with the tests, you can find the executable in the `./build/test` folder. You should be able to run those with GDB or a similar debugger.

## Full Integration tests

It's not yet possible to do a full integration test, where you would compile the whole firmware and define a keymap that you are going to test. However there are plans for doing that, because writing tests that way would probably be easier, at least for people that are not used to unit testing.

In that model you would emulate the input, and expect a certain output from the emulated keyboard.
