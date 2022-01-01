Overview
========

I think that what is special here is the layouts. I don't worry too
much about leds, or RGB, although I do like oled.  But really its mod_layer.h,
all the simple layer chunks and definitions, and the ability to apply that
to any keyboard with minimal effort. The other thing is the example it
provides for defining keymaps based on different OS locales. I use both
dvorak on Qwerty, and bepo/dvorak on bepo.  That means I must change my
locale on my OS to match my keyboard which can do qwerty or bepo locales.

It is possible, as I do, to send a keycode invoking xmonad, to execute my
qwerty - bepo switch on my computer. 

The other thing that colors my keyboard code is that I have used the kinesis
advantage for for more than 2 decades. I have used the ergodox for several years 
as well, so the evolution of my keymaps starts there with space, enter, backspace 
and delete keys on the thumbs.

Layouts
-----------
This evolved from the old layout...wrapper code. Calling everything a wrapper seems
silly. So I took a step back.

All layouts, almost, boil down to a 3x5 x 2 matrix. Bepo is 3x6. Mostly, I want 
my controls to stay the same. As we have been conditioned, these are the keys on 
the edges, or middle. Not that they can't change but I don't usually change them
much, except the side edges, - the extra pinky column.
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
  * layouts.h is where I define a new matrix when I need one. 
  * core_keys.h - where I define my custom keys. Ya know, the big enum.
  * core_keysets.h - defining base layers, qwerty, dvorak, beakl, colemak, norman, carplax...
  * edge_keys.h - defines the edges and bottom/thumbs of a keyboard.
  * layers.h - defines actual layers for navigation, symbols, keypad, layers, top rows, etc.

Process_records.c
--------------------
This is where the keycodes are processed...

If done well, this is where you call your hook functions like caps_word.
or tap_taplong(), or open_openclose().

Custom keys
-------------------
I have a lot of custom keys because of bepo. It is somewhat confusing this interaction
between a keyboard and the software that receives it.

A lot of my pain is invoked by my desire to have dvorak on bepo. Which works just fine,
although an english/cyrillic situation may not work so well. Currently I have
dvorak and beakl on bepo in addition to bepo it's self. 

Custom keys with shift
-----------------------------
Because of wanting dvorak and beakl on bepo there was the necessity to create keys
from keycodes which were not combined. For this I have a special function that
takes a keycode and gives a proper shifted character for it. It is only a 2 keycode
definition, but it does the basic non-shifted and shifted characters as you define them.

Tap-mods
-------------------------------------
I also had been using MT on my thumbs for GUI,CTRL,ALT on hold along with 
Escape, Enter, space and backspace, my thumb keys. I then added shift to my home row pinky key.
I had layer shifts to symbols, numbers, navigation all on the home row of both hands.
It worked nicely but choppy I think, switching hands for the holder of the layer is
a little like having no caps lock. It was a lot of work adding them to all my maps.

Then I moved to all home row mods with layers on my thumb keys.

This does allow for more rolls, and I have found chord/rolls simply from having my
xmonad controls be GUI-some-home-row-key-or-close. When Gui is your index finger,
everything gets easier. I look for difficulties it is interesting how things show up.

In emacs I use shift-arrows to move between windows. To get them I have to be on my
navigation layer. So left pinky (shift), right thumb(nav), right home-row(arrows).  
This works nicely, a surprise.

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
  * I have an xmonad MT to pull up desktops or terminals with tap or hold.
  * C-c/C-v, C-t/C-n, C-w/C-q are all on my Navigation layer as custom keys with tap_taplong.
  * My thumbs are Enter/space and Esc/backspace which are also Navigation and toprows and symbol layers.  They used to be GUI,CTRL,ALT,SFT. but all that's on the home row now.
  * All of the paired characters on my symbol layer have a hold which closes them, and moves the cursor back between.

### caps word
Holding both pinkies on home row for double tapping term, is effectively 
right-shift and left-shift, invokes caps-word. The next word will be capitalized. 
It continues until it shouldn't.

BEPO vs Qwerty Layers
---------------------
Essentially they are different keycode sets. So anything that needs them, causes a layer.
So there are two symbol layers, two toprows layers, two keypad layers. 
One for Qwerty and one for bepo. The Navigation layer is not affected.

I only have bepo, dvorak and beakl on dvorak.  There are a bunch for Qwerty.
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

Symbol Layer
-------------------
The symbol layer is based on the Beakl15 symbol layer. There are 3 versions.
The original, an extended called A, and an extended and enhanced for vi, called B.
The primary purpose of the extension was to provide keys which might not be available
elsewhere on the default layer. B, takes this further and moves :/? to better places.

TopRows Layer
--------------------
I think, truly this is the layer that makes tiny keyboards accessible.
This is basically the number row, the shifted number row and the function key row.
I have them so it is numbers on the home row, shifted above and function below.
There are multiple choices, I currently use the beakl number row, with everything 
else as you would expect.

Keypad Layer
--------------
There are several variations of keypads and function key pads in various sizes. 
Currently I am using a Beakl Keypad on the left hand and 3x4 funcpad on the right.

OLED
--------------------
There is a fair a bit of this as I find it the most succint way to understand the
state of my keyboard. It shows the basic stuff I could find in most places. The 
default layer, the current layer, the mods, the locks, the last key pressed, and
a map of the current layer as simply as possible. I'm sure there is more that could
be done.

XMonad
---------------------
I use xmonad. Gui is my hot key for that.  With home row mods I have home row chords
which give me access to my desktops, my scratchpads/terminals, among others. It sometimes
feels that I am playing an instrument when I invoke xmonad to do something.

Tap Dance
--------------------
I have a lot of tap dance, It's turned off. It's big. tap-hold works pretty well most of the time.
My favorites were tab-backtab,  home-end.

Switching the OS keyboard
-------------------------
This varies from system to system.  I use Arch Linux, so I use ```setxkbmap```.
I've included a helper script which makes it easy to switch between EN and FR Bepo,
called switch-kbd. In xmonad I invoke this with a keystroke. so, same deal. just map
the keystroke to a key.

