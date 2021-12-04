# Default Keymap

For ease of initial use,
  this keymap tries to follow many of the norms seen in non-programmable keyboards.
It is meant as a starting point that you will tweak over time to better suit _your_ preferences.
You can easily rearrange it in the online configurator or with the via firmware.

Features:
- A mostly normal base layer with shift, mods, delete in places expected from non-programmable keyboards.
- QWERTY, Colemak-DH and Dvorak options for the base layer layout.
- Modifiers on the home row of the non-base layers (Nav/Edit, Functions/Symbols, Numbers) to make key and modifier combinations comfortable.
- Edit keys and by word navigation in the Nav layer
- A number pad that is slightly optimized with the more frequently used numbers on the home row.

Features deliberately missing:
- Combos: as the online tools that may configuration changes easy do not handle them.
- Multi function mod-tap keys, auto shift capitalization, auto-exit modes like CAPWORD or NUMWORD: as they may be too large a step for someone new to programmable keyboards.

## Base Layer

```
| TAB   |  Q  |  W  |  E  |  R  |  T  |---------------------------|  Y  |  U  |  I  |  O  |  P  | BKSPC |
| CTRL  |  A  |  S  |  D  |  F  |  G  |---------------------------|  H  |  J  |  K  |  L  |  ;  |   '   |
| SHIFT |  Z  |  X  |  C  |  V  |  B  |  ~  |---------------| ESC |  N  |  M  |  ,  |  .  |  /  | SHIFT |
--------------|ENTER|-----| GUI | ALT | Num | Nav |---| Sym |SPACE| ALT | GUI |-----| APP |--------------
```

The base layer can be either QWERTY, Colemak-DH or Dvorak, with the non-alpha and non-symbol keys identical between them. QWERTY is the default.


A standard keyboard layout is used for:

- Tab, backspace, and shifts in the outer columns
- Alt/option and GUI/command on both thumbs, with the location swappable for windows or mac.

The differences from a standard layout are:

- Three additional "shift" keys access the navigation/editing, symbol/function, and  number layers.
- Enter is on the left thumb.
  This location allowed the more common right hand keys to be preserved.
  Feel free to adjust it or have it share the right shift key.
- Control is in the caps lock spot.
- Esc and `~ are above the thumbs.
- The rarer AltGr key is in a layer.

<details>
<summary>Details of Dvorak and Colemak-DH</summary>
In the Dvorak layout, the outer home row key is the "/?" symbols, so that the same 12 symbols can be skipped in the symbols layer.

```
Dvorak
| TAB   |  '  |  ,  |  .  |  P  |  Y  |---------------------------|  F  |  G  |  C  |  R  |  L  | BKSPC |
| CTRL  |  A  |  O  |  E  |  U  |  I  |---------------------------|  D  |  H  |  T  |  N  |  S  |  /    |
| SHIFT |  ;  |  Q  |  J  |  K  |  X  |  ~  |---------------| ESC |  B  |  M  |  W  |  V  |  Z  | SHIFT |
--------------|ENTER|-----| GUI | ALT | Num | Nav |---| Sym |SPACE| ALT | GUI |-----| APP |--------------

Colemak-DH
| TAB   |  Q  |  W  |  F  |  P  |  B  |---------------------------|  J  |  L  |  U  |  Y  |  ;  | BKSPC |
| CTRL  |  A  |  R  |  S  |  T  |  G  |---------------------------|  M  |  N  |  E  |  I  |  O  |   '   |
| SHIFT |  Z  |  X  |  C  |  D  |  V  |  ~  |---------------| ESC |  K  |  H  |  ,  |  .  |  /  | SHIFT |
--------------|ENTER|-----| GUI | ALT | Num | Nav |---| Sym |SPACE| ALT | GUI |-----| APP |--------------
```
</details>

## Navigation, Editing and Media Layer

```
| CAPS  | INS |     |     |     |VOL+ |---------------------------|PG_UP|HOME |     |  END|     | DEL   |
| CTRL  | GUI | ALT |CTRL |SHIFT|VOL- |---------------------------|PG_DN|LEFT | UP  |RIGHT|     | CTRL  |
| SHIFT |UNDO | CUT |COPY |PASTE|REDO |MUTE |---------------| ESC |     |WORDL|DOWN |WORDR|RALT | SHIFT |
--------------|ENTER|-----| GUI | ALT | Num | *** |---| Adj |BSPC | ALT | GUI |-----| APP |--------------
```
Holding down the Nav key accesses a navigation and editing layer:

- Navigation arrows are on and below the right home row in a cross pattern, For a column stagger keyboard this feels more natural than an inverted T. The keys below them move left or right by a word. Home, end, and page up/down are beside them.
- Modifiers in the left home row make it easier to use the arrows to select text with shift or move between desktops or tabs.
- Editing keys appear on the lower left.
  They, the modifiers and arrows make it easy to move text around without having to exit the layer.
- Delete is in the upper right, and a back space key is on the thumb.
- The base layer modifiers and escape are in the same spots as on the base layer, and a right control mirrors the left one.
- Media volume and play keys are on the left, accessible with one hand.
- AltGr and caps lock fill out the layer.
- A few keys do nothing and are available for more user specific needs.

## Symbol and Function Layer

```
| F12   |  !  |  @  |  #  |  $  |  %  |---------------------------|  ^  |  &  |  *  |  (  |  )  | BSPC  |
| CTRL  | F1  | F2  | F3  | F4  | F5  |---------------------------|  |  |SHIFT|CTRL | ALT | GUI | CTRL  |
| SHIFT | F6  | F7  | F8  | F9  | F10 | F11 |---------------| ESC |  \  |  [  |  ]  |  {  |  }  | SHIFT |
--------------|ENTER|-----| GUI | ALT | Num | Adj |---| *** |SPACE| ALT | GUI |-----| APP |--------------
```
Holding down the Sym key accesses symbol and function keys:

- The normal number row symbols are in the top row.
  If desired, these keys can be used for other things as the symbols are also accessible from the number pad layer with the shift key.
- The remaining symbols appear on the right.
- The function keys are on the left, aligned below the 1-5 numbers.
- A row of modifiers in the home row allow comfortable creation of any function key and modifier combination.  
- The base layer modifier and escape keys are still available, plus the extra right control key.

##  Number Pad and Algebraic Layer
```
|       |  -  |  +  |  =  |  /  |  *  |---------------------------|  .  |  7  |  8  |  9  |     | BSPC  |
| CTRL  | GUI | ALT |CTRL |SHIFT|     |---------------------------|  0  |  1  |  2  |  3  |  _  | CTRL  |
| SHIFT |     |     |     |     |     |     |---------------| ESC |  ,  |  4  |  5  |  6  |     | SHIFT |
--------------|ENTER|-----| GUI | ALT | *** |     |---|     |BSSP | ALT | GUI |-----| APP |--------------
```
Holding down the Num key accesses a number pad and arithmetic symbols:

- The number pad has the smallest numbers swapped into the home row as these are the most commonly used.
- A row of modifiers in the home row allow comfortable creation of any number and modifier combination.
- Symbols commonly used with numbers fill out the layer, and can be combined with the home row mods or the existing base layer modifiers on the right hand.
- Several keys remain unused and await more user specific needs.


## Adjust Layer
```
|       |QWERT|DVORK|COLMK|AG_SWAP|AG_NORM|-----------------------|     |     |     |     |     |       |
|       |     |     |     |     |     |---------------------------|MOD+ |BRI+ |HUE+ |SAT+ |     |       |
| RESET |     |     |     |     |     |     |--------------|RGBTOG|MOD- |BRI- |HUE- |SAT- |     |       |
--------------|     |-----|     |     |     | *** |---| *** |     |     |     |-----|     |--------------
```
Holding down the Nav and Sym keys simultaneously enables keys to adjust various keyboard settings:

- The base layer can be set to QWERTY, Colemak-DH or Dvorak, until the keyboard is powered off, when it reverts to QWERTY.
- Alt/option and GUI/command can be swapped for or mac users or restored to the windows norm. This setting does persist over power loss.
- The backlight LEDs can be enabled, disabled, and controlled. This setting also persists over power loss.


## Make it Yours

If you are coming from a more traditional keyboard with a full set of physical keys and a row staggered layout, the adjustment to a column staggered (ergo) layout and the use of layers instead of finger reaches to access numbers, symbols, and functions is an adjustment for your muscle memory and mental map of your keyboard. This layout tries to make that simpler by keeping things in the expected spot when possible.

Yet this layout is only a decent compromise, and not optimal for each user.

The online configurator makes it easy to fill in some of your most used key combinations into the navigation layer. You can add additional layers or completely switch around what these ones do.

Some changes you might consider making:
- If you are on a mac, switch the editing and word navigation keys from ctrl-x, to cmd-x.
- Change the shift keys to one-shot shift keys, where pressing and releasing them causes the next key pressed to be shifted. That is much easier on your hands than holding them down. Yet, they can still be held as normal if desired.
- Instead of holding down the thumb key to keep the symbol layer active, you could use a one shot layer key. This will likely be less stress on your hands and may even be faster. You can still hold it down instead.
- Instead of holding down the key for the number pad layer, you could make it a layer toggle, like caps lock is a capitalization toggle key.

Some other keymaps for inspiration and ideas can be seen here:
- [Ferris default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ferris/keymaps/default), which uses more advanced features as it has far fewer keys to work with.
- [Miryoku](https://github.com/manna-harbour/miryoku/tree/master/docs/reference), which is about ensuring all modifiers are comfortably available no matter what character key needs to be pressed.
- [Kyria default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/default).

A useful metaphor is to think of your keymap as a bonsai tree that you tweak slightly over time
  in response to ideas of how it might serve you better.


## Why no keymap.c

Via and the online configurator both provide very easy visual ways to work with a simple layout.
This is easiest if the keymap is maintained in the json format they use.
This default ```keymap.json``` was created with the online configurator and formated for easier reading.

If you wish, you can edit it direcly in a text editor and use the below script to restore the spacing.

Or, you can edit the keymap with the graphical online tool. To do that:

- Open the [QMK configurator](https://config.qmk.fm/#/handwired/hillside/LAYOUT)
- Using the green up arrow button load the keymap from ```qmk_firmware/keyboards/handwired/hillside/keymaps/default/keymap.json```
- Make the changes you wish to the layout
- Save the keymap using the green down arrow button.
- Copy those changes back into your QMK repository and reformat for easy reading using the format script:
```
./keyboards/handwired/hillside/keymaps/json2hill.py --input <Your download directory>/default.json > ./keyboards/handwired/hillside/keymaps/default/keymap.json
```
   You may need to make that script executable with ```chmod +x```. After your keymap is safely copied and formated, you may want to remove the keymap from your download directory so later downloads can recieve the same name.


After either method of editing, compile and flash the keymap as normal.

With a bit more complexity, you can combine a json keymap with more advanced features specified in C files.
See for example
[pierrec83's Kyria map](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/pierrec83)
