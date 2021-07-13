@pierrec83's personal keymap for the Ferris keyboard
====================================================

This keymap shares many commonalities with the default keymap.
See its readme for a write-up on many of the decisions, including
how to generate the formatted json file with json2crab.py and the
general philosophy for each layer.

Because this is my own keymap, I didn't refrain from using shortcuts
that make sense for me and may not make sense for most.

Key differences from the default keymap include:

Alpha layers:
-------------

Because I only learned to touch type when I switched from qwerty to workman,
my base layer is workman and my layout doesn't contain a qwerty layer.

My layer 1 hosts a variant of RSTHD that I am developing, inspired from workman's
focus on reducing side-index-motion. It should become my end game keymap eventually,
but I still haven't found the time to learn it to a working proficiency.

Secondary thumbs:
-----------------

Instead of a placeholder 0 and 1, the secondary thumbs on my keymap
perform the following actions:
* Navigate to previous and next workspace the base layer
* Navigate to previous and next tab on the mouse layer
* Volume control on layer
* Brightness control on layer

Mouse layer:
------------

* Copy/Paste shortcuts on the left hand, on the upper row.

Always available layer:
-----------------------

* Esc and column are placed differently to allow easy vim navigation with the positions of w and q in the workman base layer
* Enable permanent switch to the RSTHD layer in addition to the mouse layer
