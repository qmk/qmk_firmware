#include "spi_adv.h"

void spi_start_adv(void) {
    spi_start(SPI_SS_PIN, false, 3, 8);
}

void spi_write_adv(uint8_t reg_addr, uint8_t data) {
    spi_start_adv();
    //send address of the register, with MSBit = 1 to indicate it's a write
    spi_write(reg_addr | 0x80 );
    spi_write(data);

    // tSCLK-NCS for write operation
    wait_us(20);


    // tSWW/tSWR (=120us) minus tSCLK-NCS. Could be shortened, but is looks like a safe lower bound
    wait_us(100);
    spi_stop();
}

uint8_t spi_read_adv(uint8_t reg_addr) {
    spi_start_adv();
    // send adress of the register, with MSBit = 0 to indicate it's a read
    spi_write(reg_addr & 0x7f );
    uint8_t data = spi_read();

    // tSCLK-NCS for read operation is 120ns
    wait_us(1);

    //  tSRW/tSRR (=20us) minus tSCLK-NCS
    wait_us(19);

    spi_stop();
    return data;
}

__attribute__((unused))
config_pmw_t get_pmw_config(void) {
    uint8_t config_1 = spi_read_adv(REG_Configuration_I);
    return (config_pmw_t){ (config_1 & 0xFF) * 200 };
}

__attribute__((unused))
void pmw_set_config(config_pmw_t config) {
    uint8_t config_1 = (config.cpi / 200) & 0xFF;
    spi_write_adv(REG_Configuration_I, config_1);
    wait_ms(100);
}
