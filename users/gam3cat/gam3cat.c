/*Copyright 2021 @Gam3cat

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include "gam3cat.h"

void my_custom_function(void) {
    
}


__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMK_REV:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP "@" QMK_VERSION ":" QMK_BUILDDATE);
            }
            return false;
            break;
        case KC_WEB:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r"));
                wait_ms(100);
                SEND_STRING("chrome.exe\n");
            }
            return false;
            break;
        case KC_SP4:
            if (record->event.pressed) {
                SEND_STRING ("    ");
            }
            return false;
            break;
        case SM_GLHF:
            if (record->event.pressed) {
                SEND_STRING("VVGL");
                wait_ms(500);
                SEND_STRING("VVGF");
            }
            return false;
            break;
        case SM_VA1:
            if (record->event.pressed) {
                SEND_STRING("VA1");
            }
            return false;
            break;
        case SM_VA2:
            if (record->event.pressed) {
                SEND_STRING("VA2");
            }
            return false;
            break;
        case SM_VA3:
            if (record->event.pressed) {
                SEND_STRING("VA3");
            }
            return false;
            break;
        case SM_VAA:
            if (record->event.pressed) {
                SEND_STRING("VAA");
            }
            return false;
            break;
        case SM_VAF:
            if (record->event.pressed) {
                SEND_STRING("VAF");
            }
            return false;
            break;
        case SM_VAG:
            if (record->event.pressed) {
                SEND_STRING("VAG");
            }
            return false;
            break;
        case SM_VAM:
            if (record->event.pressed) {
                SEND_STRING("VAM");
            }
            return false;
            break;
        case SM_VAT1:
            if (record->event.pressed) {
                SEND_STRING("VAT1");
            }
            return false;
            break;
        case SM_VAT2:
            if (record->event.pressed) {
                SEND_STRING("VAT2");
            }
            return false;
            break;
        case SM_VAT3:
            if (record->event.pressed) {
                SEND_STRING("VAT3");
            }
            return false;
            break;
        case SM_VB1:
            if (record->event.pressed) {
                SEND_STRING("VB1");
            }
            return false;
            break;
        case SM_VB2:
            if (record->event.pressed) {
                SEND_STRING("VB2");
            }
            return false;
            break;
        case SM_VB3:
            if (record->event.pressed) {
                SEND_STRING("VB3");
            }
            return false;
            break;
        case SM_VBA:
            if (record->event.pressed) {
                SEND_STRING("VBA");
            }
            return false;
            break;
        case SM_VBB:
            if (record->event.pressed) {
                SEND_STRING("VBB");
            }
            return false;
            break;
        case SM_VBD:
            if (record->event.pressed) {
                SEND_STRING("VBD");
            }
            return false;
            break;
        case SM_VBE:
            if (record->event.pressed) {
                SEND_STRING("VBE");
            }
            return false;
            break;
        case SM_VBF:
            if (record->event.pressed) {
                SEND_STRING("VBF");
            }
            return false;
            break;
        case SM_VBG:
            if (record->event.pressed) {
                SEND_STRING("VBG");
            }
            return false;
            break;
        case SM_VBJ1:
            if (record->event.pressed) {
                SEND_STRING("VBJ1");
            }
            return false;
            break;
        case SM_VBJ3:
            if (record->event.pressed) {
                SEND_STRING("VBJ3");
            }
            return false;
            break;
        case SM_VBJJ:
            if (record->event.pressed) {
                SEND_STRING("VBJJ");
            }
            return false;
            break;
        case SM_VBM:
            if (record->event.pressed) {
                SEND_STRING("VBM");
            }
            return false;
            break;
        case SM_VBS:
            if (record->event.pressed) {
                SEND_STRING("VBS");
            }
            return false;
            break;
        case SM_VC1:
            if (record->event.pressed) {
                SEND_STRING("VC1");
            }
            return false;
            break;
        case SM_VC2:
            if (record->event.pressed) {
                SEND_STRING("VC2");
            }
            return false;
            break;
        case SM_VC3:
            if (record->event.pressed) {
                SEND_STRING("VC3");
            }
            return false;
            break;
        case SM_VCB:
            if (record->event.pressed) {
                SEND_STRING("VCB");
            }
            return false;
            break;
        case SM_VCC:
            if (record->event.pressed) {
                SEND_STRING("VCC");
            }
            return false;
            break;
        case SM_VCJ:
            if (record->event.pressed) {
                SEND_STRING("VCJ");
            }
            return false;
            break;
        case SM_VD1:
            if (record->event.pressed) {
                SEND_STRING("VD1");
            }
            return false;
            break;
        case SM_VD2:
            if (record->event.pressed) {
                SEND_STRING("VD2");
            }
            return false;
            break;
        case SM_VD3:
            if (record->event.pressed) {
                SEND_STRING("VD3");
            }
            return false;
            break;
        case SM_VDD:
            if (record->event.pressed) {
                SEND_STRING("VDD");
            }
            return false;
            break;
        case SM_VDF:
            if (record->event.pressed) {
                SEND_STRING("VDF");
            }
            return false;
            break;
        case SM_VDG:
            if (record->event.pressed) {
                SEND_STRING("VDG");
            }
            return false;
            break;
        case SM_VDM:
            if (record->event.pressed) {
                SEND_STRING("VDM");
            }
            return false;
            break;
        case SM_VEA:
            if (record->event.pressed) {
                SEND_STRING("VEA");
            }
            return false;
            break;
        case SM_VEG:
            if (record->event.pressed) {
                SEND_STRING("VEG");
            }
            return false;
            break;
        case SM_VEJ:
            if (record->event.pressed) {
                SEND_STRING("VEJ");
            }
            return false;
            break;
        case SM_VEL:
            if (record->event.pressed) {
                SEND_STRING("VEL");
            }
            return false;
            break;
        case SM_VER:
            if (record->event.pressed) {
                SEND_STRING("VER");
            }
            return false;
            break;
        case SM_VET:
            if (record->event.pressed) {
                SEND_STRING("VET");
            }
            return false;
            break;
        case SM_VEW:
            if (record->event.pressed) {
                SEND_STRING("VEW");
            }
            return false;
            break;
        case SM_VF1:
            if (record->event.pressed) {
                SEND_STRING("VF1");
            }
            return false;
            break;
        case SM_VF2:
            if (record->event.pressed) {
                SEND_STRING("VF2");
            }
            return false;
            break;
        case SM_VF3:
            if (record->event.pressed) {
                SEND_STRING("VF3");
            }
            return false;
            break;
        case SM_VFF:
            if (record->event.pressed) {
                SEND_STRING("VFF");
            }
            return false;
            break;
        case SM_VG1:
            if (record->event.pressed) {
                SEND_STRING("VG1");
            }
            return false;
            break;
        case SM_VG2:
            if (record->event.pressed) {
                SEND_STRING("VG2");
            }
            return false;
            break;
        case SM_VG3:
            if (record->event.pressed) {
                SEND_STRING("VG3");
            }
            return false;
            break;
        case SM_VGG:
            if (record->event.pressed) {
                SEND_STRING("VGG");
            }
            return false;
            break;
        case SM_VH1:
            if (record->event.pressed) {
                SEND_STRING("VH1");
            }
            return false;
            break;
        case SM_VH2:
            if (record->event.pressed) {
                SEND_STRING("VH2");
            }
            return false;
            break;
        case SM_VH3:
            if (record->event.pressed) {
                SEND_STRING("VH3");
            }
            return false;
            break;
        case SM_VHH:
            if (record->event.pressed) {
                SEND_STRING("VHH");
            }
            return false;
            break;
        case SM_VHS:
            if (record->event.pressed) {
                SEND_STRING("VHS");
            }
            return false;
            break;
        case SM_VI1:
            if (record->event.pressed) {
                SEND_STRING("VI1");
            }
            return false;
            break;
        case SM_VI2:
            if (record->event.pressed) {
                SEND_STRING("VI2");
            }
            return false;
            break;
        case SM_VI3:
            if (record->event.pressed) {
                SEND_STRING("VI3");
            }
            return false;
            break;
        case SM_VII:
            if (record->event.pressed) {
                SEND_STRING("VII");
            }
            return false;
            break;
        case SM_VQ1:
            if (record->event.pressed) {
                SEND_STRING("VQ1");
            }
            return false;
            break;
        case SM_VQ2:
            if (record->event.pressed) {
                SEND_STRING("VQ2");
            }
            return false;
            break;
        case SM_VQ3:
            if (record->event.pressed) {
                SEND_STRING("VQ3");
            }
            return false;
            break;
        case SM_VQF:
            if (record->event.pressed) {
                SEND_STRING("VQF");
            }
            return false;
            break;
        case SM_VQG:
            if (record->event.pressed) {
                SEND_STRING("VQG");
            }
            return false;
            break;
        case SM_VQN:
            if (record->event.pressed) {
                SEND_STRING("VQN");
            }
            return false;
            break;
        case SM_VQQ:
            if (record->event.pressed) {
                SEND_STRING("VQQ");
            }
            return false;
            break;
        case SM_VR1:
            if (record->event.pressed) {
                SEND_STRING("VR1");
            }
            return false;
            break;
        case SM_VR2:
            if (record->event.pressed) {
                SEND_STRING("VR2");
            }
            return false;
            break;
        case SM_VR3:
            if (record->event.pressed) {
                SEND_STRING("VR3");
            }
            return false;
            break;
        case SM_VRJ:
            if (record->event.pressed) {
                SEND_STRING("VRJ");
            }
            return false;
            break;
        case SM_VRR:
            if (record->event.pressed) {
                SEND_STRING("VRR");
            }
            return false;
            break;
        case SM_VRS:
            if (record->event.pressed) {
                SEND_STRING("VRS");
            }
            return false;
            break;
        case SM_VSA1:
            if (record->event.pressed) {
                SEND_STRING("VSA1");
            }
            return false;
            break;
        case SM_VSA2:
            if (record->event.pressed) {
                SEND_STRING("VSA2");
            }
            return false;
            break;
        case SM_VSA3:
            if (record->event.pressed) {
                SEND_STRING("VSA3");
            }
            return false;
            break;
        case SM_VSAA:
            if (record->event.pressed) {
                SEND_STRING("VSAA");
            }
            return false;
            break;
        case SM_VSAF:
            if (record->event.pressed) {
                SEND_STRING("VSAF");
            }
            return false;
            break;
        case SM_VSAG:
            if (record->event.pressed) {
                SEND_STRING("VSAG");
            }
            return false;
            break;
        case SM_VSAM:
            if (record->event.pressed) {
                SEND_STRING("VSAM");
            }
            return false;
            break;
        case SM_VSBB:
            if (record->event.pressed) {
                SEND_STRING("VSBB");
            }
            return false;
            break;
        case SM_VSBN:
            if (record->event.pressed) {
                SEND_STRING("VSBN");
            }
            return false;
            break;
        case SM_VSBT:
            if (record->event.pressed) {
                SEND_STRING("VSBT");
            }
            return false;
            break;
        case SM_VSD1:
            if (record->event.pressed) {
                SEND_STRING("VSD1");
            }
            return false;
            break;
        case SM_VSD2:
            if (record->event.pressed) {
                SEND_STRING("VSD2");
            }
            return false;
            break;
        case SM_VSD3:
            if (record->event.pressed) {
                SEND_STRING("VSD3");
            }
            return false;
            break;
        case SM_VSDD:
            if (record->event.pressed) {
                SEND_STRING("VSDD");
            }
            return false;
            break;
        case SM_VSDF:
            if (record->event.pressed) {
                SEND_STRING("VSDF");
            }
            return false;
            break;
        case SM_VSDG:
            if (record->event.pressed) {
                SEND_STRING("VSDG");
            }
            return false;
            break;
        case SM_VSDM:
            if (record->event.pressed) {
                SEND_STRING("VSDM");
            }
            return false;
            break;
        case SM_VSG1:
            if (record->event.pressed) {
                SEND_STRING("VSG1");
            }
            return false;
            break;
        case SM_VSG2:
            if (record->event.pressed) {
                SEND_STRING("VSG2");
            }
            return false;
            break;
        case SM_VSG3:
            if (record->event.pressed) {
                SEND_STRING("VSG3");
            }
            return false;
            break;
        case SM_VSGG:
            if (record->event.pressed) {
                SEND_STRING("VSGG");
            }
            return false;
            break;
        case SM_VSO:
            if (record->event.pressed) {
                SEND_STRING("VSO");
            }
            return false;
            break;
        case SM_VSQ1:
            if (record->event.pressed) {
                SEND_STRING("VSQ1");
            }
            return false;
            break;
        case SM_VSQ2:
            if (record->event.pressed) {
                SEND_STRING("VSQ2");
            }
            return false;
            break;
        case SM_VSQ3:
            if (record->event.pressed) {
                SEND_STRING("VSQ3");
            }
            return false;
            break;
        case SM_VSQQ:
            if (record->event.pressed) {
                SEND_STRING("VSQQ");
            }
            return false;
            break;
        case SM_VSR:
            if (record->event.pressed) {
                SEND_STRING("VSR");
            }
            return false;
            break;
        case SM_VSS:
            if (record->event.pressed) {
                SEND_STRING("VSS");
            }
            return false;
            break;
        case SM_VST1:
            if (record->event.pressed) {
                SEND_STRING("VST1");
            }
            return false;
            break;
        case SM_VST2:
            if (record->event.pressed) {
                SEND_STRING("VST2");
            }
            return false;
            break;
        case SM_VST3:
            if (record->event.pressed) {
                SEND_STRING("VST3");
            }
            return false;
            break;
        case SM_VSTB:
            if (record->event.pressed) {
                SEND_STRING("VSTB");
            }
            return false;
            break;
        case SM_VSTT:
            if (record->event.pressed) {
                SEND_STRING("VSTT");
            }
            return false;
            break;
        case SM_VT1:
            if (record->event.pressed) {
                SEND_STRING("VT1");
            }
            return false;
            break;
        case SM_VT2:
            if (record->event.pressed) {
                SEND_STRING("VT2");
            }
            return false;
            break;
        case SM_VT3:
            if (record->event.pressed) {
                SEND_STRING("VT3");
            }
            return false;
            break;
        case SM_VTT:
            if (record->event.pressed) {
                SEND_STRING("VTT");
            }
            return false;
            break;
        case SM_VVA:
            if (record->event.pressed) {
                SEND_STRING("VVA");
            }
            return false;
            break;
        case SM_VVB:
            if (record->event.pressed) {
                SEND_STRING("VVB");
            }
            return false;
            break;
        case SM_VVC:
            if (record->event.pressed) {
                SEND_STRING("VVC");
            }
            return false;
            break;
        case SM_VVGB:
            if (record->event.pressed) {
                SEND_STRING("VVGB");
            }
            return false;
            break;
        case SM_VVGF:
            if (record->event.pressed) {
                SEND_STRING("VVGF");
            }
            return false;
            break;
        case SM_VVGG:
            if (record->event.pressed) {
                SEND_STRING("VVGG");
            }
            return false;
            break;
        case SM_VVGH:
            if (record->event.pressed) {
                SEND_STRING("VVGH");
            }
            return false;
            break;
        case SM_VVGL:
            if (record->event.pressed) {
                SEND_STRING("VVGL");
            }
            return false;
            break;
        case SM_VVGN:
            if (record->event.pressed) {
                SEND_STRING("VVGN");
            }
            return false;
            break;
        case SM_VVGO:
            if (record->event.pressed) {
                SEND_STRING("VVGO");
            }
            return false;
            break;
        case SM_VVGQ:
            if (record->event.pressed) {
                SEND_STRING("VVGQ");
            }
            return false;
            break;
        case SM_VVGR:
            if (record->event.pressed) {
                SEND_STRING("VVGR");
            }
            return false;
            break;
        case SM_VVGS:
            if (record->event.pressed) {
                SEND_STRING("VVGS");
            }
            return false;
            break;
        case SM_VVGT:
            if (record->event.pressed) {
                SEND_STRING("VVGT");
            }
            return false;
            break;
        case SM_VVGW:
            if (record->event.pressed) {
                SEND_STRING("VVGW");
            }
            return false;
            break;
        case SM_VVK:
            if (record->event.pressed) {
                SEND_STRING("VVK");
            }
            return false;
            break;
        case SM_VVM:
            if (record->event.pressed) {
                SEND_STRING("VVM");
            }
            return false;
            break;
        case SM_VVN:
            if (record->event.pressed) {
                SEND_STRING("VVN");
            }
            return false;
            break;
        case SM_VVP:
            if (record->event.pressed) {
                SEND_STRING("VVP");
            }
            return false;
            break;
        case SM_VVS:
            if (record->event.pressed) {
                SEND_STRING("VVS");
            }
            return false;
            break;
        case SM_VVT:
            if (record->event.pressed) {
                SEND_STRING("VVT");
            }
            return false;
            break;
        case SM_VVVA:
            if (record->event.pressed) {
                SEND_STRING("VVVA");
            }
            return false;
            break;
        case SM_VVVB:
            if (record->event.pressed) {
                SEND_STRING("VVVB");
            }
            return false;
            break;
        case SM_VVVC:
            if (record->event.pressed) {
                SEND_STRING("VVVC");
            }
            return false;
            break;
        case SM_VVVD:
            if (record->event.pressed) {
                SEND_STRING("VVVD");
            }
            return false;
            break;
        case SM_VVVE:
            if (record->event.pressed) {
                SEND_STRING("VVVE");
            }
            return false;
            break;
        case SM_VVVF:
            if (record->event.pressed) {
                SEND_STRING("VVVF");
            }
            return false;
            break;
        case SM_VVVG:
            if (record->event.pressed) {
                SEND_STRING("VVVG");
            }
            return false;
            break;
        case SM_VVVJ:
            if (record->event.pressed) {
                SEND_STRING("VVVJ");
            }
            return false;
            break;
        case SM_VVVP:
            if (record->event.pressed) {
                SEND_STRING("VVVP");
            }
            return false;
            break;
        case SM_VVVR:
            if (record->event.pressed) {
                SEND_STRING("VVVR");
            }
            return false;
            break;
        case SM_VVVS:
            if (record->event.pressed) {
                SEND_STRING("VVVS");
            }
            return false;
            break;
        case SM_VVVT:
            if (record->event.pressed) {
                SEND_STRING("VVVT");
            }
            return false;
            break;
        case SM_VVVW:
            if (record->event.pressed) {
                SEND_STRING("VVVW");
            }
            return false;
            break;
        case SM_VVVX:
            if (record->event.pressed) {
                SEND_STRING("VVVX");
            }
            return false;
            break;
        case SM_VVW:
            if (record->event.pressed) {
                SEND_STRING("VVW");
            }
            return false;
            break;
        case SM_VVX:
            if (record->event.pressed) {
                SEND_STRING("VVX");
            }
            return false;
            break;
        case SM_VVY:
            if (record->event.pressed) {
                SEND_STRING("VVY");
            }
            return false;
            break;
        case SM_VXC:
            if (record->event.pressed) {
                SEND_STRING("VXC");
            }
            return false;
            break;
        case SM_VXD:
            if (record->event.pressed) {
                SEND_STRING("VXD");
            }
            return false;
            break;
        case SM_VXE:
            if (record->event.pressed) {
                SEND_STRING("VXE");
            }
            return false;
            break;
        case SM_VXF:
            if (record->event.pressed) {
                SEND_STRING("VXF");
            }
            return false;
            break;
        case SM_VXG:
            if (record->event.pressed) {
                SEND_STRING("VXG");
            }
            return false;
            break;
        case SM_VXS:
            if (record->event.pressed) {
                SEND_STRING("VXS");
            }
            return false;
            break;
        case SM_VXW:
            if (record->event.pressed) {
                SEND_STRING("VXW");
            }
            return false;
            break;
    }
    return process_record_keymap(keycode, record);
}
