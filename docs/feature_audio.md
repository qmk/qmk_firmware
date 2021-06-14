# Audio

Your keyboard can make sounds! If you've got a spare pin you can hook up a simple speaker and make it beep. You can use those beeps to indicate layer transitions, modifiers, special keys, or just to play some funky 8bit tunes.

To activate this feature, add `AUDIO_ENABLE = yes` to your `rules.mk`.

## AVR based boards
On Atmega32U4 based boards, up to two simultaneous tones can be rendered.
With one speaker connected to a PWM capable pin on PORTC driven by timer 3 and the other on one of the PWM pins on PORTB driven by timer 1.

The following pins can be configured as audio outputs in `config.h` - for one speaker set either one out of:

* `#define AUDIO_PIN C4`
* `#define AUDIO_PIN C5`
* `#define AUDIO_PIN C6`
* `#define AUDIO_PIN B5`
* `#define AUDIO_PIN B6`
* `#define AUDIO_PIN B7`

and *optionally*, for a second speaker, one of:
* `#define AUDIO_PIN_ALT B5`
* `#define AUDIO_PIN_ALT B6`
* `#define AUDIO_PIN_ALT B7`

### Wiring
per speaker is - for example with a piezo buzzer - the black lead to Ground, and the red lead connected to the selected AUDIO_PIN for the primary; and similarly with AUDIO_PIN_ALT for the secondary.


## ARM based boards
for more technical details, see the notes on [Audio driver](audio_driver.md).

<!-- because I'm not sure where to fit this in: https://waveeditonline.com/ -->
### DAC (basic)
Most STM32 MCUs have DAC peripherals, with a notable exception of the STM32F1xx series. Generally, the DAC peripheral drives pins A4 or A5. To enable DAC-based audio output on STM32 devices, add `AUDIO_DRIVER = dac_basic` to `rules.mk` and set in `config.h` either:

`#define AUDIO_PIN A4` or `#define AUDIO_PIN A5`

the other DAC channel can optionally be used with a secondary speaker, just set:

`#define AUDIO_PIN_ALT A4` or `#define AUDIO_PIN_ALT A5`

Do note though that the dac_basic driver is only capable of reproducing one tone per speaker/channel at a time, for more tones simultaneously, try the dac_additive driver.

#### Wiring:
for two piezos, for example configured as `AUDIO_PIN A4` and `AUDIO_PIN_ALT A5` would be: red lead to A4 and black to Ground, and similarly with the second one: A5 = red, and Ground = black

another alternative is to drive *one* piezo with both DAC pins - for an extra "push".
wiring red to A4 and black to A5 (or the other way round) and add `#define AUDIO_PIN_ALT_AS_NEGATIVE` to `config.h`

##### Proton-C Example:
The Proton-C comes (optionally) with one 'builtin' piezo, which is wired to A4+A5.
For this board `config.h` would include these defines:

```c
#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE
```

### DAC (additive)
Another option, besides dac_basic (which produces sound through a square-wave), is to use the DAC to do additive wave synthesis.
With a number of predefined wave-forms or by providing your own implementation to generate samples on the fly.
To use this feature set `AUDIO_DRIVER = dac_additive` in your `rules.mk`, and select in `config.h` EITHER `#define AUDIO_PIN A4` or `#define AUDIO_PIN A5`.

The used waveform *defaults* to sine, but others can be selected by adding one of the following defines to `config.h`:

* `#define AUDIO_DAC_SAMPLE_WAVEFORM_SINE`
* `#define AUDIO_DAC_SAMPLE_WAVEFORM_TRIANGLE`
* `#define AUDIO_DAC_SAMPLE_WAVEFORM_TRAPEZOID`
* `#define AUDIO_DAC_SAMPLE_WAVEFORM_SQUARE`

Should you rather choose to generate and use your own sample-table with the DAC unit, implement `uint16_t dac_value_generate(void)` with your keyboard - for an example implementation see keyboards/planck/keymaps/synth_sample or keyboards/planck/keymaps/synth_wavetable


### PWM (software)
if the DAC pins are unavailable (or the MCU has no usable DAC at all, like STM32F1xx); PWM can be an alternative.
Note that there is currently only one speaker/pin supported.

set in `rules.mk`:

`AUDIO_DRIVER = pwm_software` and in `config.h`: 
`#define AUDIO_PIN C13` (can be any pin) to have the selected pin output a pwm signal, generated from a timer callback which toggles the pin in software.

#### Wiring
the usual piezo wiring: red goes to the selected AUDIO_PIN, black goes to ground.

OR if you can chose to drive one piezo with two pins, for example `#define AUDIO_PIN B1`, `#define AUDIO_PIN_ALT B2` in `config.h`, with `#define AUDIO_PIN_ALT_AS_NEGATIVE` - then the red lead could go to B1, the black to B2.

### PWM (hardware)
STM32F1xx have to fall back to using PWM, but can do so in hardware; but again on currently only one speaker/pin.

`AUDIO_DRIVER = pwm_hardware` in `rules.mk`, and in `config.h`:
`#define AUDIO_PIN A8`
`#define AUDIO_PWM_DRIVER PWMD1`
`#define AUDIO_PWM_CHANNEL 1`
(as well as `#define AUDIO_PWM_PAL_MODE 42` if you are on STM32F2 or larger)
which will use Timer 1 to directly drive pin PA8 through the PWM hardware (TIM1_CH1 = PA8).
Should you want to use the pwm-hardware on another pin and timer - be ready to dig into the STM32 data-sheet to pick the right TIMx_CHy and pin-alternate function.


## Tone Multiplexing
Since most drivers can only render one tone per speaker at a time (with the one exception: arm dac-additive) there also exists a "workaround-feature" that does time-slicing/multiplexing - which does what the name implies: cycle through a set of active tones (e.g. when playing chords in Music Mode) at a given rate, and put one tone at a time out through the one/few speakers that are available.

To enable this feature, and configure a starting-rate, add the following defines to `config.h`:
```c
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10
```

The audio core offers interface functions to get/set/change the tone multiplexing rate from within `keymap.c`.


## Songs
There's a couple of different sounds that will automatically be enabled without any other configuration:
```
STARTUP_SONG // plays when the keyboard starts up (audio.c)
GOODBYE_SONG // plays when you press the RESET key (quantum.c)
AG_NORM_SONG // plays when you press AG_NORM (quantum.c)
AG_SWAP_SONG // plays when you press AG_SWAP (quantum.c)
CG_NORM_SONG // plays when you press CG_NORM (quantum.c)
CG_SWAP_SONG // plays when you press CG_SWAP (quantum.c)
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

* `AU_ON` - Turn Audio Feature on
* `AU_OFF` - Turn Audio Feature off
* `AU_TOG` - Toggle Audio Feature state

!> These keycodes turn all of the audio functionality on and off.  Turning it off means that audio feedback, audio clicky, music mode, etc. are disabled, completely.

## Tempo
the 'speed' at which SONGs are played is dictated by the set Tempo, which is measured in beats-per-minute. Note lengths are defined relative to that.
The initial/default tempo is set to 120 bpm, but can be configured by setting `TEMPO_DEFAULT` in `config.c`.
There is also a set of functions to modify the tempo from within the user/keymap code:
```c
void audio_set_tempo(uint8_t tempo);
void audio_increase_tempo(uint8_t tempo_change);
void audio_decrease_tempo(uint8_t tempo_change);
```

## ARM Audio Volume

For ARM devices, you can adjust the DAC sample values. If your board is too loud for you or your coworkers, you can set the max using `AUDIO_DAC_SAMPLE_MAX` in your `config.h`:

```c
#define AUDIO_DAC_SAMPLE_MAX 4095U
```
the DAC usually runs in 12Bit mode, hence a volume of 100% = 4095U

Note: this only adjusts the volume aka 'works' if you stick to WAVEFORM_SQUARE, since its samples are generated on the fly - any other waveform uses a hardcoded/precomputed sample-buffer.

## Voices
Aka "audio effects", different ones can be enabled by setting in `config.h` these defines:
`#define AUDIO_VOICES` to enable the feature, and `#define AUDIO_VOICE_DEFAULT something` to select a specific effect
for details see quantum/audio/voices.h and .c


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

The pitch standard (`PITCH_STANDARD_A`) is 440.0f by default - to change this, add something like this to your `config.h`:

    #define PITCH_STANDARD_A 432.0f

You can completely disable Music Mode as well. This is useful, if you're pressed for space on your controller.  To disable it, add this to your `config.h`:

    #define NO_MUSIC_MODE

### Music Mask

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

### Music Map

By default, the Music Mode uses the columns and row to determine the scale for the keys. For a board that uses a rectangular matrix that matches the keyboard layout, this is just fine.  However, for boards that use a more complicated matrix (such as the Planck Rev6, or many split keyboards) this would result in a very skewed experience.  

However, the Music Map option allows you to remap the scaling for the music mode, so it fits the layout, and is more natural. 

To enable this feature, add `#define MUSIC_MAP` to your `config.h` file, and then you will want to add a `uint8_t music_map` to your keyboard's `c` file, or your `keymap.c`.

```c
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_ortho_4x12(
	36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11
);
```

You will want to use whichever `LAYOUT` macro that your keyboard uses here.  This maps it to the correct key location.  Start in  the bottom left of the keyboard layout, and  move to the right, and then upwards.  Fill in all the entries until you have a complete matrix.  

You can look at the [Planck Keyboard](https://github.com/qmk/qmk_firmware/blob/e9ace1487887c1f8b4a7e8e6d87c322988bec9ce/keyboards/planck/planck.c#L24-L29) as an example of how to implement this. 

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
| `AUDIO_CLICKY_FREQ_MAX` | 1500.0f | Sets the highest frequency. Too high may result in coworkers attacking you. |
| `AUDIO_CLICKY_FREQ_FACTOR` | 1.18921f| Sets the stepping of UP/DOWN key codes.  This is a multiplicative factor.  The default steps the frequency up/down by a musical minor third.  |
| `AUDIO_CLICKY_FREQ_RANDOMNESS`     |  0.05f |  Sets a factor of randomness for the clicks, Setting this to `0f` will make each click identical, and `1.0f` will make this sound much like the 90's computer screen scrolling/typing effect. | 
| `AUDIO_CLICKY_DELAY_DURATION` | 1 | An integer note duration where 1 is 1/16th of the tempo, or a sixty-fourth note (see `quantum/audio/musical_notes.h` for implementation details). The main clicky effect will be delayed by this duration.  Adjusting this to values around 6-12 will help compensate for loud switches. |




## MIDI Functionality

See [MIDI](feature_midi.md)

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
