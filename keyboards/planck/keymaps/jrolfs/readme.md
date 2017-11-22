# Jamie's Planck Keymap
This is a fairly standard Planck keymap with a `QWERTY` layout. Notable differences include dual function `Esc`/`Control` and `Shift`/`Enter` on the base layer. It also includes a "Function" layer to accommodate mappings typically found on "clutchless" keyboards such a 60% or the HHKB.

# Programming Instructions:
Enter into programming mode and run the following command.

```shell
$ make planck:jrolfs:dfu
```

# Notes
* `Escape` behaves as `Control` when used as a modifier
* `Enter` behaves as `Shift` when used as a modifier
* `Function` key in bottom left activates the `Function` layer which currently contains movement keys
