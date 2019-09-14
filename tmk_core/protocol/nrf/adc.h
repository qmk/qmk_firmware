
/// Initializing ADC(for nrf51) or SADC(for nrf52)
void adc_init();

/// Measure VCC voltage
void adc_start();

/// Get VCC voltage in mV
uint16_t get_vcc();
