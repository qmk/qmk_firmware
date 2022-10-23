
![Layout Image](https://github.com/rootiest/rootiest.github.io/raw/main/img/rootiest-planck_legend.png)

# The Rootiest Planck Layout

This layout takes advantage of as many QMK features as possible for a huge complicated beast of a keyboard!

## Features include

- Encoder functions further extended by layers and modifiers
- Extensive use of the on-board speaker
- Extensive use of the backlight LEDs for startup animations, layer indicators, and bootloader/debug warnings, etc
- Many layers, both toggled and momentary.
- A toggled Numpad layer, with an emphasis on coding/accounting and with arrow keys on WASD
- A "Tabular" layer accessed by holding Tab with frequently used functions, including Alt+Tab via pressing Space
- A toggled Mouse-keys layer that allows full control of the mouse movement and buttons from the keyboard
- Use of Space-Cadet Shift/Ctrl keys on various layers
- Hold enter for Right-Shift
- Shift+BackSpace for Delete
- Grave-Esc in the top-left Esc key position
- Music, Terminal, MIDI, and RGB control on Functions layer
- QWERTY, COLEMAK, DVORAK, and PLOVER layers
- Special keys for common Ctrl+ combos like Ctrl+C, Ctrl+V, etc
- Special keys for Copy-Line, Cut-Line, Delete-Line, etc
- Special keys for Ctrl+Alt+Del, Alt+F4, etc
- Settings like rgb animation state and startup animation/sound are stored in the EEPROM to survive restart
- "Sticky keys" with audible indication allow most modifiers to be locked by pressing multiple times in quick succession
- Sticky-locking the Shift key toggles CapsLock instead of locking Shift
- Unicode characters and emoji can be sent via custom tap-dance keys
- Emoji and app-specific functions can be sent via leader-key chording
- VelociKey and word-per-minute tracking are also included

See the layout here: [Keyboard Layout](http://www.keyboard-layout-editor.com/#/gists/e48e19bc251a8d07ff8475fc1a16f43b)

To build and flash this keymap, use this command:

    qmk flash -kb planck/rev6 -km rootiest
