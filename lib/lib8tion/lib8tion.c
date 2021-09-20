#define FASTLED_INTERNAL
#include <stdint.h>

#define RAND16_SEED  1337
uint16_t rand16seed = RAND16_SEED;


// memset8, memcpy8, memmove8:
//  optimized avr replacements for the standard "C" library
//  routines memset, memcpy, and memmove.
//
//  There are two techniques that make these routines
//  faster than the standard avr-libc routines.
//  First, the loops are unrolled 2X, meaning that
//  the average loop overhead is cut in half.
//  And second, the compare-and-branch at the bottom
//  of each loop decrements the low byte of the
//  counter, and if the carry is clear, it branches
//  back up immediately.  Only if the low byte math
//  causes carry do we bother to decrement the high
//  byte and check that result for carry as well.
//  Results for a 100-byte buffer are 20-40% faster
//  than standard avr-libc, at a cost of a few extra
//  bytes of code.

#if defined(__AVR__)
//__attribute__ ((noinline))
void * memset8 ( void * ptr, uint8_t val, uint16_t num )
{
    asm volatile(
         "  movw r26, %[ptr]        \n\t"
         "  sbrs %A[num], 0         \n\t"
         "  rjmp Lseteven_%=        \n\t"
         "  rjmp Lsetodd_%=         \n\t"
         "Lsetloop_%=:              \n\t"
         "  st X+, %[val]           \n\t"
         "Lsetodd_%=:               \n\t"
         "  st X+, %[val]           \n\t"
         "Lseteven_%=:              \n\t"
         "  subi %A[num], 2         \n\t"
         "  brcc Lsetloop_%=        \n\t"
         "  sbci %B[num], 0         \n\t"
         "  brcc Lsetloop_%=        \n\t"
         : [num] "+r" (num)
         : [ptr]  "r" (ptr),
           [val]  "r" (val)
         : "memory"
         );
    return ptr;
}



//__attribute__ ((noinline))
void * memcpy8 ( void * dst, const void* src, uint16_t num )
{
    asm volatile(
         "  movw r30, %[src]        \n\t"
         "  movw r26, %[dst]        \n\t"
         "  sbrs %A[num], 0         \n\t"
         "  rjmp Lcpyeven_%=        \n\t"
         "  rjmp Lcpyodd_%=         \n\t"
         "Lcpyloop_%=:              \n\t"
         "  ld __tmp_reg__, Z+      \n\t"
         "  st X+, __tmp_reg__      \n\t"
         "Lcpyodd_%=:               \n\t"
         "  ld __tmp_reg__, Z+      \n\t"
         "  st X+, __tmp_reg__      \n\t"
         "Lcpyeven_%=:              \n\t"
         "  subi %A[num], 2         \n\t"
         "  brcc Lcpyloop_%=        \n\t"
         "  sbci %B[num], 0         \n\t"
         "  brcc Lcpyloop_%=        \n\t"
         : [num] "+r" (num)
         : [src] "r" (src),
           [dst] "r" (dst)
         : "memory"
         );
    return dst;
}

//__attribute__ ((noinline))
void * memmove8 ( void * dst, const void* src, uint16_t num )
{
    if( src > dst) {
        // if src > dst then we can use the forward-stepping memcpy8
        return memcpy8( dst, src, num);
    } else {
        // if src < dst then we have to step backward:
        dst = (char*)dst + num;
        src = (char*)src + num;
        asm volatile(
             "  movw r30, %[src]        \n\t"
             "  movw r26, %[dst]        \n\t"
             "  sbrs %A[num], 0         \n\t"
             "  rjmp Lmoveven_%=        \n\t"
             "  rjmp Lmovodd_%=         \n\t"
             "Lmovloop_%=:              \n\t"
             "  ld __tmp_reg__, -Z      \n\t"
             "  st -X, __tmp_reg__      \n\t"
             "Lmovodd_%=:               \n\t"
             "  ld __tmp_reg__, -Z      \n\t"
             "  st -X, __tmp_reg__      \n\t"
             "Lmoveven_%=:              \n\t"
             "  subi %A[num], 2         \n\t"
             "  brcc Lmovloop_%=        \n\t"
             "  sbci %B[num], 0         \n\t"
             "  brcc Lmovloop_%=        \n\t"
             : [num] "+r" (num)
             : [src] "r" (src),
               [dst] "r" (dst)
             : "memory"
             );
        return dst;
    }
}

#endif /* AVR */




#if 0
// TEST / VERIFICATION CODE ONLY BELOW THIS POINT
#include <Arduino.h>
#include "lib8tion.h"

void test1abs( int8_t i)
{
    Serial.print("abs("); Serial.print(i); Serial.print(") = ");
    int8_t j = abs8(i);
    Serial.print(j); Serial.println(" ");
}

void testabs()
{
    delay(5000);
    for( int8_t q = -128; q != 127; q++) {
        test1abs(q);
    }
    for(;;){};
}


void testmul8()
{
    delay(5000);
    byte r, c;

    Serial.println("mul8:");
    for( r = 0; r <= 20; r += 1) {
        Serial.print(r); Serial.print(" : ");
        for( c = 0; c <= 20; c += 1) {
            byte t;
            t = mul8( r, c);
            Serial.print(t); Serial.print(' ');
        }
        Serial.println(' ');
    }
    Serial.println("done.");
    for(;;){};
}


void testscale8()
{
    delay(5000);
    byte r, c;

    Serial.println("scale8:");
    for( r = 0; r <= 240; r += 10) {
        Serial.print(r); Serial.print(" : ");
        for( c = 0; c <= 240; c += 10) {
            byte t;
            t = scale8( r, c);
            Serial.print(t); Serial.print(' ');
        }
        Serial.println(' ');
    }

    Serial.println(' ');
    Serial.println("scale8_video:");

    for( r = 0; r <= 100; r += 4) {
        Serial.print(r); Serial.print(" : ");
        for( c = 0; c <= 100; c += 4) {
            byte t;
            t = scale8_video( r, c);
            Serial.print(t); Serial.print(' ');
        }
        Serial.println(' ');
    }

    Serial.println("done.");
    for(;;){};
}



void testqadd8()
{
    delay(5000);
    byte r, c;
    for( r = 0; r <= 240; r += 10) {
        Serial.print(r); Serial.print(" : ");
        for( c = 0; c <= 240; c += 10) {
            byte t;
            t = qadd8( r, c);
            Serial.print(t); Serial.print(' ');
        }
        Serial.println(' ');
    }
    Serial.println("done.");
    for(;;){};
}

void testnscale8x3()
{
    delay(5000);
    byte r, g, b, sc;
    for( byte z = 0; z < 10; z++) {
        r = random8(); g = random8(); b = random8(); sc = random8();

        Serial.print("nscale8x3_video( ");
        Serial.print(r); Serial.print(", ");
        Serial.print(g); Serial.print(", ");
        Serial.print(b); Serial.print(", ");
        Serial.print(sc); Serial.print(") = [ ");

        nscale8x3_video( r, g, b, sc);

        Serial.print(r); Serial.print(", ");
        Serial.print(g); Serial.print(", ");
        Serial.print(b); Serial.print("]");

        Serial.println(' ');
    }
    Serial.println("done.");
    for(;;){};
}

#endif
