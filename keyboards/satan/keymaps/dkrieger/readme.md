# dkrieger HHKB like Layout

Base derived from dbroqua (special thanks)

Based on HHKB with the following [dip switches][1] engaged:

- SW3: delete key -> backspace
- SW5: swap alt and meta keys
- SW2: Mac Mode (partial implementation, includes media keys
    - Note: this was copied from dbroqua, there seem to have been some
      modifications from stock Mac Mode

Additionally, this layout includes a mouse layer engaged by tapping Fn 3 times,
holding on the third time. The arrow keys move the mouse, scrolling when shift
is held (either left or right). Right alt is left click, right meta is right
click.

# Programming Instructions:
Enter into programming mode and run the following command.
```
$ sudo KEYMAP=dkrieger_hhkb make dfu
```
[1]: http://www.elitekeyboards.com/products.php?sub=pfu_keyboards,hhkbpro2&pid=pdkb400b
