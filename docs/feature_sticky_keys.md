# Sticky Keys

This feature emulates the Sticky Keys accessibility feature found on Windows, macOS and Linux.

Description, from [Wikipedia](https://en.wikipedia.org/wiki/Sticky_keys):

> Sticky keys is an accessibility feature of some graphical user interfaces to assist users who have physical disabilities or help users reduce repetitive strain injury (or a syndrome called the Emacs Pinky). It serializes keystrokes instead of pressing multiple keys at a time, allowing the user to press and release a modifier key, such as Shift, Ctrl, Alt, or the Windows key, and have it remain active until any other key is pressed.

## Usage

First, enable Sticky Keys by setting `STICKY_KEYS_ENABLE = yes` in your `rules.mk`.

Tap (either) `SHIFT` five times to toggle it on or off.

Once toggled on, tap modifiers to have them apply to your next key, i.e. the sequence `SHIFT`, `CTRL`, `ALT`, `X` will send `SHIFT` + `CTRL` + `ALT` + `X`.

Tapping a modifier twice will lock it, such that this sequence `SHIFT`, `CTRL`, `CTRL`, `ALT`, `X`, `Y` will send  `SHIFT` + `CTRL` + `ALT` + `X`, `CTRL` + `Y`
