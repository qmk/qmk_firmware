# FabulousAnomalyKeyBoard

This layout features an efficient layout for people without
a mouse.

## layers

Layer Base:	complete basic keyboard
Layer Fn-Tab:	F1-F12, Arrow Keys, Home, End, Backlight, Media
Layer Fn-Space: mouse keys in a vim like manner

For detailed info check out keymap.c

## the CTRL key

It is where you would suspect CAPSLOCK to be.
WHO NEEDS CAPSLOCK ANYWAYS?
For those rare cases you need to shout at somebody in a comment
section you can still do a capslock by using TABCTRL

## the SUPER key

There are two super keys. They are next to the space bar.
The intention is easing the use of tiling window mangers

## emergency mouse

Without a mouse you will find yourself in a situation where all
your tiling goodness will just not be able to click onto that 
"close ads" button.
This keymap integrates a basic mouse pointer directly into the keyboard.
Mouse is accessible via holding SPACE and tapping keys:
```
SPACE
h	Move cursor left
j	Move cursor down
k	Move cursor up
l	Move cursor right

w	Middle Mouse Click
r	Right click
e	Left click

s	Scroll wheel left
d	Scroll wheel down
f	Scroll wheel up
g	Scroll wheel right
```

## shell focused

Working in a shell the up and down arrow keys are often needed to
look at old commands or reuse some.
When held, the left ctrl and left shift will act as expected,
but when tapped they will become UP and DOWN arrow-keys.

## krautfriend
The keys <|> are accessible even without a 102nd key
