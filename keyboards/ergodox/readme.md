# The Easy Way

If you have an ErgoDox EZ, the absolute easiest way for you to customize your firmware is using the [graphical configurator](http://configure.ergodox-ez.com), which uses QMK under the hood.

If you can find firmware someone else has made that does what you want, that
is the easiest way to customize your ErgoDox.  It requires no programming
experience or the setup of a build environment.

Quickstart:

  - Find and download an existing firmware
    [from Other Firmware Options](#other-firmware-options)

  - Then flash the firmware to your [ErgoDox Ez](#ergodox-ez)
    or [ErgoDox Infinity](#ergodox-infinity)

# Customizing Keymaps

There are many existing keymaps in the "keymaps" directory.  If you just want
to use one of them, you don't need to modify keymaps and can just build and
flash the firmware as described below.  These directories each have a
"readme.md" file which describe them.

If none of the existing keymaps suit you, you can create your own custom
keymap.  This will require some experience with coding.  Follow these steps
to customize a keymap:

  - Read the [qmk firmware README](https://github.com/qmk/qmk_firmware) from top to bottom.  Then come back here.  :)

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

## ErgoDox EZ

The Ez uses the [Teensy Loader](https://www.pjrc.com/teensy/loader.html).

Linux users need to modify udev rules as described on the [Teensy
Linux page].  Some distributions provide a binary, maybe called
`teensy-loader-cli`.

[Teensy Linux page]: https://www.pjrc.com/teensy/loader_linux.html

To flash the firmware:

  - Build the firmware with `make keymapname`, for example `make default`
  - This will result in a hex file called `ergodox_ez_keymapname.hex`, e.g.
    `ergodox_ez_default.hex`

  - Start the teensy loader.

  - Load the .hex file into it.

  - Press the Reset button by inserting a paperclip gently into the reset hole
    in the top right corder.

  - Click the button in the Teensy app to download the firmware.

To flash with ´teensy-loader-cli´:

  - Build the firmware with `make keymapname`, for example `make default`

  - Run ´<path/to/>teensy_loader_cli --mcu=atmega32u4 -w ergodox_ez_<keymap>.hex´

  - Press the Reset button by inserting a paperclip gently into the reset hole
    in the top right corder.

## ErgoDox Infinity

The Infinity is two completely independent keyboards, and needs to be flashed
for the left and right halves seperately.  To flash them:

  - Build the firmware with `make infinity-keymapname`

  - Plug in the left hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make infinity-keymapname-dfu-util`

  - Build right hand firmware with `make infinity-keymapname MASTER=right`

  - Plug in the right hand keyboard only.

  - Press the program button (back of keyboard, above thumb pad).

  - Install the firmware with `sudo make infinity-keymapname-dfu-util MASTER=right`

More information on the Infinity firmware is available in the [TMK/chibios for
Input Club Infinity Ergodox](https://github.com/fredizzimo/infinity_ergodox/blob/master/README.md)

### Infinity Master/Two Halves

The Infinity is two completely independent keyboards, that can connect together.
You have a few options in how you flash the firmware:

- Flash the left half, rebuild the firmware with "MASTER=right" and then flash
  the right half.  This allows you to plug in either half directly to the
  computer and is what the above instructions do.

- Flash the left half, then flash the same firmware on the right.  This only
  works when the left half is plugged directly to the computer and the keymap
  is mirrored.  It saves the small extra step of rebuilding with
  "MASTER=right".

- The same as the previous one but with "MASTER=right" when you build the
  firmware, then flash the same firmware to both halves.  You just have to
  directly connect the right half to the computer.

- For minor changes such as changing only the keymap without having updated
  any part of the firmware code itself, you can program only the MASTER half.
  It is safest to program both halves though.

# Contributing your keymap

The QMK firmware is open-source, so it would be wonderful to have your contribution! Within a very short time after launching we already amassed dozens of user-contributed keymaps, with all sorts of creative improvements and tweaks. This is very valuable for people who aren't comfortable coding, but do want to customize their ErgoDox. To make it easy for these people to use your layout, I recommend submitting your PR in the following format.

1. All work goes inside your keymap subdirectory (`keymaps/german` in this example).
2. `keymap.c` - this is your actual keymap file; please update the ASCII comments in the file so they correspond with what you did.
3. `readme.md` - a readme file, which GitHub would display by default when people go to your directory. Explain what's different about your keymap, what you tweaked or how it works. No specific format to follow, just communicate what you did. :)
4. Any graphics you wish to add must be hosted elsewhere (please don't include images in your PR). This is absolutely not a must. If you feel like it, you can use [Keyboard Layout Editor](http://keyboard-layout-editor.com) to make something and grab a screenshot, but it's really not a must. If you do have graphics, your readme can just embed the graphic as a link (`![alt-text](url)`), just like I did with the default layout.

# Finding the keycodes you need

Let's say you want a certain key in your layout to send a colon; to figure out what keycode to use to make it do that, you're going to need `quantum/keymap_common.h`.

That file contains a big list of all of the special, fancy keys (like, being able to send % on its own and whatnot).

If you want to send a plain vanilla key, you can look up its code under `doc/keycode.txt`. That's where all the boring keys hang out.

# Other Firmware Options

There are external tools for customizing the layout, but those do not use
the featurs of this qmk firmware.  These sites include:

  - The official [ErgoDox EZ configurator](http://configure.ergodox-ez.com)
  - [Massdrop configurator](https://keyboard-configurator.massdrop.com/ext/ergodox) for EZ, works but not officially supported
  - [Input Club configurator](https://input.club/configurator-ergodox) for Infinity, provides left and right files

You can also find an existing firmware that you like, for example from:

  - [Dozens of community-contributed keymaps](http://qmk.fm/keyboards/ergodox/)
