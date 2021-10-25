// Copyright 2021 Victor Toni (@vitoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "utils.h"

#include <lib/lib8tion/lib8tion.h>

/**
* @brief Changes `*value` to `new_value`.
* @param[in,out] value      Pointer to variable to be changed.
* @param[in]     new_value  Value to be changed.
* @param[in,out] changed    Flag indicating `*value` and `new_value` were different.
*/
void update_value(uint8_t *value, const uint8_t new_value, bool *changed) {
    if (new_value != (*value)) {
        (*changed) = true;
        (*value) = new_value;
    }
}

/**
* @brief Checks whether a value is in the given range.
* @param[in] value      Value to be checked.
* @param[in] range_min  Lower bound of range (inclusive).
* @param[in] range_max  Upper bound of range (inclusive).
* @return `true` if (range_min <= value <= range_max), `false` otherwise
*/
bool in_range(const uint8_t value, const uint8_t range_min, const uint8_t range_max) {
    return range_min <= value && value <= range_max;
}

/**
* @brief Calculates the sine value based on sin8() and scales it to the given range (unsigned).
*
* Table of values for unscaled sin8() eg. a theta of 0 results to 128 and a theta of 255 (240+15) results to 125.
        0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    +----------------------------------------------------------------
   0: 128 131 134 137 140 143 146 149 152 155 158 161 164 167 170 173
  16: 177 179 182 184 187 189 192 194 197 200 202 205 207 210 212 215
  32: 218 219 221 223 224 226 228 229 231 233 234 236 238 239 241 243
  48: 245 245 246 246 247 248 248 249 250 250 251 251 252 253 253 254
  64: 255 254 253 253 252 251 251 250 250 249 248 248 247 246 246 245
  80: 245 243 241 239 238 236 234 233 231 229 228 226 224 223 221 219
  96: 218 215 212 210 207 205 202 200 197 194 192 189 187 184 182 179
 112: 177 173 170 167 164 161 158 155 152 149 146 143 140 137 134 131
 128: 128 125 122 119 116 113 110 107 104 101  98  95  92  89  86  83
 144:  79  77  74  72  69  67  64  62  59  56  54  51  49  46  44  41
 160:  38  37  35  33  32  30  28  27  25  23  22  20  18  17  15  13
 176:  11  11  10  10   9   8   8   7   6   6   5   5   4   3   3   2
 192:   1   2   3   3   4   5   5   6   6   7   8   8   9  10  10  11
 208:  11  13  15  17  18  20  22  23  25  27  28  30  32  33  35  37
 224:  38  41  44  46  49  51  54  56  59  62  64  67  69  72  74  77
 240:  79  83  86  89  92  95  98 101 104 107 110 113 116 119 122 125
*
* @param[in] theta      Angle (a full circle mapped to 0-255) used as input for sine calculation.
* @param[in] range_min  Lower bound of range (inclusive).
* @param[in] range_max  Upper bound of range (inclusive).
* @return Calculated sine value mapped to the given range.
*/
uint8_t scaled_sin(const uint8_t theta, const uint8_t range_min, const uint8_t range_max) {
    const uint8_t range = range_max - range_min;
    return scale8(sin8(theta), range) + range_min;
}

/**
* @brief Increases the given value until reaching range_max.
* The increments occur following an upwards sine wave (scaled from range_min to range_max).
* @param[in]        theta       Angle (a full circle mapped to 0-255) used as input for sine calculation.
* @param[in]        range_min   Lower bound of range (inclusive).
* @param[in]        range_max   Upper bound of range (inclusive).
* @param[in]        max_delta   Maximum delta between value and range_max (due to values being integers and eventually not fully matching).
* @param[in,out]    value       Reference of variable to be increased
* @return `true` if value and range_max are within a delta of 3 (chosen by fair dice rolling), `false` otherwise
* @see scaled_sin()
*/
bool scaled_sin_up(const uint8_t theta, const uint8_t range_min, const uint8_t range_max, const uint8_t max_delta, uint8_t *value) {
    // ensure upper range bound
    if (range_max <= (*value)) {
        (*value) = range_max;
        return true;
    }

    const uint8_t new_value = scaled_sin(theta, range_min, range_max);
    if (in_range(new_value, range_min, range_max) && (*value) < new_value) {
        (*value) = new_value;

        return range_max == (*value);
    }

    const uint8_t delta = range_max - (*value);
    if (delta <= max_delta) {
        (*value) = range_max;
    }

    return delta <= max_delta;
}

/**
* @brief Decreases the given value until reaching range_min.
* The decrements occur following an downwards sinus wave (scaled from range_min to range_max).
* @param[in]        theta       Angle (a full circle mapped to 0-255) used as input for sinus calculation.
* @param[in]        range_min   Lower bound of range (inclusive).
* @param[in]        range_max   Upper bound of range (inclusive).
* @param[in]        max_delta   Maximum delta between value and range_min (due to values being integers and eventually not fully matching).
* @param[in,out]    value       Reference of variable to be decreased
* @return `true` if value and range_max are within a delta of 3 (chosen by fair dice rolling), `false` otherwise
* @see scaled_sin()
*/
bool scaled_sin_down(const uint8_t theta, const uint8_t range_min, const uint8_t range_max, const uint8_t max_delta, uint8_t *value) {
    // ensure lower range bound
    if ((*value) <= range_min) {
        (*value) = range_min;
        return true;
    }

    const uint8_t new_value = scaled_sin(theta, range_min, range_max);
    if (in_range(new_value, range_min, range_max) && new_value < (*value)) {
        (*value) = new_value;

        return range_min == (*value);
    }

    const uint8_t delta = (*value) - range_min;
    if (delta <= max_delta) {
        (*value) = range_min;
    }

    return delta <= max_delta;
}
