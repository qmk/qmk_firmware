/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2012 - 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name   : usb_iobitmask.h
* $Rev: 1116 $
* $Date:: 2014-07-09 16:29:19 +0900#$
* Description : USB register define header
*******************************************************************************/
#ifndef USB_IOBITMASK_H
#define USB_IOBITMASK_H

/*==============================================*/
/* SYSCFG                                       */
/*==============================================*/
#define     USB_SYSCFG_USBE                 (0x0001u)
#define     USB_SYSCFG_UPLLE                (0x0002u)
#define     USB_SYSCFG_UCKSEL               (0x0004u)
/* #define  USB_SYSCFG_RESERVED1            (0x0008u) */
#define     USB_SYSCFG_DPRPU                (0x0010u)
#define     USB_SYSCFG_DRPD                 (0x0020u)
#define     USB_SYSCFG_DCFM                 (0x0040u)
#define     USB_SYSCFG_HSE                  (0x0080u)
/* #define  USB_SYSCFG_RESERVED2            (0xFF00u) */

#define     USB_SYSCFG_USBE_SHIFT           (0)
#define     USB_SYSCFG_UPLLE_SHIFT          (1)
#define     USB_SYSCFG_UCKSEL_SHIFT         (2)
/* #define  USB_SYSCFG_RESERVED1_SHIFT      (3) */
#define     USB_SYSCFG_DPRPU_SHIFT          (4)
#define     USB_SYSCFG_DRPD_SHIFT           (5)
#define     USB_SYSCFG_DCFM_SHIFT           (6)
#define     USB_SYSCFG_HSE_SHIFT            (7)
/* #define  USB_SYSCFG_RESERVED2_SHIFT      (8) */

/*==============================================*/
/* BUSWAIT                                      */
/*==============================================*/
#define     USB_BUSWAIT_BWAIT               (0x003Fu)

#define     USB_BUSWAIT_BWAIT_SHIFT         (0)

/*==============================================*/
/* SYSSTS0                                      */
/*==============================================*/
#define     USB_SYSSTS0_LNST                (0x0003u)
#define     USB_SYSSTS0_SOFEA               (0x0020u)
#define     USB_SYSSTS0_HTACT               (0x0040u)

#define     USB_SYSSTS0_LNST_SHIFT          (0)
#define     USB_SYSSTS0_SOFEA_SHIFT         (5)
#define     USB_SYSSTS0_HTACT_SHIFT         (6)

/*==============================================*/
/* DVSTCTR0                                     */
/*==============================================*/
#define     USB_DVSTCTR0_RHST               (0x0007u)
/* #define  USB_DVSTCTR0_RESERVED           (0x0008u) */
#define     USB_DVSTCTR0_UACT               (0x0010u)
#define     USB_DVSTCTR0_RESUME             (0x0020u)
#define     USB_DVSTCTR0_USBRST             (0x0040u)
#define     USB_DVSTCTR0_RWUPE              (0x0080u)
#define     USB_DVSTCTR0_WKUP               (0x0100u)

#define     USB_DVSTCTR0_RHST_SHIFT         (0)
/* #define  USB_DVSTCTR0_RESERVED_SHIFT     (3) */
#define     USB_DVSTCTR0_UACT_SHIFT         (4)
#define     USB_DVSTCTR0_RESUME_SHIFT       (5)
#define     USB_DVSTCTR0_USBRST_SHIFT       (6)
#define     USB_DVSTCTR0_RWUPE_SHIFT        (7)
#define     USB_DVSTCTR0_WKUP_SHIFT         (8)

/*==============================================*/
/* TESTMODE                                     */
/*==============================================*/
#define     USB_TESTMODE_UTST               (0x000Fu)
/* #define  USB_TESTMODE_RESERVED           (0xFFF0u) */

#define     USB_TESTMODE_UTST_SHIFT         (0)
/* #define  USB_TESTMODE_RESERVED_SHIFT     (4) */

/*==============================================*/
/* DnFBCFG                                      */
/*==============================================*/
/* #define      USB_DnFBCFG_RESERVED1       (0x000Fu) */
#define     USB_DnFBCFG_TENDE               (0x0010u)
/* #define      USB_DnFBCFG_RESERVED2       (0x0FE0u) */
#define     USB_DnFBCFG_DFACC               (0x3000u)
/* #define      USB_DnFBCFG_RESERVED3       (0xC000u) */

/* #define  USB_DnFBCFG_RESERVED1_SHIFT     (0) */
#define     USB_DnFBCFG_TENDE_SHIFT         (4)
/* #define  USB_DnFBCFG_RESERVED2_SHIFT     (5) */
#define     USB_DnFBCFG_DFACC_SHIFT         (12)
/* #define  USB_DnFBCFG_RESERVED3_SHIFT     (14) */

/*==============================================*/
/* CFIFO                                        */
/*==============================================*/
#define     USB_CFIFO_FIFOPORT              (0xFFFFFFFFuL)

#define     USB_CFIFO_FIFOPORT_SHIFT        (0)

/*==============================================*/
/* DnFIFO                                       */
/*==============================================*/
#define     USB_DnFIFO_FIFOPORT             (0xFFFFFFFFuL)

#define     USB_DnFIFO_FIFOPORT_SHIFT       (0)

/*==============================================*/
/* CFIFOSEL                                     */
/*==============================================*/
#define     USB_CFIFOSEL_CURPIPE            (0x000Fu)
/* #define  USB_CFIFOSEL_RESERVED1          (0x0010u) */
#define     USB_CFIFOSEL_ISEL_              (0x0020u)
/* #define  USB_CFIFOSEL_RESERVED2          (0x00C0u) */
#define     USB_CFIFOSEL_BIGEND             (0x0100u)
/* #define  USB_CFIFOSEL_RESERVED3          (0x0200u) */
#define     USB_CFIFOSEL_MBW                (0x0C00u)
/* #define  USB_CFIFOSEL_RESERVED4          (0x3000u) */
#define     USB_CFIFOSEL_REW                (0x4000u)
#define     USB_CFIFOSEL_RCNT               (0x8000u)

#define     USB_CFIFOSEL_CURPIPE_SHIFT      (0)
/* #define  USB_CFIFOSEL_RESERVED1_SHIFT    (4) */
#define     USB_CFIFOSEL_ISEL_SHIFT_        (5)
/* #define  USB_CFIFOSEL_RESERVED2_SHIFT    (6) */
#define     USB_CFIFOSEL_BIGEND_SHIFT       (8)
/* #define  USB_CFIFOSEL_RESERVED3_SHIFT    (9) */
#define     USB_CFIFOSEL_MBW_SHIFT          (10)
/* #define  USB_CFIFOSEL_RESERVED4_SHIFT    (12) */
#define     USB_CFIFOSEL_REW_SHIFT          (14)
#define     USB_CFIFOSEL_RCNT_SHIFT         (15)

/*==============================================*/
/* DnFIFOSEL                                    */
/*==============================================*/
#define     USB_DnFIFOSEL_CURPIPE           (0x000Fu)
/* #define  USB_DnFIFOSEL_RESERVED1         (0x00F0u) */
#define     USB_DnFIFOSEL_BIGEND            (0x0100u)
/* #define  USB_DnFIFOSEL_RESERVED2         (0x0200u) */
#define     USB_DnFIFOSEL_MBW               (0x0C00u)
#define     USB_DnFIFOSEL_DREQE             (0x1000u)
#define     USB_DnFIFOSEL_DCLRM             (0x2000u)
#define     USB_DnFIFOSEL_REW               (0x4000u)
#define     USB_DnFIFOSEL_RCNT              (0x8000u)

#define     USB_DnFIFOSEL_CURPIPE_SHIFT     (0)
/* #define  USB_DnFIFOSEL_RESERVED1_SHIFT   (4) */
#define     USB_DnFIFOSEL_BIGEND_SHIFT      (8)
/* #define  USB_DnFIFOSEL_RESERVED2_SHIFT   (9) */
#define     USB_DnFIFOSEL_MBW_SHIFT         (10)
#define     USB_DnFIFOSEL_DREQE_SHIFT       (12)
#define     USB_DnFIFOSEL_DCLRM_SHIFT       (13)
#define     USB_DnFIFOSEL_REW_SHIFT         (14)
#define     USB_DnFIFOSEL_RCNT_SHIFT        (15)

/*==============================================*/
/* CFIFOCTR                                     */
/*==============================================*/
#define     USB_CFIFOCTR_DTLN               (0x0FFFu)
/* #define  USB_CFIFOCTR_RESERVED           (0x1000u) */
#define     USB_CFIFOCTR_FRDY               (0x2000u)
#define     USB_CFIFOCTR_BCLR               (0x4000u)
#define     USB_CFIFOCTR_BVAL               (0x8000u)

#define     USB_CFIFOCTR_DTLN_SHIFT         (0)
/* #define  USB_CFIFOCTR_RESERVED_SHIFT     (12) */
#define     USB_CFIFOCTR_FRDY_SHIFT         (13)
#define     USB_CFIFOCTR_BCLR_SHIFT         (14)
#define     USB_CFIFOCTR_BVAL_SHIFT         (15)

/*==============================================*/
/* DnFIFOCTR                                    */
/*==============================================*/
#define     USB_DnFIFOCTR_DTLN              (0x0FFFu)
/* #define  USB_DnFIFOCTR_RESERVED          (0x1000u) */
#define     USB_DnFIFOCTR_FRDY              (0x2000u)
#define     USB_DnFIFOCTR_BCLR              (0x4000u)
#define     USB_DnFIFOCTR_BVAL              (0x8000u)

#define     USB_DnFIFOCTR_DTLN_SHIFT        (0)
/* #define  USB_DnFIFOCTR_RESERVED_SHIFT    (12) */
#define     USB_DnFIFOCTR_FRDY_SHIFT        (13)
#define     USB_DnFIFOCTR_BCLR_SHIFT        (14)
#define     USB_DnFIFOCTR_BVAL_SHIFT        (15)

/*==============================================*/
/* INTENB0                                      */
/*==============================================*/
/* #define  USB_INTENB0_RESERVED            (0x00FFu) */
#define     USB_INTENB0_BRDYE               (0x0100u)
#define     USB_INTENB0_NRDYE               (0x0200u)
#define     USB_INTENB0_BEMPE               (0x0400u)
#define     USB_INTENB0_CTRE                (0x0800u)
#define     USB_INTENB0_DVSE                (0x1000u)
#define     USB_INTENB0_SOFE                (0x2000u)
#define     USB_INTENB0_RSME                (0x4000u)
#define     USB_INTENB0_VBSE                (0x8000u)

/* #define  USB_INTENB0_RESERVED_SHIFT      (0) */
#define     USB_INTENB0_BRDYE_SHIFT         (8)
#define     USB_INTENB0_NRDYE_SHIFT         (9)
#define     USB_INTENB0_BEMPE_SHIFT         (10)
#define     USB_INTENB0_CTRE_SHIFT          (11)
#define     USB_INTENB0_DVSE_SHIFT          (12)
#define     USB_INTENB0_SOFE_SHIFT          (13)
#define     USB_INTENB0_RSME_SHIFT          (14)
#define     USB_INTENB0_VBSE_SHIFT          (15)

/*==============================================*/
/* INTENB1                                      */
/*==============================================*/
/* #define  USB_INTENB1_RESERVED1           (0x000Fu) */
#define     USB_INTENB1_SACKE               (0x0010u)
#define     USB_INTENB1_SIGNE               (0x0020u)
#define     USB_INTENB1_EOFERRE             (0x0040u)
/* #define  USB_INTENB1_RESERVED2           (0x0780u) */
#define     USB_INTENB1_ATTCHE              (0x0800u)
#define     USB_INTENB1_DTCHE               (0x1000u)
/* #define  USB_INTENB1_RESERVED3           (0x2000u) */
#define     USB_INTENB1_BCHGE               (0x4000u)
/* #define  USB_INTENB1_RESERVED4           (0x8000u) */

/* #define  USB_INTENB1_RESERVED1_SHIFT     (0) */
#define     USB_INTENB1_SACKE_SHIFT         (4)
#define     USB_INTENB1_SIGNE_SHIFT         (5)
#define     USB_INTENB1_EOFERRE_SHIFT       (6)
/* #define  USB_INTENB1_RESERVED2_SHIFT     (7) */
#define     USB_INTENB1_ATTCHE_SHIFT        (11)
#define     USB_INTENB1_DTCHE_SHIFT         (12)
/* #define  USB_INTENB1_RESERVED3_SHIFT     (13) */
#define     USB_INTENB1_BCHGE_SHIFT         (14)
/* #define  USB_INTENB1_RESERVED4_SHIFT     (15) */

/*==============================================*/
/* BRDYENB                                      */
/*==============================================*/
#define     USB_BRDYENB                     (0xFFFFu)

#define     USB_BRDYENB_SHIFT               (0)

/*==============================================*/
/* NRDYENB                                      */
/*==============================================*/
#define     USB_NRDYENB                     (0xFFFFu)

#define     USB_NRDYENB_SHIFT               (0)

/*==============================================*/
/* BEMPENB                                      */
/*==============================================*/
#define     USB_BEMPENB                     (0xFFFFu)

#define     USB_BEMPENB_SHIFT               (0)

/*==============================================*/
/* SOFCFG                                       */
/*==============================================*/
/* #define  USB_SOFCFG_RESERVED1            (0x003Fu) */
#define     USB_SOFCFG_BRDYM                (0x0040u)
/* #define  USB_SOFCFG_RESERVED2            (0x0080u) */
#define     USB_SOFCFG_TRNENSEL             (0x0100u)
/* #define  USB_SOFCFG_RESERVED3            (0xFE00u) */

/* #define  USB_SOFCFG_RESERVED1_SHIFT      (0) */
#define     USB_SOFCFG_BRDYM_SHIFT          (6)
/* #define  USB_SOFCFG_RESERVED2_SHIFT      (7) */
#define     USB_SOFCFG_TRNENSEL_SHIFT       (8)
/* #define  USB_SOFCFG_RESERVED3_SHIFT      (9) */

/*==============================================*/
/* INTSTS0                                      */
/*==============================================*/
#define     USB_INTSTS0_CTSQ                (0x0007u)
#define     USB_INTSTS0_VALID               (0x0008u)
#define     USB_INTSTS0_DVSQ                (0x0070u)
#define     USB_INTSTS0_VBSTS               (0x0080u)
#define     USB_INTSTS0_BRDY                (0x0100u)
#define     USB_INTSTS0_NRDY                (0x0200u)
#define     USB_INTSTS0_BEMP                (0x0400u)
#define     USB_INTSTS0_CTRT                (0x0800u)
#define     USB_INTSTS0_DVST                (0x1000u)
#define     USB_INTSTS0_SOFR                (0x2000u)
#define     USB_INTSTS0_RESM                (0x4000u)
#define     USB_INTSTS0_VBINT               (0x8000u)

#define     USB_INTSTS0_CTSQ_SHIFT          (0)
#define     USB_INTSTS0_VALID_SHIFT         (3)
#define     USB_INTSTS0_DVSQ_SHIFT          (4)
#define     USB_INTSTS0_VBSTS_SHIFT         (7)
#define     USB_INTSTS0_BRDY_SHIFT          (8)
#define     USB_INTSTS0_NRDY_SHIFT          (9)
#define     USB_INTSTS0_BEMP_SHIFT          (10)
#define     USB_INTSTS0_CTRT_SHIFT          (11)
#define     USB_INTSTS0_DVST_SHIFT          (12)
#define     USB_INTSTS0_SOFR_SHIFT          (13)
#define     USB_INTSTS0_RESM_SHIFT          (14)
#define     USB_INTSTS0_VBINT_SHIFT         (15)

/*==============================================*/
/* INTSTS1                                      */
/*==============================================*/
/* #define  USB_INTSTS1_RESERVED1           (0x000Fu) */
#define     USB_INTSTS1_SACK                (0x0010u)
#define     USB_INTSTS1_SIGN                (0x0020u)
#define     USB_INTSTS1_EOFERR              (0x0040u)
/* #define  USB_INTSTS1_RESERVED2           (0x0780u) */
#define     USB_INTSTS1_ATTCH               (0x0800u)
#define     USB_INTSTS1_DTCH                (0x1000u)
/* #define  USB_INTSTS1_RESERVED3           (0x2000u) */
#define     USB_INTSTS1_BCHG                (0x4000u)
/* #define  USB_INTSTS1_RESERVED4           (0x8000u) */

/* #define  USB_INTSTS1_RESERVED1_SHIFT     (0) */
#define     USB_INTSTS1_SACK_SHIFT          (4)
#define     USB_INTSTS1_SIGN_SHIFT          (5)
#define     USB_INTSTS1_EOFERR_SHIFT        (6)
/* #define  USB_INTSTS1_RESERVED2_SHIFT     (7) */
#define     USB_INTSTS1_ATTCH_SHIFT         (11)
#define     USB_INTSTS1_DTCH_SHIFT          (12)
/* #define  USB_INTSTS1_RESERVED3_SHIFT     (13) */
#define     USB_INTSTS1_BCHG_SHIFT          (14)
/* #define  USB_INTSTS1_RESERVED4_SHIFT     (15) */

/*==============================================*/
/* BRDYSTS                                      */
/*==============================================*/
#define     USB_BRDYSTS                     (0xFFFFu)

#define     USB_BRDYSTS_SHIFT               (0)

/*==============================================*/
/* NRDYSTS                                      */
/*==============================================*/
#define     USB_NRDYSTS                     (0xFFFFu)

#define     USB_NRDYSTS_SHIFT               (0)

/*==============================================*/
/* BEMPSTS                                      */
/*==============================================*/
#define     USB_BEMPSTS                     (0xFFFFu)

#define     USB_BEMPSTS_SHIFT               (0)

/*==============================================*/
/* FRMNUM                                       */
/*==============================================*/
#define     USB_FRMNUM_FRNM                 (0x07FFu)
/* #define  USB_FRMNUM_RESERVED             (0x3800u) */
#define     USB_FRMNUM_CRCE                 (0x4000u)
#define     USB_FRMNUM_OVRN                 (0x8000u)

#define     USB_FRMNUM_FRNM_SHIFT           (0)
/* #define  USB_FRMNUM_RESERVED_SHIFT       (11) */
#define     USB_FRMNUM_CRCE_SHIFT           (14)
#define     USB_FRMNUM_OVRN_SHIFT           (15)

/*==============================================*/
/* UFRMNUM                                      */
/*==============================================*/
#define     USB_UFRMNUM_UFRNM               (0x0007u)
/* #define  USB_UFRMNUM_RESERVED            (0xFFF8u) */

#define     USB_UFRMNUM_UFRNM_SHIFT         (0)
/* #define  USB_UFRMNUM_RESERVED_SHIFT      (3) */

/*==============================================*/
/* USBADDR                                      */
/*==============================================*/
#define     USB_USBADDR_USBADDR             (0x007Fu)
/* #define  USB_USBADDR_RESERVED            (0xFF80u) */

#define     USB_USBADDR_USBADDR_SHIFT       (0)
/* #define  USB_USBADDR_RESERVED_SHIFT      (7) */

/*==============================================*/
/* USBREQ                                       */
/*==============================================*/
#define     USB_USBREQ_BMREQUESTTYPE        (0x00FFu)
#define     USB_USBREQ_BREQUEST             (0xFF00u)

#define     USB_USBREQ_BMREQUESTTYPE_SHIFT  (0)
#define     USB_USBREQ_BREQUEST_SHIFT       (8)

/*==============================================*/
/* USBVAL                                       */
/*==============================================*/
#define     USB_USBVAL                      (0xFFFFu)

#define     USB_USBVAL_SHIFT                (0)

/*==============================================*/
/* USBINDX                                      */
/*==============================================*/
#define     USB_USBINDX                     (0xFFFFu)

#define     USB_USBINDX_SHIFT               (0)

/*==============================================*/
/* USBLENG                                      */
/*==============================================*/
#define     USB_USBLENG                     (0xFFFFu)

#define     USB_USBLENG_SHIFT               (0)

/*==============================================*/
/* DCPCFG                                       */
/*==============================================*/
/* #define  USB_DCPCFG_RESERVED1            (0x000Fu) */
#define     USB_DCPCFG_DIR                  (0x0010u)
/* #define  USB_DCPCFG_RESERVED2            (0x0060u) */
#define     USB_DCPCFG_SHTNAK               (0x0080u)
#define     USB_DCPCFG_CNTMD                (0x0100u)
/* #define  USB_DCPCFG_RESERVED3            (0xFE00u) */

/* #define  USB_DCPCFG_RESERVED1_SHIFT      (0) */
#define     USB_DCPCFG_DIR_SHIFT            (4)
/* #define  USB_DCPCFG_RESERVED2_SHIFT      (5) */
#define     USB_DCPCFG_SHTNK_SHIFT          (7)
#define     USB_DCPCFG_CNTMD_SHIFT          (8)
/* #define  USB_DCPCFG_RESERVED3            (9) */

/*==============================================*/
/* DCPMAXP                                      */
/*==============================================*/
#define     USB_DCPMAXP_MXPS                (0x007Fu)
/* #define  USB_DCPMAXP_RESERVED            (0x0F80u) */
#define     USB_DCPMAXP_DEVSEL              (0xF000u)

#define     USB_DCPMAXP_MXPS_SHIFT          (0)
/* #define  USB_DCPMAXP_RESERVED_SHIFT      (7) */
#define     USB_DCPMAXP_DEVSEL_SHIFT        (12)

/*==============================================*/
/* DCPCTR                                       */
/*==============================================*/
#define     USB_DCPCTR_PID                  (0x0003u)
#define     USB_DCPCTR_CCPL                 (0x0004u)
/* #define  USB_DCPCTR_RESERVED1            (0x0008u) */
#define     USB_DCPCTR_PINGE                (0x0010u)
#define     USB_DCPCTR_PBUSY                (0x0020u)
#define     USB_DCPCTR_SQMON                (0x0040u)
#define     USB_DCPCTR_SQSET                (0x0080u)
#define     USB_DCPCTR_SQCLR                (0x0100u)
/* #define  USB_DCPCTR_RESERVED2            (0x0600u) */
#define     USB_DCPCTR_SUREQCLR             (0x0800u)
#define     USB_DCPCTR_CSSTS                (0x1000u)
#define     USB_DCPCTR_CSCLR                (0x2000u)
#define     USB_DCPCTR_SUREQ                (0x4000u)
#define     USB_DCPCTR_BSTS                 (0x8000u)

#define     USB_DCPCTR_PID_SHIFT            (0)
#define     USB_DCPCTR_CCPL_SHIFT           (2)
/* #define  USB_DCPCTR_RESERVED1_SHIFT      (3) */
#define     USB_DCPCTR_PINGE_SHIFT          (4)
#define     USB_DCPCTR_PBUSY_SHIFT          (5)
#define     USB_DCPCTR_SQMON_SHIFT          (6)
#define     USB_DCPCTR_SQSET_SHIFT          (7)
#define     USB_DCPCTR_SQCLR_SHIFT          (8)
/* #define  USB_DCPCTR_RESERVED2_SHIFT      (9) */
#define     USB_DCPCTR_SUREQCLR_SHIFT       (11)
#define     USB_DCPCTR_CSSTS_SHIFT          (12)
#define     USB_DCPCTR_CSCLR_SHIFT          (13)
#define     USB_DCPCTR_SUREQ_SHIFT          (14)
#define     USB_DCPCTR_BSTS_SHIFT           (15)

/*==============================================*/
/* PIPESEL                                      */
/*==============================================*/
#define     USB_PIPESEL_PIPESEL             (0x000Fu)
/* #define  USB_PIPESEL_RESERVED            (0xFFF0u) */

#define     USB_PIPESEL_PIPESEL_SHIFT       (0)
/* #define  USB_PIPESEL_RESERVED_SHIFT      (4) */

/*==============================================*/
/* PIPECFG                                      */
/*==============================================*/
#define     USB_PIPECFG_EPNUM               (0x000Fu)
#define     USB_PIPECFG_DIR                 (0x0010u)
/* #define  USB_PIPECFG_RESERVED1           (0x0060u) */
#define     USB_PIPECFG_SHTNAK              (0x0080u)
#define     USB_PIPECFG_CNTMD               (0x0100u)
#define     USB_PIPECFG_DBLB                (0x0200u)
#define     USB_PIPECFG_BFRE                (0x0400u)
/* #define  USB_PIPECFG_RESERVED2           (0x3800u) */
#define     USB_PIPECFG_TYPE                (0xC000u)

#define     USB_PIPECFG_EPNUM_SHIFT         (0)
#define     USB_PIPECFG_DIR_SHIFT           (4)
/* #define  USB_PIPECFG_RESERVED1_SHIFT     (5) */
#define     USB_PIPECFG_SHTNAK_SHIFT        (7)
#define     USB_PIPECFG_CNTMD_SHIFT         (8)
#define     USB_PIPECFG_DBLB_SHIFT          (9)
#define     USB_PIPECFG_BFRE_SHIFT          (10)
/* #define  USB_PIPECFG_RESERVED2_SHIFT     (11) */
#define     USB_PIPECFG_TYPE_SHIFT          (14)

/*==============================================*/
/* PIPEBUF                                      */
/*==============================================*/
#define     USB_PIPEBUF_BUFNMB              (0x00FFu)
/* #define  USB_PIPEBUF_RESERVED1           (0x0300u) */
#define     USB_PIPEBUF_BUFSIZE             (0x7C00u)
/* #define  USB_PIPEBUF_RESERVED2           (0x8000u) */

#define     USB_PIPEBUF_BUFNMB_SHIFT        (0)
/* #define  USB_PIPEBUF_RESERVED1_SHIFT     (8) */
#define     USB_PIPEBUF_BUFSIZE_SHIFT       (10)
/* #define  USB_PIPEBUF_RESERVED2_SHIFT     (15) */

/*==============================================*/
/* PIPEMAXP                                     */
/*==============================================*/
#define     USB_PIPEMAXP_MXPS               (0x07FFu)
/* #define  USB_PIPEMAXP_RESERVED           (0x0800u) */
#define     USB_PIPEMAXP_DEVSEL             (0xF000u)

#define     USB_PIPEMAXP_MXPS_SHIFT         (0)
/* #define  USB_PIPEMAXP_RESERVED_SHIFT     (11) */
#define     USB_PIPEMAXP_DEVSEL_SHIFT       (12)

/*==============================================*/
/* PIPEPERI                                     */
/*==============================================*/
#define     USB_PIPEPERI_IITV               (0x0007u)
/* #define  USB_PIPEPERI_RESERVED1          (0x0FF8u) */
#define     USB_PIPEPERI_IFIS               (0x1000u)
/* #define  USB_PIPEPERI_RESERVED2          (0xE000u) */

#define     USB_PIPEPERI_IITV_SHIFT         (0)
/* #define  USB_PIPEPERI_RESERVED1_SHIFT    (3) */
#define     USB_PIPEPERI_IFIS_SHIFT         (12)
/* #define  USB_PIPEPERI_RESERVED2_SHIFT    (13) */

/*==============================================*/
/* PIPEnCTR_1_5                                 */
/*==============================================*/
#define     USB_PIPEnCTR_1_5_PID                (0x0003u)
/* #define  USB_PIPEnCTR_1_5_RESERVED1          (0x001Cu) */
#define     USB_PIPEnCTR_1_5_PBUSY              (0x0020u)
#define     USB_PIPEnCTR_1_5_SQMON              (0x0040u)
#define     USB_PIPEnCTR_1_5_SQSET              (0x0080u)
#define     USB_PIPEnCTR_1_5_SQCLR              (0x0100u)
#define     USB_PIPEnCTR_1_5_ACLRM              (0x0200u)
#define     USB_PIPEnCTR_1_5_ATREPM             (0x0400u)
/* #define  USB_PIPEnCTR_1_5_RESERVED2          (0x0800u) */
#define     USB_PIPEnCTR_1_5_CSSTS              (0x1000u)
#define     USB_PIPEnCTR_1_5_CSCLR              (0x2000u)
#define     USB_PIPEnCTR_1_5_INBUFM             (0x4000u)
#define     USB_PIPEnCTR_1_5_BSTS               (0x8000u)

#define     USB_PIPEnCTR_1_5_PID_SHIFT          (0)
/* #define  USB_PIPEnCTR_1_5_RESERVED1_SHIFT    (2) */
#define     USB_PIPEnCTR_1_5_PBUSY_SHIFT        (5)
#define     USB_PIPEnCTR_1_5_SQMON_SHIFT        (6)
#define     USB_PIPEnCTR_1_5_SQSET_SHIFT        (7)
#define     USB_PIPEnCTR_1_5_SQCLR_SHIFT        (8)
#define     USB_PIPEnCTR_1_5_ACLRM_SHIFT        (9)
#define     USB_PIPEnCTR_1_5_ATREPM_SHIFT       (10)
/* #define  USB_PIPEnCTR_1_5_RESERVED2_SHIFT    (11) */
#define     USB_PIPEnCTR_1_5_CSSTS_SHIFT        (12)
#define     USB_PIPEnCTR_1_5_CSCLR_SHIFT        (13)
#define     USB_PIPEnCTR_1_5_INBUFM_SHIFT       (14)
#define     USB_PIPEnCTR_1_5_BSTS_SHIFT         (15)

/*==============================================*/
/* PIPEnCTR_6_8                                 */
/*==============================================*/
#define     USB_PIPEnCTR_6_8_PID                (0x0003u)
/* #define  USB_PIPEnCTR_6_8_RESERVED1          (0x001Cu) */
#define     USB_PIPEnCTR_6_8_PBUSY              (0x0020u)
#define     USB_PIPEnCTR_6_8_SQMON              (0x0040u)
#define     USB_PIPEnCTR_6_8_SQSET              (0x0080u)
#define     USB_PIPEnCTR_6_8_SQCLR              (0x0100u)
#define     USB_PIPEnCTR_6_8_ACLRM              (0x0200u)
/* #define  USB_PIPEnCTR_6_8_RESERVED2          (0x0C00u) */
#define     USB_PIPEnCTR_6_8_CSSTS              (0x1000u)
#define     USB_PIPEnCTR_6_8_CSCLR              (0x2000u)
/* #define  USB_PIPEnCTR_6_8_RESERVED3          (0x4000u) */
#define     USB_PIPEnCTR_6_8_BSTS               (0x8000u)

#define     USB_PIPEnCTR_6_8_PID_SHIFT          (0)
/* #define  USB_PIPEnCTR_6_8_RESERVED1_SHIFT    (2) */
#define     USB_PIPEnCTR_6_8_PBUSY_SHIFT        (5)
#define     USB_PIPEnCTR_6_8_SQMON_SHIFT        (6)
#define     USB_PIPEnCTR_6_8_SQSET_SHIFT        (7)
#define     USB_PIPEnCTR_6_8_SQCLR_SHIFT        (8)
#define     USB_PIPEnCTR_6_8_ACLRM_SHIFT        (9)
/* #define  USB_PIPEnCTR_6_8_RESERVED2_SHIFT    (10) */
#define     USB_PIPEnCTR_6_8_CSSTS_SHIFT        (12)
#define     USB_PIPEnCTR_6_8_CSCLR_SHIFT        (13)
/* #define  USB_PIPEnCTR_6_8_RESERVED3_SHIFT    (14) */
#define     USB_PIPEnCTR_6_8_BSTS_SHIFT         (15)

/*==============================================*/
/* PIPEnCTR_9                                   */
/*==============================================*/
#define     USB_PIPEnCTR_9_PID                  (0x0003u)
/* #define  USB_PIPEnCTR_9_RESERVED1            (0x001Cu) */
#define     USB_PIPEnCTR_9_PBUSY                (0x0020u)
#define     USB_PIPEnCTR_9_SQMON                (0x0040u)
#define     USB_PIPEnCTR_9_SQSET                (0x0080u)
#define     USB_PIPEnCTR_9_SQCLR                (0x0100u)
#define     USB_PIPEnCTR_9_ACLRM                (0x0200u)
#define     USB_PIPEnCTR_9_ATREPM               (0x0400u)
/* #define  USB_PIPEnCTR_9_RESERVED2            (0x0800u) */
#define     USB_PIPEnCTR_9_CSSTS                (0x1000u)
#define     USB_PIPEnCTR_9_CSCLR                (0x2000u)
#define     USB_PIPEnCTR_9_INBUFM               (0x4000u)
#define     USB_PIPEnCTR_9_BSTS                 (0x8000u)

#define     USB_PIPEnCTR_9_PID_SHIFT            (0)
/* #define  USB_PIPEnCTR_9_RESERVED1_SHIFT      (2) */
#define     USB_PIPEnCTR_9_PBUSY_SHIFT          (5)
#define     USB_PIPEnCTR_9_SQMON_SHIFT          (6)
#define     USB_PIPEnCTR_9_SQSET_SHIFT          (7)
#define     USB_PIPEnCTR_9_SQCLR_SHIFT          (8)
#define     USB_PIPEnCTR_9_ACLRM_SHIFT          (9)
#define     USB_PIPEnCTR_9_ATREPM_SHIFT         (10)
/* #define  USB_PIPEnCTR_9_RESERVED2_SHIFT      (11) */
#define     USB_PIPEnCTR_9_CSSTS_SHIFT          (12)
#define     USB_PIPEnCTR_9_CSCLR_SHIFT          (13)
#define     USB_PIPEnCTR_9_INBUFM_SHIFT         (14)
#define     USB_PIPEnCTR_9_BSTS_SHIFT           (15)

/*==============================================*/
/* PIPEnCTR_A_F                                 */
/*==============================================*/
#define     USB_PIPEnCTR_A_F_PID                (0x0003u)
/* #define  USB_PIPEnCTR_A_F_RESERVED1          (0x001Cu) */
#define     USB_PIPEnCTR_A_F_PBUSY              (0x0020u)
#define     USB_PIPEnCTR_A_F_SQMON              (0x0040u)
#define     USB_PIPEnCTR_A_F_SQSET              (0x0080u)
#define     USB_PIPEnCTR_A_F_SQCLR              (0x0100u)
#define     USB_PIPEnCTR_A_F_ACLRM              (0x0200u)
#define     USB_PIPEnCTR_A_F_ATREPM             (0x0400u)
/* #define  USB_PIPEnCTR_A_F_RESERVED2          (0x3800u) */
#define     USB_PIPEnCTR_A_F_INBUFM             (0x4000u)
#define     USB_PIPEnCTR_A_F_BSTS               (0x8000u)

#define     USB_PIPEnCTR_A_F_PID_SHIFT          (0)
/* #define  USB_PIPEnCTR_A_F_RESERVED1_SHIFT    (2) */
#define     USB_PIPEnCTR_A_F_PBUSY_SHIFT        (5)
#define     USB_PIPEnCTR_A_F_SQMON_SHIFT        (6)
#define     USB_PIPEnCTR_A_F_SQSET_SHIFT        (7)
#define     USB_PIPEnCTR_A_F_SQCLR_SHIFT        (8)
#define     USB_PIPEnCTR_A_F_ACLRM_SHIFT        (9)
#define     USB_PIPEnCTR_A_F_ATREPM_SHIFT       (10)
/* #define  USB_PIPEnCTR_A_F_RESERVED2_SHIFT    (11) */
#define     USB_PIPEnCTR_A_F_INBUFM_SHIFT       (14)
#define     USB_PIPEnCTR_A_F_BSTS_SHIFT         (15)

/*==============================================*/
/* PIPEnTRE                                     */
/*==============================================*/
/* #define  USB_PIPEnTRE_RESERVED1              (0x00FFu) */
#define     USB_PIPEnTRE_TRCLR                  (0x0100u)
#define     USB_PIPEnTRE_TRENB                  (0x0200u)
/* #define  USB_PIPEnTRE_RESERVED2              (0xFC00u) */

/* #define  USB_PIPEnTRE_RESERVED1_SHIFT        (0) */
#define     USB_PIPEnTRE_TRCLR_SHIFT            (8)
#define     USB_PIPEnTRE_TRENB_SHIFT            (9)
/* #define  USB_PIPEnTRE_RESERVED2_SHIFT        (10) */

/*==============================================*/
/* PIPEnTRN                                     */
/*==============================================*/
#define     USB_PIPEnTRN                        (0xFFFFu)

#define     USB_PIPEnTRN_SHIFT                  (0)

/*==============================================*/
/* DEVADDn                                      */
/*==============================================*/
/* #define  USB_DEVADDn_RESERVED1               (0x003Fu) */
#define     USB_DEVADDn_USBSPD                  (0x00C0u)
#define     USB_DEVADDn_HUBPORT                 (0x0700u)
#define     USB_DEVADDn_UPPHUB                  (0x7800u)
/* #define  USB_DEVADDn_RESERVED2               (0x8000u) */

/* #define  USB_DEVADDn_RESERVED1_SHIFT         (0) */
#define     USB_DEVADDn_USBSPD_SHIFT            (6)
#define     USB_DEVADDn_HUBPORT_SHIFT           (8)
#define     USB_DEVADDn_UPPHUB_SHIFT            (11)
/* #define  USB_DEVADDn_RESERVED2_SHIFT         (15) */

/*==============================================*/
/* SUSPMODE                                     */
/*==============================================*/
/* #define  USB_SUSPMODE_RESERVED1              (0x3FFFu) */
#define     USB_SUSPMODE_SUSPM                  (0x4000u)
/* #define  USB_SUSPMODE_RESERVED2              (0x8000u) */

/* #define  USB_SUSPMODE_RESERVED1_SHIFT        (0) */
#define     USB_SUSPMODE_SUSPM_SHIFT            (14)
/* #define  USB_SUSPMODE_RESERVED2_SHIFT        (15) */

/*==============================================*/
/* DnFIFOBm                                     */
/*==============================================*/
#define     USB_DnFIFOBm                        (0xFFFFu)

#define     USB_DnFIFOBm_SHIFT                  (0)

#endif /* USB_IOBITMASK_H */

/* End of File */
