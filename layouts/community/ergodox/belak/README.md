# Belak's Ergodox Layout

This has been based off of [emacs\_osx\_dk](https://github.com/qmk/qmk_firmware/tree/master/layouts/community/ergodox/emacs_osx_dk)
from the main qmk repo. However, I've taken some of the ideas for the thumbs
from [dvorak\_emacs](https://github.com/qmk/qmk_firmware/tree/master/layouts/community/ergodox/dvorak_emacs)
and tweaked it a bit based on the keycaps I have.

This keyboard is intended for use in emacs (one of the main reasons for easy
access to modifiers) but it could be useful in other instances as well.

The main repo is used as a testbed, so sometimes the layout may be in a strange
state. The qmk version should be relatively stable.

## Instructions

This is currently being used on a regular ergodox, but it should work fine on
the infinity as well. Though, you may have to modify the commands to build and
flash the firmware to match the separate halves as defined in the infinity
documentation.

If you are using this keymap in the qmk repo, you should be able to just run
`make ergodox-belak-teensy`. If you're using this externally (I sometimes make
changes before syncing them to qmk), use the following instructions:

1. Clone the main qmk repo
2. Clone this to `$QMK/keyboards/ergodox/keymaps/belak-external`
3. Run `make ergodox-belak-external-teensy` from the root of the qmk repo.

## Changelog

Fifth Revision

* Change layer keys to tap-dance keys which cycle through additional layers
* Add a few emoji keys (in preparation for an emoji layer)

Fourth Revision

* Remove media layer
* Add a layer which swaps control and gui on the thumb keys.
* Add some basic code to save settings to the eeprom
* Save the state of the keys swapped in the thumb in the eeprom

Third Revision

* Add numpad layer and remove numpad from symbols layer
* Disable media layer
* Add arrow keys on ijkl to the symbols layer
* Replace ALT on held enter and held delete with GUI (for better OSX
  compatibility, as there's already an ALT key relatively close)
* Replace keys above enter and delete with temporary layer switch buttons not
  matching the other layer switch for that hand.
* Reindent and space out most of the layer definitions

Second Revision

* Clean up definitions to make differences between layers easier to see
* Remove old LCD code
* Add new LCD code based on fredizzimo's branch

First Revision

* Reverse grave and escape

Initial Version

* Copy from emacs\_osx\_dk
* "Fix" right alt
* Change thumb keys to match default layout (backspace, delete, enter, space)
* Add modifiers to thumb keys (ctrl to backspace and space, alt to delete and
  enter)
* Replace the RAlt below the brackets with LGui and RGui
* Remove LCtrl and RCtrl from the keys above shift
* Add browser forward, and move browser back
* "Fix" the order of volume keys

## Repository

The original code for this is kept at https://github.com/belak/ergodox-layout and
is synced to qmk every few main revisions.
