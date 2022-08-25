# Tractyl Manuform (3x6) variant
![Working final product](https://i.redd.it/15mq7kw29e691.jpg)

- [Read more here.](https://blog.practicaltech.ca/2022/06/learning-through-failure-keyboard.html)
- [Very extended build log here.](https://docs.google.com/document/d/1714zAB5GvLr3M8TnRpMvAdutThKMioJDGraUgG2VCB4/edit?usp=sharing)

## Community-generated
It takes a village.  Without this list, this would not have happened.
- QMK software folks
- ZSA.io/moonlander
- Drashna
- [Quentin](https://bastardkb.com/)
- Dasky and the QMK Discord crew
- /r/ergomechkeyboards
- Everyone who took the time to post build logs
- cardiactuna, for taking the time to answer my questions
- My extremely supportive wife

## Features
- 3x6 layout, but is effectively 5x6 when it comes to keymaps/rgb - 57 keys total (27L, 30R)
- 34mm trackball (*Logitech ergo mx & Kensington vertical trackball use this*) accessible from a home row position
- Modular chassis that enables more efficient full-lifecycle printing and facilitates troubleshooting
- Uses two Elite-C micro-controllers (*micro-controllers are also referred to in code/comments as MCUs*)
- Exposed wiring and circuit boards, to maximizes the janky prototype feel
- [PMW3360 Optical Sensor](https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/)
- Designed for Moonlander keycaps, including the 'piano keys'
- Per-key-RGB that can also change with layers
- Thumb clusters with lots of keys
- Dedicated arrow cluster
- Hotswap sockets - bring your own switches, mix and match, avoid rewiring catastrophes
- Currently have to plug USB-C cable into the trackball side; uses a TRRS interconnect cable
- Reset switches underneath in difficult to access areas, ensuring maximum chances of breaking something
- Uses 97% of flash space (*room to improve...but not much room for much else*)

## Code
I started by copying Drashna's userspace and the tractyl_manuform keyboard, and by the end stripped out everything I didn't need/understand.  See my userspace for more code.

### Build environment
Be sure to follow the QMK docs on getting your build environment working.

**I have included a simple build script that assumes you've already done this.**

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


### Building and flashing using my script
There are certainly better ways to do this, but it works for me.

```bash
# from the userspace folder...

# this flashes both halves, one at a time, starting with the right
# so ensure the usb cable is plugged into the right half first!
./build.sh flash

# if you only want to flash one side
./build.sh right
# or...
./build.sh left

# if you only want to build...
./build.sh build
```
