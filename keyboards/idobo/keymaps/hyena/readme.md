Hyena is a compact layout designed for typists, polyglots, mathematicians, programmers and Emacs users.

Hyena for QMK is heavily influenced by its parent Hyena for ``X11`` systems, keeping the same aims. For historic
information: [http://github.com/frgomes/hyena](http://github.com/frgomes/hyena).

For the impatient
-----------------

```bash
#!/bin/bash

# Install Python3 module for QMK:
pip3 install qmk

# Ask QMK to setup the development environment for you:
qmk setup

# Build Hyena keymap and flash it onto your device:
cd ~/qmk_firmware/keyboards/idobo/keymaps/hyena
qmk json2c -o keymap.c info.json && \
  qmk flash --keyboard idobo --keymap hyena
```

## Motivation

    1. use US ASCII as a starting point and
    2. have accents available for most popular European languages and
    3. mix in mathematical symbols and Greek letters and
    4. emulate arrow clusters on both hands for ease navigation and
    5. invert Ctrl and Alt in order to relieve my pinkies while in Emacs and
    6. all of that at the same time, without switching layouts in the OS.

I also would like to:

    7. have Hyper available in Emacs and
    8. choose alternative layouts, such as Dvorak, Colemak or Carpalx.

## Current status

A lot of work is still necessary in order to get the QMK version of Hyena to be on pair with
[the ``xkb`` version of Hyena](https://github.com/frgomes/hyena). Obviously, a programmable layout has potential of
becoming far more capable, but only after a complete feature set of the existing platform becomes fully implemented.

Currently, these features are missing in comparison with the ``xkb`` version of Hyena:

* mathematical and typographival characters;
* accented letters for a number of European languages.
