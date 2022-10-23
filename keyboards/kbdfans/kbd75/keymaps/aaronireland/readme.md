# Aaron's KBD75v2 Mac-friendly ANSI 1u Layout

This layout mimics the default KBD 75% ANSI 1u layout with a few mac-friendly tweaks. Because Mac OS uses a unique keycode
for the Function key and only recognizes that keycode from keyboards registered with an Apple vendor ID ([see here for more info](https://beta.docs.qmk.fm/faqs/faq_keymap#fn-key-on-macos)),
this layout uses custom macros and F-keycodes (F12, F13, etc) to provide Mac hotbar functionality (Print Screen, Launchpad, etc...) and maps the
**Fn** key to the QMK momentary layer `_FN` (layer index 3) so it is listed as `MO(3)`.

| Mac OS Keystroke | Description              | User-defined Macro | Layout Mapping   |
| ---------------- | ------------------------ | ------------------ | ---------------- |
| ⌘ + Shift + 3    | Print Screen             | `KC_CAPW`          | `Prt Scn`        |
| ⌘ + Shift + 4    | Print Screen (selection) | `KC_CAPP`          | `fn` + `Prt Scn` |
| F13              | Launchpad                |                    | `fn` + `Home`    |
|                  | Colemak                  | `COLEMAK`          | `fn` + `C`       |
|                  | Dvorak                   | `DVORAK`           | `fn` + `D`       |
|                  | Qwerty                   | `QWERTY`           | `fn` + `Q`       |
| `Ctrl` + `C`     | Quit/Break               | `KC_CTLC`          | `Pse Brk`        |
| `Ctrl` + `B`     | vim page up              | `KC_SPU`           | `fn` + `Pg Up`   |
| `Ctrl` + `D`     | vim page down            | `KC_SPD`           | `fn` + `Pg Dn`   |

<br>
<hr>

### QWERTY - Layer 0

![Layer 0: QWERTY](https://i.imgur.com/haydhHS.png)

### FUNCTION - Layer 3

![Layer 3: FUNCTION](https://i.imgur.com/XHUvgLd.png)

<br><br><hr>

### COLEMAK - Layer 1

![Layer 1: COLEMAK](https://i.imgur.com/sBfHH8K.png)

### DVORAK - Layer 2

![Layer 2: DVORAK](https://i.imgur.com/AaypaN4.png)
