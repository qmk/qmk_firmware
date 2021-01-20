# Sequencer

Since QMK has experimental support for MIDI, you can now turn your keyboard into a [step sequencer](https://en.wikipedia.org/wiki/Music_sequencer#Step_sequencers)!

!> **IMPORTANT:** This feature is highly experimental, it has only been tested on a Planck EZ so far. Also, the scope will be limited to support the drum machine use-case to start with.

## Enable the step sequencer

Add the following line to your `rules.mk`:

```make
SEQUENCER_ENABLE = yes
```

By default the sequencer has 16 steps, but you can override this setting in your `config.h`:

```c
#define SEQUENCER_STEPS 32
```

## Tracks

You can program up to 8 independent tracks with the step sequencer. Select the tracks you want to edit, enable or disable some steps, and start the sequence!

## Resolutions

While the tempo defines the absolute speed at which the sequencer goes through the steps, the resolution defines the granularity of these steps (from coarser to finer).

|Resolution   |Description            |
|----------   |-----------            |
|`SQ_RES_2`   |Every other beat       |
|`SQ_RES_2T`  |Every 1.5 beats        |
|`SQ_RES_4`   |Every beat             |
|`SQ_RES_4T`  |Three times per 2 beats|
|`SQ_RES_8`   |Twice per beat         |
|`SQ_RES_8T`  |Three times per beat   |
|`SQ_RES_16`  |Four times per beat    |
|`SQ_RES_16T` |Six times per beat     |
|`SQ_RES_32`  |Eight times per beat   |

## Keycodes

|Keycode  |Description                                        |
|-------  |-----------                                        |
|`SQ_ON`  |Start the step sequencer                           |
|`SQ_OFF` |Stop the step sequencer                            |
|`SQ_TOG` |Toggle the step sequencer playback                 |
|`SQ_SALL`|Enable all the steps                               |
|`SQ_SCLR`|Disable all the steps                              |
|`SQ_S(n)`|Toggle the step `n`                                |
|`SQ_TMPD`|Decrease the tempo                                 |
|`SQ_TMPU`|Increase the tempo                                 |
|`SQ_R(n)`|Set the resolution to n                            |
|`SQ_RESD`|Change to the slower resolution                    |
|`SQ_RESU`|Change to the faster resolution                    |
|`SQ_T(n)`|Set `n` as the only active track or deactivate all |

## Functions

|Function                                                             |Description                                            |
|--------                                                             |-----------                                            |
|`bool is_sequencer_on(void);`                                        |Return whether the sequencer is playing                |
|`void sequencer_toggle(void);`                                       |Toggle the step sequencer playback                     |
|`void sequencer_on(void);`                                           |Start the step sequencer                               |
|`void sequencer_off(void);`                                          |Stop the step sequencer                                |
|`bool is_sequencer_step_on(uint8_t step);`                           |Return whether the step is currently enabled           |
|`void sequencer_set_step(uint8_t step, bool value);`                 |Enable or disable the step                             |
|`void sequencer_set_step_on();`                                      |Enable the step                                        |
|`void sequencer_set_step_off();`                                     |Disable the step                                       |
|`void sequencer_toggle_step(uint8_t step);`                          |Toggle the step                                        |
|`void sequencer_set_all_steps(bool value);`                          |Enable or disable all the steps                        |
|`void sequencer_set_all_steps_on();`                                 |Enable all the steps                                   |
|`void sequencer_set_all_steps_off();`                                |Disable all the steps                                  |
|`uint8_t sequencer_get_tempo(void);`                                 |Return the current tempo                               |
|`void sequencer_set_tempo(uint8_t tempo);`                           |Set the tempo to `tempo` (between 1 and 255)           |
|`void sequencer_increase_tempo(void);`                               |Increase the tempo                                     |
|`void sequencer_decrease_tempo(void);`                               |Decrease the tempo                                     |
|`sequencer_resolution_t sequencer_get_resolution(void);`             |Return the current resolution                          |
|`void sequencer_set_resolution(sequencer_resolution_t resolution);`  |Set the resolution to `resolution`                     |
|`void sequencer_increase_resolution(void);`                          |Change to the faster resolution                        |
|`void sequencer_decrease_resolution(void);`                          |Change to the slower resolution                        |
|`bool is_sequencer_track_active(uint8_t track);`                     |Return whether the track is active                     |
|`void sequencer_set_track_activation(uint8_t track, bool value);`    |Activate or deactivate the `track`                     |
|`void sequencer_toggle_track_activation(uint8_t track);`             |Toggle the `track`                                     |
|`void sequencer_activate_track(uint8_t track);`                      |Activate the `track`                                   |
|`void sequencer_deactivate_track(uint8_t track);`                    |Deactivate the `track`                                 |
|`void sequencer_toggle_single_active_track(uint8_t track);`          |Set `track` as the only active track or deactivate all |
