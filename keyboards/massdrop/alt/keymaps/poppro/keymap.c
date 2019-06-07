#include "alt.h"

enum alt_keycodes {
    L_BRI = SAFE_RANGE, //LED Brightness Increase
    L_BRD,              //LED Brightness Decrease
    L_PTN,              //LED Pattern Select Next
    L_PTP,              //LED Pattern Select Previous
    L_PSI,              //LED Pattern Speed Increase
    L_PSD,              //LED Pattern Speed Decrease
    L_T_MD,             //LED Toggle Mode
    L_T_ONF,            //LED Toggle On / Off
    L_ON,               //LED On
    L_OFF,              //LED Off
    L_T_BR,             //LED Toggle Breath Effect
    L_T_SH,             //LED Toggle Shimmer Effect
    L_T_WV,             //LED Toggle Wave Effect
	L_T_PL,             //LED Toggle Pool Effect
	L_T_SC,				//LED Toggle Custom Color Schema
	L_T_CSTM,			//LED Toggle Custom Effect Handler
    L_T_PTD,            //LED Toggle Scrolling Pattern Direction
    U_T_AUTO,           //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,           //USB Toggle Automatic GCR control
	C1_U,				//LED Increment C1
	C1_D,				//LED Decrement C1
	C2_U,				//LED Increment C2
	C2_D,				//LED Decrement C2
	CS_R,				//LED Select Red
	CS_G,				//LED Select Green
	CS_B,				//LED Select Blue
    DBG_TOG,            //DEBUG Toggle On / Off
    DBG_MTRX,           //DEBUG Toggle Matrix Prints
    DBG_KBD,            //DEBUG Toggle Keyboard Prints
    DBG_MOU,            //DEBUG Toggle Mouse Prints
    MD_BOOT,            //Restart into bootloader after hold timeout
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, L_T_PL, \
        L_T_BR,  L_T_SH,   L_BRI,   L_T_WV,   CS_R, KC_TRNS, KC_TRNS, U_T_AUTO,U_T_AGCR,KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS,	  KC_TRNS, L_T_SC, \
        L_T_PTD, L_PTP,   L_BRD,   L_PTN,   KC_TRNS, CS_G, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         	 KC_TRNS, KC_VOLU, \
        C1_U, L_T_MD,  L_T_ONF, L_T_CSTM, KC_TRNS, CS_B, MD_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          	 KC_PGUP, KC_VOLD, \
        C1_D, C2_U, C2_D,                            KC_TRNS,                           			KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END \
    ),
    /*
    [X] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
    ),
    */
};

//effect variables & handlers

issi3733_led_t *end;
uint8_t active_key;
float prev[5][15];
float curr[5][15];

float led_animation_pool_matrix[ISSI3733_LED_COUNT];
int8_t pool_dir[ISSI3733_LED_COUNT];
int8_t pool_speed[ISSI3733_LED_COUNT];
float pool_mult;

uint8_t c_templates[][2][3] = {
{{255, 255, 0}, {0, 250, 200}}
{{24, 0, 204}, {255, 0, 118}},
{{57, 167, 142}, {57, 255, 50}}
{{24, 215, 204}, {255, 60, 118}},
};

uint8_t CS = 0; //current schema
uint8_t schemaCount = 3;

uint16_t count = 1;
uint8_t colorSelect = 0;

uint8_t led_pool_enabled = 1;
uint8_t led_wave_enabled = 1;

uint8_t getRow(uint8_t id) {
	if(id <= 15)
		return 0;
	if(id <= 30)
		return 1;
	if(id <= 44)
		return 2;
	if(id <= 58)
		return 3;
	return 4;
}

uint8_t getCol(uint8_t id) {
	if(id <= 15)//r1
		return id-1;
	if(id <= 30)//r2
		return (id-1)-15;
	if(id <= 42)//r3
		return (id-1)-30;
	if(id <= 44)//r3
		return id-30;
	if(id == 45) //lshift
		return id-45;
	if(id <= 58)//r4
		return id-44 ;
	if(id <= 61)
		return id-59;
	if(id == 62)
		return id+4-60;
	return id-53;
}

void wave_update(void) {
	if(count%750==0) {
		//update pos
		count = 1;
		for(uint8_t i = 0; i < 5; i++) {
			for(uint8_t j = 0; j < 15; j++) {
				float sum = 0;
				if(i-1>-1)
					sum += prev[i-1][j];
				if(i+1<5)
					sum += prev[i+1][j];
				if(j-1>-1)
					sum += prev[i][j-1];
				if(j+1 < 15)
					sum += prev[i][j+1];

				curr[i][j]=(sum/2)-curr[i][j];
				curr[i][j]=curr[i][j]*0.85;
			}
		}

		//swap buffers
		for(uint8_t i = 0; i < 5; i++) {
			for(uint8_t j = 0; j < 15; j++) {
				float tmp = prev[i][j];
				prev[i][j] = curr[i][j];
				curr[i][j] = tmp;
			}
		}
	}
	count++;
}

void run_pool(issi3733_led_t *cur, float* r, float* g, float* b) {
    uint8_t led_id = led_cur->id - 1;
    led_animation_pool_matrix[led_id] += ((float)pool_speed[led_id])/2.0 * (float)pool_dir[led_id];

    if (led_animation_pool_matrix[led_id] >= 255)
    	pool_dir[led_id] = -1;
    else if (led_animation_pool_matrix[led_id] <= 0)
    	pool_dir[led_id] = 1;

    pool_mult = (1.0/255.0) * led_animation_pool_matrix[led_id];
    if (pool_mult > 1) pool_mult = 1;
    else if (pool_mult < 0) pool_mult = 0;

    float wave_val = 0;
    if(cur->scan != 255)
    	wave_val = curr[getRow(cur->id)][getCol(cur->id)];

    float c1Mult = pool_mult-wave_val;
    float c2Mult = (1-wave_val)-pool_mult;

    //clamp values
    c1Mult = (c1Mult < 0) ? 0 : c1Mult;
    c1Mult = (c1Mult > 1) ? 1 : c1Mult;
    c2Mult = (c2Mult < 0) ? 0 : c2Mult;
    c2Mult = (c2Mult > 1) ? 1 : c2Mult;

    *r = c_templates[CS][0][0]*(c1Mult)+c_templates[CS][1][0]*(c2Mult);
    *g = c_templates[CS][0][1]*(c1Mult)+c_templates[CS][1][1]*(c2Mult);
    *b = c_templates[CS][0][2]*(c1Mult)+c_templates[CS][1][2]*(c2Mult);
}

void run_led(issi3733_led_t *cur, float* r,float* g, float* b) {
	if(led_pool_enabled)
		run_pool(cur, r, g, b);
}

//end effect handlers

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
	active_key = 0;
	end = led_map + ISSI3733_LED_COUNT;
	custom_led_run = &run_led;
	for(uint8_t i = 0; i < 5; i++) {
		for(uint8_t j = 0; j < 15; j++) {
			curr[i][j] = 0;
			prev[i][j] = 0;
		}
	}
	srand(1231);
	for(uint8_t i = 0; i < ISSI3733_LED_COUNT; i++) {
		uint8_t rn = rand() % 255;
		led_animation_pool_matrix[i] = rn;
		pool_speed[i] = rand()%3+1;
		if(i%2)
			pool_dir[i] = -1;
		else
			pool_dir[i] = 1;
	}
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
	if(led_wave_enabled)
		wave_update();
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case L_BRI:
            if (record->event.pressed) {
                if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
                else gcr_desired += LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
                else gcr_desired -= LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_PTN:
            if (record->event.pressed) {
                if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
                else led_animation_id++;
            }
            return false;
        case L_PTP:
            if (record->event.pressed) {
                if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
                else led_animation_id--;
            }
            return false;
        case L_PSI:
            if (record->event.pressed) {
                led_animation_speed += ANIMATION_SPEED_STEP;
            }
            return false;
        case L_PSD:
            if (record->event.pressed) {
                led_animation_speed -= ANIMATION_SPEED_STEP;
                if (led_animation_speed < 0) led_animation_speed = 0;
            }
            return false;
        case L_T_MD:
            if (record->event.pressed) {
                led_lighting_mode++;
                if (led_lighting_mode > LED_MODE_MAX_INDEX) led_lighting_mode = LED_MODE_NORMAL;
            }
            return false;
        case L_T_ONF:
            if (record->event.pressed) {
                led_enabled = !led_enabled;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_ON:
            if (record->event.pressed) {
                led_enabled = 1;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_OFF:
            if (record->event.pressed) {
                led_enabled = 0;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_T_BR:
            if (record->event.pressed) {
                led_animation_breathing = !led_animation_breathing;
                if (led_animation_breathing) {
                    gcr_breathe = gcr_desired;
                    led_animation_breathe_cur = BREATHE_MIN_STEP;
                    breathe_dir = 1;
                }
            }
            return false;
        case L_T_SH:
            if(record->event.pressed) {
              led_animation_shimmer = !led_animation_shimmer;
            }
            return false;
        case L_T_WV:
            if(record->event.pressed) {
            	led_wave_enabled = !led_wave_enabled;
            }
            return false;
        case L_T_PL:
			if(record->event.pressed) {
				led_pool_enabled = !led_pool_enabled;
			}
			return false;
        case L_T_CSTM:
        	if(record->event.pressed) {
        		custom_enabled = !custom_enabled;
        	}
        	return false;
        case L_T_PTD:
            if (record->event.pressed) {
                led_animation_direction = !led_animation_direction;
            }
            return false;
        case L_T_SC:
        	if (record->event.pressed) {
        		CS++;
        		CS%=schemaCount;
        	}
        	return false;
        case C1_U:
        	if (record->event.pressed) {
        		if(c_templates[CS][0][colorSelect] > 230)
        			c_templates[CS][0][colorSelect] = 255;
        		else
        			c_templates[CS][0][colorSelect]+=25;
        	}
        	return false;
        case C1_D:
        	if (record->event.pressed) {
        		if(c_templates[CS][0][colorSelect] < 25)
        			c_templates[CS][0][colorSelect] = 0;
        		else
        		  	c_templates[CS][0][colorSelect]-=25;
        	}
        	return false;
        case C2_U:
        	if (record->event.pressed) {
        		if(c_templates[CS][1][colorSelect] > 230)
         			c_templates[CS][1][colorSelect] = 255;
        		else
        			c_templates[CS][1][colorSelect]+=25;
        	}
        	return false;
        case C2_D:
        	if (record->event.pressed) {
        		if (record->event.pressed) {
        			if(c_templates[CS][1][colorSelect] < 25)
        				c_templates[CS][1][colorSelect] = 0;
        			else
        				c_templates[CS][1][colorSelect]-=25;
        		}
        	}
        	return false;
        case CS_R:
        	if (record->event.pressed) {
        		colorSelect = 0;
        	}
        	return false;
        case CS_G:
        	if (record->event.pressed) {
        		colorSelect = 1;
        	}
        	return false;
        case CS_B:
        	if (record->event.pressed) {
        		colorSelect = 2;
        	}
        	return false;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        default:
        	if(record->event.pressed && led_wave_enabled) {
        		uint8_t row = record->event.key.row;
        		uint8_t col = record->event.key.col;
        		curr[row][col] = 1;
        	}
            return true; //Process all other keycodes normally
    }
}
