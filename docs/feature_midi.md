# MIDI

## Enabling MIDI

Add the following to the keyboard's rules.mk

```c
MIDI_ENABLE = yes
```

## Using Basic MIDI

Enabling Basic MIDI

Add the following to your keyboard's config.h

```c
#define MIDI_BASIC
```

With basic MIDI you will only be able to send `NOTE_ON` and `NOTE_OFF` Commands to the internal MIDI device, meaning that keycodes like `MI_OCTU` and `MI_OCTD` will not work.

## Advanced MIDI

Enabling Advanced MIDI

Add the following to your keyboard's config.h

```c
#define MIDI_ADVANCED
```

With advanced MIDI you can do things like octave shifts, channel changes, velocity changes, and modulation.

### Sending MIDI Control Codes (MIDI CC)

If you're aiming to emulate the features of something like a Launchpad or other MIDI controller you'll need to access the internal MIDI device directly.

When sending MIDI CC you don't get the advantages of a preimplemented keycode and you will need to implement custom keycodes if you want to use them in your keymap directly using the function `process_record_user`. It is the same process as implementing custom keycodes for macros.

For an overview of that process look at: [Macros](feature_macros.md)

1. First enable MIDI_ADVANCED
2. use an `extern MidiDevice midi_device;` statement to bring the MIDI device into scope.
3. Send a control code with the `midi_send_cc(*midi_device, channel, number, value)`

For reference of all the possible control code numbers see [MIDI Specification](#midi-specification)

#### Example code for using Generic On Off Switches as per MIDI Specification.
```c
#include QMK_KEYBOARD_H

extern MidiDevice midi_device;

/*
MIDI CC codes for generic ON/OFF swiches
80,81,82,83
values off = 0-63
*/

#define OFF 0

/*values on = 64-127*/

#define ON 127

enum custom_keycodes { MIDI_CC80 = SAFE_RANGE, MIDI_CC81, MIDI_CC82, MIDI_CC83 };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MIDI_CC80:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 80, ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 80, OFF);
            }
            return true;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {MIDI_CC80, MIDI_CC81, MIDI_CC82, MIDI_CC83},
        // ...
    },
};

```

### Available MIDI Keycodes

| Keycode                    | Description                                             |
|----------------------------|---------------------------------------------------------|
| MI_ON                      | Turn MIDI on                                            |
| MI_OFF                     | Turn MIDI off                                           |
| MI_TOG                     | Toggle MIDI Enabled                                     |
| MI_C                       | C                                                       |
| MI_Cs                      | C ♯                                                     |
| MI_Db                      | D ♭ == C♯                                               |
| MI_D                       | D                                                       |
| MI_Ds                      | D ♯                                                     |
| MI_Eb                      | E♭ == D ♯                                               |
| MI_E                       | E                                                       |
| MI_F                       | F                                                       |
| MI_Fs                      | F ♯                                                     |
| MI_Gb                      | G ♭                                                     |
| MI_G                       | G                                                       |
| MI_Gs                      | G ♯                                                     |
| MI_Ab                      | A ♭                                                     |
| MI_A                       | A                                                       |
| MI_As                      | A ♯                                                     |
| MI_Bb                      | B ♭                                                     |
| MI_B                       | B                                                       |
| MI_C_1                     | C octave 1                                              |
| MI_Cs_1                    | C ♯ octave 1                                            |
| MI_Db_1                    | D ♭ octave 1                                            |
| MI_D_1                     | D octave 1                                              |
| MI_Ds_1                    | D ♯ octave 1                                            |
| MI_Eb_1                    | E ♭ octave 1                                            |
| MI_E_1                     | E octave 1                                              |
| MI_F_1                     | F octave 1                                              |
| MI_Fs_1                    | F ♯ octave 1                                            |
| MI_Gb_1                    | G ♭ octave 1                                            |
| MI_G_1                     | G octave 1                                              |
| MI_Gs_1                    | G ♯ octave 1                                            |
| MI_Ab_1                    | A ♭ octave 1                                            |
| MI_A_1                     | A octave 1                                              |
| MI_As_1                    | A ♯ octave 1                                            |
| MI_Bb_1                    | B ♭ octave 1                                            |
| MI_B_1                     | B octave 1                                              |
| MI_C_2                     | C octave 2                                              |
| MI_Cs_2                    | C ♯ octave 2                                            |
| MI_Db_2                    | D ♭ octave 2                                            |
| MI_D_2                     | D octave 2                                              |
| MI_Ds_2                    | D ♯ octave 2                                            |
| MI_Eb_2                    | E ♭ octave 2                                            |
| MI_E_2                     | E octave 2                                              |
| MI_F_2                     | F octave 2                                              |
| MI_Fs_2                    | F ♯ octave 2                                            |
| MI_Gb_2                    | G ♭ octave 2                                            |
| MI_G_2                     | G octave 2                                              |
| MI_Gs_2                    | G ♯ octave 2                                            |
| MI_Ab_2                    | A ♭ octave 2                                            |
| MI_A_2                     | A octave 2                                              |
| MI_As_2                    | A ♯ octave 2                                            |
| MI_Bb_2                    | B ♭ octave 2                                            |
| MI_B_2                     | B octave 2                                              |
| MI_C_3                     | C octave 3                                              |
| MI_Cs_3                    | C ♯ octave 3                                            |
| MI_Db_3                    | D ♭ octave 3                                            |
| MI_D_3                     | D octave 3                                              |
| MI_Ds_3                    | D ♯ octave 3                                            |
| MI_Eb_3                    | E ♭ octave 3                                            |
| MI_E_3                     | E octave 3                                              |
| MI_F_3                     | F octave 3                                              |
| MI_Fs_3                    | F ♯ octave 3                                            |
| MI_Gb_3                    | G ♭ octave 3                                            |
| MI_G_3                     | G octave 3                                              |
| MI_Gs_3                    | G ♯ octave 3                                            |
| MI_Ab_3                    | A ♭ octave 3                                            |
| MI_A_3                     | A octave 3                                              |
| MI_As_3                    | A ♯ octave 3                                            |
| MI_Bb_3                    | B ♭ octave 3                                            |
| MI_B_3                     | B octave 3                                              |
| MI_C_4                     | C octave 4                                              |
| MI_Cs_4                    | C ♯ octave 4                                            |
| MI_Db_4                    | D ♭ octave 4                                            |
| MI_D_4                     | D octave 4                                              |
| MI_Ds_4                    | D ♯ octave 4                                            |
| MI_Eb_4                    | E ♭ octave 4                                            |
| MI_E_4                     | E octave 4                                              |
| MI_F_4                     | F octave 4                                              |
| MI_Fs_4                    | F ♯ octave 4                                            |
| MI_Gb_4                    | G ♭ octave 4                                            |
| MI_G_4                     | G octave 4                                              |
| MI_Gs_4                    | G ♯ octave 4                                            |
| MI_Ab_4                    | A ♭ octave 4                                            |
| MI_A_4                     | A octave 4                                              |
| MI_As_4                    | A ♯ octave 4                                            |
| MI_Bb_4                    | B ♭ octave 4                                            |
| MI_B_4                     | B octave 4                                              |
| MI_C_5                     | C octave 5                                              |
| MI_Cs_5                    | C ♯ octave 5                                            |
| MI_Db_5                    | D ♭ octave 5                                            |
| MI_D_5                     | D octave 5                                              |
| MI_Ds_5                    | D ♯ octave 5                                            |
| MI_Eb_5                    | E ♭ octave 5                                            |
| MI_E_5                     | E octave 5                                              |
| MI_F_5                     | F octave 5                                              |
| MI_Fs_5                    | F ♯ octave 5                                            |
| MI_Gb_5                    | G ♭ octave 5                                            |
| MI_G_5                     | G octave 5                                              |
| MI_Gs_5                    | G ♯ octave 5                                            |
| MI_Ab_5                    | A ♭ octave 5                                            |
| MI_A_5                     | A octave 5                                              |
| MI_As_5                    | A ♯ octave 5                                            |
| MI_Bb_5                    | B ♭ octave 5                                            |
| MI_B_5                     | B octave 5                                              |
| MI_OCT_N2                  | Go to octave -2                                         |
| MI_OCT_N1                  | Go to octave -1                                         |
| MI_OCT_0                   | Go to octave  0                                         |
| MI_OCT_1                   | Go to octave  1                                         |
| MI_OCT_2                   | Go to octave  2                                         |
| MI_OCT_3                   | Go to octave  3                                         |
| MI_OCT_4                   | Go to octave  4                                         |
| MI_OCT_5                   | Go to octave  5                                         |
| MI_OCT_6                   | Go to octave  6                                         |
| MI_OCT_7                   | Go to octave  7                                         |
| MI_OCTD                    | Go down an octave                                       |
| MI_OCTU                    | Go up an octave                                         |
| MI_TRNS_N6                 | Transpose notes down 6 positions                        |
| MI_TRNS_N5                 | Transpose notes down 5 positions                        |
| MI_TRNS_N4                 | Transpose notes down 4 positions                        |
| MI_TRNS_N3                 | Transpose notes down 3 positions                        |
| MI_TRNS_N2                 | Transpose notes down 2 positions                        |
| MI_TRNS_N1                 | Transpose notes down 1 positions                         |
| MI_TRNS_0                  | No transpositions                                        |
| MI_TRNS_1                  | Transpose notes up 1 positions                           |
| MI_TRNS_2                  | Transpose notes up 2 positions                          |
| MI_TRNS_3                  | Transpose notes up 3 positions                          |
| MI_TRNS_4                  | Transpose notes up 4 positions                          |
| MI_TRNS_5                  | Transpose notes up 5 positions                          |
| MI_TRNS_6                  | Transpose notes up 6 positions                          |
| MI_TRNSD                   | Transpose notes down a positions                         |
| MI_TRNSU                   | Transpose notes up a positions                           |
| MI_VEL_0                   | Set Velocity to 0                                       |
| if VIA_ENABLE: MI_VEL_1    | If via is enabled, Velocity 1 is the same as Velocity 0 |
| if no VIA_ENABLE: MI_VEL_1 | Set Velocity to 1                                       |
| MI_VEL_2                   | Set Velocity to 2                                       |
| MI_VEL_3                   | Set Velocity to 3                                       |
| MI_VEL_4                   | Set Velocity to 4                                       |
| MI_VEL_5                   | Set Velocity to 5                                       |
| MI_VEL_6                   | Set Velocity to 6                                       |
| MI_VEL_7                   | Set Velocity to 7                                       |
| MI_VEL_8                   | Set Velocity to 8                                       |
| MI_VEL_9                   | Set Velocity to 9                                       |
| MI_VEL_10                  | Set Velocity to 10                                      |
| MI_VELD                    | Go down one tick of velocity                            |
| MI_VELU                    | Go up one tick of velocity                              |
| MI_CH1                     | Go to channel 1                                         |
| MI_CH2                     | Go to channel 2                                         |
| MI_CH3                     | Go to channel 3                                         |
| MI_CH4                     | Go to channel 4                                         |
| MI_CH5                     | Go to channel 5                                         |
| MI_CH6                     | Go to channel 6                                         |
| MI_CH7                     | Go to channel 7                                         |
| MI_CH8                     | Go to channel 8                                         |
| MI_CH9                     | Go to channel 9                                         |
| MI_CH10                    | Go to channel 10                                        |
| MI_CH11                    | Go to channel 11                                        |
| MI_CH12                    | Go to channel 12                                        |
| MI_CH13                    | Go to channel 13                                        |
| MI_CH14                    | Go to channel 14                                        |
| MI_CH15                    | Go to channel 15                                        |
| MI_CH16                    | Go to channel 16                                        |
| MI_CHD                     | Go to channel 17                                        |
| MI_CHU                     | Go to channel 18                                        |
| MI_ALLOFF                  | Turn off all notes                                      |
| MI_SUS                     | Sustain                                                 |
| MI_PORT                    | Portmento                                               |
| MI_SOST                    | Sostenuto                                               |
| MI_SOFT                    | Soft Pedal                                              |
| MI_LEG                     | Legato                                                  |
| MI_MOD                     | Modulation                                              |
| MI_MODSD                   | Decrease Modulation Speed                               |
| MI_MODSU                   | Increase Modulation Speed                               |
| MI_BENDD                   | Bend pitch down                                         |
| MI_BENDU                   | Bend pitch up                                           |

### Background

QMK MIDI is based on TMK MIDI which in turn is based on `avr-midi`

QMK MIDI is a subset implementation of the MIDI 1.0 specification. 

### References

#### QMK Internals 
 
 * [Internals/MIDI Device Setup Process](internals_midi_device_setup_process.md)
 * [Internals/MIDI Device](internals_midi_device.md)
 * [Internals/MIDI Util](internals_midi_util.md)
 
 
#### QMK C Files

 * `quantum/process_keycode/process_midi.c`
 * `quantum/quantum_keycodes.h`
 * `tmk_core/protocol/midi.h`
 * `tmk_core/protocol/midi.c`
 * `tmk_core/protocol/qmk_midi.c`
 * `tmk_core/protocol/midi_device.h`

#### MIDI Specification

 * [MIDI.org](https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message)
 * [CMU MIDI Programmer's Reference](https://www.cs.cmu.edu/~music/cmsip/readings/MIDI%20tutorial%20for%20programmers.html)
