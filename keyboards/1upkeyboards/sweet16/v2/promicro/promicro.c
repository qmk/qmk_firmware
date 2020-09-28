#include "promicro.h"
#include "encoder.h"

#ifdef ENCODER_ENABLED
void encoder_update_kb(int8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}
#endif
