Overview
========

Warning: dvorak touch typist, that uses qwerty and bepo locales on my
computer.  40+ years of vi, 30 years of vi in Emacs.

Recent years I have gone minimal, I don't use most of the keys on my ergodox,
or original edition dactyl. These maps work great on large and small keyboards,
my preference seems to be 40% split ergo keyboards like the corne.

Everything here will fit on a 30 key keyboard. I'd prefer at least 34, personally.
I like the extra 4 thumb keys.

I think that what is special here is the layouts. I don't worry too
much about leds, or RGB, although I do like oled.  But really its mod_layer.h,
all the simple layer chunks and definitions, and the ability to apply that
to any keyboard with minimal effort. The other thing is the example it
provides for defining keymaps based on different OS locales. I use both
dvorak on Qwerty, and bepo/dvorak on bepo.  That means I must change my
locale on my OS to match my keyboard which can do qwerty or bepo locales.

It is possible, as I do, to send a keycode invoking xmonad, to execute my
qwerty - bepo switch on my computer. 

Besides using dvorak, another thing that colors my keyboard code is that I 
have used the kinesis
advantage for for more than 2 decades. I have used the ergodox ez for several years 
as well, so the evolution of my keymaps starts there with space, enter, backspace 
and delete keys on the thumbs.


Base Layers
-----------------
I like to experiment with layouts. So I have a few. 
They can be turned on and offical in config.h.

[The alternate keycodes for locales is located here](https://github.com/qmk/qmk_firmware/tree/master/quantum/keymap_extras)

on _en-us_, ie. **KC_** keycodes.
 * Dvorak
 * Beakl
 * Qwerty
 * Colemak
 * Workman
 * Norman
 * Carplax
 * Eucalyn

on _bepo-fr_, ie. **BP_** keycodes.
 * Bepo
 * Dvorak
 * Beakl

 
Keymaps
-----------
I really only have one. It's in map.h.  
My config.h has all the current usable settings.
Turn on the layers by enabling and choosing them in config.h. 
Default is to provide Dvorak, Qwerty, Colemak and beakl for _en-us_, 
as well as beakl, dvorak and bepo for the _bepo-fr_ locale.

There are corresponding Bepo layers as needed which will arrive if Bepo is enabled.

Layouts
-----------
This evolved from the old layout...wrapper code. Calling everything a wrapper seems
silly. So I took a step back. Still, it's just a chain of macros all nested.
It's turtles all the way down. 

Also, with all these layers it was a real pain to apply mods consistently and 
easily. So I changed the way I use keymap macro wrappers and added in my own
mod layer. The only thing it has is the mods to apply. No more editing keymaps
to apply mods.  I do it once, and it works everywhere I want.

I set up my layouts to take a 3x10 matrix, and sometimes an additional row for numbers.
I do like thumb keys but my current layout only requires 2 on each hand.

Mostly, I want my controls to stay the same. These are the keys on 
outside of the center 3x10 matrix. Although the number row might change
if the keyboard has them.

At the bottom of this chain of wrapping macros is the last turtle, the 
LAYOUT needed by the keyboard you have. 

Then I have my Layouts to feed it with my ROWS macros which are my MOD
layer. At the top of it all, I give a 3x10 or 4x10 keymap matrix to a layout 
and I have a complete keyboard definition. Creating a new keyboard layout 
is super simple. There are several examples in _layouts.h_

Currently, 3 layouts might be needed per keyboard. A Base layout for en-us,
A base layout for bepo-fr and a layout for the function layers.
The base layouts can take 3 or 4 rows by 10 columns as desired.
The base layers, add in the function, numbers, and lower rows, outside pinky keys,
and thumbs. The function layer layout can be KC_TRNS all around the perimeter,
or not...


# Files

  * mod_layer.h is the place for home row mods or any other mods.
  * layouts.h is where I define a new matrix using the ROW macros when I need one. 
  * core_keys.h - where I define my custom keys. Ya know, the big enum.
  * altlocal_keys.c - Alternate key/shift keys for emulation on other locales.
  * core_keysets.h - Base layers; qwerty, dvorak, beakl, colemak, norman, carplax...
  * edge_keys.h - defines the edges and bottom/thumb keys of a keyboard.
  * layers.h - defines function layers for navigation, symbols, keypad, layers, top rows, etc.

The following definition files are here.
  * combos.def - Combos/chords.
  * altlocal_keys.def - Alternate shifted key pairs for a locale. 
  * tap_hold.def - Custom keys with tap and hold behavior.


Layers
------------------
All of the layers are configurable. Turn them on or off, choose a different one.
See config.h, and map.h.  I make all my core map definitions 3x10. 
All my layout macros take 3x10 regardless of the keyboard. 


## Locales

This is to manage BEPO and Qwerty Locale/language/Layers
Each locale is defined with a start and end layer from the layers enum.

The first and last defines are all done with the magic of defines in 
ericgebhart.h where the layers enum is defined.

  
The locales are defined like this.

```c
const uint16_t locale_layers[][2] = {
  [LOCALE_EN_US] =      {FIRST_EN_LAYER, LAST_EN_LAYER},
#ifdef BEPO_ENABLE
  [LOCALE_BEPO_FR] =    {FIRST_BEPO_LAYER, LAST_BEPO_LAYER},
#endif
};
```

This could potentially hold multiple locales, The map turns on off the layers 
and their enums if they are not enabled so that the layer array does not 
fill up with too many base layers, or other layers because LT only works 
up to layer 15.

What this does is allow the keyboard to know which locales it has, and which
layers go with them.

If you have an oled, the locale will be displayed after the layout name. Currently
en-us and bepo-fr are there.

Locales are tracked, as to the layer ranges which belong to them in the layers enum.
This allows for a `KC_NEXT_LOCALE` key and a `KC_NEXT_BASE_LAYER` key. 
KC_SET_BASE sets the default layer in the eeprom.

When cycling through layers only the layers for the chosen local will appear.

The layers are different keycode sets. 
So there are two symbol layers, two toprows layers, two keypad layers. 
One for Qwerty and one for bepo. The Navigation layer is not affected because
it has only control keycodes which are independent of locale. 

I only have bepo, dvorak and beakl on bepo.  There are a bunch of layers
for Qwerty. I'm most interested in beakl
at the moment, but I've used Dvorak for more than 20 years. There is also 
qwerty, colemak, norman, carplax, etc.


## Navigation Layer
I do not use a mouse. I use Xmonad as my window manager, and I have
practically no use for one.  They are necessary however. So I have
a Navigation layer which is all mouse, arrows, home, end, tab, page
up, down,  5 mouse buttons and so on. 
This layer is not affected by bepo/qwerty, but symbols and numbers are. 
There are bepo versions of everything that needs it.

Arrow combos work just fine, in emacs I use SFT(arrows) to move between windows.
My Xmonad uses GUI arrows to cycle through windows, that works easily as well.
To do this; shift is my left pinky home, Nav is right thumb Enter, and one of the four
home keys of my left hand are the arrows. Home row mods allow this to work well.
I have about 3 other ways to invoke the Nav layer as well.

## Symbol Layer
The symbol layer is based on the Beakl15 symbol layer.
The beakl symbol layer is intuitive and fairly easy to remember. There are 3 versions.
The original, an extended called A, and an extended and enhanced for vi, called B.
The primary purpose of the extension was to provide keys which might not be available
elsewhere on the default layer. B, takes this further and moves :/? to better places.

## TopRows Layer
This is my version of raise/lower that lots of folks use.
I think, truly this is the layer that makes tiny keyboards accessible in the beginning.
This is basically the number row, the shifted number row and the function key row.
I have them so it is numbers on the home row, shifted keys above and functions below.
There are multiple choices, I currently use the beakl number row, with everything 
else as you would expect. 

## Keypad Layer
There are several variations of keypads and function key pads in various sizes. 
Currently I am using a Beakl Keypad on the left hand and 3x4 funcpad on the right.
The keypad can be chosen in config.h.

OLED
--------------------
The oled shows the basic stuff I could find in most places. 
* Default layer
* Current layer
* Locale
* Mods 
* Locks 
* Last key pressed
* Map of the current layer as simply as possible. (128x64)

I'm sure there is more that could be done. @Drashna has some fancy stuff. 
If the display is big enough, there is even a display of the current layer's keymap.
  
Process_records.c
--------------------
This is where the keycodes are processed...
It tends to be where cruft gathers. If something is good enough
I have been following the patterns used by *gboards/g/combos* and
*caps_word*. There is *tap_hold*, and *altlocal_keys*, which both use
def files to add more key definitions similar to the way combos do.

Custom keys
-------------------
I have a lot of custom keys because of bepo. It is somewhat confusing this interaction
between a keyboard and the software that receives it.

A lot of my pain is invoked by my desire to have dvorak on bepo. Which works just fine.
Currently I have dvorak and beakl on bepo in addition to bepo it's self. 

Alternate keycodes for emulating a layout on another locale/language.
-----------------------------
Note: I'm always looking to improve this. I think a _dead key_ layer might be
really useful in addition to all of this.

Because of wanting dvorak and beakl on bepo there was the necessity to create keys
from keycodes which were not combined. For this I have a special function that
takes a keycode and gives a proper shifted character for it. It is only a 2 keycode
definition, but it does the basic non-shifted and shifted characters as you define them.
Put the new keycode in the keycode enum, then define it here in _altlocal_keys.def_.

Define the new key's enum, add this include, and this function call to your 
process_record_user().  Then define some keys in _altlocal_keys.def_.

I begin and end my alternate keycodes in my enum like this;
The process record function uses these START and END values to to 
constrain it's range.

``` 
enum userspace_custom_keycodes {
  ALT_LOCAL_KEYS_START = SAFE_RANGE,  
  // BEAKL on Qwerty..
  BQ_DOT,
  BQ_COMM,
  BQ_QUOT,
  // End of beakl on qwerty
  BB_DOT,
  BB_COMM,
  BB_QUOT,
  // End of beakl on Bepo

  ALT_LOCAL_KEYS_END,

  ...

  };
```

This goes where process_record_user() is.
```c
  #include "altlocal_keys.h"
  ...
  
  ...
  // in process_record_user().
  if (!process_alt_local_key(keycode, record)) { return false; }
```

Here is what some Beakl keys look like for en-us/qwerty.
Beakl has dot with @ and comma goes with !.

In *altlocal_keys.def*
```
  // Keys for BEAKL on Qwerty
  MK_KEY(BQ_DOT,  KC_DOT, MOD_NONE,    KC_2, MOD_LSFT)
  MK_KEY(BQ_COMM, KC_COMMA, MOD_NONE,  KC_1, MOD_LSFT)
  MK_KEY(BQ_QUOT, KC_QUOT, MOD_NONE,   KC_GRV, MOD_NONE)
```

Combos/Chords
----------------------------
This is recently new to me. I'm using them on my thumb keys which are all LT's.
the combos allow for layer locking for the Nav layer, and a oneshot for symbols 
among other things.  Still in a state of exploration. 

I followed the simple example at the end of the doc that uses the 
combos.def file to define the combos.

Tap-mods
-------------------------------------
I use LT and MT a fair amount.
Additionally, in tap_hold.c I have a nice couple of functions
*tap_taplong()*, and *open_openclose()* for my non MT/LT functionality.

  * I have home row mods for Shift, Ctrl, Alt, and Gui on both hands.
  * I have a number of LT mods to raise layers nearby. Nav, toprows, symbol, keypad
 are on both hands on the first and third rows around home row.
  * Xmonad tap_taplong to pull up scratchpad/terminals or desktops with tap or hold.
  * C-c/C-v, C-t/C-n, C-w/C-q are all on my Navigation layer as custom keys with tap_taplong.
  * My thumbs are LT's, with Enter/space and Esc/backspace which are also Navigation and toprows and symbol layers.
  * All of the paired characters on my symbol layer have a hold which closes them, and moves the cursor back between.

### Tap-Hold

Tap hold currently has *tap_taplong* and *open_openclose* functions.
These are in *tap_hold.c*, *tap_hold.h* and *tap_hold.defs*.
Both use **TAPPING_TERM** as the hold duration.

Include the .h, add the process_record call,
Add the .c to the SRC in rules.mk.

```c
#include "tap_hold.h"
...
...
// inside process_user_record
process_tap_hold_user(keycode, record);
```

Add your new keycodes to your enum.

Define your keys in *tap_hold.defs*.

Here is Ctrl-C, Ctrl-V, as tap and long tap.
```
// tap or long tap for different key.
// One key copy/paste
TP_TPL(KC_CCCV, LCTL(KC_C), LCTL(KC_V))
```

Or for tap open, hold for open and close, and back arrow.
Here is __(__ or __()__ with tap and long tap.
```
// Open on tap and Open with close and back arrow on hold.
// (){}[]""''``<>
OPEN_OCL(KC_OCPRN, KC_LPRN, KC_RPRN)
```

### caps word
As documented in QMK.
Holding both pinkies on home row for double tapping term, is effectively 
right-shift and left-shift, invokes caps-word. The next word will be capitalized. 
It continues until it shouldn't.


XMonad
---------------------
I use xmonad. Gui is my hot key for that.  With home row mods I have home
row chords which give me access to my desktops, my scratchpads/terminals,
custom key KC_XM_PORD, among others. It sometimes feels that I am playing
an instrument when I invoke xmonad to do something.

I had an xmonad layer at one time, it was basically dvorak, I would invoke it
with a GUI mod, so that even on bepo, or colemak, my xmonad commands remain the same.

I'm going to need to revisit that, as things are, all the commands move when I change
to a different default layer from dvorak.

Combo's can alleviate some of this pain. More to play with.


Tap Dance
--------------------
I have a lot of tap dance, It's turned off. It's big. tap-hold works pretty well most of the time, instead.
My favorites were tab-backtab,  home-end.

Switching the OS keyboard
-------------------------
This varies from system to system.  I use Arch Linux, so I use ```setxkbmap```.
I've included a helper script which makes it easy to switch between EN and FR Bepo,
called switch-kbd. In xmonad I invoke this with a keystroke. so, same deal. just map
the keystroke to a key.

