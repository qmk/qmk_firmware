# TKL keymap for frosty_flake

##Layers

  ,----.    ,-------------------. ,-------------------. ,-------------------. ,--------------.
  |ESC |    | F1 | F2 | F3 | F4 | | F5 | F6 | F7 | F8 | | F9 |F10 |F11 |F12 | |PrSc|ScLk|PsBk|
  '----'    '-------------------' '-------------------' '-------------------' '--------------'
  ,-------------------------------------------------------------------------. ,--------------. 
  |  ` | 1  |  2 |  3 | 4  |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |  Bspc  | | Ins|Home|PgUp| 
  |-------------------------------------------------------------------------| |--------------| 
  | Tab  | Q  |  W | F  | P  | G  | J  | L  |  U |  Y | ;  | [  |  ] |   \  | | Del|End |PgDn| 
  |-------------------------------------------------------------------------| '--------------'
  |  Bspc | A  | R  |  S |  T | D  | H  | N  | E  | I  | O  | '  |   Enter  |                 
  |-------------------------------------------------------------------------|      ,----.     
  |   LSPO  | Z  | X  |  C | V  |  B |  K |  M |  , |  . |  / |    RSPC     |      | Up |     
  |-------------------------------------------------------------------------| ,--------------.
  |Ctrl|LGUI|LAlt|             Space/Lower              |MSE |RGUI|Menu|Ctrl| |Left|Down|Rght|
  '-------------------------------------------------------------------------' '--------------'

### Base Layer - Colemak
	* The base layout is Colemak. 
			* I've implemented COLEMAK = SAFE_RANGE when enumerating the custom_keycodes, but I don't actually know what this does...

	* Space cadet is implemented in the shift keys (hold for shift, tap for respective parentheses)

	#### Layer Shifting
	* The spacebar is a **TAP_KEY** macro - Hold for momentary *LOWER* layer, Tap for Space.
	* The Right hand ALT key is a **TAP_TOGGLE** macro for the *MOUSE* layer (RAlt is accessible through LOWER, if you want...)
	
### LOWER

  ,----.    ,-------------------. ,-------------------. ,-------------------. ,--------------.
  |ESC |    | F1 | F2 | F3 | F4 | | F5 | F6 | F7 | F8 | | F9 |F10 |F11 |F12 | |PrSc|ScLk|PsBk|
  '----'    '-------------------' '-------------------' '-------------------' '--------------'
  ,-------------------------------------------------------------------------. ,--------------. 
  |  ~ | !  |  @ |  # |  $ |  % |  ^ |  & |  * |  ( |  ) |  _ |  + |  Bspc  | | Ins|Home|PgUp| 
  |-------------------------------------------------------------------------| |--------------| 
  | Tab  |PgUp|Home| Up | End|    |    |    |    |    |    | {  |  } |   |  | | Del|End |PgDn| 
  |-------------------------------------------------------------------------| '--------------'
  | Bckspc|PgDn|Left|Down|Rght|    |    |    |    |    |    | '  |   Enter  |                 
  |-------------------------------------------------------------------------|      ,----.     
  |   LSPO  | Z  | X  |  C | V  |    |    |    |  , |  . |  / |    RSPC     |      | Up |     
  |-------------------------------------------------------------------------| ,--------------.
  |Ctrl|LGUI|LAlt|               		                    |MSE |RGUI|Menu|Ctrl| |Left|Down|Rght|
  '-------------------------------------------------------------------------' '--------------'

 	* The *LOWER* layer contains a navigation cluster on the left hand. This layer is momentary when the spacebar or LOWER (RAlt) key is held and toggled on/off when the LOWER key is tapped.
	
	* The Navigation cluster is offset to the right compared to the traditional **WASD** nav cluster. With this implementation, you don't need to move your hand from the home position when navigating. Page Up & Down keys are found on the far left of the cluster.

 	* All unused (blank on the above keymap) keys are locked out using the XXXXXXX filler (KC_NO), all modifiers (edge |_| keys \[except 0, \. & Fn\] on the above keymap) and the ZXCV cluster are transparent (_______) to the Base layer.

### MOUSE

  ,----.    ,-------------------. ,-------------------. ,-------------------. ,--------------.
  |ESC |    | F1 | F2 | F3 | F4 | | F5 | F6 | F7 | F8 | | F9 |F10 |F11 |F12 | |PrSc|ScLk|PsBk|
  '----'    '-------------------' '-------------------' '-------------------' '--------------'
  ,-------------------------------------------------------------------------. ,--------------. 
  |  ` | 1  |  2 |  3 | 4  |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |   Del  | | Ins|Home|PgUp| 
  |-------------------------------------------------------------------------| |--------------| 
  | Tab  | WhU| WhL| MsU| WhR|    |    | M3 | M4 | M5 |    | [  |  ] |   \  | | Del|End |PgDn| 
  |-------------------------------------------------------------------------| '--------------'
  | BSPC  | WhD| MsL| MsD| MsR|    |    |LClk |RClk |    |    | '  |   Enter  |                 
  |-------------------------------------------------------------------------|      ,----.     
  |   LSPO  | Z  | X  |  C | V  |    |    |    |  , |  . |  / |    RSPC     |      | Up |     
  |-------------------------------------------------------------------------| ,--------------.
  |Ctrl|LGUI|LAlt|               Accel ++               |MSE |RGUI|Menu|Ctrl| |Left|Down|Rght|
  '-------------------------------------------------------------------------' '--------------'

 	* The *MOUSE* layer contains keys replicating functions found on the mouse. 
 		* The navigation cluster (Up, Down, Left, Right) is a replication of the Navigation cluster on the *LOWER* layer. The scroll keys are analagous to the Page Up & Down keys.
 		* The primary click (right & left) buttons are on the right home row (index & middle fingers)
 		* Secondary click buttons are above the standard keys (M3/Wheel click, M4, M5) but I do not use this function.
