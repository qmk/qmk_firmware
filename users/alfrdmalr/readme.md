# alfrdmalr's userspace
## Overview 
The alphanumeric characters and symbols are spread between three main 'typing' layers: REGULAR, NUMPAD, and SYMBOL. 

A fourth layer, NAVIGATION, contains useful modifiers, shortcuts, and navigation functions like the arrow keys and page up/down. This layer also provides access to the `ENTER` and `ESC` keys.

Finally, a SETTINGS layer can be used to adjust certain keyboard-related options. 

A visual representation of each layer can be found in [alfrdmalr.h](./alfrdmalr.h)

### Layers

#### REGULAR
Right now this is just a QWERTY layer, but other layouts (DVORAK, COLEMAK, etc.) could easily be added. The REGULAR layer uses the default modifiers. 

The default modifiers are defined in the style `K00`, where the first digit is the row index and the second digit is the column index. These indices are based on the Preonic's 5x12 grid, and are **not** adjusted for a board of different size; for instance, the upper-leftmost key in the preonic layout is `K00`, whereas the upper-leftmost key on a Planck would be `K10`.

This convention is designed to work nicely with layout wrappers.

#### NUMPAD
The NUMPAD layer puts a numpad under the right hand, surrounding the home row position. Several basic arithmetic operators are also provided, as well as comma/decimal symbols, to emulate a traditional numpad. The numlock/capslock keys are accessible from this layer as well, though it should be noted that the actual keycodes being sent by the numpad are NOT the numpad versions of the numbers - this is to prevent the normal numlock behavior from blocking numbers from being sent.

This layer also holds the first twelve function keys.

#### SYMBOL
This layer holds all the symbols that are not accessible from the REGULAR layer. There is some redundancy (for instance, `/` exists in both the REGULAR and SYMBOL layer; its position, however, remains consistent) but with the exception of single and double quotes, all symbols are available from this layer.

#### NAVIGATION
Over time, this layer has become a general utility layer, though its primary function of is still to provide arrow keys under hjkl. The surrounding keys contain similar functionality - for instance, the keys directly below `DOWN` and `UP` are `PAGEDOWN` and `PAGEUP`, respectively. `HOME` and `END` are inverted from this convention, simply because I kept hitting the wrong key when trying to jump to the beginning/end of lines when editing text.

To the immediate right of the NAVIGATION layer key are the following modifiers: `SHIFT`, `CONTROL`, `ALT`, `GUI`. All modifiers are the "left" variants. The idea is to use the left hand to hold different modifiers as necessary while using the right hand to navigate and format.

`ESCAPE` is located on the spacebar from this layer, and `DELETE` is placed next to `BACKSPACE`, for convenience when formatting text. There are also four Windows shortcuts for undo, cut, copy, and paste, located in the same position as the relevant keys on the base layer (undo, for example, is in the same place as the `Z` key). Again, this is for convenience when formatting text.

#### SETTINGS
The SETTINGS layer can be accessed by pressing both SYMBOL layer keys at once. This is functionally the same as a trilayer, though because both keys are activating the same layer it doesn't actually use the trilayer feature.

This layer contains things like feature toggles, media controls, and other infrequently-used options. 

### Leader Key Sequences
A complete list of leader sequences can be found below. The LEAD key that begins each sequence has been omitted.


| Sequence  | Function                         |
| :------:  | -------------------------------- |
| R-E-S-E-T | Reset the keyboard into DFU mode |
