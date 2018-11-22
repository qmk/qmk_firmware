# replicaJunction - Atreus Layout

This layout is designed to make the absolute most out of the Atreus 40% keyboard.

This layout is probably not perfect for you. That's okay! Use it for ideas as you design your own perfect layout.

Most of the custom logic in this keyboard is actually not in these files. Instead, it's in the directory `/users/replicaJunction` (from the root of the QMK repo). This allows me to share macros and custom logic between multiple keyboards. A `process_record_keyboard()` function defined weakly in `replicaJunction.h` allows keyboards to process records individually as well without overriding the `process_record_user()` function. (My Ergodox uses this to handle its LEDs, for example.)

The default letter layout in this keymap is [Colemak-ModDH](https://colemakmods.github.io/mod-dh/). I use the "matrix version" of that layout, which retains the M key on the home row as in normal Colemak.

## Design Goals

I designed this layout with the following goals in mind:

* Nothing may interfere with ordinary typing.
* Symbols need to be accessible quickly and organized in a manner I can remember.
* Limit more difficult finger movements (and pinky usage in general).

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

## Features

### ZXC Mods

Keys on the bottom row of each half of this keyboard can be held to send modifier keys. I've tried to map this in a relatively logical manner:

* Z / Slash: Ctrl
* X / Period: GUI
* C / Comma: Ctrl+Alt
* D / H: Alt

Combined with Shift keys on the thumbs, this makes all modifiers quick to access on either hand.

### Layer tap dance

The lower-left key on the left hand can be used to apply or remove layers based on a number of taps:

* 1 tap sends Escape, and also disables any persistent layers.
* 2 taps enables the Number pad layer.
* 5 or more taps resets the keyboard.

## Extend Layer

[Originally found on the Colemak forums](https://forum.colemak.com/topic/2014-extend-extra-extreme/), having a QMK-powered keyboard allows a super easy implementation of this concept. The idea is to place commonly-used keys under easy reach of your hands. Since I work with text often, my most common needs are things like Ctrl+Shift+arrow keys, and they're easy to access using this layer. (While technically it's four keypresses instead of just three, since it takes one key to enter the layer, that one key is a thumb button and the other three are all on the home row, so I find it much more comfortable than modifiers on a traditional keyboard.)

Also featured in this layer is easy access to Tab, plus a Shift+Tab key. Alt-Tabbing back and forth, along with Ctrl-Tab, are super easy and friendly. When I need Ctrl+Alt+Delete, I typically use the ones found on this layer.

## Layout Images

Colored keys indicate keys that swap to another layer when held.

These images are located in the `kle` folder of this directory. Also included is the "raw data" from Keyboard-Layout-Editor in a corresponding text file.

### Base layer

![Base layer](kle/base-layer.png)

### R layer

![R layer](kle/r-layer.png)

### E layer

![E layer](kle/i-layer.png)

### I layer

![I layer](kle/i-layer.png)

### Space layer

![Space layer](kle/space-layer.png)

### Function layer

![Function layer](kle/fn-layer.png)

## Credits

* [Drashna](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/readme.md)
  * User / keymap function ideas
* [Jeremy](https://github.com/qmk/qmk_firmware/blob/master/keyboards/atreus/keymaps/jeremy/readme.md)
  * Sanity check on the Function keys (_of course they should be in rows of 4, not rows of 3 like a number pad. Why did I ever use anything else?_)
* [DreymaR of the Colemak forums](https://forum.colemak.com/topic/2014-extend-extra-extreme/)
  * Original idea of the Extend layer
