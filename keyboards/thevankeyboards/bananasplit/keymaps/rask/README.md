# rask's BananaSplit60

![BS60 layout](http://i.imgur.com/Q7so1py.png)

## Notes

### Layers

Base layer is a regular HHKBish ANSI layer. Toggling the
alternate base layer (Fn3) makes it simpler to play games with
the left space being set to be an actual Space.

Layer 1 (Fn1) contains usual 60% functionalities such as the
F-row, while Layer 2 (Fn2) contains media controls.

The final layer (Fn4) is a special layer that acts as a lock
layer, meaning the keyboard is locked while the layer
is active. This firmware assumes a lock switch (read below).

### Lock switches

1.25u between the split space halves and the 1u key right
left of LeftArrow are to be operated with a lock switch.
If you don't have lock switches you should swap the `MO()`
calls with `TG()` calls to make the layer toggles work
with regular non/locking switches.

## How to make and flash

(These instructions are for Linux-based operating systems
with `dfu-programmer` available.)

`cd` into the `bananasplit` keyboard's directory and run

    make rask

which should result in a file called `bananasplit_rask.hex` appearing
in your QMK root directory.

Now plug in your BananaSplit60 keyboard via USB. Verify
with `lsusb` that it appears. At least my PCB did not have
anything preflashed so you should see `atmega32u4` or similar
in the `lsusb` output.

Now you can flash the firmware by

    $ sudo dfu-programmer atmega32u4 erase
    $ cd /qmk_firmware/root/directory
    $ sudo dfu-programmer atmega32u4 flash bananasplit_rask.hex

_If_ you happen to have some other `atmega32u4` based device
I suggest you plug it out before flashing your BS60 just to
prevent accidentally flashing your old device.
