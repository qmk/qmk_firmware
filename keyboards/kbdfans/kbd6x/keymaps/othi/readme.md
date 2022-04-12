## Othi's Universal HHKB keymap

### Goals
- Colemak layout. If you don't use Colemak then you'll need to also change the arrow key bindigns in other layers

- Vim-like navigation layer so you can use vim binding arrowkeys in non-vim environment

- Good modifier support so you don't have to hold 14 modifier keys at the same time

- RGB indicating layer change(only work with plain colors so far, don't put your rgb to pulsing or any non static animation)

### Layers
- **CL:**

	The base layer, default is Colemak

- **NM_MODE:**

	Vim-like arrowkeys in the home row, it's `LHNE` for *JENK Colemak* and `HJKL` for *QWERTY*

	Also `HOME`, `END` and next/prev word (`Ctrl + Left/Right`) in `0, 4, w, b` like in vim

- **VI_MODE:**

	The same as `NM_MODE` but with `KC_LSFT` held down for mostly highlighting

- **ACCENT + ACCENT_CAP:**

	Function row and Unicode characters

### Modifiers and Tap Dance keys
**LHS:**

- Any Tap Dance key with the format of `TD(XXX_NM)` act as normal XXX modifier upon hold, but will hold **and** put you to `NM_MODE` when double click hold(a tap before the hold)(eg you can produce `Alt + PgUp` by pressing `Alt + Alt + U`)

- `KC_TAB` acts as both `KC_TAB` on tap and `KC_LGUI` on hold

- R3 CapsLock acts as both `KC_BSPC` on tap and `KC_LCTL` on hold

- Holding `KC_Q` also puts you into `NM_MODE`

- Holding `KC_F` puts you into `VI_MODE` for fast function keys

**RHS:**

- 3 keys `KC_SCLN`, `KC_DOT` and `KC_SLSH` in `CL` layer can also be held down for respectively `KC_LCTL`, `KC_LSFT`, `KC_LALT` for easier 2-hand modifier holding

- Right modifiers hold the selected modifier with `KC_LGUI` at the same time, mainly for i3wm, you can change this to whatever combination you want

### Misc. functionalities

**Unicode:**

- In case the keyboard output the 4-digit codepoint instead of the actual unicode, you need to change the rewrite input mode of the keyboard into the EEPROM(you only have to do this if the EEPROM was cleared or your current machine use another unicode compose method other than IBus/Linux's `Ctrl + Shift + U`). Change the corresponding Input `void eeconfig_init_user(void)`. See [this](https://docs.qmk.fm/#/feature_unicode) for availble input modes.

- **NOTE:** make sure to keep your qmk env up to date with upstream
