#ifndef _UC8173_H
#define _UC8173_H

#include "gfx.h"

#define DATA_MASK   0x0100
#define DCX_CMD     0x0000
#define DCX_DATA    0x0001
#define MASTER      0x00
#define SLAVE       0x01
#define MAS_SLA     0x02
#define BLACK       0x00
#define WHITE       0x01
#define RED         0x02

#define PSR         0x0000
#define PWR         0x0001
#define POF         0x0002
#define PFS         0x0003
#define PON         0x0004
#define PMES        0x0005
#define BTST        0x0006
#define DSLP        0x0007
#define SLP         0x0008
#define DTM1        0x0010
#define DRF         0x0012
#define DTM2        0x0013
#define DTMW        0x0014
#define DTM3        0x0015
#define DTM4        0x0016
#define LUT_KWVCOM  0x0020
#define LUT_RVCOM   0x0021
#define LUT_KW      0x0022 
#define LUT_RR      0x0023 
#define LUT_RK      0x0024 
#define LUT_RW      0x0025
#define LUT_FT      0x0026
#define LPRD        0x0030
#define TSC         0x0040
#define TSE         0x0041
#define TSW         0x0042
#define TSR         0x0043
#define PBC         0x0044
#define CDI         0x0050
#define LPD         0x0051
#define TRES        0x0061
#define GDS         0x0062
#define GBS         0x0063
#define GSS         0x0064
#define REV         0x0070
#define FLG         0x0071
#define AMV         0x0080
#define VV          0x0081
#define VDCS        0x0082
#define EDS         0x0083
#define VBDS        0x0084

#define PGM         0x00A0
#define APG         0x00A1
#define ROTP        0x00A2
#define CCSET       0x00E0
#define PWS         0x00E3
#define LVSEL       0x00E4
#define TSSET       0x00E5

#define DF          0x00DF

#define Initial_23_16          0x00
#define Initial_15_0           0x0000 // 1K
#define Temperature            0x001000
#define Temperature0_23_16     0x00
#define Temperature0_15_0      0x0400 // 1K
#define Temperature1_23_16     0x00
#define Temperature1_15_0      0x0800
#define Temperature2_23_16     0x00
#define Temperature2_15_0      0x0C00
#define Temperature3_23_16     0x00
#define Temperature3_15_0      0x1000
#define Temperature4_23_16     0x00
#define Temperature4_15_0      0x1400
#define Temperature5_23_16     0x00
#define Temperature5_15_0      0x1800
#define Temperature6_23_16     0x00
#define Temperature6_15_0      0x1C00
#define Temperature7_23_16     0x00
#define Temperature7_15_0      0x2000
#define Temperature8_23_16     0x00
#define Temperature8_15_0      0x2400
#define Temperature9_23_16     0x00
#define Temperature9_15_0      0x2800
#define Temperature10_23_16    0x00
#define Temperature10_15_0     0x2C00

#define Image_Start            0x003000

#define Initial_Counter            64
#define Temperature_LUT_Counter   672


#endif // _UC8173_H
