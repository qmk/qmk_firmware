/* If you’d like to contribute a locale, we've created a google sheet:
 * https://docs.google.com/spreadsheets/d/1gSB063BTHLTNLSGalzkhqz82RdBRVQytXKlabhX5Zcg/edit?usp=sharing
 * Get in touch with us over email <contact@zsa.io> and we can help you get started!
 */

//Polish programmer, contributed by Krzysztof Bogacz.
#define PL_01 ALGR(KC_Z) // ż
#define PL_02 ALGR(KC_X) // ź
#define PL_03 ALGR(KC_S) // ś
#define PL_04 ALGR(KC_O) // ó
#define PL_05 ALGR(KC_N) // ń
#define PL_06 ALGR(KC_L) // ł
#define PL_07 ALGR(KC_E) // ę
#define PL_08 ALGR(KC_C) // ć
#define PL_09 ALGR(KC_A) // ą

//Kazakh, contributed by Zhanibek Adilbekov
#define KK_01 KC_SLASH    // №
#define KK_02 KC_DOT      // ю
#define KK_03 KC_COMMA    // б
#define KK_04 KC_M        // ь
#define KK_05 KC_N        // т
#define KK_06 KC_B        // и
#define KK_07 KC_V        // м
#define KK_08 KC_X        // ч
#define KK_09 KC_Z        // я
#define KK_10 KC_QUOTE    // э
#define KK_11 KC_SCOLON   // ж
#define KK_12 KC_L        // д
#define KK_13 KC_K        // л
#define KK_14 KC_J        // о
#define KK_15 KC_H        // р
#define KK_16 KC_G        // п
#define KK_17 KC_F        // а
#define KK_18 KC_D        // в
#define KK_19 KC_S        // ы
#define KK_20 KC_A        // ф
#define KK_21 KC_RBRACKET // ъ
#define KK_22 KC_LBRACKET // х
#define KK_23 KC_P        // з
#define KK_24 KC_O        // щ
#define KK_25 KC_I        // ш
#define KK_26 KC_U        // г
#define KK_27 KC_Y        // н
#define KK_28 KC_T        // е
#define KK_29 KC_R        // к
#define KK_30 KC_E        // у
#define KK_31 KC_W        // ц
#define KK_32 KC_Q        // й
#define KK_33 KC_EQUAL    // һ
#define KK_34 KC_MINUS    // ө
#define KK_35 KC_0        // қ
#define KK_36 KC_9        // ұ
#define KK_37 KC_8        // ү
#define KK_38 KC_7        // .
#define KK_39 KC_6        // ,
#define KK_40 KC_5        // ғ
#define KK_41 KC_4        // ң
#define KK_42 KC_3        // і
#define KK_43 KC_2        // ә
#define KK_44 KC_1        // "

//Portuguese OSX, contributed by André Cruz (@edevil)
#define PT_OSX_SECT KC_GRV  // §
#define PT_OSX_QUOT KC_MINS // '
#define PT_OSX_PLUS KC_EQL  // +
#define PT_OSX_MORD KC_LBRC // º
#define PT_OSX_ACUT KC_RBRC // ´ (dead)
#define PT_OSX_CCED KC_SCLN // Ç
#define PT_OSX_TILD KC_QUOT // ~ (dead)
#define PT_OSX_BSLS KC_NUHS // (backslash)
#define PT_OSX_LABK KC_NUBS // <
#define PT_OSX_MINS KC_SLSH // -
#define PT_OSX_PLMN S(PT_OSX_SECT) // ±
#define PT_OSX_EXLM S(KC_1)    // !
#define PT_OSX_DQUO S(KC_2)    // "
#define PT_OSX_HASH S(KC_3)    // #
#define PT_OSX_DLR  S(KC_4)    // $
#define PT_OSX_PERC S(KC_5)    // %
#define PT_OSX_AMPR S(KC_6)    // &
#define PT_OSX_SLSH S(KC_7)    // /
#define PT_OSX_LPRN S(KC_8)    // (
#define PT_OSX_RPRN S(KC_9)    // )
#define PT_OSX_EQL  S(KC_0)    // =
#define PT_OSX_QUES S(PT_OSX_QUOT) // ?
#define PT_OSX_ASTR S(PT_OSX_PLUS) // *
#define PT_OSX_FORD S(PT_OSX_MORD) // ª
#define PT_OSX_GRV  S(PT_OSX_ACUT) // ` (dead)
#define PT_OSX_CIRC S(PT_OSX_TILD) // ^ (dead)
#define PT_OSX_PIPE S(PT_OSX_BSLS) // |
#define PT_OSX_RABK S(PT_OSX_LABK) // >
#define PT_OSX_SCLN S(KC_COMM) // ;
#define PT_OSX_COLN S(KC_DOT)  // :
#define PT_OSX_UNDS S(PT_OSX_MINS) // _
#define PT_OSX_APPL A(KC_1)    //  (Apple logo)
#define PT_OSX_AT   A(KC_2)    // @
#define PT_OSX_EURO A(KC_3)    // €
#define PT_OSX_PND  A(KC_4)    // £
#define PT_OSX_PERM A(KC_5)    // ‰
#define PT_OSX_PILC A(KC_6)    // ¶
#define PT_OSX_DIV  A(KC_7)    // ÷
#define PT_OSX_LBRC A(KC_8)    // [
#define PT_OSX_RBRC A(KC_9)    // ]
#define PT_OSX_NEQL A(KC_0)    // ≠
#define PT_OSX_OE   A(KC_Q)    // Œ
#define PT_OSX_NARS A(KC_W)    // ∑
#define PT_OSX_AE   A(KC_E)    // Æ
#define PT_OSX_REGD A(KC_R)    // ®
#define PT_OSX_TM   A(KC_T)    // ™
#define PT_OSX_YEN  A(KC_Y)    // ¥
#define PT_OSX_DAGG A(KC_U)    // †
#define PT_OSX_DLSI A(KC_I)    // ı
#define PT_OSX_OSTR A(KC_O)    // Ø
#define PT_OSX_PI   A(KC_P)    // π
#define PT_OSX_DEG  A(PT_OSX_MORD) // °
#define PT_OSX_DIAE A(PT_OSX_ACUT) // ¨ (dead)
#define PT_OSX_ARNG A(KC_A)    // å
#define PT_OSX_SS   A(KC_S)    // ß
#define PT_OSX_PDIF A(KC_D)    // ∂
#define PT_OSX_FHK  A(KC_F)    // ƒ
#define PT_OSX_DOTA A(KC_G)    // ˙
#define PT_OSX_CARN A(KC_H)    // ˇ
#define PT_OSX_MACR A(KC_J)    // ¯
#define PT_OSX_DLQU A(KC_K)    // „
#define PT_OSX_LSQU A(KC_L)    // ‘
#define PT_OSX_CEDL A(PT_OSX_CCED) // ¸
#define PT_OSX_STIL A(PT_OSX_TILD) // ˜ (dead)
#define PT_OSX_LSAQ A(PT_OSX_BSLS) // ‹
#define PT_OSX_LTEQ A(PT_OSX_LABK) // ≤
#define PT_OSX_OMEG A(KC_Z)    // Ω
#define PT_OSX_LDAQ A(KC_X)    // «
#define PT_OSX_COPY A(KC_C)    // ©
#define PT_OSX_SQRT A(KC_V)    // √
#define PT_OSX_INTG A(KC_B)    // ∫
#define PT_OSX_NOT  A(KC_N)    // ¬
#define PT_OSX_MICR A(KC_M)    // µ
#define PT_OSX_LDQU A(KC_COMM) // “
#define PT_OSX_ELLP A(KC_DOT)  // …
#define PT_OSX_MDSH A(PT_OSX_MINS) // —
#define PT_OSX_IEXL S(A(KC_1))    // ¡
#define PT_OSX_FI   S(A(KC_2))    // ﬁ
#define PT_OSX_FL   S(A(KC_3))    // ﬂ
#define PT_OSX_CENT S(A(KC_4))    // ¢
#define PT_OSX_INFN S(A(KC_5))    // ∞
#define PT_OSX_BULT S(A(KC_6))    // •
#define PT_OSX_FRSL S(A(KC_7))    // ⁄
#define PT_OSX_LCBR S(A(KC_8))    // {
#define PT_OSX_RCBR S(A(KC_9))    // }
#define PT_OSX_AEQL S(A(KC_0))    // ≈
#define PT_OSX_IQUE S(A(PT_OSX_QUOT)) // ¿
#define PT_OSX_LOZN S(A(PT_OSX_PLUS)) // ◊
#define PT_OSX_DDAG S(A(KC_U))    // ‡
#define PT_OSX_RNGA S(A(KC_I))    // ˚
#define PT_OSX_NARP S(A(KC_P))    // ∏
#define PT_OSX_DACU S(A(PT_OSX_ACUT)) // ˝
#define PT_OSX_INCR S(A(KC_D))    // ∆
#define PT_OSX_SLQU S(A(KC_K))    // ‚
#define PT_OSX_RSQU S(A(KC_L))    // ’
#define PT_OSX_OGON S(A(PT_OSX_CCED)) // ˛
#define PT_OSX_DCIR S(A(PT_OSX_TILD)) // ˆ (dead)
#define PT_OSX_RSAQ S(A(PT_OSX_BSLS)) // ›
#define PT_OSX_GTEQ S(A(PT_OSX_LABK)) // ≥
#define PT_OSX_RDAQ S(A(KC_X))    // »
#define PT_OSX_RDQU S(A(KC_COMM)) // ”
#define PT_OSX_MDDT S(A(KC_DOT))  // ·
#define PT_OSX_NDSH S(A(PT_OSX_MINS)) // –

// Swiss French aliases to avoid collisions with Swiss german ones
#define FRCH_Y KC_Z
#define FRCH_Z KC_Y
#define FRCH_SECT KC_GRV
#define FRCH_QUOT KC_MINS
#define FRCH_CIRC KC_EQL
#define FRCH_EGRV KC_LBRC
#define FRCH_DIAE KC_RBRC
#define FRCH_EACU KC_SCLN
#define FRCH_AGRV KC_QUOT
#define FRCH_DLR KC_NUHS
#define FRCH_LABK KC_NUBS
#define FRCH_MINS KC_SLSH
#define FRCH_DEG S(FRCH_SECT)
#define FRCH_PLUS S(KC_1)
#define FRCH_DQUO S(KC_2)
#define FRCH_ASTR S(KC_3)
#define FRCH_CCED S(KC_4)
#define FRCH_PERC S(KC_5)
#define FRCH_AMPR S(KC_6)
#define FRCH_SLSH S(KC_7)
#define FRCH_LPRN S(KC_8)
#define FRCH_RPRN S(KC_9)
#define FRCH_EQL S(KC_0)
#define FRCH_QUES S(FRCH_QUOT)
#define FRCH_GRV S(FRCH_CIRC)
#define FRCH_UDIA S(FRCH_EGRV)
#define FRCH_EXLM S(FRCH_DIAE)
#define FRCH_ODIA S(FRCH_EACU)
#define FRCH_ADIA S(FRCH_AGRV)
#define FRCH_PND S(FRCH_DLR)
#define FRCH_RABK S(FRCH_LABK)
#define FRCH_SCLN S(KC_COMM)
#define FRCH_COLN S(KC_DOT)
#define FRCH_UNDS S(KC_MINS)
#define FRCH_BRKP ALGR(CH_1)
#define FRCH_AT ALGR(KC_2)
#define FRCH_HASH ALGR(KC_3)
#define FRCH_NOT ALGR(KC_6)
#define FRCH_PIPE ALGR(KC_7)
#define FRCH_CENT ALGR(KC_8)
#define FRCH_ACUT ALGR(FRCH_QUOT)
#define FRCH_TILD ALGR(FRCH_CIRC)
#define FRCH_EURO ALGR(KC_E)
#define FRCH_LBRC ALGR(FRCH_EGRV)
#define FRCH_RBRC ALGR(FRCH_DIAE)
#define FRCH_LCBR ALGR(FRCH_AGRV)
#define FRCH_RCBR ALGR(FRCH_DLR)
#define FRCH_BSLS ALGR(FRCH_LABK)

// Ukrainian
#define UA_01 S(A(KC_EQUAL))
#define UA_02 A(KC_EQUAL)
#define UA_03 S(KC_7)
#define UA_04 S(KC_6)
#define UA_05 S(KC_4)
#define UA_06 S(KC_3)
#define UA_07 S(KC_2)
#define UA_08 A(S(KC_GRAVE))
#define UA_09 A(KC_GRAVE)
#define UA_10 KC_GRAVE
#define UA_11 KC_SLASH
#define UA_12 KC_DOT
#define UA_13 KC_COMMA
#define UA_14 KC_M
#define UA_15 KC_N
#define UA_16 KC_B
#define UA_17 KC_V
#define UA_18 KC_C
#define UA_19 KC_X
#define UA_20 KC_Z
#define UA_21 KC_QUOTE
#define UA_22 KC_SCOLON
#define UA_23 KC_J
#define UA_24 KC_K
#define UA_25 KC_J
#define UA_26 KC_H
#define UA_27 KC_G
#define UA_28 KC_F
#define UA_29 KC_D
#define UA_30 KC_S
#define UA_31 KC_A
#define UA_32 KC_RBRACKET
#define UA_33 KC_LBRACKET
#define UA_34 KC_P
#define UA_35 KC_O
#define UA_36 KC_I
#define UA_37 A(KC_U)
#define UA_38 KC_U
#define UA_39 KC_Y
#define UA_40 KC_T
#define UA_41 KC_R
#define UA_42 KC_E
#define UA_43 KC_W
#define UA_44 KC_W

// French Canadian
#define FRCA_01 ALGR(KC_COMMA)
#define FRCA_02 ALGR(KC_M)
#define FRCA_03 ALGR(KC_RBRACKET)
#define FRCA_04 ALGR(KC_LBRACKET)
#define FRCA_05 ALGR(KC_QUOTE)
#define FRCA_06 ALGR(KC_BSLASH)
#define FRCA_07 KC_GRAVE
#define FRCA_08 A(KC_GRAVE)
#define FRCA_09 S(KC_GRAVE)
#define FRCA_10 S(KC_BSLASH)
#define FRCA_11 KC_BSLASH
#define FRCA_12 KC_RBRACKET
#define FRCA_13 KC_QUOTE
#define FRCA_14 S(KC_RBRACKET)
#define FRCA_15 KC_LBRACKET
#define FRCA_16 KC_SLASH
#define FRCA_17 ALGR(KC_SCOLON)
#define FRCA_18 ALGR(KC_P)
#define FRCA_19 ALGR(KC_O)
#define FRCA_20 ALGR(KC_MINUS)
#define FRCA_21 ALGR(KC_0)
#define FRCA_22 ALGR(KC_9)
#define FRCA_23 ALGR(KC_8)
#define FRCA_24 ALGR(KC_7)
#define FRCA_25 ALGR(KC_6)
#define FRCA_26 ALGR(KC_5)
#define FRCA_27 ALGR(KC_4)
#define FRCA_28 ALGR(KC_3)
#define FRCA_29 ALGR(KC_2)
#define FRCA_30 ALGR(KC_1)
#define FRCA_31 S(KC_6)
#define FRCA_32 S(KC_3)
#define FRCA_33 S(KC_2)

// Icelandic
#define IS_01 S(KC_DOT) //:
#define IS_02 S(KC_COMMA) //;
#define IS_03 ALGR(KC_NONUS_BSLASH) //|
#define IS_04 S(KC_NONUS_BSLASH) //>
#define IS_05 KC_NONUS_BSLASH //<
#define IS_06 S(KC_BSLASH)// *
#define IS_07 S(KC_QUOTE) //´
#define IS_08 S(KC_RBRACKET) //?
#define IS_09 S(KC_EQUAL) //_
#define IS_10 S(KC_GRAVE) //¨
#define IS_11 S(KC_0) //=
#define IS_12 S(KC_8) //(
#define IS_13 S(KC_7) //°
#define IS_14 S(KC_6) //&
#define IS_15 KC_BSLASH //+
#define IS_16 KC_QUOTE //´
#define IS_17 KC_RBRACKET //'
#define IS_18 KC_EQUAL //-
#define IS_19 KC_GRAVE //°
#define IS_20 KC_MINUS //ö
#define IS_21 KC_SCOLON //æ
#define IS_22 KC_LBRACKET //ð
#define IS_23 S(KC_9) //)
#define IS_24 S(KC_2) //"
#define IS_25 S(KC_MINUS) //Ö
#define IS_26 S(KC_SLASH) //Þ
#define IS_27 S(KC_SCOLON) //Æ
#define IS_28 S(KC_LBRACKET) //Ð

// Spanish LATAM
#define ES_LA_01 ALGR(KC_MINUS)
#define ES_LA_02 ALGR(KC_GRAVE) //¬
#define ES_LA_03 ALGR(KC_Q) //@
#define ES_LA_04 ALGR(KC_BSLASH) //`
#define ES_LA_05 ALGR(KC_QUOTE) //^
#define ES_LA_06 ALGR(KC_RBRACKET) //~
#define ES_LA_07 S(KC_SCOLON) //Ñ
#define ES_LA_08 KC_SCOLON //ñ
#define ES_LA_09 S(KC_SLASH) //_
#define ES_LA_10 KC_SLASH //-
#define ES_LA_11 S(KC_DOT) //:
#define ES_LA_12 KC_DOT //.
#define ES_LA_13 S(KC_COMMA) //;
#define ES_LA_14 KC_COMMA //,
#define ES_LA_15 S(KC_NONUS_BSLASH) //>
#define ES_LA_16 KC_NONUS_BSLASH //<
#define ES_LA_17 S(KC_BSLASH) //]
#define ES_LA_18 KC_BSLASH //}
#define ES_LA_19 S(KC_QUOTE) //[
#define ES_LA_20 KC_QUOTE //{
#define ES_LA_21 S(KC_RBRACKET) //*
#define ES_LA_22 KC_RBRACKET //+
#define ES_LA_23 S(KC_LBRACKET) //¨
#define ES_LA_24 KC_LBRACKET //´
#define ES_LA_25 S(KC_EQUAL) //¡
#define ES_LA_26 KC_EQUAL //¿
#define ES_LA_27 S(KC_MINUS) //?
#define ES_LA_28 KC_MINUS //'
#define ES_LA_29 S(KC_0) //=
#define ES_LA_30 S(KC_9) //(
#define ES_LA_31 S(KC_8) //(
#define ES_LA_32 S(KC_7) ///
#define ES_LA_33 S(KC_6) //&
#define ES_LA_34 S(KC_5) //%
#define ES_LA_35 S(KC_4) //$
#define ES_LA_36 S(KC_3) //#
#define ES_LA_37 S(KC_2) //"
#define ES_LA_38 S(KC_1) //!
#define ES_LA_39 S(KC_GRAVE) //°
#define ES_LA_40 KC_GRAVE //|

// Extra CMS codes
#define CSA_MOMEG RCTL(RSFT(KC_Q)) //Ω
