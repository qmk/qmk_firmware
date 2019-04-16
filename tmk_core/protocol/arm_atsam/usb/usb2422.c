/*
Copyright 2019 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "arm_atsam_protocol.h"
#include <string.h>

Usb2422 USB2422_shadow;
unsigned char i2c0_buf[34];

const uint16_t MFRNAME[] = { 'M','a','s','s','d','r','o','p',' ','I','n','c','.' }; //Massdrop Inc.
const uint16_t PRDNAME[] = { 'M','a','s','s','d','r','o','p',' ','H','u','b' }; //Massdrop Hub
#ifndef MD_BOOTLOADER
//Serial number reported stops before first found space character or at last found character
const uint16_t SERNAME[] = { 'U','n','a','v','a','i','l','a','b','l','e' }; //Unavailable
#else
//In production, this field is found, modified, and offset noted as the last 32-bit word in the bootloader space
//The offset allows the application to use the factory programmed serial (which may differ from the physical serial label)
//Serial number reported stops before first found space character or when max size is reached
__attribute__((__aligned__(4)))
const uint16_t SERNAME[BOOTLOADER_SERIAL_MAX_SIZE] = { 'M','D','H','U','B','B','O','O','T','L','0','0','0','0','0','0','0','0','0','0' };
//NOTE: Serial replacer will not write a string longer than given here as a precaution, so give enough
//      space as needed and adjust BOOTLOADER_SERIAL_MAX_SIZE to match amount given
#endif //MD_BOOTLOADER

uint8_t g_usb_host_port;

#ifndef MD_BOOTLOADER

uint8_t usb_gcr_auto;

#endif //MD_BOOTLOADER

void USB_write2422_block(void) {
    unsigned char *dest = i2c0_buf;
    unsigned char *src;
    unsigned char *base = (unsigned char *)&USB2422_shadow;

    DBGC(DC_USB_WRITE2422_BLOCK_BEGIN);

    for (src =  base; src < base + 256; src += 32) {
        dest[0] = src - base;
        dest[1] = 32;
        memcpy(&dest[2], src, 32);
        i2c0_transmit(USB2422_ADDR, dest, 34, 50000);
        SERCOM0->I2CM.CTRLB.bit.CMD = 0x03;
        while (SERCOM0->I2CM.SYNCBUSY.bit.SYSOP) { DBGC(DC_USB_WRITE2422_BLOCK_SYNC_SYSOP); }
        wait_us(100);
    }

    DBGC(DC_USB_WRITE2422_BLOCK_COMPLETE);
}

void USB2422_init(void) {
    Gclk *pgclk = GCLK;
    Mclk *pmclk = MCLK;
    Port *pport = PORT;
    Oscctrl *posc = OSCCTRL;
    Usb *pusb = USB;

    DBGC(DC_USB2422_INIT_BEGIN);

    while (adc_get(ADC_5V) < ADC_5V_V2C(ADC_5V_START_LEVEL)) { DBGC(DC_USB2422_INIT_WAIT_5V_LOW); }

    //setup peripheral and synchronous bus clocks to USB
    pgclk->PCHCTRL[10].bit.GEN = 0;
    pgclk->PCHCTRL[10].bit.CHEN = 1;
    pmclk->AHBMASK.bit.USB_ = 1;
    pmclk->APBBMASK.bit.USB_ = 1;

    //setup port pins for D-, D+, and SOF_1KHZ
    pport->Group[0].PMUX[12].reg = 0x77; //PA24, PA25, function column H for USB D-, D+
    pport->Group[0].PINCFG[24].bit.PMUXEN = 1;
    pport->Group[0].PINCFG[25].bit.PMUXEN = 1;
    pport->Group[1].PMUX[11].bit.PMUXE = 7; //PB22, function column H for USB SOF_1KHz output
    pport->Group[1].PINCFG[22].bit.PMUXEN = 1;

    //configure and enable DFLL for USB clock recovery mode at 48MHz
    posc->DFLLCTRLA.bit.ENABLE = 0;
    while (posc->DFLLSYNC.bit.ENABLE) { DBGC(DC_USB2422_INIT_OSC_SYNC_DISABLING); }
    while (posc->DFLLSYNC.bit.DFLLCTRLB) { DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_1); }
    posc->DFLLCTRLB.bit.USBCRM = 1;
    while (posc->DFLLSYNC.bit.DFLLCTRLB) { DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_2); }
    posc->DFLLCTRLB.bit.MODE = 1;
    while (posc->DFLLSYNC.bit.DFLLCTRLB) { DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_3); }
    posc->DFLLCTRLB.bit.QLDIS = 0;
    while (posc->DFLLSYNC.bit.DFLLCTRLB) { DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLCTRLB_4); }
    posc->DFLLCTRLB.bit.CCDIS = 1;
    posc->DFLLMUL.bit.MUL = 0xBB80; //4800 x 1KHz
    while (posc->DFLLSYNC.bit.DFLLMUL) { DBGC(DC_USB2422_INIT_OSC_SYNC_DFLLMUL); }
    posc->DFLLCTRLA.bit.ENABLE = 1;
    while (posc->DFLLSYNC.bit.ENABLE) { DBGC(DC_USB2422_INIT_OSC_SYNC_ENABLING); }

    pusb->DEVICE.CTRLA.bit.SWRST = 1;
    while (pusb->DEVICE.SYNCBUSY.bit.SWRST) { DBGC(DC_USB2422_INIT_USB_SYNC_SWRST); }
    while (pusb->DEVICE.CTRLA.bit.SWRST) { DBGC(DC_USB2422_INIT_USB_WAIT_SWRST); }
    //calibration from factory presets
    pusb->DEVICE.PADCAL.bit.TRANSN = (USB_FUSES_TRANSN_ADDR >> USB_FUSES_TRANSN_Pos) & USB_FUSES_TRANSN_Msk;
    pusb->DEVICE.PADCAL.bit.TRANSP = (USB_FUSES_TRANSP_ADDR >> USB_FUSES_TRANSP_Pos) & USB_FUSES_TRANSP_Msk;
    pusb->DEVICE.PADCAL.bit.TRIM = (USB_FUSES_TRIM_ADDR >> USB_FUSES_TRIM_Pos) & USB_FUSES_TRIM_Msk;
    //device mode, enabled
    pusb->DEVICE.CTRLB.bit.SPDCONF = 0; //full speed
    pusb->DEVICE.CTRLA.bit.MODE = 0;
    pusb->DEVICE.CTRLA.bit.ENABLE = 1;
    while (pusb->DEVICE.SYNCBUSY.bit.ENABLE) { DBGC(DC_USB2422_INIT_USB_SYNC_ENABLING); }

    pusb->DEVICE.QOSCTRL.bit.DQOS = 2;
    pusb->DEVICE.QOSCTRL.bit.CQOS = 2;

    pport->Group[USB2422_HUB_ACTIVE_GROUP].PINCFG[USB2422_HUB_ACTIVE_PIN].bit.INEN = 1;

    i2c0_init(); //IC2 clk must be high at USB2422 reset release time to signal SMB configuration

    sr_exp_data.bit.HUB_CONNECT = 1; //connect signal high to connect
    sr_exp_data.bit.HUB_RESET_N = 1; //reset high to run
    SR_EXP_WriteData();

    wait_us(100);

#ifndef MD_BOOTLOADER

    usb_gcr_auto = 1;

#endif //MD_BOOTLOADER

    DBGC(DC_USB2422_INIT_COMPLETE);
}

void USB_reset(void) {
    DBGC(DC_USB_RESET_BEGIN);

    //pulse reset for at least 1 usec
    sr_exp_data.bit.HUB_RESET_N = 0; //reset low to reset
    SR_EXP_WriteData();
    wait_us(2);
    sr_exp_data.bit.HUB_RESET_N = 1; //reset high to run
    SR_EXP_WriteData();

    wait_ms(10);

    DBGC(DC_USB_RESET_COMPLETE);
}

void USB_configure(void) {
    Usb2422 *pusb2422 = &USB2422_shadow;
    memset(pusb2422, 0, sizeof(Usb2422));

    uint16_t *serial_use = (uint16_t *)SERNAME; //Default to use SERNAME from this file
    uint8_t serial_length = sizeof(SERNAME) / sizeof(uint16_t); //Default to use SERNAME from this file
#ifndef MD_BOOTLOADER
    uint32_t serial_ptrloc = (uint32_t)&_srom - 4;
#else //MD_BOOTLOADER
    uint32_t serial_ptrloc = (uint32_t)&_erom - 4;
#endif //MD_BOOTLOADER
    uint32_t serial_address = *(uint32_t *)serial_ptrloc; //Address of bootloader's serial number if available

    DBGC(DC_USB_CONFIGURE_BEGIN);

    if (serial_address != 0xFFFFFFFF && serial_address < serial_ptrloc) {   //Check for factory programmed serial address
        if ((serial_address & 0xFF) % 4 == 0) {                             //Check alignment
            serial_use = (uint16_t *)(serial_address);
            serial_length = 0;
            while ((*(serial_use + serial_length) > 32 && *(serial_use + serial_length) < 127) &&
                   serial_length < BOOTLOADER_SERIAL_MAX_SIZE) {
                serial_length++;
                DBGC(DC_USB_CONFIGURE_GET_SERIAL);
            }
        }
    }

    //configure Usb2422 registers
    pusb2422->VID.reg = 0x04D8; // from Microchip 4/19/2018
    pusb2422->PID.reg = 0xEEC5; // from Microchip 4/19/2018 = Massdrop, Inc. USB Hub
    pusb2422->DID.reg = 0x0101; // BCD 01.01
    pusb2422->CFG1.bit.SELF_BUS_PWR = 1; // self powered for now
    pusb2422->CFG1.bit.HS_DISABLE = 1; // full or high speed
    //pusb2422->CFG2.bit.COMPOUND = 0; // compound device
    pusb2422->CFG3.bit.STRING_EN = 1; // strings enabled
    //pusb2422->NRD.bit.PORT2_NR = 0; // MCU is non-removable
    pusb2422->MAXPB.reg = 20; // 0mA
    pusb2422->HCMCB.reg = 20; // 0mA
    pusb2422->MFRSL.reg = sizeof(MFRNAME) / sizeof(uint16_t);
    pusb2422->PRDSL.reg = sizeof(PRDNAME) / sizeof(uint16_t);
    pusb2422->SERSL.reg = serial_length;
    memcpy(pusb2422->MFRSTR, MFRNAME, sizeof(MFRNAME));
    memcpy(pusb2422->PRDSTR, PRDNAME, sizeof(PRDNAME));
    memcpy(pusb2422->SERSTR, serial_use, serial_length * sizeof(uint16_t));
    //pusb2422->BOOSTUP.bit.BOOST=3;    //upstream port
    //pusb2422->BOOSTDOWN.bit.BOOST1=0; // extra port
    //pusb2422->BOOSTDOWN.bit.BOOST2=2; //MCU is close
    pusb2422->STCD.bit.USB_ATTACH = 1;
    USB_write2422_block();

    DBGC(DC_USB_CONFIGURE_COMPLETE);
}

uint16_t USB_active(void) {
    return (PORT->Group[USB2422_HUB_ACTIVE_GROUP].IN.reg & (1 << USB2422_HUB_ACTIVE_PIN)) != 0;
}

#define USB_DETECT_INIT_VAL     100         //Default value for rp/cc detection to test against after routines
#define USB_DETECT_METHOD_NONE  0
#define USB_DETECT_METHOD_RP    1
#define USB_DETECT_METHOD_V     2

//Return best Rp value match
uint8_t USB_detect_host(void) {
    static uint8_t usb_detect_onb_ext = 0;
    uint8_t rp_best_index = 0;

    DBGC(DC_USB_DETECT_HOST_BEGIN);

    g_usb_host_port = USB_HOST_PORT_UNKNOWN;                                        //Initialize host port as unknown

    usb_init_host_detection_kb();                                                   //Run keyboard specific initialization

    wait_ms(100);                                                                   //Allow power dissapation time on CC lines

    while (adc_get(ADC_5V) < ADC_5V_V2C(ADC_5V_START_LEVEL)) { DBGC(DC_USB_DETECT_HOST_5V_LOW_WAITING); } //Assert 5V bus adequate

    uint8_t detect_method = USB_DETECT_METHOD_NONE;                                 //Initial detection method
    uint8_t adc_cc_index[] = { ADC_C1A5, ADC_C1B5, ADC_C2A5, ADC_C2B5 };            //Initialize CC lines array
    uint16_t cc_readings[] = { 0, 0, 0, 0 };                                        //Initialize CC readings array
    uint8_t cc_index;
    uint8_t cc_index_max = sizeof(adc_cc_index) / sizeof(*adc_cc_index);

    //Collect CC readings for decision making processes
    for (cc_index = 0; cc_index < cc_index_max; cc_index++) {                       //For each CC line
        cc_readings[cc_index] = adc_get(adc_cc_index[cc_index]);                    //Perform ADC reading
        if (cc_readings[cc_index] == (uint16_t)ADC_NA) {                            //If the ADC was not available for reading
            cc_readings[cc_index] = 0;                                              //Set value low to not be used
            continue;                                                               //ADC not available so skip
        }

        cc_readings[cc_index] = ADC_CC_5VCOR(adc_get(ADC_5V), cc_readings[cc_index]); //Correct the ADC reading according to 5V bus
    }

#ifdef ADC_USBC_RP_DELTA_MAX
    if (detect_method == USB_DETECT_METHOD_NONE) {                                      //If a detection method has not succeeded yet
        //Using CC readings, test them for onb or ext
        uint16_t rp_delta_least = 5000;                                                 //Initialize to a high number out of ADC range
        uint16_t rp_delta;                                                              //Distance of reading to a test value
        uint8_t rp_index;                                                               //Index of Rp value being tested
        uint8_t cc_best_index = USB_DETECT_INIT_VAL;                                    //Initialize to a high number out of index

        rp_best_index = USB_DETECT_INIT_VAL;                                            //Initialize to a high number out of index
        for (cc_index = 0; cc_index < cc_index_max; cc_index++) {                       //For each CC line
            for (rp_index = 0; rp_index < ADC_USBC_TYPES; rp_index++) {                 //For each Rp
                rp_delta = abs(cc_readings[cc_index] - adc_usbc_rp_nominal[rp_index]);  //Calculate the distance between reading and Rp
                if (rp_delta < rp_delta_least && rp_delta < ADC_USBC_RP_DELTA_MAX) {    //If the distance is less than the least and within distance cap
                    rp_delta_least = rp_delta;                                          //Save the least rp distance
                    rp_best_index = rp_index;                                           //Save the closest Rp value index
                    cc_best_index = adc_cc_index[cc_index];                             //Save the closest CC line index
                }
            }
        }

        //Set up host port and extra port according to detection
        if (rp_best_index != USB_DETECT_INIT_VAL) {                                     //If a decision was made
            if (cc_best_index == ADC_C1A5 || cc_best_index == ADC_C1B5) {               //If on CON1
                usb_set_host_kb(1, rp_best_index);                                      //Set up host port on CON1 (rp used to set onb/ext)
                usb_set_extra_kb(2);                                                    //Set up extra port on CON2
                detect_method = USB_DETECT_METHOD_RP;                                   //Set detection method used
            } else if (cc_best_index == ADC_C2A5 || cc_best_index == ADC_C2B5) {        //Else if on CON2
                usb_set_host_kb(2, rp_best_index);                                      //Set up host port on CON2 (rp used to set onb/ext)
                usb_set_extra_kb(1);                                                    //Set up extra port on CON1
                detect_method = USB_DETECT_METHOD_RP;                                   //Set detection method used
            }
        }
    }
#endif

    //Detect highest voltage port and test onboard or external
    if (detect_method == USB_DETECT_METHOD_NONE) {                                  //If a detection method has not succeeded yet
        uint16_t rp_highest_v = 0;                                                  //Initialize to the lowest number possible
        uint8_t v_best_index = USB_DETECT_INIT_VAL;                                 //Initialize to the lowest number possible
        for (cc_index = 0; cc_index < cc_index_max; cc_index++) {                   //For each CC line
            if (cc_readings[cc_index] > rp_highest_v) {                             //Keep track of the highest voltage level as a secondary host detection method
                rp_highest_v = cc_readings[cc_index];                               //Save the highest voltage
                v_best_index = adc_cc_index[cc_index];                              //Save the highest voltage index
            }
        }

        //Set up host port and extra port according to detection
        usb_detect_onb_ext = !usb_detect_onb_ext;                                   //Swap onb/ext detect for this run
        rp_best_index = usb_detect_onb_ext;                                         //Force onb/ext setting
        if (v_best_index == ADC_C1A5 || v_best_index == ADC_C1B5) {                 //If on CON1
            usb_set_host_kb(1, rp_best_index);                                      //Set up host port on CON1
            usb_set_extra_kb(2);                                                    //Set up extra port on CON2
            detect_method = USB_DETECT_METHOD_V;                                    //Set detection method used
        } else if (v_best_index == ADC_C2A5 || v_best_index == ADC_C2B5) {          //Else if on CON2
            usb_set_host_kb(2, rp_best_index);                                      //Set up host port on CON2
            usb_set_extra_kb(1);                                                    //Set up extra port on CON1
            detect_method = USB_DETECT_METHOD_V;                                    //Set detection method used
        }
    }

    if (detect_method != USB_DETECT_METHOD_NONE) {                                  //If a detection method succeeded
        wait_ms(20);                                                                //Allow settling time for switching
        USB_reset();                                                                //Reset and enable the USB Hub
        USB_configure();                                                            //Configure the USB Hub and send attach
    }

    DBGC(DC_USB_DETECT_HOST_COMPLETE);

    return rp_best_index;
}

uint8_t USB2422_Port_Detect_Init(void) {
    uint32_t tmod;
    uint8_t led_state = 0;
    uint64_t port_detect_fail_ms;
    static uint8_t port_detect_retry_counter = 0;
    static uint16_t port_detect_retry_ms = 0;

    DBGC(DC_PORT_DETECT_INIT_BEGIN);

#ifdef ADC_USBC_IS_EXT
    //If the keyboard supports offboard USB extenders, rp_best_index is used to determine onboard/offboard usage
    uint8_t rp_best_index = USB_detect_host();
#else
    USB_detect_host();
#endif

    port_detect_fail_ms = timer_read64() + PORT_DETECT_RETRY_START + port_detect_retry_ms;
    uint32_t port_flash_counter = timer_read();

    while (!USB_active()) {
        tmod = (timer_read() - port_flash_counter);
        if (USB_HOST_IS_1(g_usb_host_port)) {
            //1 flash for port 1 detected (dit), additional long flash if external port (dit-dah)
            if (tmod > 500 && tmod < 600) {
                if (!led_state) { DBG_LED_ON; led_state = 1; }
            }
#ifdef ADC_USBC_IS_EXT
            else if (ADC_USBC_IS_EXT(rp_best_index) && tmod > 1000 && tmod < 1500) {
                if (!led_state) { DBG_LED_ON; led_state = 1; }
            }
#endif
            else if (led_state) { DBG_LED_OFF; led_state = 0; }
        } else if (USB_HOST_IS_2(g_usb_host_port)) {
            //2 flash for port 2 detected (dit-dit), additional long flash if external port (dit-dit-dah)
            if (tmod > 500 && tmod < 600) {
                if (!led_state) { DBG_LED_ON; led_state = 1; }
            } else if (tmod > 700 && tmod < 800) {
                if (!led_state) { DBG_LED_ON; led_state = 1; }
            }
#ifdef ADC_USBC_IS_EXT
            else if (ADC_USBC_IS_EXT(rp_best_index) && tmod > 1000 && tmod < 1500) {
                if (!led_state) { DBG_LED_ON; led_state = 1; }
            }
#endif
            else if (led_state) { DBG_LED_OFF; led_state = 0; }
        } else {
            //Flash every 250ms if port unknown (should not get here)
            if (tmod % 500 < 250) {
                if (!led_state) { DBG_LED_ON; led_state = 1; }
            } else if (led_state) { DBG_LED_OFF; led_state = 0; }
        }

        if (timer_read64() > port_detect_fail_ms) {                     //If timeout reached
            DBGC(DC_PORT_DETECT_INIT_FAILED);

            port_detect_retry_counter++;                                //Increment retry counter
            if (port_detect_retry_counter % 2 == 0) {                   //Increment timeout every 2 attempts
                port_detect_retry_ms += PORT_DETECT_RETRY_INCREMENT;    //Increment timeout
            }
            if (port_detect_retry_ms > PORT_DETECT_RETRY_MAX) {         //If the new timeout is greater than the max timeout setting
                port_detect_retry_ms = PORT_DETECT_RETRY_MAX;           //Set timeout to max
            }

            return 0;
        }
    }

    DBGC(DC_PORT_DETECT_INIT_COMPLETE);

    return 1;
}

#ifndef MD_BOOTLOADER

usbc_t usbc;

uint16_t usbc_cc_a5_v;
uint16_t usbc_cc_b5_v;
float usbc_cc_a5_v_avg;
float usbc_cc_b5_v_avg;

void usbc_cc_clear(void) {
    usbc_cc_a5_v = 0;
    usbc_cc_b5_v = 0;
    usbc_cc_a5_v_avg = 0.0f;
    usbc_cc_b5_v_avg = 0.0f;
}

//Only poll CC lines for port assigned as EXTRA
uint8_t usbc_cc_update(void) {
    if (USB_HOST_IS_1(g_usb_host_port)) {
        usbc_cc_a5_v = adc_get(ADC_C2A5);
        usbc_cc_b5_v = adc_get(ADC_C2B5);
    } else if (USB_HOST_IS_2(g_usb_host_port)) {
        usbc_cc_a5_v = adc_get(ADC_C1A5);
        usbc_cc_b5_v = adc_get(ADC_C1B5);
    } else {
        return 0;
    }

    usbc_cc_a5_v_avg = 0.9 * usbc_cc_a5_v_avg + 0.1 * (float)usbc_cc_a5_v;
    usbc_cc_b5_v_avg = 0.9 * usbc_cc_b5_v_avg + 0.1 * (float)usbc_cc_b5_v;

    return 1;
}

//Disable 5V bus on extra USB port
//If force_update != 0, force update to run
//If force_update == 0, only update if value is changed
uint8_t usbc_5v_disable(uint8_t force_update) {
    if (USB_HOST_IS_1(g_usb_host_port)) {
        if (force_update || (USBC_CFG_5V2_VAR != USBC_CFG_5V2_DIS)) {
            USBC_CFG_5V2_VAR = USBC_CFG_5V2_DIS;
            USBC_CFG_5V2_UPDATE;
        }
        return 1;
    } else if (USB_HOST_IS_2(g_usb_host_port)) {
        if (force_update || (USBC_CFG_5V1_VAR != USBC_CFG_5V1_DIS)) {
            USBC_CFG_5V1_VAR = USBC_CFG_5V1_DIS;
            USBC_CFG_5V1_UPDATE;
        }
        return 1;
    }

    return 0;
}

//Enable 5V bus on extra USB port
//If force_update != 0, force update to run
//If force_update == 0, only update if value is changed
uint8_t usbc_5v_enable(uint8_t force_update) {
    if (USB_HOST_IS_1(g_usb_host_port)) {
        if (force_update || (USBC_CFG_5V2_VAR != USBC_CFG_5V2_ENA)) {
            USBC_CFG_5V2_VAR = USBC_CFG_5V2_ENA;
            USBC_CFG_5V2_UPDATE;
        }
        return 1;
    } else if (USB_HOST_IS_2(g_usb_host_port)) {
        if (force_update || (USBC_CFG_5V1_VAR != USBC_CFG_5V1_ENA)) {
            USBC_CFG_5V1_VAR = USBC_CFG_5V1_ENA;
            USBC_CFG_5V1_UPDATE;
        }
        return 1;
    }

    return 0;
}

uint8_t usbc_5v_is_enabled(void) {
    if (USB_HOST_IS_1(g_usb_host_port)) {
        if (USBC_CFG_5V2_VAR == USBC_CFG_5V2_ENA) {
            return 1;
        } else {
            return 0;
        }
    } else if (USB_HOST_IS_2(g_usb_host_port)) {
        if (USBC_CFG_5V1_VAR == USBC_CFG_5V1_ENA) {
            return 1;
        } else {
            return 0;
        }
    }

    return 0; //Not sure technically due to unknown host port
}

void usbc_enable(void) {
    usbc_5v_disable(1);                                             //Disable 5V bus
    usbc.state = USB_STATE_UNATTACHED_WAIT_SRC;                     //Set starting state to discharge wait
    usbc.timer = USBC_CFG_TVCONNDISCHARGE;                          //Set timer for 5V bus discharge
    usbc_cc_clear();                                                //Clear CC readings
}

void usbc_disable(void) {
    usbc_5v_disable(1);                                             //Disable 5V bus
    usbc.state = USB_STATE_DISABLED_WAIT;                           //Set disabled waiting state
    usbc.timer = USBC_CFG_TVCONNDISCHARGE;                          //Set timer for 5V bus discharge
    usbc_cc_clear();                                                //Clear CC readings
}

//This macro updates the timer and returns true if timer is complete
#define USBC_TIMER_DONE (0 == (usbc.timer = (usbc.timer > USBC_CFG_PERIOD ? usbc.timer - USBC_CFG_PERIOD : 0)))

void usbc_task(void) {
    if (usbc.state == USB_STATE_UNATTACHED_SRC) {
        //Connection detected -> USB_STATE_ATTACH_WAIT_SRC

        usbc.timer = 0;                                             //Note: Changes to this state do not require clearing timer at change

        if (usbc_cc_update()) {                                     //Must have valid readings to continue
            if (USBC_IS_SINK((uint16_t)usbc_cc_a5_v_avg, (uint16_t)usbc_cc_b5_v_avg)) { //If Sink detected
                usbc.state = USB_STATE_ATTACH_WAIT_SRC;             //Set next state
                usbc.timer = USBC_CFG_TCCDEBOUNCE;                  //Set timer
            } else {
                return;                                             //Nothing more to be done
            }
        }
    }

    if (usbc.state == USB_STATE_ATTACH_WAIT_SRC) {
        //Connection removed -> USB_STATE_UNATTACHED_SRC
        //Other detection types unsupported -> USB_STATE_UNATTACHED_SRC
        if (!usbc_cc_update()) {                                                        //Must have valid readings to continue
            usbc.state = USB_STATE_UNATTACHED_SRC;                                      //Invalid reading, detach
            return;                                                                     //Nothing more to be done
        } else {                                                                        //Valid CC readings to work with
            if (!USBC_IS_SINK((uint16_t)usbc_cc_a5_v_avg, (uint16_t)usbc_cc_b5_v_avg)) {    //If not a sink type
                usbc.state = USB_STATE_UNATTACHED_SRC;                                  //Detach
                return;                                                                 //Nothing more to be done
            } else {
                //Detected Sink for tCCDebounce -> USB_STATE_ATTACHED_SRC
                if (USBC_TIMER_DONE) {                                                  //Update timer and if timer complete
                    if (usb_attach_port_configure_kb(g_usb_host_port, (uint16_t)usbc_cc_a5_v_avg, (uint16_t)usbc_cc_b5_v_avg)) {  //If configuration was successful
                        usbc_5v_enable(1);                                              //Enable 5V bus
                        usbc.state = USB_STATE_ATTACHED_SRC;                            //Set next state
                        dprintf("USB Extra: Port enabled\n");
                    } else {                                                            //port was not configured
                        usbc.state = USB_STATE_UNATTACHED_SRC;                          //Set next state
                    }
                }
            }
        }
    }

    if (usbc.state == USB_STATE_ATTACHED_SRC) {
        //Sink Removed and VCONN was On -> USB_STATE_UNATTACHED_WAIT_SRC
        //Sink removed and VCONN was Off -> USB_STATE_UNATTACHED_SRC (Will always assume VCONN was On so ignoring this)
        if (!usbc_cc_update()) {                                    //Must have valid readings to continue
            usbc_5v_disable(1);                                     //Disable 5V bus
            usbc.state = USB_STATE_UNATTACHED_WAIT_SRC;             //Enter wait state for 5V bus discharge
            usbc.timer = USBC_CFG_TVCONNDISCHARGE;                  //Set timer for 5V bus discharge
            dprintf("USB Extra: Port disabled\n");
        } else {
            if (!USBC_IS_SINK((uint16_t)usbc_cc_a5_v_avg, (uint16_t)usbc_cc_b5_v_avg)) {    //Sink lost
                usbc_5v_disable(1);                                 //Disable 5V bus
                usbc.state = USB_STATE_UNATTACHED_WAIT_SRC;         //Enter wait state for 5V bus discharge
                usbc.timer = USBC_CFG_TVCONNDISCHARGE;              //Set timer for 5V bus discharge
                dprintf("USB Extra: Port disabled\n");
            }
        }
    }

    if (usbc.state == USB_STATE_UNATTACHED_WAIT_SRC) {
        //Discharge Complete and VCONN Off -> USB_STATE_UNATTACHED_SRC
        if (USBC_TIMER_DONE) {                                      //Update timer and if timer complete
            usbc.state = USB_STATE_UNATTACHED_SRC;                  //Set next state
        }
    }

    if (usbc.state == USB_STATE_DISABLED_WAIT) {
        //Wait complete -> USB_STATE_DISABLED
        if (USBC_TIMER_DONE) {                                      //Update timer and if timer complete
            usbc.state = USB_STATE_DISABLED;                        //Set next state
        }
    }

    if (usbc.state == USB_STATE_DISABLED_UNTIL_DETACH) {
        if (usbc_5v_is_enabled()) {
            usbc_5v_disable(1);                                     //Disable 5V bus
        }

        if (!usbc_cc_update()) {                                    //Must have valid readings to continue
            usbc.state = USB_STATE_UNATTACHED_WAIT_SRC;             //Enter wait state for 5V bus discharge
            usbc.timer = USBC_CFG_TVCONNDISCHARGE;                  //Set timer for 5V bus discharge
        } else {
            if (!USBC_IS_SINK((uint16_t)usbc_cc_a5_v_avg, (uint16_t)usbc_cc_b5_v_avg)) {    //Sink lost
                usbc.state = USB_STATE_UNATTACHED_WAIT_SRC;         //Enter wait state for 5V bus discharge
                usbc.timer = USBC_CFG_TVCONNDISCHARGE;              //Set timer for 5V bus discharge
            }
        }
    }
}

void USB_HandleExtraDevice(void) {
    usbc_task();
}

#endif //MD_BOOTLOADER

