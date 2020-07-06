# AJP10304 Custom JJ40 Layout
# Also available for the Planck, Shark and Atreus50

**Note:** In the tables below where there are two characters on a key,
the second is the output when shift is applied.

**Note:** The below tables assume a UK layout.

#### Flashing
Use sleep to get a chance to get into boot mode.

`make jj40:ajp10304:flash`

##### Main Qwerty Layer

* Tab: when held, operates as shift.
* Enter: when held, operates as shift.
* MENU: perform right-click

|      |      |      |      |      |      |      |      |      |      |      |      |
| ---- |:----:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| ----:|
| Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
| Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  | Enter|
| Shft |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  | Shft |
| Fn   | Ctrl | Alt  | GUI  |Lower | Bksp |Space |Raise | Shift| MENU | Ctrl | Fn2  |

##### Function Layer
Activated when `fn` held in the above `qwerty` layer.

|       |      |      |      |      |      |      |      |      |      |      |      |
| :---: |:----:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
|  F1   |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
|  1!   |  2"  |  3£  |  4$  |  5%  |  6^  |  7&  |  8*  |  9(  |  0)  |  ~   |INSERT|
| Shift |  \|  |  `¬  |  #~  |   *  |  -_  |  =+  |  \|  |  [{  |  ]}  |  '@  |Shift |
| Fn    | Ctrl | Alt  | GUI  |Lower | Bksp |Space |Mouse | MENU | Alt  | Ctrl | Fn2  |

##### Lower Layer
Activated when `Lower` is held in the above `qwerty` layer.

* Numbers are along the top row, their shifted counterparts are on row 2.
* WrdBks: `backspace` with `ctrl` applied. I.e. delete a word.
* WrdDel: `delete` with `ctrl` applied. I.e. forward delete a word.

|       |      |      |      |      |      |      |      |      |      |      |      |
| :---: |:----:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
|  1!   |  2"  |  3£  |  4$  |  5%  |  6^  |  7&  |  8*  |  9(  |  0)  | DEL  | Bksp |
|  !    |   "  |   £  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |WrdDel|WrdBks|
| Shift |  \|  |  `¬  |  #~  |  '@  |  -_  |  =+  |  #~  |  [{  |  ]}  |  '@  |Shift |
|       |      |      |      |Lower | Del  |Space |      | Next | Vol- | Vol+ | Play |

##### Raise Layer
Activated when `Raise` is held in the above `qwerty` layer.

* Preferred layer for typing brackets.
* Allows for cursor navigation to be used solely with the right hand.
* WRDSEL: Select the word where the cursor is.
* |< and >|: Apply `ctrl` to `left` and `right` respectively for word jumping.

|       |      |      |      |      |      |       |      |      |      |       |      |
| :---: |:----:| :---:| :---:| :---:| :---:| :---: | :---:| :---:| :---:| :---: | :---:|
|   `   |      |WRDSEL|  [   |   ]  |      |       | PGUP | HOME |PGDOWN|       |PRNTSC|
|   `   |      |      |  (   |   )  |      |       | HOME |  UP  | END  |       |ZOOM +|
|       |      |      |  {   |   }  |      |&#124;<| LEFT | DOWN |RIGHT |>&#124;|ZOOM -|
| Mouse |      |      |      |      |  Alt | Enter |Raise |      |      |       |      |

##### Lower + Raise
Activated when `Lower` and `Raise` are held together in the above `qwerty` layer.

* Audio controls in the same position as cursor keys from the `Raise` layer.
* ????: Runs a macro for outputting a text string.  Do not use this store passwords.
* Reset: Enter bootloader for flashing firmware to the keyboard.
* CAPS: Toggle caps lock.
* Macro functions: Allows recording of macros.  To start recording the macro, press either REC1 or REC2. 
To finish the recording, press STOP. To replay the macro, press either PLAY1 or PLAY2.
* MAC: Toggle MAC OS extensions to layers. This allows MLWR to be enabled with LOWER,
MRSE with RAISE, MFNC with FUNC and MFNC2 with FUNC2 respectively.

|       |      |      |      |      |      |      |      |      |      |      |      |
| :---: |:----:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
| ????  | Reset|Qwerty|      |      | REC1 | REC2 |      |      |      |      |  Del |
| CAPS  |      |      |      |      | PLAY1|PLAY2 | Mute | Vol+ | Play |      |      |
| MAC   |      |      |      |      | STOP1|STOP2 | Prev | Vol- | Next |      |      |
|       |      |      |      |      |      |      |      | DYN  |      |      |      |

##### Function 2 Layer
Activated when `fn` held in the above `qwerty` layer.
* WRDSEL: Select the word where the cursor is.
* LNDEL: Delete the line where the cursor is.
* LNSEL: Select the line where the cursor is.
* DUP: Duplicate the selected text.
* LNJOIN: Join the line where the cursor is with the following line.
* MODE: Print either `PC` or `OSX` depending on what layer mode is active.

|       |      |      |      |      |      |      |      |      |      |      |      |
| :---: | :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
|       |      |WRDSEL|      |      |      | LNDEL|      |      |      |      |      |
|       |      | LNSEL| DUP  |      |      |      |      |LNJOIN|      |      |      |
|       | UNDO | CUT  | COPY | PASTE|      |      |      |      |      |      | MODE |
|       |      |      |      |      |      |      |      |      |      |      |      |

##### Mouse Layer
Activated when `fn` and `raise` held together.

|       |      |      |      |      |      |      |      |      |      |      |      |
| :---: | :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
| ESC   |      |      |      |      |      |      |      | BTN3 |      |      |      |
| ACC0  | ACC1 | ACC2 |      |      |      |      | BTN1 |  UP  | BTN2 |      |      |
| ACC0  | ACC1 | ACC2 |      |      |      |      | LEFT | DOWN | RIGHT|      |      |
|       |      |      |      |      |      |      |      |      |      |      |      |

##### Number Pad Layout
Activated when holding `Esc` key.

|       |      |      |      |      |      |      |      |      |      |      |      |
| :---: | :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|
|       |      |      |      |      |      |NMLOCK|   7  |   8  |   9  |   /  |      |
|       |      |      |      |      |      |      |   4  |   5  |   6  |   *  |      |
|       |      |      |      |      |      |      |   1  |   2  |   3  |   +  |      |
|       |      |      |      |      |      |      |   0  |   .  |   ,  |   -  |      |
