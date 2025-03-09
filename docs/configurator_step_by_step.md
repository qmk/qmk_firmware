# QMK Configurator: Step by Step

This page describes the steps for building your firmware in QMK Configurator.

## Step 1: Select Your Keyboard

Click the drop down box and select the keyboard you want to create a keymap for.

::: tip
If your keyboard has several versions, make sure you select the correct one.
:::

I'll say that again because it's important:

::: warning
**MAKE SURE YOU SELECT THE RIGHT VERSION!**
:::

Unfortunately if your keyboard has been advertised to be powered by QMK but is not in the list, you will **not** be able to use Configurator to customize your keyboard.

Chances are a developer hasn't gotten round to adding support or we haven't had a chance to merge it in yet. If there is no active [Pull Request](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+is%3Apr+label%3Akeyboard), contact the manufacturer and encourage them to add support.

## Step 2: Select Your Keyboard Layout

Choose the layout that best represents the keymap you want to create. Some keyboards do not have enough layouts or correct layouts defined yet. They will be supported in the future.

::: warning
Sometimes there isn't a layout that supports your exact build. In that case select `LAYOUT_all`.
:::

## Step 3: Name Your Keymap

Call this keymap what you want.

::: tip
If you are running into issues when compiling, it may be worth changing this name, as it may already exist in the QMK Firmware repo.
:::

## Step 4: Define Your Keymap

Keycode Entry is accomplished in one of 3 ways:

1. Drag and drop
2. Clicking on an empty spot on the layout, then clicking the keycode you desire
3. Clicking on an empty spot on the layout, then pressing the physical key on your keyboard

::: tip
Hover your mouse over a key and a short blurb will tell you what that keycode does. For a more verbose description please see:
:::

* [Basic Keycode Reference](keycodes_basic)
* [Advanced Keycode Reference](feature_advanced_keycodes)

::: warning
If your selected layout doesn't match your physical build leave the unused keys blank. If you're not sure which key is in use, for example you have a one backspace key but `LAYOUT_all` has 2 keys, put the same keycode in both locations.
:::

## Step 5: Save Your Keymap for Future Changes

When you're satisfied with your keymap or just want to work on it later, press the `Download this QMK Keymap JSON File` button. It will save your keymap to your computer. You can then load this .json file in the future by pressing the `Upload a QMK Keymap JSON File` button.

::: warning
**CAUTION:** This is not the same type of .json file used for kbfirmware.com or any other tool. If you try to use this for those tools, or the .json from those tools with QMK Configurator, you will encounter problems.
:::

## Step 6: Compile Your Firmware File

Press the green `Compile` button.

When the compilation is done, you will be able to press the green `Download Firmware` button.

## Next steps: Flashing Your Keyboard

Please refer to [Flashing Firmware](newbs_flashing).
