/**
  ******************************************************************************
  * @file    usb_regs.h
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    19-March-2012
  * @brief   hardware registers
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#ifndef __USB_OTG_REGS_H__
#define __USB_OTG_REGS_H__

typedef struct //000h
{
  __IO uint32_t GOTGCTL;      /* USB_OTG Control and Status Register    000h*/
  __IO uint32_t GOTGINT;      /* USB_OTG Interrupt Register             004h*/
  __IO uint32_t GAHBCFG;      /* Core AHB Configuration Register    008h*/
  __IO uint32_t GUSBCFG;      /* Core USB Configuration Register    00Ch*/
  __IO uint32_t GRSTCTL;      /* Core Reset Register                010h*/
  __IO uint32_t GINTSTS;      /* Core Interrupt Register            014h*/
  __IO uint32_t GINTMSK;      /* Core Interrupt Mask Register       018h*/
  __IO uint32_t GRXSTSR;      /* Receive Sts Q Read Register        01Ch*/
  __IO uint32_t GRXSTSP;      /* Receive Sts Q Read & POP Register  020h*/
  __IO uint32_t GRXFSIZ;      /* Receive FIFO Size Register         024h*/
  __IO uint32_t DIEPTXF0_HNPTXFSIZ;   /* EP0 / Non Periodic Tx FIFO Size Register 028h*/
  __IO uint32_t HNPTXSTS;     /* Non Periodic Tx FIFO/Queue Sts reg 02Ch*/
  uint32_t Reserved30[2];     /* Reserved                           030h*/
  __IO uint32_t GCCFG;        /* General Purpose IO Register        038h*/
  __IO uint32_t CID;          /* User ID Register                   03Ch*/
  uint32_t  Reserved40[48];   /* Reserved                      040h-0FFh*/
  __IO uint32_t HPTXFSIZ; /* Host Periodic Tx FIFO Size Reg     100h*/
  __IO uint32_t DIEPTXF[3];/* dev Periodic Transmit FIFO */
}
USB_OTG_GREGS;

typedef struct // 800h
{
  __IO uint32_t DCFG;         /* dev Configuration Register   800h*/
  __IO uint32_t DCTL;         /* dev Control Register         804h*/
  __IO uint32_t DSTS;         /* dev Status Register (RO)     808h*/
  uint32_t Reserved0C;           /* Reserved                     80Ch*/
  __IO uint32_t DIEPMSK;   /* dev IN Endpoint Mask         810h*/
  __IO uint32_t DOEPMSK;  /* dev OUT Endpoint Mask        814h*/
  __IO uint32_t DAINT;     /* dev All Endpoints Itr Reg    818h*/
  __IO uint32_t DAINTMSK; /* dev All Endpoints Itr Mask   81Ch*/
  uint32_t  Reserved20;          /* Reserved                     820h*/
  uint32_t Reserved9;       /* Reserved                     824h*/
  __IO uint32_t DVBUSDIS;    /* dev VBUS discharge Register  828h*/
  __IO uint32_t DVBUSPULSE;  /* dev VBUS Pulse Register      82Ch*/
  __IO uint32_t DTHRCTL;     /* dev thr                      830h*/
  __IO uint32_t DIEPEMPMSK; /* dev empty msk             834h*/
}
USB_OTG_DREGS;

typedef struct
{
  __IO uint32_t DIEPCTL; /* dev IN Endpoint Control Reg 900h + (ep_num * 20h) + 00h*/
  uint32_t Reserved04;             /* Reserved                       900h + (ep_num * 20h) + 04h*/
  __IO uint32_t DIEPINT; /* dev IN Endpoint Itr Reg     900h + (ep_num * 20h) + 08h*/
  uint32_t Reserved0C;             /* Reserved                       900h + (ep_num * 20h) + 0Ch*/
  __IO uint32_t DIEPTSIZ; /* IN Endpoint Txfer Size   900h + (ep_num * 20h) + 10h*/
  uint32_t Reserved14;
  __IO uint32_t DTXFSTS;/*IN Endpoint Tx FIFO Status Reg 900h + (ep_num * 20h) + 18h*/
  uint32_t Reserved1C;             /* Reserved  900h+(ep_num*20h)+1Ch-900h+ (ep_num * 20h) + 1Ch*/
}
USB_OTG_INEPREGS;

typedef struct
{
  __IO uint32_t DOEPCTL;       /* dev OUT Endpoint Control Reg  B00h + (ep_num * 20h) + 00h*/
  uint32_t Reserved04;         /* Reserved                      B00h + (ep_num * 20h) + 04h*/
  __IO uint32_t DOEPINT;       /* dev OUT Endpoint Itr Reg      B00h + (ep_num * 20h) + 08h*/
  uint32_t Reserved0C;         /* Reserved                      B00h + (ep_num * 20h) + 0Ch*/
  __IO uint32_t DOEPTSIZ;      /* dev OUT Endpoint Txfer Size   B00h + (ep_num * 20h) + 10h*/
  uint32_t Reserved14[3];
}
USB_OTG_OUTEPREGS;

typedef struct
{
  __IO uint32_t HCFG;             /* Host Configuration Register    400h*/
  __IO uint32_t HFIR;      /* Host Frame Interval Register   404h*/
  __IO uint32_t HFNUM;         /* Host Frame Nbr/Frame Remaining 408h*/
  uint32_t Reserved40C;                   /* Reserved                       40Ch*/
  __IO uint32_t HPTXSTS;   /* Host Periodic Tx FIFO/ Queue Status 410h*/
  __IO uint32_t HAINT;   /* Host All Channels Interrupt Register 414h*/
  __IO uint32_t HAINTMSK;   /* Host All Channels Interrupt Mask 418h*/
}
USB_OTG_HREGS;

typedef struct
{
  __IO uint32_t HCCHAR;
  __IO uint32_t HCSPLT;
  __IO uint32_t HCINT;
  __IO uint32_t HCINTMSK;
  __IO uint32_t HCTSIZ;
  uint32_t Reserved[3];
}
USB_OTG_HC_REGS;

typedef struct
{
    USB_OTG_GREGS         GREGS;
    uint32_t RESERVED0[188];
    USB_OTG_HREGS         HREGS;
    uint32_t RESERVED1[9];
    __IO uint32_t         HPRT;
    uint32_t RESERVED2[47];
    USB_OTG_HC_REGS       HC_REGS[8];
    uint32_t RESERVED3[128];
    USB_OTG_DREGS         DREGS;
    uint32_t RESERVED4[50];
    USB_OTG_INEPREGS      INEP_REGS[4];
    uint32_t RESERVED5[96];
    USB_OTG_OUTEPREGS     OUTEP_REGS[4];
    uint32_t RESERVED6[160];
    __IO uint32_t         PCGCCTL;
    uint32_t RESERVED7[127];
    __IO uint32_t         FIFO[4][1024];
}
USB_OTG_CORE_REGS;


#define OTG_FS_BASE (AHB2PERIPH_BASE + 0x0000)
#define OTG_FS ((USB_OTG_CORE_REGS *) OTG_FS_BASE)

#endif //__USB_OTG_REGS_H__

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

