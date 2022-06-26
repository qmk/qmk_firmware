# UT47 default keymap

![UT47 layout image](https://i.imgur.com/Tsz5qsF.png)

[KLE](http://www.keyboard-layout-editor.com/##@@_y:0%3B&=Esc&=Q&=W&=E&=R&=T&=Y&=U&=I&=O&=P&_w:1.5%3B&=Back%20Space&_x:0.25&a:4&f:4&w:4&h:4&d:true%3B&=%3Cb%3EGNAP!%3C%2F%2Fb%3E%3Cp%3E%3Cp%3EMinimum%20stagger%3Cp%3E47%20key%20layout%3B&@_a:7&f:3&w:1.25%3B&=Tab&=A&=S&=D&=F&=G&=H&=J&=K&=L&=%2F%3B&_w:1.25%3B&=%27%3B&@_w:1.5%3B&=Shift&=Z&=X&=C&=V&=B&=N&=M&=,&=.&=%2F%2F&=Return%3B&@=Ctrl&=Alt&=Super&=Menu&_w:1.25%3B&=%2F&dArr%2F%3B&_w:2%3B&=&_w:1.25%3B&=%2F&uArr%2F%3B&=%2F&larr%2F%3B&=%2F&darr%2F%3B&=%2F&uarr%2F%3B&=%2F&rarr%2F%3B%3B&=undefined)

Once this keymap is applied, you will need to press the top-left key + bottom-left key to put the keyboard into DFU mode for flashing. Bootmagic does not work with this keymap, because space is defined to use mod-tap (tap = space, hold = L2). Mod-tap on space and bootmagic seem to be incompatible.

Tab next to Q, like other keyboards
Escape where capslock is normally
More normal cursor cluster, with / moved next to lower (L1). Likewise with Home/PgUp/PgDn/End.
Remove app key, put \ in bottom-left, and shift Ctrl+Alt+Gui over so Alt is next to raise (L2) for less finger cross-over on cut/copy/paste
Put tilde on L1 and L2 on \ in bottom-left
Put backtick on L1 and L2 on / in middle of bottom row
Use a numpad layout on Q/A/Z cluster, because I find that easier to remember. Also use a similar layout for F-keys, on layer 3.
Space bar in L1 and L2 is dash, as an additional alternative to using J, to help with Linux commands and dates.
Backspace is backspace on most layers (don't use delete much)
Move RGB onto layer 3
Move capslock onto layer 3
Volume and media keys on layer 3
L1 + O = zero, L2 + O = zero (as well as L1 + V)
Move {} [] onto <> on layers 1/2, in addition to location on L;?
Spacebar held is L2 modifier, space on tap
1.5U either side of spacebar are both L1 to make it more symmetric

"Hold down the Bootmagic key (Space by default) and the desired hotkey while plugging in your keyboard. For example, holding Space+B should cause it to enter the bootloader."

TODO: try numpad into middle for less awkward chording for nums/syms.
TODO: Put Bootmagic on a different key than space? https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_bootmagic
TODO: http://www.keyboard-layout-editor.com/ layout for it
TODO: blog post about UT472, 2u stab PCB stab clip in, 5 pin switch support (Durock T1s), link to other places, had to reset board using button on PCB after accidentally stopping BootMagic from working!

TODO: colours: reddish purple: H: 248 S: 215 V: 95 ; more purple H: 240 S: 215 V: 95
TODO: current chosen ones: H: 248 S: 215 V: 79
