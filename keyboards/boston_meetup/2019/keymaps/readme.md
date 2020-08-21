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

# List of 2019 keymaps

* **default** default 2019 macropad layout