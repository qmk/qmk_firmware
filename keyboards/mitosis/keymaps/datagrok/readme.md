# a layout for the Mitosis

- Emphasis on momentary modifiers, all usable from either hand, arranged symmetrically, but left/right distinguishable by the OS.
  I place left- and right-versions of Shift, GUI ("Super"), and Alt ("Meta"), and Henkan/Muhenkan (which I plan to overload for "Hyper").

  I'm going for a [Space Cadet](https://en.wikipedia.org/wiki/Space-cadet_keyboard) aesthetic;
  I want a keyboard that can (even just in theory) make use of all the bucky bits my operating system can support.

- Red key and Blue key momentary-enable (like a shift key) one of three layers:

    - Red: Symbols layer
    - Blue: Numbers layer
    - "Purple" (both Red and Blue): Functions layer
    
  This tri-state layer mechanism is a bit similar to Planck and Preonic's "Raise," "Lower," and "Adjust."

- The base layer is QWERTY.
  [Colemak][], [Dvorak][], and [Workman][] may be toggled using `Red`+`Blue`+`Z`.
  When you find the one you like, save it with `Shift`+`Red`+`Blue`+`Z`.

- Minimize hand travel, so as not to lose orientation with home row.

- `?` and `!` are moved to take the place of `<` and `>`.
  Rationale: unmodded and shifted keys should be for prose, while symbols useful for programming should be colocated on their own layer.

- Key positions chosen for mnemonics.
  For example, you can distinguish between alphanumeric numerals and keypad numerals, but they occupy the same key positions.

## Layout Images

![mitosis:datagrok layout base layer](https://i.imgur.com/tap5Pjf.png)

Base layer. Notes:
- customized comma and period, which have exclamation point and question mark on their shift layer.
- tap right-shift for underscore, tap left-shift for tab.

![mitosis:datagrok layout red layer](https://i.imgur.com/sMGr34T.png)

Red layer. Intended for common navigation and programming symbols. Notes:
- symmetric layout of paired braces/brackets/slashes for easier memorization
- arrows placed directly on home position

![mitosis:datagrok layout blue layer](https://i.imgur.com/dDb2563.png)

Blue layer. Intended for "number pad." Notes:
- Keycodes generated for numbers, enter key, and mathematical symbols are from the alphanumeric keys, not keypad.
  This way they are not influenced by the state of Num Lock.
  If you want to send the keypad equivalents, just press Blue as well to access keypad numbers in the same positions in the Purple layer.

![mitosis:datagrok layout purple layer](https://i.imgur.com/pESzy2u.png)

Purple (Red+Blue) layer. Intended for "true keypad" and various functions. Notes:
- Numbers on this layer send Keypad codes, so the result will be affected by the state of Num Lock.
- "Switch Layout" toggles the alphabet keys between QWERTY, Colemak, Dvorak, and Workman.
  Shift + "Switch Layout" stores the currently selected alphabet layout in eeprom, so the selection persists across reboots and computers.
- Page Up / Page Down / Home / End are placed on corresponding arrow keys.

Keyboard layout editor sources:
[base](http://www.keyboard-layout-editor.com/#/gists/bc2d06a3203d1bc3a14ed2245cf39643)
[red](http://www.keyboard-layout-editor.com/#/gists/dbbf65f726a5522824b75117a62a321e)
[blue](http://www.keyboard-layout-editor.com/#/gists/240e807f3d7e1d3ddabe1b69ee675048)
[purple](http://www.keyboard-layout-editor.com/#/gists/9559f0f8bb1ee47677c8f2b4d766829d)

[Imgur album](https://imgur.com/a/hm4bbdM)

## Indicators

- When Red layer is active, the RGB indicator turns red.
- When Blue layer is active, the RGB indicator turns blue.
- When Purple layer is active, the RGB indicator turns purple.
- When the Workman layer is active, the RGB indicator turns green.
  Currently, this means that activating the Red layer while using the Workman layout will make the indicator show yellow. (red + green.)
- The Num Lock status is shown on the Pro Micro tx LED.
- If you attach a speaker to PC6 (pin 5) and compile with AUDIO_ENABLE=yes, music will be played at startup, when switching default layers, and when saving the default layer.

## Variants

Some additional compile-time options for this layout are available by editing rules.mk or compiling like so:

Normal compilation:

```make mitosis:datagrok```

Swap Space onto bottom thumb row: swaps Red/Backspace/Space/Red with Blue/Shift/Shift/Blue:

```make mitosis:datagrok MITOSIS_DATAGROK_BOTTOMSPACE=yes```

Lower baud UART. Useful when using an 8Mhz pro micro; corresponding changes required in wireless firmware. See rules.mk for details.

```make mitosis:datagrok MITOSIS_DATAGROK_SLOWUART=yes```

## Design notes

### Workman layout

- I'm learning a new physical key placement, so I might as well go all-out and use an optimal non-QWERTY layout.
  Bonus: it's easy to switch back to QWERTY on a traditional row-staggered keyboard.
  The designer of the Mitosis had [a similar experience](https://www.reddit.com/r/MechanicalKeyboards/comments/66588f/wireless_split_qmk_mitosis/dgfr22q/).

- I like the way Workman feels and some of its advantages over Colemak.
  Unfortunately, it was designed using a weighting system based on a standard
  row-staggered keyboard so is probably not as optimal as one could achieve
  on an ergonomic board like the Mitosis. Maybe run an optimizer routine after I
  determine good values for key difficulty on the Mitosis.

### 8Mhz Pro Micro

- I (used to) use a 3.3v Pro Micro clocked at 8Mhz rather than the 5v 16Mhz specified in the Mitosis design.
  That can't communicate with the connected wireless module at the default speed of 1M baud.
  The next fastest baudrate that works without errors is 250k baud.
  So if you want to do the same:

    - Set the Pro Micro clock and baud rate correctly in `rules.mk`:
      ```
      F_CPU = 800000
      MITOSIS_DATAGROK_SLOWUART = yes
      ```
    - Configure the receiver's wireless module to communicate at 250k baud in `main.c`. See https://github.com/reversebias/mitosis/pull/10
      ```
      -          UART_BAUDRATE_BAUDRATE_Baud1M
      +          UART_BAUDRATE_BAUDRATE_Baud250000
      ```

### Layout mnemonics

- Paired programming symbols (braces, brackets, parentheses) are arranged symmetrically in the Red layer.

- Arrow keys are in the home position on the Red layer.

  - Blue+Arrows = PgUp/PgDn/Home/End, which is intuitive for me and similar to what is done on Apple and some Dell keyboards.

- The number pad: I placed the ten-key number pad on the Blue layer.
  However, this would do the wrong thing when Num Lock was not enabled.
  Rather than attempt to manage the state of Num Lock, I arranged the normal number keys in a ten-key layout on the Blue layer instead.
  If you explicitly want the keypad keys, they're in the same position on the Red+Blue layer.

- Number-pad add, subtract, multiply, and divide are located on the same keys as alphanumeric plus, dash, asterisk, and slash, respectively.

- The Function-keys are arranged to mimic the order of the ten-key pad.

- Enter is now in a more qwerty-familiar location, and may be activated with one hand.
  Numpad Enter is in the same position for mnemonics.

- Why do I dislike [snake\_case](https://en.wikipedia.org/wiki/Snake_case) (`__variable_names_that_use_underscores_`)?
  Maybe because it's hard to type all those underscores requiring the shift key?
  Hypothesis: I'll be less annoyed by snake case by placing `_` at an unmodded position, right near the `space` key.


## Changelog

### Current

- Discard "intentionally difficult backspace" idea.
  Tab returns to left-shift.
  Del returns to Red+Backspace
- "High Profile mode:" Swap Red/Backspace/Space/Red with Blue/Shift/Shift/Blue (placing space on lower thumb keys) using `MITOSIS_DATAGROK_BOTTOMSPACE=yes` when compiling.
- Move Print Screen / Scroll Lock / Pause to pinky column on Blue layer.
- Let's try using TT instead of MO so we can e.g. lock-on the keypad.
  - We still use MO for first modifier, so e.g. Red + tapping Blue will lock purple.
    So far it feels a bit janky, we'll see.
- One key `KC_LAYO` to cycle through available base layers instead of a dedicated key for each;
  Shift + `KC_LAYO` stores current base layer selection in eeprom so it comes back after disconnecting or a reset.
- Added Colemak and Dvorak as default layers that may be selected.
- Set UART to 250kbaud with make argument `MITOSIS_DATAGROK_SLOWUART=yes`, for use with 8Mhz Pro Micros.
- Display Num Lock status on tx LED

### 0.6.60

- Experiment: no-modifier underscore on right shift key.
- New combined numbers + keypad arrangement.
  No more worrying about Num Lock key.
- Move F-keys to left board to make room.
  Calling them "the Numbers layer" and "the Functions layer" is now less accurate but the arrangement feels better.
- Audio working!
- Move Tab and Space to upper thumb row.
  I discarded the high-profile acrylic case from my Mitosis.
  With a low-profile case, it's easier to hit the upper row of thumb keys.
- Discard all my `#defines` for "Meta", "Super", and "Hyper".
  I can call them that without making the code confusing to others.
- Move Backspace to Red+A. I shouldn't be using it much anyway.
  This means Tab and Shift might as well be separate keys again.
- Distribute paired symbols symmetrically across boards like `\<{([ ])}>/`.
  Opening-symbols on the right hand was a failed experiment. 
- Change default back to target a 16Mhz/5v Pro Micro.
  I damaged the 8Mhz Pro Micro I was using so now I'm back to using a 16mhz Pro Micro again.

### 0.6.1

- Place Tab on Shift without a modifier. We use it frequently for autocomplete.
- Make QWERTY the default layout. So more people can try it out. My customized Workman is easily toggled-on.
- Don't use redundant `#define` for `KC_TRNS`
- Place Num Lock somewhere. Otherwise (if it gets turned off) we can't type any numbers!
- Add some media keys

### 0.5.155

- Enable use with my 3.3v Pro Micro
- Add a toggle-able QWERTY layer
- Golf down the LED-setting code
- Place `!` and `?` on `Shift`+`,` and `Shift`+`.`.
- Distribute paired symbols symmetrically across boards like `\)}]> <[{(/`

### 0.5.129

- A modified Workman variant for Mitosis
- Arrows in home position, modifier + Arrow = PgUp/PgDn/Home/End
- Load all paired symbols onto angle-bracket keys.

### Abandoned ideas

- Abandoned: intentionally-difficult backspace.
  "Backspace is one of the keys I most dislike on a QWERTY keyboard because it moves me away from homerow and I need to use it so often.
  Rather than make it easier to strike, I want to discourage myself from using it and train myself to type more accurately."
  
    - Many other people like an easy-to-reach backspace.
    - Many other split-spacebar ergo boards place backspace at the thumbs.
    - I can still train myself to type well with it in an easy location.
    - I couldn't think of anything really better to put opposite space.

- Abandoned: pile all brackets onto one pair of keys.
  "Since QWERTY and Workman keep angle brackets together, place other enclosing symbols on the same keys."

    - I didn't like having to pick the right modifier to get the right flavor of bracket.
      Instead, now, one modifier activates a symbols layer where all brackets are easily accessible.

- Abandoned: chorded Enter without proper chording detection

    - I tried to make Red+Space = Enter with the intention that I could hit both with my thumb.
      That didn't work well; I always trigger space first when mashing the keys
      simultaneously. ~~This might not continue to be true if I change the angle
      at which I strike the keys e.g. with a neoprene base or a wrist support.~~
      Even with a wrist rest or low-profile, this is hard to do with one hand.
      Need to adjust the firmware to understand chorded thumb keys.

## To do

- Ctrl+'+' doesn't seem to work; fix.
- **Shared Layouts.**
  Figure out how to make use of QMK's common `layouts/`
- **Chorded Combos.**
  Since the thumb keys are arranged such that it's easy to smash pairs of keys with just one thumb, figure out how to enable chording.
  For example, a single-finger Shift+Space or Red+Space that doesn't do the wrong thing if Space happens to trigger first.
- Improve **LED indications** (may require modding bluetooth firmware):
    - Num Lock status
    - Is any board nonresponsive (which one?)
    - Does either board have a low battery?
- **Num Lock management.**
  Num lock currently occupies prime real estate, but I never use it except to fix it when it's wrong.
  Do any of my applications use it?
  Should I have the firmware ensure it is set how I want it?
  Maybe cause it to be momentary active with Blue?
  See [@drashna's comment](https://github.com/qmk/qmk_firmware/pull/2366#issuecomment-404951953) for code to force it always-on, which I don't know if I want.
- ~~Store default layer in eeprom?~~
- Allow "!? on ,." to be easily toggled-off.
- Modularize "!? on ,." so it can be easily used on any QMK keyboard. (about half done)
- See if the henkan/muhenkan placement is at all useful for Japanese speakers,
  or abuse different keysyms for Left/Right Hyper. (Original space cadet used
  scancodes 145/175. 145 is LANG2, 175 is "reserved" in USB HID spec.)
- Implement "layer lock" key
- Feature parity with popular boards e.g. Planck?
  - Layers for ~~Dvorak, Coleman,~~ Plover
  - More music and midi stuff
  - Macros?
- Improve tri-layer behavior
- Find out what `update_tri_layer_state` offers that my simple layers arrangement lacks.
- ~~Find a better location for Caps Lock, PrintScr/SysRq, Scroll Lock, Pause/Break,~~.
  Placed on Blue layer. Caps will be Shift+"Layer Lock," once I get that working.
- ~~Figure out where to place non-numpad numbers so we don't need num lock turned on to type them?~~
- ~~Add Insert, PrintScr, Pause/Break~~
- ~~Make QWERTY base layer for people who customize layout in software?~~
  I default to QWERTY now.
- ~~Mod a buzzer onto my receiver and enable tones~~ Easy and works!

[Workman]: https://viralintrospection.wordpress.com/2010/09/06/a-different-philosophy-in-designing-keyboard-layouts/
