# @noroadsleft's KC60 keymap

- [Table of Contents](./readme.md)
  1. [Base Layers](./readme_ch1.md)
  2. [Quake 2 Overlays](./readme_ch2.md)
  3. **Function Layers**
  4. [Other Layers](./readme_ch4.md)


----

## Layer 6: Fn layer - `_FN`

### Accessed by holding either `Fn` key from any base layer

Arrows, Navigation keys (Insert, Home, Page Up, etc.), and Function keys are here. Also has keys for Calculator, Menu, Volume Control, and shortcuts for Select All, Undo, Cut, Copy, and Paste. Numpad Enter for when I'm working in Adobe Photoshop, because it treats Numpad Enter differently from the regular Enter key.

![Windows Fn layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/Fn.png)


----

## Layer 7: Quake 2 Fn layer - `_FQ`

### Accessed by holding either `Fn` key while either Quake 2 overlay is active.

Based on the Windows function layer, but removes some functions that are pointless to have while in the game.

![Quake 2 Fn layer](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/Quake%202%20Fn.png)

Keycode(s) Sent                   | Notes
:-------------------------------- | :----
[`Q2_GRV`](./keymap.c#L130-L137)  | Sends `KC_GRV`, then enables the Dvorak, Quake 2 Dvorak, and Quake 2 Console layers.




----

Next Chapter: [Other Layers](./readme_ch4.md)
