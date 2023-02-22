# buffet's planck layout

## Layout

The Layout is based on keychords.
The general idea is that you're able to type everything with either hand, so that you can alternate between hands as you type.

The keys are in a 2x4 block in the top left and top right respectively (mirrored).
They have greek letter names (see `keymap.c` for more info).

Thumb added to any key means shift is pressed as well.

`-` means the finger presses nothing.
`^` means the finger presses the upper row.
`v` means the finger presses the lower row.

```
Space:   thumb
Return:  vvvv  vvvv
Tab:     vv^v  v^vv
Bspace:  v--v  v--v
Esc:     lower pinky and thumb
```

### Letters

```
a:  -^--  --^-
b:  -v-^  ^-v-
c:  -^^^  ^^^-
d:  -vvv  vvv-
e:  ---^  ^---
f:  --^v  v^--
g:  -^v-  -v^-
h:  -vv-  -vv-
i:  --^-  -^--
j:  -^^v  v^^-
k:  -^vv  vv^-
l:  -^^-  -^^-
m:  -^-^  ^-^-
n:  -v--  --v-
o:  --v-  -v--
p:  -v^-  -^v-
q:  -^v^  ^v^-
r:  --^^  ^^--
s:  --vv  vv--
t:  ---v  v---
u:  -v-v  v-v-
v:  --v^  ^v--
w:  -v^v  v^v-
x:  -vv^  ^vv-
y:  -^-v  v-^-
z:  -v^^  ^^v-
```

### Numbers and Symbols

```
0:  vv--  --vv
1:  vv-v  v-vv
2:  vvv-  -vvv
3:  v^--  --^v
4:  v^-^  ^-^v
5:  v^^-  -^^v
6:  v^-v  v-^v
7:  v-v-  -v-v
8:  v^^v  v^^v
9:  v-^^  ^^-v
-:  v^vv  vv^v
=:  vvv^  ^vvv
[:  vv^-  -^vv
]:  v-^v  v^-v
\:  v^v-  -v^v
;:  v^^^  ^^^v
':  vv-^  ^-vv
,:  v-vv  vv-v
.:  vv^^  ^^vv
/:  v-^-  -^-v
`:  v--^  ^--v
```

### Modifiers

Modifiers all use the top pinky key, and a combinations of modifiers you want to activate for the next keypress (very similar to how OMS work).
For the modifiers the top row of keys is used.

```
Control: Ringfinger
Shift:   Middlefinger
Alt:     Indexfinger
Super:   Thumb
```

`^--v  v--^` can be used to lock the next modifier input.

### Remaining

These combinations are unused.

```
v^v^
v-v^
v---
```
