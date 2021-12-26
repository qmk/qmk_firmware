# diverge2

A split 5x7 keyboard with 3 thumb keys. Made by Unikeyboard, which seems to no longer exist.

Keyboard Maintainer: [skewwhiffy](https://github.com/skewwhiffy)  
Hardware Supported: Pro Micro  
Hardware Availability: Diverge 2, no longer available.

After setting up your build environment, you can build this using the command
```
qmk compile -kb diverge2 -km skewwhiffy
```

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools).

# Known issues

The number row is not working at the time of writing.

# Reflashing Animus
Reflashing the stock firmware is pretty easy. Just follow the same steps in the [original guide](https://imgur.com/a/8UapN). You will have to manually reset the Pro Micro (by shorting the GND and RST pins) during the upload step. Then reapply your keymap through Arbites.
