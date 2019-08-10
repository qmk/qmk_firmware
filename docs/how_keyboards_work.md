# How Keys Are Registered, and Interpreted by Computers

In this file, you can will learn the concepts of how keyboards work over USB,
and you'll be able to better understand what you can expect from changing your
firmware directly.

## Schematic View

Whenever you type on 1 particular key, here is the chain of actions taking
place:

``` text
+------+         +-----+       +----------+      +----------+     +----+
| User |-------->| Key |------>| Firmware |----->| USB wire |---->| OS |
+------+         +-----+       +----------+      +----------+     +----+
```

This scheme is a very simple view of what's going on, and more details follow
in the next sections.

## 1. You Press a Key

Whenever you press a key, the firmware of your keyboard can register this event.
It can register when the key is pressed, held and released.

This usually happens with a periodic scan of key presses. This speed often is limited by the mechanical key response time, the protocol to transfer those key presses (here USB HID), and by the software it is used in.

## 2. What the Firmware Sends

The [HID specification](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) tells what a keyboard can actually send through USB to have a chance to be properly recognised. This includes a pre-defined list of scancodes which are simple numbers from `0x00` to `0xE7`. The firmware assigns a scancode to each key of the keyboard.

The firmware does not send actual letters or characters, but only scancodes.
Thus, by modifying the firmware, you can only modify what scancode is sent over
USB for a given key.

## 3. What the Operating System Does

Once the keycode reaches the operating system, a piece of software has to have
it match an actual character thanks to a keyboard layout. For example, if your
layout is set to QWERTY, a sample of the matching table is as follows:

| keycode | character |
|---------|-----------|
| 0x04 | a/A |
| 0x05 | b/B |
| 0x06 | c/C |
| ... | ... |
| 0x1C | y/Y |
| 0x1D | z/Z |
| ... | ... |

## Back to the Firmware

As the layout is generally fixed (unless you create your own), the firmware can actually call a keycode by its layout name directly to ease things for you. This is exactly what is done here with `KC_A` actually representing `0x04` in QWERTY. The full list can be found in [keycodes](keycodes.md).

## List of Characters You Can Send

Putting aside shortcuts, having a limited set of keycodes mapped to a limited layout means that **the list of characters you can assign to a given key are only the ones present in the layout**.

For example, this means that if you have a QWERTY US layout, and you want to assign one key to produce `€` (euro currency symbol), you are unable to do so, because the QWERTY US layout does not have such mapping. You could fix that by using a QWERTY UK layout, or a QWERTY US International.

You may wonder why a keyboard layout containing all of Unicode is not devised then? The limited number of keycodes available through USB simply disallows such a thing.

## How to (Maybe) Enter Unicode Characters

You can have the firmware send *sequences of keys* to use the [software Unicode Input Method](https://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_input) of the target operating system, thus effectively entering characters independently of the layout defined in the OS.

Yet, it does come with multiple disadvantages:

 - Tied to a specific OS at a time (need recompilation when changing OS);
 - Within a given OS, does not work in all software;
 - Limited to a subset of Unicode on some systems.
