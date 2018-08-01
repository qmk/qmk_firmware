# Space Cadet Shift Enter

Based on the [Space Cadet Shift](feature_space_cadet_shift.md) feature. Tap the Shift key on its own, and it behaves like Enter. When held, the Shift functions as normal.

## Usage

Replace any Shift key in your keymap with `KC_SFTENT` (Shift, Enter), and you're done.

## Keycodes

|Keycode    |Description                             |
|-----------|----------------------------------------|
|`KC_SFTENT`|Right Shift when held, Enter when tapped|

## Caveats

As with Space Cadet Shift, this feature may conflict with Command, so it should be disabled in your `rules.mk` with:

```make
COMMAND_ENABLE = no
```

This feature also uses the same timers as Space Cadet Shift, so using them in tandem may produce strange results.

## Configuration

By default Space Cadet assumes a US ANSI layout, but if you'd like to use a different key for Enter, you can redefine it in your `config.h`:

|Define      |Default |Description                                     |
|------------|--------|------------------------------------------------|
|`SFTENT_KEY`|`KC_ENT`|The keycode to send when the Shift key is tapped|
