# The default keymap for Bemeier BMEK

![KLE Screenshot](https://i.imgur.com/muzFPRm.png)

[KLE Link](http://www.keyboard-layout-editor.com/#/gists/a86f8f85d044fc4734a2eea969d33de5)

This layout comes with five layers.  
- DF: A Base layer defaulting to macOS style modifiers;
- WL: An alternative default layer with windows-style modifiers
- MF & WF: Function layers, specific for macOS and Windows to make shorcuts like switching between desktops consistent.
- CL: Configuration layer (reached by pressing space from a function layer). For reset, clear eeprom, enable/disable LEDs, configure layer indicator color, brightness and saturation (see special keycodes below):

## Special Keycodes

Keyboard specific (see bmek.h/c):  
- BM_RST: Reset keyboard
- BM_LED: Toggle LEDs on/off completly
- BM_WIPE: Wipe & reset EEPROM to defaults
- BM_HI_1(-4): Increase hue used in LED layer indicator when layer 1 (2/3/4) is highest active layer.
- BM_HD_1(-4): Decrease hue used in LED layer indicator when layer 1 (2/3/4) is highest active layer.
- BM_FI-BM_FD: LED layer indicator shows a slight gradient, this increases/decreases the gradient (0 is solid color).
- BM_BI/BM_BD: Increase/decrease brightness of LED layer indicator
- BM_SI/BM_SD: Increase/decrease saturation of LED layer indicator

User/layout specific (see keymap.c):
- TOG_OS: Toggle between DF (macOS) and WF (Windows) default layer.
- ATAB_I/ATAB_D: Alt-Tab (or CMD-Tab on macOS) shortcuts for single key application switching.
- MF_SPC/WF_SPC: Space key when tapped, os-specific function layer when held.
- MN_B: B key when tapped, CMD+shift when held (macOS - Ctrl+Shift on windows).
- MN_UP: Ctrl+Up = App expose (all apps)
- MN_DOWN: Ctrl+Down = App expose (current app)
- MN_LEFT/MN_RGHT: Ctrl+Left/Right = switch worspace to left/right
- MN_SRCH: Search
- MN_CESC: ESC when tapped, CMD when held.
- MN_UNDO: CMD-Z
- MN_COPY: CMD-C
- MN_CUT: CMD-X
- MN_PASTE: CMD-V

All MN prefixed keycodes also have a WN version that create the same behaviour on Windows.
