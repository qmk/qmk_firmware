Overview
========

Warning: dvorak touch typist, that uses qwerty and bepo locales on my
computer.  40+ years of vi, 30 years of vi in Emacs.

Recent years I have gone minimal, I don't use most of the keys on my ergodox,
or original edition dactyl. These maps work great on large and small keyboards,
my preference seems to be 40% split ergo keyboards like the corne.

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

Layouts
-----------
This evolved from the old layout...wrapper code. Calling everything a wrapper seems
silly. So I took a step back. 

Also, with all these layers it was a real pain to apply mods consistently and 
easily. So I changed the way I use keymap macro wrappers and added in my own
mod layer. The only thing it has is the mods to apply. No more editing keymaps
to apply mods.  I do it once, and it works everywhere I want.

All layouts, almost, boil down to a 3x5 x 2 matrix. Bepo is 3x6. Mostly, I want 
my controls to stay the same. As we have been conditioned, these are the keys on 
the edges, or middle. Not that they can't change but I don't usually change them
much, except the side edges, - the extra pinky columns.
the F keys, the columns to the left and right and the row on the bottom. 
Thumb keys if you have them. Even the number row is practically the same.

With that in mind, reducing my layouts to 3x10 or 12 matrices would be great.
At the same time extracting my mods so they are easy to apply to any matrix.
So that's what is here. 

At the bottom is the LAYOUT, needed by the keeb you have. Then I have my Layouts
to feed it with my ROWS macros which are my MOD layer. At the end of it all,
I give a 3x10 or 12 to a layout and I have a complete keyboard definition.
Creating a new keyboard map is super simple.

  * mod_layer.h is the place for home row mods or any other mods.
  * layouts.h is where I define a new matrix using the ROW macros when I need one. 
  * core_keys.h - where I define my custom keys. Ya know, the big enum.
  * altlocal_keys.c - Alternate key/shift keys for emulation on other locales.
  * core_keysets.h - Base layers; qwerty, dvorak, beakl, colemak, norman, carplax...
  * edge_keys.h - defines the edges and bottom/thumb keys of a keyboard.
  * layers.h - defines actual layers for navigation, symbols, keypad, layers, top rows, etc.

Process_records.c
--------------------
This is where the keycodes are processed...

Custom keys
-------------------
I have a lot of custom keys because of bepo. It is somewhat confusing this interaction
between a keyboard and the software that receives it.

A lot of my pain is invoked by my desire to have dvorak on bepo. Which works just fine,
although an english/cyrillic situation may not work so well. Currently I have
dvorak and beakl on bepo in addition to bepo it's self. 

Alternate keycodes for emulating a layout on another locale/language.
-----------------------------
Because of wanting dvorak and beakl on bepo there was the necessity to create keys
from keycodes which were not combined. For this I have a special function that
takes a keycode and gives a proper shifted character for it. It is only a 2 keycode
definition, but it does the basic non-shifted and shifted characters as you define them.

Combos/Chords
----------------------------
This is recently new to me. I'm using them on my thumb keys which are all LT's.
the combos allow for layer locking for the Nav layer, and a oneshot for symbols 
among other things.

I followed the simple example at the end of the doc than uses the 
combos.def file to define the combos.

Tap-mods
-------------------------------------
I had been using MT on my thumbs for GUI,CTRL,ALT on hold along with 
Escape, Enter, space and backspace, my thumb keys. I then added shift to my home row pinky key.
I had layer shifts to symbols, numbers, navigation all on the home row of both hands.
It worked nicely but choppy I think, switching hands for the holder of the layer is
a little like having no caps lock. It was a lot of work adding them to all my maps.
This is what prompted my mod_layer.  So much easier. No maps to modify.

Then I moved to all home row mods with layers on my thumb keys.

This does allow for more rolls, and I have found chord/rolls simply from having my
xmonad controls be GUI-some-home-row-key-or-close. When Gui is your index finger,
everything gets easier. 

Somewhere along the way I got a corne, and everything had to be small. and I realized
that everything really was small. My layers are blending back, with LTs near the
home row, and all the thumbs. On my dactyl I currently have 8 thumb keys per thumb, 
I don't know what to do with them all. Remembering a time I thought that would be 
awesome.

### tap_taplong and open_openclose
In process_records.c I have a nice couple of functions,
tap_taplong(), and open_openclose() for my non MT/LT functionality.

  * I have home row mods for Shift, Ctrl, Alt, and Gui on both hands.
  * I have a number of LT mods to raise layers nearby. Nav, toprows, symbol, keypad
 are on both hands on the first and third rows around home row.
  * Xmonad tap_taplong to pull up desktops or terminals with tap or hold.
  * C-c/C-v, C-t/C-n, C-w/C-q are all on my Navigation layer as custom keys with tap_taplong.
  * My thumbs are Enter/space and Esc/backspace which are also Navigation and toprows and symbol layers.  They used to be GUI,CTRL,ALT,SFT. but all that's on the home row now.
  * All of the paired characters on my symbol layer have a hold which closes them, and moves the cursor back between.

### caps word
Holding both pinkies on home row for double tapping term, is effectively 
right-shift and left-shift, invokes caps-word. The next word will be capitalized. 
It continues until it shouldn't.

BEPO vs Qwerty Locale/language/Layers
---------------------
Essentially they are different keycode sets. So anything that needs them, causes a layer.
So there are two symbol layers, two toprows layers, two keypad layers. 
One for Qwerty and one for bepo. The Navigation layer is not affected.

I only have bepo, dvorak and beakl on bepo.  There are a bunch for Qwerty.
I have a ton of basic layers. I'm most interested in beakl at the moment, but I've used Dvorak for more than 20 years. There is also qwerty, colemak, norman, carplax, etc.

The navigation/mouse layer is not affected by bepo/qwerty, but symbols and numbers are. 
There are bepo versions of everything that needs it.

Navigation Layer
-----------------------
I do not use a mouse. I use Xmonad as my window manager, and I have
practically no use for one.  They are necessary however. So I have
a Navigation layer which is all mouse, arrows, home, end, tab, page
up, down,  5 mouse buttons and so on. 
This layer is not affected by bepo/qwerty, but symbols and numbers are. 
There are bepo versions of everything that needs it.

Arrow combos work just fine, in emacs I use SFT(arrows) to move between windows.
To do this; shift is my left pinky home, Nav is right thumb Enter, and one of the four
home keys of my left hand are the arrows. Home row mods allow this to work well.

I don't use the arrows on the dactyl and kinesis, even though they are there.

Symbol Layer
-------------------
The symbol layer is based on the Beakl15 symbol layer.
The beakl symbol layer is intuitive and fairly easy to remember. There are 3 versions.
The original, an extended called A, and an extended and enhanced for vi, called B.
The primary purpose of the extension was to provide keys which might not be available
elsewhere on the default layer. B, takes this further and moves :/? to better places.

TopRows Layer
--------------------
I think, truly this is the layer that makes tiny keyboards accessible in the beginning.
This is basically the number row, the shifted number row and the function key row.
I have them so it is numbers on the home row, shifted keys above and functions below.
There are multiple choices, I currently use the beakl number row, with everything 
else as you would expect. 

Keypad Layer
--------------
There are several variations of keypads and function key pads in various sizes. 
Currently I am using a Beakl Keypad on the left hand and 3x4 funcpad on the right.

OLED
--------------------
It shows the basic stuff I could find in most places. The 
default layer, the current layer, the mods, the locks, the last key pressed, and
a map of the current layer as simply as possible. I'm sure there is more that could
be done. @Drashna has some fancy stuff. If the display is big enough, there is even 
a display of the current layer's keymap.  

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

