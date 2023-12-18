# laurentlaurent's Preonic keyboard
Largely similar to his [ErgoDox EZ](https://configure.ergodox-ez.com/ergodox-ez/layouts/jZpmo/latest/0)'s layout

## Features

### Special Modifiers for Global Shortcuts
* Hyper key (Ctrl+Alt+Cmd+Shift)
* CAG key (Ctrl+Alt+Cmd)
* Meh key (Ctrl+Alt+Shift)

### Home Row modifiers
* Home Row modifiers (hold F/J to use CMD/Ctrl, D/L for Alt, ... )
* Separate layers for Mac and Windows keyboard to improve muscle memory linked to Home Row modifiers (CMD is mapped to F and J on Mac, CTRL for Windows)
* Extra CMD/CTRL key mapped to Z for one-handed CMD+F/CTRL+F

### Qwerty Layout improvements
* Backspace and Enter are on bottom row (next to Space bar)
* = is where Esc would be expected to be
* "-" is where Backspace would be expected to be
* Grave is where LCTRL would be expected to be
* Esc is where Alt (on Mac)/Win (on PC) would be expected to be
* Del is where CMD (on Mac)/Alt (on PC) would be expected to be
* Hyper key replaces Caps Lock

### Mod taps
* Home Row modifiers
* Lower and Raise are Backspace on tap
* Holding = is CAG (CTRL+ALT+CMD)
* Holding Esc is MEH (Ctrl+Shift+Alt)
* Right Shift is bound to RShift on hold, Backspace on tap
* Spacebar acts like a LShift on hold, Spacebar on tap
* In instances where repeated keys is needed:
    * Tap then tap-hold repeats the key
    * Lower, Raise (and most other layers) turns off mod-tap on most keys
* Music layer disables all key mappings, Gaming layer disables modtaps

### Layer Switching
* Layer switcher key, used to switch layout (allows use of _NAV, _NUM layout without holding their layer keys)
* **Punctuation layer** accessible by holding Tab, Backslash or Backspace
* Grave switches to **One-Handed layer** on hold
* **Mouse and arrow key layer** accessible by holding ; or A
* Del switches to **Numpad** on hold
* Enter switches to **Extra layer** on hold
    * Extra layer will be used for applications shortcuts

## Layers

### Mac Qwerty
```
,-----------------------------------------------------------------------------------.
| CAG/=|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| LY|TB|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | LY|\ |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Hyper| LY|A | CT/S | AT/D | WN/F |   G  |   H  | WN/J | AT/K | CT/L | LY|; |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift| WN/Z |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Sh/Bk|
|------+------+------+------+------+------+------+------+------+------+------+------|
| LY|` |MH/ESC| LY|DL|LW|Bkp|LY|Bkp| Shift/Space |LY|ENT|RS|Bkp|   [  |   ]  |LY_SW |
`-----------------------------------------------------------------------------------'
```
* Hold Tab (LY|TB), Backspace (LY|Bkp) or Backslash (LY|\ ) for **Punctuation Layer**
* Hold Grave (LY|`) for **One-Handed Layer**
* Hold Del (LY|DL) for **Numpad Layer**
* Hold A or ; for **Navigation/Mouse Layer**
* Hold Enter (LY|ENT) for **Extra layer**

### Win Qwerty
```
,-----------------------------------------------------------------------------------.
| CAG= |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| LY|TB|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | LY|\ |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Hyper| LY|A | WN/S | AT/D | CT/F |   G  |   H  | CT/J | AT/K | WN/L | LY/; |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift| CT/Z |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Sh/Bk|
|------+------+------+------+------+------+------+------+------+------+------+------|
| LY|` |ESCMEH| LY|DL|LW|Bkp|LY|Bk |    Space    |LY|ENT|RS|Bkp|   [  |   ]  |LY_SW |
`-----------------------------------------------------------------------------------'
```
* Hold Tab (LY|TB), Backspace (LY|Bkp) or Backslash (LY|\ ) for **Punctuation Layer**
* Hold Grave (LY|`) for **One-Handed Layer**
* Hold Del (LY|DL) for **Numpad Layer**
* Hold A or ; for **Navigation/Mouse Layer**
* Hold Enter (LY|ENT) for **Extra layer**

### Gaming Qwerty
```
,-----------------------------------------------------------------------------------.
|   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | LY|; |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  =   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Ctrl | ESC  |  Alt |LW|Bkp|LY|Bk |    Space    |LY|ENT|RS|Bkp|   [  |   ]  |LY_SW |
`-----------------------------------------------------------------------------------'
```

### Music Layer
```
,-----------------------------------------------------------------------------------.
| Esc  | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+------+------+------+------+------+------+------|
| XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+------+------+------+------+------+------+------|
| CTRL | ALT  | CMD  |      | XXXX |    Space    | XXXX |      | XXXX | XXXX |LY_SW |
`-----------------------------------------------------------------------------------'
```

### Lower Layer
```
,-----------------------------------------------------------------------------------.
| ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Tab  | Home |  Up  | End  | PGUP | XXXX | XXXX | XXXX | PrSc | Home | PGUP | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|  "   | Left | Down | Right|PGDWN | XXXX | XXXX | XXXX | Pause| End  |PGDWN | F12  |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      | CTRL |  Alt |  CMD | XXXX | XXXX | XXXX | XXXX | Prev | Play | Next | INS  |
|------+------+------+------+------+------+------+------+------+------+------+------|
| CTRL |  Alt |  CMD | !!!! | Bksp |    Space    | Enter|      | Vol- | Vol+ |LY_SW |
`-----------------------------------------------------------------------------------'
```

### Raise Layer
```
,-----------------------------------------------------------------------------------.
| ESC  |  F1  |  F2  |  F3  |  F4  |  F5  | SCLK |   &  |   *  |   (  |   )  | Bksp |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Tab  |  F7  |  F8  |  F9  |  F10 |  F11 | XXXX |   &  |   *  |   {  |   }  | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Caps |  F1  |  F2  |  F3  |  F4  |  F5  | XXXX |   -  |   =  |   [  |   ]  | XXXX |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |  F7  |  F8  |  F9  |  F10 |  F11 | XXXX |ISO # |ISO \ | MRC1 | MRC2 | MRSP |
|------+------+------+------+------+------+------+------+------+------+------+------|
| CTRL |  Alt |  CMD |      | Bksp |    Space    | Enter| !!!! | MPL1 | MPL2 |LY_SW |
`-----------------------------------------------------------------------------------'
```

### Adjust Layer
```
,-----------------------------------------------------------------------------------.
|      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Tab  | Reset|      |      |      |      |      |      |      |      |      | XXXX |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |      |      |Aud on|AudOff|QWmac |QWwin |QWmac |QWin  |      |      |  F12 |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |      |      |      |      |LY_SW |
`-----------------------------------------------------------------------------------'
```

### Punctuation Layer
```
,-----------------------------------------------------------------------------------.
|  +   |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |   )  |  _   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| !!!! |  &   |  |   |  {   |   }  |  -   |  -   | XXXX | XXXX |  {   |   }  |  |(!)|
|------+------+------+------+------+-------------+------+------+------+------+------|
|  "   |  /   |  *   |  (   |   )  |  +   |  +   | XXXX | XXXX |  [   |   ]  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |  \   |  %   |  [   |   ]  |  =   |  =   | XXXX |   <  |  >   |   ?  | INS  |
|------+------+------+------+------+------+------+------+------+------+------+------|
|  ~   |  _   |  ^   | Del  | !!!! |    Space    | Enter| XXXX |  [   |   ]  |LY_SW |
`-----------------------------------------------------------------------------------'
```

### Extra Layer
```
,-----------------------------------------------------------------------------------.
|  ESC |      |      |      |      |      | SCLK |      |      |      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|  Tab |      |      |      |      |      |      |      |      |      |      | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Caps |      |      |      |      |      |      |      |      |      |      |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |      | MRC1 | MRC2 | MRSP |
|------+------+------+------+------+------+------+------+------+------+------+------|
| CTRL |  ALT |  CMD | Del  | Bksp |    Space    | !!!! |      | MPL1 | MPL2 |LY_SW |
`-----------------------------------------------------------------------------------'
```

### Numeric Pad Layer
```
,-----------------------------------------------------------------------------------.
|  ESC | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | NMLK | NUM/ | NUM* | NUM- | XXXX |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      | Home |  Up  | End  | PGUP | XXXX | XXXX | NUM7 | NUM8 | NUM9 | NUM+ | XXXX |
|------+------+------+------+------+-------------+------+------+------+------+------|
| XXXX | Left | Down | Right| PGDWN| XXXX | XXXX | NUM4 | NUM5 | NUM6 | NUM+ | XXXX |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      | CTRL |  ALT | CMD  | XXXX | XXXX | XXXX | NUM1 | NUM2 | NUM3 | NENT | Bksp |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      | XXXX | !!!! | XXXX | Bksp |    Space    | NUM0 | NUM0 | NUM. | NENT | QMAC |
`-----------------------------------------------------------------------------------'
```

### Navigation Layer
```
,-----------------------------------------------------------------------------------.
|  ESC |      |      | MOB3 |      |      |      |      |      |      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |   A  | MOB2 | MOUP | MOB1 | MOSU | PGUP | Home |  Up  | End  |      | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      | !!!! | MOLF | MODN | MORT | MOSD | PGDN | Left | Down | Right| !!!! |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      | MOB4 | MOB5 | MOSL | MOSR | MOA2 | MOA0 | MPRV | MPLY | MNXT |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
| CTRL | ALT  | CMD  |      | Bksp |    Space    | Enter| VILM | VOLD | VOLU | QMAC |
`-----------------------------------------------------------------------------------'
```

### One-Handed Layer
```
,-----------------------------------------------------------------------------------.
| Esc  |  6   |   7  |   8  |   9  |   0  |   -  | XXXX | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |   Y  |   U  |   I  |   O  |   P  | MWL3 | MWFS | MWR3 | MWTL | MWTR | XXXX |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |   H  |   J  |   K  |   L  |   :  | MWL1 | MWM1 | MWR1 | MWBL | MWBR | XXXX |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |   N  |   M  |   ,  |   .  |   /  | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+------+------+------+------+------+------+------|
| !!!! |  Esc |  Del |  Ent | Bksp |             | MWLT | MWBT | MWUP | MWRT |LY_SW |
`-----------------------------------------------------------------------------------'
```
The right hand side of the keyboard contains shortcuts for moving windows on Mac (using Magnet)

### Layer Switcher
```
,-----------------------------------------------------------------------------------.
| Esc  | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+------+------+------+------+------+------+------|
|Brite | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+-------------+------+------+------+------+------|
| XXXX | XXXX | XXXX | XXXX | XXXX | GAME | XXXX | XXXX | XXXX | XXXX | NAV  | XXXX |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      | XXXX | XXXX | XXXX | XXXX | QMAC | XXXX | MUSC | XXXX | XXXX | XXXX | XXXX |
|------+------+------+------+------+------+------+------+------+------+------+------|
| XXXX | XXXX | NUM  | XXXX | XXXX |    XXXXX    | XXXX | XXXX | XXXX | XXXX | !!!! |
`-----------------------------------------------------------------------------------'
```
