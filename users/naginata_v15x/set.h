#pragma once
#include QMK_KEYBOARD_H

#define SET_SIZE 10 // 集合の最大サイズ

typedef struct {
    uint16_t elements[SET_SIZE];
    int size;
} Set;

void initializeSet(Set *set);
bool addToSet(Set *set, uint16_t keycode);
int includeSet(Set *set, uint16_t keycode);
bool removeFromSet(Set *set, uint16_t keycode);
