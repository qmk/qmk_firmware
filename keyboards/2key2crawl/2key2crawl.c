#include "2key2crawl.h"
#include "encoder.h"

void encoder_update_kb(int8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}
