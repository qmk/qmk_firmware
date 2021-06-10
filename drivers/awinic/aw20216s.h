/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
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

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct ag_led {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed)) aw_led;

#define SW_LINES_ENABLED_1_TO_1  0x0
#define SW_LINES_ENABLED_1_TO_2  0x1
#define SW_LINES_ENABLED_1_TO_3  0x2
#define SW_LINES_ENABLED_1_TO_4  0x3
#define SW_LINES_ENABLED_1_TO_5  0x4
#define SW_LINES_ENABLED_1_TO_6  0x5
#define SW_LINES_ENABLED_1_TO_7  0x6
#define SW_LINES_ENABLED_1_TO_8  0x7
#define SW_LINES_ENABLED_1_TO_9  0x8
#define SW_LINES_ENABLED_1_TO_10 0x9
#define SW_LINES_ENABLED_1_TO_11 0xA
#define SW_LINES_ENABLED_1_TO_12 0xB

extern const aw_led g_aw_leds[DRIVER_LED_TOTAL];

void AW20216S_enable(           int32_t csPin,
                                int32_t enablePin);
void AW20216S_init(             int32_t csPin,
                                uint8_t swLinesEnabled);
void AW20216S_set_color(        int     indexLED, 
                                uint8_t red, 
                                uint8_t green, 
                                uint8_t blue);
void AW20216S_set_color_all(    uint8_t red, 
                                uint8_t green, 
                                uint8_t blue);
void AW20216S_write_register(   int32_t csPin, 
                                uint8_t page, 
                                uint8_t reg, 
                                uint8_t data);
void AW20216S_write_pwm_buffer( int32_t csPin, 
                                uint8_t *pwm_buffer);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void AW20216S_update_pwm_buffers(   int32_t csPin, 
                                    uint8_t driver);

#define CS1_SW1 0
#define CS2_SW1 1
#define CS3_SW1 2
#define CS4_SW1 3
#define CS5_SW1 4
#define CS6_SW1 5
#define CS7_SW1 6
#define CS8_SW1 7
#define CS9_SW1 8
#define CS10_SW1 9
#define CS11_SW1 10
#define CS12_SW1 11
#define CS13_SW1 12
#define CS14_SW1 13
#define CS15_SW1 14
#define CS16_SW1 15
#define CS17_SW1 16
#define CS18_SW1 17
#define CS1_SW2 18
#define CS2_SW2 19
#define CS3_SW2 20
#define CS4_SW2 21
#define CS5_SW2 22
#define CS6_SW2 23
#define CS7_SW2 24
#define CS8_SW2 25
#define CS9_SW2 26
#define CS10_SW2 27
#define CS11_SW2 28
#define CS12_SW2 29
#define CS13_SW2 30
#define CS14_SW2 31
#define CS15_SW2 32
#define CS16_SW2 33
#define CS17_SW2 34
#define CS18_SW2 35
#define CS1_SW3 36
#define CS2_SW3 37
#define CS3_SW3 38
#define CS4_SW3 39
#define CS5_SW3 40
#define CS6_SW3 41
#define CS7_SW3 42
#define CS8_SW3 43
#define CS9_SW3 44
#define CS10_SW3 45
#define CS11_SW3 46
#define CS12_SW3 47
#define CS13_SW3 48
#define CS14_SW3 49
#define CS15_SW3 50
#define CS16_SW3 51
#define CS17_SW3 52
#define CS18_SW3 53
#define CS1_SW4 54
#define CS2_SW4 55
#define CS3_SW4 56
#define CS4_SW4 57
#define CS5_SW4 58
#define CS6_SW4 59
#define CS7_SW4 60
#define CS8_SW4 61
#define CS9_SW4 62
#define CS10_SW4 63
#define CS11_SW4 64
#define CS12_SW4 65
#define CS13_SW4 66
#define CS14_SW4 67
#define CS15_SW4 68
#define CS16_SW4 69
#define CS17_SW4 70
#define CS18_SW4 71
#define CS1_SW5 72
#define CS2_SW5 73
#define CS3_SW5 74
#define CS4_SW5 75
#define CS5_SW5 76
#define CS6_SW5 77
#define CS7_SW5 78
#define CS8_SW5 79
#define CS9_SW5 80
#define CS10_SW5 81
#define CS11_SW5 82
#define CS12_SW5 83
#define CS13_SW5 84
#define CS14_SW5 85
#define CS15_SW5 86
#define CS16_SW5 87
#define CS17_SW5 88
#define CS18_SW5 89
#define CS1_SW6 90
#define CS2_SW6 91
#define CS3_SW6 92
#define CS4_SW6 93
#define CS5_SW6 94
#define CS6_SW6 95
#define CS7_SW6 96
#define CS8_SW6 97
#define CS9_SW6 98
#define CS10_SW6 99
#define CS11_SW6 100
#define CS12_SW6 101
#define CS13_SW6 102
#define CS14_SW6 103
#define CS15_SW6 104
#define CS16_SW6 105
#define CS17_SW6 106
#define CS18_SW6 107
#define CS1_SW7 108
#define CS2_SW7 109
#define CS3_SW7 110
#define CS4_SW7 111
#define CS5_SW7 112
#define CS6_SW7 113
#define CS7_SW7 114
#define CS8_SW7 115
#define CS9_SW7 116
#define CS10_SW7 117
#define CS11_SW7 118
#define CS12_SW7 119
#define CS13_SW7 120
#define CS14_SW7 121
#define CS15_SW7 122
#define CS16_SW7 123
#define CS17_SW7 124
#define CS18_SW7 125
#define CS1_SW8 126
#define CS2_SW8 127
#define CS3_SW8 128
#define CS4_SW8 129
#define CS5_SW8 130
#define CS6_SW8 131
#define CS7_SW8 132
#define CS8_SW8 133
#define CS9_SW8 134
#define CS10_SW8 135
#define CS11_SW8 136
#define CS12_SW8 137
#define CS13_SW8 138
#define CS14_SW8 139
#define CS15_SW8 140
#define CS16_SW8 141
#define CS17_SW8 142
#define CS18_SW8 143
#define CS1_SW9 144
#define CS2_SW9 145
#define CS3_SW9 146
#define CS4_SW9 147
#define CS5_SW9 148
#define CS6_SW9 149
#define CS7_SW9 150
#define CS8_SW9 151
#define CS9_SW9 152
#define CS10_SW9 153
#define CS11_SW9 154
#define CS12_SW9 155
#define CS13_SW9 156
#define CS14_SW9 157
#define CS15_SW9 158
#define CS16_SW9 159
#define CS17_SW9 160
#define CS18_SW9 161
#define CS1_SW10 162
#define CS2_SW10 163
#define CS3_SW10 164
#define CS4_SW10 165
#define CS5_SW10 166
#define CS6_SW10 167
#define CS7_SW10 168
#define CS8_SW10 169
#define CS9_SW10 170
#define CS10_SW10 171
#define CS11_SW10 172
#define CS12_SW10 173
#define CS13_SW10 174
#define CS14_SW10 175
#define CS15_SW10 176
#define CS16_SW10 177
#define CS17_SW10 178
#define CS18_SW10 179
#define CS1_SW11 180
#define CS2_SW11 181
#define CS3_SW11 182
#define CS4_SW11 183
#define CS5_SW11 184
#define CS6_SW11 185
#define CS7_SW11 186
#define CS8_SW11 187
#define CS9_SW11 188
#define CS10_SW11 189
#define CS11_SW11 190
#define CS12_SW11 191
#define CS13_SW11 192
#define CS14_SW11 193
#define CS15_SW11 194
#define CS16_SW11 195
#define CS17_SW11 196
#define CS18_SW11 197
#define CS1_SW12 198
#define CS2_SW12 199
#define CS3_SW12 200
#define CS4_SW12 201
#define CS5_SW12 202
#define CS6_SW12 203
#define CS7_SW12 204
#define CS8_SW12 205
#define CS9_SW12 206
#define CS10_SW12 207
#define CS11_SW12 208
#define CS12_SW12 209
#define CS13_SW12 210
#define CS14_SW12 211
#define CS15_SW12 212
#define CS16_SW12 213
#define CS17_SW12 214
#define CS18_SW12 215
