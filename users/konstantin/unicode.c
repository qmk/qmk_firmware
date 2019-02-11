#include "unicode.h"

#ifdef UNICODEMAP_ENABLE
  const uint32_t PROGMEM unicode_map[] = {
    FOREACH_UNICODE(X_ENTRY)
  };
#endif
