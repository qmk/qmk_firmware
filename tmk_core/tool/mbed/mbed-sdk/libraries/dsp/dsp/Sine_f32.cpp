/* mbed Microcontroller Library
 * Copyright (c) 2006-2012 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "Sine_f32.h"
#include "math_helper.h"

#define RAD_2PI         (2. * PI)

namespace dsp {

Sine_f32::Sine_f32(uint32_t frequency, uint32_t sample_rate, float32_t amplitude, float32_t phase, uint32_t block_size) {
    _dx = RAD_2PI * ((float32_t)frequency / (float32_t)sample_rate);
    _amplitude = amplitude;
    _x = phase;
    _block_size = block_size;
}

void Sine_f32::process(float32_t *sgn_in, float32_t *sgn_out) {
    for (uint32_t i=0; i<_block_size; i++) {
        *sgn_out = *sgn_in + (_amplitude * arm_sin_f32(_x));
        sgn_in++; sgn_out++;
        _x += _dx;
    }
}

void Sine_f32::generate(float32_t *sgn) {
    for (uint32_t i=0; i<_block_size; i++) {
        *sgn = (_amplitude * arm_sin_f32(_x));
        sgn++;
        _x += _dx;
    }
}

void Sine_f32::reset(void) {
    _x = 0.0f;
}

}
