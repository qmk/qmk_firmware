#include "smoothled.h"
#include "dmc12.h"
#include "quantum.h"

/* Light modes */
enum light_mode_enum { SMOOTHLED, DMC12, LIGHT_MODE_SIZE };
typedef enum light_mode_enum light_mode_t;

void set_light_mode(light_mode_t value, uint32_t color);
void process_light_mode(void);
void update_light_mode(uint32_t color);
void next_light_mode(uint32_t color);
