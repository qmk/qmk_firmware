#include "crkbd.h"

char timelog[40] = {};
int last_time = 0;
int elapsed_time = 0;

void timelog_set(void)
{
  elapsed_time = timer_elapsed(last_time);
  last_time = timer_read();
  snprintf(timelog, sizeof(timelog), "lt:%5d, et:%5d", last_time, elapsed_time);
}

char *timelog_read(void)
{
  return timelog;
}
