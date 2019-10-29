#include QMK_KEYBOARD_H

	/* Escape always goes back to default layer.
	 * Full set of Ctrl, Alt, Shift almost throughout.
	 * Using QMK at qmk.thevankeyboards.com, which adds led support. */

#define _LTR 0 // letters (Dvorak)
#define _NSY 1 // numbers and symbols
#define _FUN 2 // function keys, layer switcher, repeaters for tap-key symbols
#define _MOV 3 // movement arrows and mouse
#define _RAR 4 // strange keys never used
#define _RST 5 // reseting the board

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 
	/* Layer 0: Dvorak, layers under thumbs, two arrows (not for normal typing).
	 *
	 */ 

	[ _LTR ] = LAYOUT (

	/*  Esc      '"  ,<  .>  pP  yY  fF  gG  cC  rR  lL      Bksp
	 *  Tab+LCtl  aA  oO  eE  uU  iI  dD  hH  tT  nN  sS  -_+RCtl
	 *  LSht       ;:  qQ  jJ  kK  xX  bB  mM  wW  vV  zZ    RSht
	 *  LAlt    Left _MOV  Enter+_NSY Space+_NSY _FUN  Right RAlt
	 *               hold   hold        hold    toggle 
	 */

	KC_ESC           , KC_QUOT     , KC_COMM     , KC_DOT               , KC_P                 , KC_Y         , KC_F        , KC_G    , KC_C , KC_R , KC_L , KC_BSPC          ,
       	LCTL_T ( KC_TAB ) , KC_A        , KC_O        , KC_E                 , KC_U                 , KC_I         , KC_D        , KC_H    , KC_T , KC_N , KC_S , RCTL_T ( KC_MINS ) ,
       	KC_LSFT            , KC_SCLN     , KC_Q        , KC_J                 , KC_K                 , KC_X         , KC_B        , KC_M    , KC_W , KC_V , KC_Z , KC_RSFT          ,
       	KC_LALT             , KC_LEFT     , TT ( _MOV ) ,  LT ( _NSY , KC_ENT ) , LT ( _NSY , KC_SPC ) , TG ( _FUN ) , KC_RGHT     , KC_RALT
	            ) ,


	/* Layer 1: Numbers and symbols.
	 *
	 */

	[ _NSY ] = LAYOUT (
	   
	/* _LTR  !   @   #   $   %   ^   &   *   (   )        Del
	 * LCtl   1   2   3   4   5   \|  =+  /?  [{  ]}  `~+RCtl
	 * LSht    0   9   8   7   6    |   +   ?   {   }    RSht
	 * LAlt  xxx    ___    ___     ___       ___    xxx  RAlt
	 * */
			
	TG ( _LTR ) , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_DEL          ,
       	KC_LCTL      , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_BSLS , KC_EQL  , KC_SLSH , KC_LBRC , KC_RBRC , RCTL ( KC_GRV ) , 
	KC_LSFT       , KC_0    , KC_9    , KC_8    , KC_7    , KC_6    , KC_PIPE , KC_PLUS , KC_QUES , KC_LCBR , KC_RCBR , KC_RSFT         , 
	KC_LALT        , KC_LEFT , _______ , _______ , _______ , _______ , KC_RGHT , KC_RALT
	            ) ,


	/* Layer 2: Function keys,
	 * Toward any layer by toggle.
	 * The keys on default layer which are on a tap key there,
	 * in case they need repeating.
	 */

	
	[ _FUN ] = LAYOUT (
	
 	/* _LTR _NSY _FUN _MOV _RAR _RST  xxx  xxx xxx  xxx  xxx    ~
 	 * LCtl   F1   F2   F3   F4   F5   xxx  F11  F12  F13  F14  RCtl
 	 * LSht    F10  F9   F8   F7   F6   xxx  Tab  Ent  Space -  RSht
	 * LAlt  xxx    ___     ___      ___      ___         L0    RAlt
	 */

	TG ( _LTR ) , TG ( _NSY ) , TG ( _FUN ) , TG ( _MOV ) , TG ( _RAR ) , TG ( _RST ) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_TILD ,
       	KC_LCTL      , KC_F1       , KC_F2       , KC_F3       , KC_F4       , KC_F5       , XXXXXXX , KC_F11  , KC_F12  , KC_F13  , KC_F14  , KC_RCTL ,
       	KC_LSFT       , KC_F10      , KC_F9       , KC_F8       , KC_F7       , KC_F6       , XXXXXXX , KC_TAB , KC_ENT   , KC_SPC  , KC_MINS  , KC_RSFT ,
       	KC_LALT        , KC_LEFT     , _______     , _______     , _______     , _______     , KC_RGHT , KC_RALT
	            ) ,


	/* Layer 3: Movement layer: mouse and hands on navigation
	 */

	[ _MOV ] = LAYOUT (

	/* _LTR WLft WDn  WUp  WRht  xxx  Btn3 Home PgUp PgDn End    Bksp
	 * LCtl  MLft MDn  MUp  MRht  xxx  Btn1 Left Up   Down Right RCtl
	 * LSht   Btn5 Btn4 Btn3 Butn2 Btn1 Btn2 Acc0 Acc1 Acc2 xxx  RSht
	 * LAlt   _LTR   ___     ___      ___      ___       _LTR    RAlt
	 */
			
	TG ( _LTR ) , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , XXXXXXX , KC_BTN3 , KC_HOME , KC_PGUP , KC_PGDN , KC_END  , KC_BSPC ,
       	KC_LCTL      , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , KC_BTN1 , KC_BTN1 , KC_LEFT , KC_UP   , KC_DOWN , KC_RGHT , KC_RCTL ,
       	KC_LSFT       , KC_BTN5 , KC_BTN4 , KC_BTN3 , KC_BTN2 , XXXXXXX , KC_BTN2 , KC_ACL0 , KC_ACL1 , KC_ACL2 , XXXXXXX , KC_RSFT ,
       	KC_LALT        , KC_LEFT , _______ , _______ , _______ , _______ , KC_RGHT , KC_RALT
	           ) ,

	/* Layer 4: Dump for various unused keys. Media keys on 2nd row.
	 *          There seem to be more than one Power key variant in some keymaps thus room for two.
	 */

	[ _RAR ] = LAYOUT (

	/*  _LTR Power Power Sleep Wake xxx  xxx  xxx  xxx  Pause ScrLk PrtSc
	 *  Caps  xxx   xxx   xxx   xxx  xxx  xxx  xxx  xxx  xxx   xxx Insert
	 *  NumL   Stop  Play  Prev  Next Vol- Vol+ Mute xxx  xxx   xxx   xxx
	 *  xxx    LGUI    ___   ___       ___      ___      RGUI         App
	 */

	TG ( _LTR ) , KC_PWR  , KC_PWR  , KC_SLEP , KC_WAKE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PAUS , KC_SLCK , KC_PSCR , 
	KC_CAPS      , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_INS  ,
       	KC_NLCK       , KC_MSTP , KC_MPLY , KC_MPRV , KC_MNXT , KC_VOLD , KC_VOLU , KC_MUTE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
       	XXXXXXX        , KC_LEFT , _______ , _______ , _______ , _______ , KC_RGHT , KC_APP  
	            )  ,


	/* Layer 5: Possibly dangerous functions, most keys revert to layer 0 to prevent accidents.
	 *          A letter key precedes the key of interest (Debug, Reset, EepromReset, Pause)
	 *          to give a clue about the next key.
	 *          The keys <b>, both <shifts>, <space> and Pause are added, because QMK documentation
	 *          says there are used for programming the board, although it seems unnecessary in this case.
	 */

	[ _RST ] = LAYOUT (

	/* xxx   xxx   xxx  xxx   xxx  xxx        xxx  xxx  pP  Pause xxx    xxx
	 * dD     Debug rR   Reset eE  EEpromReset xxx  xxx  xxx  xxx  xxx   xxx
	 * LSht    xxx   xxx  xxx   xxx  xxx        bB   xxx  xxx  xxx  xxx RSht
	 * xxx   xxx     ___     ___       ___            ___         xxx    xxx 
	 */

	TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , KC_P        , KC_PAUS     , TG ( _LTR ) , TG ( _LTR ) ,
       	KC_D         , DEBUG       , KC_R        , RESET       , KC_E        , EEP_RST     , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) ,
       	KC_LSFT       , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , KC_B        , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , TG ( _LTR ) , KC_RSFT     ,
       	TG ( _LTR )    , TG ( _LTR ) , _______     , _______     , _______     , _______     , TG ( _LTR ) , TG ( _LTR )
	            )
};
