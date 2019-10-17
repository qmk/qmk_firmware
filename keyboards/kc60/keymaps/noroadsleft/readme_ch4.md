# @noroadsleft's KC60 keymap

- [Table of Contents](./readme.md)
  1. [Base Layers](./readme_ch1.md)
  2. [OS Overlays](./readme_ch2.md)
  3. [Quake 2 Overlays](./readme_ch3.md)
  4. **Function Layers**
  5. [Other Layers](./readme_ch5.md)


----

## Layer 7: Windows Fn layer - `_FW`

### Accessed by holding either `Fn` key in Layer 0

Arrows, Navigation keys (Insert, Home, Page Up, etc.), and Function keys are here. Also has keys for Calculator, Menu, Volume Control, and shortcuts for Select All, Undo, Cut, Copy, and Paste. Numpad Enter for when I'm working in Adobe Photoshop, because it treats Numpad Enter differently from the regular Enter key.

![Windows Fn layer](https://i.imgur.com/XwCshcz.png)


----

## Layer 8: MacOS-oriented Fn layer - `_FM`

### Accessed by holding either `Fn` key in Layer 1

Based on my Windows Fn layer, but swaps a few functions for a MacOS environment. Arrow, Navigation, and Function keys are basically unchanged from Layer 2. This layer enables using either `Fn` key as a sort of simulated `Command` key, which I find easier to reach and use.

![MacOS-oriented Fn layer](https://i.imgur.com/Z11kRu2.png)


----

## Layer 9: Quake 2 Fn layer - `_FQ`

### Accessed by holding either `Fn` key while either Quake 2 overlay is active.

Based on the Windows function layer, but removes some functions that are pointless to have while in the game.

![Quake 2 Fn layer](https://i.imgur.com/9PG7yWb.png)

Keycode(s) Sent                   | Notes
:-------------------------------- | :----
[`Q2_GRV`](./keymap.c#L194-L201)  | Sends `KC_GRV`, then enables the Dvorak, Quake 2 Dvorak, and Quake 2 Console layers.




----

Next Chapter: [Other Layers](./readme_ch5.md)
