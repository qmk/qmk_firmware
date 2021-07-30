# Keymap FAQ

This page covers questions people often have about keymaps. If you haven't you should read [Keymap Overview](keymap.md) first.

## What Keycodes Can I Use?
See [Keycodes](keycodes.md) for an index of keycodes available to you. These link to more extensive documentation when available.

Keycodes are actually defined in [common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keycode.h).

## What Are the Default Keycodes?

There are 3 standard keyboard layouts in use around the world- ANSI, ISO, and JIS. North America primarily uses ANSI, Europe and Africa primarily use ISO, and Japan uses JIS. Regions not mentioned typically use either ANSI or ISO. The keycodes corresponding to these layouts are shown here:

<!-- Source for this image: https://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![Keyboard Layout Image](https://i.imgur.com/5wsh5wM.png)

## How Can I Make Custom Names For Complex Keycodes?

Sometimes, for readability's sake, it's useful to define custom names for some keycodes. People often define custom names using `#define`. For example:

```c
#define FN_CAPS LT(_FL, KC_CAPSLOCK)
#define ALT_TAB LALT(KC_TAB)
```

This will allow you to use `FN_CAPS` and `ALT_TAB` in your keymap, keeping it more readable.

## Some Of My Keys Are Swapped Or Not Working

QMK has two features, Bootmagic and Command, which allow you to change the behavior of your keyboard on the fly. This includes, but is not limited to, swapping Ctrl/Caps, disabling Gui, swapping Alt/Gui, swapping Backspace/Backslash, disabling all keys, and other behavioral modifications. 

As a quick fix try holding down `Space`+`Backspace` while you plug in your keyboard. This will reset the stored settings on your keyboard, returning those keys to normal operation. If that doesn't work look here:

* [Bootmagic](feature_bootmagic.md)
* [Command](feature_command.md) 

## The Menu Key Isn't Working

The key found on most modern keyboards that is located between `KC_RGUI` and `KC_RCTL` is actually called `KC_APP`. This is because when that key was invented there was already a key named `MENU` in the relevant standards, so MS chose to call that the `APP` key.

## `KC_SYSREQ` Isn't Working
Use keycode for Print Screen(`KC_PSCREEN` or `KC_PSCR`) instead of `KC_SYSREQ`. Key combination of 'Alt + Print Screen' is recognized as 'System request'.

See [issue #168](https://github.com/tmk/tmk_keyboard/issues/168) and
* https://en.wikipedia.org/wiki/Magic_SysRq_key
* https://en.wikipedia.org/wiki/System_request

## Power Keys Aren't Working

Somewhat confusingly, there are two "Power" keycodes in QMK: `KC_POWER` in the Keyboard/Keypad HID usage page, and `KC_SYSTEM_POWER` (or `KC_PWR`) in the Consumer page.

The former is only recognized on macOS, while the latter, `KC_SLEP` and `KC_WAKE` are supported by all three major operating systems, so it is recommended to use those instead. Under Windows, these keys take effect immediately, however on macOS they must be held down until a dialog appears.

## One Shot Modifier
Solves my personal 'the' problem. I often got 'the' or 'THe' wrongly instead of 'The'.  One Shot Shift mitigates this for me.
https://github.com/tmk/tmk_keyboard/issues/67

## Modifier/Layer Stuck
Modifier keys or layers can be stuck unless layer switching is configured properly.
For Modifier keys and layer actions you have to place `KC_TRANS` on same position of destination layer to  unregister the modifier key or return to previous layer on release event.

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* https://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248


## Mechanical Lock Switch Support

This feature is for *mechanical lock switch* like [this Alps one](https://deskthority.net/wiki/Alps_SKCL_Lock). You can enable it by adding this to your `config.h`:

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

After enabling this feature use keycodes `KC_LCAP`, `KC_LNUM` and `KC_LSCR` in your keymap instead.

Old vintage mechanical keyboards occasionally have lock switches but modern ones don't have. ***You don't need this feature in most case and just use keycodes `KC_CAPS`, `KC_NLCK` and `KC_SLCK`.***

## Input Special Characters Other Than ASCII like Cédille 'Ç'

See the [Unicode](feature_unicode.md) feature.

## `Fn` Key on macOS

Unlike most Fn keys, the one on Apple keyboards actually has its own keycode... sort of. It takes the place of the sixth keycode in a basic 6KRO HID report -- so an Apple keyboard is in fact only 5KRO.

It is technically possible to get QMK to send this key. However, doing so requires modification of the report format to add the state of the Fn key.
Even worse, it is not recognized unless the keyboard's VID and PID match that of a real Apple keyboard. The legal issues that official QMK support for this feature may create mean it is unlikely to happen.

See [this issue](https://github.com/qmk/qmk_firmware/issues/2179) for detailed information.

## Keys Supported in Mac OSX?
You can know which keycodes are supported in OSX from this source code.

`usb_2_adb_keymap` array maps Keyboard/Keypad Page usages to ADB scancodes(OSX internal keycodes).

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

And `IOHIDConsumer::dispatchConsumerEvent` handles Consumer page usages.

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## JIS Keys in Mac OSX
Japanese JIS keyboard specific keys like `無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` are not recognized on OSX. You can use **Seil** to enable those keys, try following options.

* Enable NFER Key on PC keyboard
* Enable XFER Key on PC keyboard
* Enable KATAKANA Key on PC keyboard

https://pqrs.org/osx/karabiner/seil.html


## RN-42 Bluetooth Doesn't Work with Karabiner
Karabiner - Keymapping tool on Mac OSX - ignores inputs from RN-42 module by default. You have to enable this option to make Karabiner working with your keyboard.
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

See these for the detail of this problem.
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## Esc and <code>&#96;</code> on a Single Key

See the [Grave Escape](feature_grave_esc.md) feature.

## Eject on Mac OSX
`KC_EJCT` keycode works on OSX. https://github.com/tmk/tmk_keyboard/issues/250
It seems Windows 10 ignores the code and Linux/Xorg recognizes but has no mapping by default.

Not sure what keycode Eject is on genuine Apple keyboard actually. HHKB uses `F20` for Eject key(`Fn+f`) on Mac mode but this is not same as Apple Eject keycode probably.


## What's `weak_mods` and `real_mods` in `action_util.c`
___TO BE IMPROVED___

real_mods is intended to retains state of real/physical modifier key state, while
weak_mods retains state of virtual or temporary modifiers which should not affect state real modifier key.

Let's say you hold down physical left shift key and type ACTION_MODS_KEY(LSHIFT, KC_A),

with weak_mods,
* (1) hold down left shift: real_mods |= MOD_BIT(LSHIFT)
* (2) press ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods |= MOD_BIT(LSHIFT)
* (3) release ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods &= ~MOD_BIT(LSHIFT)
real_mods still keeps modifier state.

without weak mods,
* (1) hold down left shift: real_mods |= MOD_BIT(LSHIFT)
* (2) press ACTION_MODS_KEY(LSHIFT, KC_A): real_mods |= MOD_BIT(LSHIFT)
* (3) release ACTION_MODS_KEY(LSHIFT, KC_A): real_mods &= ~MOD_BIT(LSHIFT)
here real_mods lost state for 'physical left shift'.

weak_mods is ORed with real_mods when keyboard report is sent.
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
