# QMK Features


## Space Cadet Shift: The future, built in

Steve Losh [described](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) the Space Cadet Shift quite well. Essentially, you hit the left Shift on its own, and you get an opening parenthesis; hit the right Shift on its own, and you get the closing one. When hit with other keys, the Shift key keeps working as it always does. Yes, it's as cool as it sounds. Head on over to the [Space Cadet Shift](space_cadet_shift.md) page to read about it.

## The Leader key: A new kind of modifier

Most modifiers have to be held or toggled. But what if you had a key that indicated the start of a sequence? You could press that key and then rapidly press 1-3 more keys to trigger a macro, or enter a special layer, or anything else you might want to do. To learn more about it check out the [Leader Key](feature_leader_key.md) page.

## Tap Dance: A single key can do 3, 5, or 100 different things

Hit the semicolon key once, send a semicolon. Hit it twice, rapidly -- send a colon. Hit it three times, and your keyboard's LEDs do a wild dance. That's just one example of what Tap Dance can do. Read more about it on the [Tap Dance](tap_dance.md) page.

## Temporarily setting the default layer

`DF(layer)` - sets default layer to _layer_. The default layer is the one at the "bottom" of the layer stack - the ultimate fallback layer. This currently does not persist over power loss. When you plug the keyboard back in, layer 0 will always be the default. It is theoretically possible to work around that, but that's not what `DF` does.

## Macro shortcuts: Send a whole string when pressing just one key

How would you like a single keypress to send a whole word, sentence, paragraph, or even document? Head on over to the [Macros](macros.md) page to read up on all aspects of Simple and Dynamic Macros.

## Additional keycode aliases for software-implemented layouts \(Colemak, Dvorak, etc\)

Everything is assuming you're in Qwerty \(in software\) by default, but there is built-in support for using a Colemak or Dvorak layout by including this at the top of your keymap:

```
#include <keymap_colemak.h>
```

If you use Dvorak, use `keymap_dvorak.h` instead of `keymap_colemak.h` for this line. After including this line, you will get access to:

* `CM_*` for all of the Colemak-equivalent characters
* `DV_*` for all of the Dvorak-equivalent characters

These implementations assume you're using Colemak or Dvorak on your OS, not on your keyboard - this is referred to as a software-implemented layout. If your computer is in Qwerty and your keymap is in Colemak or Dvorak, this is referred to as a firmware-implemented layout, and you won't need these features.

To give an example, if you're using software-implemented Colemak, and want to get an `F`, you would use `CM_F`. Using `KC_F` under these same circumstances would result in `T`.

## Backlight Breathing

In order to enable backlight breathing, the following line must be added to your config.h file.

```
#define BACKLIGHT_BREATHING
```

The following function calls are used to control the breathing effect.

* `breathing_enable()` - Enable the free-running breathing effect.
* `breathing_disable()` - Disable the free-running breathing effect immediately.
* `breathing_self_disable()` - Disable the free-running breathing effect after the current effect ends.
* `breathing_toggle()` - Toggle the free-running breathing effect.
* `breathing_defaults()` - Reset the speed and brightness settings of the breathing effect.

The following function calls are used to control the maximum brightness of the breathing effect.

* `breathing_intensity_set(value)` - Set the brightness of the breathing effect when it is at its max value.
* `breathing_intensity_default()` - Reset the brightness of the breathing effect to the default value based on the current backlight intensity.

The following function calls are used to control the cycling speed of the breathing effect.

* `breathing_speed_set(value)` - Set the speed of the breathing effect - how fast it cycles.
* `breathing_speed_inc(value)` - Increase the speed of the breathing effect by a fixed value.
* `breathing_speed_dec(value)` - Decrease the speed of the breathing effect by a fixed value.
* `breathing_speed_default()` - Reset the speed of the breathing effect to the default value.

The following example shows how to enable the backlight breathing effect when the FUNCTION layer macro button is pressed:

```
case MACRO_FUNCTION:
    if (record->event.pressed)
    {
        breathing_speed_set(3);
        breathing_enable();
        layer_on(LAYER_FUNCTION);
    }
    else
    {
        breathing_speed_set(1);
        breathing_self_disable();
        layer_off(LAYER_FUNCTION);
    }
    break;
```

The following example shows how to pulse the backlight on-off-on when the RAISED layer macro button is pressed:

```
case MACRO_RAISED:
  if (record->event.pressed)
  {
    layer_on(LAYER_RAISED);
    breathing_speed_set(2);
    breathing_pulse();
    update_tri_layer(LAYER_LOWER, LAYER_RAISED, LAYER_ADJUST);
  }
  else
  {
    layer_off(LAYER_RAISED);
    update_tri_layer(LAYER_LOWER, LAYER_RAISED, LAYER_ADJUST);
  }
  break;
```