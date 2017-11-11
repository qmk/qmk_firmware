# Keymap FAQ

This page covers questions people often have about keymaps. If you haven't you should read [Keymap Overview](keymap.md) first.

## What Keycodes Can I Use?
See [Keycodes](keycodes.md) for an index of keycodes available to you. These link to more extensive documentation when available.

Keycodes are actually defined in [common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keycode.h).

## What Are The Default Keycodes?

There are 3 standard keyboard layouts in use around the world- ANSI, ISO, and JIS. North America primarily uses ANSI, Europe and Africa primarily use ISO, and Japan uses JIS. Regions not mentioned typically use either ANSI or ISO. The keycodes corresponding to these layouts are shown here:

<!-- Source for this image: http://www.keyboard-layout-editor.com/#/gists/9ce023dc6caadc0cf11c88c782350a8c -->
![Keyboard Layout Image](https://i.imgur.com/45m4mRf.png)

## The Menu Key Isn't Working

The key found on most modern keyboards that is located between `KC_RGUI` and `KC_RCTL` is actually called `KC_APP`. This is because when that key was invented there was already a key named `MENU` in the relevant standards, so MS chose to call that the `APP` key.

## `KC_SYSREQ` isn't working
Use keycode for Print Screen(`KC_PSCREEN` or `KC_PSCR`) instead of `KC_SYSREQ`. Key combination of 'Alt + Print Screen' is recognized as 'System request'.

See [issue #168](https://github.com/tmk/tmk_keyboard/issues/168) and
- http://en.wikipedia.org/wiki/Magic_SysRq_key
- http://en.wikipedia.org/wiki/System_request

## Power key doesn't work
Use `KC_PWR` instead of `KC_POWER` or vice versa.
- `KC_PWR` works with Windows and Linux, not with OSX.
- `KC_POWER` works with OSX and Linux, not with Windows.

More info: http://geekhack.org/index.php?topic=14290.msg1327264#msg1327264

## Oneshot modifier
Solves my personal 'the' problem. I often got 'the' or 'THe' wrongly instead of 'The'.  Oneshot Shift mitgates this for me.
https://github.com/tmk/tmk_keyboard/issues/67

## Modifier/Layer stuck
Modifier keys or layers can be stuck unless layer switching is configured properly.
For Modifier keys and layer actions you have to place `KC_TRANS` on same position of destination layer to  unregister the modifier key or return to previous layer on release event.

- https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
- http://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
- https://github.com/tmk/tmk_keyboard/issues/248


## Mechanical Lock Switch Support

This feature is for *mechanical lock switch* like [this Alps one](http://deskthority.net/wiki/Alps_SKCL_Lock). You can enable it by adding this to your `config.h`:
 
```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

After enabling this feature use keycodes `KC_LCAP`, `KC_LNUM` and `KC_LSCR` in your keymap instead.

Old vintage mechanical keyboards occasionally have lock switches but modern ones don't have. ***You don't need this feature in most case and just use keycodes `KC_CAPS`, `KC_NLCK` and `KC_SLCK`.***

## Input special charactors other than ASCII like Cédille 'Ç'
NO UNIVERSAL METHOD TO INPUT THOSE WORKS OVER ALL SYSTEMS. You have to define **MACRO** in way specific to your OS or layout.

See this post for example **MACRO** code.

http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478-120.html#p195620

On **Windows** you can use `AltGr` key or **Alt code**.
- http://en.wikipedia.org/wiki/AltGr_key
- http://en.wikipedia.org/wiki/Alt_code

On **Mac** OS defines `Option` key combinations.
- http://en.wikipedia.org/wiki/Option_key#Alternative_keyboard_input

On **Xorg** you can use `compose` key, instead.
- http://en.wikipedia.org/wiki/Compose_key

And see this for **Unicode** input.
- http://en.wikipedia.org/wiki/Unicode_input


## Apple/Mac keyboard Fn
Not supported.

Apple/Mac keyboard sends keycode for Fn unlike most of other keyboards.
I think you can send Apple Fn key using Apple venter specific Page 0xff01 and usage 0x0003. But you have to change HID Report Descriptor for this, of course.

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/AppleHIDUsageTables.h


## Media control keys in Mac OSX
#### KC_MNXT and KC_MPRV does not work on Mac
Use `KC_MFFD`(`KC_MEDIA_FAST_FORWARD`) and `KC_MRWD`(`KC_MEDIA_REWIND`) instead of `KC_MNXT` and `KC_MPRV`.
See https://github.com/tmk/tmk_keyboard/issues/195


## Keys supported in Mac OSX?
You can know which keycodes are supported in OSX from this source code.

`usb_2_adb_keymap` array maps Keyboard/Keypad Page usages to ADB scancodes(OSX internal keycodes).

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

And `IOHIDConsumer::dispatchConsumerEvent` handles Consumer page usages.

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## JIS keys in Mac OSX
Japanese JIS keyboard specific keys like `無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` are not recognized on OSX. You can use **Seil** to enable those keys, try following options.

* Enable NFER Key on PC keyboard
* Enable XFER Key on PC keyboard
* Enable KATAKANA Key on PC keyboard

https://pqrs.org/osx/karabiner/seil.html


## RN-42 Bluetooth doesn't work with Karabiner
Karabiner - Keymapping tool on Mac OSX - ignores inputs from RN-42 module by default. You have to enable this option to make Karabiner working with your keyboard.
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

See these for the deail of this problem.
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## Esc and `~ on a key

Use `GRAVE_ESC` or `KC_GESC` in your keymap. `GUI`+`GRAVE_ESC` results in `` ` `` and `SHIFT`+`GRAVE_ESC` results in `~`.

Note that this will break the CTRL+SHIFT+ESC shortcut to the Windows task manager. Use `#define GRAVE_ESC_CTRL_OVERRIDE` in your `config.h` to get the shortcut back. With this option, `ESC_GRAVE` results in `ESC` if `CTRL` is held, even if `SHIFT` or `GUI` are also held.

## Arrow on Right Modifier keys with Dual-Role
This turns right modifer keys into arrow keys when the keys are tapped while still modifiers when the keys are hold. In TMK the dual-role function is dubbed **TAP**.
```

#include "keymap_common.h"


/* Arrow keys on right modifier keys with TMK dual role feature
 *
 *  https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#213-modifier-with-tap-keydual-role
 *  https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    [0] = KEYMAP( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NUHS,BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,  \
        LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,FN0, ESC, \
        FN4, LGUI,LALT,          SPC,                     APP, FN2, FN1, FN3),
    [1] = KEYMAP( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN5, TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,FN7, FN6, FN8),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_UP),
    [1] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_DOWN),
    [2] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_LEFT),
    [3] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_RIGHT),
    [4] = ACTION_LAYER_MOMENTARY(1),
    [5] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_PGUP),
    [6] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_PGDN),
    [7] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_HOME),
    [8] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_END),
};

```

Dual-role key: https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys


## Eject on Mac OSX
`KC_EJCT` keycode works on OSX. https://github.com/tmk/tmk_keyboard/issues/250
It seems Windows 10 ignores the code and Linux/Xorg recognizes but has no mapping by default.

Not sure what keycode Eject is on genuine Apple keyboard actually. HHKB uses `F20` for Eject key(`Fn+f`) on Mac mode but this is not same as Apple Eject keycode probably.


## What's weak_mods and real_mods in action_util.c
___TO BE IMPROVED___

real_mods is intended to retains state of real/physical modifier key state, while
weak_mods retains state of virtual or temprary modifiers which should not affect state real modifier key.

Let's say you hold down physical left shift key and type ACTION_MODS_KEY(LSHIFT, KC_A), 

with weak_mods,
* (1) hold down left shift: real_mods |= MOD_BIT(LSHIFT)
* (2) press ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods |= MOD_BIT(LSHIFT)
* (3) release ACTION_MODS_KEY(LSHIFT, KC_A): waek_mods &= ~MOD_BIT(LSHIFT)
real_mods still keeps modifier state.

without weak mods,
* (1) hold down left shift: real_mods |= MOD_BIT(LSHIFT)
* (2) press ACTION_MODS_KEY(LSHIFT, KC_A): real_mods |= MOD_BIT(LSHIFT)
* (3) release ACTION_MODS_KEY(LSHIFT, KC_A): real_mods &= ~MOD_BIT(LSHIFT)
here real_mods lost state for 'physical left shift'.

weak_mods is ORed with real_mods when keyboard report is sent.
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57

## Timer functionality

It's possible to start timers and read values for time-specific events - here's an example:

```c
static uint16_t key_timer;
key_timer = timer_read();

if (timer_elapsed(key_timer) < 100) {
  // do something if less than 100ms have passed
} else {
  // do something if 100ms or more have passed
}
```

It's best to declare the `static uint16_t key_timer;` at the top of the file, outside of any code blocks you're using it in.
