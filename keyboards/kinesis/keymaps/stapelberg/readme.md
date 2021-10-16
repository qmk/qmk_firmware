# Michael Stapelberg’s keymap for the Kinesis Advantage

I adjust the thumb block mapping slightly to have a standard set of modifiers
(Control, Alt, GUI/Windows, Right Alt) and Escape available conveniently.

Specifically, my keymap makes the following changes:

* Left thumb block:
  * Swap `Delete` with `Escape` (top left), from my Vim days :)
  * The `Home` key on the left thumb block is replaced by `Left GUI/Windows`.
* Right thumb block:
  * The top left key on the right thumb block produces `Right Alt`.

## Corresponding Kinesis configuration

My keymap corresponds to the following Kinesis configuration tool settings:

```
[escape]>[delete]
[rwin]>[ralt]
[delete]>[escape]
[home]>[lwin]
[intl-\]>[kp-insert]
```

Note: the last line makes the international key (labeled `|`, `\` and `Insert`)
produce `Insert`, which is default with QMK, but not default Kinesis.
