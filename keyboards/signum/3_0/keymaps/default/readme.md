# Default layout

Layout created by: [Jan Christoph Ebersbach](https://github.com/jceb)

The `generate_km.py` file automatically generates `keymap.c` with
additional comments that visually represent the layout.

This layout is maintained as I am using it. You can also use it as a
starting point to create your own layouts for the Signum 3.0 with
`km_template.txt` and `generate_km.py`.

# Customization

- Customize `layout.py` to your liking.
    - Attention 1: keycodes are either translated into symbols and
      function calls via the `translate()` function in `generate_km.py`
      or via user-defined mappings in the dictionary `qmk_dict` in
      `layout.py`. Especially the latter might require adjustment for
      uncommon qmk features
    - Attention 2: additional C functions need to be put into
      `km_template.txt`

Run `./generate_km.py` to regenerate `keymap.c` and the JSON keymap
definition that should be copied to `qmk_configurator/public/keymaps`.
