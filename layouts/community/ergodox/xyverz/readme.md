# Xyverz's ErgoDox EZ Keymap

## About this keymap:

The Dvorak layout shown here stems from my early Kinesis years, using the Contour PS/2 with a Dvorak software layout. Because of this, the RBRC and LBRC were on opposite sides of the board in the corner keys. When I originally set up this keymap, I had decided to continue using this layout with my ErgoDox. I've since modified my layout to be more effective for me and to more closely match my other ortholinear keyboard layouts

The QWERTY layout shown here is based entirely on the Kinesis Advantage layout, with the additional keys as shown in the diagrams. The Colemak layout is merely an adaptation of that.

I've enabled persistent keymaps for Qwerty, Dvorak and Colemak layers, similar to the default Planck layouts.

## What's New:

* I've overhauled this Dvorak layout a bit to more match what I've got on my other Ortho boards. For some keys, I'm moving away from my old Kinesis keymap and adding the brackets and braces to the inner column vertical keys. I figure this will help me have better ease of use. In this update, I have also removed the keypad layer since I no longer use that at all, and have remapped the MEDIA layer a bit.

## Still to do:

 * Need to figure out a better position for the ESC key.
 * Come up with a function for the empty keys shown in the alpha layers below.
 * Fix the CapsLock, NumLock, and ScrLck LEDs.

### Layer 0: Dvorak layer

 	,--------------------------------------------------. ,--------------------------------------------------.
 	| ESC    |   1  |   2  |   3  |   4  |   5  |      | |      |   6  |   7  |   8  |   9  |   0  |  ~     |
 	|--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 	| Tab    |   '  |   ,  |   .  |   P  |   Y  |      | |      |   F  |   G  |   C  |   R  |   L  |   \    |
 	|--------+------+------+------+------+------|  [   | |   ]  |------+------+------+------+------+--------|
 	| CapsLk |   A  |   O  |   E  |   U  |   I  |------| |------|   D  |   H  |   T  |   N  |   S  |   -    |
 	|--------+------+------+------+------+------|  {   | |   }  |------+------+------+------+------+--------|
 	| LShift |   ;  |   Q  |   J  |   K  |   X  |      | |      |   B  |   M  |   W  |   V  |   Z  | RShift |
 	`--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
	  |MEDIA |   `  |   ~  | Left | Rght |                             |  Up  |  Dn  |   /  |   =  | MEDIA|
 	  `----------------------------------'                             `----------------------------------'
 	                                     ,-------------. ,-------------.
 	                                     | LCTL | LALT | | RGUI | RCTL |
 	                              ,------|------|------| |------+------+------.
 	                              |      |      | Home | | PgUp |      |      |
 	                              | BkSp | Del  |------| |------| Enter| Space|
 	                              |      |      | End  | | PgDn |      |      |
 	                              `--------------------' `--------------------'

### Layer 1: QWERTY layer

 	,--------------------------------------------------. ,--------------------------------------------------.
 	| ESC    |   1  |   2  |   3  |   4  |   5  |      | |      |   6  |   7  |   8  |   9  |   0  |   -    |
 	|--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 	| Tab    |   Q  |   W  |   E  |   R  |   T  |      | |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 	|--------+------+------+------+------+------|  [   | |   ]  |------+------+------+------+------+--------|
 	| CapsLk |   A  |   S  |   D  |   F  |   G  |------| |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 	|--------+------+------+------+------+------|  {   | |   }  |------+------+------+------+------+--------|
 	| LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 	`--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 	  |MEDIA |   `  |   =  | Left | Rght |                             |  Up  |  Dn  |   [  |   ]  | MEDIA|
 	  `----------------------------------'                             `----------------------------------'
 	                                     ,-------------. ,-------------.
 	                                     | LCTL | LALT | | RGUI | RCTL |
 	                              ,------|------|------| |------+------+------.
 	                              |      |      | Home | | PgUp |      |      |
 	                              | BkSp | Del  |------| |------| Enter| Space|
 	                              |      |      | End  | | PgDn |      |      |
 	                              `--------------------' `--------------------'
	 
### Keymap 2: Colemak layer

	,--------------------------------------------------. ,--------------------------------------------------.
 	| ESC    |   1  |   2  |   3  |   4  |   5  |      | |      |   6  |   7  |   8  |   9  |   0  |   -    |
 	|--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
	| Tab    |   Q  |   W  |   F  |   P  |   G  |      | |      |   J  |   L  |   U  |   Y  |   ;  |   \    |
 	|--------+------+------+------+------+------|  [   | |   ]  |------+------+------+------+------+--------|
 	| BkSpc  |   A  |   R  |   S  |   T  |   D  |------| |------|   H  |   N  |   E  |   I  |   O  |   '    |
 	|--------+------+------+------+------+------|  {   | |   }  |------+------+------+------+------+--------|
 	| LShift |   Z  |   X  |   C  |   V  |   B  |      | |      |   K  |   M  |   ,  |   .  |   /  | RShift |
 	`--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 	  | MEDIA|   `  |   =  | Left | Rght |                             |  Up  |  Dn  |   [  |   ]  | MEDIA|
 	  `----------------------------------'                             `----------------------------------'
 	                                     ,-------------. ,-------------.
 	                                     | LCTL | LALT | | RGUI | RCTL |
 	                              ,------|------|------| |------+------+------.
 	                              |      |      | Home | | PgUp |      |      |
 	                              | BkSp | Del  |------| |------| Enter| Space|
 	                              |      |      | End  | | PgDn |      |      |
 	                              `--------------------' `--------------------'

### layer 3 : Media layer

 	,--------------------------------------------------. ,--------------------------------------------------.
 	|   F11  |  F1  |  F2  |  F3  |  F4  |  F5  |TEENSY| |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11   |
 	|--------+------+------+------+------+-------------| |------+------+------+------+------+------+--------|
 	|        |      |      |      |      |      |      | |      |      | PrSc | ScLk | Paus |      |        |
 	|--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 	| CapsLk |      | Mute | Vol- | Vol+ |      |------| |------|      |Dvorak|Qwerty|Colmak|      |        |
 	|--------+------+------+------+------+------|      | |      |------+------+------+------+------+--------|
 	|        | Stop | Prev | Play | Next | Sel  |      | |      |      |      |      |      |      |        |
 	`--------+------+------+------+------+-------------' `-------------+------+------+------+------+--------'
 	  |      |      |      |      |      |                             |      |      |      |      |      |
 	  `----------------------------------'                             `----------------------------------'
	                                     ,-------------. ,-------------.
 	                                     |      |MacLck| |MacLck|      |
 	                              ,------|------|------| |------+------+------.
 	                              |      |      |      | |      |      |      |
 	                              |      |      |------| |------|      |      |
 	                              |      |      |      | |      |      |      |
 	                              `--------------------' `--------------------'