# Sequencer

Since QMK has experimental support for MIDI, you can now turn your keyboard into a [step sequencer](https://en.wikipedia.org/wiki/Music_sequencer#Step_sequencers)!

!> **IMPORTANT:** This feature is highly experimental, it has only been tested on a Planck EZ so far. Also, the scope will be limited to support the drum machine use-case to start with.

## Enable the step sequencer

Add the following line to your `rules.mk`:

```make
SEQUENCER_ENABLE = yes
```

## Keycodes

|Keycode  |Description                        |
|-------  |-----------                        |
|`SQ_ON`  |Start the step sequencer           |
|`SQ_OFF` |Stop the step sequencer            |
|`SQ_TOG` |Toggle the step sequencer playback |

## Functions

|Function                       |Description                              |
|--------                       |-----------                              |
|`bool is_sequencer_on(void);`  |Return whether the sequencer is playing  |
|`void sequencer_toggle(void);` |Toggle the step sequencer playback       |
|`void sequencer_on(void);`     |Start the step sequencer                 |
|`void sequencer_off(void);`    |Stop the step sequencer                  |
