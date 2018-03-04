# Building Your First Firmware

Now that you have setup your build environment you are ready to start building custom firmware. For this section of the guide we will bounce between 3 programs- your file manager, your text editor, and your terminal window. Keep all 3 open until you are done and happy with your keyboard firmware.

If you have closed and reopened your terminal window since following the first part of the guide, don't forget to `cd qmk_firmware` so that your terminal is in the correct directory.

## Navigate To Your Keymaps Folder

Start by navigating to the `keymaps` folder for your keyboard.

{% hint style='info' %}
If you are on macOS or Windows there are commands you can use to easily open the `keymaps` folder.

macOS:

    open keyboards/<keyboard_folder>/keymaps

Windows:

    start keyboards/<keyboard_folder>/keymaps
{% endhint %}

## Create a Copy Of The `default` Keymap

Once you have the `keymaps` folder open you will want to create a copy of the `default` folder. We highly recommend you name your folder the same as your github username, but you can use any name you want as long as it contains only lower case letters, numbers, and the underscore character.

## Open `keymap.c` In Your Favorite Text Editor

Inside the `keymap.c` file you'll find the structure that controls how your keyboard behaves. At the top there may be some defines and enums that make the keymap easier to read. Farther down you'll find a line that looks like this:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

This line indicates the start of the list of Layers. Below that you'll find lines containing either `LAYOUT` or `KEYMAP`, and these lines indicate the start of a layer. Below that line is the list of keys that comprise a that particular layer.

{% hint style='warning' %}
When editing your keymap file be careful not to add or remove any commas. If you do you will prevent your firmware from compiling and it may not be easy to figure out where the extra, or missing, comma is.
{% endhint %}

## Customize The Layout To Your Liking

How to complete this step is entirely up to you. Make the one change that's been bugging you, or completely rework everything. You can remove layers if you don't need all of them, or add layers up to a total of 32. Check the following documentation to find out what you can define here:

* [Keycodes](keycodes.md)
* [Features](features.md)
* [FAQ](faq.md)

{% hint style='info' %}
While you get a feel for how keymaps work, keep each change small. Bigger changes make it harder to debug any problems that arise.
{% endhint %}
