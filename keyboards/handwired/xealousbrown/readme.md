# XealouS Brown

My first handwired keyboard. Originally used TMK, now ported in full glory to QMK.

Build log at:
https://sites.google.com/site/xaelous/keyboards/handwired-keyboard

Make example for this keyboard (after setting up your build environment):

    make handwired/xealousbrown:default


The brief list of speedhacks to make this keyboard blazing fast:
1) bit-bash implementation of scanning rows, columns. Very short delay between pin waiting.
2) Compiling with a few extra flags
3) Eager-per-key Debouncing algorithm (no 5ms delay before message is sent)
4) 1000hz polling
