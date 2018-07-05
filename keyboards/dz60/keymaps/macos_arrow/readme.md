# Macos keymap with arrow

This is a keymap for DZ60 configured with arrows using the layout below:

[![](https://poitr.us/mARFK9+)](http://www.keyboard-layout-editor.com/#/gists/07d924064c77c0ff43de6b8a9519f931)

My build used the following components:
* DZ60 PCB
* [Stainless steel alu plate option A with 2U left shift](https://www.aliexpress.com/item/Alu-plate-dz60-plate-for-DIY-mechanical-keyboard/32827595666.html) (optional)
* [YMDK customized 61 64 68 ANSI keyset](https://www.amazon.com/Customized-Keyset-Profile-Mechanical-Keyboard/dp/B0777LMKKK)
* 60 Cherry MX Clear for the main keys + 10 Cherry MX Grey for the large keys
* [The wood case for DZ60](https://www.aliexpress.com/item/GH60-Keyboard-Wood-Case-PCB-Board-Position-Plate-Satellite-Axis-And-Walnut-Wood-Wrist-Rest-For/32836566852.html) (optional)

## Base Layer

```
,-----------------------------------------------------------------------------------------.
| Esc | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   | -   | =   | Backspace |
|-----------------------------------------------------------------------------------------+
| Tab    | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | [   | ]   |   \    |
|-----------------------------------------------------------------------------------------+
| _FL      | A   | S   | D   | F   | G   | H   | J   | K   | L   | ;   | '   | Enter      |
|-----------------------------------------------------------------------------------------+
| Shift     | Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   | _ML | Up  |Shift|
|-----------------------------------------------------------------------------------------+
| Ctrl | Alt  | Cmd  |                Space               |Cmd/_ML| Alt | Left| Down|Right|
`-----------------------------------------------------------------------------------------'
```

* The escape key use `KC_GESC` to get grave accent on any letter with ``Alt+Esc`` and `` ` `` alone with the ``Hyper+Esc``. The `~` is obtained with `Shift+Esc`. `GRAVE_ESC_GUI_OVERRIDE` is define so `Cmd+Alt+Esc` can still work.
* The `Caps-Lock` (`Hyper`) key switch to the function layer (`_FL`).
* The right `Cmd` key is used to switch to the media layer (`_ML`) when used with keys mapped on that layer (the top row). Any other keys just act as a `Cmd+` that key.

## Function Layer (_FL)

```
,-----------------------------------------------------------------------------------------.
|  `  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |    Del    |
|-----------------------------------------------------------------------------------------+
|        |     |     |     |     |     |     |     | UP  |     |     |     |     |  Reset |
|-----------------------------------------------------------------------------------------+
|          |     |     |     |     |     |     | Left| Down|Right|     |     |            |
|-----------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |     |     |     |     |     |     |
|-----------------------------------------------------------------------------------------+
|      |      |      |                                      |     |     |     |     |     |
`-----------------------------------------------------------------------------------------'
```

The function layer is activated by the `Caps-Lock` (`Hyper`) key to access `F` keys. In addition, the `IJKL` are mapped as cursor keys on that layer.

## Media Layer (_ML)

```
,-----------------------------------------------------------------------------------------.
|     | BR- | BR+ | F3  | F4  |     |     |PREV |PLAY |NEXT |MUTE | V- | V+ |    Eject    |
|-----------------------------------------------------------------------------------------+
|        |     |     |     |     |     |     |     |     |     |     |     |     |        |
|-----------------------------------------------------------------------------------------+
|          |     |     |     |     |     |     |     |     |     |     |     |            |
|-----------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |     |     |     |     |     |     |
|-----------------------------------------------------------------------------------------+
|      |      |      |                                      |     |     |     |     |     |
`-----------------------------------------------------------------------------------------'
```

The media layer is activated by the right `Cmd` (`FN`) key. It contains the typical macos media keys on the top row. Blank keys act as `Cmd+` that key on the base layer.


