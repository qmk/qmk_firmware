/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include "keychron_task.h"
#include "quantum.h"
#include "keychron_common.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#endif

#ifdef KEYCHRON_CALLBACK_ENABLE

typedef struct lk_node {
    keychron_cb      lk_cb;
    struct lk_node *next;
} lk_Node;

typedef struct lk_process_node {
    keychron_record_process_cb process_cb;
    struct lk_process_node   *next;
} lk_process_Node;

lk_Node         *p;
lk_Node         *lk_task_list = NULL;
lk_process_Node *p_process;
lk_process_Node *lk_record_process_list = NULL;

#    if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
lk_Node *led_indicator_task_list = NULL;
#    endif

void register_keychron_cb(lk_Node **head, keychron_cb cb, bool priority) {
    /* Create task node */
    lk_Node *task = (lk_Node *)malloc(sizeof(lk_Node));
    task->lk_cb   = cb;
    task->next    = NULL;

    /* Add to the list*/
    if (*head) {
        if (priority) {
            task->next = *head;
            *head      = task;
        } else {
            p = *head;
            while (p->next)
                p = p->next;
            p->next = task;
        }
    } else {
        *head = task;
    }
}

void deregister_keychron_cb(lk_Node **head, keychron_cb cb) {
    p = *head;
    while (p) {
        if (p->lk_cb == cb) {
            // lk_Node* temp = p;
            // if
        }
    }
}

void register_keychron_task(keychron_cb cb, bool priority) {
    register_keychron_cb(&lk_task_list, cb, priority);
}

void register_led_indicator_task(keychron_cb cb, bool priority) {
    register_keychron_cb(&led_indicator_task_list, cb, priority);
}

void register_record_process(keychron_record_process_cb cb, bool priority) {
    lk_process_Node *process = (lk_process_Node *)malloc(sizeof(lk_process_Node));
    process->process_cb      = cb;
    process->next            = NULL;

    /* Add to the list*/
    if (lk_record_process_list) {
        if (priority) {
            process->next          = lk_record_process_list;
            lk_record_process_list = process;
        } else {
            p_process = lk_record_process_list;
            while (p_process->next)
                p_process = p_process->next;
            p_process->next = process;
        }
    } else {
        lk_record_process_list = process;
    }
}

inline void keychron_task(void) {
    p = lk_task_list;
    while (p) {
        p->lk_cb();
        p = p->next;
    }
}

inline bool process_record_keychron(uint16_t keycode, keyrecord_t *record) {
    p_process = lk_record_process_list;
    while (p_process) {
        if (!p_process->process_cb(keycode, record)) {
            return false;
        }
        p_process = p_process->next;
    }

    return true;
}

#    if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)
#        if defined(LED_MATRIX_ENABLE)
inline bool led_matrix_indicators_keychron(void) {
#        else
inline bool rgb_matrix_indicators_keychron(void) {
#        endif

    p = led_indicator_task_list;
    while (p) {
        p->lk_cb();
        p = p->next;
    }

    return true;
}
#    endif

#else

__attribute__((weak)) bool process_record_keychron_kb(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_keychron(uint16_t keycode, keyrecord_t *record) {
#    ifdef LK_WIRELESS_ENABLE
    extern bool process_record_wireless(uint16_t keycode, keyrecord_t * record);
    if (!process_record_wireless(keycode, record)) return false;
#    endif
#    ifdef FACTORY_TEST_ENABLE
    if (!process_record_factory_test(keycode, record)) return false;
#    endif
    // extern bool process_record_keychron_kb(uint16_t keycode, keyrecord_t *record);

    if (!process_record_keychron_kb(keycode, record)) return false;

    return true;
}

#    if defined(LED_MATRIX_ENABLE)
bool led_matrix_indicators_keychron(void) {
#        ifdef LK_WIRELESS_ENABLE
    extern bool led_matrix_indicators_bt(void);
    led_matrix_indicators_bt();
#        endif
#        ifdef FACTORY_TEST_ENABLE
    factory_test_indicator();
#        endif
    return true;
}
#    endif

#    if defined(RGB_MATRIX_ENABLE)
bool rgb_matrix_indicators_keychron(void) {
#        ifdef LK_WIRELESS_ENABLE
    extern bool rgb_matrix_indicators_bt(void);
    rgb_matrix_indicators_bt();
#        endif
#        ifdef FACTORY_TEST_ENABLE
    factory_test_indicator();
#        endif
    return true;
}
#    endif

__attribute__((weak)) bool keychron_task_kb(void) {
    return true;
}

void keychron_task(void) {
#    ifdef LK_WIRELESS_ENABLE
    extern void wireless_tasks(void);
    wireless_tasks();
#    endif
#    ifdef FACTORY_TEST_ENABLE
    factory_test_task();
#    endif
    keychron_common_task();

    keychron_task_kb();
}
#endif // #ifdef KEYCHRON_CALLBACK_ENABLE

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) return false;

    if (!process_record_keychron(keycode, record)) return false;

    return true;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) return false;

    rgb_matrix_indicators_keychron();

    return true;
}
#endif

#ifdef LED_MATRIX_ENABLE
bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) return false;

    led_matrix_indicators_keychron();

    return true;
}
#endif

void housekeeping_task_kb(void) {
    keychron_task();
}
