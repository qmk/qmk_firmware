# D48

![Proton C based handwired 40% keyboard](https://i.imgur.com/2wCYuno.jpg)

A Proton C based handwired 48 key keyboard with 2 rotary encoders, I2C OLED, WS2812 strip, buzzer & clock!

- Keyboard Maintainer: Andrew Dunai
- Hardware Supported: Proton C handwired

Make example for this keyboard (after setting up your build environment):

    make handwired/d48:default:dfu-util

## Details

- Proton C based handwired keyboard
- 2x custom 1.25mm stainless steel plates
- Kailh Choc White (clicky)
- 2x rotary encoders
- 0.91" 128x32 I<sup>2</sup>C OLED
- Small buzzer mounted inside (still waiting for the AST1109MLTRQ boys)
- WS2812 strip (14 LEDs)
- DS1307 I<sup>2</sup>C module real-time clock

Build process: [album](https://imgur.com/gallery/zZZGdDw)

## Pinout

![D48 pinout](https://imgur.com/QoStCvD.jpg)

## Challenges

I'm very happy with the result, but at some point Proton C was driving me nuts.

I did a lot of trial and error during assembly & programming.
There were a lot of *yet* undocumented caveats,
so I'll outline them here so that you guys can avoid the same issues I had.

## Matrix & encoders

Although this is a 48-key board with a 12-col & 4-row matrix, I've decided to add an extra row above the first one
to make my matrix 12x5 and wire encoders' push buttons as 2 extra keys, thus making it a total of 50 (12x4 + 2 encoders).
I used 2 columns (9 & 12) for those buttons.

So, a first row actually has 2 buttons on columns 9 & 12 (because encoders are located near those columns).
Encoders' push buttons are also configured via QMK's keymap.

Check out the `d48.h` & `config.h` for pins used & keymap macro definition.

## I<sup>2</sup>C/OLED

Most of the stuff worked out of the box, except me choosing the right pins for my OLED.

On the Proton C pinout, there are 3 labels for I<sup>2</sup>C and for some reason
there are 2 pairs of SDA/SCL for I<sup>2</sup>C<sup>1</sup> channel: `B8`/`B9` (rear left side) and `B6`/`B7` (rear right side).
I'm not sure if this is a mistake or if I was doing something wrong. So initially I picked `B8`/`B9`
which were not working. When I switched to B6/B7, things worked like a charm.
Later I used B9 for matrix row. No issues so far.

Oh, and by the way, while using `B8`/`B9`, keyboard was sometimes *swallowing* quick keypresses.
I believe this was due to I(2)C timeouts (because incorrect pins were used for OLED).

## Buzzer

It turns out once you switch on `AUDIO_ENABLE`, you cannot use A4 & A5 because they interfere with the buzzer.
My guess is that buzzer uses DAC channels (not sure why both).

I couldn't find this in documentation. Honestly, Proton C has almost zero documentation and this was
the biggest challenge. Anyway, apart from almost going crazy from those challenges, I really liked it!

## RGB

I used pin `A15` for my WS28128 RGB strip.

## D1307 real-time clock

Connecting DS1307 RTC was a piece of cake: same I<sup>2</sup> pins as OLED (SDA/SCL), GND to GND and power to Proton C VUSB pin (5v).

## Other issues

- `B5` could not be used for matrix.
- `TAP_CODE_DELAY` had to be increased to 10 to fix `tap_code(KC_VOLU/KC_VOLD)` calls being swallowed in encoder callback.
- Be extremely attentive about the pinout: keep in mind that **the official Proton C pinout displays the rear of the board, not the front.** Being used to front pinouts, I ended up soldering entire matrix to the wrong side, so I had to desolder every wire and connect it to the opposite side.

## Conclusion

I had a lot of fun. The layout was inspired by the Planck THK. Feel free to ask any questions!
