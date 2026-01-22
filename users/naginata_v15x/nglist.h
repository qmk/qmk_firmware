#pragma once
#include QMK_KEYBOARD_H
#include "keystroke.h"

#define LIST_SIZE 10 // 集合の最大サイズ

typedef struct {
    Keystroke elements[LIST_SIZE];
    int size;
} NGList;

void initializeList(NGList *list);
bool addToList(NGList *list, Keystroke *);
bool addToListAt(NGList *list, Keystroke *, int idx);
int includeList(NGList *list, uint16_t keycode);
bool removeFromList(NGList *list, uint16_t keycode);
bool removeFromListAt(NGList *list, int idx);
