# Quantum Hand-wiring Guide

Parts list:
* *x* keyswitches (MX, Matias, Gateron, etc)
* *x* diodes
* Keyboard plate (metal, plastic, cardboard, etc)
* Wire (strained for wiring to the Teensy, anything for the rows/columns)
* Soldering iron set at 600ºF or 315ºC (if temperature-controlled)
* Resin-cored solder (leaded or lead-free)
* Adequate ventilation/a fan
* Tweezers (optional)
* Wire cutters/snippers

## How the matrix works (why we need diodes)

The microcontroller (in this case, the Teensy 2.0) will be setup up via the firmware to send a logical 1 to the columns, one at a time, and read from the rows, all at once - this process is called matrix scanning. The matrix is a bunch of open switches that, by default, don't allow any current to pass through - the firmware will read this as no keys being pressed. As soon as you press one key down, the logical 1 that was coming from the column the keyswitch is attached to gets passed through the switch and to the corresponding row - check out the following 2x2 example:

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

We can now see that `row0` has an `x`, so has the value of 1. As a whole, the data the firmware receives when `key0` is pressed is

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

## The actual hand-wiring

### Getting things in place

When starting this, you should have all of your stabilisers and keyswitches already installed (and optionally keycaps). If you're using a Cherry-type stabiliser (plate-mounted only, obviously), you'll need to install that before your keyswitches. If you're using Costar ones, you can installed them afterwards.

To make things easier on yourself, make sure all of the keyswitches are oriented the same way (if they can be - not all layouts support this). Despite this, it's important to remember that the contacts on the keyswitches are completely symmetrical. We'll be using the keyswitch's left side contact for wiring the rows, and the right side one for wiring the columns.

Get your soldering iron heated-up and collect the rest of the materials from the part list at the beginning of the guide. Place your keyboard so that the bottoms of the keyswitches are accessible - it may be a good idea to place it on a cloth to protect your keyswitches/keycaps.

Before continuing, plan out where you're going to place your Teensy. If you're working with a board that has a large (6.25u) spacebar, it may be a good idea to place it in-between switches against the plate. Otherwise, you may want to trim some of the leads on the keyswitches where you plan on putting it - this will make it a little harder to solder the wire/diodes, but give you more room to place the Teensy.

### Preparing the diodes

It's a little easier to solder the diodes in place if you bend them at a 90º angle immediately after the black line - this will help to make sure you put them on the right way (direction matters), and in the correct position. The diodes will look like this when bent (with longer leads):

       ┌─────┬─┐
    ───┤     │ ├─┐
       └─────┴─┘ │
                 │

We'll be using the long lead at the bent end to connect it to the elbow (bent part) of the next diode, creating the row.

### Soldering the diodes

Starting at the top-left switch, place the diode (with tweezers if you have them) on the switch so that the diode itself is vertically aligned, and the black line is facing toward you. The straight end of the diode should be touching the left contact on the switch, and the bent end should be facing to the right and resting on the switch there, like this:

     │o
    ┌┴┐         o
    │ │    O
    ├─┤      
    └┬┘
     └─────────────

Letting the diode rest, grab your solder, and touch both it and the soldering iron to the left contact at the same time - the rosin in the solder should make it easy for the solder to flow over both the diode and the keyswitch contact. The diode may move a little, and if it does, carefully position it back it place by grabbing the bent end of the diode - the other end will become hot very quickly. If you find that it's moving too much, using needle-nose pliers of some sort may help to keep the diode still when soldering.

The smoke that the rosin releases is harmful, so be careful not to breath it or get it in your eyes/face.

After soldering things in place, it may be helpful to blow on the joint to push the smoke away from your face, and cool the solder quicker. You should see the solder develop a matte (not shiney) surface as it solidifies. Keep in mind that it will still be very hot afterwards, and will take a couple minutes to be cool to touch. Blow on it will accelerate this process.

When the first diode is complete, the next one will need to be soldered to both the keyswitch, and the previous diode at the new elbow. That will look something like this:

     │o               │o
    ┌┴┐         o    ┌┴┐         o
    │ │    O         │ │    O
    ├─┤              ├─┤      
    └┬┘              └┬┘
     └────────────────┴─────────────

After completing a row, use the wire cutters to trim the excess wire from the tops of the diodes, and from the right side on the final switch. This process will need to completed for each row you have.

When all of the diodes are completely soldered, it's a good idea to quickly inspect each one to ensure that your solder joints are solid and sturdy - repairing things after this is possible, but more difficult.

### Soldering the columns

You'll have some options in the next process - it's a good idea to insulate the column wires (since the diodes aren't), but if you're careful enough, you can use exposed wires for the columns - it's not recommended, though. If you're using single-cored wire, stripping the plastic off of the whole wire and feeding it back on is probably the best option, but can be difficult depending on the size and materials. You'll want to leave parts of the wire exposed where you're going to be solder it onto the keyswitch.

If you're using stranded wire, it's probably easiest to just use a lot of small wires to connect each keyswitch along the column. It's possible to use one and melt through the insulation, but this isn't recommended, will produce even more harmful fumes, and can ruin your soldering iron.

Before beginning to solder, it helps to have your wire pre-bent (if using single-cored), or at least have an idea of how you're going to route the column (especially if you're making a staggered board). Where you go in particular doesn't matter too much, as we'll be basing our keymap definitions on how it was wired - just make sure every key in a particular row is in a unique column, and that they're in order from left to right.

If you're not using any insulation, you can try to keep the column wires elevated, and solder them near the tips of the keyswitch contacts - if the wires are sturdy enough, they won't short out to the row wiring an diodes.

### Wiring things to the Teensy

Now that the matrix itself is complete, it's time to connect what you've done to the Teensy. You'll be needing the number of pins equal to your number of columns + your number of rows. There are some pins on the Teensy that are special, like D6 (the LED on the chip), or some of the UART, SPI, I2C, or PWM channels, but only avoid those if you're planning something in addition to a keyboard. If you're unsure about wanting to add something later, you should have enough pins in total to avoid a couple.

The pins you'll absolutely have to avoid are: GND, VCC, AREF, and RST - all the others are usable and accessible in the firmware.

Place the Teensy where you plan to put it - you'll have to cut wires to length in the next step, and you'll want to make sure they reach.

Starting with the first column on the right side, measure out how much wire you'll need to connect it to the first pin on the Teensy - it helps to pick a side that you'll be able to work down, to keep the wires from overlapping too much. It may help to leave a little bit of slack so things aren't too tight. Cut the piece of wire, and solder it to the Teensy, and then the column - you can solder it anywhere along the column, but it may be easiest at the keyswitch. Just be sure the wire doesn't separate from the keyswitch when soldering.

As you move from column to column, it'll be helpful to write the locations of the pins down. We'll use this data to setup the matrix in the future.

When you're done with the columns, start with the rows in the same process, from top to bottom, and write them all down. Again, you can solder anywhere along the row, as long as it's after the diode - soldering before the diode (on the keyswitch side) will cause that row not to work.

As you move along, be sure that the Teensy is staying in place - recutting and soldering the wires is a pain!

### Getting some basic firmware set-up

From here, you should have a working keyboard with the correct firmware. Before we attach the Teensy permanently to the keyboard, let's quickly get some firmware loaded onto the Teensy so we can test each keyswitch.

To start out, download [the firmware](https://github.com/qmk/qmk_firmware/) - we'll be using my (Jack's) fork of TMK called QMK/Quantum. We'll be doing a lot from the Terminal/command prompt, so get that open, along with a decent text editor like [Sublime Text](http://www.sublimetext.com/).

The first thing we're going to do is create a new project using the script in the root directory of the firmware. In your terminal, run this command with `<project_name>` replaced by the name of your project - it'll need to be different from any other project in the `keyboards/` folder:

    util/new_project.sh <project_name>

You'll want to navigate to the `keyboards/<project_name>/` folder by typing, like the print-out from the script specifies:

    cd keyboards/<project_name>

#### config.h

The first thing you're going to want to modify is the `config.h` file. Find `MATRIX_ROWS` and `MATRIX_COLS` and change their definitions to match the dimensions of your keyboard's matrix.

Farther down are `MATRIX_ROW_PINS` and `MATRIX_COL_PINS`. Change their definitions to match how you wired up your matrix (looking from the top of the keyboard, the rows run top-to-bottom and the columns run left-to-right). Likewise, change the definition of `UNUSED_PINS` to match the pins you did not use (this will save power).

#### \<project_name\>.h

The next file you'll want to look at is `<project_name>.h`. You're going to want to rewrite the `KEYMAP` definition - the format and syntax here is extremely important, so pay attention to how things are setup. The first half of the definition are considered the arguments - this is the format that you'll be following in your keymap later on, so you'll want to have as many k*xy* variables here as you do keys. The second half is the part that the firmware actually looks at, and will contain gaps depending on how you wired your matrix.

We'll dive into how this will work with the following example. Say we have a keyboard like this:

    ┌───┬───┬───┐
    │   │   │   │
    ├───┴─┬─┴───┤
    │     │     │
    └─────┴─────┘

This can be described by saying the top row is 3 1u keys, and the bottom row is 2 1.5u keys. The difference between the two rows is important, because the bottom row has an unused column spot (3 v 2). Let's say that this is how we wired the columns:

    ┌───┬───┬───┐
    │ ┋ │ ┋ │ ┋ │
    ├─┋─┴─┬─┴─┋─┤
    │ ┋   │   ┋ │
    └─────┴─────┘

The middle column is unused on the bottom row in this example. Our `KEYMAP` definition would look like this:

    #define KEYMAP( \
        k00, k01, k02, \
          k10,  k11,   \
    ) \
    { \
        { k00, k01,   k02 }, \
        { k10, KC_NO, k11 }, \
    }

Notice how the top half is spaced to resemble our physical layout - this helps us understand which keys are associated with which columns. The bottom half uses the keycode `KC_NO` where there is no keyswitch wired in. It's easiest to keep the bottom half aligned in a grid to help us make sense of how the firmware actually sees the wiring.

Let's say that instead, we wired our keyboard like this (a fair thing to do):

    ┌───┬───┬───┐
    │ ┋ │  ┋│ ┋ │
    ├─┋─┴─┬┋┴───┤
    │ ┋   │┋    │
    └─────┴─────┘

This would require our `KEYMAP` definition to look like this:

    #define KEYMAP( \
        k00, k01, k02, \
          k10,  k11,   \
    ) \
    { \
        { k00, k01, k02   }, \
        { k10, k11, KC_NO }, \
    }

Notice how the `k11` and `KC_NO` switched places to represent the wiring, and the unused final column on the bottom row. Sometimes it'll make more sense to put a keyswitch on a particular column, but in the end, it won't matter, as long as all of them are accounted for. You can use this process to write out the `KEYMAP` for your entire keyboard - be sure to remember that your keyboard is actually backwards when looking at the underside of it.

#### keymaps/default.c

This is the actual keymap for your keyboard, and the main place you'll make changes as you perfect your layout. `default.c` is the file that gets pull by default when typing `make`, but you can make other files as well, and specify them by typing `make KEYMAP=<variant>`, which will pull `keymaps/<variant>.c`.

The basis of a keymap is its layers - by default, layer 0 is active. You can activate other layers, the highest of which will be referenced first. Let's start with our base layer.

Using our previous example, let's say we want to create the following layout:

    ┌───┬───┬───┐
    │ A │ 1 │ H │
    ├───┴─┬─┴───┤
    │ TAB │ SPC │
    └─────┴─────┘

This can be accomplished by using the following `keymaps` definition:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = KEYMAP( /* Base */
      KC_A,  KC_1,  KC_H, \
        KC_TAB,  KC_SPC   \
    ),
    };

Note that the layout of the keycodes is similar to the physical layout of our keyboard - this make it much easier to see what's going on. A lot of the keycodes should be fairly obvious, but for a full list of them, check out [tmk_code/doc/keycode.txt](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/doc/keycode.txt) - there are also a lot of aliases to condense your keymap file.

It's also important to use the `KEYMAP` function we defined earlier - this is what allows the firmware to associate our intended readable keymap with the actual wiring.

#### Compiling your firmware

After you've written out your entire keymap, you're ready to get the firmware compiled and onto your Teensy. Before compiling, you'll need to get your [development environment set-up](build_guide.md) - you can skip the dfu-programmer instructions, but you'll need to download and install the [Teensy Loader](https://www.pjrc.com/teensy/loader.html) to get the firmware on your Teensy.

Once everything is installed, running `make` in the terminal should get you some output, and eventually a `<project_name>.hex` file in that folder. If you're having trouble with this step, see the end of the guide for the trouble-shooting section.

Once you have your `<project_name>.hex` file, open up the Teensy loader application, and click the file icon. From here, navigate to your `QMK/keyboards/<project_name>/` folder, and select the `<project_name>.hex` file. Plug in your keyboard and press the button on the Teensy - you should see the LED on the device turn off once you do. The Teensy Loader app will change a little, and the buttons should be clickable - click the download button (down arrow), and then the reset button (right arrow), and your keyboard should be ready to go!

#### Testing your firmware

Carefully flip your keyboard over, open up a new text document, and try typing - you should get the characters that you put into your keymap. Test each key, and note the ones that aren't working. Here's a quick trouble-shooting guide for non-working keys:

0. Flip the keyboard back over and short the keyswitch's contacts with a piece wire - this will eliminate the possibility of the keyswitch being bad and needing to be replaced.
1. Check the solder points on the keyswitch - these need to be plump and whole. If you touch it with a moderate amount of force and it comes apart, it's not strong enough.
2. Check the solder joints on the diode - if the diode is loose, part of your row may register, while the other may not.
3. Check the solder joints on the columns - if your column wiring is loose, part or all of the column may not work.
4. Check the solder joints on both sides of the wires going to/from the Teensy - the wires need to be fully soldered and connect to both sides.
5. Check the <project_name>.h file for errors and incorrectly placed `KC_NO`s - if you're unsure where they should be, instead duplicate a k*xy* variable.
6. Check to make sure you actually compiled the firmware and flashed the Teensy correctly. Unless you got error messages in the terminal, or a pop-up during flashing, you probably did everything correctly.

If you've done all of these things, keep in mind that sometimes you might have had multiple things affecting the keyswitch, so it doesn't hurt to test the keyswitch by shorting it out at the end.

#### Securing the Teensy, finishing your hardware, getting fancier firmware

Now that you have a working board, it's time to get things in their permanent positions. I've often used liberal amounts of hot glue to secure and insulate things, so if that's your style, start spreading that stuff like butter. Otherwise, double-sided tape is always an elegant solution, and electrical tape is a distant second. Due to the nature of these builds, a lot of this part is up to you and how you planned (or didn't plan) things out.

There are a lot of possibilities inside the firmware - check out the [readme](https://github.com/qmk/qmk_firmware/blob/master/readme.md) for a full feature list, and dive into the different project (Planck, Ergodox EZ, etc) to see how people use all of them. You can always stop by [the OLKB subreddit for help!](http://reddit.com/r/olkb)

## Trouble-shooting compiling

### Windows

#### fork: Resource temporarily unavailable

http://www.avrfreaks.net/forum/windows-81-compilation-error

### Mac

### Linux
