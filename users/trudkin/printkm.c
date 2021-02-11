#pragma once 

#include <string.h>
#include <stdio.h>

#define ALT_LEFT RALT_T(KC_LEFT)
#define GUI_DOWN RGUI_T(KC_DOWN)
#define CTRL_RT  RCTL_T(KC_RGHT)
#define HYPR_UP  HYPR_T(KC_UP)
#define S_T_SLSH RSFT_T(KC_SLASH)


#define CASE_KEY(key) case key:\
        sprintf(buf + pos, format, #key );\
        break

#define CASE_LAYER(key) case key:\
        sprintf(buf, #key );\
        break

char * get_code(uint8_t l,uint8_t r,uint8_t c, char * buf ){
   uint16_t keycode = keymaps[l][r][c];
   uint8_t  pos = 0;
   uint8_t  lowpart = 0;
   uint8_t  highpart = 0;
   uint8_t mod ;
   bool process_lowbyte = false;
   char format[32] = "%s%";
   char tmp[32];

   if (keycode >= SAFE_RANGE && keycode <= MY_PRINT_LAYOUT) {
       switch (keycode) {
        CASE_KEY(QWERTY);
        CASE_KEY(COLEMAK);
        CASE_KEY(DVORAK);
        CASE_KEY(LOWER);
        CASE_KEY(RAISE);
        CASE_KEY(KC_MAKE);
        CASE_KEY(MY_PIPE);
        CASE_KEY(SECRET1); 
        CASE_KEY(SECRET2); 
        CASE_KEY(SECRET3); 
        CASE_KEY(SECRET4); 
        CASE_KEY(SECRET5);
        CASE_KEY(MY_PRINT_LAYOUT);
       default:
        itoa(keycode,buf,16);
       }
   } else if (keycode >= QK_TAP_DANCE && keycode <= QK_TAP_DANCE_MAX) { 
       switch (keycode) {

        CASE_KEY(MY_LOW);
        CASE_KEY(MY_RAI);
        CASE_KEY(MY_9);
        CASE_KEY(MY_0);
        CASE_KEY(MY_K);
        CASE_KEY(MY_B);
        CASE_KEY(MY_DEL);
        CASE_KEY(MY_LGUI);
       default:
        itoa(keycode,buf,16);
       }
   } else if (keycode >= RESET && keycode <= 0x5cff) {
       switch (keycode) {

       CASE_KEY(NUMPAD);
       CASE_KEY(TERM_ON);
       CASE_KEY(TERM_OFF);
       CASE_KEY(MU_ON);
       CASE_KEY(MU_OFF);

    CASE_KEY(RESET);
    CASE_KEY(DEBUG);
    CASE_KEY(MAGIC_SWAP_CONTROL_CAPSLOCK);
    CASE_KEY(MAGIC_CAPSLOCK_TO_CONTROL);
    CASE_KEY(MAGIC_SWAP_LALT_LGUI);
    CASE_KEY(MAGIC_SWAP_RALT_RGUI);
    CASE_KEY(MAGIC_NO_GUI);
    CASE_KEY(MAGIC_SWAP_GRAVE_ESC);
    CASE_KEY(MAGIC_SWAP_BACKSLASH_BACKSPACE);
    CASE_KEY(MAGIC_HOST_NKRO);
    CASE_KEY(MAGIC_SWAP_ALT_GUI);
    CASE_KEY(MAGIC_UNSWAP_CONTROL_CAPSLOCK);
    CASE_KEY(MAGIC_UNCAPSLOCK_TO_CONTROL);
    CASE_KEY(MAGIC_UNSWAP_LALT_LGUI);
    CASE_KEY(MAGIC_UNSWAP_RALT_RGUI);
    CASE_KEY(MAGIC_UNNO_GUI);
    CASE_KEY(MAGIC_UNSWAP_GRAVE_ESC);
    CASE_KEY(MAGIC_UNSWAP_BACKSLASH_BACKSPACE);
    CASE_KEY(MAGIC_UNHOST_NKRO);
    CASE_KEY(MAGIC_UNSWAP_ALT_GUI);
    CASE_KEY(MAGIC_TOGGLE_NKRO);
    CASE_KEY(MAGIC_TOGGLE_ALT_GUI);
    CASE_KEY(GRAVE_ESC); 
           CASE_KEY(KC_AUDIO_MUTE);
           CASE_KEY(KC_AUDIO_VOL_UP);
           CASE_KEY(KC_AUDIO_VOL_DOWN);
           CASE_KEY(KC_MEDIA_NEXT_TRACK);
           CASE_KEY(KC_MEDIA_PREV_TRACK);
           CASE_KEY(KC_MEDIA_STOP);
           CASE_KEY(KC_MEDIA_PLAY_PAUSE);
           CASE_KEY(KC_MEDIA_SELECT);
           CASE_KEY(KC_MEDIA_EJECT);
           CASE_KEY(RGB_SPI); 
           CASE_KEY(RGB_SPD); 
           CASE_KEY(RGB_MOD); 
           CASE_KEY(RGB_RMOD); 
           CASE_KEY(RGB_TOG);   
           CASE_KEY(RGB_VAI); 
           CASE_KEY(RGB_VAD); 
           CASE_KEY(RGB_M_R); 
           CASE_KEY(RGB_M_P);  
           CASE_KEY(RGB_M_B );     
           CASE_KEY(RGB_HUI);
           CASE_KEY(RGB_HUD);
           CASE_KEY(RGB_M_K);
           CASE_KEY(RGB_M_SW); 
           CASE_KEY(RGB_M_SN); 
           CASE_KEY(RGB_SAI); 
           CASE_KEY(RGB_SAD); 
           CASE_KEY(RGB_M_T); 
           CASE_KEY(RGB_M_X);  
           CASE_KEY(RGB_M_G );
#ifdef LEADER_ENABLE
       CASE_KEY(KC_LEAD);
#endif

// Auto Shift setup
#ifndef AUTO_SHIFT_NO_SETUP
    CASE_KEY(KC_ASUP);
    CASE_KEY(KC_ASDN);
    CASE_KEY(KC_ASRP);
#endif
    CASE_KEY(KC_ASTG);
    CASE_KEY(KC_ASON);
    CASE_KEY(KC_ASOFF);

    // Audio on/off/toggle
    CASE_KEY(AU_ON);
    CASE_KEY(AU_OFF);
    CASE_KEY(AU_TOG);

       }
   } else if (keycode >0xFF ) {
       highpart = keycode>>8;
       lowpart = keycode&0xff;



       switch (highpart) {
       case QK_TOGGLE_LAYER>>8:           
           sprintf(buf, "TG(%d)", lowpart );
           process_lowbyte =false;
           break;
       case QK_MOD_TAP>>8 ... (QK_MOD_TAP>>8)+0x1f:
//         if (lowpart == (MY_PIPE&0xff) ) {
//             strcpy(buf, "MT(LALT,KC_PIPE)" );
//             process_lowbyte =false;
//             break;
//         }
           mod = highpart&0x1f;
           switch (mod ) {
           case MOD_RALT:
               strcpy(format, "RALT_T(%s)");
               process_lowbyte = true ;
               break;
           case MOD_RSFT:
               strcpy(format, "RSFT_T(%s)");
               process_lowbyte = true ;
               break;
           case MOD_LCTL:
               strcpy(format, "LCTL_T(%s)");
               process_lowbyte = true ;
               break;
           case MOD_RCTL:
               strcpy(format, "RCTL_T(%s)");
               process_lowbyte = true ;
               break;
           case 15:
               strcpy(format, "HYPR_T(%s)");
               process_lowbyte = true ;
               break;
           case MOD_RGUI:
               strcpy(format, "RGUI_T(%s)");
               process_lowbyte = true ;
               break;
           case MOD_LGUI:
               strcpy(format, "LGUI_T(%s)");
               process_lowbyte = true ;
               break;
           default:
               strcpy(format, "MT(%s)");
               process_lowbyte = true ;
               break;
           }
           break;
       case MOD_RCTL: 
           strcpy(format,"RCTL(%s)");
           process_lowbyte =true;
           break;
       case MOD_LCTL:
           strcpy(format,"LCTL(%s)");
           process_lowbyte =true;
           break;
       case MOD_LSFT:
           strcpy(format,"LSFT(%s)");
           process_lowbyte =true;
           break;
       case MOD_RSFT:
           strcpy(format,"RSFT(%s)");
           process_lowbyte =true;
           break;
        default:
            process_lowbyte = false;
            sprintf(buf + pos, "(%x,%x)", highpart,lowpart );
       }

   }

   if (keycode <= 0xff || process_lowbyte ) {
           switch (keycode & 0xff) {
           
           CASE_KEY(KC_LBRC); 
           CASE_KEY(KC_RBRC); 
           CASE_KEY(KC_PSCR);    
           CASE_KEY(KC_SLCK); 
           CASE_KEY(KC_PAUS);      
           CASE_KEY(KC_INS);     
           CASE_KEY(KC_HOME);       
           CASE_KEY(KC_PGUP);       
           CASE_KEY(KC_DEL);     
           CASE_KEY(KC_END);        
           CASE_KEY(KC_PGDN);     
           CASE_KEY(KC_RGHT);      
           CASE_KEY(KC_LEFT);  
           CASE_KEY(KC_DOWN);       
           CASE_KEY(KC_UP);         
           CASE_KEY(KC_NLCK);  
           CASE_KEY(KC_MS_UP);    
           CASE_KEY(KC_MS_DOWN);
           CASE_KEY(KC_MS_LEFT);
           CASE_KEY(KC_MS_RIGHT);
           CASE_KEY(KC_MS_BTN1);
           CASE_KEY(KC_MS_BTN2);
           CASE_KEY(KC_MS_BTN3);
           CASE_KEY(KC_MS_BTN4);
           CASE_KEY(KC_MS_BTN5); 
 
           
           CASE_KEY(KC_GESC);
           CASE_KEY(KC_LCTRL );
           CASE_KEY(KC_LSHIFT);
           CASE_KEY(KC_LALT);
           CASE_KEY(KC_LGUI);
           CASE_KEY(KC_RCTRL);
           CASE_KEY(KC_RSHIFT);
           CASE_KEY(KC_RALT);
           CASE_KEY(KC_RGUI);
           
           CASE_KEY(KC_QUOTE);
           CASE_KEY(KC_GRAVE);
           CASE_KEY(KC_COMM);
           CASE_KEY(KC_DOT);
           CASE_KEY(KC_SLSH);
           
           CASE_KEY(KC_ENT);
           CASE_KEY(KC_ESC);
           CASE_KEY(KC_TAB);
           CASE_KEY(KC_SPC);
           CASE_KEY(KC_MINS);
           CASE_KEY(KC_EQL);
           CASE_KEY(MY_DEL);
           
           CASE_KEY(KC_UNDS); 
           CASE_KEY(KC_PLUS); 
           CASE_KEY(KC_LCBR); 
           CASE_KEY(KC_RCBR);
           CASE_KEY(KC_LT);
           CASE_KEY(KC_GT);
           
           CASE_KEY(KC_KP_SLASH);
           CASE_KEY(KC_KP_ASTERISK);
           CASE_KEY(KC_KP_MINUS);
           CASE_KEY(KC_KP_PLUS);
           CASE_KEY(KC_KP_ENTER);
           CASE_KEY(KC_KP_1);
           CASE_KEY(KC_KP_2);
           CASE_KEY(KC_KP_3);
           CASE_KEY(KC_KP_4);
           CASE_KEY(KC_KP_5);
           CASE_KEY(KC_KP_6);
           CASE_KEY(KC_KP_7);
           CASE_KEY(KC_KP_8);  
           CASE_KEY(KC_KP_9);
           CASE_KEY(KC_KP_0);
           CASE_KEY(KC_KP_DOT);
           CASE_KEY(KC_NUBS);
           CASE_KEY(KC_APPLICATION);
           CASE_KEY(KC_POWER);
           CASE_KEY(KC_KP_EQUAL);
           CASE_KEY(KC_F13);
           CASE_KEY(KC_F14);
           CASE_KEY(KC_F15);
           CASE_KEY(KC_F16);
           CASE_KEY(KC_F17);
           CASE_KEY(KC_F18);
           CASE_KEY(KC_F19);
           CASE_KEY(KC_F20);
           CASE_KEY(KC_F21); 
           CASE_KEY(KC_F22);
           CASE_KEY(KC_F23);
           CASE_KEY(KC_F24);
           CASE_KEY(KC_EXECUTE);
           CASE_KEY(KC_HELP);
           CASE_KEY(KC_MENU);
           CASE_KEY(KC_SELECT);
           CASE_KEY(KC_STOP);
           CASE_KEY(KC_AGAIN);
           CASE_KEY(KC_UNDO);
           CASE_KEY(KC_CUT);
           CASE_KEY(KC_COPY);
           CASE_KEY(KC_PASTE);
           CASE_KEY(KC_FIND);
           
           CASE_KEY(KC_AUDIO_MUTE);
           CASE_KEY(KC_AUDIO_VOL_UP);
           CASE_KEY(KC_AUDIO_VOL_DOWN);
           CASE_KEY(KC_MEDIA_NEXT_TRACK);
           CASE_KEY(KC_MEDIA_PREV_TRACK);
           CASE_KEY(KC_MEDIA_STOP);
           CASE_KEY(KC_MEDIA_PLAY_PAUSE);
           CASE_KEY(KC_MEDIA_SELECT);
           CASE_KEY(KC_MEDIA_EJECT);

           CASE_KEY(KC_MS_WH_UP);
           CASE_KEY(KC_MS_WH_DOWN);
           CASE_KEY(KC_MS_WH_LEFT);
           CASE_KEY(KC_MS_WH_RIGHT);
           CASE_KEY(KC_MS_ACCEL0);
           CASE_KEY(KC_MS_ACCEL1);
           CASE_KEY(KC_MS_ACCEL2);
           CASE_KEY(KC_NUHS);

           case KC_NO:
            sprintf(buf, "XXXXXXX");
            break;
           case KC_TRNS:
            sprintf(buf, "_______");
            break;
           CASE_KEY(KC_BSPC);
           CASE_KEY(KC_SCLN);
           CASE_KEY(KC_BSLS);
           
           case KC_A ... KC_Z:
               sprintf(tmp, "KC_%c", 'A' + keycode - KC_A);
               sprintf(buf, format,tmp );
            break;
           case KC_0:    
               sprintf(tmp, "KC_%c", '0');  
               sprintf(buf, format , tmp );
            break;
           case KC_1 ... KC_9:
            sprintf(tmp, "KC_%c",'1' + keycode - KC_1);               
            sprintf(buf, format,tmp );
            break;
           case KC_F1 ... KC_F9:
            sprintf(tmp, "KC_F%c",'1' + keycode - KC_F1);
            sprintf(buf, format,tmp );
            break;
           case KC_F10 ... KC_F12:
            sprintf(tmp, "KC_F1%c",'0' + keycode - KC_F10);
            sprintf(buf, format,tmp );
            break;
           default:
            itoa(keycode,buf,16);
            }
   }
    return buf;

}

#define PRINT_JSON

void my_print_layout(void){
        char buf[32];
        char lstr[20*7];
        char rstr[20*7]; 
        char format[16] = " %-20.20s|";


        uint8_t li;
        uint8_t ri;
        uint8_t j;
        uint8_t l =0; // layer
        uint8_t r; //rows
        uint8_t c; //cols 

#ifdef PRINT_JSON
SEND_STRING("{\"version\":1");
            SEND_STRING(SS_TAP(X_ENTER));
SEND_STRING(            ",\"notes\":\"\"");
                SEND_STRING(SS_TAP(X_ENTER));
SEND_STRING(            ",\"documentation\":\"This file is a QMK Configurator export. You can import this at <https://config.qmk.fm>. \",");
                SEND_STRING(SS_TAP(X_ENTER));
SEND_STRING(            "\"keyboard\":\"preonic/rev3\",\"keymap\":\"preonic_rev3_layout_ortho_5x12_mine\"");
                SEND_STRING(SS_TAP(X_ENTER));
SEND_STRING(            ",\"layout\":\"LAYOUT_ortho_5x12\"");
                SEND_STRING(SS_TAP(X_ENTER));
SEND_STRING(            ",\"layers\":[");
            SEND_STRING(SS_TAP(X_ENTER));
        for (l = 0; l <= _ADJUST; l++) {
#else

            for (l = 0; l <= _ADJUST; l++) {
            switch (l ) {
                CASE_LAYER(_COLEMAK);
                CASE_LAYER(_QWERTY);
                CASE_LAYER(_DVORAK);
                CASE_LAYER(_LOWER);
                CASE_LAYER(_RAISE);
                CASE_LAYER(_NUMPAD);
                CASE_LAYER(_FUNCTION);
                CASE_LAYER(_MOUSE);
                CASE_LAYER(_ADJUST);
            }
            SEND_STRING(buf);
            SEND_STRING(SS_TAP(X_ENTER));
#endif 
            for (r=0;r<MATRIX_ROWS/2;r++) {
                li=0;
                ri=0;
                c=0;
                j = r+4;
#ifdef PRINT_JSON
                if (r==0 && c==0) {
                    if (l!=0) {
                        strcpy(format, ",[\"%s\"");
                    } else {
                        strcpy(format, "[\"%s\"");
                    }
                }
#endif
         
                for (c=0;c<MATRIX_COLS;c++) {
//                    sprintf(rstr,"L:%d R:%d C:%d KC:%x", l,r,c, keymaps[l][r][c] );

                    if (r<4) {
                            li += sprintf(lstr+li,format,   get_code(l,r,c,buf));
#ifdef PRINT_JSON
                            strcpy(format, ",\"%s\"");
#endif                            
                            ri += sprintf(rstr+ri,format,   get_code(l,j,c,buf)); 
                                                     
                    } else {   
#ifdef PRINT_JSON
                            strcpy(format, ",\"%s\"");
#endif                          
                        switch (c) {                 
                        case 0 ... 2:                
                        case 6 ... 8:                
                            li += sprintf(lstr+li,format,  get_code(l,8,c, buf));
                            ri += sprintf(rstr+ri,format,  get_code(l,9,c,buf));
                            break;                   
                        case 3 ... 5:                
                        case 9 ... 11:               
                            li += sprintf(lstr+li,format,  get_code(l,9,c, buf));
                            ri += sprintf(rstr+ri,format,  get_code(l,8,c, buf));
                            break;
                        }
                    }
                }
                        
                SEND_STRING(lstr);
                SEND_STRING(rstr);
                SEND_STRING(SS_TAP(X_ENTER));
            }
#ifdef PRINT_JSON
            SEND_STRING("]");
        SEND_STRING(SS_TAP(X_ENTER));
#endif
            
        }

#ifdef PRINT_JSON
        SEND_STRING("]}");
        SEND_STRING(SS_TAP(X_ENTER));
#endif
    }
