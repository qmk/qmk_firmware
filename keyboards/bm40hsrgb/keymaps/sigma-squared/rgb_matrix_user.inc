// !!! DO NOT ADD #pragma once !!! //
//#include <print.h>

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(FACE_EFFECT)
RGB_MATRIX_EFFECT(kitt_effect)
RGB_MATRIX_EFFECT(FRACTAL)
RGB_MATRIX_EFFECT(FRACTAL_RGB)
RGB_MATRIX_EFFECT(REACTIVE_FACE)
RGB_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE_B)
RGB_MATRIX_EFFECT(pixelanim)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS



//-----------------------------------------------------------------------------------


//FACE EFFECT

//float wLEDs[54];
// e.g: A simple effect, self-contained within a single method
static bool FACE_EFFECT(effect_params_t* params) {

  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  float wLEDs[54] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1,  0  , 1, 0, 0, 0, 0,

      0,    0,    0,   0,   0,   0
  };

  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
  }
  for (uint16_t i = led_min; i < led_max; i++) {
    if (wLEDs[i] == 1 ){
      rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
    }
  }
  return led_max < DRIVER_LED_TOTAL;
}




//-----------------------------------------------------------------------------------


// KITT EFFECT

uint8_t k_led_count = 8;
uint8_t k_led_first = 14;
static uint8_t time_to_led(uint8_t time, uint8_t led_behind) {
    uint16_t led_time = k_led_count * time;
    uint16_t step = ((2 * k_led_count + (led_time / 128)) - led_behind) % (2 * k_led_count);
    uint8_t led;
    if (step < k_led_count) {
        led = step;
    } else {
        led = k_led_count - 1 - (step - k_led_count);
    }
    return led;
}

static HSV kitt_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    hsv.h = 0;
    hsv.s = 255;

    if (i >= k_led_first && i < k_led_first + k_led_count) {
        uint8_t j = i - k_led_first;
        if (j == time_to_led(time, 0)) {
            hsv.v = hsv.v;
        } else if (j == time_to_led(time, 1)) {
            hsv.v = hsv.v/2;
        } else if (j == time_to_led(time, 2)) {
            hsv.v = hsv.v/4;
        } else if (j == time_to_led(time, 3)) {
            hsv.v = hsv.v/8;
        } else {
            hsv.v = 0;
        }
    } else {
        hsv.v = 0;
    }

    return hsv;
}

bool kitt_effect(effect_params_t* params) {
    return effect_runner_i(params, &kitt_effect_math);
}




//-----------------------------------------------------------------------------------


//FRACTAL effect

uint32_t f_timer = 0;

uint8_t halfArray[6][4];
uint8_t fullArray[12][4];
uint8_t halfbottom[3];
uint8_t fullbottom[6];
uint8_t displArray[54];

static bool FRACTAL(effect_params_t* params) {
  uint16_t f_speed = (400 / rgb_matrix_config.speed) * 127;

  if (f_timer > g_rgb_timer) {
    return false;
  }

  if (params->init) {
    srand(g_rgb_timer);
  }

  HSV hsv  = rgb_matrix_config.hsv;
  RGB rgb = hsv_to_rgb(hsv);
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int j = led_min; j < led_max; j++) {
      int i = j > 41 ? j + 1 : j;
      if (displArray[i]) {
          rgb_matrix_set_color(j, rgb.r, rgb.g, rgb.b);
      } else {
          rgb_matrix_set_color(j, 0x00, 0x00, 0x00);
      }
  }

  if (led_max == DRIVER_LED_TOTAL) {
    f_timer = g_rgb_timer + f_speed;

    // move columns
    for (uint8_t col = 5; col > 0; col--) {
        for (uint8_t row = 0; row < 4; row++) {
            halfArray[col][row] = halfArray[col-1][row];
        }
    }
    //bottom
    for (uint8_t col = 2; col > 0; col--) {
        halfbottom[col] = halfbottom[col-1];
    }



    // random fill first column
    for (uint8_t row = 0; row < 4; row++) {
      halfArray[0][row] = rand() % 2;
    }
    // bottom
    halfbottom[0] = rand() % 2;




    // transfer to big array
    for (uint8_t col = 0; col < 6; col++) {
        for (uint8_t row = 0; row < 4; row++){
            fullArray[5 - col][row] = halfArray[col][row];
            fullArray[6 + col][row] = halfArray[col][row];
        }
    }
    //bottom
    for (uint8_t col = 0; col < 3; col++){
      fullbottom[2 - col] = halfbottom[col];
      fullbottom[3 + col] = halfbottom[col];
    }



    // transfer to matrix array
    uint8_t k = 0;
    for (uint8_t row = 0; row < 4; row++) {
        for (uint8_t col = 0; col < 12; col++) {
              displArray[k] = fullArray[col][row];
              k++;
        }
    }
    //bottom
    uint8_t l = 48;
    for (uint8_t col = 0; col < 6; col++) {
        displArray[l] = fullbottom[col];
        l++;
    }
  }

  return led_max < DRIVER_LED_TOTAL;
}


//-----------------------------------------------------------------------------------


//FRACTAL RGB

uint32_t frgb_timer = 0;

uint8_t rgb_halfArray[6][4];
uint8_t rgb_fullArray[12][4];
uint8_t rgb_halfbottom[3];
uint8_t rgb_fullbottom[6];
uint8_t rgb_displArray[54];

static bool FRACTAL_RGB(effect_params_t* params) {
  uint16_t frgb_speed = (400 / rgb_matrix_config.speed) * 127;

  if (frgb_timer > g_rgb_timer) {
    return false;
  }

  if (params->init) {
    srand(g_rgb_timer);
  }
/*
  HSV hsv  = rgb_matrix_config.hsv;
  hsv.h += frgb_timer;
  RGB rgb = hsv_to_rgb(hsv);
*/
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int j = led_min; j < led_max; j++) {
      int i = j > 41 ? j + 1 : j;
      if (rgb_displArray[i]) {
          HSV hsv  = rgb_matrix_config.hsv;
          //hsv.h += g_led_config.point[i].x * 2 + g_rgb_timer/frgb_speed;
          hsv.h += g_led_config.point[i].x;
          RGB rgb = hsv_to_rgb(hsv);
          rgb_matrix_set_color(j, rgb.r, rgb.g, rgb.b);
      } else {
          rgb_matrix_set_color(j, 0x00, 0x00, 0x00);
      }
  }

  if (led_max == DRIVER_LED_TOTAL) {
    frgb_timer = g_rgb_timer + frgb_speed;

    // move columns
    for (uint8_t col = 5; col > 0; col--) {
        for (uint8_t row = 0; row < 4; row++) {
            rgb_halfArray[col][row] = rgb_halfArray[col-1][row];
        }
    }
    //bottom
    for (uint8_t col = 2; col > 0; col--) {
        rgb_halfbottom[col] = rgb_halfbottom[col-1];
    }



    // random fill first column
    for (uint8_t row = 0; row < 4; row++) {
      rgb_halfArray[0][row] = rand() % 2;
    }
    // bottom
    rgb_halfbottom[0] = rand() % 2;




    // transfer to big array
    for (uint8_t col = 0; col < 6; col++) {
        for (uint8_t row = 0; row < 4; row++){
            rgb_fullArray[5 - col][row] = rgb_halfArray[col][row];
            rgb_fullArray[6 + col][row] = rgb_halfArray[col][row];
        }
    }
    //bottom
    for (uint8_t col = 0; col < 3; col++){
      rgb_fullbottom[2 - col] = rgb_halfbottom[col];
      rgb_fullbottom[3 + col] = rgb_halfbottom[col];
    }



    // transfer to matrix array
    uint8_t k = 0;
    for (uint8_t row = 0; row < 4; row++) {
        for (uint8_t col = 0; col < 12; col++) {
              rgb_displArray[k] = rgb_fullArray[col][row];
              k++;
        }
    }
    //bottom
    uint8_t l = 48;
    for (uint8_t col = 0; col < 6; col++) {
        rgb_displArray[l] = rgb_fullbottom[col];
        l++;
    }
  }

  return led_max < DRIVER_LED_TOTAL;
}



//-----------------------------------------------------------------------------------

//REACTIVE FACE

static HSV REACTIVE_FACE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick + dist * 5;
    if (effect > 255) effect = 255;
    hsv.v = qadd8(hsv.v, 255 - effect);
    return hsv;
}

bool REACTIVE_FACE(effect_params_t* params) {
  /*RGB_MATRIX_USE_LIMITS(led_min, led_max);
  float whLEDs[54] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1,  0  , 1, 0, 0, 0, 0,

      0,    0,    0,   0,   0,   0
  };

  for (uint16_t i = led_min; i < led_max; i++) {
    if (whLEDs[i] == 1 ){
      rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
    }
  };
*/

  rgb_matrix_set_color(3, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(8, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(13, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(14, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(15, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(20, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(21, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(22, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(29, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(30, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(40, 0xff, 0xff, 0xff);
  rgb_matrix_set_color(42, 0xff, 0xff, 0xff);


  return effect_runner_reactive_splash(0, params, &REACTIVE_FACE_math);
  //rgb_matrix_set_color(15, 0xff, 0xff, 0xff);

}

//==============================================================================================

// Bottom Reactive

static HSV SOLID_REACTIVE_SIMPLE_B_math(HSV hsv, uint16_t offset) {
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

bool SOLID_REACTIVE_SIMPLE_B(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  HSV hsv  = rgb_matrix_config.hsv;
  RGB rgb = hsv_to_rgb(hsv);

  effect_runner_reactive(params, &SOLID_REACTIVE_SIMPLE_B_math);
    for (uint16_t i = led_min; i < led_max; i++) {
      if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
      }
    }

  return led_max < DRIVER_LED_TOTAL;
}

//==============================================================================================

// PIXELANIM

int faceArray[3][54] = {
  { //00
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,  0  , 0, 0, 0, 0, 0,

      0,    0,    0,   0,   0,   0
  },
  { //01
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0,  0  , 0, 0, 0, 0, 0,

      0,    0,    0,   0,   0,   0
  },
  { //02
    0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0,  0  , 0, 0, 0, 0, 0,

      0,    0,    0,   0,   0,   0
  }
};

uint32_t p_timer = 0;
uint8_t c_frame = 0;

static bool pixelanim(effect_params_t* params) {
  if (p_timer > g_rgb_timer) {
    return false;
  }

  HSV hsv  = rgb_matrix_config.hsv;
  RGB rgb = hsv_to_rgb(hsv);
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int j = led_min; j < led_max; j++) {
      if (faceArray[c_frame][j]) {
          rgb_matrix_set_color(j, rgb.r, rgb.g, rgb.b);
      } else {
          rgb_matrix_set_color(j, 0x00, 0x00, 0x00);
      }
  }

  if (led_max == DRIVER_LED_TOTAL) {
    p_timer = g_rgb_timer + 400;
    c_frame = c_frame == 2 ? 0 : c_frame + 1;
    dprintf("c_frame = %d\n", c_frame);
  }

  return led_max < DRIVER_LED_TOTAL;
}



#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
