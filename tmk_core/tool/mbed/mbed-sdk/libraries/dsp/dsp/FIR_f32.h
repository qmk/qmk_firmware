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
#ifndef FIR_F32_H
#define FIR_F32_H 

#include <stdint.h>
#include "arm_math.h"

namespace dsp {

template<uint16_t num_taps, uint32_t block_size=32>
class FIR_f32 {
public:
    FIR_f32(const float32_t *coeff) {
        arm_fir_init_f32(&fir, num_taps, (float32_t*)coeff, fir_state, block_size);
    }
    
    void process(float32_t *sgn_in, float32_t *sgn_out) {
        arm_fir_f32(&fir, sgn_in, sgn_out, block_size);
    }
    
    void reset(void) {
        memset(fir_state, 0, sizeof(fir_state));
    }

private:
    arm_fir_instance_f32 fir;
    float32_t fir_state[block_size + num_taps - 1];
};

}
#endif
