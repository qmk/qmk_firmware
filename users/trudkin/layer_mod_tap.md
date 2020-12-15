# Layer Mod with a Tap Dance

## Introduction

Layer Mod, *LM(layer, mod)*,is a very handy concept. But its biggest drawback is it takes up two keys to get to the same layer.  While this may be fine on a 100% keyboard on a 40% or 60% this is limiting, and where it is needed most. But what if a key could be both the access to the layer and the modified layer?  In fact tap-hold is the layer, double-tap-hold is layer with mod, and triple-tap-hold is layer with yet another mod.


## Usage

First requirement is to setup as for [mod_tap](https://docs.qmk.fm/#/feature_tap_dance?id=how-to-use). Also add to rules.mk ```SRC += layer_mod_tap.c```

Also in config.h MAX\_LAYER\_MOD_TAP can be set, the default is 8 

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
  SINGLE_HOLD				Momentary activate the layer
  DOUBLE_TAP				Activate the layer
  DOUBLE\_HOLD				Momentary activate the layer with mod_1
  DOUBLE\_SINGLE_TAP		Send the base key twice
  TRIPLE\_TAP				Same as DOUBLE_TAP
  TRIPLE\_HOLD				Momentary activate the layer with mod_2
```

## Limitations
Pressing two Tap Dance keys, as you would with LOWER and RAISE, at the same instant, within a time window, fails to bring up  ADJUST.  Only one of the two calls can be active, we are not multi-threaded.  

The modifier keys are limited to those listed in [Modifier Keys](https://docs.qmk.fm/#/feature_advanced_keycodes?id=modifier-keys)