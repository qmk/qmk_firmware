# QMK Configurator: Step by Step

This page describes the steps for building your firmware in QMK Configurator.

## Step 1: Select Your Keyboard

Click the drop down box and select the keyboard you want to create a keymap for.

?> If your keyboard has several versions, make sure you select the correct one.

I'll say that again because it's important:

!> **MAKE SURE YOU SELECT THE RIGHT VERSION!**

If your keyboard has been advertised to be powered by QMK but is not in the list, chances are a developer hasn't gotten to it yet or we haven't had a chance to merge it in yet. File an issue at [qmk_firmware](https://github.com/qmk/qmk_firmware/issues) requesting to support that particular keyboard, if there is no active [Pull Request](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+is%3Apr+label%3Akeyboard) for it. There are also QMK powered keyboards that are in their manufacturer's own github accounts. Double check for that as well.  <!-- FIXME(skullydazed): This feels too wordy and I'm not sure we want to encourage these kinds of issues. Also, should we prompt them to bug the manufacutrer? -->

## Step 2: Select Your Keyboard Layout

Choose the layout that best represents the keymap you want to create. Some keyboards do not have enough layouts or correct layouts defined yet. They will be supported in the future.

!> Sometimes there isn't a layout that supports your exact build. In that case select `LAYOUT_all`.

## Step 3: Name Your Keymap

Call this keymap what you want.

?> If you are running into issues when compiling, it may be worth changing this name, as it may already exist in the QMK Firmware repo.

## Step 4: Define Your Keymap

Keycode Entry is accomplished in one of 3 ways:

1. Drag and drop
2. Clicking on an empty spot on the layout, then clicking the keycode you desire
3. Clicking on an empty spot on the layout, then pressing the physical key on your keyboard

?> Hover your mouse over a key and a short blurb will tell you what that keycode does. For a more verbose description please see:

* [Basic Keycode Reference](keycodes_basic.md)
* [Advanced Keycode Reference](feature_advanced_keycodes.md)

!> If your selected layout doesn't match your physical build leave the unused keys blank. If you're not sure which key is in use, for example you have a one backspace key but `LAYOUT_all` has 2 keys, put the same keycode in both locations.

## Step 5: Save Your Keymap for Future Changes

When you're satisfied with your keymap or just want to work on it later, press the `Export Keymap` button. It will save your keymap to your computer. You can then load this .json file in the future by pressing the `Import Keymap` button.

!> **CAUTION:** This is not the same type of .json file used for kbfirmware.com or any other tool. If you try to use this for those tools, or the .json from those tools with QMK Configurator, you will encounter problems.

## Step 6: Compile Your Firmware File

Press the green `Compile` button.

When the compilation is done, you will be able to press the green `Download Firmware` button.

## Next steps: Flashing Your Keyboard

Please refer to [Flashing Firmware](newbs_flashing.md).
