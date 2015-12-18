# Getting started

There are two main ways you could customize the ErgoDox EZ.

## The Easy Way: Use an existing firmware file and just flash it

1. Download and install the [Teensy Loader](https://www.pjrc.com/teensy/loader.html)
2. Find a firmware file you like. You can find a few if these in the keymaps subdirectory right here. The file you need ends with .hex, and you can look at its .c counterpart (or its PNG image) to see what you'll be getting. You can also use the [Massdrop configurator](https://keyboard-configurator.massdrop.com/ext/ergodox) to create a firmware Hex file you like.
3. Download the firmware file
4. Connect the keyboard, press its Reset button (gently insert a paperclip into the hole in the top-right corner) and flash it using the Teensy loader you installed on step 1 and the firmware you downloaded.

## More technical: create your own totally custom firmware by editing the source files. 

This requires a little bit of familiarity with coding.

1. Go to https://github.com/jackhumbert/qmk_firmware and read the Readme at the base of this repository, top to bottom. Then come back here :)
2. Clone the repository (download it)
3. Set up a build environment as per https://www.pjrc.com/teensy/gcc.html
4. Customize the firmware to your liking and compile it
5. Flash it using the [Teensy loader](https://www.pjrc.com/teensy/loader.html) as described in step 4 above.
6. Submit your work as a pull request to this repository, so others can also use it. :)

Good luck! :)

## Finding the keycodes you need

Let's say you want a certain key in your layout to send a colon; to figure out what keycode to use to make it do that, you're going to need `quantum/keymap_common.h`.

That file contains a big list of all of the special, fancy keys (like, being able to shend % on its own and whatnot).

If you want to send a plain vanilla key, you can look up its code under `doc/keycode.txt`. That's where all the boring keys hang out.
