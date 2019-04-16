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

#ifndef _USB2422_H_
#define _USB2422_H_

#include "config_usb.h" //From keyboard's directory

#define REV_USB2422        0x100

#define USB2422_ADDR       0x58 //I2C device address, one instance

#define USB2422_HUB_ACTIVE_GROUP    0   //PA
#define USB2422_HUB_ACTIVE_PIN      18  //18

/* -------- USB2422_VID : (USB2422L Offset: 0x00) (R/W 16) Vendor ID -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t VID_LSB : 8;
    uint16_t VID_MSB : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} USB2422_VID_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_PID : (USB2422L Offset: 0x02) (R/W 16) Product ID -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t PID_LSB : 8;
    uint16_t PID_MSB : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} USB2422_PID_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_DID : (USB2422L Offset: 0x04) (R/W 16) Device ID -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t DID_LSB : 8;
    uint16_t DID_MSB : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} USB2422_DID_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_CFG1 : (USB2422L Offset: 0x06) (R/W 8) Configuration Data Byte 1-------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t PORT_PWR : 1;
    uint8_t CURRENT_SNS : 2;
    uint8_t EOP_DISABLE : 1;
    uint8_t MTT_ENABLE : 1;
    uint8_t HS_DISABLE :1;
    uint8_t :1;
    uint8_t SELF_BUS_PWR : 1;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_CFG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_CFG2 : (USB2422L Offset: 0x07) (R/W 8) Configuration Data Byte 2-------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t : 3;
    uint8_t COMPOUND : 1;
    uint8_t OC_TIMER :2;
    uint8_t :1;
    uint8_t DYNAMIC : 1;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_CFG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_CFG3 : (USB2422L Offset: 0x08) (R/W 16) Configuration Data Byte 3-------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t STRING_EN : 1;
    uint8_t  :2;
    uint8_t PRTMAP_EN :1;
    uint8_t : 4;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_CFG3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_NRD : (USB2422L Offset: 0x09) (R/W 8) Non Removable Device -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t : 5;
    uint8_t PORT2_NR :1;
    uint8_t PORT1_NR :1;
    uint8_t : 1;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_NRD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_PDS : (USB2422L Offset: 0x0A) (R/W 8) Port Diable for Self-Powered Operation -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t : 1;
    uint8_t PORT1_DIS :1;
    uint8_t PORT2_DIS :1;
    uint8_t : 5;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_PDS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_PDB : (USB2422L Offset: 0x0B) (R/W 8) Port Diable for Bus-Powered Operation -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t : 1;
    uint8_t PORT1_DIS :1;
    uint8_t PORT2_DIS :1;
    uint8_t : 5;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_PDB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_MAXPS : (USB2422L Offset: 0x0C) (R/W 8) Max Power for Self-Powered Operation -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t MAX_PWR_SP : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_MAXPS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_MAXPB : (USB2422L Offset: 0x0D) (R/W 8) Max Power for Bus-Powered Operation -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t MAX_PWR_BP : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_MAXPB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_HCMCS : (USB2422L Offset: 0x0E) (R/W 8) Hub Controller Max Current for Self-Powered Operation -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t HC_MAX_C_SP : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_HCMCS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_HCMCB : (USB2422L Offset: 0x0F) (R/W 8) Hub Controller Max Current for Bus-Powered Operation -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t HC_MAX_C_BP : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_HCMCB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_PWRT : (USB2422L Offset: 0x10) (R/W 8) Power On Time -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t POWER_ON_TIME : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_PWRT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_LANGID LSB : (USB2422L Offset: 0x11) (R/W 16) Language ID -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t LANGID_LSB : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_LANGID_LSB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_LANGID MSB : (USB2422L Offset: 0x12) (R/W 16) Language ID -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t LANGID_MSB : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_LANGID_MSB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */


/* -------- USB2422_MFRSL : (USB2422L Offset: 0x13) (R/W 8) Manufacturer String Length -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t MFR_STR_LEN : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_MFRSL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_PRDSL : (USB2422L Offset: 0x14) (R/W 8) Product String Length -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t PRD_STR_LEN : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_PRDSL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_SERSL : (USB2422L Offset: 0x15) (R/W 8) Serial String Length -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t SER_STR_LEN : 8;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_SERSL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_MFRSTR : (USB2422L Offset: 0x16-53) (R/W 8) Maufacturer String -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef uint16_t USB2422_MFRSTR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_PRDSTR : (USB2422L Offset: 0x54-91) (R/W 8) Product String -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef uint16_t USB2422_PRDSTR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_SERSTR : (USB2422L Offset: 0x92-CF) (R/W 8) Serial String -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef uint16_t USB2422_SERSTR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_BCEN : (USB2422L Offset: 0xD0) (R/W 8) Battery Charging Enable -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t : 1;
    uint8_t PORT1_BCE :1;
    uint8_t PORT2_BCE :1;
    uint8_t : 5;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_BCEN_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_BOOSTUP : (USB2422L Offset: 0xF6) (R/W 8) Boost Upstream -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t BOOST :2;
    uint8_t : 6;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_BOOSTUP_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_BOOSTDOWN : (USB2422L Offset: 0xF8) (R/W 8) Boost Downstream -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t BOOST1 :2;
    uint8_t BOOST2 :2;
    uint8_t : 4;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_BOOSTDOWN_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_PRTSP : (USB2422L Offset: 0xFA) (R/W 8) Port Swap -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t : 1;
    uint8_t PORT1_SP :1;
    uint8_t PORT2_SP :1;
    uint8_t : 5;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_PRTSP_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* -------- USB2422_PRTR12 : (USB2422L Offset: 0xFB) (R/W 8) Port 1/2 Remap -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t PORT1_REMAP: 4;
    uint8_t PORT2_REMAP: 4;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_PRTR12_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
#define USB2422_PRTR12_DISABLE 0
#define USB2422_PRT12_P2TOL1 1
#define USB2422_PRT12_P2XTOL2 2
#define USB2422_PRT12_P1TOL1 1
#define USB2422_PRT12_P1XTOL2 2

/* -------- USB2422_STCD : (USB2422L Offset: 0xFF) (R/W 8) Status Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t USB_ATTACH: 1;
    uint8_t RESET: 1;
    uint8_t INTF_PWRDN: 1;
    uint8_t : 5;
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} USB2422_STCD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** \brief USB2422 device hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  USB2422_VID_Type          VID;        /**< \brief Offset: 0x00*/
  USB2422_PID_Type          PID;        /**< \brief Offset: 0x02*/
  USB2422_DID_Type          DID;        /**< \brief Offset: 0x04*/
  USB2422_CFG1_Type         CFG1;       /**< \brief Offset: 0x06*/
  USB2422_CFG2_Type         CFG2;       /**< \brief Offset: 0x07*/
  USB2422_CFG3_Type         CFG3;       /**< \brief Offset: 0x08*/
  USB2422_NRD_Type          NRD;        /**< \brief Offset: 0x09*/
  USB2422_PDS_Type          PDS;        /**< \brief Offset: 0x0A*/
  USB2422_PDB_Type          PDB;        /**< \brief Offset: 0x0B*/
  USB2422_MAXPS_Type        MAXPS;      /**< \brief Offset: 0x0C*/
  USB2422_MAXPB_Type        MAXPB;      /**< \brief Offset: 0x0D*/
  USB2422_HCMCS_Type        HCMCS;      /**< \brief Offset: 0x0E*/
  USB2422_HCMCB_Type        HCMCB;      /**< \brief Offset: 0x0F*/
  USB2422_PWRT_Type         PWRT;       /**< \brief Offset: 0x10*/
  USB2422_LANGID_LSB_Type   LANGID_LSB; /**< \brief Offset: 0x11*/
  USB2422_LANGID_MSB_Type   LANGID_MSB; /**< \brief Offset: 0x12*/
  USB2422_MFRSL_Type        MFRSL;      /**< \brief Offset: 0x13*/
  USB2422_PRDSL_Type        PRDSL;      /**< \brief Offset: 0x14*/
  USB2422_SERSL_Type        SERSL;      /**< \brief Offset: 0x15*/
  USB2422_MFRSTR_Type       MFRSTR[31]; /**< \brief Offset: 0x16*/
  USB2422_PRDSTR_Type       PRDSTR[31]; /**< \brief Offset: 0x54*/
  USB2422_SERSTR_Type       SERSTR[31]; /**< \brief Offset: 0x92*/
  USB2422_BCEN_Type         BCEN;       /**< \brief Offset: 0xD0*/
  uint8_t                   Reserved1[0x25];
  USB2422_BOOSTUP_Type      BOOSTUP;    /**< \brief Offset: 0xF6*/
  uint8_t                   Reserved2[0x1];
  USB2422_BOOSTDOWN_Type    BOOSTDOWN;  /**< \brief Offset: 0xF8*/
  uint8_t                   Reserved3[0x1];
  USB2422_PRTSP_Type        PRTSP;      /**< \brief Offset: 0xFA*/
  USB2422_PRTR12_Type       PRTR12;     /**< \brief Offset: 0xFB*/
  uint8_t                   Reserved4[0x3];
  USB2422_STCD_Type         STCD;       /**< \brief Offset: 0xFF*/
} Usb2422;
#endif

//When testing for USB enumeration, retry after this many ms
#define PORT_DETECT_RETRY_START             2000
#define PORT_DETECT_RETRY_INCREMENT         2000
#define PORT_DETECT_RETRY_MAX               10000

//Onboard ports must have an even number
//External ports must have an odd number
//The only exception is the unknown state
#define USB_HOST_PORT_1                     0
#define USB_HOST_PORT_1_EXT                 1
#define USB_HOST_PORT_2                     2
#define USB_HOST_PORT_2_EXT                 3
#define USB_HOST_PORT_UNKNOWN               4

//Macros to check host port assignment
#define USB_HOST_IS_1(host)                 (host == USB_HOST_PORT_1 || host == USB_HOST_PORT_1_EXT)
#define USB_HOST_IS_2(host)                 (host == USB_HOST_PORT_2 || host == USB_HOST_PORT_2_EXT)

//Macros to test if the sink device is connected to the onboard or external port
//Note: USBC_IS_SINK defined in the keyboard's config_adc.h
#define USBC_IS_SINK_ONB(a5, b5)            (ADC_USBC_IS_ONB(g_usb_host_port) && USBC_IS_SINK(a5, b5))
#define USBC_IS_SINK_EXT(a5, b5)            (ADC_USBC_IS_EXT(g_usb_host_port) && USBC_IS_SINK(a5, b5))

//Note: Due to the way timers are implemented, waits will always be slightly longer than defined
#define USBC_TIMER_ATTACH_WAIT              0
#define USBC_TIMER_DETACH                   1       //tCCDebounce
#define USBC_CFG_PERIOD                     5       //How often the extra USB port is checked (ms)(This multiple affects the accuracy of USB timers)
#define USBC_CFG_TCCDEBOUNCE                150     //tCCDebounce - Time a port shall wait before it can determine it is attached (ms)
#define USBC_CFG_TSRCDISCONNECT             0       //tSRCDisconnect - Time a Source shall detect the SRC.Open state (As fast as possible)(ms)
#define USBC_CFG_TVCONNDISCHARGE            100     //UnattachedWait time for VCONN discharge
#define USBC_CFG_TDISABLED                  100     //Minimum time to wait after state machine disabled

#define USB_STATE_UNKNOWN                   0       //Custom state for init
#define USB_STATE_UNATTACHED_SRC            1       //Directed from any state
                                                    //From USB_STATE_UNATTACHED_WAIT_SRC after Discharge Complete and Vconn Off
                                                    //From USB_STATE_ATTACHED_SRC if Sink Removed and Vconn was Off
                                                    //From USB_STATE_ATTACH_WAIT_SRC if Connection Removed
#define USB_STATE_ATTACH_WAIT_SRC           2       //From USB_STATE_UNATTACHED_SRC when Connection detected
#define USB_STATE_ATTACHED_SRC              3       //From USB_STATE_ATTACHWAIT_SRC when Vbus at vSafe0V and Sink Detected for tCCDebounce
#define USB_STATE_UNATTACHED_WAIT_SRC       4       //From USB_STATE_ATTACHED_SRC when Sink Removed and Vconn was On
#define USB_STATE_DISABLED_WAIT             100     //Custom state for USB 5V Bus discharge then to USB_STATE_DISABLED_WAIT
#define USB_STATE_DISABLED                  101     //Directed from any state
#define USB_STATE_DISABLED_UNTIL_DETACH     102     //Custom state for when USB 5V Bus overloads and device must be detached before use

//USB Type-C State machine for a SOURCE
typedef struct usbc_s {
    uint8_t state;
    uint16_t timer;
} usbc_t;

extern uint8_t g_usb_host_port;
extern uint8_t usb_extra_state;
extern uint8_t usb_gcr_auto;
extern usbc_t usbc;
extern uint16_t usbc_cc_a5_v;
extern uint16_t usbc_cc_b5_v;
extern float usbc_cc_a5_v_avg;
extern float usbc_cc_b5_v_avg;

void USB2422_init(void);
void USB_reset(void);
void USB_configure(void);
uint16_t USB_active(void);
uint8_t USB_detect_host(void);
uint8_t USB2422_Port_Detect_Init(void);
void USB_HandleExtraDevice(void);
void usbc_enable(void);
void usbc_disable(void);
void usbc_task(void);

//Keyboard defined functions
void usb_set_host_kb(uint8_t con, uint8_t rp_best_index);
void usb_set_extra_kb(uint8_t con);
void usb_init_host_detection_kb(void);
uint8_t usb_attach_port_configure_kb(uint8_t g_usb_host_port, uint16_t usbc_cc_a5_v, uint16_t usbc_cc_b5_v);

#endif //_USB2422_H_

