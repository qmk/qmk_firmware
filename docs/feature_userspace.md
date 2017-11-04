# Userspace: sharing code between keymaps

If you use more than one keyboard with a similar keymap, you might see the benefit in being able to share code between them. Create your own folder in `users/` named the same as your keymap (ideally your github username, `<name>`) with the following structure:

* `/users/<name>/` (added to the path automatically)
  * `readme.md`
  * `rules.mk` (included automatically)
  * `<name>.h` (optional)
  * `<name>.c` (optional)

`<name>.c` will need to be added to the SRC in `rules.mk` like this:

    SRC += <name>.c

Additional files may be added in the same way - it's recommended you have one named `<name>`.c/.h though.

All this only happens when you build a keymap named `<name>`, like this:

    make planck:<name>

For example, 

    make planck:jack

Will include the `/users/jack/` folder in the path, along with `/users/jack/rules.mk`.

## Readme

Please include authorship (your name, github username, email), and optionally [a license that's GPL compatible](https://www.gnu.org/licenses/license-list.html#GPLCompatibleLicenses).

## Example

For a brief example, checkout `/users/_example/` until we have more reasonable and useful examples.