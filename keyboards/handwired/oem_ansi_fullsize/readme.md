# oem_ansi_fullsize

![oem_ansi_fullsize](https://imgur.com/a/Tw7dwK4)
This is a basic layout for a full-sized ANSI board. It should be compatible with any 100% full-sized layout, for example [RobotDoctor's MECH-104](https://www.thingiverse.com/thing:4205065).

* Keyboard Maintainer: [Cian Johnston](https://github.com/johnstcn)
* Hardware Supported: Teensy®++ 2.0 as it has enough pins for the matrix.
* Hardware Availability: [pjrc.com](https://www.pjrc.com/store/teensypp.html)

The pin layout I used is shown below. Change it as you wish, but be sure to avoid pin D6!

```
                   ┌──────┐
              ┌────┴──────┴────┐
          +5V │o              o│ GND
    CL <== B6 │o              o│ B7 ==> CE
    CK <== B5 │o              o│ D0 ==> CD
    CJ <== B4 │o              o│ D1 ==> CC
    CI <== B3 │o              o│ D2 ==> CB
    CH <== B2 │o              o│ D3 ==> CA
    CG <== B1 │o              o│ D4 ==> C9
    CF <== B0 │o              o│ D5 ==> C8
           E7 │o              o│ D6 ==> NOPE
    C7 <== E6 │o              o│ D7 ==> C6
          GND │o              o│ E0 ==> C5
          RST │o              o│ E1 ==> C4
    R5 <== F0 │o              o│ C0 ==> C3
    R4 <== F1 │o  A0 o  o A4  o│ C1 ==> C2
    R3 <== F2 │o  A1 o  o A5  o│ C2 ==> C1
    R2 <== F3 │o  A2 o  o A6  o│ C3 ==> C0
    R1 <== F4 │o  A3 o  o A7  o│ C4
    R0 <== F5 │o              o│ C5
           F6 │o              o│ C6
           F7 │o  o   o   o   o│ C7
              └────────────────┘
                  R   G   +
                  S   N   5
                  T   D   V
```

Make example for this keyboard (after setting up your build environment):

    make handwired/oem_ansi_fullsize:default

Flashing example for this keyboard:

    make handwired/oem_ansi_fullsize:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
