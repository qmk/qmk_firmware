#include "fft.c"
#include "analog.h"

#define AUDIO_INPUT_PIN 8

#define STANDBY_ON_DELAY 250
#define STANDBY_OFF_DELAY  50
#define STANDBY_THRESHOLD 5

/* KICK LED */
#define KICK_BAND_FROM      1
#define KICK_BAND_TO        1
#define KICK_WINDOW_SIZE    10
#define KICK_COEFFICIENT    1.5
#define KICK_TH_WINDOW_SIZE 70
#define KICK_TH_COEFFICIENT 1.5
#define KICK_ABS_TH         24
#define KICK_ALPHA    ((float)2 / (1 + KICK_WINDOW_SIZE))
#define KICK_TH_ALPHA ((float)2 / (1 + KICK_TH_WINDOW_SIZE))

/* RGB LED */
#define BLUE_BAND_FROM    4
#define BLUE_BAND_TO      7
#define RED_BAND_FROM     8
#define RED_BAND_TO       24
#define GREEN_BAND_FROM   25
#define GREEN_BAND_TO     63
#define RGB_WINDOW_SIZE   40
#define RGB_THRESHOLD     55
#define BLUE_COEFFICIENT  1.30
#define RED_COEFFICIENT   1.10
#define GREEN_COEFFICIENT 1.15
#define RGB_ALPHA ((float)2 / (1 + RGB_WINDOW_SIZE))

#define min(A, B) ((A) < (B) ? (A) : (B))
#define max(A, B) ((A) > (B) ? (A) : (B))

float lightshow_amp = 1.0;

void lightshow_task (void) {
    static bool standby = true;
    static uint8_t standby_timer;
    static float kick, kick_average, red, green, blue;
    static LED_TYPE led[RGBLED_NUM];

    int8_t re[128], im[128];
    uint8_t i;
    int16_t t, maximum;
    uint16_t abs[128];

    /* collect 128 samples (-128~+128 each) */
    for (i = maximum = 0; i < 128; i++) {
        t = (analogRead(AUDIO_INPUT_PIN) - 512) * lightshow_amp;
        maximum = max(t, maximum);
        re[i] = (int8_t)t, im[i] = 0;
    }

    /* toggle standby-mode */
    if((!standby && maximum < STANDBY_THRESHOLD)
       || (standby && maximum >= STANDBY_THRESHOLD))
        standby_timer++;
    if((!standby && standby_timer >= STANDBY_ON_DELAY)
       || (standby && standby_timer >= STANDBY_OFF_DELAY))
        standby = !standby, standby_timer = 0;

    /* FFT (7 = log2(128)) */
    fix_fft(re, im, 7);

    /* calculate absolute values (64 = 128 / 2) */
    for(i = 0; i < 64; i++)
        abs[i] = (int16_t)re[i]*re[i] + (int16_t)im[i]*im[i];

    /* kick led */
    for(t = 0, i = KICK_BAND_FROM; i <= KICK_BAND_TO; i++) t += abs[i];
    kick_average = t * KICK_TH_ALPHA + kick_average * (1 - KICK_TH_ALPHA);
    t = t > kick_average * KICK_TH_COEFFICIENT && t > KICK_ABS_TH ? t * KICK_COEFFICIENT : 0;
    kick = t * KICK_ALPHA + kick * (1 - KICK_ALPHA);

    /* blue_led */
    for(t = 0, i = BLUE_BAND_FROM; i <= BLUE_BAND_TO; i++) t += abs[i];
    t = max((t - RGB_THRESHOLD) * BLUE_COEFFICIENT, 0);
    blue = t * RGB_ALPHA + blue * (1 - RGB_ALPHA);

    /* red_led */
    for(t = 0, i = RED_BAND_FROM; i <= RED_BAND_TO; i++) t += abs[i];
    t = max((t - RGB_THRESHOLD) * RED_COEFFICIENT, 0);
    red = t * RGB_ALPHA + red * (1 - RGB_ALPHA);

    /* green_led */
    for(t = 0, i = GREEN_BAND_FROM; i <= GREEN_BAND_TO; i++) t += abs[i];
    t = max((t - RGB_THRESHOLD) * GREEN_COEFFICIENT, 0);
    green = t * RGB_ALPHA + green * (1 - RGB_ALPHA);

    if (!standby) {
        /* backlight */
        setrgb(min(red, 255), min(green, 255), min(blue, 255), &led[0]);
        setrgb(min(red, 255), min(green, 255), min(blue, 255), &led[1]);
        setrgb(min(red, 255), min(green, 255), min(blue, 255), &led[2]);
        setrgb(min(red, 255), min(green, 255), min(blue, 255), &led[3]);
        /* underglow */
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[4]);
        setrgb(0, 0, min(blue, 255), &led[5]);
        setrgb(min(red, 255), 0, 0, &led[6]);
        setrgb(0, min(green, 255), 0, &led[7]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[8]);
        /* sideview (left) */
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[9]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[10]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[11]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[12]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[13]);
        /* sideview (right) */
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[14]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[15]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[16]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[17]);
        setrgb(min(kick, 255), min(kick, 255), min(kick, 255), &led[18]);
        /*  */
        ws2812_setleds(led, RGBLED_NUM);
    } else {
        rgblight_setrgb_range(255, 255, 255, 0, 4);
        rgblight_setrgb_range(0, 0, 0, 4, 9);
        rgblight_setrgb_range(0, 0, 0, 9, 19);
    }
}
