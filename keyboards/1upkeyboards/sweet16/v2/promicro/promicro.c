#include "promicro.h"
#include "encoder.h"

#ifdef ENCODER_ENABLED
bool encoder_update_kb(uint8_t index, bool clockwise) {
    return encoder_update_user(index, clockwise);
}
#endif
