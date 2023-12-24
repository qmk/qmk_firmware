#include "nglist.h"

// 集合を初期化する関数
void initializeList(NGList *list) {
    list->size = 0;
}

// 要素を集合に追加する関数
bool addToList(NGList *list, uint16_t element) {
    if (list->size >= LIST_SIZE) {
        return false;
    }

    // 集合に要素を追加
    list->elements[list->size++] = element;
    return true;
}

bool addToListAt(NGList *list, uint16_t element, int idx) {
    if (list->size >= LIST_SIZE) {
        return false;
    }
    for (int i = idx; i < list->size; i++) {
        list->elements[i + i] = list->elements[i];
    }
    // 集合に要素を追加
    list->elements[idx] = element;
    list->size++;

    return true;
}

int includeList(NGList *list, uint16_t element) {
    // 要素のインデックスを見つける
    for (int i = 0; i < list->size; i++) {
        if (list->elements[i] == element) {
            return i;
            break;
        }
    }

    return -1;
}

// 集合から要素を削除する関数
bool removeFromList(NGList *list, uint16_t element) {
    int foundIndex = includeList(list, element);

    if (foundIndex == -1) {
        return false;
    }

    // 要素を削除して集合を再構築
    for (int i = foundIndex; i < list->size - 1; i++) {
        list->elements[i] = list->elements[i + 1];
    }
    list->size--;
    return true;
}

void copyList(NGList *a, NGList *b) {
    initializeList(b);
    for (int i = 0; i < a->size; i++) {
        addToList(b, a->elements[i]);
    }
}

// 集合から要素を削除する関数
bool removeFromListAt(NGList *list, int idx) {
    // 要素を削除して集合を再構築
    for (int i = idx; i < list->size - 1; i++) {
        list->elements[i] = list->elements[i + 1];
    }
    list->size--;
    return true;
}

bool compareList0(NGList *list, uint16_t a) {
    if (list->elements[0] == a)
        return true;
    else
        return false;
}

bool compareList01(NGList *list, uint16_t a, uint16_t b) {
    if ((list->elements[0] == a && list->elements[1] == b) || (list->elements[0] == b && list->elements[1] == a))
        return true;
    else
        return false;
}
