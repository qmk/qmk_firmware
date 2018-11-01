# Dr NotSoKind's layout

*Feel free to ask questions or send suggestions to [me on Twitter](https://twitter.com/pnikosis)*

I love some features from the default layout, although there are things that definitively I can't get used to. Other layouts such as *circuit* gave me some good ideas, so I combined them all plus some own stuff to fit better my needs.

BTW, I don't use Dvorak or other layouts than QWERTY and I'm too old and grumpy for learning something new (I'm lying a bit here, I learn new stuff every day), so I removed the ther typing layouts

## Things I love about the default layout
1. I love the consistency between the raise and lower layers, like one is the shifted version of the other.
2. I like the F keys distributed in two rows, from F1 to F6 and F7 to F12, which makes them easier to find and access.

## Things I don't like from the default layout
1. Arrow keys distributed VIM like. I use VIM frequently, but there I navigate using HJKL. Moving to the arrows intituively I tend to expect three arrows on the bottom (left, down, right) and one up in the middle (up).
2. Tab and Esc. I switched them.
3. Alt and Super. Switched them too.

## Needs, changes and goals
1. Arrow keys distributed "traditionally".
2. Media keys easily accessible.
3. A button for Sleep/Power.
4. As close as possible to a US QWERTY layout.
5. A Numpad, for when I want to feel like an accountant.
6. Be able to record Dynamic Macros.
7. Zoom in and Zoom out (basically Ctrl - and Ctrl +)

I've been experimenting a lot and I think I'm getting closer to my customization end game.

## Layers:

## Main Layer / QWERTY

Apart from the default, lower and raise, I added an extra Media/Action layer, for volume and playback control, plus some keyboard actions such as Print Screen, Insert, Calculator or Power/Sleep/Wake. Also in the [MEDIA] layer, you can record two different macros and reproduce them.

### About the volume up and down

That was a hard decision. I wanted the vol up, down and mute easily accessible, and in an obvious palce. I finally decided to use the `Raise` and `Lower` modifier keys to manage the volume, in combination with the [MEDIA] modifier key. This could look a little weird, since the modifier keys are having a different function than modify the layer, but ended up working fairly well, so while pressing [MEDIA] you have the `Lower` key to put the volume down, `Raise` to raise the volume, and `Space` for mute.

### Zoom in and Zoom out

Using the [MEDIA] modifier you can zoom in and zoom out in browsers and other applications using `,` (for zooming out) and `.` (for zooming in). These keys are mapped to `LCTRL -` and `LCTRL =`. I initially thought about mapping zoom in to `LCTRL +` but most apps also map the zoom in using the `=` key, and some they don't event support zooming in with `+` (I'm looking at you Sublime Text).

### Right Shift and Enter

`RSHFT` and `ENTER` are combined. Tap once for `ENTER` and hold for `RSHFT`. `ENTER` will be registered on release if released within 200 ms, else `RSHFT` is registered starting at 201 ms until release.

If for some reason, this interferes with the normal usage of the `ENTER` key in any way, (some problem that may never happen), there is a regular non-modified `ENTER` key on the same key in the [LOWER] and [RAISE] layers, as well in the [LOCK] mode (see below).

### Caps Lock

`LSHFT` and `CAPS` are also combined. The key works like a normal `LSHFT` unless double-tapped, in which case it counts as `CAPS`. This functionality unfortunately delays all key presses by at most 200 ms, but I have added ways to disable this both temporarily or permanently, described below.

A normal behavior for `LSHFT` key is on the same key in the [LOWER], [RAISE] and [MEDIA] layers (so you can double tap it, as in IntelliJ IDEA), you can also use the [LOCK] mode.

### Copy/Paste

There are `UNDO`, `CUT`, `COPY`, and `PASTE` keys with the [MEDIA] modifier. This was intended to be a universal way to use these commands since in macOS cut is `⌘ + C` but in Windows it is `⌃ + C`. Unfortunately these special keys only work in Windows.

### How to record and play dynamic Macros

I wanted the macros a little "harder" to start recording than usual, since I didn't want to accidentally delete a macro. Also I wanted to share the same key for storing and reproducing the macros, made more sense for me than using one key for storing the Macro1, and use another one for reproducing that Macro.

**Record a Macro**

Press `Media` and `LCtrl` (that's left control), you will hear a beep if you have the audio on. Then choose where you want to store the Macro, in `;` or `'`, so press that key, you will now hear a tone for the macro start being recorded.

When you are done, press `Media` and `Enter`. You will finally hear a tune confirming that the macro has been stored.

**Play a Macro**

Press `Media` and the key where you stored your Macro, either `;` or `'`. The Macro will play.

![Imgur](https://i.imgur.com/ri4lEcl.png)

http://www.keyboard-layout-editor.com/#/gists/4cfb26f84bbb4fabe5e6c7cc22c85e24

## Lock Mode

The Lock mode toggle disables the double-tap `CAPS` and disables `GUI` keys (WINDOWS key), also makes `ENTER` behave normally (not `RSHIFT` when hold).

## Lower + Raise (adjust) Layer

Lower + Raise gives access to the layer switching, plus keyboard modes (such as enabling music mode for annoying your coworkers), reset, SysReq and Lock Mode, which disables the double shift tap for CapsLock (taken from the *circuit* layout, see the comments below). Also provides another distribution for the F keys.

![Adjust](https://i.imgur.com/6m6baos.png)

http://www.keyboard-layout-editor.com/#/gists/12462bfba17d16bb40b54ed914209d92

## Numpad Layer

![Numpad](https://i.imgur.com/od1plfz.png)

http://www.keyboard-layout-editor.com/#/gists/5ab730ab278d2050c5250498806e8edc

This layer is mostly for quick typing numbers using the numpad. You have NumLock available to switch before the keypad numbers or the actions (movement, del, insert, etc). Esc serves as a quick way to go abck to the QWERTY layer (also you can go to the QWERTY layer through the adjust layer).

