/**
 * \file
 *
 * \brief Declaration of main function used by HID keyboard example
 *
 * Copyright (c) 2009-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _MAIN_H_
#define _MAIN_H_

//Enters the application in low power mode
//Callback called when USB host sets USB line in suspend state
void main_suspend_action(void);

//Called by UDD when the USB line exit of suspend state
void main_resume_action(void);

//Called when a start of frame is received on USB line
void main_sof_action(void);

//Called by UDC when USB Host request to enable remote wakeup
void main_remotewakeup_enable(void);

//Called by UDC when USB Host request to disable remote wakeup
void main_remotewakeup_disable(void);


#ifdef KBD
extern volatile bool main_b_kbd_enable;
bool main_kbd_enable(void);
void main_kbd_disable(void);
#endif //KBD

#ifdef NKRO
extern volatile bool main_b_nkro_enable;
bool main_nkro_enable(void);
void main_nkro_disable(void);
#endif //NKRO

#ifdef EXK
extern volatile bool main_b_exk_enable;
bool main_exk_enable(void);
void main_exk_disable(void);
#endif //EXK

#ifdef MOU
extern volatile bool main_b_mou_enable;
bool main_mou_enable(void);
void main_mou_disable(void);
#endif //MOU

#ifdef RAW
extern volatile bool main_b_raw_enable;
bool main_raw_enable(void);
void main_raw_disable(void);
#endif //RAW

#endif // _MAIN_H_
