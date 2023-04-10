# The Default Planck Layout

This is my Windows keymap for a Drop + OLKB Planck Rev 6.1. It is inspired by No by Noah and should be good for coding/scripting/SQL.

- [Noah Frederick](https://noahfrederick.com/log/the-planck-keyboard)

Compile Command:

```text
qmk compile -kb planck/rev6 -km T4CORUN
```

## Changelog

2021-07-24

- Created new Keymap file T4CORUN
- Added aliases for Layer Taps, Mod Taps, Windows Shortcuts.
- RAISE: Numbers layer. moved the numbers to home row. Has F1-F10 and calculation symbols
- LOWER: Navigation layer
- SYMBOLS: Activated by RAISE + LOWER. Has the symbols over the numbers and F11 and F12
- WINGUI: Mouse function and Windows Shortcuts. The idea is to mimic holding control

2021-07-25

- I got too used to enter being where shift is so I moved a lot of stuff back to the planck defaults. It also bothered me that I do not have a keycap with ' for the top row
- Space Cadet Shift is now Space Cadet alt

2021-07-26

- LOWER: make transparent A, Z, X, C, V so I can get copy, pasta, etc functions with Control Tap
- RAISE: make transparent . so I can do 21.3 without having to release RAISE
- Fixed a bug where GUI + direction keys do not work to snap. Need to use LGUI() instead of LGUI_T()
- Fixed a bug where the snipping tool shortcut didn't work LGUI + LSHIFT + S. Need to use LSG() instead of LAG_T()
- Turned off COMMAND_ENABLE in my rules.mk so space cadet will function without interfering with the COMMAND mode
- Changed Backspace to Delete on RAISE, SYMBOLS. On LOWER, the P is the Delete
- Removed TERM_ON and TERM_OFF

2021-07-26 Part 2

- Enabled per layer RGB per [QMK RGB Lighting](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md). This does remove the ability to change the HSV manually.
- ADJUST: Removed the RGB_MOD and HSV key mappings

2021-07-27

- Converted the keyboard from 1x 2u Spacebar to 2x 1u Spacebar
- Formatted comments
- Updated the music_mask_user with my custom keycodes
- Remove PLOVER Layer and references except for the Audio
- Remove BACKLIT references
- LOWER: Renamed Layer ```_LOWER``` to ```_NAV```
- SYMBOL: Renamed Layer ```_SYMBOLS``` to ```_LOWER```
- BASE: Change left space to Layer Tap ```NAV_BSP```
- BASE: Moved the ```AD_QUOT``` and ```AD_SLSH``` to the top right again. Rotated the keycap so it matches R2
- BASE: Moved ```KC_ENT``` up to R3 and changed it to Mod Tap ```CTL_ENT```
- BASE: Enabled Space Cadet Shift on both sides. Remove Space Cadet Alt
- BASE: Remove both Layer Tap ```GUI_L``` and ```GUI_R```
- BASE: Converted the aforementioned Layer Taps to ```CA_LBRC``` and ```CA_RBRC``` for VS Code
- BASE: Added Layer Tap ```SA_LCBR``` and ```SA_RCBR``` for notepad++ and SSMS
- RAISE: Moved ```KC_BSLS``` to the top right
- RAISE: Change left space to Layer Tap ```KC_DEL```
- RAISE: Added ```KC_TRNS``` for ```KC_SLSH```
- LOWER: Moved ```KC_PIPE``` to the top right
- LOWER: Change left space to Layer Tap ```KC_DEL```
- NAV: Remove delete key
- NAV: Added Mod Tap ```PRVWORD``` and ```NXTWORD```

2021-08-02

- RAISE: Change ```KC_UNDS``` to ```___x___```
- Added the ```IGNORE_MOD_TAP_INTERRUPT``` to config.h. "...requires holding both keys for the TAPPING_TERM to trigger the hold function (the mod)."
- Added global setting for ```TAPPING_TERM``` and set it to 150. Default is 200. This is to reduce time required for me to register a hold.
- Added a setting ```TAPPING_FORCE_HOLD``` so I can register a hold rather than repeat keys on second press. Now I will need to tap repeatedly to press a key.
- Added the setting ```PERMISSIVE_HOLD```. I understand what this does in theory, but I don't see why I need this yet

2021-08-02

- BASE: Added Home Row Modifiers GASC style
- Removed ```PERMISSIVE_HOLD```
- Adjusted ```TAPPING_TERM``` to 175 because I type too fast I guess I roll my keys so it would think I'm pressing the modifier on the home row
- NAV: Enabled Home Row Mods on this layer. Moved the large movement keys

2021-08-02

- Adjusted ```TAPPING_TERM``` to 190 because I was still triggering Modifiers on the home row while in a typing test.

2021-08-03

- I think I roll my keys a lot. For example I have issues with "ad" or "shift". I think I need to do per key settings. Added ```TAPPING_TERM_PER_KEY```
- added a function ```set_tapping_term``` and starting tuning the homerow mods. I added 50ms delay to the homerow keys and took 50 off the space cadet shift. In testing on monkeytype I am not triggering Home Row Mods by accident.

2021-08-04

- I was reading about the size of the MCU. I'm reading that it is a STM32F303. My chip on the PCB is 40pin for sure. ST says that in this form factor that it comes in 128kb and 256kb sizes. Internet says I have 256kb size. Therefore I do not understand why I can't enable tap dance.
- Turned off ```RGBLIGHT_ENABLE``` because i can barely see the lights on my keyboard and to see how much space I would save. It saved 4kb. It looked like when I flashed it, the RGB is on and set to red. I cannot toggle it off.
- Removed the PLOVER Song to see how much more it goes down. I commented out all the code in the ```dip_switch_update_user```. It goes from 46696 to 46544b so it doesn't save that much room.
- deleted ```NAV_BSP``` to see how much that would save. It saved no space. same 46544.
- Now i deleted the audio references in the ```dip_switch_update_user``` to see if I left commented in code would affect size. It did not change the size. The HEX is 128kb though.
- Re-enabled ```RGBLIGHT_ENABLE``` because I did not like that the red lights stay on despite the settings being off. this bumped up the bin size to 46544 to 50164 and the HEX size to 138kb.
- Turned off ```ENCODER_ENABLE``` as I do not use rotary encoders on this keyboard. It went from 50164 to 49788kb and 138kb to 137kb. When I remove the function in the keymap and there is no change in size.
- Turned off ```DIP_SWITCH_ENABLE``` and its function as I do not have a dipswitch here. I hope it doesn't affect the boot magic. 49788b to 49532b.

2021-08-08

- I should have been documenting all along
- turned the tap ```TAPPING_TERM``` to 200
- Enabled tap dance. I think my earlier issue was that I set the tap dance enum starting index too high. Starting from zero did the trick. I added two tap dance keys, to cycle through the braces/brackets.
- Disabled Space Cadet Shift, and went back to normal shift

2021-08-09

- Today focusing on some cleanup.
- Created a ```tap_dance.h``` and moved the tap dance method definitions to that file to cleanup the keymap.c
- Cleaned up the keymap grid comments
- BASE: Replaced the Shift+Alt Mod Tap Curly Brace with the WIN Layer toggle. With homerow mods I notice I hardly go into this layer anymore.
- BASE: went back to a regular backspace. Now I can hold backspace down, even though that is a bad practice.
- MOUSE: Renamed ```_WIN``` layer to ```_MOUSE```
- LOWER: Moved the media keys to this layer
- NAV: Moved the print screen and pause/break to this layer
- Removed unused keycode definitions

2021-08-11

- Moved all the key aliasing to ```key_alias.h``` to improve some readability of the ```keymap.c```. I actually do not know how from a C perspective the code still compiles.
- Added ```<``` and ```>``` to the brace tap dance
- NAV: added Caps Lock
- MOUSE: Renamed all Win Layer references to MOUSE

2021-08-12

- ADJUST: Remove the AG Swap keys
- ADJUST: Enabled ```DYNAMIC_MACRO_ENABLE``` and added those keys to the layer
- ADJUST: Shuffled around the whole layer so it makes sense
- GAMING: Added a new base layer for gaming. It is the QWERTY Layer from the base keymap.
- DVORAK: Removed this layer. Can always add it back later
- BASE: Removed some of the right hand mod-Tap keys I will not use, due to getting comfortable with home row mods with the right hand
- BASE: Replaced the right side mods with volume/mute
- RAISE: Moved Menu Key here on top of the GUI key
- NAV: MOved Page Up and Page Down to make it easier to navigate one handed

2021-08-14

- LOWER: Removed all the multimedia keys
- RAISE: Added Next song and Play/Pause to where the volume up and mute keys are
- GAMING: Removed the dedicated arrow keys. Added my Nav Backspace back. Then, added all the tap dance bracket keys to the far right of the board.

2021-08-15

- starting to implement user spaces. Let's see how this goes
- There may be two commits for this. I moved all the tap dance to the user space. I also was trying to understand how the definitions like ```KEYBOARD_planck_rev6``` worked. Right now it seems like magic.
- I also added breaks to the case statement in my planck keymap

2021-08-20

- BASE: Removed the <, > from tap dance as it is not very practical to hit that key
- BASE: Moved tap dance to the shift keys
- BASE: moved shift to the left space bar. Moved NAV and Lower over a key and removed Left Alt
- LOWER: is now my function row
- RAISE: is now numbers and symbols. I also removed some redundant symbols like * and / from this layer. I think I may also remove _ and + from this layer now that the shift key is in a easier spot.

2021-08-22

- Working on the split layout I decided to do some changes to my normal layout
- BASE: Removed home row keys because I kept activating shortcuts like sending emails.
- BASE: Moved the Escape Key to the bottom left so I don't press escape on accident while doing stuff like writing emails.
- BASE: Went back to a normal backspace key.
- LOWER: Is now my arrow keys
- LOWER: Added some frequently used shortcut keys so I can do them one handed. Snipping Tool, Undo, Cut, Copy, and Paste. The latter so I can do them without having to reposition my hands for undo and cut.
- LOWER: I added the mods to the right side so I can do selections and whatnot using the arrow key.
- FUNCTION: this is a new layer which is exclusively my functions. Those keys are designed to be used one handed.
- MOUSE: Added the snap + arrow keys.
- added sounds to layers so I know what layer I am on.

2021-09-12

- This may be my last update for a while. It looks like I didn't document my last set of changes very well
- FUNCTION: Put the leader key on the function layer. I keep pressing it when I want backspace. I realized I don't use leader all that much
- FUNCTION: Added tap dance bracket keys to this layer for when I am in gaming mode
- cleaned up the keymap comments because they were incorrect
- made the leader delay longer
- BASE: Decided to make dedicated space and lower keys
- GAMING: made it more like the default layers so I wouldn't get confused. I am thinking about removing this layer and gaming on my other keyboard because some FPS may need the number row.
- LEADER: I removed some unused mappings and adjusted some so its more intuitive

2021-10-24

- Inspired by manna-harbour_miryoku I moved the layer and keycode enumeration to my user profile. No impact on keyboard functionality

2021-11-21

- Moving some stuff from the user profile to the planck that is only specific to the planck. version.h.
- Made a backup of my old keymap
- Revising the planck keymap to match the corne
- Got everything to compile
- Remove the leader stuff and the tri layer stuff

2021-12-07

- Switching to using wrappers so it is easier to have all my keyboards to have the same bindings
- The extra keys on the planck are dedicated media keys. Playback on the left, and volume on the right
- Updated my wrappers for row 4 when I was updating my planck to make it fit 4x12 better
- Turned off One Shot Mods, Space Cadet Enable, Grave Escape Enable to save space
- Added more configuration and animations to the RGBLIGHT
- Changed the wrapper so that the ADJUST Right side has Music controls if AUDIO_ENABLE but is blank when its not.
- Added a Windows Explorer Shortcut

2021-12-12

- Renamed some of the wrappers for clarity.
- Redid the order of the media keys to be consistent with the other keyboards

2022-01-23

- Updated this keymap so it matches my Corne

2022-02-21

- Removed DEBUG from the left side of ADJUST layer as it is redundant
- Renamed the old Keymap.bak to Keymap_CodeExamples.c so I can see how I did stuff like leader and what not. I dont do this anymore so I will remove this from the userspace config.h

2023-01-02

- Updated the keymap to match the Rollow. Will turn the planck into a pseudo split keyboard

2023-01-16

- moved the thumb cluster inwards one position.
- added	a lower right escape key because i ran out of matching keycaps

2023-02-20

- Refresh keymap to match rollow

## Bugs / Improvements

- Audio
	- The startup noise doesn't play. This appears to be broken for a long time. The last time I known this works is Nov 2018
	- The music mode is now fixed but left alt doesn't play any sounds despite being in the music mask list [Music info](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_audio.md)
	- the key aliases I setup have a delay for music when I press the keys. Maybe I need to add the tap keys I have aliased in order to get rid of the delay. for example the [ in GUI_L
	- Need to add all the Home row mods to the music_mask_user function
	- Consider making the layers activate different sounds
- BASE Layer
	- Setup a HYPER { and HYPER }. [Purpose of Hyper](https://www.reddit.com/r/olkb/comments/7h0pe3/purpose_of_hyper_in_qmk/)
	- Do home row mods for DVORAK and COLEMAK
- LOWER Layer
	- I'm thinking about moving the function keys to here and on the bottom row because I keep pressing the function keys when I go for numbers. Maybe not as I will get used to it over time.
- RAISE Layer
	- Consider making the top row F1 through F12 on one layer rather than 1-10 and then 11-12.
- MOUSE Layer
	- Flesh this out. Maybe add back windows snap or something
- Make macros to type in common things like my logins and whatnot
- Make it match your corne keymap
- Fix the sounds playing as you added more layer

## My Research

- The shipped keymap is here [Default v6.1 Bin](https://github.com/qmk/qmk_firmware/releases/tag/planck-6.1) back in Nov-2018
- The current code has broken startup sound.
- This keymap is for a Rev6 part of the Drop + OLKB Planck Rev6.1
- The default keymap is for ```LAYOUT_planck_grid``` (4x12), but I verified but it still works for ```LAYOUT_planck_mit``` (2u Spacebar). The switch is wired for k36 not k35 on a rev6
- In order for the music mode to work, you need to specify keycodes and aliases in the function ```music_mask_user``` so they don't get recorded and sounds can play.
- the function ```update_tri_layer_state``` lets you hold lower and raise to go into a third layer
- set RGB_MATRIX_ENABLE = yes to get RGB_MOD key to work
- set COMMAND_ENABLE = no so Space Cadet won't do weird things. You have to hold left shift and right shift together to issue commands
- When I do per layer RGB color, I lose the ability to use the HSV. Only RGB_TOG remains
- When you set ```keyboard_post_init_user```, the #define RGBLIGHT_LAYERS variable must be in lower case. I don't know why
- On MT3 profile if you rotate R3 keys 180 degrees then they match up with R2 perfectly
- [Home Row Mods](https://precondition.github.io/home-row-mods). Definitely Want to implement home row mods. GACS

## Example Code

```C
//Enable per layer RGB
#ifdef RGBLIGHT_ENABLE
const rgblight_segment_t PROGMEM QWERTY_LED[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 9, HSV_PURPLE}       // Light 9 LEDs, starting with LED 0
);

const rgblight_segment_t PROGMEM LOWER_LED[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 9, HSV_CYAN} 
);

const rgblight_segment_t PROGMEM RAISE_LED[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 9, HSV_ORANGE} 
);

const rgblight_segment_t PROGMEM NAV_LED[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 9, HSV_WHITE} 
);

const rgblight_segment_t PROGMEM WINGUI_LED[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 9, HSV_BLUE} 
);

const rgblight_segment_t PROGMEM ADJUST_LED[] = RGBLIGHT_LAYER_SEGMENTS(
	{0, 9, HSV_RED} 
);

const rgblight_segment_t* const PROGMEM RGB_LAYERS[] = RGBLIGHT_LAYERS_LIST(
	QWERTY_LED,
	LOWER_LED,
	RAISE_LED,
	NAV_LED,
	WINGUI_LED,
	ADJUST_LED
);

void keyboard_post_init_user(void) {
	// Enable the LED layers
	rgblight_layers = RGB_LAYERS;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
	return state;
}
#endif

//This is what allows LOWER + RAISE to call ADJUST
layer_state_t layer_state_set_user(layer_state_t state) {
  #ifdef RGBLIGHT_ENABLE
  rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
  rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
  rgblight_set_layer_state(3, layer_state_cmp(state, _NAV));
  rgblight_set_layer_state(4, layer_state_cmp(state, _WINGUI));
  rgblight_set_layer_state(5, layer_state_cmp(state, _ADJUST));
  #endif
  return update_tri_layer_state(state, _LOWER, _RAISE, _WINGUI);
}
```
