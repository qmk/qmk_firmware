# jhenahan's layout

## Layout

The base layer is based on the
[Workman Dead](https://github.com/ojbucao/Workman/tree/master/mac) layout. The
primary interaction layer is a slightly modified Workman layout with a 'dead'
key on the third row under the middle finger. The dead key activates a layer of
special characters.

## [Layers](http://www.keyboard-layout-editor.com/#/gists/2b875f7d5d76fe4408c0a5b3bd76ddae)
### Function Layer

This is very slightly modified from the default, mainly just to rearrange the media keys.

### [KWM](https://github.com/koekeishiya/kwm) Interaction Layer

`kwm` is a tiling window manager for OS X. The keys defined in my keymap
correspond to the settings I use in
[my `kwmrc` file](https://github.com/jhenahan/dotfiles/blob/master/kwm/kwmrc).

### QWERTY

Just in case.

### [Plover](http://www.openstenoproject.org/plover/)

This layout functions exactly as a Workman layout unless you're running the Plover
application. Includes a key for toggling Plover while it's running.

Add this in the appropriate section of your `plover.cfg` to allow this altered layout:

``` ini
[System: English Stenotype]
keymap[keyboard] = [["#", ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "="]], ["S-", ["q", "a"]], ["T-", ["d"]], ["K-", ["s"]], ["P-", ["r"]], ["W-", ["h"]], ["H-", ["w"]], ["R-", ["t"]], ["A-", ["m"]], ["O-", ["c"]], ["*", ["y", "g", "j", "b"]], ["-E", ["l"]], ["-U", [","]], ["-F", ["f"]], ["-R", ["n"]], ["-P", ["u"]], ["-B", ["e"]], ["-L", ["p"]], ["-G", ["o"]], ["-T", [";"]], ["-S", ["i"]], ["-D", ["BackSpace"]], ["-Z", ["'"]], ["no-op", ["\\", "]", "x", ".", "/"]], ["arpeggiate", ["space"]]]
```

### Adjust Layer

This layer is only slightly modified from the default to remove Dvorak and
Colemak and replace them with Workman.
