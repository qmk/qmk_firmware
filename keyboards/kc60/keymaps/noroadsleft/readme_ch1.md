# @noroadsleft's KC60 keymap

- [Table of Contents](./readme.md)
  1. **Base Layers**
  2. [Quake 2 Overlays](./readme_ch2.md)
  3. [Function Layers](./readme_ch3.md)
  4. [Other Layers](./readme_ch4.md)


----

## Layer 0: QWERTY - `_QW`

Standard QWERTY layout, with four QMK features:

- The `Menu` key has been replaced by `MO(_FW)`, which moves to my Windows Fn layer when held.
- The Right `GUI` key has been replaced with a `MO(_MA)` key, which moves to the Macro layer when held.
- The `Caps Lock` key has been replaced with a dual function `LT()` key, which opens the Windows Fn layer when held, and is `Caps Lock` when tapped
- The Left `Control` key has been replaced with a `MT(MOD_CTRL, KC_GRV)` key, which is <code>&#96; ~</code> when tapped and `Ctrl` when held.

![QWERTY layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/QWERTY.png)


----

## Layer 1: Hardware Dvorak - `_DV`

### Accessed by holding either `Fn` and tapping `/?` key, then tapping `2@`.

A hardware-based Dvorak Simplified layout. At my weekend job, I use a shared computer that runs MacOS Sierra, in US QWERTY layout. In this layer, I can leave the system in QWERTY, plug my keyboard in, and still type in Dvorak.

![Hardware Dvorak layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/Dvorak.png)


----

## Layer 2: Hardware Colemak `_CM`

### Accessed by holding either `Fn` and tapping `/?` key, then tapping `3#`.

A hardware-based Colemak layout. Been thinking of trying it, so it's here.

![Hardware Colemak layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/Colemak.png)


----

Next Chapter: [Quake 2 Overlays](./readme_ch2.md)
