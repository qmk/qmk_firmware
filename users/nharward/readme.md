# nharward's mod to manna-harbour_miryoku

I'm a new fan of miryoku but cannot get past the muscle memory from using
a Kinesis Advantage2. I wanted miryoku (plus QWERTY and vi navigation) but
with the space and backspace keys swapped. I've reused miryoku source
wherever I can, only patching a custom configuration and a modified
`miryoku_babel/miryoku_layer_alternatives.h` generated from the org
[source](https://github.com/nharward/miryoku_babel/tree/nharward).

## Updating

Run `make -f .makefile clean` followed by `make -f .makefile`. This will copy
(most) source files from `../manna-harbour_miryoku` then patch with the minor
mods described above.
