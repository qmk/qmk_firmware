# @noroadsleft's KC60 keymap

- [Table of Contents](./readme.md)
  1. [Base Layers](./readme_ch1.md)
  2. **Quake 2 Overlays**
  3. [Function Layers](./readme_ch3.md)
  4. [Other Layers](./readme_ch4.md)


----

## Layer 3: Quake 2 `_Q2`

- Accessed by holding either `Fn` key and tapping the `/?` key, then tapping `4$`

These layers were born out of the confusion I have had trying to use the in-game chat and the console in [Quake 2](https://en.wikipedia.org/wiki/Quake_II). When Quake 2 came out, alternate keyboard layouts weren't really a thing. As a result, all in-game text input is hard-locked to US QWERTY, regardless of what the operating system is using for its input method.

I have solved this by writing a custom QMK macro. The keycode in the System layer that enables these layers, [`GO_Q2`](./keymap.c#L205), is a [macro](./keymap.c#L63-L70) that sets the default layer to the QWERTY layer, then turns the Quake 2 layer `_Q2` on. The result is a partially-overwritten QWERTY layer, that changes the dual-function Left Control/Grave key to a standard Left Control, and the Enter key into a special Enter key specific to Quake 2.

When I hit the `Enter` key (bound in-game to text chat), the [macro keycode](./keymap.c#L71-L86) I've created sends the keycode for `Enter`, then follows with flipping an internal boolean variable and enabling the Hardware Dvorak layer. Now the game is in text chat mode, and my keyboard is in Dvorak. When I hit `Enter` again, another `Enter` key is sent, which sends the message, then the macro flips the boolean back to false and disables the Hardware Dvorak layer, which brings me back to the standard QWERTY+Quake 2 setup. Hitting `Escape` instead runs a [macro](./keymap.c#L87-L97) that cancels the sending of the message, and undoes the layers.

![Quake 2](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/kc60/keymaps/noroadsleft/layer-3-quake2.png)


----

Next Chapter: [Function Layers](./readme_ch3.md)
