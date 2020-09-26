# TADA68 ISO keymap by peippo

Nordic ISO layout with faster access to cursor movement keys and brackets.

## Keymap notes

-   A few MacOS specific shortcuts, but also has a key dedicated for swapping Alt and GUI buttons for Windows use.
-   Default layer has a Grave Escape which outputs Escape when pressed normally, and `§` when Shift or Command are held. I like to setup Command+Esc to moving focus to next window (MacOS preferences, Keyboard / Shortcuts / Keyboard).
-   `Caps Lock` or `FN` can be held to access the modifier layer.

## Modifier layer

-   Additional cursor movement keys on `J/K/L/I`, and Page Up/Page Down on `U/O`.
-   Easier access to [] & {} (w/ Shift) on `8/9` (MacOS).
-   Show desktop on `D` (MacOS).
-   Screen capture tool on `S` (MacOS).
-   Media shortcuts on Arrow keys & Page Up/Page Down.
-   MacOS/Windows key for swapping Alt and GUI on both sides.
-   Backlighting adjustment (Toggle on `B`, increase/decrease on `V/B`).

### Build

To build the firmware, run `make tada68:peippo:flashbin`.
Detailed instructions at https://github.com/qmk/qmk_firmware/tree/master/keyboards/tada68
