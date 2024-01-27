# SlotThe's Keyboardio Atreus Keymap

Note: the following is (a relevant and shortened) excerpt from [this
rewiev](https://tony-zorman.com/posts/atreus-review.html) of the
keyboard itself. See there for, e.g., some thoughts about modifier
placement.

## Base layer

    .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.------.
    |  Q  |  W  |  F  |  P  |  B  |           |  J  |  L  |  U  |  Y  | M4+; |
    .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.------.
    |  A  |  R  |  S  |  T  |  G  |           |  M  |  N  |  E  |  I  |  O   |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.------.
    | S+Z |  X  |  C  |  D  |  V  | ARP | REP |  K  |  H  |  ,  |  .  | S+/  |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.------.
    | ESC | TAB | M4  | L1  | SPC | A[] | BSC | C() | L2  |  -  |  '  | RET  |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.------.

I use [Colemak Mod-DH][colemak-dh] as my layout, so this takes up most of the base of the keyboard.

Perhaps strikingly, I opted for not putting Shift on the thumb,
but recreating the "ordinary" one-on-each-side setup from the good old typewriter days.
While I already have a key to access the `LOWER` (L1) layer with my left thumb,
I had to sacrifice Shift so I could fit a key to the `RAISE` (L2) layer on the right thumb.
This also jumps to the `ADJUST` (L3) layer when both `LOWER` and `RAISE` are held at the same time.
I will gladly trade two layers for one Shift key.

One of the most basic things—besides having layers—that one can do with QMK is [mod-taps][qmk:mod-tap].
These are keys that act as modifiers when held, and as "ordinary" keys when pressed.
For example, all of the `S+«key»` keys emit Shift when held and `«key»` when pressed.
There is a slight delay between pressing the key and the press registering,
since we have to wait for a possible tap,
which keeps me from using modifiers on the home-row, as some people like to do.
Likewise, the `M4+;` key acts as Super when held and as `;` when pressed.
At this point, it is actually my main way to press the Super key,
even though I don't find the real `M4` key particularly hard to hit with my thumb.
Sometimes these things just happen,
I suppose,
though it may help that I press both outer keys of the top row (that is, `q` and `;`) with my ring finger
instead of my pinky.

The `A[]` and `C()` keys are utilising [tap dances][qmk:tap-dance],
in order to do even more.
Tap dances are very similar to mod-taps,
only in addition to just differentiating between a "pressed" and a "held" state,
QMK now also keeps track of *how often* a key has been tapped.
So far, [my setup][qmk:slotthe:tapdances] here is quite basic;
I only check whether a key was pressed once, twice, or is being held.
This allows me to not need extra keys for parentheses,
as they can fit on the modifier keys:

  - `A[]`: Alt when held, `[` when pressed once, and `]` when pressed twice.
    This one is especially neat, since tap dances play well with other modifiers,
    so pressing `S-M1` once will result in `{` and pressing it twice gives `}`.

  - `C()`: Control when held, `(` when pressed once, and `)` when pressed twice.

I don't mind having the extra indirection for the respective closed delimiter,
as [paredit][emacs:paredit],
[puni][emacs:puni],
`electric-pair-mode`,
or a different package of choice usually takes care of inserting it.

The `REP` and `AREP` keys make use of the [Repeat Key][qmk:repeat-key] functionality;
basically, `REP` executes the key chord that was last pressed.
On the other hand,
`AREP` is an alternative, configurable, of "repeating" things;
by default, it turns some directional movements
around—e.g., `M-f` becomes `M-b`—but
it can be made to pretty much input anything one wants.

## Layer 1

    .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-------.
    |  &  | *>  | >>= | <&> |     |           |  =  |  +  |  *  |  -  | M4+RT |
    .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-------.
    | ::  | =>  | =<< | <|> |  @  |           | LFT |  UP | DWN | RGT |   \   |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.
    | S+! | <*  | <*> | <$> | <-  |     | MEN |  -> |  $  |  #  |  %  |  S+^  |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.
    |     |     |     |     |     |     |     |     | L3  | ALT |     | S-Ins |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.

Guess which programming language I like based on this layer's [macros][qmk:macros] :).

Crucially, keys that were "Shift when held,
*something* when pressed" on the base layer retain the Shift part of that functionality.
This is used for the commutativity of the modifier
keys—i.e., it does not matter whether I press `S-L1-«key»` or `L1-S-«key»`—which
would otherwise drive me insane.
The same goes for all fall-through keys:
keys that appear blank in the above layout.
These aren't blocked or anything,
just no new functionality is added
so the key falls back to what's on the next lowest layer.
In plain terms,
the key to the left of `L3` will still be Control,
as I can comfortably press that while holding down something with my left hand.
The same can't be said for the Alt key,
which is on the left hand by default,
so a separate binding for it has to be created on the right hand.
Thus,
as the two don't commute,
key chords involving the LOWER layer and Alt are to be avoided if possible.

The `S-Ins` key is not some sort of tap,
but actually just emits a Shift-Insert,
which can be used to paste stuff from the [X11 primary selection][x11:clipboard].

## Layer 2

    .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
    |     |  7  |  8  |  9  |     |           |     |  +  |  *  |  -  |     |
    .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
    |  :  |  4  |  5  |  6  |  =  |           |     |  `  |  _  |  '  |  "  |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
    | S+0 |  1  |  2  |  3  |     |     |     |     |     |  #  |  %  | S+^ |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
    |     |     |     | L3  |     |     |     |     |     |     |     |     |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.

A relatively unspectacular layer,
RAISE is mainly used for numbers,
and number adjacent things.
Some symbols related to this,
like `=`, `+`, `*`, and `-`,
are replicated from the LOWER layer.
This is due to the above mentioned issues of inserting arithmetic.
This layer also features \` and `'` quite prominently,
as these are important for [CDLaTeX].
Plus, putting `'` and `"` on this layer circumvents the difficult to hit key on the base layer.

## Layer 3

    .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
    |     |     |     |     |     |           |     | F7  | F8  | F9  | F10 |
    .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
    |     |     |     |     |     |           |     | F4  | F5  | F6  | F11 |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
    |     |     |     |     |     |     |     |     | F1  | F2  | F3  | F12 |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
    |     |     |     |     |     |     |     |     |     |     |     |     |
    .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.

So far, only the seldom used F-keys are present here.
As should be obvious, this is the least developed layer,
and also the one that'll probably change the most in the future.
Currently, I'm thinking of putting some XMonad specific bindings on here,
which could even to free up the Super key to be used inside of Emacs
for certain things—that would certainly be a worthwhile experiment.
Other thoughts include things like volume and brightness controls,
although this is less critical since my laptop keyboard is never far away.

## Other features

There are some features that aren't necessarily reflected in the keys themselves,
yet are quite essential for day-to-day use.
The TL;DR can be found in [rules.mk][./rules.mk].

### [Key overrides][qmk:key-overrides]

Quoting from the documentation

> Key overrides allow you to override modifier-key combinations to send a different modifier-key combination
> or perform completely custom actions.

Some keys on the keyboard are quite hard to hit.
On the default layout,
one of these turns out to be the Tab key,
which is nonetheless important in a lot of situations.
Conveniently, Emacs interprets `C-i` as Tab, so there is less need to actually hit the "real" key.
However, not all programs are quite so understanding—or old, I guess.
With key overrides, one can send a real `TAB` whenever `C-i` is pressed;
no special convention on how to interpret certain key chords required!
I also rebound `C-m` to `RET` (with the same justification), and `S-BSP` to `DEL`.

This is one of those features that I didn't know I needed,
yet now couldn't live without anymore.
I'm definitely looking forward to discovering new and interesting ways of using this!

### [Autocorrect][qmk:autocorrect]

This is a quaint little feature: auto-correct inside of your keyboard's firmware!
I promise that it's not as bad as it sounds.
It does not work automatically, thankfully, but is based off a given list of replacements.
For example,

    widht -> width

would fire anytime one writes `widht`, which then gets replaced by `width`.
This is based on (a trie of) the most recently pressed keys,
so whenever one actually wants to write `widht`
all that's needed is pressing, for example, any modifier during the insertion.

As I've really just been trying this out for a laugh, my current word list is quite short:

    :alot       ->  a lot
    accesories  ->  accessories
    accomodate  ->  accommodate
    alledge     ->  allege

In general,
I think the solution to stop misspelling a word is not to remap key sequences on the firmware level,
but to—you know—learn how to spell that word.
Still,
I can imagine at least one or two use-cases where something like this could be useful,
so I figured it might be nice to make people aware of this features' existence.

In addition—as I've found out on three separate occasions so far—using the words "auto-correct, but in firmware"
makes people stare in utter disbelief and/or disgust at your keyboard.
That alone makes this feature worth it.

### [Caps Word][qmk:caps-word]

Caps Word is a clever alternative to Caps Lock,
which I enable by pressing both Shift keys together.
After that,
all of the letter keys are shifted,
and `-` becomes `_`
until a different key (excluding common sense ones like backspace) is pressed.
This is very useful for, e.g.,
writing long constants,
as these tend to have capital names separated with underscores:
writing `BOTH_SHIFTS_TURNS_ON_CAPS_WORD` has never been easier!

One thing to note is that,
while layer switching works just fine in "Caps Word mode",
the [Tri Layer][qmk:tri-layer] feature does not seem to play nicely with it;
i.e., the mode gets disabled when switching to these layers.
This is also the reason why I have an explicit LOWER, RAISE, and ADJUST setup,
instead of just using Tri Layer.
One could fiddle with the `caps_word_press_user` callback,
but it seemed much easier to just create one additional layer toggle instead.
I haven't looked at how hard it would be to hack this into Caps Word,
so maybe this is a future pull request.

[CDLaTeX]: https://github.com/cdominik/cdlatex
[colemak-dh]: https://colemakmods.github.io/mod-dh/
[emacs:paredit]: https://paredit.org/
[emacs:puni]: https://github.com/AmaiKinono/puni
[qmk:autocorrect]: https://docs.qmk.fm/#/feature_autocorrect
[qmk:caps-word]: https://docs.qmk.fm/#/feature_caps_word
[qmk:key-overrides]: https://docs.qmk.fm/#/feature_key_overrides
[qmk:macros]: https://docs.qmk.fm/#/feature_macros
[qmk:mod-tap]: https://docs.qmk.fm/#/mod_tap
[qmk:repeat-key]: https://docs.qmk.fm/#/feature_repeat_key
[qmk:slotthe:tapdances]: https://github.com/slotThe/qmk_firmware/blob/keyboardio/atreus/slotThe/keyboards/keyboardio/atreus/keymaps/slotThe/keymap.c#L187
[qmk:tap-dance]: https://docs.qmk.fm/#/feature_tap_dance
[qmk:tri-layer]: https://docs.qmk.fm/#/feature_tri_layer
[x11:clipboard]: https://www.uninformativ.de/blog/postings/2017-04-02/0/POSTING-en.html
