atreus keyboard firmware
======================

## Quantum MK Firmware

You have access to a bunch of goodies! Check out the Makefile to enable/disable some of the features. Uncomment the `#` to enable them. Setting them to `no` does nothing and will only confuse future you.

    BACKLIGHT_ENABLE = yes # Enable keyboard backlight functionality
    MIDI_ENABLE = yes      # MIDI controls
    # UNICODE_ENABLE = yes # Unicode support - this is commented out, just as an example. You have to use #, not //
    BLUETOOTH_ENABLE = yes # Enable Bluetooth with the Adafruit EZ-Key HID

## Atreus specific information

These configuration files are specifically for the Atreus keyboards created by Phil Hagelberg (@technomancy). This keyboard is available in two variants: one powered by a Teensy 2, one powered by an A-Star. This repository currently assumes that you have an A-Star powered Atreus. If you are using a Teensy2, specify that by adding `TEENSY2=yes` to your `make` commands.

If you are coming from the [atreus-firmware](https://github.com/technomancy/atreus-firmware), we've also brought forward the `make upload` command for you to use.

## Quick aliases to common actions

Your keymap can include shortcuts to common operations (called "function actions" in tmk).

### Switching and toggling layers

`MO(layer)` - momentary switch to *layer*. As soon as you let go of the key, the layer is deactivated and you pop back out to the previous layer. When you apply this to a key, that same key must be set as `KC_TRNS` on the destination layer. Otherwise, you won't make it back to the original layer when you release the key (and you'll get a keycode sent). You can only switch to layers *above* your current layer. If you're on layer 0 and you use `MO(1)`, that will switch to layer 1 just fine. But if you include `MO(3)` on layer 5, that won't do anything for you -- because layer 3 is lower than layer 5 on the stack.

`LT(layer, kc)` - momentary switch to *layer* when held, and *kc* when tapped. Like `MO()`, this only works upwards in the layer stack (`layer` must be higher than the current layer).

`TG(layer)` - toggles a layer on or off. As with `MO()`, you should set this key as `KC_TRNS` in the destination layer so that tapping it again actually toggles back to the original layer. Only works upwards in the layer stack.

### Fun with modifier keys

* `LSFT(kc)` - applies left Shift to *kc* (keycode) - `S(kc)` is an alias
* `RSFT(kc)` - applies right Shift to *kc*
* `LCTL(kc)` - applies left Control to *kc*
* `RCTL(kc)` - applies right Control to *kc*
* `LALT(kc)` - applies left Alt to *kc*
* `RALT(kc)` - applies right Alt to *kc*
* `LGUI(kc)` - applies left GUI (command/win) to *kc*
* `RGUI(kc)` - applies right GUI (command/win) to *kc*

You can also chain these, like this:

    LALT(LCTL(KC_DEL)) -- this makes a key that sends Alt, Control, and Delete in a single keypress.

The following shortcuts automatically add `LSFT()` to keycodes to get commonly used symbols. Their long names are also available and documented in `/quantum/keymap_common.h`.

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

`MT(mod, kc)` - is *mod* (modifier key - MOD_LCTL, MOD_LSFT) when held, and *kc* when tapped. In other words, you can have a key that sends Esc (or the letter O or whatever) when you tap it, but works as a Control key or a Shift key when you hold it down. 

These are the values you can use for the `mod` in `MT()` (right-hand modifiers are not available):

  * MOD_LCTL
  * MOD_LSFT
  * MOD_LALT
  * MOD_LGUI

These can also be combined like `MOD_LCTL | MOD_LSFT` e.g. `MT(MOD_LCTL | MOD_LSFT, KC_ESC)` which would activate Control and Shift when held, and send Escape when tapped.

We've added shortcuts to make common modifier/tap (mod-tap) mappings more compact:

  * `CTL_T(kc)` - is LCTL when held and *kc* when tapped 
  * `SFT_T(kc)` - is LSFT when held and *kc* when tapped 
  * `ALT_T(kc)` - is LALT when held and *kc* when tapped 
  * `GUI_T(kc)` - is LGUI when held and *kc* when tapped 
  * `ALL_T(kc)` - is Hyper (all mods) when held and *kc* when tapped. To read more about what you can do with a Hyper key, see [this blog post by Brett Terpstra](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)

### Temporarily setting the default layer 

`DF(layer)` - sets default layer to *layer*. The default layer is the one at the "bottom" of the layer stack - the ultimate fallback layer. This currently does not persist over power loss. When you plug the keyboard back in, layer 0 will always be the default. It is theoretically possible to work around that, but that's not what `DF` does.

### Remember: These are just aliases

These functions work the same way that their `ACTION_*` functions do - they're just quick aliases. To dig into all of the tmk ACTION_* functions, please see the [TMK documentation](https://github.com/jackhumbert/qmk_firmware/blob/master/tmk_core/doc/keymap.md#2-action).

Instead of using `FNx` when defining `ACTION_*` functions, you can use `F(x)` - the benefit here is being able to use more than 32 function actions (up to 4096), if you happen to need them.

## Macro shortcuts: Send a whole string when pressing just one key

Instead of using the `ACTION_MACRO` function, you can simply use `M(n)` to access macro *n* - *n* will get passed into the `action_get_macro` as the `id`, and you can use a switch statement to trigger it. This gets called on the keydown and keyup, so you'll need to use an if statement testing `record->event.pressed` (see keymap_default.c).

```c
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END  ); // this sends the string 'hello' when the macro executes
      } 
      break;
  }
  return MACRO_NONE;
};
```
A macro can include the following commands:

* I() change interval of stroke in milliseconds.
* D() press key.
* U() release key.
* T() type key(press and release).
* W() wait (milliseconds).
* END end mark.

So above you can see the stroke interval changed to 255ms between each keystroke, then a bunch of keys being typed, waits a while, then the macro ends.

Note: Using macros to have your keyboard send passwords for you is a bad idea.

### Additional keycode aliases for software-implemented layouts (Colemak, Dvorak, etc)

Everything is assuming you're in Qwerty (in software) by default, but there is built-in support for using a Colemak or Dvorak layout by including this at the top of your keymap:

   #include "keymap_<layout>.h"

Where <layout> is "colemak" or "dvorak". After including this line, you will get access to:
 
 * `CM_*` for all of the Colemak-equivalent characters
 * `DV_*` for all of the Dvorak-equivalent characters
 
These implementations assume you're using Colemak or Dvorak on your OS, not on your keyboard - this is referred to as a software-implemented layout. If your computer is in Qwerty and your keymap is in Colemak or Dvorak, this is referred to as a firmware-implemented layout, and you won't need these features. 

To give an example, if you're using software-implemented Colemak, and want to get an `F`, you would use `CM_F` - `KC_F` under these same circumstances would result in `T`.

## Additional language support

In `quantum/keymap_extras/`, you'll see various language files - these work the same way as the alternative layout ones do. Most are defined by their two letter country/language code followed by an underscore and a 4-letter abbreviation of its name. `FR_UGRV` which will result in a `ù` when using a software-implemented AZERTY layout. It's currently difficult to send such characters in just the firmware (but it's being worked on - see Unicode support).

## Unicode support

You can currently send 4 hex digits with your OS-specific modifier key (RALT for OSX with the "Unicode Hex Input" layout) - this is currently limited to supporting one OS at a time, and requires a recompile for switching. 8 digit hex codes are being worked on. The keycode function is `UC(n)`, where *n* is a 4 digit hexidecimal. Enable from the Makefile.

## Other firmware shortcut keycodes

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

## MIDI functionalty

This is still a WIP, but check out `quantum/keymap_midi.c` to see what's happening. Enable from the Makefile.

## Bluetooth functionality

This requires [some hardware changes](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts), but can be enabled via the Makefile. The firmware will still output characters via USB, so be aware of this when charging via a computer. It would make sense to have a switch on the Bluefruit to turn it off at will.

## Building

Download or clone the whole firmware and navigate to the keyboards/planck folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use `make dfu` to program your PCB once you hit the reset button. 

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` and see keymap document (you can find in top readme.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with `KEYMAP` option like:
```
$ make KEYMAP=[default|jack|<name>]
```
Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
