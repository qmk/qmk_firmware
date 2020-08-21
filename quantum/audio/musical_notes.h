/* Copyright 2016 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUSICAL_NOTES_H
#define MUSICAL_NOTES_H

// Tempo Placeholder
#ifndef TEMPO_DEFAULT
#    define TEMPO_DEFAULT 100
#endif

#define SONG(notes...) \
    { notes }

// Note Types
#define MUSICAL_NOTE(note, duration) \
    { (NOTE##note), duration }
#define BREVE_NOTE(note) MUSICAL_NOTE(note, 128)
#define WHOLE_NOTE(note) MUSICAL_NOTE(note, 64)
#define HALF_NOTE(note) MUSICAL_NOTE(note, 32)
#define QUARTER_NOTE(note) MUSICAL_NOTE(note, 16)
#define EIGHTH_NOTE(note) MUSICAL_NOTE(note, 8)
#define SIXTEENTH_NOTE(note) MUSICAL_NOTE(note, 4)

#define BREVE_DOT_NOTE(note) MUSICAL_NOTE(note, 128 + 64)
#define WHOLE_DOT_NOTE(note) MUSICAL_NOTE(note, 64 + 32)
#define HALF_DOT_NOTE(note) MUSICAL_NOTE(note, 32 + 16)
#define QUARTER_DOT_NOTE(note) MUSICAL_NOTE(note, 16 + 8)
#define EIGHTH_DOT_NOTE(note) MUSICAL_NOTE(note, 8 + 4)
#define SIXTEENTH_DOT_NOTE(note) MUSICAL_NOTE(note, 4 + 2)

// Note Type Shortcuts
#define M__NOTE(note, duration) MUSICAL_NOTE(note, duration)
#define B__NOTE(n) BREVE_NOTE(n)
#define W__NOTE(n) WHOLE_NOTE(n)
#define H__NOTE(n) HALF_NOTE(n)
#define Q__NOTE(n) QUARTER_NOTE(n)
#define E__NOTE(n) EIGHTH_NOTE(n)
#define S__NOTE(n) SIXTEENTH_NOTE(n)
#define BD_NOTE(n) BREVE_DOT_NOTE(n)
#define WD_NOTE(n) WHOLE_DOT_NOTE(n)
#define HD_NOTE(n) HALF_DOT_NOTE(n)
#define QD_NOTE(n) QUARTER_DOT_NOTE(n)
#define ED_NOTE(n) EIGHTH_DOT_NOTE(n)
#define SD_NOTE(n) SIXTEENTH_DOT_NOTE(n)

// Note Timbre
// Changes how the notes sound
#define TIMBRE_12 0.125f
#define TIMBRE_25 0.250f
#define TIMBRE_50 0.500f
#define TIMBRE_75 0.750f
#ifndef TIMBRE_DEFAULT
#    define TIMBRE_DEFAULT TIMBRE_50
#endif

// Notes - # = Octave

#ifdef __arm__
#    define NOTE_REST 1.00f
#else
#    define NOTE_REST 0.00f
#endif

/* These notes are currently bugged
#define NOTE_C0          16.35f
#define NOTE_CS0         17.32f
#define NOTE_D0          18.35f
#define NOTE_DS0         19.45f
#define NOTE_E0          20.60f
#define NOTE_F0          21.83f
#define NOTE_FS0         23.12f
#define NOTE_G0          24.50f
#define NOTE_GS0         25.96f
#define NOTE_A0          27.50f
#define NOTE_AS0         29.14f
#define NOTE_B0          30.87f
#define NOTE_C1          32.70f
#define NOTE_CS1         34.65f
#define NOTE_D1          36.71f
#define NOTE_DS1         38.89f
#define NOTE_E1          41.20f
#define NOTE_F1          43.65f
#define NOTE_FS1         46.25f
#define NOTE_G1          49.00f
#define NOTE_GS1         51.91f
#define NOTE_A1          55.00f
#define NOTE_AS1         58.27f
*/

#define NOTE_B1 61.74f
#define NOTE_C2 65.41f
#define NOTE_CS2 69.30f
#define NOTE_D2 73.42f
#define NOTE_DS2 77.78f
#define NOTE_E2 82.41f
#define NOTE_F2 87.31f
#define NOTE_FS2 92.50f
#define NOTE_G2 98.00f
#define NOTE_GS2 103.83f
#define NOTE_A2 110.00f
#define NOTE_AS2 116.54f
#define NOTE_B2 123.47f
#define NOTE_C3 130.81f
#define NOTE_CS3 138.59f
#define NOTE_D3 146.83f
#define NOTE_DS3 155.56f
#define NOTE_E3 164.81f
#define NOTE_F3 174.61f
#define NOTE_FS3 185.00f
#define NOTE_G3 196.00f
#define NOTE_GS3 207.65f
#define NOTE_A3 220.00f
#define NOTE_AS3 233.08f
#define NOTE_B3 246.94f
#define NOTE_C4 261.63f
#define NOTE_CS4 277.18f
#define NOTE_D4 293.66f
#define NOTE_DS4 311.13f
#define NOTE_E4 329.63f
#define NOTE_F4 349.23f
#define NOTE_FS4 369.99f
#define NOTE_G4 392.00f
#define NOTE_GS4 415.30f
#define NOTE_A4 440.00f
#define NOTE_AS4 466.16f
#define NOTE_B4 493.88f
#define NOTE_C5 523.25f
#define NOTE_CS5 554.37f
#define NOTE_D5 587.33f
#define NOTE_DS5 622.25f
#define NOTE_E5 659.26f
#define NOTE_F5 698.46f
#define NOTE_FS5 739.99f
#define NOTE_G5 783.99f
#define NOTE_GS5 830.61f
#define NOTE_A5 880.00f
#define NOTE_AS5 932.33f
#define NOTE_B5 987.77f
#define NOTE_C6 1046.50f
#define NOTE_CS6 1108.73f
#define NOTE_D6 1174.66f
#define NOTE_DS6 1244.51f
#define NOTE_E6 1318.51f
#define NOTE_F6 1396.91f
#define NOTE_FS6 1479.98f
#define NOTE_G6 1567.98f
#define NOTE_GS6 1661.22f
#define NOTE_A6 1760.00f
#define NOTE_AS6 1864.66f
#define NOTE_B6 1975.53f
#define NOTE_C7 2093.00f
#define NOTE_CS7 2217.46f
#define NOTE_D7 2349.32f
#define NOTE_DS7 2489.02f
#define NOTE_E7 2637.02f
#define NOTE_F7 2793.83f
#define NOTE_FS7 2959.96f
#define NOTE_G7 3135.96f
#define NOTE_GS7 3322.44f
#define NOTE_A7 3520.00f
#define NOTE_AS7 3729.31f
#define NOTE_B7 3951.07f
#define NOTE_C8 4186.01f
#define NOTE_CS8 4434.92f
#define NOTE_D8 4698.64f
#define NOTE_DS8 4978.03f
#define NOTE_E8 5274.04f
#define NOTE_F8 5587.65f
#define NOTE_FS8 5919.91f
#define NOTE_G8 6271.93f
#define NOTE_GS8 6644.88f
#define NOTE_A8 7040.00f
#define NOTE_AS8 7458.62f
#define NOTE_B8 7902.13f

// Flat Aliases
#define NOTE_DF0 NOTE_CS0
#define NOTE_EF0 NOTE_DS0
#define NOTE_GF0 NOTE_FS0
#define NOTE_AF0 NOTE_GS0
#define NOTE_BF0 NOTE_AS0
#define NOTE_DF1 NOTE_CS1
#define NOTE_EF1 NOTE_DS1
#define NOTE_GF1 NOTE_FS1
#define NOTE_AF1 NOTE_GS1
#define NOTE_BF1 NOTE_AS1
#define NOTE_DF2 NOTE_CS2
#define NOTE_EF2 NOTE_DS2
#define NOTE_GF2 NOTE_FS2
#define NOTE_AF2 NOTE_GS2
#define NOTE_BF2 NOTE_AS2
#define NOTE_DF3 NOTE_CS3
#define NOTE_EF3 NOTE_DS3
#define NOTE_GF3 NOTE_FS3
#define NOTE_AF3 NOTE_GS3
#define NOTE_BF3 NOTE_AS3
#define NOTE_DF4 NOTE_CS4
#define NOTE_EF4 NOTE_DS4
#define NOTE_GF4 NOTE_FS4
#define NOTE_AF4 NOTE_GS4
#define NOTE_BF4 NOTE_AS4
#define NOTE_DF5 NOTE_CS5
#define NOTE_EF5 NOTE_DS5
#define NOTE_GF5 NOTE_FS5
#define NOTE_AF5 NOTE_GS5
#define NOTE_BF5 NOTE_AS5
#define NOTE_DF6 NOTE_CS6
#define NOTE_EF6 NOTE_DS6
#define NOTE_GF6 NOTE_FS6
#define NOTE_AF6 NOTE_GS6
#define NOTE_BF6 NOTE_AS6
#define NOTE_DF7 NOTE_CS7
#define NOTE_EF7 NOTE_DS7
#define NOTE_GF7 NOTE_FS7
#define NOTE_AF7 NOTE_GS7
#define NOTE_BF7 NOTE_AS7
#define NOTE_DF8 NOTE_CS8
#define NOTE_EF8 NOTE_DS8
#define NOTE_GF8 NOTE_FS8
#define NOTE_AF8 NOTE_GS8
#define NOTE_BF8 NOTE_AS8

#endif
