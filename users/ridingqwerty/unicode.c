#include "unicode.h"

#ifdef UNICODEMAP_ENABLE
const uint32_t unicode_map[] PROGMEM = {
    FOREACH_UNICODE(UCM_ENTRY)
};
#endif
