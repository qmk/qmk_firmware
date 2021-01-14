# External Userspace: Store your code outside the QMK repo

Store your [keymaps](keymap.md),  [community layouts](feature_layouts.md) and [userspace](feature_userspace.md) outside the `qmk_firmware` repository and automatically link it during build time.
This allows you to store your code in a separate `git` repository and manage it separately.
Updating the QMK repo should be easier as well, as the chance of code conflict is basically non-existent.

## Directory structure
*Note*: all directories and files are optional, create only what you actually need

* `/my_qmk_stuff/` (put it anywhere you'd like and name is whatever you want (no whitespaces, please))
  * `common/` (content will be always included, equivalent of [userspace](feature_userspace.md)))
    * `rules.mk`
    * `config.h`
    * `<name>.h`
    * `<name>.c`
    * `cool_rgb_stuff.c`
    * `cool_rgb_stuff.h`
  * `keyboards/` (keyboard-specific [keymaps](keymap.md))
    * `planck/`
      * `my_planck_keymap/` (keymaps for all Planck revisions)
        * `keymap.c`
        * `config.h`
      * `rev6` (keymaps only for the `planck/rev6`)
        * `my_rev6_keymap/`
          * `keymap.json`
          * `rules.mk` 
  * `layouts/` (layout specific keymaps, equivalent of [community layouts](feature_layouts.md))
    * `ortho_4x12/`
      * `my_grid_keymap/`
        * `keymap.c`

## Configuration

    qmk config user.userspace=/path/to/external_userspace

**Note**: It's important to specify absolute path.

*Example*: I created my external userspace in `/home/erovia/qmk/my_qmk_stuff`, so I have to run this command:

    qmk config user.userspace=/home/erovia/qmk/my_qmk/stuff

`qmk doctor` will check if the directory exists and if the provided path is an absolute one.

## Additional source files

You can add additional source files to the compilation with the EXT_SRC option, which is very similar to [SRC](config_options?id=build-options) used in in-tree keymaps.
You need to add the EXT_SRC in `rules.mk` like this:

    EXT_SRC += <filename>.c

Additional files may be added in the same way.

Similarly to [userspace](feature_userspace.md), the `common/rules.mk` file will be included in the build _after_ the `rules.mk` from your keymap. This allows you to have features in your userspace `rules.mk` that depend on individual QMK features that may or may not be available on a specific keyboard. 

For example, if you have RGB control features shared between all your keyboards that support RGB lighting, you can add support for that if the RGBLIGHT feature is enabled:
```make
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  # Include my fancy rgb functions source here
  EXT_SRC += cool_rgb_stuff.c
endif
```

Alternatively, you can `define RGB_ENABLE` in your keymap's `rules.mk` and then check for the variable in your userspace's `rules.mk` like this:
```make
ifdef RGB_ENABLE
  # Include my fancy rgb functions source here
  EXT_SRC += cool_rgb_stuff.c
endif
```
