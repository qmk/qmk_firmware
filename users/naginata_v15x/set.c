#include "set.h"

// 集合を初期化する関数
void initializeSet(Set *set) {
    set->size = 0;
}

// 要素を集合に追加する関数
bool addToSet(Set *set, uint16_t element) {
    if (set->size >= SET_SIZE) {
        return false;
    }

    // 重複要素をチェック
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            return false;
        }
    }

    // 集合に要素を追加
    set->elements[set->size++] = element;
    return true;
}

int includeSet(Set *set, uint16_t element) {
    // 要素のインデックスを見つける
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            return i;
            break;
        }
    }

    return -1;
}

// 集合から要素を削除する関数
bool removeFromSet(Set *set, uint16_t element) {
    int foundIndex = includeSet(set, element);

    if (foundIndex == -1) {
        return false;
    }

    // 要素を削除して集合を再構築
    for (int i = foundIndex; i < set->size - 1; i++) {
        set->elements[i] = set->elements[i + 1];
    }
    set->size--;
    return true;
}
