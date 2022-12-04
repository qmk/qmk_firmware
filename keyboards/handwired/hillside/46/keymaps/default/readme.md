# Hillside 46 Default Keymap

For easier initial use, this keymap follows the layout of more standard keyboards where possible. It is a starting point for you to tweak over time to suit your preferences better. You can easily customize it with the [QMK configurator](https://config.qmk.fm/#/handwired/hillside/46/LAYOUT).

Some of its key features are:

- Numbers and symbols along the top row of their layers for familiarity.
- Comfortable modifier and function or symbol combinations on the non-base layers using modifiers on the home row of the symbol and number/function layers.
- A layer with both navigation and editing keys allows document editing without leaving the layer.
- QWERTY, Colemak-DH and Dvorak base layer options.

## Base Layer


![Base QWERTY layer](https://imgur.com/C2kxwOuh.png)

The base layer provides a very standard key layout with four differences:

- Numbers, functions and most symbols are accessed with number and symbol shift keys.
- Escape is on the upper left thumb.
- The left thumb has a shift key that affects the next key pressed. So to get 'A', press and release the thumb shift key, press 'a'. You can also hold the key down, and it will work like a standard shift key.
- Caps word toggles a mode that capitalizes all letters until something other than a letter, digit, dash, underscore, delete or backspace is typed. The mode also times out five seconds after the last key press.
- The Menu and AltGr keys are on a layer.

The default layout is QWERTY with alternatives of Dvorak and Colemak-DH, and the alt/option and win/command key locations are swappable for windows or mac.

<details>
<summary>Details of Dvorak and Colemak-DH</summary>
The Dvorak and Colemak-DH base layers have identical non-alpha and non-symbol keys as the QWERTY base layer.
![Base Dvorak layer](https://imgur.com/5gGk2rOh.png)
![Base Colemak layer](https://imgur.com/xExBB8eh.png)
</details>


## Navigation, Editing, Number and Function Layer

![Navigation layer](https://imgur.com/Obx6oRTh.png)

Holding down the Nav/Edit key accesses the navigation, editing, number and function layer:

- Numbers are along the top row, and function keys are on the bottom.
- The arrow keys on the right can be combined with the home row modifiers on the left to easily move around and select text, which can then be cut, copied and pasted.


## Symbol and Media Layer

![Symbol layer](https://imgur.com/mzcB2JFh.png)

Holding down the SYM key accesses the symbol layer:

- The symbols not present on the base layer are along the top row and left side, arranged similarly to a large keyboard.
- Duplicates of the modifier keys are along the right home keys. This positioning allows a very comfortable combination of any set of modifiers plus a key on the left side of the board.
- Forward delete is on the upper right, taking backspace's place.
- The Window OS application menu key is on the right upper thumb. 
- The AltGr key affects the next key pressed so that it can combine with a key on any layer. It changes the meaning of the next key pressed after the AltGr key is pressed and released. For example, to do AltGr-h: press SYM, press and release AltGr, release SYM, press and release h.


## Adjust Layer

![Adjust layer](https://imgur.com/r3Ip7hxh.png)

Simultaneously holding down the Sym and Nav/Edit keys enables keys to adjust keyboard settings:

- The base layer can be set to QWERTY, Colemak-DH or Dvorak, although the keyboard reverts to QWERTY each time it is plugged in.
- Alt/option and GUI/command can be swapped for mac users or restored to the windows norm.
- The backlight LEDs can be enabled, disabled, and controlled.
- BOOT allows loading new firmware, such as for keymap changes.

## Make it Yours

If you are coming from a traditional keyboard,
  with a large set of physical keys,
  learning to use a column staggered (ergo) and layer-based keyboard,
  which uses layers instead of finger reaches to access numbers, symbols and functions,
  will be an adjustment for your muscle memory and your mental keyboard map.
This default layout tries to simplify that adjustment by keeping things in the expected spots when possible.

Yet this layout is only a decent compromise and is not optimal for each user.
The online configurator makes it easy to tweak this layout to your needs.
You can add additional layers or completely switch around what these do.

A good metaphor is to think of your keymap as a bonsai tree that you tweak slightly over time
  in response to ideas of how it might serve you better.

Some changes you might consider making:

- If you are on a mac, switch the editing keys from ctrl-x to cmd-x.
- Put some of your most-used key combinations on the unused keys
  on the symbol layer.
- Instead of holding down the thumb key to keep the symbol layer active,
  you could use a one-shot layer key.
  One-shot modifiers are likely less stress on your hands and may even be faster.
  You would still be able to hold it down instead.
- Instead of holding down the key for the number layer,
  you could make it a layer toggle.

Here are some other keymaps for inspiration and ideas:

- The [Ferris default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ferris/keymaps/default) uses more advanced features as it has far fewer keys to work with.
- The [Miryoku](https://github.com/manna-harbour/miryoku/tree/master/docs/reference) keymap ensures that all modifiers are comfortably available with each character key.
- The [Kyria default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/default) has different keymap choices.

## Why no keymap.c

The online configurator provides a straightforward visual way
   to work with a simple layout and uses a .json keymap format.
So this default ```keymap.json``` was created with the online configurator.

If you wish, you can edit the ```keymap.json``` directly in a text editor,  compile it and flash it.

Or, you can use the graphical configurator to edit the keymap. To do that:

- Open the [QMK configurator](https://config.qmk.fm/#/handwired/hillside/46/LAYOUT)
- Using the green up arrow button, load the keymap from ```qmk_firmware/keyboards/handwired/hillside/46/keymaps/default/keymap.json```
- Make the changes you wish to the layout
- Save the keymap using the green down arrow button.
- Move the downloaded keymap back into your QMK repository 
     at the same location as above.
- Rename it back to keymap.json
- Compile and flash the firmware.

You can combine a .json based keymap with more advanced features
  specified in .c files with a bit more complexity.
For example, see
 [pierrec83's Kyria map](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/pierrec83).
 

### Pretty Printing
 
The QMK configurator's .json download has only one key per line,
so it is hard to visualize the keymap if editing manually.
If you want, the Hillside git repo has a pretty-printing script for the keymap.json file.
 
As with anything downloaded from the internet, you should take some steps to assure yourself that the script will not harm your computer nor steal your data. The script is short, so reading it should at least convince you it is rearranging and printing the keymap feed to it, not reading any banking data on your computer.
See the [Hillside wiki](https://github.com/mmccoyd/hillside/wiki) for the script.

