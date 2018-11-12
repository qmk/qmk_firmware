# replicaJunction - Ergodox (EZ) Layout

This keymap is designed to complement my Atreus keyboard layout, found in keyboards/atreus. The Atreus keyboard is a 40% board whose design was heavily influenced by the Ergodox. Since I use both keyboards, I've designed these layouts in an effort to make switching between the two as easy as possible.

I've also tried to make use of the extra keys on the Ergodox in as logical of a manner as possible, adding to the layers in the Atreus config without disturbing what's there already. This allows for things like F11-F20, the Application (Menu) key, and better media key placement.

Because of this design philosophy, there are several cases where functionality is duplicated and keys are available in more than one place. I don't find that a bad thing.

This layout makes heavy use of dual-role keys. Dual-role keys seemed to affect my typing speed for quite some time until I discovered the [`USE_PERMISSIVE_HOLD` flag](https://docs.qmk.fm/features/advanced-keycodes#permissive-hold). After applying this flag, I haven't had an issue with dual-role keys and typing quickly.

The default letter layout in this keymap is [Colemak-ModDH](https://colemakmods.github.io/mod-dh/). I use the "matrix version" of that layout, which retains the M key on the home row as in normal Colemak.

## Design Goals

I designed this layout with the following goals in mind:

* Atreus layout compatibility.
* Nothing may interfere with ordinary typing.
* Symbols need to be accessible quickly and organized in a manner I can remember.
* Limit more difficult finger movements (and pinky usage in general).
* Gaming should be easy.

### Atreus layout compatibility

Most of the functionality in this layout isn't strictly necessary - the Ergodox is a 76-key keyboard, and it's got plenty of room for extra keys and functionality compared to smaller boards like the Atreus. However, I've replicated a lot of 40% functionality on this layout in order to preserve my muscle memory.

The biggest deviation is the Shift keys. My Atreus uses thumb keys for Shift, but the Ergodox doesn't have corresponding thumb keys in a comfortable enough location. I briefly tried using the outermost 1u keys in the bottom row as Shift keys, but they take a large enough thumb movement that it interfered with typing.

### Nothing may interfere with ordinary typing

For a long time, this meant that I couldn't use letters or home row keys as dual-role keys. I'm a fast typer, and I'm sometimes already typing the next letter before I've fully released the previous one. Normal keyboards don't care about this, but if I started adding dual-role functionality to letters, I found that I would sometimes type the next letter before releasing the layer toggle, and the letter I tried to send would still be sent under the layer I thought I'd left off.

Fortunately, though, QMK has addressed this with the `PERMISSIVE_HOLD` flag. [Details are on the QMK docs page.](https://docs.qmk.fm/#/feature_advanced_keycodes?id=permissive-hold)

Using that flag, I'm comfortable having layer shift keys on the home row, and this goes a long way to eliminate finger stress.

### Sympols need to be accessible quickly

Symbols are available under my left hand by holding the I key (on my right hand). I've grouped parenthesis, slashes, and braces together; the remaining symbols are ordered in the same way as they appear on USA keycap legends (for example, 1 is !, so that symbol is first in my lineup). Practically, I just had to get used to these other "misc" symbols.

This also means that some symbols are accessible in more than one way. For example, the carats (greater than and less than) are available both in the "normal" location (Shift+Comma / Shift+Period) and on the symbol layer. I make regular changes to some of the symbols I don't use as commonly as I think of them.

### Limit more difficult finger movements

This is why I kept trying to put layer toggles on the home row keys instead of just placing them on random thumb keys. I suffer from RSI, and it's important for me to watch out for more "stressful" finger movements.

The home row is the easiest row for your fingers to hit, followed by the upper row, and the lower row is noticeably more difficult to press. Because of this, I favored the upper row over the lower one any time I had the option to do so.

### Gaming should be easy

I've added a dedicated gaming layer accessible by pressing the upper-right key on the right hand (next to the 6 key). This layer disables most of the tap/hold functionality to allow keys to act normally. This layer also reverses Backspace and Space (so Space is available on the left thumb while the right hand is on the mouse).

I've also added a lock key on the right hand's bottom 1.5u key and mouse keys on the right thumb cluster. This has been amazingly helpful for games that involve holding keys for extended times (for example, I can hold the left mouse button in Minecraft to continually mine).

I strongly recommend using ESDF (QWERTY positions) for movement on the Ergodox rather than WASD. This makes the thumb keys much more accessible.

Finally, I considered having the gaming layer revert to a QWERTY layout, but decided against it because it really threw me off when I needed to type in chat. I've accepted that I will need to rebind keys in most games as a reasonable compromise.

## Features

### ZXC Mods

Keys on the bottom row of each half of this keyboard can be held to send modifier keys. I've tried to map this in a relatively logical manner:

* Z / Slash: Ctrl
* X / Period: GUI
* C / Comma: Ctrl+Alt
* D / H: Alt

This is an example of maintaining compatibility with the Atreus layout. An Ergodox doesn't really need these keys, but I've grown accustomed to them on the Atreus, so they're copied here to preserve compatibility.

### Layer Switching - Tap Dance

The lower-left key on the left hand can be used to apply or remove layers based on a number of taps:

* 1 tap sends Escape, and also disables any persistent layers.
* 2 taps enables the Number pad layer.
* 3 taps enables the QWERTY layer.
* 5 or more taps resets the keyboard.

## Extend Layer

[Originally found on the Colemak forums](https://forum.colemak.com/topic/2014-extend-extra-extreme/), having a QMK-powered keyboard allows a super easy implementation of this concept. The idea is to place commonly-used keys under easy reach of your hands. Since I work with text often, my most common needs are things like Ctrl+Shift+arrow keys, and they're easy to access using this layer. (While technically it's four keypresses instead of just three, since it takes one key to enter the layer, that one key is a thumb button and the other three are all on the home row, so I find it much more comfortable than modifiers on a traditional keyboard.)

Also featured in this layer is easy access to Tab, plus a Shift+Tab key. Alt-Tabbing back and forth, along with Ctrl-Tab, are super easy and friendly. When I need Ctrl+Alt+Delete, I typically use the ones found on this layer.

## Credits

* [Drashna](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/readme.md)
  * User / keymap function ideas
* [Jeremy](https://github.com/qmk/qmk_firmware/blob/master/keyboards/atreus/keymaps/jeremy/readme.md)
  * Sanity check on the Function keys (_of course they should be in rows of 4, not rows of 3 like a number pad. Why did I ever use anything else?_)
* [DreymaR of the Colemak forums](https://forum.colemak.com/topic/2014-extend-extra-extreme/)
  * Original idea of the Extend layer
