# GMMK 2 65% Custom layout

## Main changes:

### Remapped fn layer

  1. fn+pgdown or fn+pgup sends a right control (for virtualbox)
  2. Arrow keys are for media control
    * Up and down change volume
    * Left and right change tracks
    * Enter mutes/unmutes (follows the trend of ascending keys being for audio)
    * Pipe/backslash plays/stops (think of it as or/toggle `|`)
  3. RGB control is around the WASD area
    * W/S increase/decrease brightness (same trend as media keys)
    * A/D change to the previous/next RBG profile 
    * E changes hue (color), shift can be used to reverse it but it rolls over after 255
    * Q changes saturation, shift can be used to reverse it but it rolls over after 255
    * R/F are used to increase/decrease the RGB speeds

Changed the following config options:
| config.h parameter			| reason					|
| --------------------------------------| ---------------------------------------------	|
| `#define FORCE_NKRO`			| Enable n-key rollover				|
| `#define LEADER_TIMEOUT 500`		| Set the leader timeout to 500ms		|
| `#define LEADER_NO_TIMEOUT`		| Disable leader timeout for first keypress	|
| `#define LEADER_PER_KEY_TIMING`	| Reset the leader timer on each keypress	|
| `#define GRAVE_ESC_CTRL_OVERRIDE`	| Fix ctrl+shift+esc for task manager		|

Changed the following make rules options:
| rules.mk parameter			| reason					|
| --------------------------------------| ---------------------------------------------	|
| `SRC += analog.c`			| Enable use of the ADC 			|
| `LEADER_ENABLE = yes`			| Enable the leader key				|
| `CONSOLE_ENABLE = yes`		| Enable the console (for debugging)		|
| `WPM_ENABLE = yes`			| Enable WPM tracking/calculation		|

Added the following to `halconf.h` for ADC usage:
```
#pragma once
#define HAL_USE_ADC TRUE
#include_next <halconf.h>
```

Likewise for `mcuconf.h`:
```
#pragma once
#include_next <mcuconf.h>
#define WB32_ADC_USE_ADC1 TRUE
```

### Added a custom leader mode:
The leader can be act




### RGB

Added custom indicator modes:
  * Caps lock makes the `caps lock`, `underglow keys`, and `c` `a` `p` `s` `l` `o` `c` `k` keys pulse red, with the whole keyboard pulsing red at the peak
  * Debug mode spells `d` `e` `b` `u` `g` in pulsing blue, and also lights the `esc` key
  * The leader mode makes the `.` / `>` key turn green while the leader is taking input/processing

Removed most of the RGB patterns, left the following:
  * Solid color			[Builtin]
  * Rainbow Beacon	(fn+c)	[Default]
  * Pixel rain
  * Heatmap		(fn+a)
  * Simple reactive
  * Solid reactive
  * Reactive multiwide
  * Reactive multicross
  * Reactive multinexus (fn+x)
	
Changed the following config options:
| config.h parameter			| reason					|
| --------------------------------------| ---------------------------------------------	|
| `#define RGB_MATRIX_DEFAULT_SPD 64`	| Set the default speed to 64			|
| `#define RGB_MATRIX_KEYPRESSES`	| Make RGB process individual keypresses	|


x
