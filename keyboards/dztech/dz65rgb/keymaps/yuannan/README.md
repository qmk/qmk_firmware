[DZ65RGB/v3 Yuannan's Layout Imgur Album](https://imgur.com/a/BI2RjgE)

![Alpha](https://i.imgur.com/ikqvrtF.png)
![Vim Editing Layer](https://i.imgur.com/Zm6Tf6p.png)
![Mouse and Autoclicker](https://i.imgur.com/hoBvSRR.png)
![Hyper functions and RGB Layer](https://i.imgur.com/QWmWaWY.png)

# Yuannan's DZ65 Custom Profile. Autoclicker, Vim, and more!

## Features

1. Much better mouse support. Now able to: move mouse around with 3 levels of acceleration, click and nav using mouse buttons 1-5, mouse scroll in all 4 directions, autoclick with 5 different levels of speed! Increase or Decrease the speeds of {500, 50, 20, 10, 1} clicks per second\*(Read Note Below). Press Shift while using the Increase or Decrease button to do the opposite. It's ready to be dropped into your keymap.c today!
2. Ctrl and Caps swapped. The new indicator is dynamically colored and has been moved as well!
3. Improved navigation via Vim like keys.
4. Dynamic Macros now enabled!
5. Custom Editing Macros such as:
	- Deleting entire line
	- Deleting from cursor to start of line
	- Deleting form cursor to end of line
6. VIA/VIAL support6. Improved granularity of the RGB Matrix now with steps of 8/256 (32 steps!)
7. The default toggle for RGB now sets the matrix to be on low brightness. Why? if the matrix is completely toggled off then indicators for Caps Locks and FN are also completely off. You can completely turn it off by pressing shift while processing the "RGB_TOG" keycode.
8. Disabled some effects to free up more space.

### Notes

The RGB animation on the board actually eats a load of CPU cycles. Enough to actually put a massive dent in the clicks per second output. So if you wish for optimal CPS then disable the RGB. Even you set the brightness all the way down to 0 the animation code will still run. This is true as of (2022/01/02), I hope someone may fix this so if the bright is set to 0 it will not run the animations. In the meantime I have created a second array for delays for the autoclicker while RGB mode is active. Users should note there is yet another caveat to this. Because of  the FN layer indicator setting it's own colour the animation does not compute it for that key. When your FN layers are mostly populated like it is on this keymap it actually speeds up the animation compute time by a lot. I could compensate for this once again but it'll be a chase into oblivion.

TL;DR: The CPS is not accurate and it **CANNOT** be while the RGB lighting is on! Setting brightness to 0 is not the same, it needs to be off COMPLETELY. It is {FN1+FN2+Shift+Space} on this keymap.