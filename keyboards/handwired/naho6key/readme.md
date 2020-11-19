# naholyr’s 6-key: training with QMK and Pro-Micro

Disclaimer: I'm an absolute noob in electronics, and just discovered QMK, so I had to dive in and learn. This is the project I used to learn, I hope it could help others to understand the internals more easily.

The main goal was to train with QMK, and validate a few things:

- Doing fun things with layer switching policies
- Send emojis and standard Unicode characters
- Try special keycodes
- Try controlling the mouse
- Play with an RGB LED

## The Keymap

(click on the image to open Keyboard Layout Editor)

[![](https://i.imgur.com/FtkCXfz.png)](http://www.keyboard-layout-editor.com/##@@_c=%23fffbcf&f:1&fa@:0&:0&:2%3B%3B&=copy%0A%E2%86%90%0A%F0%9F%A4%A6%0A%0A%F0%9F%94%89%0A%0A%E2%86%90&_c=%239bc79b%3B&=emoji%20%E2%87%A8%0Aclick%0A%0A%0A%F0%9F%94%87%0A%0Ashift&_c=%23fffbcf%3B&=cut%0A%E2%86%92%0A%F0%9F%A4%B7%0A%0A%F0%9F%94%8A%0A%0A%E2%86%92&_x:0.75&c=%23ffb5b5%3B&=paste%0A%E2%86%93%0A%F0%9F%91%8D%0A%0A%E2%8F%AF%0A%0A%E2%86%93&_c=%239e9e9e%3B&=nav%20%E2%87%A9%0Amedia%20%E2%87%A9%0A%CF%80%0A%0Abase%20%E2%86%BA%0A%0Amouse%20%E2%87%A9&_c=%23ffb5b5%3B&=calc%0A%E2%86%91%0A%F0%9F%A4%A3%0A%0Ar.%20click%0A%0A%E2%86%91)

I've worked with 2 "rows" (left/right) of 3 columns, each "row" having generally 2 "main" buttons surrounding a middle "action" button.

We have 5 layers, each one its own color:

- Base (white) = copy/cut/paste/calculator (why not?)
    - left action = activate emoji (as modifier)
    - right action = activate keyboard nav (hold for temporary, tap to toggle)
- Emoji (pink) = facepalm/shrug/thumbsup/rofl
    - left action unavailable
    - right action = Pi (why not?)
- Keyboard nav (blue) = left/right/down/up
    - left action = shift
    - right action = activate mouse nav (hold for temporary, tap to toggle)
- Mouse nav (red) = left/right/down/up
    - left action = left click
    - right action = active media (hold) or back to base (tap)
- Media (green) = vol-/vol+/pause/right click
    - left action = mute
    - right action unavailable
    
With this keymap you can hold right action + left action (= keyboard nav + shift), move cursor (selecting text as shift is pressed), then release and press copy/cut then paste, this sort of tremendously useful and difficult things to do with a normal keyboard (irony intended).

## The wiring

Here is the circuit schematic (quite ugly, and probably wrong as I didn't have the "RGB LED" component, but you get it):

![](https://i.imgur.com/4kUTRUX.png)

LED is **obviously not wired without resistors** (never do this!), I actually used different resistors on each of its branch to mitigate brightness and have balanced colors:

- R = 1 kΩ
- G = 10 kΩ
- B = 5 kΩ

Here is a (weirdly cabled) real-life prototype on a breadboard:

![](https://i.imgur.com/qpYPpJ4.jpg)

The real-life picture + the circuit schematic should be enough to get it all.

## How to make it yourself

### Hardware

- Mandatory components:
  - A Pro Micro controller (if you use another one, translating pins should be enough)
  - 6 buttons (the actual keys)
  - 6 diodes (I used 1N4148)
  - something to make it all hold, like a soldering iron (for the controller), breadboard, wires…
  - A computer and a micro-USB cable **with data** (don't laugh, many of the micro-USB cables you'll find in your drawers are charge-only, and you may ‑ as I did ‑ believe your controller is dead and lose HOURS)
- Optional components:
  - 1 button (the small reset button)
  - A wired RGB LED (the one with 4 legs)
  - 3 resistors (I used 1K, 5K, and 10K)

Wire it all as described above 😁 then flash the beast (see below)!

### Software

- Install QMK: see the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
- Clone this repository
- Plug your freshly built incredibly powerful macro pad
- Build and flash the firmware

```
make handwired/naho6key:default:flash
```

After building the firmware, it should be waiting with a message like *Detecting USB port, reset your controller now.......*, just press the "reset" button (or short the "GND" and "RST" pins). If it's not detecting your controller, unplug it, hold the "reset" button while plugging it again, and then release the reset button.

For more information, see the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
