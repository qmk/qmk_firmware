Planck keyboard firmware
======================
DIY/Assembled compact ortholinear 40% keyboard by [Ortholinear Keyboards](http://ortholinearkeyboards.com).

## Quantum MK Firmware
You have access to a bunch of goodies! Check out the Makefile to enable/disable some of the features. Uncomment the `#` to enable them. Setting them to `no` does nothing and will only confuse future you.

    BACKLIGHT_ENABLE = yes # Enable keyboard backlight functionality
    MIDI_ENABLE = yes      # MIDI controls
    # UNICODE_ENABLE = yes # Unicode support
    BLUETOOTH_ENABLE = yes # Enable Bluetooth with the Adafruit EZ-Key HID

### Mod shortcuts

* `LSFT(kc)` - applies left shift to *kc* - `S(kc)` is an alias
* `RSFT(kc)` - applies right shift to *kc*
* `LCTL(kc)` - applies left control to *kc*
* `RCTL(kc)` - applies right control to *kc*
* `LALT(kc)` - applies left alt to *kc*
* `RALT(kc)` - applies right alt to *kc*
* `LGUI(kc)` - applies left gui (command/win) to *kc*
* `RGUI(kc)` - applies right gui (command/win) to *kc*

You can also use more than one, like this:

    LALT(LGUI(KC_ESC))

The following shortcuts automatically add `LSFT()` to keycodes to get commonly used symbols. Their long names (see `quantum/keymap_common.h`) are also availble.

    KC_TILD  ~
    KC_EXLM  !
    KC_AT    @
    KC_HASH  #
    KC_DLR   $
    KC_PERC  %
    KC_CIRC  ^
    KC_AMPR  &
    KC_ASTR  *
    KC_LPRN  (
    KC_RPRN  )
    KC_UNDS  _
    KC_PLUS  +
    KC_LCBR  {
    KC_RCBR  }
    KC_PIPE  |
    KC_COLN  :

### Function shortcuts

Instead of using `FNx`, you can use `F(x)` - the benefit here is being able to use more than 32 function layers (up to 4096), if you happen to need them.

There are also keycode shortcuts for common actions:

* `MO(layer)` - momentary switch to *layer*
* `DF(layer)` - sets default layer to *layer*
* `TG(layer)` - toggle between the current layer and *layer*
* `MT(mod, kc)` - is *mod* when held, and *kc* when tapped
  * `CTL_T(kc)` - is LCTL when held and *kc* when tapped 
  * `SFT_T(kc)` - is LSFT when held and *kc* when tapped 
  * `ALT_T(kc)` - is LALT when held and *kc* when tapped 
  * `GUI_T(kc)` - is LGUI when held and *kc* when tapped 
  * `ALL_T(kc)` - is Hyper (all mods) when held and *kc* when tapped 
* `LT(layer, kc)` - momentary switch to *layer* when held, and *kc* when tapped

These functions work the same way that their `ACTION_*` functions do, and will require KC_TRNS on the layer being switched to - check out the default keymap for an example.

### Additional keycodes for software-implemented layouts (Colemak, Dvorak, etc)

Everything is assuming you're in Qwerty (in software) by default, but there is built-in support for using a Colemak or Dvorak layout by including this at the top of your keymap:

     #include "keymap_<layout>.h"
     
Where <layout> is "colemak" or "dvorak". After including this line, you will get access to:
 
 * `CM_*` for all of the Colemak-equivalent characters
 * `DV_*` for all of the Dvorak-equivalent characters
 
These implementations assume you're using Colemak or Dvorak on your OS, not on your keyboard - this is referred to as a software-implemented layout. If your computer is in Qwerty and your keymap is in Colemak or Dvorak, this is referred to as a firmware-implemented layout, and you won't need these features. 

To give an example, if you're using software-implemented Colemak, and want to get an `F`, you would use `CM_F` - `KC_F` under these same circumstances would result in `T`.

### Additional language support

In `quantum/keymap_extras/`, you'll see various language files - these work the same way as the alternative layout ones do. Most are defined by their two letter country/language code followed by an underscore and a 4-letter abbrivation of its name. `FR_UGRV` which will result in a `ù` when using a software-implemented AZERTY layout. It's currently difficult to send such characters in just the firmware (but it's being worked on - see Unicode support).

### Unicode support

You can currently send 4 hex digits with your OS-specific modifier key (RALT for OSX with the "Unicode Hex Input" layout) - this is currently limited to supporting one OS at a time, and requires a recompile for switching. 8 digit hex codes are being worked on. The keycode function is `UC(n)`, where *n* is a 4 digit hexidecimal. Enable from the Makefile.

### Macro shortcuts

Instead of using the `ACTION_MACRO` function, you can simply use `M(n)` to access macro *n* - *n* will get passed into the `action_get_macro` as the `id`, and you can use a switch statement to filter them. This gets called on the keydown and keyup, so you'll need to use an if statement testing `record->event.pressed` (see keymap_default.c).

### Other keyboard shortcut keycodes

* `RESET` - puts the MCU in DFU mode for flashing new firmware (with `make dfu`)
* `DEBUG` - the firmware into debug mode - you'll need hid_listen to see things
* `BL_ON` - turns the backlight on
* `BL_OFF` - turns the backlight off
* `BL_<n>` - sets the backlight to level *n*
* `BL_INC` - increments the backlight level by one
* `BL_DEC` - decrements the backlight level by one
* `BL_TOGG` - toggles the backlight
* `BL_STEP` - steps through the backlight levels

Enable the backlight from the Makefile.


### MIDI functionalty

This is still a WIP, but check out `quantum/keymap_midi.c` to see what's happening. Enable from the Makefile.

### Bluetooth functionality

This requires [some hardware changes](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts), but can be enabled via the Makefile. The firmware will still output characters via USB, so be aware of this when charging via a computer. It would make sense to have a switch on the Bluefruit to turn it off at will.

## Building

Download or clone the whole firmware and navigate to the keyboard/planck folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use `make dfu` to program your PCB once you hit the reset button. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document (you can find in top README.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with `KEYMAP` option like:
```
$ make KEYMAP=[default|jack|<name>]
```
Keymaps follow the format **__keymap\_\<name\>.c__** and are stored in the `keymaps` folder.

### Notable forks (which some of the keymap files are from)
- [Shane's Fork](https://github.com/shanecelis/tmk_keyboard/tree/master/keyboard/planck)
- [Pierre's Fork](https://github.com/pcarrier/tmk_keyboard/blob/pcarrier/planck/keyboard/gh60/keymap_planck.c)
- [Nathan's Fork](https://github.com/nathanrosspowell/tmk_keyboard/tree/planck-jack/keyboard/planck)
- [Matthew's Fork](https://github.com/pepers/tmk_keyboard/tree/master/keyboard/planck_grid)
