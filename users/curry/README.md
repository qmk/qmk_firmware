# Information

These is my userspace files, heavily influenced by @drashna's userspace structure.

# Keyboards

Main uses are for corne & lily58, supporting dfu bootloader (elite-c)

## Split Common
Is compatible with split_common when the previous two keyboards update to them. 

If you want to use these keymaps with split common code, they are on my personal github fork: [CurryFurious/qmk_firmware](https://github.com/CurryFurious/qmk_firmware)

Referenced PRs: #6260, #5998, #6001

## Keymaps
Keymap layout is similar between the two keyboards. Lily58 has a lot of open keys for custom keys as well. Keymap formatting is set up in the physical layout of the keyboard, so mapping keys should be easier.

## Tap Dances

Tap dances are enabled but none are defined, you can add them to [tapdances.c](tapdances.c). If not using tapdances, you can disable them in the keymaps.

## RGB 
RGB is implemented pretty much the same as @drashna. Only change is that I added the RGB code from the drashna's corne [keymap.c](../../keyboards/crkbd/keymaps/drashna/keymap.c), lines 313-383 into rgb_stuff.c.

## OLED
Similarly to RGB, I moved all OLED code into [oled.c](oled.c) to better clear up the keymap.c file. I haven't experimented with the kyria's 128x64 pixel screen so it probably won't work as well with it yet.

## Wrappers
Have implemented QWERTY, COLEMAK Mod DH, and DVORAK. Other macros are defined, some modified from drashna's. Drashna's [wrappers.h](../drashna/wrappers.h) has other layouts that you can copy in as you see fit, make sure to add them to the userspace_layers enum in [curry.h](curry.h)
