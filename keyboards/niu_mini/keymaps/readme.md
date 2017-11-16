# How to add your own keymap

Folders can be named however you'd like (will be approved upon merging), or should follow the format with a preceding `_`:

    _[ISO 3166-1 alpha-2 code*]_[layout variant]_[layout name/author]

\* See full list: https://en.wikipedia.org/wiki/ISO_3166-1#Officially_assigned_code_elements

and contain the following files:

* `keymap.c`
* `readme.md` *recommended*
* `config.h` *optional*, found automatically when compiling
* `Makefile` *optional*, found automatically when compling

When adding your keymap to this list, keep it organised alphabetically (select list, edit->sort lines), and use this format:

     * **folder_name** description

# List of keymaps

<<<<<<< HEAD
* **default** default Planck layout
=======
- **default** default layout from KBDFans
- **planck** Planck default layout
>>>>>>> 05f15b789f4f6098a72474e028a19fdbccdaf2d3
