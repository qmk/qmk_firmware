# @noroadsleft's KC60 keymap

### Last updated: April 26, 2021 13:33 (-0700)

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
  - Layer 0: QWERTY `_QW`
  - Layer 1: Hardware Dvorak `_DV`
  - Layer 2: Hardware Colemak `_CM`
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

### Layer 0: QWERTY - `_QW`

Standard QWERTY layout, with four QMK features:

- The `Menu` key has been replaced by `MO(_FW)`, which moves to my Windows Fn layer when held.
- The Right `GUI` key has been replaced with a `MO(_MA)` key, which moves to the Macro layer when held.
- The `Caps Lock` key has been replaced with a dual function `LT()` key, which opens the Windows Fn layer when held, and is `Caps Lock` when tapped
- The Left `Control` key has been replaced with a `MT(MOD_CTRL, KC_GRV)` key, which is <code>&#96; ~</code> when tapped and `Ctrl` when held.

![QWERTY layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/qwerty.png)


----

### Layer 1: Hardware Dvorak - `_DV`

- Accessed by holding either `Fn` and tapping `/?` key, then tapping `2@`.

A hardware-based Dvorak Simplified layout. At my weekend job, I use a shared computer that runs MacOS Sierra, in US QWERTY layout. In this layer, I can leave the system in QWERTY, plug my keyboard in, and still type in Dvorak.

![Hardware Dvorak layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/dvorak.png)


----

### Layer 2: Hardware Colemak `_CM`

- Accessed by holding either `Fn` and tapping `/?` key, then tapping `3#`.

A hardware-based Colemak layout. Been thinking of trying it, so it's here.

![Hardware Colemak layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/colemak.png)


----

## Quake 2 Layer

### Layer 3: Quake 2 `_Q2`

- Accessed by holding either `Fn` key and tapping the `/?` key, then tapping `4$`

These layers were born out of the confusion I have had trying to use the in-game chat and the console in [Quake 2](https://en.wikipedia.org/wiki/Quake_II). When Quake 2 came out, alternate keyboard layouts weren't really a thing. As a result, all in-game text input is hard-locked to US QWERTY, regardless of what the operating system is using for its input method.

I have solved this by writing a custom QMK macro. The keycode in the System layer that enables these layers, [`GO_Q2`](./keymap.c#L205), is a [macro](./keymap.c#L63-L70) that sets the default layer to the QWERTY layer, then turns the Quake 2 layer `_Q2` on. The result is a partially-overwritten QWERTY layer, that changes the dual-function Left Control/Grave key to a standard Left Control, and the Enter key into a special Enter key specific to Quake 2.

When I hit the `Enter` key (bound in-game to text chat), the [macro keycode](./keymap.c#L71-L86) I've created sends the keycode for `Enter`, then follows with flipping an internal boolean variable and enabling the Hardware Dvorak layer. Now the game is in text chat mode, and my keyboard is in Dvorak. When I hit `Enter` again, another `Enter` key is sent, which sends the message, then the macro flips the boolean back to false and disables the Hardware Dvorak layer, which brings me back to the standard QWERTY+Quake 2 setup. Hitting `Escape` instead runs a [macro](./keymap.c#L87-L97) that cancels the sending of the message, and undoes the layers.

![Quake 2](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/quake2.png)


----

## Function Layer

### Layer 4: Fn layer - `_FN`

- Accessed by holding either `Fn` key from any base layer

Arrows, Navigation keys (Insert, Home, Page Up, etc.), and Function keys are here. Also has keys for Calculator, Menu, Volume Control, and shortcuts for Select All, Undo, Cut, Copy, and Paste. Numpad Enter for when I'm working in Adobe Photoshop, because it treats Numpad Enter differently from the regular Enter key.

![Fn layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/function.png)


----

## Other Layers

### Layer 5: Numpad layer - `_NP`

- Accessed by holding either `Fn` key and tapping `Space`, from any of the Base Layers

Puts a Numpad on the right-hand side of the keyboard. A through F included for hexadecimal input. Tapping `Space` returns to the previous Base Layer.

![Numpad layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/numpad.png)


----

### Layer 6: Macro layer - `_MA`

- Accessed by holding the right-side `Win` key

Has some macros that I use in Git, and keys for use with the [Dynamic Macros feature](https://docs.qmk.fm/#/feature_dynamic_macros).

For macro documentation, see [my userspace readme](../../../../users/noroadsleft/readme.md).

![Macro layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/macros.png)


----

### Layer 7: System layer - `_SY`

- Accessed by holding either `Fn` key and tapping the `/?` key

This is where I change my keyboard function. Base layer select on `1` through `4`, Backlight controls on `C` through `N`, Reset on `8*`, Debug on `0)`. Hitting `Esc` exits the layer.

![System layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/system.png)
