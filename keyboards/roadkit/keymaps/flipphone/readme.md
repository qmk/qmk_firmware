# Flip Phone layout for Roadkit

Uses the numpad with classic cellular phone style letters assigned to the numbers.

# LAYERS

* Numpad - The layer that matches the caps mostly
* FPH - Base layer for text
* FPHNOISY - Text layer that outputs every character and then backspaces as they're replaced
* DYN - dynamic macro layer for recording and playing macros

## T9

Poke the "2" key twice and it makes "B".

## T9NOISY

Poke the "2" key twice and it makes "A"+backspace+"B" so you can see it cycle through.

## MACROS

May be able to record macros with the T9 layer because the "KC_*"s are only sent
at the end.  Trying to do a macro with T9NOISY would probably fill up the buffer
in just a few characters.
