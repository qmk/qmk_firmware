#include "quantum.h"
#include "config.h"

#include <string.h>

typedef struct seq_t {
    const char *sequence;
    const char *result;
} seq_t;

extern seq_t seq_config[];
extern uint16_t seq_config_size;

void seq_start(void);
bool seq_feed(uint16_t keycode);
