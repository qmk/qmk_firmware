#include <avr/io.h>
#include <avr/interrupt.h>
#include "quantum.h"
#include "adns9800_srom_A4.h"
#include "../../lib/lufa/LUFA/Drivers/Peripheral/SPI.h"
#include "adns.h"

// registers
#define REG_Product_ID                           0x00
#define REG_Revision_ID                          0x01
#define REG_Motion                               0x02
#define REG_Delta_X_L                            0x03
#define REG_Delta_X_H                            0x04
#define REG_Delta_Y_L                            0x05
#define REG_Delta_Y_H                            0x06
#define REG_SQUAL                                0x07
#define REG_Pixel_Sum                            0x08
#define REG_Maximum_Pixel                        0x09
#define REG_Minimum_Pixel                        0x0a
#define REG_Shutter_Lower                        0x0b
#define REG_Shutter_Upper                        0x0c
#define REG_Frame_Period_Lower                   0x0d
#define REG_Frame_Period_Upper                   0x0e
#define REG_Configuration_I                      0x0f
#define REG_Configuration_II                     0x10
#define REG_Frame_Capture                        0x12
#define REG_SROM_Enable                          0x13
#define REG_Run_Downshift                        0x14
#define REG_Rest1_Rate                           0x15
#define REG_Rest1_Downshift                      0x16
#define REG_Rest2_Rate                           0x17
#define REG_Rest2_Downshift                      0x18
#define REG_Rest3_Rate                           0x19
#define REG_Frame_Period_Max_Bound_Lower         0x1a
#define REG_Frame_Period_Max_Bound_Upper         0x1b
#define REG_Frame_Period_Min_Bound_Lower         0x1c
#define REG_Frame_Period_Min_Bound_Upper         0x1d
#define REG_Shutter_Max_Bound_Lower              0x1e
#define REG_Shutter_Max_Bound_Upper              0x1f
#define REG_LASER_CTRL0                          0x20
#define REG_Observation                          0x24
#define REG_Data_Out_Lower                       0x25
#define REG_Data_Out_Upper                       0x26
#define REG_SROM_ID                              0x2a
#define REG_Lift_Detection_Thr                   0x2e
#define REG_Configuration_V                      0x2f
#define REG_Configuration_IV                     0x39
#define REG_Power_Up_Reset                       0x3a
#define REG_Shutdown                             0x3b
#define REG_Inverse_Product_ID                   0x3f
#define REG_Motion_Burst                         0x50
#define REG_SROM_Load_Burst                      0x62
#define REG_Pixel_Burst                          0x64

// pins
#define NCS 0

extern const uint16_t firmware_length;
extern const uint8_t firmware_data[];

enum motion_burst_property{
    motion = 0,
    observation,
    delta_x_l,
    delta_x_h,
    delta_y_l,
    delta_y_h,
    squal,
    pixel_sum,
    maximum_pixel,
    minimum_pixel,
    shutter_upper,
    shutter_lower,
    frame_period_upper,
    frame_period_lower,
    end_data
};

report_adns_t report;

void adns_begin(void){
    PORTB &= ~ (1 << NCS);
}

void adns_end(void){
    PORTB |= (1 << NCS);
}

void adns_write(uint8_t reg_addr, uint8_t data){

    adns_begin();

    //send address of the register, with MSBit = 1 to indicate it's a write
    SPI_TransferByte(reg_addr | 0x80 );
    SPI_TransferByte(data);

    // tSCLK-NCS for write operation
    wait_us(20);

    adns_end();

    // tSWW/tSWR (=120us) minus tSCLK-NCS. Could be shortened, but is looks like a safe lower bound
    wait_us(100);
}

uint8_t adns_read(uint8_t reg_addr){

    adns_begin();

    // send adress of the register, with MSBit = 0 to indicate it's a read
    SPI_TransferByte(reg_addr & 0x7f );
    uint8_t data = SPI_TransferByte(0);

    // tSCLK-NCS for read operation is 120ns
    wait_us(1);

    adns_end();

    //  tSRW/tSRR (=20us) minus tSCLK-NCS
    wait_us(19);

    return data;
}

void adns_init(void) {

    // interrupt 2
    EICRA &= ~(1 << 4);
    EICRA |= (1 << 5);
    EIMSK |= (1<<INT2);

    // mode 3
    SPI_Init(
        SPI_SPEED_FCPU_DIV_8 |
        SPI_ORDER_MSB_FIRST |
        SPI_SCK_LEAD_FALLING |
        SPI_SAMPLE_TRAILING |
        SPI_MODE_MASTER);

    // set B0 output
    DDRB |= (1 << 0);

    // reset serial port
    adns_end();
    adns_begin();
    adns_end();

    // reboot
    adns_write(REG_Power_Up_Reset, 0x5a);
    wait_ms(50);

    // read registers and discard
    adns_read(REG_Motion);
    adns_read(REG_Delta_X_L);
    adns_read(REG_Delta_X_H);
    adns_read(REG_Delta_Y_L);
    adns_read(REG_Delta_Y_H);

    // upload firmware

    // set the configuration_IV register in 3k firmware mode
    // bit 1 = 1 for 3k mode, other bits are reserved
    adns_write(REG_Configuration_IV, 0x02);

    // write 0x1d in SROM_enable reg for initializing
    adns_write(REG_SROM_Enable, 0x1d);

    // wait for more than one frame period
    // assume that the frame rate is as low as 100fps... even if it should never be that low
    wait_ms(10);

    // write 0x18 to SROM_enable to start SROM download
    adns_write(REG_SROM_Enable, 0x18);

    // write the SROM file (=firmware data)
    adns_begin();

    // write burst destination adress
    SPI_TransferByte(REG_SROM_Load_Burst | 0x80);
    wait_us(15);

    // send all bytes of the firmware
    unsigned char c;
    for(int i = 0; i < firmware_length; i++){
        c = (unsigned char)pgm_read_byte(firmware_data + i);
        SPI_TransferByte(c);
        wait_us(15);
    }

    adns_end();

    wait_ms(10);

    // enable laser(bit 0 = 0b), in normal mode (bits 3,2,1 = 000b)
    // reading the actual value of the register is important because the real
    // default value is different from what is said in the datasheet, and if you
    // change the reserved bytes (like by writing 0x00...) it would not work.
    uint8_t laser_ctrl0 = adns_read(REG_LASER_CTRL0);
    adns_write(REG_LASER_CTRL0, laser_ctrl0 & 0xf0);

    wait_ms(1);

    // set the configuration_I register to set the CPI
    // 0x01 = 50, minimum
    // 0x44 = 3400, default
    // 0x8e = 7100
    // 0xA4 = 8200, maximum
    adns_write(REG_Configuration_I, 0x04);

    wait_ms(100);
}

int16_t convertDeltaToInt(uint8_t high, uint8_t low){

    // join bytes into twos compliment
    uint16_t twos_comp = (high << 8) | low;

    // convert twos comp to int
    if ((twos_comp & 0x8000) != 0)
        return -1 * (~twos_comp + 1);

    return twos_comp;
}

report_adns_t adns_get_report(void) {
    return report;
}

void adns_clear_report(void) {
    report.x = 0;
    report.y = 0;
}

ISR(INT2_vect){

    adns_begin();

    SPI_TransferByte(REG_Motion_Burst & 0x7f);

    uint8_t burst_data[pixel_sum];

    for (int i = 0; i < pixel_sum; ++i)
        burst_data[i] = SPI_TransferByte(0);

    report.x += convertDeltaToInt(burst_data[delta_x_h], burst_data[delta_x_l]);
    report.y += convertDeltaToInt(burst_data[delta_y_h], burst_data[delta_y_l]);

    adns_end();
}
