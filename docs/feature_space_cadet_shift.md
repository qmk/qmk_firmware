# Space Cadet Shift: The Future, Built In

Steve Losh described the [Space Cadet Shift](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) quite well. Essentially, when you tap Left Shift on its own, you get an opening parenthesis; tap Right Shift on its own and you get the closing one. When held, the Shift keys function as normal. Yes, it's as cool as it sounds.

## Usage

Replace the Left Shift key in your keymap with `KC_LSPO` (Left Shift, Parenthesis Open), and Right Shift with `KC_RSPC` (Right Shift, Parenthesis Close).

## Keycodes

|Keycode  |Description                           |
|---------|--------------------------------------|
|`KC_LSPO`|Left Shift when held, `(` when tapped |
|`KC_RSPC`|Right Shift when held, `)` when tapped|

## Caveats

Space Cadet's functionality can conflict with the default Command functionality when both Shift keys are held at the same time. Make sure that Command is disabled in your `rules.mk` with:

```make
COMMAND_ENABLE = no
```

## Configuration

By default Space Cadet assumes a US ANSI layout, but if your layout uses different keys for parentheses, you can redefine them in your `config.h`.
You can also disable the rollover, allowing you to use the opposite Shift key to cancel the Space Cadet state in the event of an erroneous press, instead of emitting a pair of parentheses when the keys are released.

|Define                        |Default      |Description                                                 |
|------------------------------|-------------|------------------------------------------------------------|
|`LSPO_KEY`                    |`KC_9`       |The keycode to send when Left Shift is tapped               |
|`RSPC_KEY`                    |`KC_0`       |The keycode to send when Right Shift is tapped              |
|`DISABLE_SPACE_CADET_ROLLOVER`|*Not defined*|If defined, use the opposite Shift key to cancel Space Cadet|
