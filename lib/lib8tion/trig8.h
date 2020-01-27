#ifndef __INC_LIB8TION_TRIG_H
#define __INC_LIB8TION_TRIG_H

///@ingroup lib8tion

///@defgroup Trig Fast trig functions
/// Fast 8 and 16-bit approximations of sin(x) and cos(x).
///        Don't use these approximations for calculating the
///        trajectory of a rocket to Mars, but they're great
///        for art projects and LED displays.
///
///        On Arduino/AVR, the 16-bit approximation is more than
///        10X faster than floating point sin(x) and cos(x), while
/// the 8-bit approximation is more than 20X faster.
///@{

#if defined(__AVR__)
#define sin16 sin16_avr
#else
#define sin16 sin16_C
#endif

/// Fast 16-bit approximation of sin(x). This approximation never varies more than
/// 0.69% from the floating point value you'd get by doing
///
///     float s = sin(x) * 32767.0;
///
/// @param theta input angle from 0-65535
/// @returns sin of theta, value between -32767 to 32767.
LIB8STATIC int16_t sin16_avr( uint16_t theta )
{
    static const uint8_t data[] =
    { 0,         0,         49, 0, 6393%256,   6393/256, 48, 0,
      12539%256, 12539/256, 44, 0, 18204%256, 18204/256, 38, 0,
      23170%256, 23170/256, 31, 0, 27245%256, 27245/256, 23, 0,
      30273%256, 30273/256, 14, 0, 32137%256, 32137/256,  4 /*,0*/ };

    uint16_t offset = (theta & 0x3FFF);

    // AVR doesn't have a multi-bit shift instruction,
    // so if we say "offset >>= 3", gcc makes a tiny loop.
    // Inserting empty volatile statements between each
    // bit shift forces gcc to unroll the loop.
    offset >>= 1; // 0..8191
    asm volatile("");
    offset >>= 1; // 0..4095
    asm volatile("");
    offset >>= 1; // 0..2047

    if( theta & 0x4000 ) offset = 2047 - offset;

    uint8_t sectionX4;
    sectionX4 = offset / 256;
    sectionX4 *= 4;

    uint8_t m;

    union {
        uint16_t b;
        struct {
            uint8_t blo;
            uint8_t bhi;
        };
    } u;

    //in effect u.b = blo + (256 * bhi);
    u.blo = data[ sectionX4 ];
    u.bhi = data[ sectionX4 + 1];
    m     = data[ sectionX4 + 2];

    uint8_t secoffset8 = (uint8_t)(offset) / 2;

    uint16_t mx = m * secoffset8;

    int16_t  y  = mx + u.b;
    if( theta & 0x8000 ) y = -y;

    return y;
}

/// Fast 16-bit approximation of sin(x). This approximation never varies more than
/// 0.69% from the floating point value you'd get by doing
///
///     float s = sin(x) * 32767.0;
///
/// @param theta input angle from 0-65535
/// @returns sin of theta, value between -32767 to 32767.
LIB8STATIC int16_t sin16_C( uint16_t theta )
{
    static const uint16_t base[] =
    { 0, 6393, 12539, 18204, 23170, 27245, 30273, 32137 };
    static const uint8_t slope[] =
    { 49, 48, 44, 38, 31, 23, 14, 4 };

    uint16_t offset = (theta & 0x3FFF) >> 3; // 0..2047
    if( theta & 0x4000 ) offset = 2047 - offset;

    uint8_t section = offset / 256; // 0..7
    uint16_t b   = base[section];
    uint8_t  m   = slope[section];

    uint8_t secoffset8 = (uint8_t)(offset) / 2;

    uint16_t mx = m * secoffset8;
    int16_t  y  = mx + b;

    if( theta & 0x8000 ) y = -y;

    return y;
}


/// Fast 16-bit approximation of cos(x). This approximation never varies more than
/// 0.69% from the floating point value you'd get by doing
///
///     float s = cos(x) * 32767.0;
///
/// @param theta input angle from 0-65535
/// @returns sin of theta, value between -32767 to 32767.
LIB8STATIC int16_t cos16( uint16_t theta)
{
    return sin16( theta + 16384);
}

///////////////////////////////////////////////////////////////////////

// sin8 & cos8
//        Fast 8-bit approximations of sin(x) & cos(x).
//        Input angle is an unsigned int from 0-255.
//        Output is an unsigned int from 0 to 255.
//
//        This approximation can vary to to 2%
//        from the floating point value you'd get by doing
//          float s = (sin( x ) * 128.0) + 128;
//
//        Don't use this approximation for calculating the
//        "real" trigonometric calculations, but it's great
//        for art projects and LED displays.
//
//        On Arduino/AVR, this approximation is more than
//        20X faster than floating point sin(x) and cos(x)

#if defined(__AVR__) && !defined(LIB8_ATTINY)
#define sin8 sin8_avr
#else
#define sin8 sin8_C
#endif


static const uint8_t b_m16_interleave[8] = { 0, 49, 49, 41, 90, 27, 117, 10 };

/// Fast 8-bit approximation of sin(x). This approximation never varies more than
/// 2% from the floating point value you'd get by doing
///
///     float s = (sin(x) * 128.0) + 128;
///
/// @param theta input angle from 0-255
/// @returns sin of theta, value between 0 and 255
LIB8STATIC uint8_t  sin8_avr( uint8_t theta)
{
    uint8_t offset = theta;

    asm volatile(
                 "sbrc %[theta],6         \n\t"
                 "com  %[offset]           \n\t"
                 : [theta] "+r" (theta), [offset] "+r" (offset)
                 );

    offset &= 0x3F; // 0..63

    uint8_t secoffset  = offset & 0x0F; // 0..15
    if( theta & 0x40) secoffset++;

    uint8_t m16; uint8_t b;

    uint8_t section = offset >> 4; // 0..3
    uint8_t s2 = section * 2;

    const uint8_t* p = b_m16_interleave;
    p += s2;
    b   = *p;
    p++;
    m16 = *p;

    uint8_t mx;
    uint8_t xr1;
    asm volatile(
                 "mul %[m16],%[secoffset]   \n\t"
                 "mov %[mx],r0              \n\t"
                 "mov %[xr1],r1             \n\t"
                 "eor  r1, r1               \n\t"
                 "swap %[mx]                \n\t"
                 "andi %[mx],0x0F           \n\t"
                 "swap %[xr1]               \n\t"
                 "andi %[xr1], 0xF0         \n\t"
                 "or   %[mx], %[xr1]        \n\t"
                 : [mx] "=d" (mx), [xr1] "=d" (xr1)
                 : [m16] "d" (m16), [secoffset] "d" (secoffset)
                 );

    int8_t y = mx + b;
    if( theta & 0x80 ) y = -y;

    y += 128;

    return y;
}


/// Fast 8-bit approximation of sin(x). This approximation never varies more than
/// 2% from the floating point value you'd get by doing
///
///     float s = (sin(x) * 128.0) + 128;
///
/// @param theta input angle from 0-255
/// @returns sin of theta, value between 0 and 255
LIB8STATIC uint8_t sin8_C( uint8_t theta)
{
    uint8_t offset = theta;
    if( theta & 0x40 ) {
        offset = (uint8_t)255 - offset;
    }
    offset &= 0x3F; // 0..63

    uint8_t secoffset  = offset & 0x0F; // 0..15
    if( theta & 0x40) secoffset++;

    uint8_t section = offset >> 4; // 0..3
    uint8_t s2 = section * 2;
    const uint8_t* p = b_m16_interleave;
    p += s2;
    uint8_t b   =  *p;
    p++;
    uint8_t m16 =  *p;

    uint8_t mx = (m16 * secoffset) >> 4;

    int8_t y = mx + b;
    if( theta & 0x80 ) y = -y;

    y += 128;

    return y;
}

/// Fast 8-bit approximation of cos(x). This approximation never varies more than
/// 2% from the floating point value you'd get by doing
///
///     float s = (cos(x) * 128.0) + 128;
///
/// @param theta input angle from 0-255
/// @returns sin of theta, value between 0 and 255
LIB8STATIC uint8_t cos8( uint8_t theta)
{
    return sin8( theta + 64);
}

/// Fast 16-bit approximation of atan2(x).
/// @returns atan2, value between 0 and 255
LIB8STATIC uint8_t atan2_8(int16_t dy, int16_t dx)
{
    if (dy == 0)
    {
        if (dx >= 0)
            return 0;
        else
            return 128;
    }

    int16_t abs_y = dy > 0 ? dy : -dy;
    int8_t a;

    if (dx >= 0)
        a = 32 - (32 * (dx - abs_y) / (dx + abs_y));
    else
        a = 96 - (32 * (dx + abs_y) / (abs_y - dx));

    if (dy < 0)
        return -a;     // negate if in quad III or IV
    return a;
}

///@}
#endif
