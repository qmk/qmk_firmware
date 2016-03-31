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
3. Set up a build environment as per [pjrc.com/teensy/gcc.html](https://www.pjrc.com/teensy/gcc.html)
    - Using a Mac and have homebrew? just run `brew tap osx-cross/avr && brew install avr-libc`
4. Copy `keymaps/default/keymap.c` into `keymaps/your_name/keymap.c` (for example, `keymaps/german/keymap.c`)
5. Edit this file, changing keycodes to your liking (see "Finding the keycodes you need" below). Try to edit the comments as well, so the "text graphics" represent your layout correctly. See below for more tips on sharing your work.
6. Compile your firmware by running `make clean` followed by `make KEYMAP=your_name`. For example, `make KEYMAP=german`. This will result in a hex file, which will always be called `ergodox_ez.hex`, regardless of your keymap name.
6. Flash this hex file using the [Teensy loader](https://www.pjrc.com/teensy/loader.html) as described in step 4 in the "Easy Way" above.
7. Submit your work as a pull request to this repository, so others can also use it. :) See below on specifics.

Good luck! :)

## Contributing your keymap

The ErgoDox EZ firmware is open-source, so it would be wonderful to have your contribution! Within a very short time after launching we already amassed almost 20 user-contributed keymaps, with all sorts of creative improvements and tweaks. This is very valuable for people who aren't comfortable coding, but do want to customize their ErgoDox EZ. To make it easy for these people to use your layout, I recommend submitting your PR in the following format. 

1. All work goes inside your keymap subdirectory (`keymaps/german` in this example).
2. `keymap.c` - this is your actual keymap file; please update the ASCII comments in the file so they correspond with what you did.
3. `german.hex` - a compiled version of your keymap. Commit it to the repo with `git add -f` as hex files are ignored by default. This allows people to just download your hex file and flash it without having to set up a build toolchain to make it.
3. `readme.md` - a Readme file, which GitHub would display by default when people go to your directory. Explain what's different about your keymap, what you tweaked or how it works. No specific format to follow, just communicate what you did. :)
4. Any graphics you wish to add. This is absolutely not a must. If you feel like it, you can use [Keyboard Layout Editor](http://keyboard-layout-editor.com) to make something and grab a screenshot, but it's really not a must. If you do have graphics, your Readme can just embed the graphic as a link, just like I did with the default layout. 


## Finding the keycodes you need

Let's say you want a certain key in your layout to send a colon; to figure out what keycode to use to make it do that, you're going to need `quantum/keymap_common.h`.

That file contains a big list of all of the special, fancy keys (like, being able to send % on its own and whatnot).

If you want to send a plain vanilla key, you can look up its code under `doc/keycode.txt`. That's where all the boring keys hang out.
