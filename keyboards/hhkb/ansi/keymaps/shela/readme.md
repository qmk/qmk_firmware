# Shela's keymap for HHKB Pro 2 US Layout with Alternate Controller

## Layers

Layer 1: Qwerty Layer  
Layer 2: Dvorak Layer  
Layer 3: Colemak Layer  
Layer 4: Pseudo US Layer  
Layer 5: Tenkey Layer  
Layer 6: Mouse Layer  
Layer 7: HHKB Fn Layer  
Layer 8: SpaceFN Layer  

### Qwerty/Dvorak/Colemak Layer

Basic keymap layer for each keyboard layout.

### Pseudo US Layer

A layer that can be used with the same physical layout as the previously activated basic (Qwerty/Dvorak/Colemak) keymap layer, with the keyboard still configured as a Japanese keyboard on the OS.

This is useful when using virtual environments and remote desktops, because you can use Japanese Windows with the same keyboard without changing the OS keyboard settings. Also, when using the keyboard as a US keyboard on Windows OS, all keys existing only on Japanese keyboards are ignored and it is not possible to assign these keys to the desired function of any application. You can avoid such problems.

### Tenkey/Mouse Layer

Tenkey (numeric keypad) and mouse layers. For the Tenkey to work, Numlock must be turned on in the OS.

### HHKB Fn Layer

A layer that is equivalent to Fn key of Happy Hacking Keyboard. There are also some layer switching keys and special function keys.

### SpaceFN Layer

Customized [SpaceFN](https://geekhack.org/index.php?topic=51069.0) layer. There are left-hand and right-hand Arrows/Home/End/PageUp/PageDown keys. Frequently used keys in HHKB Fn layer are configured to this layer and can be used as an alternative layer to the HHKB Fn layer.

## Special function keycodes

### Pseudo US keycode

A special keycode that implements Pseudo US Layout.

### Mac mode keycode

A special keycode that toggles Mac mode. When Mac mode is enabled, the keymap of the Left Inner/Outer and Right Inner/Outer keys are changed for macOS. See _Left Inner/Outer, Right Inner/Outer keys_ for details.

### Left Inner/Outer, Right Inner/Outer keycodes

If you tap a Mod-Tap key and another key within the time specified by TAPPING_TERM, QMK interprets these keys as if they were pressed at the same time even if they were not pressed simultaneously. Therefore, for fast typists, Mod-Tap can accidentally send a keycode with modifier. These special keycodes allow you to work around this issue and change the keymap in Mac mode.

These keys work as follows:

Mac mode: Disabled

| Key         | Keycode | Tap     | Hold    |
| ----------- | ------- | ------- | ------- |
| Left Inner  | L_INNER | KC_MHEN | KC_LALT |
| Left Outer  | L_OUTER | KC_LGUI | KC_LGUI |
| Right Inner | R_INNER | KC_KANA | KC_RALT |
| Right Outer | R_OUTER | KC_RGUI | KC_RGUI |

Mac mode: Enabled

| Key         | Keycode | Tap      | Hold    |
| ----------- | ------- | -------- | ------- |
| Left Inner  | L_INNER | KC_LANG2 | KC_LCMD |
| Left Outer  | L_OUTER | KC_LOPT  | KC_LOPT |
| Right Inner | R_INNER | KC_LANG1 | KC_RCMD |
| Right Outer | R_OUTER | KC_ROPT  | KC_ROPT |
