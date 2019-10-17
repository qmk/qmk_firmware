# Building Your First Firmware

Now that you have setup your build environment you are ready to start building custom firmware. For this section of the guide we will bounce between 3 programs- your file manager, your text editor, and your terminal window. Keep all 3 open until you are done and happy with your keyboard firmware.

If you have closed and reopened your terminal window since following the first part of the guide, don't forget to `cd qmk_firmware` so that your terminal is in the correct directory.

## Navigate To Your Keymaps Folder

Start by navigating to the `keymaps` folder for your keyboard.

If you are on macOS or Windows there are commands you can use to easily open the keymaps folder.

### macOS:

``` open keyboards/<keyboard_folder>/keymaps ```

### Windows:

``` start .\\keyboards\\<keyboard_folder>\\keymaps ```

## Create a Copy Of The `default` Keymap

Once you have the `keymaps` folder open you will want to create a copy of the `default` folder. We highly recommend you name your folder the same as your GitHub username, but you can use any name you want as long as it contains only lower case letters, numbers, and the underscore character.

To automate the process, you also have the option to run the `new_keymap.sh` script. 

Navigate to the `qmk_firmware/util` directory and type the following:

```
./new_keymap.sh <keyboard path> <username>
```

For example, for a user named John, trying to make a new keymap for the 1up60hse, they would type in

```
./new_keymap.sh 1upkeyboards/1up60hse john
```

## Open `keymap.c` In Your Favorite Text Editor

Open up your `keymap.c`. Inside this file you'll find the structure that controls how your keyboard behaves. At the top of `keymap.c` there may be some defines and enums that make the keymap easier to read. Farther down you'll find a line that looks like this:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

This line indicates the start of the list of Layers. Below that you'll find lines containing either `LAYOUT` or `KEYMAP`, and these lines indicate the start of a layer. Below that line is the list of keys that comprise a that particular layer.

!> When editing your keymap file be careful not to add or remove any commas. If you do you will prevent your firmware from compiling and it may not be easy to figure out where the extra, or missing, comma is.

## Customize The Layout To Your Liking

How to complete this step is entirely up to you. Make the one change that's been bugging you, or completely rework everything. You can remove layers if you don't need all of them, or add layers up to a total of 32. Check the following documentation to find out what you can define here:

* [Keycodes](keycodes.md)
* [Features](features.md)
* [FAQ](faq.md)

?> While you get a feel for how keymaps work, keep each change small. Bigger changes make it harder to debug any problems that arise.

## Build Your Firmware

When your changes to the keymap are complete you will need to build the firmware. To do so go back to your terminal window and run the build command:

    make <my_keyboard>:<my_keymap>

For example, if your keymap is named "xyverz" and you're building a keymap for a rev5 planck, you'll use this command:

    make planck/rev5:xyverz

While this compiles you will have a lot of output going to the screen informing you of what files are being compiled. It should end with output that looks similar to this:

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex                                                        [OK]
 * File size is fine - 18392/28672
```

## Flash Your Firmware

Move on to [Flashing Firmware](newbs_flashing.md) to learn how to write your new firmware to your keyboard.
