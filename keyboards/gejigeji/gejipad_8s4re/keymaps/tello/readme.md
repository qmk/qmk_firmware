# Tello keymap for Gejipad 8S4RE

Maps the 8 switches and 4 rotary encoders to [DJI Tello SDK](https://www.ryzerobotics.com/tello) text commands, for use with a Tello SDK bridge running on the host computer.

## Keys

| Switch | Function |
| --- | --- |
| SW6 | `land` |
| SW7 | `right 100` |
| SW8 | `right 50` |
| SW9 | `flip r` |
| SW10 | `flip l` |
| SW11 | `left 50` |
| SW12 | `left 100` |
| SW13 | `takeoff` |

## Encoders

| Encoder | CW | CCW |
| --- | --- | --- |
| 1 | `up 20` | `down 20` |
| 2 | `forward 20` | `back 20` |
| 3 | `cw 5` | `ccw 5` |
| 4 | `right 20` | `left 20` |

Build/flash with:

    make gejigeji/gejipad_8s4re:tello
    make gejigeji/gejipad_8s4re:tello:flash
