byungyoonc's GMMK Pro Layout
============================

## Keymap

### Base Layer
![GMMK Pro Base Layer Layout Image](https://i.imgur.com/VvEL08Q.png)

Made a bit of a change on the leftmost side of the keyboard to set Home and End closer to the arrow keys. Also uses a shortcut for Windows Task Manager, Windows PowerToys microphone mute.

### Fn Layer
![GMMK Pro Fn Layer Layout Image](https://i.imgur.com/uQy2gSh.png)

F-row media functions roughly matches the Keychron keyboard's layout.

Added Debug key for faster debugging iteration.

Supports Secrets input by Fn + Numbers.

The rest are pretty self-explanatory RGB controls, a GUI toggle and an NKRO toggle.

## Rotary Encoder Rotation
Volume control when no mods, Ctrl+Left/Right when Ctrl is pressed while rotating the encoder.

## RGB Indicators
Uses side strap RGB as the RGB indicators. 
- Top third lights on when the Num Lock is turned off.
- Middle third lights on when the Caps Lock is turned on.
- Bottom third lights on when the GUI is disabled (via `GUI_TOG`).

## Debounce
Uses the `DEBOUNCE_TYPE` of `sym_eager_pk` for the shortest response time possible, and `DEBOUNCE` time of `40` in order to eliminate any key chattering.

## NKRO
N-key rollover is turned on by default.

## RGB Matrix
Keypresses effects are enabled.
Disabled default several RGB effects.
Added custom RGB matrix effect `saturated_solid_multisplash`.
Every keypress increases the RGB hue value.
