# callum’s planck layout

This is a layout for the grid planck, built with a few ideals in mind. These ideals are just my opinion mind! The great thing about *qmk* is that we can all afford to have different opinions about what makes a good layout:

- Minimal response times should be maintained. i.e. keys that react differently depending on whether they are tapped or held, keys that react differently if they are double tapped, etc. should be avoided --- since they inevitably send their keycode later than a normal key, interrupting the immediate feedback from the screen. Therefore we restrict ourselves to chording.
- The hands should never need to leave the home position. The usual culprit for this is the arrow cluster, so the arrow cluster should be as close to home as possible.
- There should be two of every modifier (one on each side), since otherwise certain long key combinations become hard to make.
- Backspace should be in the “capslock position” as God intended.
- The keyboard should be usable without any firmware changes on any operating system. In my case that means it should work on *Windows* and *Linux* without any software modifications, while I can change the behaviour slightly on *macOS* in software since that’s my home OS. The images reflect the intended use on *macOS* **after** minor software tweaks; which will be noted.

We have four layers. A `BASE` layer, in colemak; a `MOVE` layer, with an arrow cluster etc, a `SYMB` layer, with numbers and symbols; and a `FUNC` layer, with function keys and media keys.

## The `BASE` layer
![](http://i.imgur.com/aEXOlWl.png)

This is the default layer; in [colemak](https://colemak.com). `esc` and `del` are conspicuously absent but are especially easy to reach from either of the other main layers (see below). The `backspace` location is standard colemak. The `caps` key is still on the `BASE` layer but only because I  don’t really use the bottom corners so there’s nothing else I would rather put there. Having `enter` on a thumb means I can still have `quote` immediately to the right of `O`, something that would have annoyed me endlessly otherwise. `minus` is in the upper right because I had an extra space and it’s probably my next most used key that didn’t yet have a home.

The `MOVE` and `SYMB` layers are reached by holding down the `move` and `symb` keys respectively. The `FUNC` layer is reached by holding down both the `move` and `symb` keys simultaneosly, *or* by holding down the `fn` key. The intended use is that whenever both hands are on the keyboard, the former method is used, and the latter is only used when, for example, reaching over to the keyboard with one hand to access the media controls. 

The `ctrl`, `alt`, `cmd` cluster is asymmetric around the centre so that at least one of each of the modifiers can be reached with the thumbs. The intended use is to always hit the left `cmd` and the right `ctrl`, unless an awkward key combination dictates otherwise.

In firmware `ctrl` and `cmd`/`GUI` are swapped with respect to the image above --- I swap them to the illustrated location when using *macOS* and leave them be for *Windows* and *Linux*. (so that `cmd-z,x,c,v,...` becomes `ctrl-z,x,c,v,...` saving me some confusion)

## The `MOVE` layer
![](http://i.imgur.com/KXRSuHT.png)

This is fairly self explanatory. I almost exclusively use the right hand cluster so that movement is a one handed affair, but the left hand cluster is there if it’s needed.

On *macOS* I recommend using [Karabiner](https://pqrs.org/osx/karabiner/) and ticking *Use PC Style Home/End #2* and *Use PC Style PageUp/PageDown* so that `home` and `end` jump you to the beginning and end of the line respectively and so that `pg up` and `pg dn` move the cursor instead of just scrolling.

None of the modifiers are overwritten so that `shift-alt-arrows` etc work as expected.

## The `SYMB` layer
![](http://i.imgur.com/thh1ne2.png)

The symbol layer has all the numbers and their usual corresponding symbols in the first two rows, with the symbols on the home row since I use them more frequently than the numbers. The third row contains all the remaining symbols, arranged roughly so that the most used symbols are accessible with the strongest fingers.

`esc` and `del` are repeated here since I wanted to be able to reach either, one handed, with either hand.

Again none of the modifiers are overwritten so that shortcuts involving numbers or symbols work as expected.

## The `FUNC` layer
![](http://i.imgur.com/skxRZiH.png)

The only thing of note here is that `bl+` and `bl-` are short for *backlight up* and *backlight down* respectively, and in firmware are actually `KC_PAUS` and `KC_SLCK` respectively, since *macOS* interprets these as the backlight keys.

## Other changes from the default
I have LEDs and sound disabled, simply because I have no need of them.