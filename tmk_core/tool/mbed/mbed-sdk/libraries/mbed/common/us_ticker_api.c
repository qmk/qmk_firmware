/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stddef.h>
#include "us_ticker_api.h"
#include "cmsis.h"

static ticker_event_handler event_handler;
static ticker_event_t *head = NULL;

void us_ticker_set_handler(ticker_event_handler handler) {
    us_ticker_init();

    event_handler = handler;
}

void us_ticker_irq_handler(void) {
    us_ticker_clear_interrupt();

    /* Go through all the pending TimerEvents */
    while (1) {
        if (head == NULL) {
            // There are no more TimerEvents left, so disable matches.
            us_ticker_disable_interrupt();
            return;
        }

        if ((int)(head->timestamp - us_ticker_read()) <= 0) {
            // This event was in the past:
            //      point to the following one and execute its handler
            ticker_event_t *p = head;
            head = head->next;
            if (event_handler != NULL) {
                event_handler(p->id); // NOTE: the handler can set new events
            }
            /* Note: We continue back to examining the head because calling the
             * event handler may have altered the chain of pending events. */
        } else {
            // This event and the following ones in the list are in the future:
            //      set it as next interrupt and return
            us_ticker_set_interrupt(head->timestamp);
            return;
        }
    }
}

void us_ticker_insert_event(ticker_event_t *obj, timestamp_t timestamp, uint32_t id) {
    /* disable interrupts for the duration of the function */
    __disable_irq();

    // initialise our data
    obj->timestamp = timestamp;
    obj->id = id;

    /* Go through the list until we either reach the end, or find
       an element this should come before (which is possibly the
       head). */
    ticker_event_t *prev = NULL, *p = head;
    while (p != NULL) {
        /* check if we come before p */
        if ((int)(timestamp - p->timestamp) < 0) {
            break;
        }
        /* go to the next element */
        prev = p;
        p = p->next;
    }

    /* if we're at the end p will be NULL, which is correct */
    obj->next = p;

    /* if prev is NULL we're at the head */
    if (prev == NULL) {
        head = obj;
        us_ticker_set_interrupt(timestamp);
    } else {
        prev->next = obj;
    }

    __enable_irq();
}

void us_ticker_remove_event(ticker_event_t *obj) {
    __disable_irq();

    // remove this object from the list
    if (head == obj) {
        // first in the list, so just drop me
        head = obj->next;
        if (head == NULL) {
            us_ticker_disable_interrupt();
        } else {
            us_ticker_set_interrupt(head->timestamp);
        }
    } else {
        // find the object before me, then drop me
        ticker_event_t* p = head;
        while (p != NULL) {
            if (p->next == obj) {
                p->next = obj->next;
                break;
            }
            p = p->next;
        }
    }

    __enable_irq();
}

int us_ticker_get_next_timestamp(timestamp_t *timestamp) {
    int ret = 0;

    /* if head is NULL, there are no pending events */
    __disable_irq();
    if (head != NULL) {
        *timestamp = head->timestamp;
        ret = 1;
    }
    __enable_irq();

    return ret;
}
