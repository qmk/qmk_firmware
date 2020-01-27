# The Deft Planck Layout

![Deft layout for the Planck keyboard](https://i.imgur.com/VtUkAyh.png)

The Deft Planck layout is designed for efficiency in programming and transferability between ortholinear boards. It features a fairly standard default layer with properly placed arrow keys, a lower layer with a usable numpad and symbols, and a raise layer for numbers, f-keys, and music controls. The code is also cut down to only what you need. The result is a very usable Planck that can easily replace fullsize layouts.

The strangely placed Enter key is meant to be closer to your thumb and moving it allows for proper arrow key placement without disturbing our layout too much. I wanted to separate the enter key from the forward slash key anyway, as I was commonly pressing enter when I meant to type a question mark. You get used to it pretty fast.

Follow my cat:

https://twitter.com/CatBucha

https://www.instagram.com/buchathecat/


## Flashing:
| Rev 5 or earlier: | Rev 6: |
|-|-|
| `make planck/revX:deft:dfu` | `make planck/rev6:deft:dfu-util` |

## Layout:

### QWERTY layer
```
,-----------------------------------------------------------------------------------.
| Esc  |  Q   |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Tab  |  A   |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
|------+------+------+------+------+------|------+------+------+------+------+------|
|Shift |  Z   |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |  /   |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Ctrl | Alt  | GUI  | Copy |Lower |    Space    |Raise |Enter | Left | Down |Right |
`-----------------------------------------------------------------------------------'
```

### Lower layer
```
,-----------------------------------------------------------------------------------.
| Del  | Alt1 | Alt2 | Alt3 | Alt4 |  (   |  )   | Num7 | Num8 | Num9 | Num0 |      |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |  `   |  \   |  =   |  -   |  <   |  >   | Num4 | Num5 | Num6 | Num. | NumL |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      | Num/ | Num* | Num- | Num+ |  [   |  ]   | Num1 | Num2 | Num3 | Pgup | Num= |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |Paste |      |             |      | NumE | Home | Pgdn | End  |
`-----------------------------------------------------------------------------------'
```

### Raise layer
```
,-----------------------------------------------------------------------------------.
|      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      | F11  | F12  | F13  | F14  | F15  | F16  | F17  | F18  | F19  | Vol+ |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      | Cut  |      |             |      |      | Play | Vol- | Next |
`-----------------------------------------------------------------------------------'
```

### Adjust layer
```
,-----------------------------------------------------------------------------------.
|Reset |      |      |      |      |      |      |      |      |      |      |      |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |      |      |      |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |      |      |      |      |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |             |      |      |      |      |      |
`-----------------------------------------------------------------------------------'
```
