I love some features from the default layout*, although there are things that definitively I can't get used to. The *circuit* layout gave me some good ideas, so I combined both, with some own ideas to fit better my needs. BTW, I don't use Dvorak or other layouts than QWERTY, and I'm too old and grumpy for learning something new (I'm lying a bit here, I learn new stuff every day), so nay for other typing layouts

## Things I love about the default layout
1. I love the consistency between the raise and lower layers, like one is the shifter version of the other.
2. I like the F keys distributed in two rows, from F1 to F6 and F7 to F12, which makes them easier to find.

## Things I don't like from the default layout
1. Arrow keys distributed VIM like. I use VIM frequently, but there I navigate using HJKL. Moving to the arrows intituively I tend to expect three arrows on the bottom (left, down, right) and one up in the middle (up).
2. Tab and Esc. I switched them.
3. Alt and Super. Switched them too.

## Goals
1. Arrow keys and distributed "traditionally".
2. Media keys available, also I use PrintScreen a lot for capturing screenshots in Gnome.
3. A button for Sleep.
4. As close as possible to a US QWERTY layout.
5. Optional Numpad.
6. Record Dynamic Macros.

Layers:

Main Layout / QWERTY:

Has four modes: The default, Lower, Raise and Media.

Media gives access to most media keys, and some keyboard actions such as Print Screen, Insert, Calculator or Power/Sleep/Wake. Also in the Media layer, you can record two different macros and reproduce them.

http://www.keyboard-layout-editor.com/#/gists/4cfb26f84bbb4fabe5e6c7cc22c85e24

Additionally, Lower + Raise gives access to the layer switching, plus keyboard modes (such as music mode), reset, SysReq and Lock Mode, which disables the double shift tap for CapsLock (taken from the *circuit* layout). Also provides another distribution for the F keys.

Lower + Raise:
http://www.keyboard-layout-editor.com/#/gists/12462bfba17d16bb40b54ed914209d92

Numpad:
http://www.keyboard-layout-editor.com/#/gists/5ab730ab278d2050c5250498806e8edc

--------------------------------------
Notes taken from the circuit layout:

###Special keys:
* `RSHFT` and `ENTER` are combined. Tap once for `ENTER` and hold for `RSHFT`. `ENTER` will be registered on release if released within 200 ms, else `RSHFT` is registered starting at 201 ms until release.
* If for some reason, this interferes with the normal usage of the `ENTER` key in any way, (some problem that may never happen), I have added a regular non-modified `ENTER` key on the same key in the [LOWER] and [RAISE] layers.
* `LSHFT` and `CAPS` are also combined. The key works like a normal `LSHFT` unless double-tapped, in which case it counts as `CAPS`. This functionality unfortunately delays all key presses by at most 200 ms, but I have added ways to disable this both temporarily or permanently, described below.
* A failsafe `CAPS` key is on the same key in the [LOWER] and [RAISE] layers.
* There are `UNDO`, `CUT`, `COPY`, and `PASTE` keys. This was intended to be a universal way to use these commands since in macOS cut is `⌘ + C` but in Windows it is `⌃ + C`. Unfortunately these special keys only work in Windows. ¯\\\_(ツ)\_/¯

##Game lock:
**TL;DR** the game lock toggle disables the double-tap `CAPS`, and disables `GUI` keys (WINDOWS key).

![keyboard-layout](https://i.imgur.com/HHSZSQq.png)
