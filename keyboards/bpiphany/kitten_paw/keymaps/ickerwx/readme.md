# My personal keymap for the Kitten Paw controller

This keymap only works correctly when you have your OS configured with a German keymap. Use the keymap however you like. It's most likely a living thing that will never be quite finished.

## Description of the layers
Layer 0 (DEFAULT) works just like you would expect a keyboard to work, mostly, except:
Caps Lock switches to the mouse layer, RGUI and APP are switches to the programming layer and media layer.
Mouse and programming layer switches can be held or double-tapped to lock.
Holding space switches to the MISC layer where I currently accumulate useful shortcuts.
Tapping left and right Shift, Ctrl and Alt will send (), [] and {} respectively.

Layers 1 and 2 (PROG1 and PROG2) emulate the US layout while still using a German OS keymap setting. I was annoyed of having to change the OS settings every time I wanted to use the US layout for coding, so I made these layers to behave just like the US layout even though the OS still uses German. The shift keys were a bit tricky, I had to use them as MO(PROG2) switches, so to get the actual expected behavior I enable LSFT for almost every keypress on PROG2 in ```process_record_user```. Since the shift keys are MO() function keys, they do not print () at the moment, which sucks. I'm working on it.

Layer 3 (MEDIA) just has a couple of media keys on it, mainly around the cursor keys and nav key cluster.

Layers 4 and 5 (MOUSE1 and MOUSE2) are mouse layers. Move the cursor using ESDF, scroll using HJKL, Space for left click, N and M for right and middle click. There's more, look at the keymap.

Layer 6 is a layer I don't have a good name for, so I call it MISC. You'll find cursor keys at ESDF, other navigation keys around the HJKL cluster and F12 to F24 on the F-keys. For now.