Overview
========

This is my personal userspace.  Most of my code exists here. I only have one keymap, and that
is for an ergodox_ez.  There are a lot of layers, 7 of them are default layers. I primarily use 
dvorak and Bepo. I've been using emacs in vi mode for over 23 years. I also us Xmonad as my 
window manager, additionally I've been using a Kinesis advantage keyboard in dvorak for over 20
years.  All of those things tend to color the layouts I have. 

The Bepo layer needs some love.  It is true to the layout at Bepo.fr, but I find it a little
cumbersome, and I miss some of my favorite keys.

There are 2 dvorak layers, one for a qwerty OS keyboard, and one for a Bepo OS keyboard. 
There is a symbol/keypad layer for bepo and qwerty. And of course there is a mouse/media layer.  
There are 2 Xmonad layers one for qwerty and one for Bepo. Layer selection happens automatically 
based on your current default layer.  I use 2 tap dance keys for layer selection.

There are also Qwerty, Colemak, Workman and Norman layers for qwerty.


Keyboard Layout Templates
-------------------------

I borrowed the idea for the keyboard defines and some of the definitions from @drashna. 
I think it is an awesome idea, It makes consistency between layout definitions so much easier.
@drashna had this to say about it.


This borrows from @jola5's "Not quite neo" code.  This allows me to maintain blocks of keymaps in the userspace, so that I can modify the userspace, and this is reflected in all of the keyboards that use it, at once. 

This makes adding tap/hold mods, or other special keycodes or functions to all keyboards super easy, as it's done to all of them at once. 

The caveat here is that the keymap needs a processor/wrapper, as it doesn't like the substitutions.  However, this is as simple as just pushing it through a define. For instance: 

`#define LAYOUT_ergodox_wrapper(...)   LAYOUT_ergodox(__VA_ARGS__)`

Once that's been done and you've switched the keymaps to use the "wrapper", it will read the substitution blocks just fine. 

Credit goes to @jola5 for first implementing this awesome idea.


Custom Keycodes
---------------

Keycodes are defined in the ericgebhart.h file and need to be included in the keymap.c files, so that they can be used there.  The keymap.c file has very little in it, the most important thing to see there are the keys that are at the ends of each row, ie. the 1st and last key on each row is defined there.
Everything else is in ericgebhart.h.

Layer Indication
----------------

The ergodox_ez only has 3 leds, layer indication is pretty lame.
Currently the first led lights up if the default layer is not qwerty.  The symbol and media layers get
the other 2 leds,  and all the leds light up if you are on the "layers" layer.
I hope I can figure out how to make it better, but I just don't see a way with 3 leds and 11 layers.


BEPO vs Qwerty Layers
---------------------

There are 7 base layers. Dvorak, qwerty, Colemak, Workman, and Norman work on a Qwerty software layer on the OS.  Dvorak_on_bepo and Bepo both work on a Bepo software layer on the os.
Dvorak on qwerty is the default.  There is a function in ericgebhart.c which will allow the keyboard
to persist it's default layer through power down. It is currently commented out.

I don't actually use Qwerty, but it seemed like I should have it,
@drashna had it along with Colemak, Workman and Norman so I added them
to my existing dvorak and bepo definitions.

There are two tap dance functions that allow switching the default layers
and the overlay layers.

The default layers switch according to the current OS keyboard of the current Default layer.
Shifting the key, causes the selection to use the other OS keyboard selections. ie,
if you are on qwerty, you get dvorak, qwerty, colemak, workman and norman. If you shift it you get 
dvorak on bepo and bepo.  If you are not on qwerty the unshifted taps get dvorak and bepo on bepo.

The other tap dance for layers is for the symbol, mouse and layers layers.  The layers layer is just a
safety layer, knowing I can get to if I screw something up...

XMonad
---------------------

Additionally there is an advanced tap dance called XMONAD_ESC. One tap is Escape, tap and hold is
LGUI with the proper XMONAD layer, it is essentially dvorak, for the
given OS layer.  2 taps is Shift lgui with xmonad, and 2 taps and hold
is Control LGUI with Xmonad.  This allows for the finger patterns for
Xmonad to remain the same regarless of the keyboard in use.  The hold
versions allow for secondary menu selection in Xmonad, the 2 tap function
must be for a key that is in the top level keymap of Xmonad.  This is how
many people use xmonad so it's not a real problem.  There are plenty of
keys combinations to choose from with these choices. The function can
be expanded to 3 taps and 3 tap and hold, and on and on....

I have a few other special keys,  for momentary symbols or shift on the home row of each hand.

Also, after using a kinesis for many years I'm very accustomed to the
space, enter, backspace and delete keys on the thumbs.  I've added control
and alt as a secondary function. These are also the Control and Alt keys
if held down.

Tap Dance
--------------------

Additionally there are other tap dance functions,  tab-backtab,  home-end as well as I few I'm not actually using.

Building  and flashing
-----------------------

```make ergodox_z:ericgebhart```   will compile the code.

I use the teensy-loader cli  so that's all I know. There is a script here called flash_ergodox

Use it like this, 

```flash-ergodox <path to your hex file>```

then use a paperclip to push the reset button on your keyboard.

Switching the OS keyboard
-------------------------

This varies from system to system.  I use Arch Linux, so I use ```setxkbmap```.
I've included a helper script which makes it easy to switch between EN and FR Bepo,
called switch-kbd.

