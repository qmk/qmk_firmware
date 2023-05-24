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
                midi_send_cc(&midi_device, midi_config.channel, 80, ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 80, OFF);
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

|Keycode     |Aliases  |Description                      |
|------------|---------|---------------------------------|
|`MI_ON`     |         |Turn MIDI on                     |
|`MI_OFF`    |         |Turn MIDI off                    |
|`MI_TOG`    |         |Toggle MIDI enabled              |
|`MI_C`      |         |C octave 0                       |
|`MI_Cs`     |`MI_Db`  |C♯/D♭ octave 0                   |
|`MI_D`      |         |D octave 0                       |
|`MI_Ds`     |`MI_Eb`  |D♯/E♭ octave 0                   |
|`MI_E`      |         |E octave 0                       |
|`MI_F`      |         |F octave 0                       |
|`MI_Fs`     |`MI_Gb`  |F♯/G♭ octave 0                   |
|`MI_G`      |         |G octave 0                       |
|`MI_Gs`     |`MI_Gs`  |G♯/A♭ octave 0                   |
|`MI_A`      |         |A octave 0                       |
|`MI_As`     |`MI_Bb`  |A♯/B♭ octave 0                   |
|`MI_B`      |         |B octave 0                       |
|`MI_C_1`    |         |C octave 1                       |
|`MI_Cs_1`   |`MI_Db_1`|C♯/D♭ octave 1                   |
|`MI_D_1`    |         |D octave 1                       |
|`MI_Ds_1`   |`MI_Eb_1`|D♯/E♭ octave 1                   |
|`MI_E_1`    |         |E octave 1                       |
|`MI_F_1`    |         |F octave 1                       |
|`MI_Fs_1`   |`MI_Gb_1`|F♯/G♭ octave 1                   |
|`MI_G_1`    |         |G octave 1                       |
|`MI_Gs_1`   |`MI_Ab_1`|G♯/A♭ octave 1                   |
|`MI_A_1`    |         |A octave 1                       |
|`MI_As_1`   |`MI_Bb_1`|A♯/B♭ octave 1                   |
|`MI_B_1`    |         |B octave 1                       |
|`MI_C_2`    |         |C octave 2                       |
|`MI_Cs_2`   |`MI_Db_2`|C♯/D♭ octave 2                   |
|`MI_D_2`    |         |D octave 2                       |
|`MI_Ds_2`   |`MI_Eb_2`|D♯/E♭ octave 2                   |
|`MI_E_2`    |         |E octave 2                       |
|`MI_F_2`    |         |F octave 2                       |
|`MI_Fs_2`   |`MI_Gb_2`|F♯/G♭ octave 2                   |
|`MI_G_2`    |         |G octave 2                       |
|`MI_Gs_2`   |`MI_Ab_2`|G♯/A♭ octave 2                   |
|`MI_A_2`    |         |A octave 2                       |
|`MI_As_2`   |`MI_Bb_2`|A♯/B♭ octave 2                   |
|`MI_B_2`    |         |B octave 2                       |
|`MI_C_3`    |         |C octave 3                       |
|`MI_Cs_3`   |`MI_Db_3`|C♯/D♭ octave 3                   |
|`MI_D_3`    |         |D octave 3                       |
|`MI_Ds_3`   |`MI_Eb_3`|D♯/E♭ octave 3                   |
|`MI_E_3`    |         |E octave 3                       |
|`MI_F_3`    |         |F octave 3                       |
|`MI_Fs_3`   |`MI_Gb_3`|F♯/G♭ octave 3                   |
|`MI_G_3`    |         |G octave 3                       |
|`MI_Gs_3`   |`MI_Ab_3`|G♯/A♭ octave 3                   |
|`MI_A_3`    |         |A octave 3                       |
|`MI_As_3`   |`MI_Bb_3`|A♯/B♭ octave 3                   |
|`MI_B_3`    |         |B octave 3                       |
|`MI_C_4`    |         |C octave 4                       |
|`MI_Cs_4`   |`MI_Db_4`|C♯/D♭ octave 4                   |
|`MI_D_4`    |         |D octave 4                       |
|`MI_Ds_4`   |`MI_Eb_4`|D♯/E♭ octave 4                   |
|`MI_E_4`    |         |E octave 4                       |
|`MI_F_4`    |         |F octave 4                       |
|`MI_Fs_4`   |`MI_Gb_4`|F♯/G♭ octave 4                   |
|`MI_G_4`    |         |G octave 4                       |
|`MI_Gs_4`   |`MI_Ab_4`|G♯/A♭ octave 4                   |
|`MI_A_4`    |         |A octave 4                       |
|`MI_As_4`   |`MI_Bb_4`|A♯/B♭ octave 4                   |
|`MI_B_4`    |         |B octave 4                       |
|`MI_C_5`    |         |C octave 5                       |
|`MI_Cs_5`   |`MI_Db_5`|C♯/D♭ octave 5                   |
|`MI_D_5`    |         |D octave 5                       |
|`MI_Ds_5`   |`MI_Eb_5`|D♯/E♭ octave 5                   |
|`MI_E_5`    |         |E octave 5                       |
|`MI_F_5`    |         |F octave 5                       |
|`MI_Fs_5`   |`MI_Gb_5`|F♯/G♭ octave 5                   |
|`MI_G_5`    |         |G octave 5                       |
|`MI_Gs_5`   |`MI_Ab_5`|G♯/A♭ octave 5                   |
|`MI_A_5`    |         |A octave 5                       |
|`MI_As_5`   |`MI_Bb_5`|A♯/B♭ octave 5                   |
|`MI_B_5`    |         |B octave 5                       |
|`MI_OCT_N2` |         |Set octave to -2                 |
|`MI_OCT_N1` |         |Set octave to -1                 |
|`MI_OCT_0`  |         |Set octave to 0                  |
|`MI_OCT_1`  |         |Set octave to 1                  |
|`MI_OCT_2`  |         |Set octave to 2                  |
|`MI_OCT_3`  |         |Set octave to 3                  |
|`MI_OCT_4`  |         |Set octave to 4                  |
|`MI_OCT_5`  |         |Set octave to 5                  |
|`MI_OCT_6`  |         |Set octave to 6                  |
|`MI_OCT_7`  |         |Set octave to 7                  |
|`MI_OCTD`   |         |Move down an octave              |
|`MI_OCTU`   |         |Move up an octave                |
|`MI_TRNS_N6`|         |Set transposition to -6 semitones|
|`MI_TRNS_N5`|         |Set transposition to -5 semitones|
|`MI_TRNS_N4`|         |Set transposition to -4 semitones|
|`MI_TRNS_N3`|         |Set transposition to -3 semitones|
|`MI_TRNS_N2`|         |Set transposition to -2 semitones|
|`MI_TRNS_N1`|         |Set transposition to -1 semitone |
|`MI_TRNS_0` |         |No transposition                 |
|`MI_TRNS_1` |         |Set transposition to +1 semitone |
|`MI_TRNS_2` |         |Set transposition to +2 semitones|
|`MI_TRNS_3` |         |Set transposition to +3 semitones|
|`MI_TRNS_4` |         |Set transposition to +4 semitones|
|`MI_TRNS_5` |         |Set transposition to +5 semitones|
|`MI_TRNS_6` |         |Set transposition to +6 semitones|
|`MI_TRNSD`  |         |Decrease transposition           |
|`MI_TRNSU`  |         |Increase transposition           |
|`MI_VEL_0`  |         |Set velocity to 0                |
|`MI_VEL_1`  |         |Set velocity to 12               |
|`MI_VEL_2`  |         |Set velocity to 25               |
|`MI_VEL_3`  |         |Set velocity to 38               |
|`MI_VEL_4`  |         |Set velocity to 51               |
|`MI_VEL_5`  |         |Set velocity to 64               |
|`MI_VEL_6`  |         |Set velocity to 76               |
|`MI_VEL_7`  |         |Set velocity to 89               |
|`MI_VEL_8`  |         |Set velocity to 102              |
|`MI_VEL_9`  |         |Set velocity to 114              |
|`MI_VEL_10` |         |Set velocity to 127              |
|`MI_VELD`   |         |Decrease velocity                |
|`MI_VELU`   |         |Increase velocity                |
|`MI_CH1`    |         |Set channel to 1                 |
|`MI_CH2`    |         |Set channel to 2                 |
|`MI_CH3`    |         |Set channel to 3                 |
|`MI_CH4`    |         |Set channel to 4                 |
|`MI_CH5`    |         |Set channel to 5                 |
|`MI_CH6`    |         |Set channel to 6                 |
|`MI_CH7`    |         |Set channel to 7                 |
|`MI_CH8`    |         |Set channel to 8                 |
|`MI_CH9`    |         |Set channel to 9                 |
|`MI_CH10`   |         |Set channel to 10                |
|`MI_CH11`   |         |Set channel to 11                |
|`MI_CH12`   |         |Set channel to 12                |
|`MI_CH13`   |         |Set channel to 13                |
|`MI_CH14`   |         |Set channel to 14                |
|`MI_CH15`   |         |Set channel to 15                |
|`MI_CH16`   |         |Set channel to 16                |
|`MI_CHD`    |         |Decrease channel                 |
|`MI_CHU`    |         |Increase channel                 |
|`MI_ALLOFF` |         |Stop all notes                   |
|`MI_SUS`    |         |Sustain                          |
|`MI_PORT`   |         |Portmento                        |
|`MI_SOST`   |         |Sostenuto                        |
|`MI_SOFT`   |         |Soft Pedal                       |
|`MI_LEG`    |         |Legato                           |
|`MI_MOD`    |         |Modulation                       |
|`MI_MODSD`  |         |Decrease modulation speed        |
|`MI_MODSU`  |         |Increase modulation speed        |
|`MI_BENDD`  |         |Bend pitch down                  |
|`MI_BENDU`  |         |Bend pitch up                    |

### Configuration

Certain values are stored in the `midi_config` struct. This configuration is not persisted to EEPROM. By default, these values are:

|Configuration      |Value|Comments                 |
|-------------------|-----|-------------------------|
|Octave             |`4`  |Corresponds to `MI_OCT_2`|
|Transposition      |`0`  |                         |
|Velocity           |`127`|                         |
|Channel            |`0`  |                         |
|Modulation Interval|`8`  |                         |

For the above, the `MI_C` keycode will produce a C3 (note number 48), and so on.

### References
#### MIDI Specification

 * [MIDI.org](https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message)
 * [CMU MIDI Programmer's Reference](https://www.cs.cmu.edu/~music/cmsip/readings/MIDI%20tutorial%20for%20programmers.html)
#### QMK C Files

 * `quantum/process_keycode/process_midi.c`
 * `quantum/quantum_keycodes.h`
 * `tmk_core/protocol/midi.h`
 * `tmk_core/protocol/midi.c`
 * `tmk_core/protocol/qmk_midi.c`
 * `tmk_core/protocol/midi_device.h`

<!--
#### QMK Internals (Autogenerated)
 
 * [Internals/MIDI Device Setup Process](internals/midi_device_setup_process.md)
 * [Internals/MIDI Device](internals/midi_device.md)
 * [Internals/MIDI Util](internals/midi_util.md)
-->
