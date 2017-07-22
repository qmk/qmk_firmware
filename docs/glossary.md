# Glossary of QMK terms

## Dynamic Macro
A macro which has been recorded on the keyboard and which will be lost when the keyboard is unplugged or the computer rebooted.

## git
Versioning software used at the commandline

## Keycode
A 2-byte number that represents a particular key. `0x00`-`0xFF` are used for [Basic Keycodes](keycodes.html) while `0x100`-`0xFFFF` are used for [Quantum Keycodes](quantum_keycodes.html).

## Keymap
An array of keycodes mapped to a physical keyboard layout, which are processed on key presses and releases

## Matrix
A wiring pattern of columns and rows (and usually diodes) that enables the MCU to detect keypresses with a fewer number of pins

## Macro
A feature that lets you send muiltple keypress events (hid reports) after having pressed only a single key.

## Mousekeys
A feature that lets you control your mouse cursor and click from your keyboard.

* [Mousekeys Documentation](mouse_keys.html)

## Tap Dance
A feature that lets you assign muiltple keycodes to the same key based on how many times you press it.

* [Tap Dance Documentation](tap_dance.html)
