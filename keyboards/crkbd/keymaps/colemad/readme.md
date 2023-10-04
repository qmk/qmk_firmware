# **COLEMAD**

Compiled and tested: `July 12, 2023`

## Corne Keyboard (CRKBD) **Colemak** layout by [ACortesDev](https://github.com/ACortesDev)

1. **Ergonomic navigation keys**.
2. **Symbols where expected to be**.
3. **Numbers (numpad)**.
   Using the Telephone/ATM numpad layout. Easier to memorize/visualize as numbers follow *left-to-right, top-to-bottom* order.
4. **Easy Capital letters**.
   Added a *CAPS Lock* key because... [There is no *CAPS Lock* key in the Colemak Layout](https://colemak.com/FAQ#Where_is_the_Caps_Lock_key.3F).

---

### **Flashing**

~~For *Pro Micro* execute: `sudo make crkbd:colemad:avrdude`~~

~~For *Elite-C* execute: `sudo make crkbd:colemad:dfu`~~

For *Pro Micro* and *Elite-C* run:

```sh
qmk flash -kb crkbd -km colemad -bl dfu
```

---

### **Layers**

#### 0. **COLEMAK**

Notes:

- Double tap Shift to (de)activate CAPS Lock.
- Hold down the Enter thumb key to switch to the LOWER layer
- Hold down the Space thumb key to switch to the RAISE layer
- Characters  **"**  **:**  **|**  **<**  **>**  **?** as you would expect them using *Shift*.

```text
  ,-----------------------------------------------------.      ,-----------------------------------------------------.
  |    Tab |      Q |      W |      F |      P |      G |      |      J |      L |      U |      Y |      ; |      \ |
  |--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
  | BackSP |      A |      R |      S |      T |      D |      |      H |      N |      E |      I |      O |      ' |
  |--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
  |  Shift |      Z |      X |      C |      V |      B |      |      K |      M |      , |      . |      / |    ESC |
  `--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------'
                                               ,--------.      ,--------.
                             ,-----------------|        |      |        |-----------------.
                             |   Alt  |  Ctrl  |  Space |      | Enter  |  Shift |    GUI |
                             |        |        | (RAISE)|      |(LOWER) |        |        |
                             `--------+--------+--------'      `--------+--------+--------'
```

#### 1. **LOWER**

##### Numpad + Navigation

```text
  ,-----------------------------------------------------.      ,-----------------------------------------------------.
  |    Tab |      0 |      1 |      2 |      3 |      - |      |   PgUP |   HOME |      ↑ |    END |    ESC |        |
  |--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
  | BackSP |      / |      4 |      5 |      6 |      + |      |   PgDN |      ← |      ↓ |      → |    DEL |        |
  |--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
  |  Shift |      * |      7 |      8 |      9 |      = |      |        |        |        |        |        |    ESC |
  `--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------'
                                               ,--------.      ,--------.
                             ,-----------------|        |      |        |-----------------.
                             |    Alt |  Ctrl  |  Space |      |        |  Shift |    GUI |
                             |        |        | (RAISE)|      |(LOWER) |        |        |
                             `--------+--------+--------'      `--------+--------+--------'
```

#### 2. **RAISE**

##### Symbols + Function Keys

```text
  ,-----------------------------------------------------.      ,-----------------------------------------------------.
  |    Tab |      ! |      @ |      # |      $ |      % |      |      ^ |      & |      * |      ( |      ) |    F11 |
  |--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
  | BackSP |     F1 |     F2 |     F3 |     F4 |     F5 |      |      ` |      - |      = |      [ |      ] |    F12 |
  |--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
  |  Shift |     F6 |     F7 |     F8 |     F9 |    F10 |      |      ~ |      _ |      + |      { |      } |    ESC |
  `--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------'
                                               ,--------.      ,--------.
                             ,-----------------|        |      |        |-----------------.
                             |   Alt  |  Ctrl  |        |      |  Enter |  Shift |    GUI |
                             |        |        | (RAISE)|      |(LOWER) |        |        |
                             `--------+--------+--------'      `--------+--------+--------'
```

#### 3. **ADJUST**

##### Macros + Settings

Notes:

- Function keys (from F13 to F19) to use for Linux/MacOS shortcuts.

```text
  ,-----------------------------------------------------.      ,-----------------------------------------------------.
  |        |        |    F13 |    F14 |    F15 |        |      |RGB_TOG |RGB_MOD |RGB_VAI |RGB_HUI |RGB_SAI |RGB_SPI |
  |--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
  |        |    F16 |    F17 |    F18 |    F19 |        |      |        |RGB_RMOD|RGB_VAD |RGB_HUD |RGB_SAD |RGB_SPD |
  |--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |      |        |        |        |        |        |        |
  `--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------'
                                               ,--------.      ,--------.
                             ,-----------------|        |      |        |-----------------.
                             |        |        |        |      |        |        |        |
                             |        |        | (RAISE)|      |(LOWER) |        |        |
                             `--------+--------+--------'      `--------+--------+--------'
```

##### Ready to use Macro examples

Checkout `keycodes.h` and `process_records.c/h` files.

- Macro **VSCTERM**: Toggles the vscode terminal (Ctrl + `)
- Macro **CHNLANG**: Changes the OS keyboard layout (Ctrl + Shift + N)
