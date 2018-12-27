#include "quantum.h"
#include "eeprom.h"

//i don't think i need this ?
//TODO: test rgb without this snippet
//#ifdef RGBLIGHT_ENABLE
//#include "rgblight.h"
//#endif

//Layers Definition
#define CL 0
#define NM_MODE 2
#define VI_MODE 3
#define FN3 4
#define ACCENT 5
#define ACCENT_CAP 6

//Unicode Definitions
#define DE_AE     UC(0x00E4)
#define DE_SS     UC(0x00DF)
#define DE_OE     UC(0x00F6)
#define DE_UE     UC(0x00FC)
#define DE_AE_CAP UC(0x00C4)
#define DE_OE_CAP UC(0x00D6)
#define DE_UE_CAP UC(0x00DC)
enum tap_dancers {
  CTL_NM = 0,
  GUI_NM = 1,
  ALT_NM = 2,
  SFT_NM = 3,
};
