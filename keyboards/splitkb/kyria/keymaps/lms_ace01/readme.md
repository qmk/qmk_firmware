# AceVice One's Keymap for [Kyria](https://github.com/splitkb/kyria)

## Introduction

This is my first personal keymap for Kyria with a little bunch of *steroids*.

The hardware build implements 2 rotatory encoders and 2 OLED displays.

## Features

These are some of the generic features built in:

- Two alternative default character distributions (**QWERTY**, **COLEMAK**) with *Spanish* layout.
- Layer selection on some keys (**Esc**, **Lower**, **Space**, **Enter**, **Raise**).
- Multiple selectable layers:
  - **Symbols**: Numbers on top row, common programming symbols (curly, square and angle brackets, parentheses, at and hash) on bottom row with symmetric distribution (open on left, close on right).
  - **Function**/**Numpad**: Function keys on left side, Number Pad on right side.
  - **Navigation**: Mouse keys on left side, Navigation keys on right side.
  - **Git commands**: The most common and useful Git commands at your fingertips.
  - **Settings**: Select default distribution, Media keys, RGB settings.
- Symmetric design -left/right side- for modifiers (**Shift**, **Ctrl**, **Alt** and **GUI**).
- **Arrows**/**Modifiers** on same keys (right side).
- **Tab**/**Caps Lock** key.
- **Backspace**/**Delete** with **Insert**/**Overwrite** selectable mode on same key.
- **Single/Double Quote** (`' "`) on same key as English layouts.
- Handedness set by EEPROM.
- Mouse Keys has been disabled by default for space saving (Pro Micro controller limit).

Some of the more specific features are described below:

### Tap Dance

- Use of `ACTION_TAP_DANCE_DOUBLE()` for **Tab**/**Caps Lock** key.
- Implementation of new `ACTION_TAP_DANCE_FN_ADVANCED_USER()` function:
  - Any user data can be sent to personalized functions.
  - Generalized design makes action reuse easy.
  - User can tap a keycode and/or layer selection (single tap, single hold, double tap) depending on modifiers (**None**, **Shift**, **Ctrl**).

### OLEDs

Master-side OLED displays dynamic data:

- Current layer.
- Modifiers state (lock mode included).
- Caps Lock state.
- Insert/Overwrite state.

Slave-side OLED displays horizontal scrolling Kyria logo.

### Rotary Encoders

Encoders click buttons for mode changing. Supported modes are:

- Character Left / Right, Line Up / Down.
- Word Left / Right, Page Up / Down.
- Tabbing Left / Right (Navigator, Editor).
- Volume Up / Down.

## TODO list

- [x] Show modifiers in OLED when triggered as One Shot keys
- [x] Manage Backspace key with dual funcion (Delete when shifted)
- [x] OLED modifier status bar one line down
- [x] Show INS/OWR Mode in right OLED
- [x] Show RGB Led Settings on OLED when Settings layer on
- [x] Show Locked Modifiers (Shift, Control, Alt, GUI)
- [x] Arrow keys on right modifier keys
- [x] Improve Esc/Layer Symbol: Tap -> Keycode, Hold -> Momentary Layer, Double Tap -> Toggler Layer
- [x] Check transparent keys on all layers (avoid collateral effects)
- [x] Add "Print Screen" / "Scroll Lock" / "Pause Break" keys on Navigation layer
- [x] Add Basic characters layers: COLEMAK (ES)
- [x] Create custom keycode with quotes (single/double) for ES layout
- [x] Add Tap-Dance actions for keycodes (Tab, Space, Enter) and layer selection
- [x] Add Git commands to some layer
- [x] Disable Mouse Keys (saving space)
- [x] Settings Layer not accesible
- [x] Layer buttons with double/triple function (Normal/Shift/Control mode)
- [x] Tab/Caps Lock on same key (single/double tap)
- [x] Backspace/Delete/Insert on same key (Normal/Shift/Ctrl)
- [x] Separate default layer from RGB settings rendering for conditional compiling
- [x] Encoders: Improve with more functionality (modes)
- [ ] Encoders: Add mode for navigation through windows (applications)
- [ ] Show more info about RGB Led Settings (On/Off, Animation, ...)
- [ ] Activate "Nums Lock" when Fn/NumPad layer locked
- [ ] Show status indicator when locked layer
- [ ] Set RGB Led Color by selected Layer (activable)
- [ ] Add more uses for left OLED
- [ ] Something strange returning from One Shot hold

## Acknowledgements

Thanks to the entire QMK community for your invaluable help.
