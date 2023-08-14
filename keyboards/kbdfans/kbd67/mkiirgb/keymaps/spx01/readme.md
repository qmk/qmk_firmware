# spx01's KBD67 MKIIRGB Layout

This is a fairly simple QWERTY 2 layer layout, full list of particularities below:

* Besides Fn acting like a standard layer switch, CapsLock is set to switch to layer 2 while held and activate CapsLock when tapped.
* The Esc key/grave key (top left) is set to QMK's "Grave Escape" (sends Esc when tapped alone, Grave when tapped together with Shift/Ctrl/GUI), but on the 2nd layer it's set to the CK_ESCG custom keycode, acting like grave when tapped alone and as Esc when Shift is also held down. This means that there is easy access to both the characters (grave and tilde) and the Esc key while also allowing for shortcuts such as Ctrl+Shift+Esc with Ctrl+Shift+Caps+Esc (the Windows Task Manager shortcut).
* The default RGB Matrix effect is set to a custom one, RGB_STATIC, which sets a solid RGB color based on a global variable, featuring EEPROM saving and automatic loading independent on the HSV EEPROM memory that the standard effects use. This was done in order to accomodate the next feature.
* The HexRGB mode is triggered by pressing the '/' key in the second layer (CK_HEXRGB) and enables the user to type a 6 digit hexadecimal color code that is then stored as the color for the RGB_STATIC effect. If any invalid key is pressed during color input, the keymap will go back to its normal behavior without any changes to RGB.
* Besides keys representing hexadecimal digits (0-9 and a-f), there are also 2 more keys that provide functionality in the HexRGB input mode (only as a first keypress). HEXRGB_SAVE_KC (set by default to S) triggers the RGB_STATIC effect to save the currently set RGB color to EEPROM and the HEXRGB_RESET_KC (set by default to R) resets the RGB color to the one currently saved in EEPROM. These 2 keys can be reassigned in config.h.

Various 2nd layer keys:
* 1 to '+' for F1-12
* P for PrtSc/Print
* Backspace for Delete
* Home (top right key) for Insert
* E for resetting EEPROM
* '\\' for bootloader mode
* Space for toggling RGB on or off
* Right Shift for pausing media
* Left/Right for previous track/next track
* Up/Down for volume up/down

**Note: I disabled VIA in rules.mk because I don't use it, but there is enough memory space for it to be enabled.**
