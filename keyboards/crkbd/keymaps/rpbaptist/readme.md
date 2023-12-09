# Corne keyboard layout

This is my highly personalized CRKBD layout. I use Colemak DH as main typing layer. I use this keyboard and layout in my daily programming job and for everything at home, including gaming.

This keymap is the result of an evolution from Ultimate Hacking Keyboard to Iris, to Corne. It took many iterations and changes and only now I feel this is ready to be merged into the main QMK repository, because I think further changes will be minor. This is my 1.0 release so to speak.

Many thanks to foostan for the keyboard, all QMK contributors and drashna specifically for his work on this keyboard.

## Layers

### COLEMAKDH

Main typing layer. I really love having SHIFT available on thumbs. I am a left thumb space bar person, so I put SPACE there and ENTER on right. I use CTRL key combos lot in my text editor and desktop environment. That's why I have two of them. I also found them to be a great position for the square brackets. (`[` and `]`). These become parenthesis (`(` and `)`) on either of the layers.

Holding SHIFT while tapping BACKSPACE will output DEL. Holding both SHIFT keys will output SHIFT+DEL.

I don't know about you but "lower" and "raise" don't mean that much to me. I named my layers `SYM`, short for symbols and `NAV`, short for navigation. Holding the key will activate the layer for as long as it is held, double tapping it will switch to it. Single tapping it once will switch to main layer again.

Holding TAB will access `NUMPAD` layer which features a numpad. This is lockable by going to `ADJUST` layer and pressing the same key.

### SYM

Includes a number row, the symbols normally on SHIFT and numbers and a variety of other symbols used mostly for programming.

### NAV

This is where I access F keys, arrow keys, page up, down, home, end and F keys. I also added general tab forward and backward keys. Tab close and window close. I primarily use these in my browser, terminal and text editor.

### UTIL

Short for utility. This is accessed by pressing both `SYM` and `NAV` at the same time. It has a software `QK_BOOT` key, control for RGB and switching the main layer. More on the RGB below.

### NUMPAD"

This gives access to a numpad on the right half with some additional symbols I find useful when using the numpad. The left half has media control.

### GAMING

Sometimes I switch to type in Discord, Steam, or in game chat, so I think it's more important to keep typing functional than put WASD on where I want movement to be. This means I rebind my keys in all games. It's worth it to me.

I put movement on FRST (would be ESDF on QWERTY), because it lines up more comfortably with the columnar staggered layout of the Corne. It also gives more easy access to all keys on left half.

Most notable here is that there are no tap and hold differences anymore on left hand side besides the new layer key. This is a different layer than `SYM`.

### WASD

This is functionally the same as the `GAMING` layer, but uses traditional WASD layout. This is done for games where I don't need to type and want to just jump in without rebinding everything.

### GAMING_EXT

This is the gaming extended layer. I moved this to most inner thumb instead of mid thumb position. Num row is now moved to the home row. Besides that it gives me an ENTER key which does not switch. This is good when a game requires you to hold ENTER.

## RGB

I took a big inspiration from Drashna's RGB configuration and tweaked it.

- `RGB_UND`: Toggles underglow indicators on and off. Each layer has its own color.
- `RGB_IDL`: This will enable/disable idle mode. By default an "active" RGB mode will be used. When the idle timeout has exceeded the secondary animation will be activated, which is a passive animation. When switching to `GAMING` layer the timeout will be reduced and the idle animation changed to `RGB_MATRIX_RAINBOW_PINWHEELS`.
   When disabling idle mode, the current idle animation will be activated.
   On idling, on idling, the underglow layer indication will be deactivated and the animation RGB will be set instead.
- `RGB_ATG`: Cylces through three active modes: `RGB_MATRIX_SOLID_REACTIVE_SIMPLE` -> `RGB_MATRIX_TYPING_HEATMAP` -> `RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS`
- `RGB_PST`: Cycles through three passive modes: `RGB_MATRIX_SOLID_COLOR` -> `RGB_MATRIX_BREATHING` -> `RGB_MATRIX_CYCLE_ALL`
- `RGB_PCT`: Cycles through two, more colorful, passive modes: `RGB_MATRIX_RAINBOW_PINWHEELS` -> `RGB_MATRIX_CYCLE_LEFT_RIGHT`

## Building

`qmk flash -bl dfu -kb crkbd -km rpbaptist`

## Notes

I use several OLED slave side images, depending on the keycaps I am using. These also determine the default LED color and underglow.

Provide the theme like this:

`THEME=laser qmk flash -bl dfu -kb crkbd -km rpbaptist`

Current supported themes are:

- pulse (default)
- godspeed
- laser
- milkshake
