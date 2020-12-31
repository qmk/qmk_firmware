
```
/* Copyright 2020 Terence Rudkin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
```

# Layer Mod with a Tap Dance
## Introduction

Layer Mod, *LM(layer, mod)*,is a very handy concept. But its biggest drawback is it takes up two keys to get to the same layer.  While this may be fine on a 100% keyboard on a 40% or 60% this is limiting, and where it is needed most. But what if a key could be both the access to the layer and the modified layer?  In fact tap-hold is the layer, double-tap-hold is layer with mod, and triple-tap-hold is layer with yet another mod.

The inspiration was my plank, desiring quick access so the numbers and symbols.  The top row on LOWER layer is the number keys, SINGLE\_HOLD.  and they become the symbols with DOUBLE\_HOLD.

## Usage

First requirement is to setup as for [mod_tap](https://docs.qmk.fm/#/feature_tap_dance?id=how-to-use). Also add to rules.mk ```SRC += layer_mod_tap.c```

Also in config.h MAX\_LAYER\_MOD\_TAP can be set, the default is 8 

```
#define MAX_LAYER_MOD_TAP 6
```

```
ACTION_MOD_LAYER( index,keycode,layer,mod_2_tap,mod_3_tap)
```
The API takes an index to allow multiple ACTION\_MOD\_LAYER to be active, as would be the case for LOWER and RAISE to activate ADJUST.   keycode is the key to be activated KC_NO if none is desired.  layer is the layer to activate



### Action as from cur_state

```
  SINGLE_TAP 				Send the base key
  SINGLE_HOLD				Momentary activate the layer   			(MO)
  DOUBLE_TAP				Activate the layer							(TG)
  DOUBLE_HOLD				Momentary activate the layer with mod_1	(LM)
  DOUBLE_SINGLE_TAP 		Send the base key twice
  TRIPLE_TAP				Same as DOUBLE_TAP							(TG)
  TRIPLE_HOLD				Momentary activate the layer with mod_2	(LM)
```

## Example
```
// top of file or header
enum  td_keycodes {
    MOD_LOW,
    MOD_RAI,
    TD_DEL_INS,
};

// place these in keymap
#define MY_LOW TD(MOD_LOW)
#define MY_RAI TD(MOD_RAI)
#define MY_DEL TD(TD_DEL_INS)

// bottom of source 
qk_tap_dance_action_t tap_dance_actions[] = {
    [MOD_LOW]  = ACTION_MOD_LAYER(1, KC_MINS, _LOWER, KC_RSFT, KC_RALT),
    [MOD_RAI]  = ACTION_MOD_LAYER(2, KC_EQL , _RAISE, KC_RCTL, KC_RSFT),
    [TD_DEL_INS]  = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_INS),
};
```
## Limitations
Pressing two Tap Dance keys, as you would with LOWER and RAISE, at the same instant, within a time window, fails to bring up  ADJUST.  Only one of the two calls can be active, we are not multi-threaded.  But if the second is pushed after the the first is active ADJUST will come up.  

The modifier keys are limited to those listed in [Modifier Keys](https://docs.qmk.fm/#/feature_advanced_keycodes?id=modifier-keys)