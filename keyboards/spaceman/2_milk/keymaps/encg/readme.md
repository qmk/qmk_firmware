# encg's Keymap

## What is this?

A simple slot machine emulator for the [2% Milk Keyboard](https://github.com/Spaceman/SpaceboardsHardware/tree/master/Keyboards/2%25%20Milk). This idea is based on the [implementation by /u/ln8r on /r/mechanicalkeyboards](https://www.reddit.com/r/MechanicalKeyboards/comments/hcw21b/2_milk_slot_machine/).

## How does it work?

The top button outputs all possible winning emoji combinations followed by a corresponding "score." Emojis are output one-by-one with a short delay to simulate the "slots" feel.

![IMG](https://i.imgur.com/rUc3IOn.gif)

The bottom button outputs 3 random emojis one by one. The random function takes `timer_read()` as its seed value [(referenced here)](https://beta.docs.qmk.fm/developing-qmk/qmk-reference/ref_functions#software-timers).

![IMG](https://i.imgur.com/4EREsIq.png)

## Unicode Setup

This keymap's default unicode input mode is `UNICODE_MODE_WINCOMPOSE` which requires [WinCompose](https://github.com/samhocevar/wincompose). For other OSes, see [QMK documentation on unicode input modes](https://docs.qmk.fm/#/feature_unicode?id=input-modes).

## Ideas for the future

- [ ] Factor in emoji hierarchy into RNG algorithm
- [ ] Random/Wildcard emoji
- [ ] Keep a count for winng combinations
- [ ] Implement tap dance for easily switching unicode input types
