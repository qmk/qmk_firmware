Copyright 2021 Alan Pocklington <ajp10304@gmail.com> @ajp10304

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

# AJP10304 Custom 40% Layout
# For the Planck, Shark, Quark, JJ40 and Atreus50

**Note:** In the tables below where there are two characters on a key,
the second is the output when shift is applied.

**Note:** The below tables assume a UK layout.

#### Flashing
Refer to the README.md of the keyboard you want to flash.

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

##### Main Colemak-DHm Layer

|      |      |      |     |       |      |       |       |       |      |      |      |
| ---- |:----:| :---:|:---:|:-----:|:----:|:-----:|:-----:|:-----:|:----:|:----:| ----:|
| Esc  |   Q  |   W  |  F  |   P   |  B   |   J   |   L   |   U   |  Y   |  ;:  | Bksp |
| Tab  |   A  |   R  |  S  |   T   |  G   |   M   |   N   |   E   |  I   |  O   | Enter|
| Shft |   Z  |   X  |  C  |   D   |  V   |   K   |   H   |  ,<   |  .>  |  /?  | Shft |
| Fn   | Ctrl | Alt  | GUI | Lower | Bksp | Space | Raise | Shift | MENU | Ctrl | Fn2  |

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

|       |      |      |      |      |      |      |      |      |      |      |         |
| :---: |:----:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:| :---:|:-------:|
| ????  | Reset|Qwerty|      |      | REC1 | REC2 |      |      |      |      |   Del   |
| CAPS  |      |      |      |      | PLAY1|PLAY2 | Mute | Vol+ | Play |      | Qwerty  |
| MAC   |      |      |      |      | STOP1|STOP2 | Prev | Vol- | Next |      | Colemak |
|       |      |      |      |      |      |      |      | DYN  |      |      |         |

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
| ESC   |      |      |      |      |      | W_L  | W_UP | BTN3 | W_DWN| W_R  |      |
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
