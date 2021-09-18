# Georgi Plover HID firmware

This is a steno-only firmware for the Georgi using the (as of now) experimental Plover HID protocol
instead of a serial steno protocol.

This firmware only defines a keymap of the form:

```
X1 S1- T- P- H- S1 S3 -F -P -L -T -D
X2 S2- X- W- R- S2 S4 -R -B -G -S -Z
          #1 A  O  E  U  #7
```

and is meant to be used with the [plover-machine-hid](https://github.com/dnaq/plover-machine-hid) plugin.
