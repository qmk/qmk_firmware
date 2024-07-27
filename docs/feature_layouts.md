# Community Layouts

This feature allows a keymap to be shared with and compiled on keyboards that have the same, community-established, physical layout.

#### Example
You have a QMK powered, TKL ANSI keyboard flashed with a keymap of your new experimental functional layout. Your friend/"partner in keyboard layout crime" also has a QMK powered, TKL ANSI physical layout keyboard but it's a different manufacturer and/or model to your keyboard and therefore would require your friend to recreate your experimental keymap exclusively for their keyboard.
In this example, although both keyboards have an identical physical layout, this same keymap would have to be defined twice; once for each specfic keyboard. By placing your experimental keymap within the respective `tkl_ansi` Community Layout directory, the keymap in question has been defined once so it can be compiled for your keyboard, your friend's keyboard, and every QMK powered keyboard with `tkl_ansi` Community Layout support.

[Miryoku](https://github.com/manna-harbour/miryoku) functional layout is a prominent utiliser of this feature.

?> Community Layouts also function in conjunction with the [Userspace](./feature_userspace.md) feature.

## Directory Structure
The `layouts/` directory acts as the parent directory for this feature.
The `layouts/default/` and `layouts/community/` sub-directories are two examples of Community Layout "repositories":
- `default/` contains reference information regarding each Community Layout, which includes a default keymap for testing Community Layout support.  
- `community/` is typically used for storing local (to GitHub Repository) keymaps and community/user shared keymaps (e.g. Miryoku) for each respective Community Layout.

To assist explanation of concepts, terms encapsulated in angled brackets are used.
```
layouts/
├── default/
│   └── <community_layout>/
│       └── <community_layout_keymap>/
│           └── keymap.c
└── community/
    └── <community_layout>/
        └── <community_layout_keymap>/
            └── keymap.c
```
**<community_layout>**: As well as sub-directory name, this serves as the Community Layout name  
**<community_layout_keymap>**: As well as sub-directory name, this serves as keymap name

## Add Community Layout support to keyboard

For a keyboard to support one or more Community Layouts, the keyboard's `info.json`/`keyboard.json` file must include:
1. A `"community_layouts"` array containing the name(s) of the respective Community Layout(s) the keyboard in question supports. Name(s) must be identical to *<community_layout>*.
#### `layouts/` directory example:
```
layouts/
└── default/
    ├── 60_ansi/
    │   └── <...>
    └── 60_iso/
        └── <...>
```
#### keyboard's `info.json`/`keyboard.json`file:
```json
    "community_layouts": ["60_ansi", "60_iso"]
```
2. Within `"layouts"` object literal, for each Community Layout supported, add layout information with macro name that is identical to the respective Community Layout's macro name; macro name is specified in keymap file (`keymap.c`/`keymap.json`) of *<community_layout_keymap>*.

#### Macro name example for Community Layout `60_ansi`
`layouts/default/60_ansi/default_60_ansi/keymap.c`:
```c
    [0] = LAYOUT_60_ansi(
        ...
    )
```

#### Keyboard's `info.json`/`keyboard.json` file:
```json
    "layouts": {
        "LAYOUT_60_ansi": {
            "layout": [
                {...}
            ]
        }
    }
```

Additionally, for each Community Layout being added to `"layouts"`:
- Array length of `"layout"` **must** match array length of respective Community Layout
- key sequence (i.e. order of keys from top to bottom) and graphical properties of each key (i.e. `"x":`, `"y":`, `"w":`, `"h":`) should be identical to respective Community Layout

Array length and key sequence for each Community Layout are located in `layouts/default/`*<community_layout>*`/info.json`.

## Compiling Community Layout keymap
Compiling keyboard firmware with a keymap inside either Community Layout repository is identical to regular keymap compilation, with the difference of the keymap argument being *<community_layout_keymap>*: 

    qmk compile -kb <keyboard> -km <community_layout_keymap>

The following examples compile the "default" keymap for the repsective Community Layouts; generally used to test if Community Layout support has been implemented correctly for the given keyboard:

    qmk compile -kb dztech/pluto -km default_tkl_nofrow_ansi
    qmk compile -kb dz60 -km default_60_iso

### Conflicting Keymaps
When compiling a <community_layout_keymap> that has the same name in two or more <community_layouts> the target keyboard supports, this can result in the undesired keymap being compiled.

#### Example Scenario:
Using the `contra` keyboard in this scenario, as it supports `ortho_4x12` and `planck_mit` Community Layouts.

**keyboard's `info.json`/`keyboard.json`**
```json
"community_layouts": ["ortho_4x12", "planck_mit"]
```

**layouts/ directory example**
```
layouts/
└── community/
    ├── ortho_4x12/
    │   └── jondough/
    │       └── keymap.c
    └── planck_mit/
        └── jondough/
            └── keymap.c
```
Running `qmk compile -kb contra -km jondough` without additional context doesn't determine which `jondough` keymap is being specified for compilation.

In this scenario the `FORCE_LAYOUT` argument is included, to specify from which <community_layout> the specified keymap is located:

    qmk compile -kb <keyboard> -km <community_layout_keymap> -e FORCE_LAYOUT=<community_layout>

Example:

    qmk compile -kb contra -km jondough -e FORCE_LAYOUT=planck_mit
