typedef struct _xglobal_t {
    uint16_t last_pressed_time;
    uint16_t last_pressed_key;
    uint16_t last_released_time;
    uint16_t last_released_key;
} xglobal_t;

typedef struct _xkey_t {
    int8_t  consecutive_count;
    uint16_t duration;
} xkey_t;


xkey_t _renda;
xkey_t _longpress;
xglobal_t _xkey;

bool xkey_process_record_user(uint16_t keycode, keyrecord_t *record);

inline bool is_renda(uint16_t keycode,uint8_t cnt)
{
    return keycode == _xkey.last_released_key && cnt == _renda.consecutive_count;
}

