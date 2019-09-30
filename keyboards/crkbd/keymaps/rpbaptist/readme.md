# Corne keyboard layout

This is my highly personalized CRKBD layout. I use Colemak DHm as main typing layer. I use this keyboard and layout in my daily programming job and for everything at home, including gaming.

This keymap is the result of an evolution from Ultimate Hacking Keyboard to Iris, to Corne. It took many iterations and changes and only now I feel this is ready to be merged into the main QMK repository, because I think further changes will be minor. This is my 1.0 release so to speak.

Many thanks to foostan for the keyboard, all QMK contributors and drashna specifically for his work on this keyboard.

## Layers

### COLEMAKDHM

Main typing layer. I really love having SHIFT available on thumbs. I am a left thumb space bar person, so I put SPACE there and ENTER on right. I use CTRL key combos lot in my text editor and desktop environment. That's why I have two of them. I also found them to be a great position for the square brackets. (`[` and `]`)

I don't know about you but "lower" and "raise" don't mean that much to me. I named my layers `NUM`, short for numbers and `NAV`, short for navigation. Holding the key will activate the layer for as long as it is held, double tapping it will switch to it. Single tapping it once will switch to main layer again.

Everything else is pretty standard I'd say.

### NUM

Includes a number row, the symbols normally on SHIFT and numbers, as well as a numpad under right side homing keys.

### NAV

This is where I access arrow keys, page up, down, home, end and mouse control. I also added general tab forward and backward keys. I use these in my browser, terminal and text editor. 

## FN

Short for function. This gives access to the function keys, as well as rarely used keys on the left side and often used symbols (for me) on the right side. It is accessed by holding TAB.

### UTIL

Short for utility. This is accessed by pressing both `NUM` and `NAV` at the same time. It has a software `RESET` key, media keys, RGB control and switches main layer between Colemak and a gaming layer.

### GAMING

Sometimes I switch to type in Discord, Steam, or in game chat, so I think it's more important to keep typing functional than put WASD on where I want movement to be. This means I rebind my keys in all games. It's worth it to me.

I put movement on FRST (would be ESDF on QWERTY), because it lines up more comfortably with the columnar staggered layout of the Corne. It also gives more easy access to all keys on left half.

Most notable here is that there are no tap and hold differences anymore on left hand side besides the new layer key. This is a different layer than `NUM`. 

### GAMING_EXT

This is the gaming extended layer where movement keys remain the same. This means I can keep moving while accessing second layer keys. All other keys are keys on which I can easily rebind something. Besides that it gives me the function keys and an ENTER key which does not change. This is good when a game requires you to hold ENTER.

## Notes

I use MT3 Godspeed caps and thought it would be fun to theme the OLED output towards it. The slave side has the icon and two planets. The left side refers to modifiers by matching the novelty mod legends.

## Building

I am using DFU and have to flash both halves individually.

Left half: `make crkbd/rev1:rpbaptist:dfu-split-left`

Right half: `make crkbd/rev1:rpbaptist:dfu-split-right RGB_MATRIX_SPLIT_RIGHT=yes`
