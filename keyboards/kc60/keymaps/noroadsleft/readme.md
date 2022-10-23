# @noroadsleft's KC60 keymap

### Last updated: November 9, 2021, 9:47 (-0800)

![](https://i.imgur.com/tzhXQYIl.jpg)

I am a full-time Dvorak typist, and occasional semi-serious FPS gamer. The layers are oriented towards a mix of typing and gaming.


----

## Preface

Images in this readme follow the following format:

![Legend](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/legend.png)  
*Legend*

Descriptions of the physical locations of keys will use the key's function in a US QWERTY layout, even if the layout itself is not QWERTY.


----

## Outline

- [Base Layers](#base-layers)
  - Layer 0: Dvorak `_DV`
  - Layer 1: QWERTY `_QW`
  - Layer 2: Colemak `_CM`
- [Quake 2 Layer](#quake-2-layer)
  - Layer 3: Quake 2 `_Q2`
- [Function Layer](#function-layer)
  - Layer 4: Fn layer `_FN`
- [Other Layers](#other-layers)
  - Layer 5: Numpad layer `_NP`
  - Layer 6: Macro layer `_MA`
  - Layer 7: System layer `_SY`


----

## Base Layers

My base layers are pretty standard for a 60%, with the following changes:

- The `Menu` key has been replaced by `MO(_FN)`, which moves to my Function layer when held.
- The Right `GUI` key has been replaced with a `MO(_MA)` key, which moves to the Macro layer when held.
- The `Caps Lock` key has been replaced with a dual function `LT()` key, which opens the Function layer when held, and is `Caps Lock` when tapped.
- The Left `Control` key has been replaced with a `MT(MOD_CTRL, KC_GRV)` key, which is `Ctrl` when held and <code>&#96; ~</code> when tapped.
- The Number Row `1` through `0` keys will send Numeric Keypad keycodes instead of Number Row keycodes if tapped while `Right Alt` is active. This functionality is documented in [my userspace readme](../../../../users/noroadsleft/readme.md#emulated-numeric-keypad).

### Layer 0: Dvorak - `_DV`

A hardware-based Dvorak Simplified layout. In this layer, I can leave the host system in QWERTY, plug my keyboard in, and still type in Dvorak.

![Dvorak layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/dvorak.png)


### Layer 1: QWERTY - `_QW`

- Accessed by holding either `Fn` and tapping `/?` key, then tapping `2@`.

For when other people need to use my keyboard. :)

![QWERTY layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/qwerty.png)


### Layer 2: Hardware Colemak `_CM`

- Accessed by holding either `Fn` and tapping `/?` key, then tapping `3#`.

A hardware-based Colemak layout. Been thinking of trying it, so it's here.

![Colemak layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/colemak.png)


----

## Quake 2 Layer

### Layer 3: Quake 2 `_Q2`

- Accessed by holding either `Fn` key and tapping the `/?` key, then tapping `4$`

I used to have some macro craziness here. I've now switched to leaving my main system in QWERTY and having the Dvorak stuff happen on the keyboard, and setting my in-game key assignments to the Dvorak mapping (`.OEU` instead of `ESDF`).

![Quake 2](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/quake2.png)


----

## Function Layer

### Layer 4: Function layer - `_FN`

- Accessed by holding either `Fn` key from any base layer

Arrows, Navigation keys (Insert, Home, Page Up, etc.), and Function keys are here. Also has keys for Calculator, Menu, Volume Control, and shortcuts for Select All, Undo, Cut, Copy, and Paste. Numpad Enter for when I'm working in Adobe Photoshop, because it treats Numpad Enter differently from the regular Enter key.

Similarly to my Emulated Numeric Keypad functionality, the `F1` through `F12` keys will change to `F13` through `F24` while `Right Alt` is active. This functionality is documented in [my userspace readme](../../../../users/noroadsleft/readme.md#emulated-extended-function-keys).

![Fn layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/function.png)


----

## Other Layers

### Layer 5: Numpad layer - `_NP`

- Accessed by holding either `Fn` key and tapping `Space`, from any of the Base Layers

Puts a Numpad on the right-hand side of the keyboard. A through F included for hexadecimal input. Tapping `Space` returns to the previous Base Layer.

![Numpad layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/numpad.png)


### Layer 6: Macro layer - `_MA`

- Accessed by holding the right-side `Win` key

Has some macros that I use in Git, and keys for use with the [Dynamic Macros feature](https://docs.qmk.fm/#/feature_dynamic_macros).

For macro documentation, see [my userspace readme](../../../../users/noroadsleft/readme.md).

![Macro layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/macros.png)


### Layer 7: System layer - `_SY`

- Accessed by holding either `Fn` key and tapping the `/?` key

This is where I change my keyboard function. Base layer select on `1` through `4`, Backlight controls on `C` through `N`, Reset on `8*`, Debug on `0)`. Hitting `Esc` exits the layer.

![System layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/system.png)
