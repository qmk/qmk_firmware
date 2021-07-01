enum encoder_state {
    ENCODER_VOLUME = 0,
    ENCODER_RGB_HUE,
    ENCODER_RGB_SAT,
    ENCODER_RGB_VAL,
    ENCODER_RGB_EFFECT_SPEED,
    ENCODER_RGB_EFFECT,
};

#define ENCODER_DEFAULT ENCODER_VOLUME

void volume_up(void);
void volume_down(void);
