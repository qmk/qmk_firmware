//===-- aeabi_cfcmpeq.c - Test __aeabi_cfcmpeq ----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file tests __aeabi_cfcmpeq for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pico/float.h>
#include "pico/stdlib.h"
#include "inttypes.h"

extern int __aeabi_fcmpun(float a, float b);

#if __arm__

#include "call_apsr.h"

extern __attribute__((pcs("aapcs"))) void __aeabi_cfcmpeq(float a, float b);

int test__aeabi_cfcmpeq(float a, float b, int expected) {
    uint32_t cpsr_value = call_apsr_f(a, b, __aeabi_cfcmpeq);
    union cpsr cpsr = {.value = cpsr_value};
    if (expected != cpsr.flags.z) {
        printf("error in __aeabi_cfcmpeq(%f, %f) => Z = %08x, expected %08x\n",
               a, b, cpsr.flags.z, expected);
        return 1;
    }
    return 0;
}

#endif

int test_cfcmpeq() {
#if __arm__
    if (test__aeabi_cfcmpeq(1.0, 1.0, 1))
        return 1;
    if (test__aeabi_cfcmpeq(1234.567, 765.4321, 0))
        return 1;
    if (test__aeabi_cfcmpeq(-123.0, -678.0, 0))
        return 1;
    if (test__aeabi_cfcmpeq(0.0, -0.0, 1))
        return 1;
    if (test__aeabi_cfcmpeq(0.0, 0.0, 1))
        return 1;
    if (test__aeabi_cfcmpeq(-0.0, -0.0, 1))
        return 1;
    if (test__aeabi_cfcmpeq(-0.0, 0.0, 1))
        return 1;
    if (test__aeabi_cfcmpeq(0.0, -1.0, 0))
        return 1;
    if (test__aeabi_cfcmpeq(-0.0, -1.0, 0))
        return 1;
    if (test__aeabi_cfcmpeq(-1.0, 0.0, 0))
        return 1;
    if (test__aeabi_cfcmpeq(-1.0, -0.0, 0))
        return 1;
    if (test__aeabi_cfcmpeq(1.0, NAN, 0))
        return 1;
    if (test__aeabi_cfcmpeq(NAN, 1.0, 0))
        return 1;
    if (test__aeabi_cfcmpeq(NAN, NAN, 0))
        return 1;
    if (test__aeabi_cfcmpeq(INFINITY, 1.0, 0))
        return 1;
    if (test__aeabi_cfcmpeq(0.0, INFINITY, 0))
        return 1;
    if (test__aeabi_cfcmpeq(-INFINITY, 0.0, 0))
        return 1;
    if (test__aeabi_cfcmpeq(0.0, -INFINITY, 0))
        return 1;
    if (test__aeabi_cfcmpeq(INFINITY, INFINITY, 1))
        return 1;
    if (test__aeabi_cfcmpeq(-INFINITY, -INFINITY, 1))
        return 1;
#else
    printf("skipped\n");
#endif
    return 0;
}

#if __arm__

extern __attribute__((pcs("aapcs"))) void __aeabi_cfcmple(float a, float b);

extern __attribute__((pcs("aapcs"))) void __aeabi_cfrcmple(float a, float b);

int test_fcmple_gt(float a, float b, int expected) {
    if ((a <= b) != expected) {
        printf("error in fcmple(%f, %f) => %d, expected %d\n",
               a, b, a <= b, expected);
        return 1;
    }
    if ((a > b) == expected && !isnanf(a) && !isnanf(b)) {
        printf("error in fcmpgt(%f, %f) => %d, expected %d\n",
               a, b, a > b, !expected);
        return 1;
    }
    return 0;
}

int test_fcmplt_ge(float a, float b, int expected) {
    if ((a < b) != expected) {
        printf("error in fcmplt(%f, %f) => %d, expected %d\n",
               a, b, a < b, expected);
        return 1;
    }
    if ((a >= b) == expected && !isnanf(a) && !isnanf(b)) {
        printf("error in fcmpge(%f, %f) => %d, expected %d\n",
               a, b, a >= b, !expected);
        return 1;
    }
    return 0;
}

int test__aeabi_cfcmple(float a, float b, int expected) {
    int32_t cpsr_value = call_apsr_f(a, b, __aeabi_cfcmple);
    int32_t r_cpsr_value = call_apsr_f(b, a, __aeabi_cfrcmple);
    int32_t cpsr_value2 = call_apsr_f(b, a, __aeabi_cfcmple);
    int32_t r_cpsr_value2 = call_apsr_f(a, b, __aeabi_cfrcmple);

    if (cpsr_value != r_cpsr_value) {
        printf("error: __aeabi_cfcmple(%f, %f) != __aeabi_cfrcmple(%f, %f)\n", a, b, b, a);
        return 1;
    }

    int expected_z, expected_c;
    if (expected == -1) {
        expected_z = 0;
        expected_c = 0;
    } else if (expected == 0) {
        expected_z = 1;
        expected_c = 1;
    } else {
        // a or b is NaN, or a > b
        expected_z = 0;
        expected_c = 1;
    }
#if PICO_FLOAT_COMPILER
    // gcc has this backwards it seems - not a good thing, but I guess it doesn't ever call them
    expected_c ^= 1;
#endif

    union cpsr cpsr = {.value = cpsr_value};
    if (expected_z != cpsr.flags.z || expected_c != cpsr.flags.c) {
        printf("error in __aeabi_cfcmple(%f, %f) => (Z = %d, C = %d), expected (Z = %d, C = %d)\n",
               a, b, cpsr.flags.z, cpsr.flags.c, expected_z, expected_c);
        return 1;
    }

    cpsr.value = r_cpsr_value;
    if (expected_z != cpsr.flags.z || expected_c != cpsr.flags.c) {
        printf("error in __aeabi_cfrcmple(%f, %f) => (Z = %d, C = %d), expected (Z = %d, C = %d)\n",
               a, b, cpsr.flags.z, cpsr.flags.c, expected_z, expected_c);
        return 1;
    }
    return 0;
}

#endif

int test_cfcmple() {
#if __arm__
    if (test__aeabi_cfcmple(1.0, 1.0, 0))
        return 1;
    if (test__aeabi_cfcmple(1234.567, 765.4321, 1))
        return 1;
    if (test__aeabi_cfcmple(765.4321, 1234.567, -1))
        return 1;
    if (test__aeabi_cfcmple(-123.0, -678.0, 1))
        return 1;
    if (test__aeabi_cfcmple(-678.0, -123.0, -1))
        return 1;
    if (test__aeabi_cfcmple(-123.0, 678.0, -1))
        return 1;
    if (test__aeabi_cfcmple(678.0, -123.0, 1))
        return 1;
    if (test__aeabi_cfcmple(0.0, -0.0, 0))
        return 1;
    if (test__aeabi_cfcmple(1.0, NAN, 1))
        return 1;
    if (test__aeabi_cfcmple(NAN, 1.0, 1))
        return 1;
    if (test__aeabi_cfcmple(NAN, NAN, 1))
        return 1;
#else
    printf("skipped\n");
#endif
    return 0;
}

int test_cmple_gt() {
    if (test_fcmple_gt(1.0, 1.0, 1))
        return 1;
    if (test_fcmple_gt(1234.567, 765.4321, 0))
        return 1;
    if (test_fcmple_gt(765.4321, 1234.567, 1))
        return 1;
    if (test_fcmple_gt(-123.0, -678.0, 0))
        return 1;
    if (test_fcmple_gt(-678.0, -123.0, 1))
        return 1;
    if (test_fcmple_gt(-123.0, 678.0, 1))
        return 1;
    if (test_fcmple_gt(678.0, -123.0, 0))
        return 1;
    if (test_fcmple_gt(0.0, -0.0, 1))
        return 1;
    if (test_fcmple_gt(-0.0, 0.0, 1))
        return 1;
    if (test_fcmple_gt(1.0, NAN, 0))
        return 1;
    if (test_fcmple_gt(NAN, 1.0, 0))
        return 1;
    if (test_fcmple_gt(NAN, NAN, 0))
        return 1;
    return 0;
}

int test_cmplt_ge() {
    if (test_fcmplt_ge(1.0, 1.0, 0))
        return 1;
    if (test_fcmplt_ge(1234.567, 765.4321, 0))
        return 1;
    if (test_fcmplt_ge(765.4321, 1234.567, 1))
        return 1;
    if (test_fcmplt_ge(-123.0, -678.0, 0))
        return 1;
    if (test_fcmplt_ge(-678.0, -123.0, 1))
        return 1;
    if (test_fcmplt_ge(-123.0, 678.0, 1))
        return 1;
    if (test_fcmplt_ge(678.0, -123.0, 0))
        return 1;
    if (test_fcmplt_ge(0.0, -0.0, 0))
        return 1;
    if (test_fcmplt_ge(-0.0, 0.0, 0))
        return 1;
    if (test_fcmplt_ge(1.0, NAN, 0))
        return 1;
    if (test_fcmplt_ge(NAN, 1.0, 0))
        return 1;
    if (test_fcmplt_ge(NAN, NAN, 0))
        return 1;
    return 0;
}

int check_fcmpun(float a, float b, bool expected, bool expect_equal) {
    if (__aeabi_fcmpun(a, b) != expected) {
        printf("Failed fcmpun(%f, %f)\n", a, b);
        return 1;
    }
    if ((a == b) != expect_equal) {
        printf("Failed equality check %f %f\n", a, b);
        __breakpoint();
        if (b == a) {
            printf("SAS\n");
        }
        return 1;
    }
    return 0;
}

int test_fcmpun() {
    if (check_fcmpun(0, 0, false, true) ||
        check_fcmpun(-INFINITY, INFINITY, false, false) ||
        check_fcmpun(NAN, 0, true, false) ||
        check_fcmpun(0, NAN, true, false) ||
        check_fcmpun(NAN, NAN, true, false) ||
        check_fcmpun(-NAN, NAN, true, false)) {
        return 1;
    }
    return 0;
}

#define assert_nan(a) assert(isnan(a))
#define check_nan(a) ({ assert_nan(a); a; })

float __aeabi_i2f(int32_t);
float __aeabi_ui2f(int32_t);
float __aeabi_l2f(int64_t);
float __aeabi_ul2f(int64_t);
int32_t __aeabi_f2iz(float);
int64_t __aeabi_f2lz(float);
float __aeabi_fmul(float, float);
float __aeabi_fdiv(float, float);
#if LIB_PICO_FLOAT_PICO
float __real___aeabi_i2f(int);
float __real___aeabi_ui2f(int);
float __real___aeabi_l2f(int64_t);
float __real___aeabi_ul2f(int64_t);
float __real___aeabi_fmul(float, float);
float __real___aeabi_fdiv(float, float);
int32_t __real___aeabi_f2iz(float);
int64_t __real___aeabi_f2lz(float);
float __real_sqrtf(float);
float __real_cosf(float);
float __real_sinf(float);
float __real_tanf(float);
float __real_expf(float);
float __real_logf(float);
float __real_atan2f(float, float);
float __real_powf(float, float);
float __real_truncf(float);
float __real_ldexpf(float, int);
float __real_fmodf(float, float);
#define EPSILON 1e-9
#define assert_close(a, b) assert(((b - a) < EPSILON || (a - b) < EPSILON) || (isinf(a) && isinf(b) && (a < 0) == (b < 0)))
#define check1(func,p0) ({ typeof(p0) r = func(p0), r2 = __CONCAT(__real_, func)(p0); assert(r == r2); r; })
#define check2(func,p0,p1) ({ typeof(p0) r = func(p0,p1), r2 = __CONCAT(__real_, func)(p0,p1); assert(r == r2); r; })
#define check_close1(func,p0) ({ typeof(p0) r = func(p0), r2 = __CONCAT(__real_, func)(p0); if (isnan(p0)) assert_nan(r); else assert_close(r, r2); r; })
#define check_close2(func,p0,p1) ({ typeof(p0) r = func(p0,p1), r2 = __CONCAT(__real_, func)(p0,p1); if (isnan(p0) || isnan(p1)) assert_nan(r); else assert_close(r, r2); r; })
#else
#define check1(func,p0) func(p0)
#define check2(func,p0,p1) func(p0,p1)
#define check_close1(func,p0) func(p0)
#define check_close2(func,p0,p1) func(p0,p1)
#endif

double aa = 0.5;
double bb = 1;

int main() {
    setup_default_uart();

    bool fail = false;

    printf("%d\n", aa < bb);
    for(float a = -1; a <= 1; a++) {
        for(float b = -1; b <= 1; b++) {
            printf("%f < %f ? %d\n", a, b, a < b);
        }
    }
    for(float a = -1; a <=1; a++) {
        for(float b = -1; b <= 1; b++) {
            printf("%f > %f ? %d\n", a, b, a > b);
        }
    }
    printf("F\n");
    for(float f = -1.0; f<=1.f; f+=0.25f) {
        printf("%d\n", (int)f);
    }
    printf("D\n");
    for(double d = -1.0; d<=1.0; d+=0.25) {
        printf("%d\n", (int)d);
    }
    printf("LD\n");
    for(double d = -1.0; d<=1.0; d+=0.25) {
        printf("%lld\n", (int64_t)d);
    }

    for(float d = -0.125; d>=-65536.0*65536.0*65536.0*65536.0*2; d*=2) {
        printf("%g %d, %lld, %u, %llu\n", d, (int32_t)d, (int64_t)d, (uint32_t)d, (uint64_t)d);
    }
    for(float d = 0.125; d<=65536.0*65536.0*65536.0*65536.0*2; d*=2) {
        printf("%g %d, %lld, %u, %llu\n", d, (int32_t)d, (int64_t)d, (uint32_t)d, (uint64_t)d);
    }

    for(double d = -0.125; d>=-65536.0*65536.0*65536.0*65536.0*2; d*=2) {
        printf("%g %d, %lld, %u, %llu\n", d, (int32_t)d, (int64_t)d, (uint32_t)d, (uint64_t)d);
    }
    for(double d = 0.125; d<=65536.0*65536.0*65536.0*65536.0*2; d*=2) {
        printf("%g %d, %lld, %u, %llu\n", d, (int32_t)d, (int64_t)d, (uint32_t)d, (uint64_t)d);
    }

    for(int i = (int32_t)0x80000000; i <0; i /= 2) {
        printf("%d %f\n", i, (double)i);
    }
    for(int i = (1<<30); i >0; i /= 2) {
        printf("%d %f\n", i, (double)i);
    }

    printf("%f\n", 0.5);
    printf("SQRT %10.18g\n", 0.5);
    printf("SQRT %10.18g\n", 0.333333333333333333333333);

#if 1
    for (float x = 0; x < 3; x++) {
        printf("\n ----- %f\n", x);
        printf("FSQRT %10.18f\n", check_close1(sqrtf, x));
        printf("FCOS %10.18f\n", check_close1(cosf, x));
        printf("FSIN %10.18f\n", check_close1(sinf, x));
        float s, c;
        sincosf(x, &s, &c);
        printf("FSINCOS %10.18f %10.18f\n", s, c);
        printf("FTAN %10.18f\n", check_close1(tanf, x));
        printf("FATAN2 %10.18f\n", check_close2(atan2f, x, 10.f));
        printf("FATAN2 %10.18f\n", check_close2(atan2f, 10.f, x));
        printf("FEXP %10.18f\n", check_close1(expf, x));
        printf("FLN %10.18f\n", check_close1(logf, x));
        printf("POWF %10.18f\n", check_close2(powf, x, x));
        printf("TRUNCF %10.18f\n", check_close1(truncf, x));
        printf("LDEXPF %10.18f\n", check_close2(ldexpf, x, x));
        printf("FMODF %10.18f\n", check_close2(fmodf, x, 3.0f));
        sincosf(x, &s, &c);
        printf("SINCOS %10.18f %10.18f\n", s, c);
        if (s != sinf(x) || c != cosf(x)) {
            printf("SINCOS mismatch\n");
            fail = true;
        }
    }

    for (double x = 0; x < 3; x++) {
        printf("\n ----- %g\n", x);
        printf("SQRT %10.18g\n", sqrt(x));
        printf("COS %10.18g\n", cos(x));
        printf("SIN %10.18g\n", sin(x));
        printf("TAN %10.18g\n", tan(x));
        printf("ATAN2 %10.18g\n", atan2(x, 10));
        printf("ATAN2 %10.18g\n", atan2(10, x));
        printf("EXP %10.18g\n", exp(x));
        printf("LN %10.18g\n", log(x));
    }

#if PICO_FLOAT_PROPAGATE_NANS
    {
        float x = NAN;
        printf("NANO %10.18f\n", x);
        printf("FSQRT %10.18f\n", sqrtf(x));
        printf("FCOS %10.18f\n", cosf(x));
        printf("FSIN %10.18f\n", sinf(x));
        printf("FTAN %10.18f\n", tanf(x));
        printf("FATAN2 %10.18f\n", atan2f(x, 10));
        printf("FATAN2 %10.18f\n", atan2f(10, x));
        printf("FEXP %10.18f\n", expf(x));
        printf("FLN %10.18f\n", logf(x));
        printf("POWF %10.18f\n", powf(x, x));
        printf("TRUNCF %10.18f\n", truncf(x));
        printf("LDEXPF %10.18f\n", ldexpf(x, x));
        printf("FMODF %10.18f\n", fmodf(x, 3.0f));
        float s, c;
//        sincosf(x, &s, &c);
        printf("FSINCOS %10.18f %10.18f\n", s, c);

        for(int j=0;j<2;j++) {
            for (int i = 1; i < 4; i++) {
                char buf[4];
                sprintf(buf, "%d", i);
                float f0 = -nanf(buf);
                double d0 = -nan(buf);
                // hmm nanf/nan seem to ignore payload
                *(uint64_t *) &d0 |= i;
                *(uint32_t *) &f0 |= i;
                if (j) {
                    // try without top bit set
                    *(uint64_t *) &d0 &= ~0x0008000000000000ull;
                    *(uint32_t *) &f0 &= ~0x00400000u;
                }
                float f = (float) d0;
                double d = (double) f0;
                printf("f2d %f %08"PRIx32" -> %g %016"PRIx64"\n", f0, *(uint32_t *) &f0, d, *(uint64_t *) &d);
                printf("d2f %f %016"PRIx64" -> %f %08"PRIx32"\n", d0, *(uint64_t *) &d0, f, *(uint32_t *) &f);
            }
        }
    }
#endif

    {
        int32_t y;
//        for (int32_t x = 0; x>-512; x--) {
//            printf("i %d->%f\n", (int)x, (float) x);
//        }
        for (int32_t x = -1; x; x <<= 1) {
            printf("i %d->%f\n", x, (float) x);
            check1(__aeabi_i2f, x);
        }
        for (int32_t x = 1; x; x <<= 1) {
            printf("i %d->%f\n", x, (float) x);
            check1(__aeabi_i2f, x);
            y = x << 1;
        }
        for (int64_t x = 1; x; x <<= 1) {
            printf("i %lld->%f\n", x, (float) x);
            check1(__aeabi_l2f, x);
            y = x << 1;
        }
        for (int64_t x = -1; x; x <<= 1) {
            printf("i %lld->%f\n", x, (float) x);
            check1(__aeabi_l2f, x);
            y = x << 1;
        }
        printf("d %d->%f\n", y, (float) y);
    }

    {
        uint32_t y;
        for(uint32_t x = 1; x; x <<= 1) {
            printf("u %u->%f\n", x, (float)x);
            check1(__aeabi_ui2f, x);
            y = x << 1;
        }
        printf("u %u->%f\n", y, (float)y);
    }
    for(int64_t x = 1; x !=0; x <<= 1u) {
        printf("%lld->%f\n", x, (float)x);
        check1(__aeabi_l2f, x);
    }
    for(float x = -4294967296.f * 4294967296.f; x>=0.5f; x/=2.f) {
        printf("f %f->%lld\n", x, (int64_t)x);
        if (x < INT64_MIN) {
            // seems like there is a bug in the gcc version!
            assert(__aeabi_f2lz(x) == INT64_MIN);
        } else {
            check1(__aeabi_f2lz, x);
        }
    }
    for(float x = 4294967296.f * 4294967296.f * 2.f; x>=0.5f; x/=2.f) {
        printf("f2i64 %f->%lld\n", x, (int64_t)x);
        if (x >= INT64_MAX) {
            // seems like there is a bug in the gcc version!
            assert(__aeabi_f2lz(x) == INT64_MAX);
        } else {
            check1(__aeabi_f2lz, x);
        }
    }
    for(float x = -4294967296.f * 4294967296.f; x<=-0.5f; x/=2.f) {
        printf("d2i32 %f->%d\n", x, (int32_t)x);
        check1(__aeabi_f2iz, x);
    }
    for(float x = 4294967296.f * 4294967296.f; x>=0.5f; x/=2.f) {
        printf("d2i32 %f->%d\n", x, (int32_t)x);
        check1(__aeabi_f2iz, x);
    }

    for (float x = 1; x < 11; x += 2) {
        float f = x * x;
        float g = 1.0f / x;
        printf("%g %10.18g %10.18g, %10.18g, %10.18g %10.18g\n", x, f, x + 0.37777777777777777777777777777f,
               x - 0.377777777777777777777777777777f, g, 123456789.0f / x);
        check2(__aeabi_fmul, x, x);
        check2(__aeabi_fdiv, 1.0f, x);
    }

    if (fail ||
        test_cfcmpeq() ||
        test_cfcmple() ||
        test_fcmpun() ||
        test_cmple_gt() ||
        test_cmplt_ge()) {
        printf("FAILED\n");
        return 1;
    } else {
        printf("PASSED\n");
        return 0;
    }
#endif
}

#if 0
// todo need to add tests like these

bool __noinline check(float x, float y) {
    return x > y;
}

bool __noinline checkd(double x, double y) {
    return x >= y;
}

int main() {
    stdio_init_all();
#if 0
    printf("0 op nan %d\n", check(0, nanf("sd")));
    printf("nan op 0 %d\n", check(nanf("sd"), 0));
    printf("0 op -nan %d\n", check(0, -nanf("sd")));
    printf("-nan op 0 %d\n", check(-nanf("sd"), 0));
    printf("-nan op nan %d\n", check(-nanf("xx"), nanf("xx")));
    printf("-nan op -nan %d\n", check(-nanf("xx"), -nanf("xx")));
    printf("nan op -nan %d\n", check(nanf("xx"), -nanf("xx")));
    printf("nan op nan %d\n", check(nanf("xx"), nanf("xx")));
    printf("0 op inf %d\n", check(0, infinityf()));
    printf("inf op 0 %d\n", check(infinityf(), 0));
    printf("0 op -inf %d\n", check(0, -infinityf()));
    printf("-inf op 0 %d\n", check(-infinityf(), 0));
    printf("-inf op inf %d\n", check(-infinityf(), infinityf()));
    printf("-inf op -inf %d\n", check(-infinityf(), -infinityf()));
    printf("inf op -inf %d\n", check(infinityf(), -infinityf()));
    printf("inf op inf %d\n", check(infinityf(), infinityf()));
    printf("1 op 1 %d\n", check(1, 1));
    printf("-1 op 1 %d\n", check(-1, 1));
    printf("1 op -1 %d\n", check(1, -1));
    printf("-1 op -1 %d\n", check(-1, -1));
    printf("1 op 2 %d\n", check(1, 2));
    printf("2 op 1 %d\n", check(2, 1));
    printf("-1 op -2 %d\n", check(-1, -2));
    printf("-2 op -1 %d\n", check(-2, -1));
#else
    printf("0 op nan %d\n", checkd(0, nan("sd")));
    printf("nan op 0 %d\n", checkd(nan("sd"), 0));
    printf("0 op -nan %d\n", checkd(0, -nan("sd")));
    printf("-nan op 0 %d\n", checkd(-nan("sd"), 0));
    printf("-nan op nan %d\n", checkd(-nan("xx"), nan("xx")));
    printf("-nan op -nan %d\n", checkd(-nan("xx"), -nan("xx")));
    printf("nan op -nan %d\n", checkd(nan("xx"), -nan("xx")));
    printf("nan op nan %d\n", checkd(nan("xx"), nan("xx")));
    printf("0 op inf %d\n", checkd(0, infinity()));
    printf("inf op 0 %d\n", checkd(infinity(), 0));
    printf("0 op -inf %d\n", checkd(0, -infinity()));
    printf("-inf op 0 %d\n", checkd(-infinity(), 0));
    printf("-inf op inf %d\n", checkd(-infinity(), infinity()));
    printf("-inf op -inf %d\n", checkd(-infinity(), -infinity()));
    printf("inf op -inf %d\n", checkd(infinity(), -infinity()));
    printf("inf op inf %d\n", checkd(infinity(), infinity()));
    printf("1 op 1 %d\n", checkd(1, 1));
    printf("-1 op 1 %d\n", checkd(-1, 1));
    printf("1 op -1 %d\n", checkd(1, -1));
    printf("-1 op -1 %d\n", checkd(-1, -1));
    printf("1 op 2 %d\n", checkd(1, 2));
    printf("2 op 1 %d\n", checkd(2, 1));
    printf("-1 op -2 %d\n", checkd(-1, -2));
    printf("-2 op -1 %d\n", checkd(-2, -1));
#endif
}
#endif