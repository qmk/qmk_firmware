# Space Cadet: The Future, Built In

Steve Losh described the [Space Cadet Shift](https://web.archive.org/web/20230330090938/https://stevelosh.com/blog/2012/10/a-modern-space-cadet/) quite well. Essentially, when you tap Left Shift on its own, you get an opening parenthesis; tap Right Shift on its own and you get the closing one. When held, the Shift keys function as normal. Yes, it's as cool as it sounds, and now even cooler supporting Control and Alt as well!

## Usage

Firstly, in your keymap, do one of the following:
- Replace the Left Shift key with `SC_LSPO` (Left Shift, Parenthesis Open), and Right Shift with `SC_RSPC` (Right Shift, Parenthesis Close).
- Replace the Left Control key with `SC_LCPO` (Left Control, Parenthesis Open), and Right Control with `SC_RCPC` (Right Control, Parenthesis Close).
- Replace the Left Alt key with `SC_LAPO` (Left Alt, Parenthesis Open), and Right Alt with `SC_RAPC` (Right Alt, Parenthesis Close).
- Replace any Shift key in your keymap with `SC_SENT` (Right Shift, Enter).

## Keycodes

|Keycode                                       |Aliases  |Description                             |
|----------------------------------------------|---------|----------------------------------------|
|`QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN`   |`SC_LCPO`|Left Control when held, `(` when tapped |
|`QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE` |`SC_RCPC`|Right Control when held, `)` when tapped|
|`QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN`  |`SC_LSPO`|Left Shift when held, `(` when tapped   |
|`QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE`|`SC_RSPC`|Right Shift when held, `)` when tapped  |
|`QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN`    |`SC_LAPO`|Left Alt when held, `(` when tapped     |
|`QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE`  |`SC_RAPC`|Right Alt when held, `)` when tapped    |
|`QK_SPACE_CADET_RIGHT_SHIFT_ENTER`            |`SC_SENT`|Right Shift when held, Enter when tapped|

## Caveats

Space Cadet's functionality can conflict with the default Command functionality when both Shift keys are held at the same time. See the [Command feature](feature_command.md) for info on how to change it, or make sure that Command is disabled in your `rules.mk` with:

```make
COMMAND_ENABLE = no
```

## Configuration

By default Space Cadet assumes a US ANSI layout, but if your layout uses different keys for parentheses, you can redefine them in your `config.h`. In addition, you can redefine the modifier to send on tap, or even send no modifier at all. The new configuration defines bundle all options up into a single define of 3 key codes in this order: the `Modifier` when held or when used with other keys, the `Tap Modifer` sent when tapped (no modifier if `KC_TRNS`), finally the `Keycode` sent when tapped. Now keep in mind, mods from other keys will still apply to the `Keycode` if say `KC_RSFT` is held while tapping `SC_LSPO` key with `KC_TRNS` as the `Tap Modifer`.

|Define          |Default                        |Description                                                                      |
|----------------|-------------------------------|---------------------------------------------------------------------------------|
|`LSPO_KEYS`     |`KC_LSFT, LSPO_MOD, LSPO_KEY`  |Send `KC_LSFT` when held, the mod and  key defined by `LSPO_MOD` and `LSPO_KEY`. |
|`RSPC_KEYS`     |`KC_RSFT, RSPC_MOD, RSPC_KEY`  |Send `KC_RSFT` when held, the mod and  key defined by `RSPC_MOD` and `RSPC_KEY`. |
|`LCPO_KEYS`     |`KC_LCTL, KC_LSFT, KC_9`       |Send `KC_LCTL` when held, the mod `KC_LSFT` with the key `KC_9` when tapped.     |
|`RCPC_KEYS`     |`KC_RCTL, KC_RSFT, KC_0`       |Send `KC_RCTL` when held, the mod `KC_RSFT` with the key `KC_0` when tapped.     |
|`LAPO_KEYS`     |`KC_LALT, KC_LSFT, KC_9`       |Send `KC_LALT` when held, the mod `KC_LSFT` with the key `KC_9` when tapped.     |
|`RAPC_KEYS`     |`KC_RALT, KC_RSFT, KC_0`       |Send `KC_RALT` when held, the mod `KC_RSFT` with the key `KC_0` when tapped.     |
|`SFTENT_KEYS`   |`KC_RSFT, KC_TRNS, SFTENT_KEY` |Send `KC_RSFT` when held, no mod with the key `SFTENT_KEY` when tapped.          |
|`SPACE_CADET_MODIFIER_CARRYOVER`   |*Not defined* |Store current modifiers before the hold mod is pressed and use them with the tap mod and keycode. Useful for when you frequently release a modifier before triggering Space Cadet.  |


## Obsolete Configuration

These defines are used in the above defines internally to support backwards compatibility, so you may continue to use them, however the above defines open up a larger range of flexibility than before. As an example, say you want to not send any modifier when you tap just `SC_LSPO`, with the old defines you had an all or nothing choice of using the `DISABLE_SPACE_CADET_MODIFIER` define. Now you can define that key as: `#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_9`. This tells the system to set Left Shift if held or used with other keys, then on tap send no modifier (transparent) with the `KC_9`.

|Define                        |Default      |Description                                                       |
|------------------------------|-------------|------------------------------------------------------------------|
|`LSPO_KEY`                    |`KC_9`       |The keycode to send when Left Shift is tapped                     |
|`RSPC_KEY`                    |`KC_0`       |The keycode to send when Right Shift is tapped                    |
|`LSPO_MOD`                    |`KC_LSFT`    |The modifier to apply to `LSPO_KEY`                               |
|`RSPC_MOD`                    |`KC_RSFT`    |The modifier to apply to `RSPC_KEY`                               |
|`SFTENT_KEY`                  |`KC_ENT`     |The keycode to send when the Shift key is tapped                  |
|`DISABLE_SPACE_CADET_MODIFIER`|*Not defined*|If defined, prevent the Space Cadet from applying a modifier      |
