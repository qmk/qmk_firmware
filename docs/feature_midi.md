
# MIDI

## Enabling MIDI

Add the following to the keyboard's rules.mk

```c
MIDI_ENABLE = yes
```

## Using Basic MIDI

Enabling Basic MIDI only

Add the following to your keyboard's config.h

```c
#define MIDI_BASIC
```

With basic MIDI you will only be able to send `NOTE_ON` and `NOTE_OFF` Commands to the internal MIDI device, meaning that keycodes like `MI_OCTU` and `MI_OCTD` won't work.

## Advanced MIDI

Enabling Advanced MIDI

Add the following to your keyboard's config.h

```c
#define MIDI_ADVANCED
```

With advanced MIDI you can do things like octave shifts, channel changes, velocity changes, and modulation.

### Sending MIDI Control Codes (MIDI CC)

If you're aiming to emulate the features of something like a Launchpad or other MIDI controller you'll need to access the internal MIDI device directly.

It's best to follow a refernce because when sending MIDI CC you don't get the advantages of a keycode and you will need to impliment a `process_record_user` and the custom keycodes for that. It's the same process as implmenting custom key behavior or macros.

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

### Avaiable MIDI Keycodes

| Keycode                    | MIDI Code | Description                                             |
|----------------------------|-----------|---------------------------------------------------------|
| MI_ON                      | 5C2C      | Turn MIDI on                                            |
| MI_OFF                     | 5C2D      | Turn MIDI off                                           |
| MI_TOG                     | 5C2E      | Toggle MIDI Enabled                                     |
| MI_C                       | 5C2F      | C                                                       |
| MI_Cs                      | 5C30      | C ♯                                                     |
| MI_Db                      | MI_Cs     | D ♭ == C♯                                               |
| MI_D                       | 5C31      | D                                                       |
| MI_Ds                      | 5C32      | D ♯                                                     |
| MI_Eb                      | MI_Ds     | E♭ == D ♯                                               |
| MI_E                       | 5C33      | E                                                       |
| MI_F                       | 5C34      | F                                                       |
| MI_Fs                      | 5C35      | F ♯                                                     |
| MI_Gb                      | MI_Fs     | G ♭                                                     |
| MI_G                       | 5C36      | G                                                       |
| MI_Gs                      | 5C37      | G ♯                                                     |
| MI_Ab                      | MI_Gs     | A ♭                                                     |
| MI_A                       | 5C38      | A                                                       |
| MI_As                      | 5C39      | A ♯                                                     |
| MI_Bb                      | MI_As     | B ♭                                                     |
| MI_B                       | 5C3A      | B                                                       |
| MI_C_1                     | 5C3B      | C octave 1                                              |
| MI_Cs_1                    | 5C3C      | C ♯ octave 1                                            |
| MI_Db_1                    | MI_Cs_1   | D ♭ octave 1                                            |
| MI_D_1                     | 5C3D      | D octave 1                                              |
| MI_Ds_1                    | 5C3E      | D ♯ octave 1                                            |
| MI_Eb_1                    | MI_Ds_1   | E ♭ octave 1                                            |
| MI_E_1                     | 5C3F      | E octave 1                                              |
| MI_F_1                     | 5C40      | F octave 1                                              |
| MI_Fs_1                    | 5C41      | F ♯ octave 1                                            |
| MI_Gb_1                    | MI_Fs_1   | G ♭ octave 1                                            |
| MI_G_1                     | 5C42      | G octave 1                                              |
| MI_Gs_1                    | 5C43      | G ♯ octave 1                                            |
| MI_Ab_1                    | MI_Gs_1   | A ♭ octave 1                                            |
| MI_A_1                     | 5C44      | A octave 1                                              |
| MI_As_1                    | 5C45      | A ♯ octave 1                                            |
| MI_Bb_1                    | MI_As_1   | B ♭ octave 1                                            |
| MI_B_1                     | 5C46      | B octave 1                                              |
| MI_C_2                     | 5C47      | C octave 2                                              |
| MI_Cs_2                    | 5C48      | C ♯ octave 2                                            |
| MI_Db_2                    | MI_Cs_2   | D ♭ octave 2                                            |
| MI_D_2                     | 5C49      | D octave 2                                              |
| MI_Ds_2                    | 5C4A      | D ♯ octave 2                                            |
| MI_Eb_2                    | MI_Ds_2   | E ♭ octave 2                                            |
| MI_E_2                     | 5C4B      | E octave 2                                              |
| MI_F_2                     | 5C4C      | F octave 2                                              |
| MI_Fs_2                    | 5C4D      | F ♯ octave 2                                            |
| MI_Gb_2                    | MI_Fs_2   | G ♭ octave 2                                            |
| MI_G_2                     | 5C4E      | G octave 2                                              |
| MI_Gs_2                    | 5C4F      | G ♯ octave 2                                            |
| MI_Ab_2                    | MI_Gs_2   | A ♭ octave 2                                            |
| MI_A_2                     | 5C50      | A octave 2                                              |
| MI_As_2                    | 5C51      | A ♯ octave 2                                            |
| MI_Bb_2                    | MI_As_2   | B ♭ octave 2                                            |
| MI_B_2                     | 5C52      | B octave 2                                              |
| MI_C_3                     | 5C53      | C octave 3                                              |
| MI_Cs_3                    | 5C54      | C ♯ octave 3                                            |
| MI_Db_3                    | MI_Cs_3   | D ♭ octave 3                                            |
| MI_D_3                     | 5C55      | D octave 3                                              |
| MI_Ds_3                    | 5C56      | D ♯ octave 3                                            |
| MI_Eb_3                    | MI_Ds_3   | E ♭ octave 3                                            |
| MI_E_3                     | 5C57      | E octave 3                                              |
| MI_F_3                     | 5C58      | F octave 3                                              |
| MI_Fs_3                    | 5C59      | F ♯ octave 3                                            |
| MI_Gb_3                    | MI_Fs_3   | G ♭ octave 3                                            |
| MI_G_3                     | 5C5A      | G octave 3                                              |
| MI_Gs_3                    | 5C5B      | G ♯ octave 3                                            |
| MI_Ab_3                    | MI_Gs_3   | A ♭ octave 3                                            |
| MI_A_3                     | 5C5C      | A octave 3                                              |
| MI_As_3                    | 5C5D      | A ♯ octave 3                                            |
| MI_Bb_3                    | MI_As_3   | B ♭ octave 3                                            |
| MI_B_3                     | 5C5E      | B octave 3                                              |
| MI_C_4                     | 5C5F      | C octave 4                                              |
| MI_Cs_4                    | 5C60      | C ♯ octave 4                                            |
| MI_Db_4                    | MI_Cs_4   | D ♭ octave 4                                            |
| MI_D_4                     | 5C61      | D octave 4                                              |
| MI_Ds_4                    | 5C62      | D ♯ octave 4                                            |
| MI_Eb_4                    | MI_Ds_4   | E ♭ octave 4                                            |
| MI_E_4                     | 5C63      | E octave 4                                              |
| MI_F_4                     | 5C64      | F octave 4                                              |
| MI_Fs_4                    | 5C65      | F ♯ octave 4                                            |
| MI_Gb_4                    | MI_Fs_4   | G ♭ octave 4                                            |
| MI_G_4                     | 5C66      | G octave 4                                              |
| MI_Gs_4                    | 5C67      | G ♯ octave 4                                            |
| MI_Ab_4                    | MI_Gs_4   | A ♭ octave 4                                            |
| MI_A_4                     | 5C68      | A octave 4                                              |
| MI_As_4                    | 5C69      | A ♯ octave 4                                            |
| MI_Bb_4                    | MI_As_4   | B ♭ octave 4                                            |
| MI_B_4                     | 5C6A      | B octave 4                                              |
| MI_C_5                     | 5C6B      | C octave 5                                              |
| MI_Cs_5                    | 5C6C      | C ♯ octave 5                                            |
| MI_Db_5                    | MI_Cs_5,  | D ♭ octave 5                                            |
| MI_D_5                     | 5C6D      | D octave 5                                              |
| MI_Ds_5                    | 5C6E      | D ♯ octave 5                                            |
| MI_Eb_5                    | MI_Ds_5,  | E ♭ octave 5                                            |
| MI_E_5                     | 5C6F      | E octave 5                                              |
| MI_F_5                     | 5C70      | F octave 5                                              |
| MI_Fs_5                    | 5C71      | F ♯ octave 5                                            |
| MI_Gb_5                    | MI_Fs_5,  | G ♭ octave 5                                            |
| MI_G_5                     | 5C72      | G octave 5                                              |
| MI_Gs_5                    | 5C73      | G ♯ octave 5                                            |
| MI_Ab_5                    | MI_Gs_5,  | A ♭ octave 5                                            |
| MI_A_5                     | 5C74      | A octave 5                                              |
| MI_As_5                    | 5C75      | A ♯ octave 5                                            |
| MI_Bb_5                    | MI_As_5,  | B ♭ octave 5                                            |
| MI_B_5                     | 5C76      | B octave 5                                              |
| MI_OCT_N2                  | 5C77      | Go to octave -2                                         |
| MI_OCT_N1                  | 5C78      | Go to octave -1                                         |
| MI_OCT_0                   | 5C79      | Go to octave  0                                         |
| MI_OCT_1                   | 5C7A      | Go to octave  1                                         |
| MI_OCT_2                   | 5C7B      | Go to octave  2                                         |
| MI_OCT_3                   | 5C7C      | Go to octave  3                                         |
| MI_OCT_4                   | 5C7D      | Go to octave  4                                         |
| MI_OCT_5                   | 5C7E      | Go to octave  5                                         |
| MI_OCT_6                   | 5C7F      | Go to octave  6                                         |
| MI_OCT_7                   | 5C80      | Go to octave  7                                         |
| MI_OCTD                    | 5C81      | Go down an octave                                       |
| MI_OCTU                    | 5C82      | Go up an octave                                         |
| MI_TRNS_N6                 | 5C83      | Transpose notes down 6 posisions                        |
| MI_TRNS_N5                 | 5C84      | Transpose notes down 5 posisions                        |
| MI_TRNS_N4                 | 5C85      | Transpose notes down 4 posisions                        |
| MI_TRNS_N3                 | 5C86      | Transpose notes down 3 posisions                        |
| MI_TRNS_N2                 | 5C87      | Transpose notes down 2 posisions                        |
| MI_TRNS_N1                 | 5C88      | Transpose notes down 1 posision                         |
| MI_TRNS_0                  | 5C89      | No transposision                                        |
| MI_TRNS_1                  | 5C8A      | Transpose notes up 1 posision                           |
| MI_TRNS_2                  | 5C8B      | Transpose notes up 2 posisions                          |
| MI_TRNS_3                  | 5C8C      | Transpose notes up 3 posisions                          |
| MI_TRNS_4                  | 5C8D      | Transpose notes up 4 posisions                          |
| MI_TRNS_5                  | 5C8E      | Transpose notes up 5 posisions                          |
| MI_TRNS_6                  | 5C8F      | Transpose notes up 6 posisions                          |
| MI_TRNSD                   | 5C90      | Transpose notes down a posision                         |
| MI_TRNSU                   | 5C91      | Transpose notes up a posision                           |
| MI_VEL_0                   | 5C92      | Set Velocity to 0                                       |
| if VIA_ENABLE: MI_VEL_1    | MI_VEL_0  | If via is enabled, Velocity 1 is the same as Velocity 0 |
| if no VIA_ENABLE: MI_VEL_1 | 5C93      | Set Velocity to 1                                       |
| MI_VEL_2                   | 5C94      | Set Velocity to 2                                       |
| MI_VEL_3                   | 5C95      | Set Velocity to 3                                       |
| MI_VEL_4                   | 5C96      | Set Velocity to 4                                       |
| MI_VEL_5                   | 5C97      | Set Velocity to 5                                       |
| MI_VEL_6                   | 5C98      | Set Velocity to 6                                       |
| MI_VEL_7                   | 5C99      | Set Velocity to 7                                       |
| MI_VEL_8                   | 5C9A      | Set Velocity to 8                                       |
| MI_VEL_9                   | 5C9B      | Set Velocity to 9                                       |
| MI_VEL_10                  | 5C9C      | Set Velocity to 10                                      |
| MI_VELD                    | 5C9D      | Go down one tick of velocity                            |
| MI_VELU                    | 5C9E      | Go up one tick of velocity                              |
| MI_CH1                     | 5C9F      | Go to channel 1                                         |
| MI_CH2                     | 5CA0      | Go to channel 2                                         |
| MI_CH3                     | 5CA1      | Go to channel 3                                         |
| MI_CH4                     | 5CA2      | Go to channel 4                                         |
| MI_CH5                     | 5CA3      | Go to channel 5                                         |
| MI_CH6                     | 5CA4      | Go to channel 6                                         |
| MI_CH7                     | 5CA5      | Go to channel 7                                         |
| MI_CH8                     | 5CA6      | Go to channel 8                                         |
| MI_CH9                     | 5CA7      | Go to channel 9                                         |
| MI_CH10                    | 5CA8      | Go to channel 10                                        |
| MI_CH11                    | 5CA9      | Go to channel 11                                        |
| MI_CH12                    | 5CAA      | Go to channel 12                                        |
| MI_CH13                    | 5CAB      | Go to channel 13                                        |
| MI_CH14                    | 5CAC      | Go to channel 14                                        |
| MI_CH15                    | 5CAD      | Go to channel 15                                        |
| MI_CH16                    | 5CAE      | Go to channel 16                                        |
| MI_CHD                     | 5CAF      | Go to channel 17                                        |
| MI_CHU                     | 5CB0      | Go to channel 18                                        |
| MI_ALLOFF                  | 5CB1      | Turn off all notes                                      |
| MI_SUS                     | 5CB2      | Sustain                                                 |
| MI_PORT                    | 5CB3      | Portmento                                               |
| MI_SOST                    | 5CB4      | Sostenuto                                               |
| MI_SOFT                    | 5CB5      | Soft Pedal                                              |
| MI_LEG                     | 5CB6      | LEGATO                                                  |
| MI_MOD                     | 5CB7      | Modulation                                              |
| MI_MODSD                   | 5CB8      | Decrease Modulation Speed                               |
| MI_MODSU                   | 5CB9      | Increase Modulation Speed                               |
| MI_BENDD                   | 5CBA      | Bend pitch down                                         |
| MI_BENDU                   | 5CBB      | Bend pitch up                                           |

### Background

QMK MIDI is based on TMK MIDI which in turn is based on `avr-midi`

QMK MIDI is a subset implentation of the MIDI 1.0 specification. 

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
