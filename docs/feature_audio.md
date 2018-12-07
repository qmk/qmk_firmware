# Audio

Your keyboard can make sounds! If you've got a Planck, Preonic, or basically any AVR keyboard that allows access to certain PWM-capable pins, you can hook up a simple speaker and make it beep. You can use those beeps to indicate layer transitions, modifiers, special keys, or just to play some funky 8bit tunes.

Up to two simultaneous audio voices are supported, one driven by timer 1 and another driven by timer 3.  The following pins can be defined as audio outputs in config.h:

Timer 1:
`#define B5_AUDIO`
`#define B6_AUDIO`
`#define B7_AUDIO`

Timer 3:
`#define C4_AUDIO`
`#define C5_AUDIO`
`#define C6_AUDIO`

If you add `AUDIO_ENABLE = yes` to your `rules.mk`, there's a couple different sounds that will automatically be enabled without any other configuration:

```
STARTUP_SONG // plays when the keyboard starts up (audio.c)
GOODBYE_SONG // plays when you press the RESET key (quantum.c)
AG_NORM_SONG // plays when you press AG_NORM (quantum.c)
AG_SWAP_SONG // plays when you press AG_SWAP (quantum.c)
MUSIC_ON_SONG // plays when music mode is activated (process_music.c)
MUSIC_OFF_SONG // plays when music mode is deactivated (process_music.c)
CHROMATIC_SONG // plays when the chromatic music mode is selected (process_music.c)
GUITAR_SONG // plays when the guitar music mode is selected (process_music.c)
VIOLIN_SONG // plays when the violin music mode is selected (process_music.c)
MAJOR_SONG // plays when the major music mode is selected (process_music.c)
```

You can override the default songs by doing something like this in your `config.h`:

```c
#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif
```

A full list of sounds can be found in [quantum/audio/song_list.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/song_list.h) - feel free to add your own to this list! All available notes can be seen in [quantum/audio/musical_notes.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/musical_notes.h).

To play a custom sound at a particular time, you can define a song like this (near the top of the file):

```c
float my_song[][2] = SONG(QWERTY_SOUND);
```

And then play your song like this:

```c
PLAY_SONG(my_song);
```

Alternatively, you can play it in a loop like this:

```c
PLAY_LOOP(my_song);
```

It's advised that you wrap all audio features in `#ifdef AUDIO_ENABLE` / `#endif` to avoid causing problems when audio isn't built into the keyboard.

The available keycodes for audio are: 

* `AU_ON` - Turn audio mode on
* `AU_OFF` - Turn audio mode off
* `AU_TOG` - Toggle audio mode

## ARM Audio Volume

For ARM devices, you can adjust the DAC sample values. If your board is too loud for you or your coworkers, you can set the max using `DAC_SAMPLE_MAX` in your `config.h`:

```c
#define DAC_SAMPLE_MAX 65535U
```

## Music Mode

The music mode maps your columns to a chromatic scale, and your rows to octaves. This works best with ortholinear keyboards, but can be made to work with others. All keycodes less than `0xFF` get blocked, so you won't type while playing notes - if you have special keys/mods, those will still work. A work-around for this is to jump to a different layer with KC_NOs before (or after) enabling music mode.

Recording is experimental due to some memory issues - if you experience some weird behavior, unplugging/replugging your keyboard will fix things.

Keycodes available:

* `MU_ON` - Turn music mode on
* `MU_OFF` - Turn music mode off
* `MU_TOG` - Toggle music mode
* `MU_MOD` - Cycle through the music modes:
  * `CHROMATIC_MODE` - Chromatic scale, row changes the octave
  * `GUITAR_MODE` - Chromatic scale, but the row changes the string (+5 st)
  * `VIOLIN_MODE` - Chromatic scale, but the row changes the string (+7 st)
  * `MAJOR_MODE` - Major scale

In music mode, the following keycodes work differently, and don't pass through:

* `LCTL` - start a recording
* `LALT` - stop recording/stop playing
* `LGUI` - play recording
* `KC_UP` - speed-up playback
* `KC_DOWN` - slow-down playback

By default, `MUSIC_MASK` is set to `keycode < 0xFF` which means keycodes less than `0xFF` are turned into notes, and don't output anything. You can change this by defining this in your `config.h` like this:

    #define MUSIC_MASK keycode != KC_NO

Which will capture all keycodes - be careful, this will get you stuck in music mode until you restart your keyboard!

For a more advanced way to control which keycodes should still be processed, you can use `music_mask_kb(keycode)` in `<keyboard>.c` and `music_mask_user(keycode)` in your `keymap.c`:

    bool music_mask_user(uint16_t keycode) {
      switch (keycode) {
        case RAISE:
        case LOWER:
          return false;
        default:
          return true;
      }
    }

Things that return false are not part of the mask, and are always processed.

The pitch standard (`PITCH_STANDARD_A`) is 440.0f by default - to change this, add something like this to your `config.h`:

    #define PITCH_STANDARD_A 432.0f

You can completely disable Music Mode as well. This is useful, if you're pressed for space on your controller.  To disable it, add this to your `config.h`:

    #define NO_MUSIC_MODE

## Audio Click

This adds a click sound each time you hit a button, to simulate click sounds from the keyboard. And the sounds are slightly different for each keypress, so it doesn't sound like a single long note, if you type rapidly. 

* `CK_TOGG` - Toggles the status (will play sound if enabled)
* `CK_ON` - Turns on Audio Click (plays sound)
* `CK_OFF` - Turns off Audio Click (doesn't play sound)
* `CK_RST` - Resets the frequency to the default state (plays sound at default frequency)
* `CK_UP` - Increases the frequency of the clicks (plays sound at new frequency)
* `CK_DOWN` - Decreases the frequency of the clicks (plays sound at new frequency)


The feature is disabled by default, to save space.  To enable it, add this to your `config.h`:

    #define AUDIO_CLICKY


You can configure the default, min and max frequencies, the stepping and built in randomness by defining these values: 

| Option | Default Value | Description |
|--------|---------------|-------------|
| `AUDIO_CLICKY_FREQ_DEFAULT` | 440.0f | Sets the default/starting audio frequency for the clicky sounds. |
| `AUDIO_CLICKY_FREQ_MIN` | 65.0f | Sets the lowest frequency (under 60f are a bit buggy). |
| `AUDIO_CLICKY_FREQ_MAX` | 1500.0f | Sets the the highest frequency. Too high may result in coworkers attacking you. |
| `AUDIO_CLICKY_FREQ_FACTOR` | 1.18921f| Sets the stepping of UP/DOWN key codes. |
| `AUDIO_CLICKY_FREQ_RANDOMNESS`     |  0.05f |  Sets a factor of randomness for the clicks, Setting this to `0f` will make each click identical, and `1.0f` will make this sound much like the 90's computer screen scrolling/typing effect. | 




## MIDI Functionality

This is still a WIP, but check out `quantum/keymap_midi.c` to see what's happening. Enable from the Makefile.


## Audio Keycodes

|Key             |Aliases  |Description                       |
|----------------|---------|----------------------------------|
|`AU_ON`         |         |Audio mode on                     |
|`AU_OFF`        |         |Audio mode off                    |
|`AU_TOG`        |         |Toggles Audio mode                |
|`CLICKY_TOGGLE` |`CK_TOGG`|Toggles Audio clicky mode         |
|`CLICKY_UP`     |`CK_UP`  |Increases frequency of the clicks |
|`CLICKY_DOWN`   |`CK_DOWN`|Decreases frequency of the clicks |
|`CLICKY_RESET`  |`CK_RST` |Resets frequency to default       |
|`MU_ON`         |         |Turns on Music Mode               |
|`MU_OFF`        |         |Turns off Music Mode              |
|`MU_TOG`        |         |Toggles Music Mode                |
|`MU_MOD`        |         |Cycles through the music modes    |

<!-- FIXME: this formatting needs work

## Audio

```c
#ifdef AUDIO_ENABLE
    AU_ON,
    AU_OFF,
    AU_TOG,

    #ifdef FAUXCLICKY_ENABLE
        FC_ON,
        FC_OFF,
        FC_TOG,
    #endif

    // Music mode on/off/toggle
    MU_ON,
    MU_OFF,
    MU_TOG,

    // Music voice iterate
    MUV_IN,
    MUV_DE,
#endif
```

### Midi

#if !MIDI_ENABLE_STRICT || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
    MI_ON,  // send midi notes when music mode is enabled
    MI_OFF, // don't send midi notes when music mode is enabled
#endif

MIDI_TONE_MIN,
MIDI_TONE_MAX

MI_C = MIDI_TONE_MIN,
MI_Cs,
MI_Db = MI_Cs,
MI_D,
MI_Ds,
MI_Eb = MI_Ds,
MI_E,
MI_F,
MI_Fs,
MI_Gb = MI_Fs,
MI_G,
MI_Gs,
MI_Ab = MI_Gs,
MI_A,
MI_As,
MI_Bb = MI_As,
MI_B,

MIDI_TONE_KEYCODE_OCTAVES > 1

where x = 1-5:
MI_C_x,
MI_Cs_x,
MI_Db_x = MI_Cs_x,
MI_D_x,
MI_Ds_x,
MI_Eb_x = MI_Ds_x,
MI_E_x,
MI_F_x,
MI_Fs_x,
MI_Gb_x = MI_Fs_x,
MI_G_x,
MI_Gs_x,
MI_Ab_x = MI_Gs_x,
MI_A_x,
MI_As_x,
MI_Bb_x = MI_As_x,
MI_B_x,

MI_OCT_Nx 1-2
MI_OCT_x 0-7
MIDI_OCTAVE_MIN = MI_OCT_N2,
MIDI_OCTAVE_MAX = MI_OCT_7,
MI_OCTD, // octave down
MI_OCTU, // octave up

MI_TRNS_Nx 1-6
MI_TRNS_x 0-6
MIDI_TRANSPOSE_MIN = MI_TRNS_N6,
MIDI_TRANSPOSE_MAX = MI_TRNS_6,
MI_TRNSD, // transpose down
MI_TRNSU, // transpose up

MI_VEL_x 1-10
MIDI_VELOCITY_MIN = MI_VEL_1,
MIDI_VELOCITY_MAX = MI_VEL_9,
MI_VELD, // velocity down
MI_VELU, // velocity up

MI_CHx 1-16
MIDI_CHANNEL_MIN = MI_CH1
MIDI_CHANNEL_MAX = MI_CH16,
MI_CHD, // previous channel
MI_CHU, // next channel

MI_ALLOFF, // all notes off

MI_SUS, // sustain
MI_PORT, // portamento
MI_SOST, // sostenuto
MI_SOFT, // soft pedal
MI_LEG,  // legato

MI_MOD, // modulation
MI_MODSD, // decrease modulation speed
MI_MODSU, // increase modulation speed
#endif // MIDI_ADVANCED

-->
