# Space Cadet: The Future, Built In

Steve Losh described the [Space Cadet Shift](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) quite well. Essentially, when you tap Left Shift on its own, you get an opening parenthesis; tap Right Shift on its own and you get the closing one. When held, the Shift keys function as normal. Yes, it's as cool as it sounds, and now even cooler supporting Control and Alt as well!

## Usage

Firstly, in your keymap, do one of the following:
- Replace the Left Shift key with `KC_LSPO` (Left Shift, Parenthesis Open), and Right Shift with `KC_RSPC` (Right Shift, Parenthesis Close).
- Replace the Left Control key with `KC_LCPO` (Left Control, Parenthesis Open), and Right Control with `KC_RCPC` (Right Control, Parenthesis Close).
- Replace the Left Alt key with `KC_LAPO` (Left Alt, Parenthesis Open), and Right Alt with `KC_RAPC` (Right Alt, Parenthesis Close).
- Replace any Shift key in your keymap with `KC_SFTENT` (Right Shift, Enter).

## Keycodes

|Keycode    |Description                                |
|-----------|-------------------------------------------|
|`KC_LSPO`  |Left Shift when held, `(` when tapped      |
|`KC_RSPC`  |Right Shift when held, `)` when tapped     |
|`KC_LCPO`  |Left Control when held, `(` when tapped    |
|`KC_RCPC`  |Right Control when held, `)` when tapped   |
|`KC_LAPO`  |Left Alt when held, `(` when tapped        |
|`KC_RAPC`  |Right Alt when held, `)` when tapped       |
|`KC_SFTENT`|Right Shift when held, `Enter` when tapped |

## Caveats

Space Cadet's functionality can conflict with the default Command functionality when both Shift keys are held at the same time. See the [Command feature](feature_command.md) for info on how to change it, or make sure that Command is disabled in your `rules.mk` with:

```make
COMMAND_ENABLE = no
```

## Configuration

By default Space Cadet assumes a US ANSI layout, but if your layout uses different keys for parentheses, you can redefine them in your `config.h`. In addition, you can redefine the modifier to send on tap, or even send no modifier at all. The new configuration defines bundle all options up into a single define of 3 key codes in this order: the `Modifier` when held or when used with other keys, the `Tap Modifer` sent when tapped (no modifier if `MOD_NONE`), finally the `Keycode` sent when tapped. Now keep in mind, mods from other keys will still apply to the `Keycode` if say `KC_RSFT` is held while tapping `KC_LSPO` key with `MOD_NONE` as the `Tap Modifer`.

|Define          |Default                         |Description                                                                       |
|----------------|--------------------------------|----------------------------------------------------------------------------------|
|`LSPO_KEYS`     |`MOD_LSFT, LSPO_MOD, LSPO_KEY`  |Send `MOD_LSFT` when held, the mod and  key defined by `LSPO_MOD` and `LSPO_KEY`. |
|`RSPC_KEYS`     |`MOD_RSFT, RSPC_MOD, RSPC_KEY`  |Send `MOD_RSFT` when held, the mod and  key defined by `RSPC_MOD` and `RSPC_KEY`. |
|`LCPO_KEYS`     |`MOD_LCTL, MOD_LCTL, KC_9`      |Send `MOD_LCTL` when held, the mod `MOD_LCTL` with the key `KC_9` when tapped.    |
|`RCPO_KEYS`     |`MOD_RCTL, MOD_RCTL, KC_0`      |Send `MOD_RCTL` when held, the mod `MOD_RCTL` with the key `KC_0` when tapped.    |
|`LAPO_KEYS`     |`MOD_LALT, MOD_LALT, KC_9`      |Send `MOD_LALT` when held, the mod `MOD_LALT` with the key `KC_9` when tapped.    |
|`RAPO_KEYS`     |`MOD_RALT, MOD_RALT, KC_0`      |Send `MOD_RALT` when held, the mod `MOD_RALT` with the key `KC_0` when tapped.    |
|`SFTENT_KEYS`   |`MOD_RSFT, MOD_NONE, SFTENT_KEY`|Send `MOD_RSFT` when held, no mod with the key `SFTENT_KEY` when tapped.          |


## Obsolete Configuration

These defines are used in the above defines internally to support backwards compatibility, so you may continue to use them, however the above defines open up a larger range of flexibility than before. As an example, say you want to not send any modifier when you tap just `KC_LSPO`, with the old defines you had an all or nothing choice of using the `DISABLE_SPACE_CADET_MODIFIER` define. Now you can define that key as: `#define LSPO_KEYS MOD_LSFT, MOD_NONE, KC_9`. This tells the system to set Left Shift if held or used with other keys, then on tap send no modifier (transparent) with the `KC_9`

|Define                        |Default      |Description                                                       |
|------------------------------|-------------|------------------------------------------------------------------|
|`LSPO_KEY`                    |`KC_9`       |The keycode to send when Left Shift is tapped                     |
|`RSPC_KEY`                    |`KC_0`       |The keycode to send when Right Shift is tapped                    |
|`LSPO_MOD`                    |`MOD_LSFT`   |The modifier to apply to `LSPO_KEY`                               |
|`RSPC_MOD`                    |`MOD_RSFT`   |The modifier to apply to `RSPC_KEY`                               |
|`SFTENT_KEY`                  |`KC_ENT`     |The keycode to send when the Shift key is tapped                  |
|`DISABLE_SPACE_CADET_MODIFIER`|*Not defined*|If defined, prevent the Space Cadet from applying a modifier      |
