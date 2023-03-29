# Brazilian keymap for the BM40RGB keyboard

![photo](https://user-images.githubusercontent.com/62627597/228396721-b38ea064-6e80-4aff-90ec-01164d0515ae.jpg)

This keymap deviates somewhat from the generally used conventions of Planck style keyboards. 
It's built on the following principles:

1. Availability of different base layouts. QWERTY, Dvorak, Colemak and Workman are available. They can be chosen with the four right hand home row keys on the ADJUST layer (NAV + NUM keys). The base layout you choose gets stored on the keyboard EEPROM, so it will still be set if you unplug or reset the keyboard.
2. Frequent use of navigation keys such as the arrow keys, home, end, and hotkeys using those keycodes. For that reason, it keeps the navigation keys on a dedicated nav layer, on the home row, under the right hand. The nav layer is activated by the first button of the home row (the usual caps lock position). I find this much better than using dedicated arrow keys on the bottom right of the keyboard, as the very reason I swapped to a 40% is to move my hands less.
3. Accessibility of the ´ ` ^ ~ ç symbols. There are several blank spaces left on the symbols layer, if you need access to other symbols or diacritics.
4. Proper touch typing, and hotkey access, with the Shift key on both sides. I found my hands very much expect Ctrl to be on the edge of the keyboard, and as such I've kept both bottom corner keys as Ctrl. The right Ctrl will act as an Enter key if tapped.
5. Numbers and navigation keys should be slightly more accessible than symbols and function keys. If you use symbols more often, consider swapping the NUM and SYM layer toggle keys.
6. It's easier to remember layers when they make sense conceptually, so no "lower" and "raise" layers. Instead, there are dedicated layers for navigation/utility (NAV), numbers (NUM), symbols (SYM) and function keys (FN). There's also dedicated MIDI layers, a layer for one-hand typing, a mouse-emulating layer, and a layer for one-hand navigation and copy-pasting.
7. Tap hold is a good tool and you should use it if you can. Backspace and Delete are set as tap functions on the two more accessible layer toggle keys. The bottom right Ctrl behaves as Enter when tapped. The Nav layer button is Tab when tapped.
8. Easy-to-access shortcut modifiers. This layout includes a Master key (Shift+Ctrl+Alt) and a Hyper key (Shift+Ctrl+Alt+Super) for configuring system shortcuts.

It will only work as intended if your system keyboard layout is set to Brazilian ABNT2. It may work with other international layouts, but some keys, including brackets and the ´ ` ~ ^ keys, will get broken. If your system layout is another one, it should be relatively easy to change keymap.c (search and replace each key with the equivalent one from the international keymaps file). 

# Layers and functions

In each key:
Top left: SYM layer; 
Top right: FUN layer;
Bottom left: NAV layer;
Bottom right: NUM layer;
Bottom: Behavior when tapped (tap/hold)

# Base Layers

## Normal

![bm40rgb-wolff-base](https://user-images.githubusercontent.com/62627597/228594776-c683da4e-a7fe-43d1-a3e8-740d6eda9e3e.png)

QWERTY, Dvorak, Colemak and Workman are built-in.

## MIDI

![bm40rgb-wolff-midi](https://user-images.githubusercontent.com/62627597/228644387-0b7c99ad-9f4e-4052-ae50-07690794a11f.png)

One and a half octaves piano on the top rows, control signals in the bottom rows. SYM and FUN remain accessible so the ADJ layer can be accessed.

# Auxiliary layers

## FUN Layer

![bm40rgb-wolff-fun](https://user-images.githubusercontent.com/62627597/228640768-b2283b05-bc40-478e-83cf-957dbce9b476.png)

## ADJUST Layer (SYM + FUN)

![bm40rgb-wolff-adj(1)](https://user-images.githubusercontent.com/62627597/228640331-5e445822-3661-4445-bf2b-7e96f6f47413.png)

# Additional/utility layers (toggled by a key in the ADJ layer)

## SWP Layer (Hand-swap layer, for one-hand typing)

(Image)

## CPY Layer (One-hand navigation layer)

(Image)
