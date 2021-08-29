#pragma once

#include "HT16K33_GFX.h"
#include <string.h>

#define DISP_MODE_SCROLL    0
#define DISP_MODE_BOUNCE    1
#define DISP_MODE_PUSH      2

#define BLANK "   "

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

typedef struct animation_t {
    uint8_t mode : 7;
    uint8_t enabled: 1;
    int8_t pos : 8;
    int8_t dir : 3;
    uint16_t speed : 13;
    uint16_t delay_timer : 16;
    HT16K33 *disp;
    char *message;
} animation_t;

animation_t *newAnimation (HT16K33 *disp) {
  animation_t *animation = malloc(sizeof(animation_t));
    if (animation == NULL)
        return NULL;

    animation->mode = DISP_MODE_SCROLL;
    animation->enabled = false;
    animation->pos = 0;
    animation->dir = 1;
    animation->speed = 300;
    animation->delay_timer = timer_read();
    animation->disp = disp;
    animation->message = "";

    return animation;
}

__attribute__((weak)) void animation_done_cbk(animation_t *animation) {
}

void animation_scroll(animation_t *animation) {
    uint8_t target = min(animation->disp->size, strlen(animation->message));
    for (uint8_t n=0; n<target; n++) {
        HT16K33_dispASCII(animation->disp, n, animation->message[animation->pos+n]);
    }

    if ((animation->enabled) &&  (strlen(animation->message) > animation->disp->size)) {
        if (++animation->pos > strlen(animation->message) - animation->disp->size) {
            animation->pos = 0;
            animation_done_cbk(animation);
        }
    }

    HT16K33_refresh(animation->disp);
    animation->delay_timer = timer_read();
}

void animation_bounce(animation_t *animation) {
    uint8_t target = min(animation->disp->size, strlen(animation->message));
    for (uint8_t n=0; n<target; n++) {
        HT16K33_dispASCII(animation->disp, n, animation->message[animation->pos+n]);
    }

    if ((animation->enabled) &&  (strlen(animation->message) > animation->disp->size)) {
        animation->pos += animation->dir;
        if (animation->pos < 0) {
            animation->dir = 1;
            animation->pos += animation->dir;
            animation_done_cbk(animation);
        }
        else if (animation->pos > strlen(animation->message) - animation->disp->size) {
            animation->dir = -1;
            animation->pos += animation->dir;
        }
    }

    HT16K33_refresh(animation->disp);
    animation->delay_timer = timer_read();
}

void _refresh(animation_t *animation, bool force) {
    if ((timer_elapsed(animation->delay_timer) > animation->speed) || force) {
        if (strlen(animation->message) > INT8_MAX) {
            // dprintf("Message too long! Max: %d\n", INT8_MAX);
            return;
        }

        switch (animation->mode) {

            case DISP_MODE_SCROLL:
            animation_scroll(animation);
            break;

            case DISP_MODE_BOUNCE:
            animation_bounce(animation);
            break;

            default:
            break;
        }
    }
}

void animation_refresh(animation_t *animation) {
    _refresh(animation, false);
}

void force_animation_refresh(animation_t *animation) {
    animation->pos = 0;
    animation->dir = 1;
    _refresh(animation, true);
}