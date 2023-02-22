# Emoji Keymap
![Picture](https://i.imgur.com/1zEZ9Lq.png)

# Unicode Setup

Unicode input in QMK works by inputting a sequence of characters to the 
OS, sort of like a macro. Unfortunately, the way this is done differs 
for each platform. Specifically, each platform requires a different 
combination of keys to trigger Unicode input. Therefore, a 
corresponding input mode has to be set in QMK.

Documentation: [Feature Unicode](https://beta.docs.qmk.fm/features/feature_unicode#input-modes)

On this keymap the default unicode mode it's `UNICODE_MODE_LINUX`.
You can change it permanently tapping 2 times the KeyOne to select the next mode.

## Unicode Mode List
- UNICODE_MODE_LINUX
- UNICODE_MODE_MACOS
- UNICODE_MODE_WINDOWS
- UNICODE_MODE_WINCOMPOSE

# Keymap
To add more functionality to this Minimal Keyboard, 
it's implemented the tap dance feature, so pressing the same key 
multiples times will produce different emojis.

## Key One

- 1 Tap: `¯\_(ツ)_/¯`
- 2 Taps: Switch Unicode Input Type

## Key Two

- 1 Tap: `ಠ_ಠ`
- 2 Taps: `(ノಠ痊ಠ)ノ彡┻━┻`
- 3 Taps: `╭∩╮(-_-)╭∩╮`
- 4 Taps: `(づ￣ ³￣)づ`
- 5 Taps: `(︺︹︺)`