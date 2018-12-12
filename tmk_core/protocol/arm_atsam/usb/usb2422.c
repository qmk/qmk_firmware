/*
Copyright 2018 Massdrop Inc.

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

uint8_t usb_host_port;

#ifndef MD_BOOTLOADER

uint8_t usb_extra_state;
uint8_t usb_extra_manual;
uint8_t usb_gcr_auto;

#endif //MD_BOOTLOADER

uint16_t adc_extra;

void USB_write2422_block(void)
{
    unsigned char *dest = i2c0_buf;
    unsigned char *src;
    unsigned char *base = (unsigned char *)&USB2422_shadow;

    DBGC(DC_USB_WRITE2422_BLOCK_BEGIN);

    for (src =  base; src < base + 256; src += 32)
    {
        dest[0] = src - base;
        dest[1] = 32;
        memcpy(&dest[2], src, 32);
        i2c0_transmit(USB2422_ADDR, dest, 34, 50000);
        SERCOM0->I2CM.CTRLB.bit.CMD = 0x03;
        while (SERCOM0->I2CM.SYNCBUSY.bit.SYSOP) { DBGC(DC_USB_WRITE2422_BLOCK_SYNC_SYSOP); }
        CLK_delay_us(100);
    }

    DBGC(DC_USB_WRITE2422_BLOCK_COMPLETE);
}

void USB2422_init(void)
{
    Gclk *pgclk = GCLK;
    Mclk *pmclk = MCLK;
    Port *pport = PORT;
    Oscctrl *posc = OSCCTRL;
    Usb *pusb = USB;

    DBGC(DC_USB2422_INIT_BEGIN);

    while ((v_5v = adc_get(ADC_5V)) < ADC_5V_START_LEVEL) { DBGC(DC_USB2422_INIT_WAIT_5V_LOW); }

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

    sr_exp_data.bit.HUB_CONNECT = 1; //connect signal
    sr_exp_data.bit.HUB_RESET_N = 1; //reset high
    SR_EXP_WriteData();

    CLK_delay_us(100);

#ifndef MD_BOOTLOADER

    usb_extra_manual = 0;
    usb_gcr_auto = 1;

#endif //MD_BOOTLOADER

    DBGC(DC_USB2422_INIT_COMPLETE);
}

void USB_reset(void)
{
    DBGC(DC_USB_RESET_BEGIN);

    //pulse reset for at least 1 usec
    sr_exp_data.bit.HUB_RESET_N = 0; //reset low
    SR_EXP_WriteData();
    CLK_delay_us(1);
    sr_exp_data.bit.HUB_RESET_N = 1; //reset high to run
    SR_EXP_WriteData();
    CLK_delay_us(1);

    DBGC(DC_USB_RESET_COMPLETE);
}

void USB_configure(void)
{
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

    if (serial_address != 0xFFFFFFFF && serial_address < serial_ptrloc) //Check for factory programmed serial address
    {
        if ((serial_address & 0xFF) % 4 == 0) //Check alignment
        {
            serial_use = (uint16_t *)(serial_address);
            serial_length = 0;
            while ((*(serial_use + serial_length) > 32 && *(serial_use + serial_length) < 127) &&
                   serial_length < BOOTLOADER_SERIAL_MAX_SIZE)
            {
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

    adc_extra = 0;

    DBGC(DC_USB_CONFIGURE_COMPLETE);
}

uint16_t USB_active(void)
{
    return (PORT->Group[USB2422_HUB_ACTIVE_GROUP].IN.reg & (1 << USB2422_HUB_ACTIVE_PIN)) != 0;
}

void USB_set_host_by_voltage(void)
{
    //UP is upstream device (HOST)
    //DN1 is downstream device (EXTRA)
    //DN2 is keyboard (KEYB)

    DBGC(DC_USB_SET_HOST_BY_VOLTAGE_BEGIN);

    usb_host_port = USB_HOST_PORT_UNKNOWN;
#ifndef MD_BOOTLOADER
    usb_extra_state = USB_EXTRA_STATE_UNKNOWN;
#endif //MD_BOOTLOADER
    sr_exp_data.bit.SRC_1 = 1;       //USBC-1 available for test
    sr_exp_data.bit.SRC_2 = 1;       //USBC-2 available for test
    sr_exp_data.bit.E_UP_N = 1;      //HOST disable
    sr_exp_data.bit.E_DN1_N = 1;     //EXTRA disable
    sr_exp_data.bit.E_VBUS_1 = 0;    //USBC-1 disable full power I/O
    sr_exp_data.bit.E_VBUS_2 = 0;    //USBC-2 disable full power I/O

    SR_EXP_WriteData();

    CLK_delay_ms(250);

    while ((v_5v = adc_get(ADC_5V)) < ADC_5V_START_LEVEL) { DBGC(DC_USB_SET_HOST_5V_LOW_WAITING); }

    v_con_1 = adc_get(ADC_CON1);
    v_con_2 = adc_get(ADC_CON2);

    v_con_1_boot = v_con_1;
    v_con_2_boot = v_con_2;

    if (v_con_1 > v_con_2)
    {
        sr_exp_data.bit.S_UP = 0;        //HOST to USBC-1
        sr_exp_data.bit.S_DN1 = 1;       //EXTRA to USBC-2
        sr_exp_data.bit.SRC_1 = 1;       //HOST on USBC-1
        sr_exp_data.bit.SRC_2 = 0;       //EXTRA available on USBC-2

        sr_exp_data.bit.E_VBUS_1 = 1;    //USBC-1 enable full power I/O
        sr_exp_data.bit.E_VBUS_2 = 0;    //USBC-2 disable full power I/O

        SR_EXP_WriteData();

        sr_exp_data.bit.E_UP_N = 0;      //HOST enable

        SR_EXP_WriteData();

        usb_host_port = USB_HOST_PORT_1;
    }
    else
    {
        sr_exp_data.bit.S_UP = 1;        //EXTRA to USBC-1
        sr_exp_data.bit.S_DN1 = 0;       //HOST to USBC-2
        sr_exp_data.bit.SRC_1 = 0;       //EXTRA available on USBC-1
        sr_exp_data.bit.SRC_2 = 1;       //HOST on USBC-2

        sr_exp_data.bit.E_VBUS_1 = 0;    //USBC-1 disable full power I/O
        sr_exp_data.bit.E_VBUS_2 = 1;    //USBC-2 enable full power I/O

        SR_EXP_WriteData();

        sr_exp_data.bit.E_UP_N = 0;      //HOST enable

        SR_EXP_WriteData();

        usb_host_port = USB_HOST_PORT_2;
    }

#ifndef MD_BOOTLOADER
    usb_extra_state = USB_EXTRA_STATE_DISABLED;
#endif //MD_BOOTLOADER

    USB_reset();
    USB_configure();

    DBGC(DC_USB_SET_HOST_BY_VOLTAGE_COMPLETE);
}

uint8_t USB2422_Port_Detect_Init(void)
{
    uint32_t port_detect_retry_ms;
    uint32_t tmod;

    DBGC(DC_PORT_DETECT_INIT_BEGIN);

    USB_set_host_by_voltage();

    port_detect_retry_ms = CLK_get_ms() + PORT_DETECT_RETRY_INTERVAL;

    while (!USB_active())
    {
        tmod = CLK_get_ms() % PORT_DETECT_RETRY_INTERVAL;

        if (v_con_1 > v_con_2) //Values updated from USB_set_host_by_voltage();
        {
            //1 flash for port 1 detected
            if (tmod > 500 && tmod < 600) { DBG_LED_ON; }
            else { DBG_LED_OFF; }
        }
        else if (v_con_2 > v_con_1) //Values updated from USB_set_host_by_voltage();
        {
            //2 flash for port 2 detected
            if (tmod > 500 && tmod < 600) { DBG_LED_ON; }
            else if (tmod > 700 && tmod < 800) { DBG_LED_ON; }
            else { DBG_LED_OFF; }
        }

        if (CLK_get_ms() > port_detect_retry_ms)
        {
            DBGC(DC_PORT_DETECT_INIT_FAILED);
            return 0;
        }
    }

    DBGC(DC_PORT_DETECT_INIT_COMPLETE);

    return 1;
}

#ifndef MD_BOOTLOADER

void USB_ExtraSetState(uint8_t state)
{
    uint8_t state_save = state;

    if (state == USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG)
        state = USB_EXTRA_STATE_DISABLED;

    if (usb_host_port == USB_HOST_PORT_1) sr_exp_data.bit.E_VBUS_2 = state;
    else if (usb_host_port == USB_HOST_PORT_2) sr_exp_data.bit.E_VBUS_1 = state;
    else return;

    sr_exp_data.bit.E_DN1_N = !state;
    SR_EXP_WriteData();

    usb_extra_state = state_save;

    if (usb_extra_state == USB_EXTRA_STATE_ENABLED) CDC_print("USB: Extra enabled\r\n");
    else if (usb_extra_state == USB_EXTRA_STATE_DISABLED)
    {
      CDC_print("USB: Extra disabled\r\n");
      if (led_animation_breathing) gcr_breathe = gcr_desired;
    }
    else if (usb_extra_state == USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG) CDC_print("USB: Extra disabled until replug\r\n");
    else CDC_print("USB: Extra state unknown\r\n");
}

void USB_HandleExtraDevice(void)
{
    uint16_t adcval;

    if (usb_host_port == USB_HOST_PORT_1) adcval = adc_get(ADC_CON2);
    else if (usb_host_port == USB_HOST_PORT_2) adcval = adc_get(ADC_CON1);
    else return;

    adc_extra = adc_extra * 0.9 + adcval * 0.1;

    //Check for a forced disable state (such as overload prevention)
    if (usb_extra_state == USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG)
    {
        //Detect unplug and reset state to disabled
        if (adc_extra > USB_EXTRA_ADC_THRESHOLD) usb_extra_state = USB_EXTRA_STATE_DISABLED;

        return; //Return even if unplug detected
    }

    if (usb_extra_manual)
    {
        if (usb_extra_state == USB_EXTRA_STATE_DISABLED)
        USB_ExtraSetState(USB_EXTRA_STATE_ENABLED);

        return;
    }

    //dpf("a %i %i\r\n",adcval, adc_extra);
    if (usb_extra_state == USB_EXTRA_STATE_DISABLED && adc_extra < USB_EXTRA_ADC_THRESHOLD) USB_ExtraSetState(USB_EXTRA_STATE_ENABLED);
    else if (usb_extra_state == USB_EXTRA_STATE_ENABLED && adc_extra > USB_EXTRA_ADC_THRESHOLD) USB_ExtraSetState(USB_EXTRA_STATE_DISABLED);
}

#endif //MD_BOOTLOADER

