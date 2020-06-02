# plattfot's keymap for [Kyria](https://github.com/splitkb/kyria)

![Keyboard](https://i.imgur.com/Pvsm973l.jpg)

Designed to be ease of use when programming, typing in both English
and Swedish and navigating around in a tiling window manager, in my
case [sway](https://swaywm.org/). Uses the two rotary encoders (lower
left/right thumb row) as two palm buttons.

This keymap avoids [Mod-tap](https://docs.qmk.fm/#/mod_tap) as they do
not work for me. [Kyria](https://github.com/splitkb/kyria) has enough
thumb keys to make it work without them.


# Base Layer: Default
```
 // ,-------------------------------------------.                              ,-------------------------------------------.
 // |   `    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |   Å    |
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 // |  Tab   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 // |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 // | LShift |   Z  |   X  |   C  |   V  |   B  | Lead | RAISE|  | LOWER|DBLTAP|   N  |   M  | ,  < | . >  | /  ? | RShift |
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                        | MPlay| GUI  | LCtrl| Space| LALT |  | Enter|BSpace| NAV  | LAlt |Worksp|
 //                        |      |      |      |      |      |  |      |      |      |      |toggle|
 //                        `----------------------------------'  `----------------------------------'
```

Setup for typing in both English and Swedish (hence the Å in the top
right corner, which is just [ on an US layout).

Modifiers are mostly on the left hand, to make it comfortable when
require keyboard and mouse. For example working in a DCC (Digital
Content Creation tool) like [Houdini](https://www.sidefx.com/) and
[Maya](https://www.autodesk.com/products/maya/overview).

## Notable features on this layer

Left rotary encoder
- Press: play/pause
- Rotate: Volume control

Right rotary encoder
- Press: Call keybinding that toggles between two recent workspaces.
         For [sway](https://swaywm.org/) that is `workspace
         back_and_forth`
- Rotate: Page up/Page down. Used mouse scrolling at first. But
          scrolling only works in the window where the mouse pointer
          is. Which kind of defeated the purpose of having the scroll
          on the keyboard, as I still needed to move my hand to the
          mouse and then I could just use the scroll on the mouse.

[Leader key](https://docs.qmk.fm/#/feature_leader_key) is mainly used
for jumping between workspaces. Otherwise I would need to use both
hands everytime I need to switch. With the leader key I can jump
between 1-5 with just the left hand. The right rotary encoder also
helps jumping back and forth between two workspaces by just pressing
down my right palm.

The double tap key, which I based on a code snippet from a
[reddit post](https://www.reddit.com/r/olkb/comments/citkbx/double_key_press_modifier_qmkwould_work_like/ev9cue8).
When pressed, it will repeat the next key twice. Reason for this is
that I found it a bit awkward to hold down the lower key when I need
to type a symbol twice. Which happens a lot when programming or
running commands on the command line. Does not save me any key presses
but more comfortable to type double keys, for example `--` and `&&`.

# Lower Layer: Symbols
```
 //
 // ,-------------------------------------------.                              ,-------------------------------------------.
 // |   ~    |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |        |
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 // |        |  |   |  _   |  \   |  -   |  +   |                              |   =  |  {   |  }   |  [   |  ]   |   ''   |
 // |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 // |        |  []  |  {}  |  ()  |  <>  |      |      |      |  |      |      |      |      |  <   |  >   |  ?   |        |
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                        | Mute |      |      |      |      |  |      |      |      |      |      |
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        `----------------------------------'  `----------------------------------'
```

Contains most of the symbols, only exceptions are those that are
already on the default US base layer i.e. quotes, punctuation and
forward slash.

## Notable features on this layer

Left rotary encoder
- Press: mute
- Rotate: Skip next/previous song

The left letter bottom row contains macros to quickly type the
different types of brackets and move the cursor to be inside. For
example lower+c will type `()←`, where `←` is pressing the left arrow.
Same principle for the `''` macro. Really nice to have when
programming, and it is editor agnostic.

# Raise Layer: Function keys
```
 // ,-------------------------------------------.                              ,-------------------------------------------.
 // |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  | F10  |        |
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 // |        |      |      |      |      | F11  |                              | F12  |      |      |      |      |        |
 // |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 // |        |      |      |      |      |      |ScLock|      |  |      | Ins  |      |      |      |      |      |        |
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                        |      |      |      |      |      |  | Esc  | Del  |      | RAlt |      |
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        `----------------------------------'  `----------------------------------'
```

Access to the functional keys, which I mostly use to run `emacs`
compilation mode.

Scroll Lock is used to toggle between English and Swedish.

## Notable features on this layer

Right rotary encoder
- Press: Right Alt, rarely use this, but it is needed for the Swedish
         layout to type some symbols. But I find I mostly switch back
         to the English layout if I need to type symbols. Might change
         this in the future.
- Rotate: Moving between tabs in the browser, as described in this
          [blog post](https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-).

# Navigation Layer: Number keys, navigation
```
 // ,-------------------------------------------.                              ,-------------------------------------------.
 // |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 // |        |      |      |      |      |      |                              |      | Left | Up   | Down | Right|        |
 // |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 // |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                        |      |      |      |      |      |  |      |      |      | RCtrl|      |
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        `----------------------------------'  `----------------------------------'
```

Access to the number as well as the arrow keys. Got use to the number
row after using [ErgoDox](https://www.ergodox.io/) keyboards for a few
years. Do not feel I need a numpad layer, which seems to be quite
common with small keyboards like this.

# Adjust Layer: RGB
```
 //
 // ,-------------------------------------------.                              ,-------------------------------------------.
 // |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 // |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      |      |      |        |
 // |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 // |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        |      |      |      |      |      |  |      |      |      |      |      |
 //                        `----------------------------------'  `----------------------------------'
```

Right now it only contains adjustment to the underglow.
