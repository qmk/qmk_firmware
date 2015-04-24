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
#include "TimerEvent.h"
#include "cmsis.h"

#include <stddef.h>

namespace mbed {

TimerEvent::TimerEvent() : event() {
    us_ticker_set_handler((&TimerEvent::irq));
}

void TimerEvent::irq(uint32_t id) {
    TimerEvent *timer_event = (TimerEvent*)id;
    timer_event->handler();
}

TimerEvent::~TimerEvent() {
    remove();
}

// insert in to linked list
void TimerEvent::insert(timestamp_t timestamp) {
    us_ticker_insert_event(&event, timestamp, (uint32_t)this);
}

void TimerEvent::remove() {
    us_ticker_remove_event(&event);
}

} // namespace mbed
