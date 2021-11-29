# colinta's keymap for XD75

```
make xiudi/xd75:colinta:dfu
```

The default layout is a Colemak keyboard with "one-shot" keys assigned to the modifier keys.

    .--------------------------------------------------------------------------------------------------------------------------------------.
    | ESC    | 1      | 2      | 3      | 4      | 5      | DYN_M1 | DYN_M2 | DEL    | 6      | 7      | 8      | 9      | 0      | -      |
    |--------+-/F1----+-/F2----+-/F3----+-/F4----+-/F5----+--------+--------+--------+-/F6----+-/F7----+-/F8----+-/F9----+-/F10---+--------|
    | TAB    | Q      | W      | F      | P      | G      | MACRO  |  (FN)  | BKSP   | J      | L      | U      | Y      | ;      | =      |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
    | SHIFT  | A      | R      | S      | T      | D      | [      | ]      | ENTER  | H      | N      | E      | I      | O      | '      |
    |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
    | CTRL   | Z      | X      | C      | V      | B      | HOME   | END    | PG UP  | K      | M      | ,      | .      | /      | \      |
    |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
    | VOL-   | PLAY   | VOL+   | ALT    | GUI    |          SPACE           | PG DN  | MENU   | ESC    | LEFT   | DOWN   | UP     | RIGHT  |
    '--/RRND----/MUTE----/FFWD-------------------------------------------------------------------------------------------------------------'


I've implemented my own "tap/hold" feature, identical in spirit to "Space Cadet", but generic.  Tapping "1" sends a 1, but press and hold to send "F1".  Or, tap "VOL-" to turn the volume down, but press and hold to rewind.

The function layer is only to switch to Qwerty (so other people can use this keyboard - also turns off sticky keys) and to start recording keypresses.

I implemented "stop recording" in a unique way; starting a macro recording sends the keyboard layer to one that has all the macro keys assigned to `DYN_REC_STOP`, and restores the layer to the default when recording is stopped.

I wish Dynamic Macros supported more, because I'd like to record a third macro in the MACRO slot instead of hardcoding it.  I'm using these to store some passwords.

## Regarding "secrets.h"

The macros I'm using are sensitive, I'm comfortable having them hardcoded onto my keyboard (no SSN or private GPG keys), but not suitable for public viewing.  So I've put them in a header file that is excluded from the project, and I can include this file using a compiler flag.

If you would *also* like to take advantage of this feature, you'll first want to make sure your "secrets" file isn't included in the repo.  Open `.git/info/exclude` and add `secrets.h` to that file, below the comments.

###### .git/info/exclude
```
# git ls-files --others --exclude-from=.git/info/exclude
# Lines that start with '#' are comments.
# For a project mostly in C, the following would be a good set of
# exclude patterns (uncomment them if you want to use them):
# *.[oa]
# *~
/keyboards/xiudi/xd75/keymaps/colinta/secrets.h
```

Then you can create this file and add your macro strings to it:

```
$EDITOR keyboards/xiudi/xd75/keymaps/colinta/secrets.h
```

###### secrets.h
```
#define SENDSTRING_MM0 "abcd1234"
#define SENDSTRING_MM1 "shhhhh secret"
#define SENDSTRING_MM2 "stop saying pickle rick"
```

To include the feature at compile time, include the flag `IS_COLINTA` like so:

```
make xiudi/xd75:colinta:dfu EXTRAFLAGS=-DIS_COLINTA
```
