### Custom aurora sweep keymap

This keymap is inspired by [optimot](https://optimot.fr) which is a French layout.  
Nonetheless it uses the US international extended keymap for French keys.

It uses the _best_ QMK features :

-   combos ♥
-   auto shift
-   leader

I tried to optimise key positions for neovim and i3wm while limit digrams.  
The oled screens are used to display the current layout, the modifier keys and the leader key.

![oledmodifiers](https://i.imgur.com/on95jx0.png)
![oledmouse](https://i.imgur.com/PwkR6P2.png)

#### Install

Clone this repo in the folder :

    ~/qmk_firmware/keyboards/splitkb/aurora/sweep/keymaps/

#### Compile and flash

Navigate into the keymap folder and launch this command for both sides :

    qmk compile && qmk flash

And :

    Click twice on the flash button and use nautilus for instance to clic on the keyboard.
    Don't forget to flash with the double tap bootloader define before soldering.

#### Layout

Set the us altgr international to activate French keys :

    /usr/share/X11/xkb/symbols/
    localectl list-x11-keymap-variants us

    setxkbmap us altgr-intl

#### Links

[qmk](https://docs.qmk.fm/#/)  
[ferris sweep](https://github.com/davidphilipbarr/Sweep)  
[splitkb](https://splitkb.com)

#### Layouts

![base](https://i.imgur.com/i7NgrCD.png)  
![numeric](https://i.imgur.com/6Yso40L.png)  
![mouse](https://i.imgur.com/skSL4Lo.png)  
![arrows](https://i.imgur.com/NIjJR2I.png)  
![adjust](https://i.imgur.com/xj6i70P.png)  
![fn](https://i.imgur.com/Q41ZdQi.png)  
![left hand](https://i.imgur.com/WDEGxGM.png)

![combos](https://i.imgur.com/wj6DEY0.png)

#### Leader

| -             |            |
| ------------- | ---------- |
| M + S         | mail short |
| M + L         | mail long  |
| D + E + G     | °          |
| C + O + P     | ©          |
| R + E + G     | ®          |
| D + I + A     | ø          |
| D + I + A + M | Ø          |
| E + U + R     | €          |
| P + O + U     | £          |
| Y + E + N     | ¥          |
| C + E + N     | ¢          |
| P + I         | π          |
| P + I + I     | Π          |
| O + M + E     | ω          |
| O + M + E + G | Ω          |
| U + P + F     | ⁰          |
| D + N + F     | ₀          |

| -         |     |
| --------- | --- |
| M + U + L | ×   |
| D + I + V | ÷   |
| P + M     | ±   |
| I + N + E | ≠   |
| A + L + M | ≈   |
| S + Q + U | √   |
| I + N + F | ∞   |
| < + <     | ≤   |
| > + >     | ≥   |
| F + S + T | ¼   |
| F + S + G | ½   |
| F + H + T | ¾   |
