# QMK Configurator

The [QMK Configurator](https://config.qmk.fm) is an online graphical user interface that generates QMK Firmware hex files.  

?> **Please follow these steps in order.**

Watch the [Video Tutorial](https://youtu.be/tx54jkRC9ZY)

The QMK Configurator works best with Chrome/Firefox. 


!> **Files from other tools such as KLE, or kbfirmware will not be compatible with QMK Configurator. Do not load them, do not import them. QMK Configurator is a DIFFERENT tool. **

## Selecting your keyboard

Click the drop down box and select the keyboard you want to create a keymap for. 

?> If your keyboard has several versions, make sure you select the correct one.** 

I'll say that again because it's important

!> **MAKE SURE YOU SELECT THE RIGHT VERSION!**

If your keyboard has been advertised to be powered by QMK but is not in the list, chances are a developer hasn't gotten to it yet or we haven't had a chance to merge it in yet. File an issue at [qmk_firmware](https://github.com/qmk/qmk_firmware/issues) requesting to support that particular keyboard, if there is no active [Pull Request](https://github.com/qmk/qmk_firmware/pulls?q=is%3Aopen+is%3Apr+label%3Akeyboard) for it. There are also QMK powered keyboards that are in their manufacturer's own github accounts. Double check for that as well. 

## Selecting your keyboard layout

Choose the layout that best represents the keymap you want to create. Some keyboards do not have enough layouts or correct layouts defined yet. They will be supported in the future. 

## Keymap Name

Call this keymap what you want. 

?> If you are running into issues when compiling, it may be worth changing this name, as it may already exist in the QMK  Firmware repo.

## Creating Your Keymap

Keycode Entry is accomplished in 3 ways.  
1. Drag and dropping 
2. Clicking on an empty spot on the layout and clicking the keycode you desire
3. Clicking on an empty spot on the layout, pressing the physical key on your keyboard. 

Hover your mouse over a key and a short blurb will tell you what that keycode does. For a more verbose description please see    

[Basic Keycode Reference](https://docs.qmk.fm/#/keycodes_basic)    
[Advanced Keycode Reference](https://docs.qmk.fm/#/feature_advanced_keycodes)    

In the event that you can't find a layout that supports your keymap, for example three spots for spacebar, or two spots for backspace, or 2 spots for shift etc etc, Fill them ALL up. 

### Example:

3 spots for spacebar: Fill them ALL with spacebar

2 spots for backspace: Fill them BOTH with backspace

2 spots for right shift: Fill them BOTH with right shift

1 spot for left shift and 1 spot for iso support: Fill them both with left shift

5 spots, but only 4 keys: Guess and check or ask someone who has done it before. 

## Saving Your Keymap for Future Edits

When you're satisfied with your keymap or just want to work on it later, press the `Export Keymap` button. It will save your keymap as the name you chose above appended with .json. 

You can then load this .json file in the future by pressing the `Import Keymap` button. 

!> **CAUTION:** This is not the same type of .json file used for kbfirmware.com or any other tool. If you try to use this for those tools, or the .json from those tools with QMK Configurator, there is a chance your keyboard will **explode**. 

## Generating your firmware file

Press the green `Compile` button.

When the compilation is done, you will be able to press the green `Download Firmware` button. 

## Flashing Your Keyboard

Please refer to [Flashing Firmware](newbs_flashing.md)

## Troubleshooting

#### My .json file is not working

If the .json file was generated with QMK Configurator, congratulations you have stumbled upon a bug. File an issue at [qmk_configurator](https://github.com/qmk/qmk_configurator/issues)

If not....how did you miss my big bold message at the top saying not to use other .json files? 

#### There are extra spaces in my layout? What do I do? 

If you're referring to having three spots for space bar, the best course of action is to just fill them all with space bar. The same can be done for backspace and shifts

#### What is the keycode for.......

Please see

[Basic Keycode Reference](https://docs.qmk.fm/#/keycodes_basic)    
[Advanced Keycode Reference](https://docs.qmk.fm/#/feature_advanced_keycodes)    

#### It won't compile

Please double check the other layers of your keymap to make sure there are no random keys present. 

## Problems and Bugs

We are always accepting customer requests and bug reports. Please file them at [qmk_configurator](https://github.com/qmk/qmk_configurator/issues)
