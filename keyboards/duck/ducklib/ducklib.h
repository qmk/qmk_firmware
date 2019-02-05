#pragma once

#define RES 6000

#define NS_PER_SEC (1000000000L)
#define CYCLES_PER_SEC (F_CPU)
#define NS_PER_CYCLE (NS_PER_SEC / CYCLES_PER_SEC)
#define NS_TO_CYCLES(n) ((n) / NS_PER_CYCLE)

enum Device {
  Device_PCBRGB,
  Device_STATUSLED
};

void show(void);

