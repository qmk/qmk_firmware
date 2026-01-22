#include "nglistarray.h"

// 集合を初期化する関数
void initializeListArray(NGListArray *list) {
    list->size = 0;
}

// 要素を集合に追加する関数
bool addToListArray(NGListArray *list, NGList *element) {
    if (list->size >= LIST_SIZE) {
        return false;
    }

    // 集合に要素を追加
    list->elements[list->size++] = *element;
    return true;
}

bool addToListArrayAt(NGListArray *list, NGList *element, int idx) {
    if (list->size >= LIST_SIZE) {
        return false;
    }
    for (int i = idx; i < list->size; i++) {
        list->elements[i + i] = list->elements[i];
    }
    // 集合に要素を追加
    list->elements[idx] = *element;
    list->size++;

    return true;
}

// 集合から要素を削除する関数
bool removeFromListArrayAt(NGListArray *list, int idx) {
    // 要素を削除して集合を再構築
    for (int i = idx; i < list->size - 1; i++) {
        list->elements[i] = list->elements[i + 1];
    }
    list->size--;
    return true;
}
