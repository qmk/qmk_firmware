# Keymap FAQ

This page covers questions people often have about keymaps. If you haven't you should read [Keymap Overview](keymap) first.

## What Keycodes Can I Use?

See [Keycodes](keycodes) for an index of keycodes available to you. These link to more extensive documentation when available.

Keycodes are actually defined in [quantum/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/keycode.h).

## What Are the Default Keycodes?

There are 3 standard keyboard layouts in use around the world- ANSI, ISO, and JIS. North America primarily uses ANSI, Europe and Africa primarily use ISO, and Japan uses JIS. Regions not mentioned typically use either ANSI or ISO. The keycodes corresponding to these layouts are shown here:

<!-- Source for this image: https://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![Keyboard Layout Image](https://i.imgur.com/5wsh5wM.png)

## How Can I Make Custom Names For Complex Keycodes?

Sometimes, for readability's sake, it's useful to define custom names for some keycodes. People often define custom names using `#define`. For example:

```c
#define FN_CAPS LT(_FL, KC_CAPS)
#define ALT_TAB LALT(KC_TAB)
```

This will allow you to use `FN_CAPS` and `ALT_TAB` in your keymap, keeping it more readable.

## My Keymap Doesn't Update When I Flash It

This is usually due to VIA, and has to do with how it deals with keymaps.

On first run, the VIA code in the firmware will copy the keymap from flash memory into EEPROM so that it can be rewritten at runtime by the VIA app. From this point QMK will use the keymap stored in EEPROM instead of flash, and so updates to your `keymap.c` will not be reflected.

The simple fix for this is to clear the EEPROM. You can do this in several ways:

* Hold the Bootmagic key (usually top left/Escape) while plugging the board in, which will also place the board into bootloader mode; then unplug and replug the board.
* Press the `QK_CLEAR_EEPROM`/`EE_CLR` keycode if it is accessible on your keymap.
* Place the board into bootloader mode and hit the "Clear EEPROM" button. This may not be available for all bootloaders, and you may need to reflash the board afterwards.

## Some Of My Keys Are Swapped Or Not Working

QMK has a couple of features which allow you to change the behavior of your keyboard on the fly. This includes, but is not limited to, swapping Ctrl/Caps, disabling GUI, swapping Alt/GUI, swapping Backspace/Backslash, disabling all keys, and other behavioral modifications.

Refer to the EEPROM clearing methods above, which should return those keys to normal operation. If that doesn't work, look here:

* [Magic Keycodes](keycodes_magic)
* [Command](features/command)

## The Menu Key Isn't Working

The key found on most modern keyboards that is located between `KC_RGUI` and `KC_RCTL` is actually called `KC_APP`. This is because when the key was invented, there was already a key named "Menu" in the HID specification, so for whatever reason, Microsoft chose to create a new key and call it "Application".

## Power Keys Aren't Working

Somewhat confusingly, there are two "Power" keycodes in QMK: `KC_KB_POWER` in the Keyboard/Keypad HID usage page, and `KC_SYSTEM_POWER` (or `KC_PWR`) in the Consumer page.

The former is only recognized on macOS, while the latter, `KC_SLEP` and `KC_WAKE` are supported by all three major operating systems, so it is recommended to use those instead. Under Windows, these keys take effect immediately, however on macOS they must be held down until a dialog appears.

## One Shot Modifier

Solves my personal 'the' problem. I often got 'the' or 'THe' wrongly instead of 'The'.  One Shot Shift mitigates this for me.
https://github.com/tmk/tmk_keyboard/issues/67

## Modifier/Layer Stuck

Modifier keys or layers can be stuck unless layer switching is configured properly.
For Modifier keys and layer actions you have to place `KC_TRNS` on same position of destination layer to  unregister the modifier key or return to previous layer on release event.

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* https://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248

## Mechanical Lock Switch Support

This feature is for *mechanical lock switch* like [this Alps one](https://deskthority.net/wiki/Alps_SKCL_Lock). You can enable it by adding this to your `config.h`:

```c
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

After enabling this feature use keycodes `KC_LCAP`, `KC_LNUM` and `KC_LSCR` in your keymap instead.

Old vintage mechanical keyboards occasionally have lock switches but modern ones don't have. ***You don't need this feature in most case and just use keycodes `KC_CAPS`, `KC_NUM` and `KC_SCRL`.***

## Input Special Characters Other Than ASCII like Cédille 'Ç'

See the [Unicode](features/unicode) feature.

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

See the [Grave Escape](features/grave_esc) feature.

## Eject on Mac OSX

`KC_EJCT` keycode works on OSX. https://github.com/tmk/tmk_keyboard/issues/250
It seems Windows 10 ignores the code and Linux/Xorg recognizes but has no mapping by default.

Not sure what keycode Eject is on genuine Apple keyboard actually. HHKB uses `F20` for Eject key(`Fn+F`) on Mac mode but this is not same as Apple Eject keycode probably.

## What are "Real" and "Weak" modifiers?

Real modifiers refer to the state of the real/physical modifier keys, while weak modifiers are the state of "virtual" or temporary modifiers which should not interfere with the internal state of the real modifier keys.

The real and weak modifier states are ORed together when the keyboard report is sent, so if you release a weak modifier while the same real modifier is still held, the report does not change:

 1. **Hold down physical Left Shift:** Real mods now contains Left Shift, final state is Left Shift
 2. **Add weak Left Shift:** Weak mods now contains Left Shift, final state is Left Shift
 3. **Remove weak Left Shift:** Weak mods now contains nothing, final state is Left Shift
 4. **Release physical Left Shift:** Real mods now contains nothing, final state is nothing
