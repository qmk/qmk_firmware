# Aurora Sweep's Default Keymap

A chord-based keymap for effective typing
===

While the default keymap makes heavy use of held keys as layer switches, this keymap instead prioritises chords.
It uses set keys to navigate up and down layers and emphasises the thumb keys as modifiers.
The idea is to avoid having to hold keys for extended periods or have too many layers to remember.

It makes the _super_ modifier always available for use with i3wm or equivalent window managers.

Layer map
---

The thumb buttons are the same in all layers for consistency and access to modifiers.
This keymap is not designed around one-handed use.

### Layer 0: typing

This base layer is intended for a convenient typing experience which provides alphabetic characters, whitespace, and common punctuation in an accessible manner.

### Layer 1: numbers & symbols

It is common to need access to numbers and symbols, whether for general typing, regular expressions, window manager commands, or suchlike.
As such, having access to modifier keys and these characters on a single layer is beneficial.

### Layer 2: navigation

QMK supports mouse emulation.
This layer makes use of that and other navigation tools, such as arrow keys.

### Layer 3: function keys

The assumption is that function keys, whilst useful, are used infrequently and thus can be relegated to a less accessible layer.
This layer also controls the RGB LEDs, if available.
