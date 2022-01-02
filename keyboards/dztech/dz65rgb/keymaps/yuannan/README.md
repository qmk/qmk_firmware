[DZ65RGB/v3 Yuannan's Layout Imgur Album](https://imgur.com/a/HfLTahi)

![Alpha](https://i.imgur.com/Zwvl3Za.png)
![Vim Editing Layer](https://i.imgur.com/1IsATG5.png)
![Mouse and Autoclicker](https://i.imgur.com/IP6JwO3.png)
![Hyper functions and RGB Layer](https://i.imgur.com/kkvjM0p.png)

# Yuannan's DZ65 Custom Profile

## Features

1. VIA/VIAL support
2. Improved navigation via VIM like keys.
3. Dynamic Macros now enabled!
4. Custom Editing Macros such as:
	- Deleting entire line
	- Deleting from cursor to start of line
	- Deleting form cursor to end of line
5. Much better mouse support. Now able to: move mouse around with 3 levels of accleration, click and nav using mouse buttons 1-5, mouse scroll in all 4 directions, autoclick with 5 different levels of speed! Toggle in speeds of {0, 20, 50, 100, 1000} -> {1000, 50, 20, 10, 1} clicks per second. In reality it will be lower due to board and OS lag.
6. Improved granularity of the RGB Matrix now with steps of 8/256 (32 steps!)
7. Disabled some effects to free up more space.

### Notes

The RGB animation on the board actually eats a load of CPU cycles. Enough to actually put a massive dent in the clicks per second output. So if you wish to optimal CPS then disable the RGB. Even you set the brightness all the way down to 0 the animation code will still run. This is true as of (2022/01/02), I hope someone may fix this. In the meantime I have created a second array for delays for the autoclicker while RGB mode is active. Users to note there is yet another caveat to this. Because of  the FN layer indicator setting it's own colour the animation does not compute it for that key. When your FN layers are mostly populated like it is on this keymap it actually speeds up the animation compute time by a lot. I could compensate for this once again but it'll be a chase into oblivion.

TL;DR: If you wish for the fastest and most time accurate autotlicker you should turn RGB OFF COMPLETELY. Setting brighness to 0 is not the same.