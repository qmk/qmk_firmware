make:
    make splitkb/aurora/sofle_v2/rev1:nilscc -e CONVERT_TO=liatris

[no-cd]
json2c INPUT="keymap_in.json":
    qmk json2c -o keymap.c {{INPUT}}
    @echo "Please verify generated keymap.c manually!"
