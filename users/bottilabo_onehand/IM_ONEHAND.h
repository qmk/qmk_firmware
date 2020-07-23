/* Copyright 2020 bottilabo [twitter @bottinabo]
 *                          [https://github.com/bottilabo/bottilabo_onehand]
 *
 * GNU General Public License version 3 [http://www.gnu.org/licenses/]
 */

#define ONEHAND_KANA_BUF_SZ 5
typedef struct {
    bool enabled;
    uint8_t im_mode;
    uint8_t mod_shift;
    uint8_t mod_ctl;
    uint8_t mod_alt;
    uint8_t mod_gui;
    uint8_t press_cnt;
    tick_t time_max;
    tick_t time_pressed;
    tick_t time_released;
      
    uint8_t chrcount;
    uint32_t keycomb;
    uint32_t keyreleased;
    int8_t candidate_idx;
    uint32_t candidate[ONEHAND_KANA_BUF_SZ];
} onehand_t;
extern onehand_t _onehand;

bool onehand_type(bool long_press);
void onehand_clear(void);

void onehand_mode(uint16_t, keyrecord_t *);

void onehand_on(void);
void onehand_off(void);
bool onehand_state(void);

bool process_ONEHAND(uint16_t, keyrecord_t *);
void set_onehand(uint8_t);


void IM_ONEHAND_enable(uint8_t modef);
uint16_t onehand_transkeycode_keycode(uint16_t kc);

#ifndef ONEHAND_TERM
#define ONEHAND_TERM 33
#endif
    
#ifndef DBLTAP_TERM
#define DBLTAP_TERM 200
#endif
    
#ifndef LONGPRESS_TERM
#define LONGPRESS_TERM 200
#endif
