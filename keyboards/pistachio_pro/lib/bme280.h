#pragma once

void bme280_init(void);
void bme280_exec(void);
double bme280_getTemp(void);
double bme280_getPress(void);
double bme280_getHum(void);
