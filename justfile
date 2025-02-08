make:
    make splitkb/aurora/sofle_v2/rev1:nilscc

[no-cd]
json2c INPUT="keymap_in.json":
    qmk json2c -o keymap.c {{INPUT}}
    @echo "Please verify generated keymap.c manually!"
