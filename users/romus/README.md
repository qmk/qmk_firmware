# overview

 this is a modified version of let's split keyboard from bbaserdem. i don't like standard dvorak overuses right pinky
 so i shifted the columns out. i'm not sure if this is any good, time will tell.

 i have ortholinear let's split eh, which share a lot of functions with other ortholinear keyboards.

# layout

i use dvorak with an unorthodox off layout.
if you wanna grab my code, and you used a layout with a persistent base
layer change, change it to layer 0 before proceeding.

# layers

* **dvorak**: base layer,with dvorak layout.
* **alternative**: has alternate characters.
* **game**: toggled from *function*, comfortable for gaming use.
* **numeric**: has numericals and symbols. can be locked.
* **function**: layer has media and function keys.
* **mouse**: manipulates mouse. can be locked.
* **music** allows playing sounds.

# functionality

* **rgb backlight**: with layer indication, and ability to change base layer lighting mode.
* **secrets**: by placing a secrets.h, and not tracking it, passwords can be stored.
* **mouse**: mouse emulation, complete with diagonal keys.
* **turkish**: an altgr-like overlay that allows some non-common letters, in unicode.

i suggest checking out how i enabled turkish keys,
how i planned out rgb lighting,
and my mouse implementation;
they might offer some insight into fringe user cases.

# issues

all features are too big for the 32kb bootloader.
offenders are audio and rgb lights; it comes down to one or the other.

~the proton board, and rev 6 might fix that.~

# credits

this is a modified version of let's split keyboard from bbaserdem who has previously written his keymap by himself before, but rewrote it here.
