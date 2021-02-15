#pragma once

// place overrides here
#ifdef V60_POLESTAR
#undef V60_POLESTAR
#endif
#undef USB_POLLING_INTERVAL_MS
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO
