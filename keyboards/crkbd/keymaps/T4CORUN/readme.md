# T4CORUN Corne V3

- Author: Victor Nguyen
- This is my keymap for a Corne V3.0.1.
- QMK Compile Command:

	```Makefile
	qmk compile -kb crkbd/rev1 -km T4CORUN
	```

- Keymap is heavily inspired by [Miryoku](https://github.com/manna-harbour/miryoku).

	```text
	Userspace
	C:\QMK Firmware\users\manna-harbour_miryoku

	Split 3x6 example
	C:\QMK Firmware\layouts\community\split_3x6_3\manna-harbour_miryoku
	```

- Code structure heavily inspired by Drashna

	```text
	Userspace
	C:\QMK Firmware\users\drashna

	Split 3x6 example
	C:\QMK Firmware\layouts\community\split_3x6_3\drashna
	```

- My keymap utilizes code from my userspace. Please review for more information

	```text
	C:\QMK Firmware\users\T4CORUN
	```

---

## General Notes

- [Crkbd GitHub](https://github.com/foostan/crkbd)
- [Corne V3.01 Build Guide](https://github.com/foostan/crkbd/blob/main/corne-cherry/doc/v3/buildguide_en.md)
- [Firmware Build Guide](https://github.com/foostan/crkbd/blob/main/doc/firmware_en.md)

Notes/Learnings so far:

- [Dimensions 94 x 135 x 40? mm 5.3 x 3.7 in](https://josef-adamcik.cz/electronics/corne-keyboard-build-log.html)
- [Review](https://devpew.com/blog/corne-eng/)
- for a case you would need 5.3 x 7.4 in or 10.6 x 3.7 in

---

## Changelog

2021-10-13

- Created T4CORUN keymap based on the crkbd/rev1 default keymap
- Added my qmk user files ```#include "T4CORUN.h"```
- Improved readability copying the planck structure
	- by enumerating the layer names
	- layer comment to visualize the keymap
- Setup initial layers for `_QWERTY`, `_COLEMAK`,`_SYMBOL`, `_NUMBER`, `_NAVIGATION`, `_FUNCTION`, `_MOUSE`, and `_ADJUST`
- Established my keymap based on Miroyku. Mine ended up being a hand swap from the prescribed as I like using arrow keys with my left hand and the numpad with the right.
- Removed unused bindings for both keybozzzzards from `TACORUN.h` to save space
- Enabled `RGB_MATRIX_ENABLE` per the readme and disabled a bunch of animations to save space
- Optimized `oled_render_layer_state` function to use my layer enumerations
- Can switch between QWERTY and COLEMAK. QWERTY is the default layer upon startup.

2021-11-18

- Able to set the default layer without touching the EEPROM
- Cleaned up the formatting of all the Existing OLED code
- the OLED screen will show the default/base layer (QWERTY or COLEMAK DH)

2021-11-21

- Added some options to the rules.mk/config.h to reduce the file size
- Replaced all of the default keymap OLED code with the one from Drashna's OLED example keymap and tweaked it some (e.g. removed the bootmagic stuff). Overall it shows way more status info now. It turns out he based it off of his stuff in his user profile, but this was much easier to follow.

2021-11-21

- Cleaned up the comments
- Added the enter, app, and escape to the symbols, navigation, number, function, mouse
- Moved caps lock to the function layer.
- Enabled A on the navigation layer so I can do ctrl-A
- swapped the layer tab for function and mouse. Cleaned up the T4CORUN.h
- Added the UCCPR shortcuts to the mouse layer. Cleaned up some buttons too
- Cleaned up some comments on the Adjust layer
- Reordered the layer enum to match the order in my Corne keymap

2021-11-23

- Had a front RGB Scare. I was trying to show the RGB mode on the screen and then the RGB wigged out. Now I have a testRGB keymap to try out the RGB. I think I had to flash the handedness in `QMKToolbox.exe` in order for the RGB to work
- I cleaned up my user profile. cleaned up the defines mostly
- Made the polling rate keyboard specific. Maybe my Atmega32u4 doesn't like 1000Hz. I set mine to 500Hz.
- Made the `Tapping_Term` to 150 instead of 200 because I was typing in n instead of _

2021-11-26

- Added a custom wakeup and power down things to get the OLED and LEDs to turn off when the computer is off. This didn't work
- This is where keymap_beforeConversion.c stops

2021-11-26

- Copied the old code to this folder before the conversion. See that readme for more information

	```text
	C:\QMK Firmware\keyboards\crkbd\keymaps\T4CORUN_beforeConversion
	```

- Implemented wrappers like Drashna did for my Miryoku layout, so I can reuse code for different keyboards
- Revamped this readme file
- Adjusted code for all the breaking changes in the 27-Nov Changelog. Get my firmware to compile again.

2021-11-29

- Fixed a bug in the wrapper.h where `_______________MOD_CMDS_L1_________________` was not mapped correctly. Lost Snipping Tool Shortcut

	```C
	#define _______________MOD_CMDS_L1_________________         ___x___, ___x___, ___x___, W_SNIP,  KC_DEL
	```

- Changed the polling rate back to 1000Hz
- Changed the global tapping term from 150 to 160
- Added another check for the crkbd keyboard after reviewing Drashna's profile

	```C
	#elif defined(KEYBOARD_crkbd_rev1) || defined(KEYBOARD_crkbd)
	```

2021-12-02

- I struggled with moving the cursor when I held space down too long when I am typing. Doing some reshuffling.
	- Made the space key dedicated
	- Removed the symbol layer. Now I will activate number and press shift to get symbols
	- Moved the function layer to the right half.
	- Redid the layer tap keys. Function and Number on the Left; Navigation and Mouse on the right.

2021-12-07

- Updated my wrappers for row 4 when I was updating my planck to make it fit 4x12 better
- Changed the wrapper so that the ADJUST Right side has Music controls if AUDIO_ENABLE but is blank when its not.
- Added a Windows Explorer Shortcut

2021-12-12

- Renamed some of the wrappers for clarity.
- Redid the order of the media keys to be consistent with the other keyboards

2022-01-23

- swapped ADJUST and Escape after I used Excel. I had to move some of the basemap keys around
- Added `_________EDIT_L3_________` wrapper so I can get delete and backspace where I'm used to on my navigation layer
- Removed Control and Alt from the MOUSE Layer
- This is where keymap3x6.c stops

2022-02-20

- Consolidated all my corne keymaps together since the config.h and rules.mk are the same. I renamed them so its easier to find. Just need to rename them to keymap.c if I want to compile them
- Made a new Keymap for 3x5.

	- Commented out all the outer column mappings and remapped them to other layers via wrapper

- Keymap 3x6

	- Removed DEBUG from the left side of ADJUST Layer
	- Swapped EDIT_L3 wrapper to NAVIGATION_L4 for more consistent naming conventions

- Config.h (userspace)

	- Added a new define global variable `SPLIT3X5` which affects which wrapper.h definitions are used
	- Comment out this line for the planck, dz60, and split 3x6
	- Moved `NO_ACTION_ONESHOT` from the keyboard config.h to the userspace.h because that was causing my One shot mods not to work
	- I also learned that `TAPPING_FORCE_HOLD` will break one shot keys, so I took it out of the 3x5 configuration and added it back to the other keyboards
	- Cleaned up the code to make it more consistent and robust.

- Wrapper.h

	- Added conditional blocks for the 3x5 and default 3x6 definitions so my variable names don't need to change, thus my keymap files can stay mostly the same
	- Implemented one shot mods just for 3x5
	- Moved `Esc` to the `Q` key on layers just for 3x5. Made it a grave escape. I might set it back
	- Moved `;` to the Numpad replacing space just for 3x5
	- Implemented the Control A shortcut for all keyboards
	- Removed Snipping tool shortcut from right side keyboard for all keyboards
	- Added enter to the left side thumb cluster on layers for all keyboards

- Tacorun.h

	- Implemented One shot mods
	- Added mappings to Toggle Layers. I think I can use this to enable mouse and function layer when the encoders come in.
	- Added a new key mapping for control A

2022-02-23

- Userspace tapping.c

	- I straight ripped off drashna's and removed stuff I didn't want to have right now. I enabled per key `IGNORE_MOD_TAP_INTERRUPT_PER_KEY`, `TAPPING_FORCE_HOLD_PER_KEY`, and `TAPPING_TERM_PER_KEY`. 
	- Set a custom `TAPPING_FORCE_HOLD_PER_KEY` for my `NUM_BSP` because I was getting repeated backspace if I rapidly press it twice and hold on the second press, when I wanted a number layer
	- Hope the tapping term ends up 175 instead of the default 200 as found in the action_tapping.h in the quantum folder

- Userspace config.h

	- Embraced the philosphy that this file affects all keyboards so I moved the per keyboard things to each keyboards config.h
	- Left the SPLIT3X5 logic in here because I might want to emulate the Rollow 3x5 wrapper onto multiple keyboards.
	- However moved the variable definition to the keymap config.h. Hope it takes effect here

- Userspace Wrapper.h

	- Removed Grave Escape and turned off the functionality in the keymap rules.mk
	- Replaced `KC_DEL` with `KC_GRV` in the 3x5 mappings
	- Replaced `KC_GRV` with `KC_SCLN` in the 3x5 mappings. Im debating if I should put the semicolon on the left side so I don't have to relearn where grave is.
	- Restored Space on the Numpad layer

2022-02-27

- In my userspace and crkbd keymaps I made all the indentations 2 spaces
- I removed the commented out code in the wrappers. I decided I was okay with the grave key to be on the left half of the keyboard
- Lowered the tapping term of the `NUM_BSP` key to 150 to see if it that helps with my keyboard shortcuts on that hand
- I successfully moved all my OLED stuff into my userspace. It wasn't as painful as I thought it was going to be. I removed all the OLED stuff from my corne keymap

2022-03-03

- I adjusted the tapping term to 200

2022-04-16

- It is not very efficient with miyroku for coding. I have to switch between shift and number alot for random symbols. Went back to more what my planck was lol.
	- Moved NAV key back to left hand and Number back to right hand
	- Number row
- Fixed F12
- Put Tab and Del on the MODS_CMD_R3
- Put Enter on MODS_CMD_R2
- Mirrored the MODS_CMD_L1 to R1
- Removed layer taps for func and mouse ahead of the encoder
- Added another command for the KEYLOG_ENABLE to turn off the keylogger in the OLED. This saves a good chunk of memory

Future

- Clean up  the ADJUST Layer
- Fix the planck and make it a split keyboard
- Maybe remove all the 3x6 stuff maybe now that my 3x5 Rollow is taking over

2022-04-24

- Enabled combos using the germ way. I have to add that include g/key_combos.h in my keymap.c or i get linker errors. boo
- Made the code more robust to turning off/on features. Shouldn't need to change code to change settings in the rules.mk
- Cleaned up the wrapper file. Made it easier to read. Grouped the left half and right half together
- had to turn off the RGB in order for the firmware to fit on the MCU
- fixed a bug where only one side for the RGBLIGHT worked

2022-04-25

- updated the combos
- cleaned up the wrapper some

2022-05-08

- stopped using the semi colon and colon tap dance. Tab wouldn't activate on the number layer

2022-08-09

- Added Tab to the keymap

2022-08-10

- I redid a lot of files to make it more ready for Rollow (two thumb keys only). I'm going to do more Miryoku after driving it for a little bit. like pinky layers
- Made the code more robust. Added custom flags to rules.mk and code to handle them.
- Removed unnecessary code (One shot mods, Number/Function Row, Key mappings)
-	I	was	able to add RGB	Matrix effects again.

2022-08-14

- undid some of the stuff. i put shift and space back where i had it. now	it is	a	shift	enter	mod	tap	because	i	got	used to having enter on the home row
- function layer is now held down with the Z key
- tuned the tapping term for home row mods

2022-08-15

- Removed the enter on the thumb shift. Put enter on a layer
- Fixed a bug on the adjust

2022-08-16

- Changed the behavior of the Enter Key
- Optimized and removed keys I plan not to use

2022-08-28

- More tweaks to make the numpad feel better

2023-01-02

- Refresh keymap to match rollow

2023-02-20

- Refresh keymap to match rollow

## To do List

- Consider taking more of Drashna's OLED stuff. He seems to have 256 keycode and the kitty animation in there. Maybe I can replace my right side with that

## Pondering

- consider flipping zero and period on the number pad
- Maybe do some autocorrection? [Autocorrection with QMK](https://getreuer.info/posts/keyboards/autocorrection/index.html)
- Could reintroduce the symbols layer to do better rolls. right now its awkward as hell to type in >=.

	- hold shift, press /, hold backspace, press ;
	- [Symbol Optimizations](https://getreuer.info/posts/keyboards/symbol-layer/index.html)

- [Word Selection](https://hip2save.com/tips/amazon-prime-membership-price-increase/)
- Instead of redesigning symbols we can implement macros for commonly used stuff

	- symbols >= != <= etc
	- SQL stuff INNER JOIN, SELECT * FROM, etc
	- Markdown URL syntax
	- Maybe implement tap dance for the equal sign? this may let me cycle through the symbols, but it may cost me a lot of memory. On the Rollow it may work because there is no OLED

- Swapper for easier alt tab [Callum Oakley](https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum#oneshot-modifiers). I guess I don't have to do this because one shot toggle lets me hold down alt
- Consider changing your one shot toggle setting from 3 to 2?
- [how do you use rotary encoders](https://www.reddit.com/r/ErgoMechKeyboards/comments/j8cfwr/what_do_you_use_your_rotary_encoder_for/)
- [uses for rotary encoders with code examples](https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-)

More keymap ideas can be found [here](https://www.reddit.com/r/ErgoMechKeyboards/comments/r7y42o/keymap_tinkering/)

## Lessons Learned from development

- The master side does not send certain signals/states the slave side, so things like the slave side not going to sleep happen
- Unplugging the TRRS cable while the USB is plugged in may kill the board
- If I enabled ehnanced communication between master and slave side, the keyboard will freeze up or glitch (e.g. `SPLIT_OLED_ENABLE` and `SPLIT_LAYER_STATE_ENABLE`)

## My Requirements

This is my 3rd Keyboard. Based on all my experiences

- Left thumb shift
- Right thumb spacebar
- Dedicated Homerow mods
- I learn towards doing backspace over delete
- I do not like homerow mods but I have not trained my hands for that
- Like having a dedicated snip and sketch shortcut
- Right now I prefer having home row numbers over a numpad, but I will get used to the latter.
- I do like having volume keys on the default layer
- I do like having all four mods as dedicated keys
- Holding modifiers to select columns. (Shift Alt)
- Keys Shortcuts I use all the time
	- Column Cursor/Select (Shift Alt)
	- Lock Computer (Win L)
	- Switch Apps (Alt Tab)
	- Snip and Sketch (Win Shift S)
	- Backspace entire words (Ctrl Backspace)
	- Cursor through words (Ctrl Arrows)
	- Select words (Ctrl Shift Arrows)
	- Media Keys (Vol Up/Down and Mute)
	- Tab entire paragraphs (Tab / Shift Tab)
	- Snap Windows (Win Arrow)
	- Open File Explorer (Win E)
	- Clear Desktop (Win D)
	- Undo, Cut, Copy, Paste (Ctrl Z X C V)

## [Etsy Beekeeb - Leo](https://www.etsy.com/listing/1017177758/pre-soldered-crkbd-v3-corne-keyboard-diy?ref=yr_purchases&variation1=2261234011)

Product Description

- latest version v3.0.1
- Support QMK firmware for custom keymaps
- Support Kailh MX hotswap
- Improved symmetry
- South facing switches
- RGB LEDs SK6812MINI-E
- Underglow SMD RGB LEDs WS2812B-5050
- The keyboard is pre-soldered. Soldering is not required.
- There might be some no-clean flux residues.

This kit contains:

- One set of white or black PCBs contains the left side and the right side.
- Pro Micro Controller Boards
- Custom-made low profile 12P pin headers
- SMD Diodes
- Kailh hotswap sockets for MX
- TRRS jacks PJ-320A
- TRRS Cable
- Reset tactile switches (6mm*3mm) with gold plated connectors
- 0.91 128x32 OLED Displays
- Per key switches RGB LEDs SK6812MINI-E 3228
- Underglow RGB LEDs WS2812B-5050

Custom Order:

- If you have a special request, please message me for a custom order

Important note:

- You will need to buy and install key switches and key caps separately.
- Generic pro micro USB micro-B connectors are fragile.
- The Magnet Cable for Pro Micro is not included. It is an optional upgrade. [Magnetic Cable](https://www.etsy.com/listing/1086812633)
- [Optionally upgrade to USB Type-C ShiroC Pro Micro Alternative (2 controllers)](https://www.etsy.com/listing/997001176)
- [Source code and license](https://github.com/foostan/crkbd)
