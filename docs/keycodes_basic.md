# Basic Keycodes

The basic set of keycodes are based on the [HID Keyboard/Keypad Usage Page (0x07)](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) with the exception of `KC_NO`, `KC_TRNS` and keycodes in the `0xA5-DF` range. See below for more details.

## Letters and Numbers

[keycodes_letters_and_numbers.md](./keycodes_letters_and_numbers.md ':include')

## F Keys

[keycodes_f_keys.md](./keycodes_f_keys.md ':include')

## Punctuation

[keycodes_punctuation.md](./keycodes_punctuation.md ':include')

## Lock Keys

[keycodes_lock_keys.md](./keycodes_lock_keys.md ':include')

## Basic Modifiers

[keycodes_basic_modifiers.md](./keycodes_basic_modifiers.md ':include')

## International

[keycodes_international.md](./keycodes_international.md ':include')

## Commands

[keycodes_international.md](./keycodes_international.md ':include')

## Media Keys

These keycodes are not part of the Keyboard/Keypad usage page. The `SYSTEM_` keycodes are found in the Generic Desktop page, and the rest are located in the Consumer page.

?> Some of these keycodes may behave differently depending on the OS. For example, on macOS, the keycodes `KC_MEDIA_FAST_FORWARD`, `KC_MEDIA_REWIND`, `KC_MEDIA_NEXT_TRACK` and `KC_MEDIA_PREV_TRACK` skip within the current track when held, but skip the entire track when tapped.

[keycodes_media.md](./keycodes_media.md ':include')

## Number Pad

[keycodes_number_pad.md](./keycodes_number_pad.md ':include')

## Special Keys

In addition to these, keycodes in the range of `0xA5-DF` are reserved for internal use.

[keycodes_special.md](./keycodes_special.md ':include')