# Default Keymap

This default keymap follows many of the norms seen in non-programmable keyboards
  to ease initial use of the Hillside keyboard.
It is a starting point for you to tweak over time to better suit _your_ preferences.
You can easily customize it with the
  [QMK configurator](https://config.qmk.fm/#/hillside/0_1/LAYOUT)
  or with the [via firmware](https://caniusevia.com).

Some of its key features are:
- A mostly standard base layer with letters, some symbols, shift, modifier and delete keys
  in the expected places for non-programmable keyboards.
- QWERTY, Colemak-DH and Dvorak options for the letter and symbol layout.
- Comfortable modifier and function or symbol combinations on the non-base layers
  using modifiers on the home row of the navigation/edit, symbol/function and number-pad layers.
- Word navigation and cut/copy/paste keys on the navigation layer.
- A slightly optimized number pad with the more frequently used numbers on the home row.

We've deliberately omitted some features:
- Combos: because the online configuration tools do not handle them
  and because they would add to the initial learning curve,
  as helpful to a keymap as a light sprinkling of combos can be.
- Multi-function mod-tap keys, auto shift capitalization and auto-exit modes such as CAPWORD or NUMWORD:
  as they may be too large a step for someone new to programmable keyboards.

## Base Layer

```
| TAB   |  Q  |  W  |  E  |  R  |  T  |---------------------------|  Y  |  U  |  I  |  O  |  P  | BKSPC |
| CAPS  |  A  |  S  |  D  |  F  |  G  |---------------------------|  H  |  J  |  K  |  L  |  ;  | ENTER |
| SHIFT |  Z  |  X  |  C  |  V  |  B  |  ~  |---------------| ESC |  N  |  M  |  ,  |  .  |  /  | SHIFT |
--------------|CTRL |-----| GUI | ALT | Num | Nav |---| Sym |SPACE| ALT | GUI |-----|  '  |--------------
```

The base layer provides a very standard key layout:

- Return, Tab, backspace and shift keys in the outer columns.
- Alt/option and win/command keys on both thumbs, with the location swappable for windows or mac.
- A space key on the right thumb.

The differences from a standard layout are:

- There are three additional "shift" keys
  to access the navigation/editing, symbol/function, and number layers.
- Esc and `~ are above the thumbs.
- The Menu and AltGr keys are on a layer.

The default layout is QWERTY with alternatives of Dvorak and Colemak-DH
and the alt/option and win/command key locations are swappable for windows or mac.

<details>
<summary>Details of Dvorak and Colemak-DH</summary>
The Dvorak and Colemak-DH base layers
  have identical non-alpha and non-symbol keys as the QWERTY base layer.
In the Dvorak layout, the symbol key in the bottom row is the "/?" symbols
  so that the same 12 symbols are taken care of on the base layer.

```
Dvorak
| TAB   |  '  |  ,  |  .  |  P  |  Y  |---------------------------|  F  |  G  |  C  |  R  |  L  | BKSPC |
| CAPS  |  A  |  O  |  E  |  U  |  I  |---------------------------|  D  |  H  |  T  |  N  |  S  | ENTER |
| SHIFT |  ;  |  Q  |  J  |  K  |  X  |  ~  |---------------| ESC |  B  |  M  |  W  |  V  |  Z  | SHIFT |
--------------|CTRL |-----| GUI | ALT | Num | Nav |---| Sym |SPACE| ALT | GUI |-----|  /  |--------------

Colemak-DH
| TAB   |  Q  |  W  |  F  |  P  |  B  |---------------------------|  J  |  L  |  U  |  Y  |  ;  | BKSPC |
| CAPS  |  A  |  R  |  S  |  T  |  G  |---------------------------|  M  |  N  |  E  |  I  |  O  | ENTER |
| SHIFT |  Z  |  X  |  C  |  D  |  V  |  ~  |---------------| ESC |  K  |  H  |  ,  |  .  |  /  | SHIFT |
--------------|CTRL |-----| GUI | ALT | Num | Nav |---| Sym |SPACE| ALT | GUI |-----|  '  |--------------
```
</details>

## Navigation, Editing and Media Layer

```
|       | INS |     |     |     |VOL+ |---------------------------|PG_UP|HOME |     |  END|     | DEL   |
|       | GUI | ALT |CTRL |SHIFT|VOL- |---------------------------|PG_DN|LEFT | UP  |RIGHT|     | ENTER |
| SHIFT |UNDO | CUT |COPY |PASTE|REDO |MUTE |---------------| ESC |RALT |WORDL|DOWN |WORDR|MENU | SHIFT |
--------------|CTRL |-----| GUI | ALT | Num | *** |---| Adj |BSPC | ALT | GUI |-----|CTRL |--------------
```
Holding down the Nav key accesses a navigation and editing layer:

- Navigation arrows are on and below the right home row in a cross pattern.
  This feels more natural for a column stagger keyboard than an inverted T.
  The keys below that move left or right by a word.
  Home, end, and page up/down are beside them.
- Modifiers in the left home row make it easier to use the arrows
  to select text with the shift key or move between desktops or tabs.
- Editing keys appear on the lower left.
  The edit keys, modifiers and arrows make it easy to move text around without leaving the layer.
- Delete is in the upper right, and a backspace key is on the thumb.
- The base layer modifiers and escape are in the same spots as on the base layer,
  and a right-hand control key is added.
- Media volume and play keys are on the left, accessible with one hand.
- Menu and AltGr keys fill out the layer.
- A few keys do nothing and are available for more user-specific needs.

## Symbol and Function Layer

```
| F11   |  !  |  @  |  #  |  $  |  %  |---------------------------|  ^  |  &  |  *  |  (  |  )  | BSPC  |
| F12   | F1  | F2  | F3  | F4  | F5  |---------------------------|  |  |SHIFT|CTRL | ALT | GUI | ENTER |
| SHIFT | F6  | F7  | F8  | F9  | F10 |PRTSC|---------------| ESC |  \  |  [  |  ]  |  {  |  }  | SHIFT |
--------------|CTRL |-----| GUI | ALT | Num | Adj |---| *** |SPACE| ALT | GUI |-----|CTRL |--------------
```
Holding down the Sym key accesses a layer of symbol and function keys:

- The symbols usually found on the number keys are in the top row.
  If desired, you can use these positions for other things,
  as the symbols are also accessible from the number pad layer with the shift key.
- Several more symbols appear on the right.
- The function keys are on the left, beginning with two rows of five.
- A row of modifiers in the home row allows the comfortable creation of any modifier and function key combination.  
- The base layer modifier and escape keys are still available, as is a right-hand control key.

##  Number Pad and Algebraic Layer
```
| TAB   |  -  |  +  |  =  |  /  |  *  |---------------------------|  .  |  7  |  8  |  9  |     | BSPC  |
|       | GUI | ALT |CTRL |SHIFT|     |---------------------------|  0  |  1  |  2  |  3  |  _  | ENTER |
| SHIFT |     |     |     |     |     |     |---------------| ESC |  ,  |  4  |  5  |  6  |     | SHIFT |
--------------|CTRL |-----| GUI | ALT | *** |     |---|     |BSPC | ALT | GUI |-----|CTRL |--------------
```
Holding down the Num key accesses a number pad and arithmetic symbols:

- The number pad has the lowest numbers swapped into the home row as these are the most commonly used.
- A row of modifiers in the home row allows the comfortable creation of any modifier and number combination.
- Symbols commonly used with numbers fill out the layer
   and can be combined with the home row mods or the existing base layer modifiers on the right hand.
- Several keys remain unused and await more user-specific needs.


## Adjust Layer
```
|       |QWERT|DVORK|COLMK|AG_SWAP|AG_NORM|-----------------------|     |     |     |     |     |       |
|       |     |     |     |CTR_S|CTR_N|---------------------------|MOD+ |BRI+ |HUE+ |SAT+ |     |       |
| RESET |     |     |     |     |     |     |--------------|RGBTOG|MOD- |BRI- |HUE- |SAT- |     |       |
--------------|     |-----|     |     |     | *** |---| *** |     |     |     |-----|     |--------------
```
Simultaneously holding down the Nav and Sym keys enables keys to adjust various keyboard settings:

- The base layer can be set to QWERTY, Colemak-DH or Dvorak,
  but the keyboard reverts to QWERTY each time it is plugged in.
- Alt/option and GUI/command can be swapped for mac users or restored to the windows norm.
  This setting persists over power loss.
- The backlight LEDs can be enabled, disabled, and controlled.
  These settings also persist over power loss.


## Make it Yours

If you are coming from a traditional keyboard,
  with a row-staggered layout and a large set of physical keys,
  learning to use a column staggered (ergo) and layer-based keyboard,
  which uses layers instead of finger reaches to access numbers, symbols and functions,
  will be an adjustment for your muscle memory and your mental keyboard map.
This default layout tries to simplify that adjustment by keeping things    in the expected spots when possible.

Yet this layout is only a decent compromise and is not optimal for each user.

The online configurator makes it easy to tweak this layout to your needs.
You can add additional layers or completely switch around what these do.

Some changes you might consider making:
- Put some of your most-used key combinations on the unused keys on the navigation layer.
- If you are on a mac, switch the editing and word navigation keys from ctrl-x to cmd-x.
- Change the shift keys to one-shot shift keys,
  where pressing and releasing them shifts the next key pressed.
  That is much easier on your hands than holding them down.
  Yet, they can still be held as usual if desired.
- Instead of holding down the thumb key to keep the symbol layer active,
  you could use a one-shot layer key.
  One-shot modifiers are likely less stress on your hands and may even be faster.
  You would still be able to hold it down instead.
- Instead of holding down the key for the number pad layer,
  you could make it a layer toggle, like caps lock is a capitalization toggle key.

Here are some other keymaps for inspiration and ideas:
- The [Ferris default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ferris/keymaps/default) uses more advanced features as it has far fewer keys to work with.
- The [Miryoku](https://github.com/manna-harbour/miryoku/tree/master/docs/reference) keymap ensures that all modifiers are comfortably available with each character key.
- The [Kyria default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/default) has different keymap choices and a couple more keys.

A good metaphor is to think of your keymap as a bonsai tree that you tweak slightly over time
  in response to ideas of how it might serve you better.


## Why no keymap.c

Via and the online configurator provide straightforward visual ways to work with a simple layout,
  and both use a .json keymap format.
So this default ```keymap.json``` was created with the online configurator
  and formatted for easier reading and editing.

If you wish, you can edit the ```keymap.json``` directly in a text editor, optionally use the below ```json2hill.py``` to restore the spacing, and then compile and flash it.

Or, you can use the graphical configurator to edit the keymap. To do that:

- Open the [QMK configurator](https://config.qmk.fm/#/handwired/hillside/LAYOUT)
- Using the green up arrow button, load the keymap from ```qmk_firmware/keyboards/handwired/hillside/keymaps/default/keymap.json```
- Make the changes you wish to the layout
- Save the keymap using the green down arrow button.
- Copy those changes back into your QMK repository and reformat for easy reading using the format script:
```
./keyboards/handwired/hillside/0_1/keymaps/json2hill.py --input <Your download directory>/default.json > ./keyboards/handwired/hillside/0_1/keymaps/default/keymap.json
```
   You may need to make that script executable with ```chmod +x```. After your keymap is safely copied and formated, you may want to remove the keymap from your download directory so later downloads will automatically receive the same file name.

After either method of editing, compile and flash the keymap as usual.

You can combine a .json based keymap with more advanced features specified in .c files
  with a bit more complexity.
For example, see
[pierrec83's Kyria map](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/pierrec83).
