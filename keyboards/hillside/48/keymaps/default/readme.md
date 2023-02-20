# Hillside 48 Default Keymap

For easier initial use, this keymap follows the layout of more standard keyboards where possible. It is a starting point for you to tweak over time to suit your preferences better. You can easily customize it with the [QMK configurator](https://config.qmk.fm/#/hillside/48/LAYOUT).

Some of its key features are:

- Numbers and symbols along the top row of their layers for familiarity.
- Comfortable combination of modifier and function or symbol on the non-base layers
  using modifiers on the home row of the symbol and number/function layers.
- A layer with both navigation and editing keys allows document editing without leaving the layer.
- QWERTY, Colemak-DH and Dvorak base layer options.

## Base Layer

```
|  `    |  Q  |  W  |  E  |  R  |  T  |---------------------------|  Y  |  U  |  I  |  O  |  P  | BKSPC |
| TAB   |  A  |  S  |  D  |  F  |  G  |---------------------------|  H  |  J  |  K  |  L  |  ;  | ENTER |
| SHIFT |  Z  |  X  |  C  |  V  |  B  | ESC |---------------|CAPS |  N  |  M  |  ,  |  .  |  /  | SHIFT |
--------------|CTRL |-----| GUI | ALT | Sym |SHIFT|---| Nav |SPACE| ALT | GUI |-----|  '  |--------------
```

The base layer provides a very standard key layout with five differences:

- Numbers, functions and most symbols are accessed with number and symbol shift keys.
- Escape is on the left thumb.
- The left thumb has a shift key that affects the next key pressed. So to get 'A', press and release the thumb shift key, press 'a'. You can also hold the key down, and it will work like a standard shift key. There are still standard shift keys at either end of the keyboard.
- The right upper thumb turns on a mode that capitalizes all letters until something other than a letter, digit, dash, underscore, delete or backspace is typed. The caps word mode also times out after five seconds of no key presses.
- The Menu and AltGr keys are on a layer.

The default layout is QWERTY with alternatives of Dvorak and Colemak-DH, and the alt/option and the win/command key locations are swappable for windows or mac.


<details>
<summary>Details of Dvorak and Colemak-DH</summary>
The Dvorak and Colemak-DH base layers
  have identical non-alpha and non-symbol keys as the QWERTY base layer.

```
Dvorak
|  `    |  '  |  ,  |  .  |  P  |  Y  |---------------------------|  F  |  G  |  C  |  R  |  L  | BKSPC |
| TAB   |  A  |  O  |  E  |  U  |  I  |---------------------------|  D  |  H  |  T  |  N  |  S  | ENTER |
| SHIFT |  ;  |  Q  |  J  |  K  |  X  | ESC |---------------|CAPS |  B  |  M  |  W  |  V  |  Z  | SHIFT |
--------------|CTRL |-----| GUI | ALT | Sym |SHIFT|---| Nav |SPACE| ALT | GUI |-----|  /  |--------------

Colemak-DH
|  `    |  Q  |  W  |  F  |  P  |  B  |---------------------------|  J  |  L  |  U  |  Y  |  ;  | BKSPC |
| TAB   |  A  |  R  |  S  |  T  |  G  |---------------------------|  M  |  N  |  E  |  I  |  O  | ENTER |
| SHIFT |  Z  |  X  |  C  |  D  |  V  | ESC |---------------|CAPS |  K  |  H  |  ,  |  .  |  /  | SHIFT |
--------------|CTRL |-----| GUI | ALT | Sym |SHIFT|---| Nav |SPACE| ALT | GUI |-----|  '  |--------------
```
</details>

## Symbol and Media Layer

```
| HOME  |  !  |  @  |  #  |  $  |  %  |---------------------------|  ^  |  &  |  *  |  (  |  )  | DEL   |
| END   | GUI | ALT |CTRL |SHIFT| INS |---------------------------|  [  |  ]  |  -  |  =  |  \  | ENTER |
| SHIFT |     |VOL- |MUTE |VOL+ |PLAY |OSM ALT |------------|MENU |  {  |  }  |  _  |  +  |  |  | SHIFT |
--------------|CTRL |-----| GUI | ALT | *** |SHIFT|---| Adj |SPACE| ALT | GUI |-----|CTRL |--------------
```
Holding down the SYM key accesses the symbol layer:

- The symbols not present on the base layer are along the top row and right side, similar to a full-size keyboard.
- Duplicates of the modifier keys are along the left home keys. This allows a very comfortable combination of any set of modifiers plus a key on the right side of the board.
- Forward delete is on the upper right, taking backspace's place.
- The Windows OS application menu key is on the upper right thumb.
- The AltGr key affects the next key pressed so that it can combine with a key on any layer. It changes the meaning of the next key pressed after the AltGr key is pressed and released. For example, to do AltGr-h: press SYM, press and release AltGr, release SYM, press and release h.

## Navigation, Editing, Number and Function Layer

```
| CUT   |  1  |  2  |  3  |  4  |  5  |---------------------------|  6  |  7  |  8  |  9  |  0  | BSPC  |
| COPY  |LEFT |DOWN | UP  |RIGHT|PASTE|---------------------------|PG_UP|SHIFT|CTRL | ALT | GUI | PG_DN |
| SHIFT | F1  | F2  | F3  | F4  | F5  |UNDO |---------------|REDO | F6  | F7  | F8  | F9  | F10 | SHIFT |
--------------|CTRL |-----| GUI | ALT | Adj |SHIFT|---| *** |SPACE| ALT | GUI |-----|CTRL |--------------
```
Holding down the Nav/Edit key accesses the navigation, editing, number and function layer:

- Numbers are along the top row, and function keys are on the bottom row.
- The arrow keys on the left can be combined with the home row modifiers on the right to easily move around and select text, which can then be cut, copied and pasted.


## Adjust Layer
```
|       |QWERT|DVORK|COLMK|AG_SWAP|CTR_SWAP|----------------------|     | F11 | F12 |PR_SCR|    |       |
|       |     |     |     |AG_NORM|CTR_NORM|----------------------|MOD+ |BRI+ |HUE+ |SAT+ |     |       |
|       | GUI | ALT |CTRL |SHIFT|     |     |--------------|RGBTOG|MOD- |BRI- |HUE- |SAT- |     | BOOT  |
--------------|     |-----|     |     | *** |     |---| *** |     |     |     |-----|     |--------------
```
Simultaneously holding down the Sym and Nav/Edit keys enables keys to adjust keyboard settings:

- The base layer can be set to QWERTY, Colemak-DH or Dvorak, although the keyboard reverts to QWERTY each time it is plugged in.
- Alt/option and GUI/command can be swapped for mac users or restored to the windows norm.
- The backlight LEDs can be enabled, disabled, and controlled.
- BOOT allows loading new firmware, such as for keymap changes.
- The remaining Fn keys are here with modifiers to use with them.

## Make it Yours

If you are coming from a traditional keyboard,
  with a large set of physical keys,
  learning to use a column staggered (ergo) and layer-based keyboard,
  which uses layers instead of finger reaches to access numbers, symbols and functions,
  will be an adjustment for your muscle memory and your mental keyboard map.
This default layout tries to simplify that adjustment by keeping things in the expected spots when possible.

Yet this layout is only a decent compromise and is not optimal for each user.
The online [configurator](https://config.qmk.fm/#/hillside/48/LAYOUT) makes it easy to tweak this layout to your needs.
You can add additional layers or completely switch around what these do.

A good metaphor is to think of your keymap as a bonsai tree that you tweak slightly over time
  in response to ideas of how it might serve you better.
  
Some changes you might consider making:

- If you are on a mac, switch the editing keys from ctrl-x to cmd-x.
- Change the shift keys to one-shot shift keys,
  where pressing and releasing them shifts the next key pressed.
  That is much easier on your hands than holding them down.
  Yet, they can still be held as usual if desired.
- Instead of holding down the thumb key to keep the symbol layer active,
  you could use a one-shot layer key.
  One-shot modifiers are likely less stress on your hands and may even be faster.
  You would still be able to hold it down instead.

Here are some other keymaps for inspiration and ideas:

- The [Ferris default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ferris/keymaps/default) uses more advanced features as it has far fewer keys.
- The [Miryoku](https://github.com/manna-harbour/miryoku/tree/master/docs/reference) keymap ensures that all modifiers are comfortably available with each character key.
- The [Kyria default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/default) has different keymap choices and a couple more keys.



## Why no keymap.c

The online configurator provides a straightforward visual way
   to work with a simple layout and uses a .json keymap format.
So this default ```keymap.json``` was created with the online configurator.

If you wish, you can edit the ```keymap.json``` directly in a text editor,  compile it and flash it.

Or, you can use the graphical configurator to edit the keymap. To do that:

- Open the [QMK configurator](https://config.qmk.fm/#/hillside/48/LAYOUT)
- Using the green up arrow button, load the keymap from ```qmk_firmware/keyboards/hillside/48/keymaps/default/keymap.json```
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
 
As with anything downloaded from the internet, you should take some steps to assure yourself that the script will not harm your computer nor steal your data. The script is short, so reading it should at least convince you it is rearranging and printing the keymap provided, not reading your banking data.
See the [Hillside wiki](https://github.com/mmccoyd/hillside/wiki) for the script.
