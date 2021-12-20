/* Identify this digitizer as a less generic device */
#define DIGITIZER_USAGE_ID DIG_TOUCH_SCREEN

/* Set x/y resolution to match desired screen aspect ratio */
#define DIGITIZER_MAX_X 2560
#define DIGITIZER_MAX_Y 1440

/* Jitter x/y to simulate more realistic touch events for the OS */
#define DIGITIZER_FUZZ
