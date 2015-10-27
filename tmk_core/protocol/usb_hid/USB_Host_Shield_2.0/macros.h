/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */

#if !defined(_usb_h_) || defined(MACROS_H)
#error "Never include macros.h directly; include Usb.h instead"
#else
#define MACROS_H

////////////////////////////////////////////////////////////////////////////////
// HANDY MACROS
////////////////////////////////////////////////////////////////////////////////

#define VALUE_BETWEEN(v,l,h) (((v)>(l)) && ((v)<(h)))
#define VALUE_WITHIN(v,l,h) (((v)>=(l)) && ((v)<=(h)))
#define output_pgm_message(wa,fp,mp,el) wa = &mp, fp((char *)pgm_read_pointer(wa), el)
#define output_if_between(v,l,h,wa,fp,mp,el) if(VALUE_BETWEEN(v,l,h)) output_pgm_message(wa,fp,mp[v-(l+1)],el);

#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
#ifndef __BYTE_GRABBING_DEFINED__
#define __BYTE_GRABBING_DEFINED__ 1
#ifdef BROKEN_OPTIMIZER_LITTLE_ENDIAN
// Note: Use this if your compiler generates horrible assembler!
#define BGRAB0(__usi__)  (((uint8_t *)&(__usi__))[0])
#define BGRAB1(__usi__)  (((uint8_t *)&(__usi__))[1])
#define BGRAB2(__usi__)  (((uint8_t *)&(__usi__))[2])
#define BGRAB3(__usi__)  (((uint8_t *)&(__usi__))[3])
#define BGRAB4(__usi__)  (((uint8_t *)&(__usi__))[4])
#define BGRAB5(__usi__)  (((uint8_t *)&(__usi__))[5])
#define BGRAB6(__usi__)  (((uint8_t *)&(__usi__))[6])
#define BGRAB7(__usi__)  (((uint8_t *)&(__usi__))[7])
#else
// Note: The cast alone to uint8_t is actually enough.
// GCC throws out the "& 0xff", and the size is no different.
// Some compilers need it.
#define BGRAB0(__usi__)  ((uint8_t)((__usi__) & 0xff ))
#define BGRAB1(__usi__)  ((uint8_t)(((__usi__) >> 8) & 0xff))
#define BGRAB2(__usi__)  ((uint8_t)(((__usi__) >> 16) & 0xff))
#define BGRAB3(__usi__)  ((uint8_t)(((__usi__) >> 24) & 0xff))
#define BGRAB4(__usi__)  ((uint8_t)(((__usi__) >> 32) & 0xff))
#define BGRAB5(__usi__)  ((uint8_t)(((__usi__) >> 40) & 0xff))
#define BGRAB6(__usi__)  ((uint8_t)(((__usi__) >> 48) & 0xff))
#define BGRAB7(__usi__)  ((uint8_t)(((__usi__) >> 56) & 0xff))
#endif
#define BOVER1(__usi__)  ((uint16_t)(__usi__) << 8)
#define BOVER2(__usi__)  ((uint32_t)(__usi__) << 16)
#define BOVER3(__usi__)  ((uint32_t)(__usi__) << 24)
#define BOVER4(__usi__)  ((uint64_t)(__usi__) << 32)
#define BOVER5(__usi__)  ((uint64_t)(__usi__) << 40)
#define BOVER6(__usi__)  ((uint64_t)(__usi__) << 48)
#define BOVER7(__usi__)  ((uint64_t)(__usi__) << 56)

// These are the smallest and fastest ways I have found so far in pure C/C++.
#define BMAKE16(__usc1__,__usc0__) ((uint16_t)((uint16_t)(__usc0__) | (uint16_t)BOVER1(__usc1__)))
#define BMAKE32(__usc3__,__usc2__,__usc1__,__usc0__) ((uint32_t)((uint32_t)(__usc0__) | (uint32_t)BOVER1(__usc1__) | (uint32_t)BOVER2(__usc2__) | (uint32_t)BOVER3(__usc3__)))
#define BMAKE64(__usc7__,__usc6__,__usc5__,__usc4__,__usc3__,__usc2__,__usc1__,__usc0__) ((uint64_t)((uint64_t)__usc0__ | (uint64_t)BOVER1(__usc1__) | (uint64_t)BOVER2(__usc2__) | (uint64_t)BOVER3(__usc3__) | (uint64_t)BOVER4(__usc4__) | (uint64_t)BOVER5(__usc5__) | (uint64_t)BOVER6(__usc6__) | (uint64_t)BOVER1(__usc7__)))
#endif

/*
 * Debug macros: Strings are stored in progmem (flash) instead of RAM.
 */
#define USBTRACE(s) (Notify(PSTR(s), 0x80))
#define USBTRACE1(s,l) (Notify(PSTR(s), l))
#define USBTRACE2(s,r) (Notify(PSTR(s), 0x80), D_PrintHex((r), 0x80), Notify(PSTR("\r\n"), 0x80))
#define USBTRACE3(s,r,l) (Notify(PSTR(s), l), D_PrintHex((r), l), Notify(PSTR("\r\n"), l))


#endif /* MACROS_H */

