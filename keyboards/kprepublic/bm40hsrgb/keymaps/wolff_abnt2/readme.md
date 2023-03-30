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

# Base Layers

These are selected as the base by a button in the Adjust layer.

## Normal

![bm40rgb-wolff-base](https://user-images.githubusercontent.com/62627597/228847515-68802f2e-0cf7-4be1-bf19-9d1ba06766d6.png)

QWERTY, Dvorak, Colemak and Workman are built-in.

## MIDI

![bm40rgb-wolff-midi](https://user-images.githubusercontent.com/62627597/228708182-5ba2b9f4-e1f4-4e10-be6e-58ff373f274a.png)

One and a half octaves piano on the top rows, control signals in the bottom rows. SYM and FUN remain accessible so the ADJ layer can be accessed.

## Joystick

![bm40rgb-wolff-game](https://user-images.githubusercontent.com/62627597/228709807-43f39b05-03a6-4e48-9fca-15ad28824f5b.png)

Emulates a 32-button joystick for using as a button-box or dedicated game controller.

# Modifier layers

These are activated by holding down modifier keys.

## Navigation Layer (NAV)

![bm40rgb-wolff-nav](https://user-images.githubusercontent.com/62627597/228712172-a3c42451-e43b-445d-8777-5e62aaf7d6a2.png)

The layer you'll access most often. Navigation keys right on the right-hand homerow, plus a few common utilities.

## Functions Layer (FUN)

![bm40rgb-wolff-fun](https://user-images.githubusercontent.com/62627597/228708222-044c9ff2-af17-4259-ab36-490aef111fae.png)

## Mouse Layer

![bm40rgb-wolff-mouse](https://user-images.githubusercontent.com/62627597/228847570-6ca1ca4a-c485-4fe0-9ff7-43369646b50f.png)

Emulates mouse action so you can perform simple tasks without reaching for the mouse.

## Adjust Layer (SYM + FUN)

![bm40rgb-wolff-adj](https://user-images.githubusercontent.com/62627597/228708232-9281bfb4-f7da-4999-9a62-9b102d6880a2.png)

# Additional/utility layers

These are utility overlays toggled by a key in the Adjust layer.

## Handswap Layer

![bm40rgb-swap-hands](https://user-images.githubusercontent.com/62627597/228847606-0c5a33d1-a683-41c8-a2af-6df582f6ef65.png)

For one-hand typing. The three top rows are mirrorred when SWAP is held down.

## CPY Layer (One-hand navigation layer)

![bm40rgb-copy](https://user-images.githubusercontent.com/62627597/228847641-4caa777e-c368-4921-a0a4-10c47afa2537.png)

For general navigation and quick copy-paste one-handed stuff. I don't like using it, but my job demands it sometimes.
