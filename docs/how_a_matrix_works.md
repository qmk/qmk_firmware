# How a Keyboard Matrix Works

Keyboard switch matrices are arranged in rows and columns. Without a matrix circuit, each switch would require its own wire directly to the controller.

When the circuit is arranged in rows and columns, if a key is pressed, a column wire makes contact with a row wire and completes a circuit. The keyboard controller detects this closed circuit and registers it as a key press.

The microcontroller will be set up via the firmware to send a logical 1 to the columns, one at a time, and read from the rows, all at once - this process is called matrix scanning. The matrix is a bunch of open switches that, by default, don't allow any current to pass through - the firmware will read this as no keys being pressed. As soon as you press one key down, the logical 1 that was coming from the column the keyswitch is attached to gets passed through the switch and to the corresponding row - check out the following 2x2 example:

        Column 0 being scanned     Column 1 being scanned
                  x                                   x
                 col0     col1              col0     col1
                  |        |                 |        |
        row0 ---(key0)---(key1)    row0 ---(key0)---(key1)
                  |        |                 |        |
        row1 ---(key2)---(key3)    row1 ---(key2)---(key3)

The `x` represents that the column/row associated has a value of 1, or is HIGH. Here, we see that no keys are being pressed, so no rows get an `x`. For one keyswitch, keep in mind that one side of the contacts is connected to its row, and the other, its column.

When we press `key0`, `col0` gets connected to `row0`, so the values that the firmware receives for that row is `0b01` (the `0b` here means that this is a bit value, meaning all of the following digits are bits - 0 or 1 - and represent the keys in that column). We'll use this notation to show when a keyswitch has been pressed, to show that the column and row are being connected:

        Column 0 being scanned     Column 1 being scanned
                  x                                   x
                 col0     col1              col0     col1
                  |        |                 |        |
      x row0 ---(-+-0)---(key1)    row0 ---(-+-0)---(key1)
                  |        |                 |        |
        row1 ---(key2)---(key3)    row1 ---(key2)---(key3)

We can now see that `row0` has an `x`, so has the value of 1. As a whole, the data the firmware receives when `key0` is pressed is:

    col0: 0b01
    col1: 0b00
            │└row0
            └row1

A problem arises when you start pressing more than one key at a time. Looking at our matrix again, it should become pretty obvious:

        Column 0 being scanned     Column 1 being scanned
                  x                                   x
                 col0     col1              col0     col1
                  |        |                 |        |
      x row0 ---(-+-0)---(-+-1)  x row0 ---(-+-0)---(-+-1)
                  |        |                 |        |
      x row1 ---(key2)---(-+-3)  x row1 ---(key2)---(-+-3)

      Remember that this ^ is still connected to row1

The data we get from that is:

    col0: 0b11
    col1: 0b11
            │└row0
            └row1

Which isn't accurate, since we only have 3 keys pressed down, not all 4. This behavior is called ghosting, and only happens in odd scenarios like this, but can be much more common on a bigger keyboard. The way we can get around this is by placing a diode after the keyswitch, but before it connects to its row. A diode only allows current to pass through one way, which will protect our other columns/rows from being activated in the previous example. We'll represent a dioded matrix like this;

        Column 0 being scanned     Column 1 being scanned
                    x                                   x
                  col0      col1              col0     col1
                    │        │                 |        │
                 (key0)   (key1)            (key0)   (key1)
                  ! │      ! │               ! |      ! │
        row0 ─────┴────────┘ │     row0 ─────┴────────┘ │
                    │        │                 |        │
                 (key2)   (key3)            (key2)   (key3)
                  !        !                 !        !
        row1 ─────┴────────┘       row1 ─────┴────────┘

In practical applications, the black line of the diode will be placed facing the row, and away from the keyswitch - the `!` in this case is the diode, where the gap represents the black line. A good way to remember this is to think of this symbol: `>|`

Now when we press the three keys, invoking what would be a ghosting scenario:

        Column 0 being scanned     Column 1 being scanned
                    x                                   x
                  col0      col1              col0     col1
                    │        │                 │        │
                 (┌─┤0)   (┌─┤1)            (┌─┤0)   (┌─┤1)
                  ! │      ! │               ! │      ! │
      x row0 ─────┴────────┘ │   x row0 ─────┴────────┘ │
                    │        │                 │        │
                 (key2)   (┌─┘3)            (key2)   (┌─┘3)
                  !        !                 !        !
        row1 ─────┴────────┘     x row1 ─────┴────────┘

Things act as they should! Which will get us the following data:

    col0: 0b01
    col1: 0b11
            │└row0
            └row1

The firmware can then use this correct data to detect what it should do, and eventually, what signals it needs to send to the OS.

Further reading:
- [Wikipedia article](https://en.wikipedia.org/wiki/Keyboard_matrix_circuit)
- [Deskthority article](https://deskthority.net/wiki/Keyboard_matrix)
- [Keyboard Matrix Help by Dave Dribin (2000)](https://www.dribin.org/dave/keyboard/one_html/)
- [How Key Matrices Works by PCBheaven](https://pcbheaven.com/wikipages/How_Key_Matrices_Works/) (animated examples)
- [How keyboards work - QMK documentation](how_keyboards_work)
