#ifndef TRANSKEYCODE_USER
	#define TRANSKEYCODE_USER(X) X
#endif

#define TRANSKEYCODE_ACTION_TAP_DANCE_DOUBLE(kc1, kc2) { \
    .fn = { transkeycode_tap_dance_pair_on_each_tap, transkeycode_tap_dance_pair_finished, transkeycode_tap_dance_pair_reset }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }),  \
  }

const char* get_kb_layout(void);
void select_kb_layout(uint8_t id);

void transkeycode_set(const uint8_t* layout,const char* name);
void transkeycode_reset(void);
__attribute__ ((weak)) uint16_t transkeycode(uint16_t kc);


#ifndef TRANSKEYCODE_ON_CHANGE_KB_LAYOUT
    #define TRANSKEYCODE_ON_CHANGE_KB_LAYOUT(ID,NAME)  ((void)0)
#endif

#define TRANSKEYCODE_DEF(Q,W,E,R,T,Y,U,I,O,P, A,S,D,F,G,H,J,K,L,SCLN, Z,X,C,V,B,N,M,COMM,DOT,SLSH) { \
    KC_##A,KC_##B,KC_##C,KC_##D,KC_##E,KC_##F,KC_##G,KC_##H,KC_##I,KC_##J,KC_##K,KC_##L,KC_##M,KC_##N,KC_##O,KC_##P,KC_##Q,KC_##R,KC_##S,KC_##T,KC_##U,KC_##V,KC_##W,KC_##X,KC_##Y,KC_##Z, \
    KC_##SCLN,KC_##COMM, KC_##DOT, KC_##SLSH  }

#define TRANSKEYCODE_DEF_N(Q,W,E,R,T,Y,U,I,O,P, A,S,D,F,G,H,J,K,L,SCLN, Z,X,C,V,B,N,M,COMM,DOT,SLSH) { \
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, \
    KC_##SCLN,KC_##COMM, KC_##DOT, KC_##SLSH  }
