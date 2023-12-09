# MIDI

## Usage

First, enable MIDI by adding the following to your `rules.mk`:

```make
MIDI_ENABLE = yes
```

There are two MIDI systems in QMK: basic and advanced. With basic MIDI you will only be able to send Note On and Note Off messages using the note keycodes, meaning that keycodes like `MI_OCTU` and `MI_OCTD` will not work. Advanced MIDI allows you to do things like octave shifts, channel changes, velocity changes, modulation, and more.

### Caveats

MIDI requires 2 USB endpoints and as such may not work on some hardware such as V-USB controllers.

### Basic MIDI

To enable basic MIDI, add the following to your `config.h`:

```c
#define MIDI_BASIC
```

### Advanced MIDI

To enable advanced MIDI, add the following to your `config.h`:

```c
#define MIDI_ADVANCED
```

#### Sending Control Change (CC) Messages

If you're aiming to emulate the features of something like a Launchpad or other MIDI controller you'll need to access the internal MIDI device directly.

Because there are so many possible CC messages, not all of them are implemented as keycodes. Additionally, you might need to provide more than just two values that you would get from a keycode (pressed and released) - for example, the analog values from a fader or a potentiometer. So, you will need to implement [custom keycodes](feature_macros.md) if you want to use them in your keymap directly using `process_record_user()`.


For reference of all the possible control code numbers see [MIDI Specification](#midi-specification)

#### Example code for using Generic On Off Switches as per MIDI Specification.
```c
#include QMK_KEYBOARD_H

extern MidiDevice midi_device;

// MIDI CC codes for generic on/off switches (80, 81, 82, 83)
// Off: 0-63
// On:  64-127

#define MIDI_CC_OFF 0
#define MIDI_CC_ON  127

enum custom_keycodes {
    MIDI_CC80 = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MIDI_CC80:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 80, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 80, MIDI_CC_OFF);
            }
            return true;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        // ...
        MIDI_CC80,
        // ...
    )
};
```

### Keycodes

|Keycode                        |Aliases           |Description                      |
|-------------------------------|------------------|---------------------------------|
|`QK_MIDI_ON`                   |`MI_ON`           |Turn MIDI on                     |
|`QK_MIDI_OFF`                  |`MI_OFF`          |Turn MIDI off                    |
|`QK_MIDI_TOGGLE`               |`MI_TOGG`         |Toggle MIDI enabled              |
|`QK_MIDI_NOTE_C_0`             |`MI_C`            |C octave 0                       |
|`QK_MIDI_NOTE_C_SHARP_0`       |`MI_Cs`, `MI_Db`  |C♯/D♭ octave 0                   |
|`QK_MIDI_NOTE_D_0`             |`MI_D`            |D octave 0                       |
|`QK_MIDI_NOTE_D_SHARP_0`       |`MI_Ds`, `MI_Eb`  |D♯/E♭ octave 0                   |
|`QK_MIDI_NOTE_E_0`             |`MI_E`            |E octave 0                       |
|`QK_MIDI_NOTE_F_0`             |`MI_F`            |F octave 0                       |
|`QK_MIDI_NOTE_F_SHARP_0`       |`MI_Fs`, `MI_Gb`  |F♯/G♭ octave 0                   |
|`QK_MIDI_NOTE_G_0`             |`MI_G`            |G octave 0                       |
|`QK_MIDI_NOTE_G_SHARP_0`       |`MI_Gs`, `MI_Ab`  |G♯/A♭ octave 0                   |
|`QK_MIDI_NOTE_A_0`             |`MI_A`            |A octave 0                       |
|`QK_MIDI_NOTE_A_SHARP_0`       |`MI_As`, `MI_Bb`  |A♯/B♭ octave 0                   |
|`QK_MIDI_NOTE_B_0`             |`MI_B`            |B octave 0                       |
|`QK_MIDI_NOTE_C_1`             |`MI_C1`           |C octave 1                       |
|`QK_MIDI_NOTE_C_SHARP_1`       |`MI_Cs1`, `MI_Db1`|C♯/D♭ octave 1                   |
|`QK_MIDI_NOTE_D_1`             |`MI_D1`           |D octave 1                       |
|`QK_MIDI_NOTE_D_SHARP_1`       |`MI_Ds1`, `MI_Eb1`|D♯/E♭ octave 1                   |
|`QK_MIDI_NOTE_E_1`             |`MI_E1`           |E octave 1                       |
|`QK_MIDI_NOTE_F_1`             |`MI_F1`           |F octave 1                       |
|`QK_MIDI_NOTE_F_SHARP_1`       |`MI_Fs1`, `MI_Gb1`|F♯/G♭ octave 1                   |
|`QK_MIDI_NOTE_G_1`             |`MI_G1`           |G octave 1                       |
|`QK_MIDI_NOTE_G_SHARP_1`       |`MI_Gs1`, `MI_Ab1`|G♯/A♭ octave 1                   |
|`QK_MIDI_NOTE_A_1`             |`MI_A1`           |A octave 1                       |
|`QK_MIDI_NOTE_A_SHARP_1`       |`MI_As1`, `MI_Bb1`|A♯/B♭ octave 1                   |
|`QK_MIDI_NOTE_B_1`             |`MI_B1`           |B octave 1                       |
|`QK_MIDI_NOTE_C_2`             |`MI_C2`           |C octave 2                       |
|`QK_MIDI_NOTE_C_SHARP_2`       |`MI_Cs2`, `MI_Db2`|C♯/D♭ octave 2                   |
|`QK_MIDI_NOTE_D_2`             |`MI_D2`           |D octave 2                       |
|`QK_MIDI_NOTE_D_SHARP_2`       |`MI_Ds2`, `MI_Eb2`|D♯/E♭ octave 2                   |
|`QK_MIDI_NOTE_E_2`             |`MI_E2`           |E octave 2                       |
|`QK_MIDI_NOTE_F_2`             |`MI_F2`           |F octave 2                       |
|`QK_MIDI_NOTE_F_SHARP_2`       |`MI_Fs2`, `MI_Gb2`|F♯/G♭ octave 2                   |
|`QK_MIDI_NOTE_G_2`             |`MI_G2`           |G octave 2                       |
|`QK_MIDI_NOTE_G_SHARP_2`       |`MI_Gs2`, `MI_Ab2`|G♯/A♭ octave 2                   |
|`QK_MIDI_NOTE_A_2`             |`MI_A2`           |A octave 2                       |
|`QK_MIDI_NOTE_A_SHARP_2`       |`MI_As2`, `MI_Bb2`|A♯/B♭ octave 2                   |
|`QK_MIDI_NOTE_B_2`             |`MI_B2`           |B octave 2                       |
|`QK_MIDI_NOTE_C_3`             |`MI_C3`           |C octave 3                       |
|`QK_MIDI_NOTE_C_SHARP_3`       |`MI_Cs3`, `MI_Db3`|C♯/D♭ octave 3                   |
|`QK_MIDI_NOTE_D_3`             |`MI_D3`           |D octave 3                       |
|`QK_MIDI_NOTE_D_SHARP_3`       |`MI_Ds3`, `MI_Eb3`|D♯/E♭ octave 3                   |
|`QK_MIDI_NOTE_E_3`             |`MI_E3`           |E octave 3                       |
|`QK_MIDI_NOTE_F_3`             |`MI_F3`           |F octave 3                       |
|`QK_MIDI_NOTE_F_SHARP_3`       |`MI_Fs3`, `MI_Gb3`|F♯/G♭ octave 3                   |
|`QK_MIDI_NOTE_G_3`             |`MI_G3`           |G octave 3                       |
|`QK_MIDI_NOTE_G_SHARP_3`       |`MI_Gs3`, `MI_Ab3`|G♯/A♭ octave 3                   |
|`QK_MIDI_NOTE_A_3`             |`MI_A3`           |A octave 3                       |
|`QK_MIDI_NOTE_A_SHARP_3`       |`MI_As3`, `MI_Bb3`|A♯/B♭ octave 3                   |
|`QK_MIDI_NOTE_B_3`             |`MI_B3`           |B octave 3                       |
|`QK_MIDI_NOTE_C_4`             |`MI_C4`           |C octave 4                       |
|`QK_MIDI_NOTE_C_SHARP_4`       |`MI_Cs4`, `MI_Db4`|C♯/D♭ octave 4                   |
|`QK_MIDI_NOTE_D_4`             |`MI_D4`           |D octave 4                       |
|`QK_MIDI_NOTE_D_SHARP_4`       |`MI_Ds4`, `MI_Eb4`|D♯/E♭ octave 4                   |
|`QK_MIDI_NOTE_E_4`             |`MI_E4`           |E octave 4                       |
|`QK_MIDI_NOTE_F_4`             |`MI_F4`           |F octave 4                       |
|`QK_MIDI_NOTE_F_SHARP_4`       |`MI_Fs4`, `MI_Gb4`|F♯/G♭ octave 4                   |
|`QK_MIDI_NOTE_G_4`             |`MI_G4`           |G octave 4                       |
|`QK_MIDI_NOTE_G_SHARP_4`       |`MI_Gs4`, `MI_Ab4`|G♯/A♭ octave 4                   |
|`QK_MIDI_NOTE_A_4`             |`MI_A4`           |A octave 4                       |
|`QK_MIDI_NOTE_A_SHARP_4`       |`MI_As4`, `MI_Bb4`|A♯/B♭ octave 4                   |
|`QK_MIDI_NOTE_B_4`             |`MI_B4`           |B octave 4                       |
|`QK_MIDI_NOTE_C_5`             |`MI_C5`           |C octave 5                       |
|`QK_MIDI_NOTE_C_SHARP_5`       |`MI_Cs5`, `MI_Db5`|C♯/D♭ octave 5                   |
|`QK_MIDI_NOTE_D_5`             |`MI_D5`           |D octave 5                       |
|`QK_MIDI_NOTE_D_SHARP_5`       |`MI_Ds5`, `MI_Eb5`|D♯/E♭ octave 5                   |
|`QK_MIDI_NOTE_E_5`             |`MI_E5`           |E octave 5                       |
|`QK_MIDI_NOTE_F_5`             |`MI_F5`           |F octave 5                       |
|`QK_MIDI_NOTE_F_SHARP_5`       |`MI_Fs5`, `MI_Gb5`|F♯/G♭ octave 5                   |
|`QK_MIDI_NOTE_G_5`             |`MI_G5`           |G octave 5                       |
|`QK_MIDI_NOTE_G_SHARP_5`       |`MI_Gs5`, `MI_Ab5`|G♯/A♭ octave 5                   |
|`QK_MIDI_NOTE_A_5`             |`MI_A5`           |A octave 5                       |
|`QK_MIDI_NOTE_A_SHARP_5`       |`MI_As5`, `MI_Bb5`|A♯/B♭ octave 5                   |
|`QK_MIDI_NOTE_B_5`             |`MI_B5`           |B octave 5                       |
|`QK_MIDI_OCTAVE_N2`            |`MI_OCN2`         |Set octave to -2                 |
|`QK_MIDI_OCTAVE_N1`            |`MI_OCN1`         |Set octave to -1                 |
|`QK_MIDI_OCTAVE_0`             |`MI_OC0`          |Set octave to 0                  |
|`QK_MIDI_OCTAVE_1`             |`MI_OC1`          |Set octave to 1                  |
|`QK_MIDI_OCTAVE_2`             |`MI_OC2`          |Set octave to 2                  |
|`QK_MIDI_OCTAVE_3`             |`MI_OC3`          |Set octave to 3                  |
|`QK_MIDI_OCTAVE_4`             |`MI_OC4`          |Set octave to 4                  |
|`QK_MIDI_OCTAVE_5`             |`MI_OC5`          |Set octave to 5                  |
|`QK_MIDI_OCTAVE_6`             |`MI_OC6`          |Set octave to 6                  |
|`QK_MIDI_OCTAVE_7`             |`MI_OC7`          |Set octave to 7                  |
|`QK_MIDI_OCTAVE_DOWN`          |`MI_OCTD`         |Move down an octave              |
|`QK_MIDI_OCTAVE_UP`            |`MI_OCTU`         |Move up an octave                |
|`QK_MIDI_TRANSPOSE_N6`         |`MI_TRN6`         |Set transposition to -6 semitones|
|`QK_MIDI_TRANSPOSE_N5`         |`MI_TRN5`         |Set transposition to -5 semitones|
|`QK_MIDI_TRANSPOSE_N4`         |`MI_TRN4`         |Set transposition to -4 semitones|
|`QK_MIDI_TRANSPOSE_N3`         |`MI_TRN3`         |Set transposition to -3 semitones|
|`QK_MIDI_TRANSPOSE_N2`         |`MI_TRN2`         |Set transposition to -2 semitones|
|`QK_MIDI_TRANSPOSE_N1`         |`MI_TRN1`         |Set transposition to -1 semitone |
|`QK_MIDI_TRANSPOSE_0`          |`MI_TR0`          |No transposition                 |
|`QK_MIDI_TRANSPOSE_1`          |`MI_TR1`          |Set transposition to +1 semitone |
|`QK_MIDI_TRANSPOSE_2`          |`MI_TR2`          |Set transposition to +2 semitones|
|`QK_MIDI_TRANSPOSE_3`          |`MI_TR3`          |Set transposition to +3 semitones|
|`QK_MIDI_TRANSPOSE_4`          |`MI_TR4`          |Set transposition to +4 semitones|
|`QK_MIDI_TRANSPOSE_5`          |`MI_TR5`          |Set transposition to +5 semitones|
|`QK_MIDI_TRANSPOSE_6`          |`MI_TR6`          |Set transposition to +6 semitones|
|`QK_MIDI_TRANSPOSE_DOWN`       |`MI_TRSD`         |Decrease transposition           |
|`QK_MIDI_TRANSPOSE_UP`         |`MI_TRSU`         |Increase transposition           |
|`QK_MIDI_VELOCITY_0`           |`MI_VL0`          |Set velocity to 0                |
|`QK_MIDI_VELOCITY_1`           |`MI_VL1`          |Set velocity to 12               |
|`QK_MIDI_VELOCITY_2`           |`MI_VL2`          |Set velocity to 25               |
|`QK_MIDI_VELOCITY_3`           |`MI_VL3`          |Set velocity to 38               |
|`QK_MIDI_VELOCITY_4`           |`MI_VL4`          |Set velocity to 51               |
|`QK_MIDI_VELOCITY_5`           |`MI_VL5`          |Set velocity to 64               |
|`QK_MIDI_VELOCITY_6`           |`MI_VL6`          |Set velocity to 76               |
|`QK_MIDI_VELOCITY_7`           |`MI_VL7`          |Set velocity to 89               |
|`QK_MIDI_VELOCITY_8`           |`MI_VL8`          |Set velocity to 102              |
|`QK_MIDI_VELOCITY_9`           |`MI_VL9`          |Set velocity to 114              |
|`QK_MIDI_VELOCITY_10`          |`MI_VL10`         |Set velocity to 127              |
|`QK_MIDI_VELOCITY_DOWN`        |`MI_VELD`         |Decrease velocity                |
|`QK_MIDI_VELOCITY_UP`          |`MI_VELU`         |Increase velocity                |
|`QK_MIDI_CHANNEL_1`            |`MI_CH1`          |Set channel to 1                 |
|`QK_MIDI_CHANNEL_2`            |`MI_CH2`          |Set channel to 2                 |
|`QK_MIDI_CHANNEL_3`            |`MI_CH3`          |Set channel to 3                 |
|`QK_MIDI_CHANNEL_4`            |`MI_CH4`          |Set channel to 4                 |
|`QK_MIDI_CHANNEL_5`            |`MI_CH5`          |Set channel to 5                 |
|`QK_MIDI_CHANNEL_6`            |`MI_CH6`          |Set channel to 6                 |
|`QK_MIDI_CHANNEL_7`            |`MI_CH7`          |Set channel to 7                 |
|`QK_MIDI_CHANNEL_8`            |`MI_CH8`          |Set channel to 8                 |
|`QK_MIDI_CHANNEL_9`            |`MI_CH9`          |Set channel to 9                 |
|`QK_MIDI_CHANNEL_10`           |`MI_CH10`         |Set channel to 10                |
|`QK_MIDI_CHANNEL_11`           |`MI_CH11`         |Set channel to 11                |
|`QK_MIDI_CHANNEL_12`           |`MI_CH12`         |Set channel to 12                |
|`QK_MIDI_CHANNEL_13`           |`MI_CH13`         |Set channel to 13                |
|`QK_MIDI_CHANNEL_14`           |`MI_CH14`         |Set channel to 14                |
|`QK_MIDI_CHANNEL_15`           |`MI_CH15`         |Set channel to 15                |
|`QK_MIDI_CHANNEL_16`           |`MI_CH16`         |Set channel to 16                |
|`QK_MIDI_CHANNEL_DOWN`         |`MI_CHND`         |Decrease channel                 |
|`QK_MIDI_CHANNEL_UP`           |`MI_CHNU`         |Increase channel                 |
|`QK_MIDI_ALL_NOTES_OFF`        |`MI_AOFF`         |Stop all notes                   |
|`QK_MIDI_SUSTAIN`              |`MI_SUST`         |Sustain                          |
|`QK_MIDI_PORTAMENTO`           |`MI_PORT`         |Portmento                        |
|`QK_MIDI_SOSTENUTO`            |`MI_SOST`         |Sostenuto                        |
|`QK_MIDI_SOFT`                 |`MI_SOFT`         |Soft Pedal                       |
|`QK_MIDI_LEGATO`               |`MI_LEG`          |Legato                           |
|`QK_MIDI_MODULATION`           |`MI_MOD`          |Modulation                       |
|`QK_MIDI_MODULATION_SPEED_DOWN`|`MI_MODD`         |Decrease modulation speed        |
|`QK_MIDI_MODULATION_SPEED_UP`  |`MI_MODU`         |Increase modulation speed        |
|`QK_MIDI_PITCH_BEND_DOWN`      |`MI_BNDD`         |Bend pitch down                  |
|`QK_MIDI_PITCH_BEND_UP`        |`MI_BNDU`         |Bend pitch up                    |

### Configuration

Certain values are stored in the `midi_config` struct. This configuration is not persisted to EEPROM. By default, these values are:

|Configuration      |Value|Comments               |
|-------------------|-----|-----------------------|
|Octave             |`4`  |Corresponds to `MI_OC2`|
|Transposition      |`0`  |                       |
|Velocity           |`127`|                       |
|Channel            |`0`  |                       |
|Modulation Interval|`8`  |                       |

For the above, the `MI_C` keycode will produce a C3 (note number 48), and so on.

### References
#### MIDI Specification

 * [MIDI.org](https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message)
 * [CMU MIDI Programmer's Reference](https://www.cs.cmu.edu/~music/cmsip/readings/MIDI%20tutorial%20for%20programmers.html)
#### QMK C Files

 * `quantum/process_keycode/process_midi.c`
 * `quantum/quantum_keycodes.h`
 * `quantum/midi/midi.h`
 * `quantum/midi/midi.c`
 * `quantum/midi/qmk_midi.c`
 * `quantum/midi/midi_device.h`

<!--
#### QMK Internals (Autogenerated)
 
 * [Internals/MIDI Device Setup Process](internals/midi_device_setup_process.md)
 * [Internals/MIDI Device](internals/midi_device.md)
 * [Internals/MIDI Util](internals/midi_util.md)
-->
