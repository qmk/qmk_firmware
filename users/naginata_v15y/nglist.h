#pragma once
#include QMK_KEYBOARD_H

#define LIST_SIZE 5 // 集合の最大サイズ

typedef struct {
    uint16_t elements[LIST_SIZE];
    int size;
} NGList;

void initializeList(NGList *);
bool addToList(NGList *, uint16_t);
bool addToListAt(NGList *, uint16_t, int);
int includeList(NGList *, uint16_t);
bool removeFromList(NGList *, uint16_t);
bool removeFromListAt(NGList *, int);
void copyList(NGList *, NGList *);

bool compareList0(NGList *, uint16_t);
bool compareList01(NGList *, uint16_t, uint16_t);
