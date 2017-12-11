# Layouts: Using a Keymap with Multiple Keyboards

The `layouts/` folder contains different physical key layouts that can apply to different keyboards.

```
layouts/
+ default/
| + 60_ansi/
| | + readme.md
| | + layout.json
| | + a_good_keymap/
| | | + keymap.c
| | | + readme.md
| | | + config.h
| | | + rules.mk
| | + <keymap folder>/
| | + ...
| + <layout folder>/
+ community/
| + <layout folder>/
| + ...
```

The `layouts/default/` and `layouts/community/` are two examples of layout "repositories" - currently `default` will contain all of the information concerning the layout, and one default keymap named `default_<layout>`, for users to use as a reference. `community` contains all of the community keymaps, with the eventual goal of being split-off into a separate repo for users to clone into `layouts/`. QMK searches through all folders in `layouts/`, so it's possible to have multiple repositories here.

Each layout folder is named (`[a-z0-9_]`) after the physical aspects of the layout, in the most generic way possible, and contains a `readme.md` with the layout to be defined by the keyboard:

```md
# 60_ansi

   LAYOUT_60_ansi
```

New names should try to stick to the standards set by existing layouts, and can be discussed in the PR/Issue.

## Supporting a Layout

For a keyboard to support a layout, the variable (`[a-z0-9_]`) must be defined in it's `<keyboard>.h`, and match the number of arguments/keys (and preferably the physical layout):

    #define LAYOUT_60_ansi KEYMAP_ANSI

The folder name must be added to the keyboard's `rules.mk`:

    LAYOUTS = 60_ansi

`LAYOUTS` can be set in any keyboard folder level's `rules.mk`:

    LAYOUTS = 60_iso

but the `LAYOUT_<layout>` variable must be defined in `<folder>.h` as well.

## Tips for Making Layouts Keyboard-Agnostic

Instead of using `#include "planck.h"`, you can use this line to include whatever `<keyboard>.h` (`<folder>.h` should not be included here) file that is being compiled:

    #include QMK_KEYBOARD_H

If you want to keep some keyboard-specific code, you can use these variables to escape it with an `#ifdef` statement:

* `KEYBOARD_<folder1>_<folder2>`

For example:

```c
#ifdef KEYBOARD_planck
    #ifdef KEYBOARD_planck_rev4
        planck_rev4_function();
    #endif
#endif
```

Note that the names are lowercase and match the folder/file names for the keyboard/revision exactly.
