# Paul's Ferris Keymap

My Ferris keymap has the following objectives:

- Limit the use of mod-tap to reduce typing latency.
- Limit the number of layers, although this is not as minimalist as other layouts.
- Optimise for MacOS, Typescript development use; for my day job.
- Use combos for commonly used shortcuts to further reduce layer switching.

To achieve the objectives the keymap has the following layers:

1. Base (QT), aka Qwerty.
1. Navigation (NV) and shortcuts.
1. Symbols (SB).
1. Numbers (NU).

Details concerning what's unique about each layer is presented in the following
subsections.

To view the full layout, see [Keyboard layout editor](http://www.keyboard-layout-editor.com/#/gists/cb5daf091e88d37b1c169cd36d01ae9c).

# Base (QT)

![Base layer](https://i.imgur.com/ZiZ5upv.png)
 
 The base layer contains the alphabet layed out in Qwerty format.

 In terms of base layer symbols, `'` has been chosen for the base layer instead
 of `;`, which has been moved to the symbols layer.

 All layer toggles are on this base layer.

 The only two mod-tap keys in the whole layout are on this layer. They are:

 - `Shift` / `Z`
 - `Shift` / `/`

These keys are mod-tapped to correspond to the lower pinky position of shift
keys on a normal keyboard.

Other common base layer keys such as escape, tab, enter, are available in the
navigation layer or as combos.

 ## Combos

All combos are based on base layer key combinations. However, they fall into two
main categories. Those that map to simple keys and those that map to shortcuts.

The general pattern is that keys rely on horizontal combos and shortcuts rely on
vertical combos.

### Key Combos

![Key combos](https://i.imgur.com/449LcPG.png)

Key combos enable access to keys that are normally on a base layer on a larger
keyboard without needing to switch layers in this layout.

|Key|Combo|
|---|---|
|Tab|`Q` + `W`|
|Escape|`A` + `S`|
|Backspace|`O` + `P`|
|Enter|`L` + `'`|

### Shortcut Combos

![Shortcut combos](https://i.imgur.com/RNzVIEi.png)

Shortcut combos are aimed at reducing the number of keystrokes needed to perform
common (for me) shortcuts. Because modifiers are mapped to the navigation layer,
it means that without combos, to do something like copy requires pressing three
keys with two hands in a specific sequence. Having combos instead for shortcuts
reduces the mental overhead needed to do these quickly.

|Shortcut|Keys|Combo|
|---|---|---|
|Copy|⌘-C|`D` + `C`|
|Cut|⌘-X|`S` + `X`|
|Paste|⌘-V|`F` + `V`|
|Save|⌘-S|`W` + `S`|
|Undo|⌘-Z|`A` + `Z`|

# Navigation (NV) And Shortcuts

![Navigation layer](https://i.imgur.com/U5ZuX4t.png)

Navigation and shortcuts contain basic VIM-like navigation keys with HJKL,
modifiers, tab, escape, etc. as well as some shortcut keys.

The key layout in this layer was intended to reduce layout learning curve by
trying to map as many non-alpha control keys to familiar locations.

This means that tab, escape, modifiers, delete, backspace, and enter are all
around the edges of the keyboard.

It should be noted that shift has been mapped to the location of `V` and only on
one side. The reasoning for this is to enable pressing of double-shift, which is
the *Search Everywhere* shortcut in WebStorm. As an experiment in trying to get
rid of mod-tap shift on the base layer, there is a one-shot-mod shift mapped to
the `F` position too.

In terms of shortcuts, the following have been included:

|Shortcut|Keys|Base Key Location|
|---|---|---|
|Back-search in Bash/Zsh|⌃-R|`R`|
|Delete previous word|⌥-⌫|Right-hand left thumb key|
|Hyper|⌃-⌥-⌘-⇧|Right-hand right thumb key|
|Next application window|⌘-\`|`W`|
|Next word|⌥-→|`M`|
|Previous word|⌥-←|`N`|
|Spotlight|⌘-(Space)|`S`|
|TMux Prefix|⌃-B|`B`|

# Numbers

![Numbers layer](https://i.imgur.com/fhwRQ8z.png)

The numbers layer attempts to provide a numpad on the right-hand side and
function keys layed out in a similar numpad style on the left-hand side. 

# Symbols

![Symbols layer](https://i.imgur.com/PgJMAW2.png)

The purpose of the symbol layer is to allow for symbols to be typed without
needing to press shift.

For bracket-like symbols, they are also paired to allow for rolls and avoid same
finger bigrams.

Symbols that are present on the base layer are not reproduced on this layer.
