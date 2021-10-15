#include "usb2422.h"
#include "i2c_master.h"
#include "wait.h"
#include <string.h>

/* -------- USB2422_VID : (USB2422L Offset: 0x00) (R/W 16) Vendor ID -------- */
typedef union {
    struct {
        uint16_t VID_LSB : 8;
        uint16_t VID_MSB : 8;
    } bit;        /*!< Structure used for bit  access                  */
    uint16_t reg; /*!< Type      used for register access              */
} USB2422_VID_Type;

/* -------- USB2422_PID : (USB2422L Offset: 0x02) (R/W 16) Product ID -------- */
typedef union {
    struct {
        uint16_t PID_LSB : 8;
        uint16_t PID_MSB : 8;
    } bit;        /*!< Structure used for bit  access                  */
    uint16_t reg; /*!< Type      used for register access              */
} USB2422_PID_Type;

/* -------- USB2422_DID : (USB2422L Offset: 0x04) (R/W 16) Device ID -------- */
typedef union {
    struct {
        uint16_t DID_LSB : 8;
        uint16_t DID_MSB : 8;
    } bit;        /*!< Structure used for bit  access                  */
    uint16_t reg; /*!< Type      used for register access              */
} USB2422_DID_Type;

/* -------- USB2422_CFG1 : (USB2422L Offset: 0x06) (R/W 8) Configuration Data Byte 1-------- */
typedef union {
    struct {
        uint8_t PORT_PWR : 1;
        uint8_t CURRENT_SNS : 2;
        uint8_t EOP_DISABLE : 1;
        uint8_t MTT_ENABLE : 1;
        uint8_t HS_DISABLE : 1;
        uint8_t : 1;
        uint8_t SELF_BUS_PWR : 1;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_CFG1_Type;

/* -------- USB2422_CFG2 : (USB2422L Offset: 0x07) (R/W 8) Configuration Data Byte 2-------- */
typedef union {
    struct {
        uint8_t : 3;
        uint8_t COMPOUND : 1;
        uint8_t OC_TIMER : 2;
        uint8_t : 1;
        uint8_t DYNAMIC : 1;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_CFG2_Type;

/* -------- USB2422_CFG3 : (USB2422L Offset: 0x08) (R/W 16) Configuration Data Byte 3-------- */
typedef union {
    struct {
        uint8_t STRING_EN : 1;
        uint8_t : 2;
        uint8_t PRTMAP_EN : 1;
        uint8_t : 4;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_CFG3_Type;

/* -------- USB2422_NRD : (USB2422L Offset: 0x09) (R/W 8) Non Removable Device -------- */
typedef union {
    struct {
        uint8_t : 5;
        uint8_t PORT2_NR : 1;
        uint8_t PORT1_NR : 1;
        uint8_t : 1;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_NRD_Type;

/* -------- USB2422_PDS : (USB2422L Offset: 0x0A) (R/W 8) Port Diable for Self-Powered Operation -------- */
typedef union {
    struct {
        uint8_t : 1;
        uint8_t PORT1_DIS : 1;
        uint8_t PORT2_DIS : 1;
        uint8_t : 5;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_PDS_Type;


/* -------- USB2422_PDB : (USB2422L Offset: 0x0B) (R/W 8) Port Diable for Bus-Powered Operation -------- */

typedef union {
    struct {
        uint8_t : 1;
        uint8_t PORT1_DIS : 1;
        uint8_t PORT2_DIS : 1;
        uint8_t : 5;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_PDB_Type;

/* -------- USB2422_MAXPS : (USB2422L Offset: 0x0C) (R/W 8) Max Power for Self-Powered Operation -------- */
typedef union {
    struct {
        uint8_t MAX_PWR_SP : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_MAXPS_Type;

/* -------- USB2422_MAXPB : (USB2422L Offset: 0x0D) (R/W 8) Max Power for Bus-Powered Operation -------- */
typedef union {
    struct {
        uint8_t MAX_PWR_BP : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_MAXPB_Type;

/* -------- USB2422_HCMCS : (USB2422L Offset: 0x0E) (R/W 8) Hub Controller Max Current for Self-Powered Operation -------- */
typedef union {
    struct {
        uint8_t HC_MAX_C_SP : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_HCMCS_Type;

/* -------- USB2422_HCMCB : (USB2422L Offset: 0x0F) (R/W 8) Hub Controller Max Current for Bus-Powered Operation -------- */
typedef union {
    struct {
        uint8_t HC_MAX_C_BP : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_HCMCB_Type;

/* -------- USB2422_PWRT : (USB2422L Offset: 0x10) (R/W 8) Power On Time -------- */
typedef union {
    struct {
        uint8_t POWER_ON_TIME : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_PWRT_Type;

/* -------- USB2422_LANGID LSB : (USB2422L Offset: 0x11) (R/W 16) Language ID -------- */
typedef union {
    struct {
        uint8_t LANGID_LSB : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_LANGID_LSB_Type;

/* -------- USB2422_LANGID MSB : (USB2422L Offset: 0x12) (R/W 16) Language ID -------- */
typedef union {
    struct {
        uint8_t LANGID_MSB : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_LANGID_MSB_Type;

/* -------- USB2422_MFRSL : (USB2422L Offset: 0x13) (R/W 8) Manufacturer String Length -------- */
typedef union {
    struct {
        uint8_t MFR_STR_LEN : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_MFRSL_Type;

/* -------- USB2422_PRDSL : (USB2422L Offset: 0x14) (R/W 8) Product String Length -------- */
typedef union {
    struct {
        uint8_t PRD_STR_LEN : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_PRDSL_Type;

/* -------- USB2422_SERSL : (USB2422L Offset: 0x15) (R/W 8) Serial String Length -------- */
typedef union {
    struct {
        uint8_t SER_STR_LEN : 8;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_SERSL_Type;

/* -------- USB2422_MFRSTR : (USB2422L Offset: 0x16-53) (R/W 8) Maufacturer String -------- */
typedef uint16_t USB2422_MFRSTR_Type;

/* -------- USB2422_PRDSTR : (USB2422L Offset: 0x54-91) (R/W 8) Product String -------- */
typedef uint16_t USB2422_PRDSTR_Type;

/* -------- USB2422_SERSTR : (USB2422L Offset: 0x92-CF) (R/W 8) Serial String -------- */
typedef uint16_t USB2422_SERSTR_Type;

/* -------- USB2422_BCEN : (USB2422L Offset: 0xD0) (R/W 8) Battery Charging Enable -------- */

typedef union {
    struct {
        uint8_t : 1;
        uint8_t PORT1_BCE : 1;
        uint8_t PORT2_BCE : 1;
        uint8_t : 5;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_BCEN_Type;

/* -------- USB2422_BOOSTUP : (USB2422L Offset: 0xF6) (R/W 8) Boost Upstream -------- */
typedef union {
    struct {
        uint8_t BOOST : 2;
        uint8_t : 6;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_BOOSTUP_Type;

/* -------- USB2422_BOOSTDOWN : (USB2422L Offset: 0xF8) (R/W 8) Boost Downstream -------- */
typedef union {
    struct {
        uint8_t BOOST1 : 2;
        uint8_t BOOST2 : 2;
        uint8_t : 4;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_BOOSTDOWN_Type;

/* -------- USB2422_PRTSP : (USB2422L Offset: 0xFA) (R/W 8) Port Swap -------- */
typedef union {
    struct {
        uint8_t : 1;
        uint8_t PORT1_SP : 1;
        uint8_t PORT2_SP : 1;
        uint8_t : 5;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_PRTSP_Type;

/* -------- USB2422_PRTR12 : (USB2422L Offset: 0xFB) (R/W 8) Port 1/2 Remap -------- */
typedef union {
    struct {
        uint8_t PORT1_REMAP : 4;
        uint8_t PORT2_REMAP : 4;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_PRTR12_Type;

#define USB2422_PRTR12_DISABLE 0
#define USB2422_PRT12_P2TOL1 1
#define USB2422_PRT12_P2XTOL2 2
#define USB2422_PRT12_P1TOL1 1
#define USB2422_PRT12_P1XTOL2 2

/* -------- USB2422_STCD : (USB2422L Offset: 0xFF) (R/W 8) Status Command -------- */
typedef union {
    struct {
        uint8_t USB_ATTACH : 1;
        uint8_t RESET : 1;
        uint8_t INTF_PWRDN : 1;
        uint8_t : 5;
    } bit;       /*!< Structure used for bit  access                  */
    uint8_t reg; /*!< Type      used for register access              */
} USB2422_STCD_Type;

/** \brief USB2422 device hardware registers */
typedef struct {
    USB2422_VID_Type        VID;        /**< \brief Offset: 0x00*/
    USB2422_PID_Type        PID;        /**< \brief Offset: 0x02*/
    USB2422_DID_Type        DID;        /**< \brief Offset: 0x04*/
    USB2422_CFG1_Type       CFG1;       /**< \brief Offset: 0x06*/
    USB2422_CFG2_Type       CFG2;       /**< \brief Offset: 0x07*/
    USB2422_CFG3_Type       CFG3;       /**< \brief Offset: 0x08*/
    USB2422_NRD_Type        NRD;        /**< \brief Offset: 0x09*/
    USB2422_PDS_Type        PDS;        /**< \brief Offset: 0x0A*/
    USB2422_PDB_Type        PDB;        /**< \brief Offset: 0x0B*/
    USB2422_MAXPS_Type      MAXPS;      /**< \brief Offset: 0x0C*/
    USB2422_MAXPB_Type      MAXPB;      /**< \brief Offset: 0x0D*/
    USB2422_HCMCS_Type      HCMCS;      /**< \brief Offset: 0x0E*/
    USB2422_HCMCB_Type      HCMCB;      /**< \brief Offset: 0x0F*/
    USB2422_PWRT_Type       PWRT;       /**< \brief Offset: 0x10*/
    USB2422_LANGID_LSB_Type LANGID_LSB; /**< \brief Offset: 0x11*/
    USB2422_LANGID_MSB_Type LANGID_MSB; /**< \brief Offset: 0x12*/
    USB2422_MFRSL_Type      MFRSL;      /**< \brief Offset: 0x13*/
    USB2422_PRDSL_Type      PRDSL;      /**< \brief Offset: 0x14*/
    USB2422_SERSL_Type      SERSL;      /**< \brief Offset: 0x15*/
    USB2422_MFRSTR_Type     MFRSTR[31]; /**< \brief Offset: 0x16*/
    USB2422_PRDSTR_Type     PRDSTR[31]; /**< \brief Offset: 0x54*/
    USB2422_SERSTR_Type     SERSTR[31]; /**< \brief Offset: 0x92*/
    USB2422_BCEN_Type       BCEN;       /**< \brief Offset: 0xD0*/
    uint8_t                 Reserved1[0x25];
    USB2422_BOOSTUP_Type    BOOSTUP; /**< \brief Offset: 0xF6*/
    uint8_t                 Reserved2[0x1];
    USB2422_BOOSTDOWN_Type  BOOSTDOWN; /**< \brief Offset: 0xF8*/
    uint8_t                 Reserved3[0x1];
    USB2422_PRTSP_Type      PRTSP;  /**< \brief Offset: 0xFA*/
    USB2422_PRTR12_Type     PRTR12; /**< \brief Offset: 0xFB*/
    uint8_t                 Reserved4[0x3];
    USB2422_STCD_Type       STCD; /**< \brief Offset: 0xFF*/
} Usb2422;

#ifndef USB2422_ADDRESS
#    define USB2422_ADDRESS 0x58
#endif

Usb2422       USB2422_shadow;
unsigned char i2c0_buf[34];

static const uint16_t MFRNAME[] = {'M', 'a', 's', 's', 'd', 'r', 'o', 'p', ' ', 'I', 'n', 'c', '.'};  // Massdrop Inc.
static const uint16_t PRDNAME[] = {'M', 'a', 's', 's', 'd', 'r', 'o', 'p', ' ', 'H', 'u', 'b'};       // Massdrop Hub
static const uint16_t SERNAME[] = {'U', 'n', 'a', 'v', 'a', 'i', 'l', 'a', 'b', 'l', 'e'};  // Unavailable

static void USB2422_write_block(void) {
    unsigned char *dest = i2c0_buf;
    unsigned char *src;
    unsigned char *base = (unsigned char *)&USB2422_shadow;

    for (src = base; src < base + 256; src += 32) {
        dest[0] = src - base;
        dest[1] = 32;
        memcpy(&dest[2], src, 32);
        i2c0_transmit(USB2422_ADDRESS, dest, 34, 50000);
        SERCOM0->I2CM.CTRLB.bit.CMD = 0x03;
        while (SERCOM0->I2CM.SYNCBUSY.bit.SYSOP) {}
        wait_us(100);
    }
}

void USB2422_init() {
    //i2c_init();
    i2c0_init();  // IC2 clk must be high at USB2422 reset release time to signal SMB configuration
}

void USB2422_configure(){
    Usb2422 *pusb2422 = &USB2422_shadow;
    memset(pusb2422, 0, sizeof(Usb2422));

    uint16_t *serial_use    = (uint16_t *)SERNAME;                 // Default to use SERNAME from this file
    uint8_t   serial_length = sizeof(SERNAME) / sizeof(uint16_t);  // Default to use SERNAME from this file
// #ifndef MD_BOOTLOADER
//     uint32_t serial_ptrloc = (uint32_t)&_srom - 4;
// #else                                                      // MD_BOOTLOADER
//     uint32_t serial_ptrloc = (uint32_t)&_erom - 4;
// #endif                                                     // MD_BOOTLOADER
//     uint32_t serial_address = *(uint32_t *)serial_ptrloc;  // Address of bootloader's serial number if available

//     if (serial_address != 0xFFFFFFFF && serial_address < serial_ptrloc)  // Check for factory programmed serial address
//     {
//         if ((serial_address & 0xFF) % 4 == 0)  // Check alignment
//         {
//             serial_use    = (uint16_t *)(serial_address);
//             serial_length = 0;
//             while ((*(serial_use + serial_length) > 32 && *(serial_use + serial_length) < 127) && serial_length < BOOTLOADER_SERIAL_MAX_SIZE) {
//                 serial_length++;
//                 DBGC(DC_USB_CONFIGURE_GET_SERIAL);
//             }
//         }
//     }

    // configure Usb2422 registers
    pusb2422->VID.reg               = 0x04D8;  // from Microchip 4/19/2018
    pusb2422->PID.reg               = 0xEEC5;  // from Microchip 4/19/2018 = Massdrop, Inc. USB Hub
    pusb2422->DID.reg               = 0x0101;  // BCD 01.01
    pusb2422->CFG1.bit.SELF_BUS_PWR = 1;       // self powered for now
    pusb2422->CFG1.bit.HS_DISABLE   = 1;       // full or high speed
    // pusb2422->CFG2.bit.COMPOUND = 0; // compound device
    pusb2422->CFG3.bit.STRING_EN = 1;  // strings enabled
    // pusb2422->NRD.bit.PORT2_NR = 0; // MCU is non-removable
    pusb2422->MAXPB.reg = 20;  // 0mA
    pusb2422->HCMCB.reg = 20;  // 0mA
    pusb2422->MFRSL.reg = sizeof(MFRNAME) / sizeof(uint16_t);
    pusb2422->PRDSL.reg = sizeof(PRDNAME) / sizeof(uint16_t);
    pusb2422->SERSL.reg = serial_length;
    memcpy(pusb2422->MFRSTR, MFRNAME, sizeof(MFRNAME));
    memcpy(pusb2422->PRDSTR, PRDNAME, sizeof(PRDNAME));
    memcpy(pusb2422->SERSTR, serial_use, serial_length * sizeof(uint16_t));
    // pusb2422->BOOSTUP.bit.BOOST=3;    //upstream port
    // pusb2422->BOOSTDOWN.bit.BOOST1=0; // extra port
    // pusb2422->BOOSTDOWN.bit.BOOST2=2; //MCU is close
    pusb2422->STCD.bit.USB_ATTACH = 1;

    USB2422_write_block();
}
