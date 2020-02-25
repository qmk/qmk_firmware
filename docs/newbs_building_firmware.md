# Building Your First Firmware

Now that you have setup your build environment you are ready to start building custom firmware. For this section of the guide we will bounce between 3 programs- your file manager, your text editor, and your terminal window. Keep all 3 open until you are done and happy with your keyboard firmware.

## Create a New Keymap

To create your own keymap you'll want to create a copy of the `default` keymap. If you configured your build environment in the last step you can do that easily with the QMK CLI:

    qmk new-keymap

If you did not configure your environment, or you have multiple keyboards, you can specify a keyboard name:

    qmk new-keymap -kb <keyboard_name>

Look at the output from that command, you should see something like this:

    Ψ <github_username> keymap directory created in: /home/me/qmk_firmware/keyboards/clueboard/66/rev3/keymaps/<github_username>

This is the location of your new `keymap.c` file.

## Open `keymap.c` In Your Favorite Text Editor

Open your `keymap.c` file in your text editor. Inside this file you'll find the structure that controls how your keyboard behaves. At the top of `keymap.c` there may be some defines and enums that make the keymap easier to read. Farther down you'll find a line that looks like this:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

This line indicates where the list of Layers begins. Below that you'll find lines containing `LAYOUT`, and these lines indicate the start of a layer. Below that line is the list of keys that comprise a particular layer.

!> When editing your keymap file be careful not to add or remove any commas. If you do you will prevent your firmware from compiling and it may not be easy to figure out where the extra, or missing, comma is.

## Customize The Layout To Your Liking

How to complete this step is entirely up to you. Make the one change that's been bugging you, or completely rework everything. You can remove layers if you don't need all of them, or add layers up to a total of 32. There are a lot of features in QMK, explore the sidebar to the left under "Using QMK" to see the full list. To get you started here are a few of the easier to use features:

* [Basic Keycodes](keycodes_basic.md)
* [Quantum Keycodes](quantum_keycodes.md)
* [Grave/Escape](feature_grave_esc.md)
* [Mouse keys](feature_mouse_keys.md)

?> While you get a feel for how keymaps work, keep each change small. Bigger changes make it harder to debug any problems that arise.

## Build Your Firmware

When your changes to the keymap are complete you will need to build the firmware. To do so go back to your terminal window and run the compile command:

    qmk compile

If you did not configure your environment, or you have multiple keyboards, you can specify a keyboard and/or keymap:

    qmk compile -kb <keyboard> -km <keymap>

While this compiles you will have a lot of output going to the screen informing you of what files are being compiled. It should end with output that looks similar to this:

```
Linking: .build/planck_rev5_default.elf                                                             [OK]
Creating load file for flashing: .build/planck_rev5_default.hex                                     [OK]
Copying planck_rev5_default.hex to qmk_firmware folder                                              [OK]
Checking file size of planck_rev5_default.hex                                                       [OK]
 * The firmware size is fine - 27312/28672 (95%, 1360 bytes free)
```

## Flash Your Firmware

Move on to [Flashing Firmware](newbs_flashing.md) to learn how to write your new firmware to your keyboard.
