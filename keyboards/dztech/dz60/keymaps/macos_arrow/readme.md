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
|  `  | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   | -   | =   | Backspace |
|-----------------------------------------------------------------------------------------+
| Tab    | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | [   | ]   |   \    |
|-----------------------------------------------------------------------------------------+
| _FL/Esc  | A   | S   | D   | F   | G   | H   | J   | K   | L   | ;   | '   | Enter      |
|-----------------------------------------------------------------------------------------+
| Shift     | Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   |     | Up  |Shift|
|-----------------------------------------------------------------------------------------+
| Ctrl | Alt  | Cmd  |            _NL / Space             |Cmd/_ML| Alt | Left| Down|Right|
`-----------------------------------------------------------------------------------------'
```

* The escape key is moved to the capslock to get keep grave letter pristine.
* The `Caps-Lock` (`Hyper`) key switch to the function layer (`_FL`) or escape when used alone.
* The right `Cmd` key is used to switch to the media layer (`_ML`) when used with keys mapped on that layer.
* The space key can be used to switch to the numpad layer (`_NL`) when used with one of the mapped key on that layer.

## Function Layer (_FL)

```
,-----------------------------------------------------------------------------------------.
|  `  | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |    Del    |
|-----------------------------------------------------------------------------------------+
|        |     |     |     |     |     |     |PgDwn| PgUp|     |     |     |     |        |
|-----------------------------------------------------------------------------------------+
|          |     |     |     |     |     | Left| Down| Up  |Right|     |     |            |
|-----------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |     |     |     |     |     |     |
|-----------------------------------------------------------------------------------------+
|      |      |      |                                      |     |     |     |     |     |
`-----------------------------------------------------------------------------------------'
```

The function layer is activated by the `Caps-Lock` (`Hyper`) key to access `F` keys. In addition, the `HJKL` are mapped as cursor keys on that layer.

## Media Layer (_ML)

```
,-----------------------------------------------------------------------------------------.
|Eject| BR- | BR+ |     |     |     |     |PREV |PLAY |NEXT |MUTE | V- | V+ |             |
|-----------------------------------------------------------------------------------------+
|        |     |     |     |     |     |     |     |     |     |     |     |     |  Reset |
|-----------------------------------------------------------------------------------------+
|          |     |     |     |     |     |     |     |     |     |     |     |            |
|-----------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |     |     |     |     |     |     |
|-----------------------------------------------------------------------------------------+
|      |      |      |                                      |     |     |     |     |     |
`-----------------------------------------------------------------------------------------'
```

The media layer is activated by the right `Cmd` (`FN`) key. It contains the typical macos media keys on the top row. Blank keys act as `Cmd+` that key on the base layer.

## Numpad Layer (_NL)

```
,-----------------------------------------------------------------------------------------.
|     |     |     |     |     |     |     |     |  %  |  (  |  )  |  < |  > |             |
|-----------------------------------------------------------------------------------------+
|        |     |     |     |     |     |     |  *  |  0  |  1  |  2  |  3  |     |        |
|-----------------------------------------------------------------------------------------+
|          |     |     |     |     |     |     |  .  |  -  |  4  |  5  |  6  |            |
|-----------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |  ,  |  =  |  7  |  8  |  9  |     |     |
|-----------------------------------------------------------------------------------------+
|      |      |      |                                      |     |     |     |     |     |
`-----------------------------------------------------------------------------------------'
```

The numpad layer is activated by the space bar, when hold.