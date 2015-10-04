## READ FIRST
https://github.com/tmk/tmk_keyboard/blob/master/doc/keymap.md

## How to get keycode
See [doc/keycode.txt](https://github.com/tmk/tmk_keyboard/blob/master/doc/keycode.txt).
Keycodes are actually defined in [common/keycode.h](https://github.com/tmk/tmk_keyboard/blob/master/common/keycode.h).

## Sysrq key
Use keycode for Print Screen(`KC_PSCREEN` or `KC_PSCR`) instead of `KC_SYSREQ`. Key combination of 'Alt + Print Screen' is recognized as 'System request'.

See [issue #168](https://github.com/tmk/tmk_keyboard/issues/168) and
- http://en.wikipedia.org/wiki/Magic_SysRq_key
- http://en.wikipedia.org/wiki/System_request

## Power key doesn't work
Use `KC_PWR` instead of `KC_POWER` or vice versa.
- `KC_PWR` works with Windows and Linux, not with OSX.
- `KC_POWER` works with OSX and Linux, not with Windows.

http://geekhack.org/index.php?topic=14290.msg1327264#msg1327264

## Oneshot modifier
Solves my personal 'the' problem. I often got 'the' or 'THe' wrongly instead of 'The'.  Oneshot Shift mitgates this for me.
https://github.com/tmk/tmk_keyboard/issues/67

## Modifier/Layer stuck
Modifier keys or layers can be stuck unless layer switching is configured properly.
For Modifier keys and layer actions you have to place `KC_TRANS` on same position of destination layer to  unregister the modifier key or return to previous layer on release event.

- https://github.com/tmk/tmk_keyboard/blob/master/doc/keymap.md#31-momentary-switching
- http://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
- https://github.com/tmk/tmk_keyboard/issues/248


## Mechanical Lock Switch Support
https://github.com/tmk/tmk_keyboard#mechanical-locking-support

This feature is for *mechanical lock switch* like this Alps one.
http://deskthority.net/wiki/Alps_SKCL_Lock

Using enabling this feature and using keycodes `LCAP`, `LNUM` or `LSCR` in keymap you can use physical locking CapsLock, NumLock or ScrollLock keys as you expected.

Old vintage mechanical keyboards occasionally have lock switches but modern ones don't have. ***You don't need this feature in most case and just use keycodes `CAPS`, `NLCK` and `SLCK`.***


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


### Apple keyboard Fn
Not supported.

Apple keyboard sends keycode for Fn unlike most of other keyboards.
I think you can send Apple Fn key using Apple venter specific Page 0xff00 and usage 0x0003. But you have to change HID Report Descriptor for this, of course.

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
https://github.com/p3lim/keyboard_firmware/commit/fd799c12b69a5ab5addd1d4c03380a1b8ef8e9dc