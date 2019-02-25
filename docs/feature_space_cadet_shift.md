# Space Cadet Shift: The Future, Built In

Steve Losh described the [Space Cadet Shift](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) quite well. Essentially, when you tap Left Shift on its own, you get an opening parenthesis; tap Right Shift on its own and you get the closing one. When held, the Shift keys function as normal. Yes, it's as cool as it sounds, and now even cooler supporting Control and Alt!

## Usage

Firstly, enable Space Cadet in your keymap's Makefile.

```make
SPACE_CADET_ENABLE = yes
```

Then do one of the following:
Replace the Left Shift key in your keymap with `KC_LSPO` (Left Shift, Parenthesis Open), and Right Shift with `KC_RSPC` (Right Shift, Parenthesis Close).
Replace the Left Control key in your keymap with `KC_LCPO` (Left Control, Parenthesis Open), and Right Control with `KC_RCPC` (Right Control, Parenthesis Close).
Replace the Left Alt key in your keymap with `KC_LAPO` (Left Alt, Parenthesis Open), and Right Alt with `KC_RAPC` (Right Alt, Parenthesis Close).

## Keycodes

|Keycode  |Description                              |
|---------|-----------------------------------------|
|`KC_LSPO`|Left Shift when held, `(` when tapped    |
|`KC_RSPC`|Right Shift when held, `)` when tapped   |
|`KC_LCPO`|Left Control when held, `(` when tapped  |
|`KC_RCPC`|Right Control when held, `)` when tapped |
|`KC_LAPO`|Left Alt when held, `(` when tapped      |
|`KC_RAPC`|Right Alt when held, `)` when tapped     |

## Caveats

Space Cadet's functionality can conflict with the default Command functionality when both Shift keys are held at the same time. Make sure that Command is disabled in your `rules.mk` with:

```make
COMMAND_ENABLE = no
```

## Configuration

By default Space Cadet assumes a US ANSI layout, but if your layout uses different keys for parentheses, you can redefine them in your `config.h`.
You can also disable the rollover, allowing you to use the opposite modifer key to cancel the Space Cadet state in the event of an erroneous press, instead of emitting a pair of parentheses when the keys are released.
Also, by default, the Space Cadet applies modifiers LSPO_MOD and RSPC_MOD to keys defined by LSPO_KEY and RSPC_KEY. You can override this behavior by redefining those variables in your `config.h`. You can also prevent the Space Cadet to apply a modifier by defining DISABLE_SPACE_CADET_MODIFIER in your `config.h`.

|Define                        |Default      |Description                                                                     |
|------------------------------|-------------|--------------------------------------------------------------------------------|
|`LSPO_KEY`                    |`KC_9`       |The keycode to send when Left Shift is tapped                                   |
|`RSPC_KEY`                    |`KC_0`       |The keycode to send when Right Shift is tapped                                  |
|`LSPO_MOD`                    |`KC_LSFT`    |The modifier to apply to `LSPO_KEY`                                             |
|`RSPC_MOD`                    |`KC_RSFT`    |The modifier to apply to `RSPC_KEY`                                             |
|`LCPO_KEY`                    |`KC_9`       |The keycode to send when Left Control is tapped                                 |
|`RCPC_KEY`                    |`KC_0`       |The keycode to send when Right Control is tapped                                |
|`LCPO_MOD`                    |`KC_LCTL`    |The modifier to apply to `LCPO_KEY`                                             |
|`RCPC_MOD`                    |`KC_RCTL`    |The modifier to apply to `RCPC_KEY`                                             |
|`LAPO_KEY`                    |`KC_9`       |The keycode to send when Left Alt is tapped                                     |
|`RAPC_KEY`                    |`KC_0`       |The keycode to send when Right Alt is tapped                                    |
|`LAPO_MOD`                    |`KC_LALT`    |The modifier to apply to `LAPO_KEY`                                             |
|`RAPC_MOD`                    |`KC_RALT`    |The modifier to apply to `RAPC_KEY`                                             |
|`DISABLE_SPACE_CADET_ROLLOVER`|*Not defined*|If defined, use the opposite modifer key to cancel Space Cadet                  |
|`DISABLE_SPACE_CADET_MODIFIER`|*Not defined*|If defined, prevent the Space Cadet from applying a modifier                    |
