# Typehud Keymap

VIA compatible keymap that displays a live wpm HUD on your OLED.

<https://nullbits.co/static/file/snap-typehud.webp>

## Configuration

Configuration options (other than the keymap itself) can be found in `typehud/config.h`.

### Graph Type

By default the graph is filled. For a non-filled graph remove or comment out the following line:

```c
#define TYPEHUD_FILLGRAPH
```

### Keyboard Matrix Orientation

To change the keyboard matrix orientation add one of the following:

- `TYPEHUD_MATRIX_ROTATE_90`
- `TYPEHUD_MATRIX_ROTATE_180`
- `TYPEHUD_MATRIX_ROTATE_270`

### Keyboard Matrix Key Overrides

If the number of physical keys doesn't match the keyboard matrix rows/columns you can override it:

```c
#define TYPEHUD_MATRIX_ROWS 6
#define TYPEHUD_MATRIX_COLS 16
```

In addition if the position of the physical keys doesn't match the matrix you can override it. Negative numbers will shift the keys left/up and positive numbers will shift the keys right/down:

```c
#define TYPEHUD_MATRIX_ROW_SHIFT -1
#define TYPEHUD_MATRIX_COL_SHIFT -2
```

### Split Keyboard Side

For split keyboards, the keymap assumes it will be rendered to the slave side.

To render to master instead, add the following configuration line:

```c
#define TYPEHUD_MASTER
```
