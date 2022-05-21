## Greetings, Traveler!

This layout is for the [Wuque ikki68 Aurora](https://shop.wuquestudio.com/pages/ikki68-aurora) and is primarily meant for Windows.

The keymap is similar to the default keymap for the Aurora, but it overloads the left alt key to behave like an additional 'Fn' key while keeping the standard functionality of the alt key intact.

### For Example
```
LeftAlt + 1...N         -> F1...FN
LeftAlt + L/R Arrows    -> Home/End
LeftAlt + Home          -> End
LeftAlt + Backspace     -> Delete
LeftAlt + Esc           -> Backtick (`)
LeftAlt + Shift + Esc   -> Tilde (~)
LeftAlt + LeftShift + 4 -> Alt+F4
```

The novel part of this keymap is that it **preserves the default functionality** of the left alt key, so ```'alt + tab', 'ctrl + alt + del', 'alt + f4'```, etc. all work as expected without having to use timers.

Everything also works with other modifier keys, so ```'alt + L/R' and 'alt + shift + L/R'``` work great for text manipulation to select lines.

This **super alt** keymap will feel very familiar for anyone **coming from macOS** since the Windows alt key is in the same position as CMD on macOS keyboards.

And finally, the original alt key functionality can be toggled at any time by pressing ```'Fn + period'``` so for example if a game requires use of the left alt, you can easily turn it off.

### Toggle LED Modes
You can also cycle though multiple LED modes (underglow, logo, all, none) by pressing ```'Fn + x'``` (the default ikki68 Aurora keymap only supports all or none). The last value set is persisted in EEPROM.

### Compiling/Flashing
1) After installing QMK MSYS, open the QMK MSYS terminal
2) Type ```qmk compile -kb wuque/ikki68_aurora -km ewersp``` to test compilation
3) Type ```qmk flash -kb wuque/ikki68_aurora -km ewersp``` to start flashing
4) Press ```Fn+Page Up``` to put your keyboard into bootloader mode
    - Note: After installing the keymap, to enter bootloader mode again press and hold ```Fn+B``` for half a second
5) Wait for the ```Validating... Success``` message to appear and you're done!
    - Note: If it gets stuck on ```Bootloader not found. Trying again every 0.5s...``` you may need to run QMK Toolbox to install/update drivers

If you have any questions, feel free to reach out to me at: ewersp [at] gmail [dot] com.

Enjoy! **<3**
