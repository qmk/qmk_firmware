/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <math.h>
#include "pico/double.h"

// opened a separate issue https://github.com/raspberrypi/pico-sdk/issues/166 to deal with these warnings if at all
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wconversion\"")
_Pragma("GCC diagnostic ignored \"-Wsign-conversion\"")

typedef uint64_t ui64;
typedef uint32_t ui32;
typedef int64_t i64;

#define PINF ( HUGE_VAL)
#define MINF (-HUGE_VAL)
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

#define DUNPACK(x,e,m) e=((x)>>52)&0x7ff,m=((x)&0x000fffffffffffffULL)|0x0010000000000000ULL
#define DUNPACKS(x,s,e,m) s=((x)>>63),DUNPACK((x),(e),(m))

typedef union {
    double d;
    ui64 ix;
} double_ui64;

static inline double ui642double(ui64 ix) {
    double_ui64 tmp;
    tmp.ix = ix;
    return tmp.d;
}

static inline ui64 double2ui64(double d) {
    double_ui64 tmp;
    tmp.d = d;
    return tmp.ix;
}

static inline bool disnan(double x) {
    ui64 ix= double2ui64(x);
    // checks the top bit of the low 32 bit of the NAN, but it I think that is ok
    return ((uint32_t)(ix >> 31)) > 0xffe00000u;
}

#if PICO_DOUBLE_PROPAGATE_NANS
#define check_nan_d1(x) if (disnan((x))) return (x)
#define check_nan_d2(x,y) if (disnan((x))) return (x); else if (disnan((y))) return (y);
#else
#define check_nan_d1(x) ((void)0)
#define check_nan_d2(x,y) ((void)0)
#endif

static inline int dgetsignexp(double x) {
    ui64 ix=double2ui64(x);
    return (ix>>52)&0xfff;
}

static inline int dgetexp(double x) {
    ui64 ix=double2ui64(x);
    return (ix>>52)&0x7ff;
}

static inline double dldexp(double x,int de) {
    ui64 ix=double2ui64(x),iy;
    int e;
    e=dgetexp(x);
    if(e==0||e==0x7ff) return x;
    e+=de;
    if(e<=0) iy=ix&0x8000000000000000ULL; // signed zero for underflow
    else if(e>=0x7ff) iy=(ix&0x8000000000000000ULL)|0x7ff0000000000000ULL; // signed infinity on overflow
    else iy=ix+((ui64)de<<52);
    return ui642double(iy);
}

double WRAPPER_FUNC(ldexp)(double x, int de) {
    check_nan_d1(x);
    return dldexp(x, de);
}


static inline double dcopysign(double x,double y) {
    ui64 ix=double2ui64(x),iy=double2ui64(y);
    ix=((ix&0x7fffffffffffffffULL)|(iy&0x8000000000000000ULL));
    return ui642double(ix);
}

double WRAPPER_FUNC(copysign)(double x, double y) {
    check_nan_d2(x,y);
    return dcopysign(x, y);
}
static inline int diszero(double x)  { return dgetexp    (x)==0; }
static inline int dispzero(double x) { return dgetsignexp(x)==0; }
static inline int dismzero(double x) { return dgetsignexp(x)==0x800; }
static inline int disinf(double x)   { return dgetexp    (x)==0x7ff; }
static inline int dispinf(double x)  { return dgetsignexp(x)==0x7ff; }
static inline int disminf(double x)  { return dgetsignexp(x)==0xfff; }

static inline int disint(double x) {
    ui64 ix=double2ui64(x),m;
    int e=dgetexp(x);
    if(e==0) return 1;       // 0 is an integer
    e-=0x3ff;                // remove exponent bias
    if(e<0) return 0;        // |x|<1
    e=52-e;                  // bit position in mantissa with significance 1
    if(e<=0) return 1;       // |x| large, so must be an integer
    m=(1ULL<<e)-1;           // mask for bits of significance <1
    if(ix&m) return 0;       // not an integer
    return 1;
}

static inline int disoddint(double x) {
    ui64 ix=double2ui64(x),m;
    int e=dgetexp(x);
    e-=0x3ff;                // remove exponent bias
    if(e<0) return 0;        // |x|<1; 0 is not odd
    e=52-e;                  // bit position in mantissa with significance 1
    if(e<0) return 0;        // |x| large, so must be even
    m=(1ULL<<e)-1;           // mask for bits of significance <1 (if any)
    if(ix&m) return 0;       // not an integer
    if(e==52) return 1;      // value is exactly 1
    return (ix>>e)&1;
}

static inline int disstrictneg(double x) {
    ui64 ix=double2ui64(x);
    if(diszero(x)) return 0;
    return ix>>63;
}

static inline int disneg(double x) {
    ui64 ix=double2ui64(x);
    return ix>>63;
}

static inline double dneg(double x) {
    ui64 ix=double2ui64(x);
    ix^=0x8000000000000000ULL;
    return ui642double(ix);
}

static inline int dispo2(double x) {
    ui64 ix=double2ui64(x);
    if(diszero(x)) return 0;
    if(disinf(x)) return 0;
    ix&=0x000fffffffffffffULL;
    return ix==0;
}

static inline double dnan_or(double x) {
#if PICO_DOUBLE_PROPAGATE_NANS
    return NAN;
#else
    return x;
#endif
}

double WRAPPER_FUNC(trunc)(double x) {
    check_nan_d1(x);
    ui64 ix=double2ui64(x),m;
    int e=dgetexp(x);
    e-=0x3ff;                // remove exponent bias
    if(e<0) {                // |x|<1
        ix&=0x8000000000000000ULL;
        return ui642double(ix);
    }
    e=52-e;                  // bit position in mantissa with significance 1
    if(e<=0) return x;       // |x| large, so must be an integer
    m=(1ULL<<e)-1;           // mask for bits of significance <1
    ix&=~m;
    return ui642double(ix);
}

double WRAPPER_FUNC(round)(double x) {
    check_nan_d1(x);
    ui64 ix=double2ui64(x),m;
    int e=dgetexp(x);
    e-=0x3ff;                // remove exponent bias
    if(e<-1) {               // |x|<0.5
        ix&=0x8000000000000000ULL;
        return ui642double(ix);
    }
    if(e==-1) {              // 0.5<=|x|<1
        ix&=0x8000000000000000ULL;
        ix|=0x3ff0000000000000ULL;        // ±1
        return ui642double(ix);
    }
    e=52-e;                  // bit position in mantissa with significance 1, <=52
    if(e<=0) return x;       // |x| large, so must be an integer
    m=1ULL<<(e-1);           // mask for bit of significance 0.5
    ix+=m;
    m=m+m-1;                 // mask for bits of significance <1
    ix&=~m;
    return ui642double(ix);
}

double WRAPPER_FUNC(floor)(double x) {
    check_nan_d1(x);
    ui64 ix=double2ui64(x),m;
    int e=dgetexp(x);
    if(e==0) {               // x==0
        ix&=0x8000000000000000ULL;
        return ui642double(ix);
    }
    e-=0x3ff;                // remove exponent bias
    if(e<0) {                // |x|<1, not zero
        if(disneg(x)) return -1;
        return PZERO;
    }
    e=52-e;                  // bit position in mantissa with significance 1
    if(e<=0) return x;       // |x| large, so must be an integer
    m=(1ULL<<e)-1;           // mask for bit of significance <1
    if(disneg(x)) ix+=m;     // add 1-ε to magnitude if negative
    ix&=~m;                  // truncate
    return ui642double(ix);
}

double WRAPPER_FUNC(ceil)(double x) {
    check_nan_d1(x);
    ui64 ix=double2ui64(x),m;
    int e=dgetexp(x);
    if(e==0) {               // x==0
        ix&=0x8000000000000000ULL;
        return ui642double(ix);
    }
    e-=0x3ff;                 // remove exponent bias
    if(e<0) {                // |x|<1, not zero
        if(disneg(x)) return MZERO;
        return 1;
    }
    e=52-e;                  // bit position in mantissa with significance 1
    if(e<=0) return x;       // |x| large, so must be an integer
    m=(1ULL<<e)-1;           // mask for bit of significance <1
    if(!disneg(x)) ix+=m;    // add 1-ε to magnitude if positive
    ix&=~m;                  // truncate
    return ui642double(ix);
}

double WRAPPER_FUNC(asin)(double x) {
    check_nan_d1(x);
    double u;
    u=(1-x)*(1+x);
    if(disstrictneg(u)) return dnan_or(PINF);
    return atan2(x,sqrt(u));
}

double WRAPPER_FUNC(acos)(double x) {
    check_nan_d1(x);
    double u;
    u=(1-x)*(1+x);
    if(disstrictneg(u)) return dnan_or(PINF);
    return atan2(sqrt(u),x);
}

double WRAPPER_FUNC(atan)(double x) {
    check_nan_d1(x);
    if(dispinf(x)) return  PI/2;
    if(disminf(x)) return -PI/2;
    return atan2(x,1);
}

double WRAPPER_FUNC(sinh)(double x) {
    check_nan_d1(x);
    return dldexp((exp(x)-exp(dneg(x))),-1);
}

double WRAPPER_FUNC(cosh)(double x) {
    check_nan_d1(x);
    return dldexp((exp(x)+exp(dneg(x))),-1);
}

double WRAPPER_FUNC(tanh)(double x) {
    check_nan_d1(x);
    double u;
    int e;
    e=dgetexp(x);
    if(e>=5+0x3ff) {             // |x|>=32?
        if(!disneg(x)) return  1;  // 1 << exp 2x; avoid generating infinities later
        else           return -1;  // 1 >> exp 2x
    }
    u=exp(dldexp(x,1));
    return (u-1)/(u+1);
}

double WRAPPER_FUNC(asinh)(double x) {
    check_nan_d1(x);
    int e;
    e=dgetexp(x);
    if(e>=32+0x3ff) {                                // |x|>=2^32?
        if(!disneg(x)) return      log(     x )+LOG2;  // 1/x^2 << 1
        else           return dneg(log(dneg(x))+LOG2); // 1/x^2 << 1
    }
    if(x>0) return      log(sqrt(x*x+1)+x);
    else    return dneg(log(sqrt(x*x+1)-x));
}

double WRAPPER_FUNC(acosh)(double x) {
    check_nan_d1(x);
    int e;
    if(disneg(x)) x=dneg(x);
    e=dgetexp(x);
    if(e>=32+0x3ff) return log(x)+LOG2;           // |x|>=2^32?
    return log(sqrt((x-1)*(x+1))+x);
}

double WRAPPER_FUNC(atanh)(double x) {
    check_nan_d1(x);
    return dldexp(log((1+x)/(1-x)),-1);
}

double WRAPPER_FUNC(exp2)(double x) {
    check_nan_d1(x);
    int e;
    // extra check for disminf as this catches -Nan, and x<=-4096 doesn't.
    if (disminf(x) || x<=-4096) return 0;    // easily underflows
    else if (x>=4096)           return PINF; // easily overflows
    e=(int)round(x);
    x-=e;
    return dldexp(exp(x*LOG2),e);
}
double WRAPPER_FUNC(log2)(double x) { check_nan_d1(x); return log(x)*LOG2E;  }
double WRAPPER_FUNC(exp10)(double x) { check_nan_d1(x); return pow(10,x); }
double WRAPPER_FUNC(log10)(double x) { check_nan_d1(x); return log(x)*LOG10E; }

// todo these are marked as lofi
double WRAPPER_FUNC(expm1(double x) { check_nan_d1(x); return exp)(x)-1; }
double WRAPPER_FUNC(log1p(double x) { check_nan_d1(x); return log)(1+x); }
double WRAPPER_FUNC(fma)(double x,double y,double z) { check_nan_d1(x); return x*y+z; }

// general power, x>0, finite
static double dpow_1(double x,double y) {
    int a,b,c;
    double t,rt,u,v,v0,v1,w,ry;
    a=dgetexp(x)-0x3ff;
    u=log2(dldexp(x,-a)); // now log_2 x = a+u
    if(u>0.5) u-=1,a++;              // |u|<=~0.5
    if(a==0) return exp2(u*y);
    // here |log_2 x| >~0.5
    if(y>= 4096) { // then easily over/underflows
        if(a<0) return 0;
        return PINF;
    }
    if(y<=-4096) { // then easily over/underflows
        if(a<0) return PINF;
        return 0;
    }
    ry=round(y);
    v=y-ry;
    v0=dldexp(round(ldexp(v,26)),-26);
    v1=v-v0;
    b=(int)ry; // guaranteed to fit in an int; y=b+v0+v1
    // now the result is exp2( (a+u) * (b+v0+v1) )
    c=a*b;      // integer
    t=a*v0;
    rt=round(t);
    c+=(int)rt;
    w=t-rt;
    t=a*v1;
    w+=t;
    t=u*b;
    rt=round(t);
    c+=(int)rt;
    w+=t-rt;
    w+=u*v;
    return dldexp(exp2(w),c);
}

static double dpow_int2(double x,int y) {
    double u;
    if(y==1) return x;
    u=dpow_int2(x,y/2);
    u*=u;
    if(y&1) u*=x;
    return u;
}

// for the case where x not zero or infinity, y small and not zero
static inline double dpowint_1(double x,int y) {
    if(y<0) x=1/x,y=-y;
    return dpow_int2(x,y);
}

// for the case where x not zero or infinity
static double dpowint_0(double x,int y) {
    int e;
    if(disneg(x)) {
        if(disoddint(y)) return dneg(dpowint_0(dneg(x),y));
        else             return      dpowint_0(dneg(x),y);
    }
    if(dispo2(x)) {
        e=dgetexp(x)-0x3ff;
        if(y>=2048) y= 2047;  // avoid overflow
        if(y<-2048) y=-2048;
        y*=e;
        return dldexp(1,y);
    }
    if(y==0) return 1;
    if(y>=-32&&y<=32) return dpowint_1(x,y);
    return dpow_1(x,y);
}

double WRAPPER_FUNC(powint)(double x,int y) {
    _Pragma("GCC diagnostic push")
    _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"")
    if(x==1.0||y==0) return 1;
    _Pragma("GCC diagnostic pop")
    check_nan_d1(x);
    if(diszero(x)) {
        if(y>0) {
            if(y&1) return x;
            else    return 0;
        }
        if((y&1)) return dcopysign(PINF,x);
        return PINF;
    }
    if(dispinf(x)) {
        if(y<0) return 0;
        else    return PINF;
    }
    if(disminf(x)) {
        if(y>0) {
            if((y&1)) return MINF;
            else      return PINF;
        }
        if((y&1)) return MZERO;
        else      return PZERO;
    }
    return dpowint_0(x,y);
}

// for the case where y is guaranteed a finite integer, x not zero or infinity
static double dpow_0(double x,double y) {
    int e,p;
    if(disneg(x)) {
        if(disoddint(y)) return dneg(dpow_0(dneg(x),y));
        else             return      dpow_0(dneg(x),y);
    }
    p=(int)y;
    if(dispo2(x)) {
        e=dgetexp(x)-0x3ff;
        if(p>=2048) p= 2047;  // avoid overflow
        if(p<-2048) p=-2048;
        p*=e;
        return dldexp(1,p);
    }
    if(p==0) return 1;
    if(p>=-32&&p<=32) return dpowint_1(x,p);
    return dpow_1(x,y);
}

double WRAPPER_FUNC(pow)(double x,double y) {
    _Pragma("GCC diagnostic push")
    _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"")

    if(x==1.0||diszero(y)) return 1;
    check_nan_d2(x, y);
    if(x==-1.0&&disinf(y)) return 1;
    _Pragma("GCC diagnostic pop")

    if(diszero(x)) {
        if(!disneg(y)) {
            if(disoddint(y)) return x;
            else             return 0;
        }
        if(disoddint(y)) return dcopysign(PINF,x);
        return PINF;
    }
    if(dispinf(x)) {
        if(disneg(y)) return 0;
        else          return PINF;
    }
    if(disminf(x)) {
        if(!disneg(y)) {
            if(disoddint(y)) return MINF;
            else             return PINF;
        }
        if(disoddint(y)) return MZERO;
        else             return PZERO;
    }
    if(dispinf(y)) {
        if(dgetexp(x)<0x3ff) return PZERO;
        else                 return PINF;
    }
    if(disminf(y)) {
        if(dgetexp(x)<0x3ff) return PINF;
        else                 return PZERO;
    }
    if(disint(y)) return dpow_0(x,y);
    if(disneg(x)) return PINF;
    return dpow_1(x,y);
}

double WRAPPER_FUNC(hypot)(double x,double y) {
    check_nan_d2(x, y);
    int ex,ey;
    ex=dgetexp(x); ey=dgetexp(y);
    if(ex>=0x3ff+400||ey>=0x3ff+400) { // overflow, or nearly so
        x=dldexp(x,-600),y=dldexp(y,-600);
        return dldexp(sqrt(x*x+y*y), 600);
    }
    else if(ex<=0x3ff-400&&ey<=0x3ff-400) { // underflow, or nearly so
        x=dldexp(x, 600),y=dldexp(y, 600);
        return dldexp(sqrt(x*x+y*y),-600);
    }
    return sqrt(x*x+y*y);
}

double WRAPPER_FUNC(cbrt)(double x) {
    check_nan_d1(x);
    int e;
    if(disneg(x)) return dneg(cbrt(dneg(x)));
    if(diszero(x)) return dcopysign(PZERO,x);
    e=dgetexp(x)-0x3ff;
    e=(e*0x5555+0x8000)>>16;  // ~e/3, rounded
    x=dldexp(x,-e*3);
    x=exp(log(x)*ONETHIRD);
    return dldexp(x,e);
}

// reduces mx*2^e modulo my, returning bottom bits of quotient at *pquo
// 2^52<=|mx|,my<2^53, e>=0; 0<=result<my
static i64 drem_0(i64 mx,i64 my,int e,int*pquo) {
    int quo=0,q,r=0,s;
    if(e>0) {
        r=0xffffffffU/(ui32)(my>>36);  // reciprocal estimate Q16
    }
    while(e>0) {
        s=e; if(s>12) s=12;    // gain up to 12 bits on each iteration
        q=(mx>>38)*r;          // Q30
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

double WRAPPER_FUNC(fmod)(double x,double y) {
    check_nan_d2(x, y);
    ui64 ix=double2ui64(x),iy=double2ui64(y);
    int sx,ex,ey;
    i64 mx,my;
    DUNPACKS(ix,sx,ex,mx);
    DUNPACK(iy,ey,my);
    if(ex==0x7ff) return dnan_or(PINF);
    if(ey==0) return PINF;
    if(ex==0) {
        if(!disneg(x)) return PZERO;
        return MZERO;
    }
    if(ex<ey) return x;  // |x|<|y|, including case x=±0
    mx=drem_0(mx,my,ex-ey,0);
    if(sx) mx=-mx;
    return fix642double(mx,0x3ff-ey+52);
}

double WRAPPER_FUNC(remquo)(double x,double y,int*quo) {
    check_nan_d2(x, y);
    ui64 ix=double2ui64(x),iy=double2ui64(y);
    int sx,sy,ex,ey,q;
    i64 mx,my;
    DUNPACKS(ix,sx,ex,mx);
    DUNPACKS(iy,sy,ey,my);
    if(quo) *quo=0;
    if(ex==0x7ff) return PINF;
    if(ey==0)     return PINF;
    if(ex==0)     return PZERO;
    if(ey==0x7ff) return x;
    if(ex<ey-1)   return x;  // |x|<|y|/2
    if(ex==ey-1) {
        if(mx<=my) return x;   // |x|<=|y|/2, even quotient
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
        mx=drem_0(mx,my,ex-ey,&q);
        if(mx+mx>my || (mx+mx==my&&(q&1)) ) { // |x|>|y|/2, or equality and an odd quotient?
            mx-=my;
            q++;
        }
    }
    if(sy) q=-q;
    if(quo) *quo=q;
    return fix642double(mx,0x3ff-ey+52);
}

double WRAPPER_FUNC(drem)(double x,double y) { check_nan_d2(x, y); return remquo(x,y,0); }

double WRAPPER_FUNC(remainder)(double x,double y) { check_nan_d2(x, y); return remquo(x,y,0); }

_Pragma("GCC diagnostic pop") // conversion