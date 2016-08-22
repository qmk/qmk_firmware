
# Customizing Keymaps

There are many existing keymaps in the "keymaps" directory.  If you just want
to use one of them, you don't need to modify keymaps and can just build and
flash the firmware as described below.  These directories each have a
"readme.md" file which describe them.

If none of the existing keymaps suit you, you can create your own custom
keymap.  This will require some experience with coding.  Follow these steps
to customize a keymap:

  - Read the [qmk firmware README](https://github.com/jackhumbert/qmk_firmware) from top to bottom.  Then come back here.  :)

  - Clone the qmk_firmware repository

  - Set up your build environment (see below).

  - Make a new directory under "keymaps" to hold your customizations.

  - Copy an existing keymap that is close to what you want, such as
    "keymaps/default/keymap.c".

  - Use an editor to modify the new "keymap.c".  See "Finding the keycodes you
    need" below).  Try to edit the comments as well, so the "text graphics"
    represent your layout correctly.

  - Compile your new firmware (see below)

  - Flash your firmware (see below)

  - Test the changes.

  - Submit your keymap as a pull request to the qmk_firmware repository so
    others can use it.  You will want to add a "readme.md" that describes the
    keymap.

# Build Dependencies

Before you can build, you will need the build dependencies.  There is a script
to try to do this for Linux:

  - Run the `util/install_dependencies.sh` script as root.

For the Infinity, you need the chibios submodules to be checked out or you
will receive errors about the build process being unable to find the chibios
files.  Check them out with:

  - Go to the top level repo directory and run: `git submodule update --init --recursive`

# Flashing Firmware

## ErgoDox Ez

The Ez uses the [Teensy Loader](https://www.pjrc.com/teensy/loader.html).

Linux users need to modify udev rules as described on the Teensy Linux page.
Some distributions provide a binary, maybe called `teensy-loader-cli`).

To flash the firmware:

  - Build the firmware with `make keymap=keymapname`, for example `make
    keymap=default`

  - This will result in a hex file called `ergodox_ez_keymapname.hex`, e.g.
    `ergodox_ez_default.hex`

  - Start the teensy loader.

  - Load the .hex file into it.

  - Press the Reset button by inserting a paperclip gently into the reset hole
    in the top right corder.

  - Click the button in the Teensy app to download the firmware.

## ErgoDox Infinity

The Infinity is two completely independent keyboards, and needs to be flashed
for the left and right halves seperately.  To flash them:

  - Build the firmware with `make keymap=keymapname subproject=infinity`

  - Plug in the left hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make dfu-util keymap=keymapname subproject=infinity`

  - Build left hand firmware with `make keymap=keymapname subproject=infinity MASTER=right`

  - Plug in the right hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make dfu-util keymap=keymapname subproject=infinity MASTER=right`

More information on the Infinity firmware is available in the [TMK/chibios for
Input Club Infinity Ergodox](https://github.com/fredizzimo/infinity_ergodox/blob/master/README.md)

# Contributing your keymap

The QMK firmware is open-source, so it would be wonderful to have your contribution! Within a very short time after launching we already amassed dozens of user-contributed keymaps, with all sorts of creative improvements and tweaks. This is very valuable for people who aren't comfortable coding, but do want to customize their ErgoDox. To make it easy for these people to use your layout, I recommend submitting your PR in the following format.

1. All work goes inside your keymap subdirectory (`keymaps/german` in this example).
2. `keymap.c` - this is your actual keymap file; please update the ASCII comments in the file so they correspond with what you did.
3. `readme.md` - a readme file, which GitHub would display by default when people go to your directory. Explain what's different about your keymap, what you tweaked or how it works. No specific format to follow, just communicate what you did. :)
4. Any graphics you wish to add. This is absolutely not a must. If you feel like it, you can use [Keyboard Layout Editor](http://keyboard-layout-editor.com) to make something and grab a screenshot, but it's really not a must. If you do have graphics, your readme can just embed the graphic as a link, just like I did with the default layout.

# Finding the keycodes you need

Let's say you want a certain key in your layout to send a colon; to figure out what keycode to use to make it do that, you're going to need `quantum/keymap_common.h`.

That file contains a big list of all of the special, fancy keys (like, being able to send % on its own and whatnot).

If you want to send a plain vanilla key, you can look up its code under `doc/keycode.txt`. That's where all the boring keys hang out.

# Other Firmware Options

There are external tools for customizing the layout, but those do not use
the featurs of this qmk firmware.  These sites include:

  - [Massdrop configurator](https://keyboard-configurator.massdrop.com/ext/ergodox) for Ez
  - [Input Club configurator](https://input.club/configurator-ergodox) for Infinity, provides left and right files

You can also find an existing firmware that you like, for example from:

  - [Dozens of community-contributed keymaps](http://qmk.fm/keyboards/ergodox/)

This qmk firmware also provides the ability to customize keymaps, but requires
a toolchain to build the firmware.  See below for instructions on building
firmware and customizing keymaps.
