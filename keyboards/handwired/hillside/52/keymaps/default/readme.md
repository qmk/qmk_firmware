# Hillside56 Default Keymap

This default keymap follows many of the norms seen in non-programmable keyboards to ease initial use of the Hillside keyboard. It is a starting point for you to tweak over time to better suit your preferences. You can easily customize it with the QMK configurator.

Some of its key features are:

- A mostly standard base layer with most keys in the expected places.
- An inverted-T arrow cluster on the base layer.
- Numbers and symbols along the top row of their layers, for familiarity.
- Comfortable modifier and function or symbol combinations on the non-base layers using modifiers on the home row of the symbol and number/function layers.
- QWERTY, Colemak-DH and Dvorak base layer options.

Some features are deliberately omitted:

- Combos: because the online configuration tool does not handle them and because they would add to the initial learning curve, as helpful to a keymap as a light sprinkling of combos can be.
- Multi-function mod-tap keys, auto shift capitalization and auto-exit modes such as CAPWORD or NUMWORD: as they may be too large a step for someone new to programmable keyboards.

## Base Layer

The base layer provides a very standard key layout with four differences:
- Numbers, functions and most symbols are accessed with number and symbol shift keys.
- Escape and caps lock are on the thumbs.
- Page up/down, home and end are in a left navigation T cluster.
- Forward delete is on the symbol layer.

The default layout is QWERTY with alternatives of Dvorak and Colemak-DH and the alt/option and win/command key locations are swappable for windows or mac.

Details of Dvorak and Coleman-DH
In the Dvorak layout, the outer home row key is the "/?" symbols so that the same 12 symbols are taken care of on the base layer. 

## Symbol Layer
Holding down the SYM key accesses the symbol layer:

- The symbols not present on the base layer are along the top row and right side similar to a full-size keyboard.

- Duplicates of the modifier keys are along the left home keys. This allows very comfortable combination of any set of modifiers plus a key on the right side of the board.

- The Window OS application menu key is above the right thumb. 

- So that the AltGr key can combine with a key on any layer, it changes the meaning of the next key pressed after the AltGr key is pressed and released. For example, to do AltGr-h: press SYM, press and release AltGr, release SYM, press and release h.


## Number, Function, Media Layer
Holding down the Num key accesses the number, function and media layer:

- Numbers are along the top row, with the shifted symbol values of all the number keys are also available.
- Function keys are on the left with duplicate modifier keys on the right home row.
- Media keys are on the right.


## Keyboard Adjust Layer

Simultaneously holding down the Sym and Num keys enables keys to adjust keyboard settings:

- The base layer can be set to QWERTY, Colemak-DH or Dvorak, but the keyboard reverts to QWERTY each time it is plugged in.
- Alt/option and GUI/command can be swapped for mac users or restored to the windows norm. This setting persists over power loss.
- The backlight LEDs can be enabled, disabled, and controlled. These settings also persist over power loss.
- Reset allows loading new firmware, such as for keymap changes.

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

A good metaphor is to think of your keymap as a bonsai tree that you tweak slightly over time
  in response to ideas of how it might serve you better.

Some changes you might consider making:
- Use the upper thumb key for shift.
  This will likely be for comfortable than reaching with your pinky.
- Put some of your most-used key combinations on the unused keys
  on the symbol layer.
- Change the shift keys to one-shot shift keys,
  where pressing and releasing them shifts the next key pressed.
  That is much easier on your hands than holding them down.
  Yet they can still be held as usual if desired.
- Instead of holding down the thumb key to keep the symbol layer active,
  you could use a one-shot layer key.
  One-shot modifiers are likely less stress on your hands and may even be faster.
  You would still be able to hold it down instead.
- Instead of holding down the key for the number layer,
  you could make it a layer toggle,
  like caps lock is a capitalization toggle key.

Here are some other keymaps for inspiration and ideas:
- The [Ferris default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ferris/keymaps/default) uses more advanced features as it has far fewer keys to work with.
- The [Miryoku](https://github.com/manna-harbour/miryoku/tree/master/docs/reference) keymap ensures that all modifiers are comfortably available with each character key.
- The [Kyria default](https://github.com/qmk/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/default) has different keymap choices.
