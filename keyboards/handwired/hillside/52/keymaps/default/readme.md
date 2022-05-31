# Hillside 52 Default Keymap

For easier initial use, this keymap follows the layout of more standard keyboards where possible. It is a starting point for you to tweak over time to suit your preferences better. You can easily customize it with the [QMK configurator](https://config.qmk.fm/#/handwired/hillside/52/LAYOUT).

Some of its key features are:

- An inverted-T arrow cluster on the base layer.
- Numbers and symbols along the top row of their layers for familiarity.
- Comfortable modifier and function or symbol combinations on the non-base layers using modifiers on the home row of the symbol and number/function layers.
- A layer with both navigation and editing keys allows document editing without leaving the layer.
- QWERTY, Colemak-DH and Dvorak base layer options.

## Base Layer

![Base QWERTY layer](https://imgur.com/vO9pnaY.png)

The base layer provides a very standard key layout with four differences:

- Numbers, functions and most symbols are accessed with number and symbol shift keys.
- Escape is on the bottom row.
- The left thumb has a shift key that affects the next key pressed. So to get 'A', press and release the thumb shift key, press 'a'. You can also hold the key down, and it will work like a standard shift key. There are still standard shift keys at either end of the keyboard.
- The lower left key turns on a mode that capitalizes all letters until something other than a letter, digit, dash, underscore, delete or backspace is typed. The caps word mode also times out after five seconds of no key presses.
- The Menu and AltGr keys are on a layer.

The default layout is QWERTY with alternatives of Dvorak and Colemak-DH, and the alt/option and win/command key locations are swappable for windows or mac.

<details>
<summary>Details of Dvorak and Coleman-DH</summary>
The Dvorak and Colemak-DH base layers have identical non-alpha and non-symbol keys as the QWERTY base layer.
![Base Dvorak layer](https://imgur.com/Baxt3L9.png)
![Base Colemak layer](https://imgur.com/5BHeur8.png)
</details>


## Symbol and Media Layer

![Symbol layer](https://imgur.com/lg5PqMX.png)

Holding down the SYM key accesses the symbol layer:

- The symbols not present on the base layer are along the top row and right side, similar to a full-size keyboard.
- Duplicates of the modifier keys are along the left home keys. This positioning allows a very comfortable combination of any set of modifiers plus a key on the right side of the board.
- Forward delete is on the upper right, taking backspace's place.
- The Window OS application menu key is on the lower right. 
- The AltGr key affects the next key pressed so that it can combine with a key on any layer. It changes the meaning of the next key pressed after the AltGr key is pressed and released. For example, to do AltGr-h: press SYM, press and release AltGr, release SYM, press and release h.


## Navigation, Editing, Number and Function Layer

![Navigation layer](https://imgur.com/eCzNwZP.png)

Holding down the Nav/Edit key accesses the navigation, editing, number and function layer:

- Numbers are along the top row, and function keys are on the bottom.
- The arrow keys on the left can be combined with the home row modifiers on the right to easily move around and select text, which can then be cut, copied and pasted.


## Adjust Layer

![Adjust layer](https://imgur.com/bC3CRSK.png)

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
- Change the shift keys to one-shot,
  where pressing and releasing them shifts the next key pressed.
  That is much easier on your hands than holding them down.
  Yet they can still be held as usual if desired.
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

  The online configurator provides a straightforward visual way to work with a simple layout
   and uses a .json keymap format.
 So this default ```keymap.json``` was created with the online configurator
   and formatted for easier reading and editing.

  If you wish, you can edit the ```keymap.json``` directly in a text editor, optionally use the below ```json2hill52.py``` to restore the spacing, and then compile and flash it.

  Or, you can use the graphical configurator to edit the keymap. To do that:

  - Open the [QMK configurator](https://config.qmk.fm/#/handwired/hillside/52/LAYOUT)
 - Using the green up arrow button, load the keymap from ```qmk_firmware/keyboards/handwired/hillside/52/keymaps/default/keymap.json```
 - Make the changes you wish to the layout
 - Save the keymap using the green down arrow button.
 - Copy those changes back into your QMK repository and reformat them for easy reading using the format script:

 ```
 ./keyboards/handwired/hillside/52/keymaps/json2hill52.py \
     --input <Your download directory>/default.json \
     > ./keyboards/handwired/hillside/52/keymaps/default/keymap.json
 ```
 
You may need to make that script executable with ```chmod +x```. After your keymap is safely copied and formatted, you may want to remove the keymap from your download directory so later downloads will automatically receive the same file name.

  After either method of editing, compile and flash the keymap as usual.

  You can combine a .json based keymap with more advanced features specified in .c files
   with a bit more complexity.
 For example, see
 [pierrec83's Kyria map](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/pierrec83).
 
