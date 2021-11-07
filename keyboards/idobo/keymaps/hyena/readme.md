Hyena is a compact layout designed for typists, polyglots, mathematicians, programmers and Emacs users.

Hyena for QMK is heavily influenced by its parent Hyena for ``X11`` systems, keeping the same aims. For historic
information: [http://github.com/frgomes/hyena](http://github.com/frgomes/hyena).

## For the impatient

    qmk flash -kb idobo -mk hyena

## Motivation

    1. use US ASCII as a starting point and
    2. have accents available for most popular European languages and
    3. mix in mathematical symbols and Greek letters and
    4. emulate arrow clusters on both hands for ease navigation and
    5. invert Ctrl and Alt in order to relieve poor pinkies while in Emacs and
    6. works on Linux and [Windows with alternative modifier chords](https://www.gnu.org/software/emacs/manual/html_node/emacs/Modifier-Keys.html#Modifier-Keys) and
    7. works behind [TESmart KVM switch](https://www.tesmart.com/collections/kvm-switch/products/tesmart-4x1-hdmi-kvm-switch-4k-60hz4-4-4-auto-seamless-switching-audio-output-usb-sharing-4-port-hdmi-kvm-switcher-with-2-pcs-5ft-kvm-cables-controls-up-to-4-computers-servers-dvr-red)
    8. all of that at the same time, without switching layouts in the OS.

I also would like to:

    9. have Hyper available in Emacs and
    10. choose alternative layouts, such as Dvorak, Colemak or Carpalx.

## Current status

A lot of work is still necessary in order to get the QMK version of Hyena to be on pair with
[the ``xkb`` version of Hyena](https://github.com/frgomes/hyena). Obviously, a programmable layout has potential of
becoming far more capable, but only after a complete feature set of the existing platform becomes fully implemented.

Currently, these features are missing in comparison with the ``xkb`` version of Hyena:

* mathematical and typographival characters;
* accented letters for a number of European languages.
