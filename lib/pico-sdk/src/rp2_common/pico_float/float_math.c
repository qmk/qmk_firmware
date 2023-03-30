/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/float.h"

// opened a separate issue https://github.com/raspberrypi/pico-sdk/issues/166 to deal with these warnings if at all
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wconversion\"")
_Pragma("GCC diagnostic ignored \"-Wsign-conversion\"")

typedef uint32_t ui32;
typedef int32_t i32;

#define FPINF ( HUGE_VALF)
#define FMINF (-HUGE_VALF)
#define NANF ((float)NAN)
#define PZERO (+0.0)
#define MZERO (-0.0)

#define PI       3.14159265358979323846
#define LOG2     0.69314718055994530941
// Unfortunately in double precision ln(10) is very close to half-way between to representable numbers
#define LOG10    2.30258509299404568401
#define LOG2E    1.44269504088896340737
#define LOG10E   0.43429448190325182765
#define ONETHIRD 0.33333333333333333333

#define PIf       3.14159265358979323846f
#define LOG2f     0.69314718055994530941f
#define LOG2Ef    1.44269504088896340737f
#define LOG10Ef   0.43429448190325182765f
#define ONETHIRDf 0.33333333333333333333f

#define FUNPACK(x,e,m) e=((x)>>23)&0xff,m=((x)&0x007fffff)|0x00800000
#define FUNPACKS(x,s,e,m) s=((x)>>31),FUNPACK((x),(e),(m))

typedef union {
    float f;
    ui32 ix;
} float_ui32;

static inline float ui322float(ui32 ix) {
    float_ui32 tmp;
    tmp.ix = ix;
    return tmp.f;
}

static inline ui32 float2ui32(float f) {
    float_ui32 tmp;
    tmp.f = f;
    return tmp.ix;
}

static inline bool fisnan(float x) {
    ui32 ix=float2ui32(x);
    return ix * 2 > 0xff000000u;
}

#if PICO_FLOAT_PROPAGATE_NANS
#define check_nan_f1(x) if (fisnan((x))) return (x)
#define check_nan_f2(x,y) if (fisnan((x))) return (x); else if (fisnan((y))) return (y);
#else
#define check_nan_f1(x) ((void)0)
#define check_nan_f2(x,y) ((void)0)
#endif

static inline int fgetsignexp(float x) {
    ui32 ix=float2ui32(x);
    return (ix>>23)&0x1ff;
}

static inline int fgetexp(float x) {
    ui32 ix=float2ui32(x);
    return (ix>>23)&0xff;
}

static inline float fldexp(float x,int de) {
    ui32 ix=float2ui32(x),iy;
    int e;
    e=fgetexp(x);
    if(e==0||e==0xff) return x;
    e+=de;
    if(e<=0) iy=ix&0x80000000; // signed zero for underflow
    else if(e>=0xff) iy=(ix&0x80000000)|0x7f800000ULL; // signed infinity on overflow
    else iy=ix+((ui32)de<<23);
    return ui322float(iy);
}

float WRAPPER_FUNC(ldexpf)(float x, int de) {
    check_nan_f1(x);
    return fldexp(x, de);
}

static inline float fcopysign(float x,float y) {
    ui32 ix=float2ui32(x),iy=float2ui32(y);
    ix=((ix&0x7fffffff)|(iy&0x80000000));
    return ui322float(ix);
}

float WRAPPER_FUNC(copysignf)(float x, float y) {
    check_nan_f2(x,y);
    return fcopysign(x, y);
}

static inline int fiszero(float x)  { return fgetexp    (x)==0; }
static inline int fispzero(float x) { return fgetsignexp(x)==0; }
static inline int fismzero(float x) { return fgetsignexp(x)==0x100; }
static inline int fisinf(float x)   { return fgetexp    (x)==0xff; }
static inline int fispinf(float x)  { return fgetsignexp(x)==0xff; }
static inline int fisminf(float x)  { return fgetsignexp(x)==0x1ff; }

static inline int fisint(float x) {
    ui32 ix=float2ui32(x),m;
    int e=fgetexp(x);
    if(e==0) return 1;       // 0 is an integer
    e-=0x7f;                 // remove exponent bias
    if(e<0) return 0;        // |x|<1
    e=23-e;                  // bit position in mantissa with significance 1
    if(e<=0) return 1;       // |x| large, so must be an integer
    m=(1<<e)-1;              // mask for bits of significance <1
    if(ix&m) return 0;       // not an integer
    return 1;
}

static inline int fisoddint(float x) {
    ui32 ix=float2ui32(x),m;
    int e=fgetexp(x);
    e-=0x7f;                 // remove exponent bias
    if(e<0) return 0;        // |x|<1; 0 is not odd
    e=23-e;                  // bit position in mantissa with significance 1
    if(e<0) return 0;        // |x| large, so must be even
    m=(1<<e)-1;              // mask for bits of significance <1 (if any)
    if(ix&m) return 0;       // not an integer
    if(e==23) return 1;      // value is exactly 1
    return (ix>>e)&1;
}

static inline int fisstrictneg(float x) {
    ui32 ix=float2ui32(x);
    if(fiszero(x)) return 0;
    return ix>>31;
}

static inline int fisneg(float x) {
    ui32 ix=float2ui32(x);
    return ix>>31;
}

static inline float fneg(float x) {
    ui32 ix=float2ui32(x);
    ix^=0x80000000;
    return ui322float(ix);
}

static inline int fispo2(float x) {
    ui32 ix=float2ui32(x);
    if(fiszero(x)) return 0;
    if(fisinf(x)) return 0;
    ix&=0x007fffff;
    return ix==0;
}

static inline float fnan_or(float x) {
#if PICO_FLOAT_PROPAGATE_NANS
    return NANF;
#else
    return x;
#endif
}

float WRAPPER_FUNC(truncf)(float x) {
    check_nan_f1(x);
    ui32 ix=float2ui32(x),m;
    int e=fgetexp(x);
    e-=0x7f;                 // remove exponent bias
    if(e<0) {                // |x|<1
        ix&=0x80000000;
        return ui322float(ix);
    }
    e=23-e;                  // bit position in mantissa with significance 1
    if(e<=0) return x;       // |x| large, so must be an integer
    m=(1<<e)-1;              // mask for bits of significance <1
    ix&=~m;
    return ui322float(ix);
}

float WRAPPER_FUNC(roundf)(float x) {
    check_nan_f1(x);
    ui32 ix=float2ui32(x),m;
    int e=fgetexp(x);
    e-=0x7f;                 // remove exponent bias
    if(e<-1) {               // |x|<0.5
        ix&=0x80000000;
        return ui322float(ix);
    }
    if(e==-1) {              // 0.5<=|x|<1
        ix&=0x80000000;
        ix|=0x3f800000;        // ±1
        return ui322float(ix);
    }
    e=23-e;                  // bit position in mantissa with significance 1, <=23
    if(e<=0) return x;       // |x| large, so must be an integer
    m=1<<(e-1);              // mask for bit of significance 0.5
    ix+=m;
    m=m+m-1;                 // mask for bits of significance <1
    ix&=~m;
    return ui322float(ix);
}

float WRAPPER_FUNC(floorf)(float x) {
    check_nan_f1(x);
    ui32 ix=float2ui32(x),m;
    int e=fgetexp(x);
    if(e==0) {       // x==0
        ix&=0x80000000;
        return ui322float(ix);
    }
    e-=0x7f;                 // remove exponent bias
    if(e<0) {                // |x|<1, not zero
        if(fisneg(x)) return -1;
        return PZERO;
    }
    e=23-e;                  // bit position in mantissa with significance 1
    if(e<=0) return x;       // |x| large, so must be an integer
    m=(1<<e)-1;              // mask for bit of significance <1
    if(fisneg(x)) ix+=m;     // add 1-ε to magnitude if negative
    ix&=~m;                  // truncate
    return ui322float(ix);
}

float WRAPPER_FUNC(ceilf)(float x) {
    check_nan_f1(x);
    ui32 ix=float2ui32(x),m;
    int e=fgetexp(x);
    if(e==0) {       // x==0
        ix&=0x80000000;
        return ui322float(ix);
    }
    e-=0x7f;                 // remove exponent bias
    if(e<0) {                // |x|<1, not zero
        if(fisneg(x)) return MZERO;
        return 1;
    }
    e=23-e;                  // bit position in mantissa with significance 1
    if(e<=0) return x;       // |x| large, so must be an integer
    m=(1<<e)-1;              // mask for bit of significance <1
    if(!fisneg(x)) ix+=m;    // add 1-ε to magnitude if positive
    ix&=~m;                  // truncate
    return ui322float(ix);
}

float WRAPPER_FUNC(asinf)(float x) {
    check_nan_f1(x);
    float u;
    u=(1.0f-x)*(1.0f+x);
    if(fisstrictneg(u)) return fnan_or(FPINF);
    return atan2f(x,sqrtf(u));
}

float WRAPPER_FUNC(acosf)(float x) {
    check_nan_f1(x);
    float u;
    u=(1.0f-x)*(1.0f+x);
    if(fisstrictneg(u)) return fnan_or(FPINF);
    return atan2f(sqrtf(u),x);
}

float WRAPPER_FUNC(atanf)(float x) {
    check_nan_f1(x);
    if(fispinf(x)) return (float)( PIf/2);
    if(fisminf(x)) return (float)(-PIf/2);
    return atan2f(x,1.0f);
}

float WRAPPER_FUNC(sinhf)(float x) {
    check_nan_f1(x);
    return fldexp((expf(x)-expf(fneg(x))),-1);
}

float WRAPPER_FUNC(coshf)(float x) {
    check_nan_f1(x);
    return fldexp((expf(x)+expf(fneg(x))),-1);
}

float WRAPPER_FUNC(tanhf)(float x) {
    check_nan_f1(x);
    float u;
    int e;
    e=fgetexp(x);
    if(e>=4+0x7f) {             // |x|>=16?
        if(!fisneg(x)) return  1;  // 1 << exp 2x; avoid generating infinities later
        else           return -1;  // 1 >> exp 2x
    }
    u=expf(fldexp(x,1));
    return (u-1.0f)/(u+1.0f);
}

float WRAPPER_FUNC(asinhf)(float x) {
    check_nan_f1(x);
    int e;
    e=fgetexp(x);
    if(e>=16+0x7f) {                                   // |x|>=2^16?
        if(!fisneg(x)) return      logf(     x )+LOG2f;  // 1/x^2 << 1
        else           return fneg(logf(fneg(x))+LOG2f); // 1/x^2 << 1
    }
    if(x>0) return      (float)log(sqrt((double)x*(double)x+1.0)+(double)x);
    else    return fneg((float)log(sqrt((double)x*(double)x+1.0)-(double)x));
}

float WRAPPER_FUNC(acoshf)(float x) {
    check_nan_f1(x);
    int e;
    if(fisneg(x)) x=fneg(x);
    e=fgetexp(x);
    if(e>=16+0x7f) return logf(x)+LOG2f;           // |x|>=2^16?
    return (float)log(sqrt(((double)x+1.0)*((double)x-1.0))+(double)x);
}

float WRAPPER_FUNC(atanhf)(float x) {
    check_nan_f1(x);
    return fldexp(logf((1.0f+x)/(1.0f-x)),-1);
}

float WRAPPER_FUNC(exp2f)(float x) { check_nan_f1(x); return (float)exp((double)x*LOG2); }
float WRAPPER_FUNC(log2f)(float x) { check_nan_f1(x); return logf(x)*LOG2Ef;  }
float WRAPPER_FUNC(exp10f)(float x) { check_nan_f1(x); return (float)exp((double)x*LOG10); }
float WRAPPER_FUNC(log10f)(float x) { check_nan_f1(x); return logf(x)*LOG10Ef; }

float WRAPPER_FUNC(expm1f)(float x) { check_nan_f1(x); return (float)(exp((double)x)-1); }
float WRAPPER_FUNC(log1pf)(float x) { check_nan_f1(x); return (float)(log(1+(double)x)); }
float WRAPPER_FUNC(fmaf)(float x,float y,float z) {
    check_nan_f2(x,y);
    check_nan_f1(z);
    return (float)((double)x*(double)y+(double)z);
} // has double rounding so not exact

// general power, x>0
static inline float fpow_1(float x,float y) {
    return (float)exp(log((double)x)*(double)y); // using double-precision intermediates for better accuracy
}

static float fpow_int2(float x,int y) {
    float u;
    if(y==1) return x;
    u=fpow_int2(x,y/2);
    u*=u;
    if(y&1) u*=x;
    return u;
}

// for the case where x not zero or infinity, y small and not zero
static inline float fpowint_1(float x,int y) {
    if(y<0) x=1.0f/x,y=-y;
    return fpow_int2(x,y);
}

// for the case where x not zero or infinity
static float fpowint_0(float x,int y) {
    int e;
    if(fisneg(x)) {
        if(fisoddint(y)) return fneg(fpowint_0(fneg(x),y));
        else             return      fpowint_0(fneg(x),y);
    }
    if(fispo2(x)) {
        e=fgetexp(x)-0x7f;
        if(y>=256) y= 255;  // avoid overflow
        if(y<-256) y=-256;
        y*=e;
        return fldexp(1,y);
    }
    if(y==0) return 1;
    if(y>=-32&&y<=32) return fpowint_1(x,y);
    return fpow_1(x,y);
}

float WRAPPER_FUNC(powintf)(float x,int y) {
    _Pragma("GCC diagnostic push")
    _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"")
    if(x==1.0f||y==0) return 1;
    if(x==0.0f) {
        if(y>0) {
            if(y&1) return x;
            else    return 0;
        }
        if((y&1)) return fcopysign(FPINF,x);
        return FPINF;
    }
    _Pragma("GCC diagnostic pop")
    check_nan_f1(x);
    if(fispinf(x)) {
        if(y<0) return 0;
        else    return FPINF;
    }
    if(fisminf(x)) {
        if(y>0) {
            if((y&1)) return FMINF;
            else      return FPINF;
        }
        if((y&1)) return MZERO;
        else      return PZERO;
    }
    return fpowint_0(x,y);
}

// for the case where y is guaranteed a finite integer, x not zero or infinity
static float fpow_0(float x,float y) {
    int e,p;
    if(fisneg(x)) {
        if(fisoddint(y)) return fneg(fpow_0(fneg(x),y));
        else             return      fpow_0(fneg(x),y);
    }
    p=(int)y;
    if(fispo2(x)) {
        e=fgetexp(x)-0x7f;
        if(p>=256) p= 255;  // avoid overflow
        if(p<-256) p=-256;
        p*=e;
        return fldexp(1,p);
    }
    if(p==0) return 1;
    if(p>=-32&&p<=32) return fpowint_1(x,p);
    return fpow_1(x,y);
}

float WRAPPER_FUNC(powf)(float x,float y) {
    _Pragma("GCC diagnostic push")
    _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"")
    if(x==1.0f||fiszero(y)) return 1;
    check_nan_f2(x,y);
    if(x==-1.0f&&fisinf(y)) return 1;
    _Pragma("GCC diagnostic pop")
    if(fiszero(x)) {
        if(!fisneg(y)) {
            if(fisoddint(y)) return x;
            else             return 0;
        }
        if(fisoddint(y)) return fcopysign(FPINF,x);
        return FPINF;
    }
    if(fispinf(x)) {
        if(fisneg(y)) return 0;
        else          return FPINF;
    }
    if(fisminf(x)) {
        if(!fisneg(y)) {
            if(fisoddint(y)) return FMINF;
            else             return FPINF;
        }
        if(fisoddint(y)) return MZERO;
        else             return PZERO;
    }
    if(fispinf(y)) {
        if(fgetexp(x)<0x7f) return PZERO;
        else                return FPINF;
    }
    if(fisminf(y)) {
        if(fgetexp(x)<0x7f) return FPINF;
        else                return PZERO;
    }
    if(fisint(y)) return fpow_0(x,y);
    if(fisneg(x)) return FPINF;
    return fpow_1(x,y);
}

float WRAPPER_FUNC(hypotf)(float x,float y) {
    check_nan_f2(x,y);
    int ex,ey;
    ex=fgetexp(x); ey=fgetexp(y);
    if(ex>=0x7f+50||ey>=0x7f+50) { // overflow, or nearly so
        x=fldexp(x,-70),y=fldexp(y,-70);
        return fldexp(sqrtf(x*x+y*y), 70);
    }
    else if(ex<=0x7f-50&&ey<=0x7f-50) { // underflow, or nearly so
        x=fldexp(x, 70),y=fldexp(y, 70);
        return fldexp(sqrtf(x*x+y*y),-70);
    }
    return sqrtf(x*x+y*y);
}

float WRAPPER_FUNC(cbrtf)(float x) {
    check_nan_f1(x);
    int e;
    if(fisneg(x)) return fneg(cbrtf(fneg(x)));
    if(fiszero(x)) return fcopysign(PZERO,x);
    e=fgetexp(x)-0x7f;
    e=(e*0x5555+0x8000)>>16;  // ~e/3, rounded
    x=fldexp(x,-e*3);
    x=expf(logf(x)*ONETHIRDf);
    return fldexp(x,e);
}

// reduces mx*2^e modulo my, returning bottom bits of quotient at *pquo
// 2^23<=|mx|,my<2^24, e>=0; 0<=result<my
static i32 frem_0(i32 mx,i32 my,int e,int*pquo) {
    int quo=0,q,r=0,s;
    if(e>0) {
        r=0xffffffffU/(ui32)(my>>7);  // reciprocal estimate Q16
    }
    while(e>0) {
        s=e; if(s>12) s=12;    // gain up to 12 bits on each iteration
        q=(mx>>9)*r;           // Q30
        q=((q>>(29-s))+1)>>1;  // Q(s), rounded
        mx=(mx<<s)-my*q;
        quo=(quo<<s)+q;
        e-=s;
    }
    if(mx>=my) mx-=my,quo++; // when e==0 mx can be nearly as big as 2my
    if(mx>=my) mx-=my,quo++;
    if(mx<0) mx+=my,quo--;
    if(mx<0) mx+=my,quo--;
    if(pquo) *pquo=quo;
    return mx;
}

float WRAPPER_FUNC(fmodf)(float x,float y) {
    check_nan_f2(x,y);
    ui32 ix=float2ui32(x),iy=float2ui32(y);
    int sx,ex,ey;
    i32 mx,my;
    FUNPACKS(ix,sx,ex,mx);
    FUNPACK(iy,ey,my);
    if(ex==0xff) {
        return fnan_or(FPINF);
    }
    if(ey==0) return FPINF;
    if(ex==0) {
        if(!fisneg(x)) return PZERO;
        return MZERO;
    }
    if(ex<ey) return x;  // |x|<|y|, including case x=±0
    mx=frem_0(mx,my,ex-ey,0);
    if(sx) mx=-mx;
    return fix2float(mx,0x7f-ey+23);
}

float WRAPPER_FUNC(remquof)(float x,float y,int*quo) {
    check_nan_f2(x,y);
    ui32 ix=float2ui32(x),iy=float2ui32(y);
    int sx,sy,ex,ey,q;
    i32 mx,my;
    FUNPACKS(ix,sx,ex,mx);
    FUNPACKS(iy,sy,ey,my);
    if(quo) *quo=0;
    if(ex==0xff) return FPINF;
    if(ey==0)    return FPINF;
    if(ex==0)    return PZERO;
    if(ey==0xff) return x;
    if(ex<ey-1)  return x;  // |x|<|y|/2
    if(ex==ey-1) {
        if(mx<=my) return x;  // |x|<=|y|/2, even quotient
        // here |y|/2<|x|<|y|
        if(!sx) { // x>|y|/2
            mx-=my+my;
            ey--;
            q=1;
        } else { // x<-|y|/2
            mx=my+my-mx;
            ey--;
            q=-1;
        }
    }
    else {
        if(sx) mx=-mx;
        mx=frem_0(mx,my,ex-ey,&q);
        if(mx+mx>my || (mx+mx==my&&(q&1)) ) { // |x|>|y|/2, or equality and an odd quotient?
            mx-=my;
            q++;
        }
    }
    if(sy) q=-q;
    if(quo) *quo=q;
    return fix2float(mx,0x7f-ey+23);
}

float WRAPPER_FUNC(dremf)(float x,float y) { check_nan_f2(x,y); return remquof(x,y,0); }

float WRAPPER_FUNC(remainderf)(float x,float y) { check_nan_f2(x,y); return remquof(x,y,0); }

_Pragma("GCC diagnostic pop") // conversion