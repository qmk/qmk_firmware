#include "crkbd.h"

char timelog[40] = {};
int last_time = 0;
int elapsed_time = 0;

void set_timelog(void)
{
  elapsed_time = timer_elapsed(last_time);
  last_time = timer_read();
  snprintf(timelog, sizeof(timelog), "lt:%5d, et:%5d", last_time, elapsed_time);
}

char *read_timelog(void)
{
  return timelog;
}
