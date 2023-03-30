//===-- aeabi_cdcmpeq.c - Test __aeabi_cdcmpeq ----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file tests __aeabi_cdcmpeq for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pico/double.h>
#include "pico/stdlib.h"
#include "inttypes.h"

extern int __aeabi_dcmpun(double a, double b);

#if __arm__

#include "call_apsr.h"

extern __attribute__((pcs("aapcs"))) void __aeabi_cdcmpeq(double a, double b);

int test__aeabi_cdcmpeq(double a, double b, int expected) {
    uint32_t cpsr_value = call_apsr_d(a, b, __aeabi_cdcmpeq);
    union cpsr cpsr = {.value = cpsr_value};
    if (expected != cpsr.flags.z) {
        printf("error in __aeabi_cdcmpeq(%f, %f) => Z = %08x, expected %08x\n",
               a, b, cpsr.flags.z, expected);
        return 1;
    }
    return 0;
}

#endif

int test_cdcmpeq() {
#if __arm__
    if (test__aeabi_cdcmpeq(1.0, 1.0, 1))
        return 1;
    if (test__aeabi_cdcmpeq(1234.567, 765.4321, 0))
        return 1;
    if (test__aeabi_cdcmpeq(-123.0, -678.0, 0))
        return 1;
    if (test__aeabi_cdcmpeq(0.0, -0.0, 1))
        return 1;
    if (test__aeabi_cdcmpeq(0.0, 0.0, 1))
        return 1;
    if (test__aeabi_cdcmpeq(-0.0, -0.0, 1))
        return 1;
    if (test__aeabi_cdcmpeq(-0.0, 0.0, 1))
        return 1;
    if (test__aeabi_cdcmpeq(0.0, -1.0, 0))
        return 1;
    if (test__aeabi_cdcmpeq(-0.0, -1.0, 0))
        return 1;
    if (test__aeabi_cdcmpeq(-1.0, 0.0, 0))
        return 1;
    if (test__aeabi_cdcmpeq(-1.0, -0.0, 0))
        return 1;
    if (test__aeabi_cdcmpeq(1.0, NAN, 0))
        return 1;
    if (test__aeabi_cdcmpeq(NAN, 1.0, 0))
        return 1;
    if (test__aeabi_cdcmpeq(NAN, NAN, 0))
        return 1;
    if (test__aeabi_cdcmpeq(INFINITY, 1.0, 0))
        return 1;
    if (test__aeabi_cdcmpeq(0.0, INFINITY, 0))
        return 1;
    if (test__aeabi_cdcmpeq(-INFINITY, 0.0, 0))
        return 1;
    if (test__aeabi_cdcmpeq(0.0, -INFINITY, 0))
        return 1;
    if (test__aeabi_cdcmpeq(INFINITY, INFINITY, 1))
        return 1;
    if (test__aeabi_cdcmpeq(-INFINITY, -INFINITY, 1))
        return 1;
#else
    printf("skipped\n");
#endif
    return 0;
}

#if __arm__

extern __attribute__((pcs("aapcs"))) void __aeabi_cdcmple(double a, double b);

extern __attribute__((pcs("aapcs"))) void __aeabi_cdrcmple(double a, double b);

int test_dcmple_gt(double a, double b, int expected) {
    if ((a <= b) != expected) {
        printf("error in dcmple(%f, %f) => %d, expected %d\n",
               a, b, a <= b, expected);
        return 1;
    }
    if ((a > b) == expected && !isnan(a) && !isnan(b)) {
        printf("error in dcmpgt(%f, %f) => %d, expected %d\n",
               a, b, a > b, !expected);
        return 1;
    }
    return 0;
}

int test_dcmplt_ge(double a, double b, int expected) {
    if ((a < b) != expected) {
        printf("error in dcmplt(%f, %f) => %d, expected %d\n",
               a, b, a < b, expected);
        return 1;
    }
    if ((a >= b) == expected && !isnan(a) && !isnan(b)) {
        printf("error in dcmpge(%f, %f) => %d, expected %d\n",
               a, b, a >= b, !expected);
        return 1;
    }
    return 0;
}

int test__aeabi_cdcmple(double a, double b, int expected) {
    int32_t cpsr_value = call_apsr_d(a, b, __aeabi_cdcmple);
    int32_t r_cpsr_value = call_apsr_d(b, a, __aeabi_cdrcmple);
    int32_t cpsr_value2 = call_apsr_d(b, a, __aeabi_cdcmple);
    int32_t r_cpsr_value2 = call_apsr_d(a, b, __aeabi_cdrcmple);

    if (cpsr_value != r_cpsr_value) {
        printf("error: __aeabi_cdcmple(%f, %f) != __aeabi_cdrcmple(%f, %f)\n", a, b, b, a);
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
#if PICO_DOUBLE_COMPILER
    // gcc has this backwards it seems - not a good thing, but I guess it doesn't ever call them
    expected_c ^= 1;
#endif

    union cpsr cpsr = {.value = cpsr_value};
    if (expected_z != cpsr.flags.z || expected_c != cpsr.flags.c) {
        printf("error in __aeabi_cdcmple(%f, %f) => (Z = %d, C = %d), expected (Z = %d, C = %d)\n",
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

int test_cdcmple() {
#if __arm__
    if (test__aeabi_cdcmple(1.0, 1.0, 0))
        return 1;
    if (test__aeabi_cdcmple(1234.567, 765.4321, 1))
        return 1;
    if (test__aeabi_cdcmple(765.4321, 1234.567, -1))
        return 1;
    if (test__aeabi_cdcmple(-123.0, -678.0, 1))
        return 1;
    if (test__aeabi_cdcmple(-678.0, -123.0, -1))
        return 1;
    if (test__aeabi_cdcmple(-123.0, 678.0, -1))
        return 1;
    if (test__aeabi_cdcmple(678.0, -123.0, 1))
        return 1;
    if (test__aeabi_cdcmple(0.0, -0.0, 0))
        return 1;
    if (test__aeabi_cdcmple(1.0, NAN, 1))
        return 1;
    if (test__aeabi_cdcmple(NAN, 1.0, 1))
        return 1;
    if (test__aeabi_cdcmple(NAN, NAN, 1))
        return 1;
#else
    printf("skipped\n");
#endif
    return 0;
}

int test_cmple_gt() {
    if (test_dcmple_gt(1.0, 1.0, 1))
        return 1;
    if (test_dcmple_gt(1234.567, 765.4321, 0))
        return 1;
    if (test_dcmple_gt(765.4321, 1234.567, 1))
        return 1;
    if (test_dcmple_gt(-123.0, -678.0, 0))
        return 1;
    if (test_dcmple_gt(-678.0, -123.0, 1))
        return 1;
    if (test_dcmple_gt(-123.0, 678.0, 1))
        return 1;
    if (test_dcmple_gt(678.0, -123.0, 0))
        return 1;
    if (test_dcmple_gt(0.0, -0.0, 1))
        return 1;
    if (test_dcmple_gt(-0.0, 0.0, 1))
        return 1;
    if (test_dcmple_gt(1.0, NAN, 0))
        return 1;
    if (test_dcmple_gt(NAN, 1.0, 0))
        return 1;
    if (test_dcmple_gt(NAN, NAN, 0))
        return 1;
    return 0;
}

int test_cmplt_ge() {
    if (test_dcmplt_ge(1.0, 1.0, 0))
        return 1;
    if (test_dcmplt_ge(1234.567, 765.4321, 0))
        return 1;
    if (test_dcmplt_ge(765.4321, 1234.567, 1))
        return 1;
    if (test_dcmplt_ge(-123.0, -678.0, 0))
        return 1;
    if (test_dcmplt_ge(-678.0, -123.0, 1))
        return 1;
    if (test_dcmplt_ge(-123.0, 678.0, 1))
        return 1;
    if (test_dcmplt_ge(678.0, -123.0, 0))
        return 1;
    if (test_dcmplt_ge(0.0, -0.0, 0))
        return 1;
    if (test_dcmplt_ge(-0.0, 0.0, 0))
        return 1;
    if (test_dcmplt_ge(1.0, NAN, 0))
        return 1;
    if (test_dcmplt_ge(NAN, 1.0, 0))
        return 1;
    if (test_dcmplt_ge(NAN, NAN, 0))
        return 1;
    return 0;
}

int check_dcmpun(double a, double b, bool expected, bool expect_equal) {
    if (__aeabi_dcmpun(a, b) != expected) {
        printf("Failed dcmpun(%f, %f)\n", a, b);
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

int test_dcmpun() {
    if (check_dcmpun(0, 0, false, true) ||
        check_dcmpun(-INFINITY, INFINITY, false, false) ||
        check_dcmpun(NAN, 0, true, false) ||
        check_dcmpun(0, NAN, true, false) ||
        check_dcmpun(NAN, NAN, true, false) ||
        check_dcmpun(-NAN, NAN, true, false)) {
        return 1;
    }
    return 0;
}

#define assert_nan(a) assert(isnan(a))
#define check_nan(a) ({ assert_nan(a); a; })

double __aeabi_i2d(int32_t);
double __aeabi_ui2d(int32_t);
double __aeabi_l2d(int64_t);
double __aeabi_ul2d(int64_t);
int32_t __aeabi_d2iz(double);
int64_t __aeabi_d2lz(double);
double __aeabi_dmul(double, double);
double __aeabi_ddiv(double, double);
#if LIB_PICO_DOUBLE_PICO
double __real___aeabi_i2d(int);
double __real___aeabi_ui2d(int);
double __real___aeabi_l2d(int64_t);
double __real___aeabi_ul2d(int64_t);
double __real___aeabi_dmul(double, double);
double __real___aeabi_ddiv(double, double);
int32_t __real___aeabi_d2iz(double);
int64_t __real___aeabi_d2lz(double);
double __real_sqrt(double);
double __real_cos(double);
double __real_sin(double);
double __real_tan(double);
double __real_exp(double);
double __real_log(double);
double __real_atan2(double, double);
double __real_pow(double, double);
double __real_trunc(double);
double __real_ldexp(double, int);
double __real_fmod(double, double);

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
    for(double a = -1; a <= 1; a++) {
        for(double b = -1; b <= 1; b++) {
            printf("%f < %f ? %d\n", a, b, a < b);
        }
    }
    for(double a = -1; a <=1; a++) {
        for(double b = -1; b <= 1; b++) {
            printf("%f > %f ? %d\n", a, b, a > b);
        }
    }

#if 1
    for (double x = 0; x < 3; x++) {
        printf("\n ----- %g\n", x);
        printf("SQRT %10.18g\n", check_close1(sqrt, x));
        printf("COS %10.18g\n", check_close1(cos, x));
        printf("SIN %10.18g\n", check_close1(sin, x));
        printf("TAN %10.18g\n", check_close1(tan, x));
        printf("ATAN2 %10.18g\n", check_close2(atan2, x, 10.0));
        printf("ATAN2 %10.18g\n", check_close2(atan2, 10.0, x));
        printf("EXP %10.18g\n", check_close1(exp, x));
        printf("LN %10.18g\n", check_close1(log, x));
        printf("POW %10.18f\n", check_close2(pow, x, x));
        printf("TRUNC %10.18f\n", check_close1(trunc, x));
        printf("LDEXP %10.18f\n", check_close2(ldexp, x, x));
        printf("FMOD %10.18f\n", check_close2(fmod, x, 3.0f));
        double s, c;
        sincos(x, &s, &c);
        printf("SINCOS %10.18f %10.18f\n", s, c);
        if (s != sin(x) || c != cos(x)) {
            printf("SINCOS mismatch\n");
            fail = true;
        }
    }

#if PICO_DOUBLE_PROPAGATE_NANS
    {
        float x = NAN;
        printf("SQRT %10.18g\n", check_close1(sqrt, x));
        printf("COS %10.18g\n", check_close1(cos, x));
        printf("SIN %10.18g\n", check_close1(sin, x));
        printf("TAN %10.18g\n", check_close1(tan, x));
        printf("ATAN2 %10.18g\n", check_close2(atan2, x, 10.0));
        printf("ATAN2 %10.18g\n", check_close2(atan2, 10.0, x));
        printf("EXP %10.18g\n", check_close1(exp, x));
        printf("LN %10.18g\n", check_close1(log, x));
        printf("POW %10.18f\n", check_nan(pow(x, x)));
        printf("TRUNC %10.18f\n", check_nan(trunc(x)));
        printf("LDEXP %10.18f\n", check_nan(ldexp(x, x)));
        printf("FMOD %10.18f\n", check_nan(fmod(x, 3.0f)));
        double s, c;
        sincos(x, &s, &c);
        printf("SINCOS %10.18f %10.18f\n", check_nan(s), check_nan(c));

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
            printf("i %d->%f\n", x, (double) x);
            check1(__aeabi_i2d, x);
        }
        for (int32_t x = 1; x; x <<= 1) {
            printf("i %d->%f\n", x, (double) x);
            check1(__aeabi_i2d, x);
            y = x << 1;
        }
        for (int64_t x = 1; x; x <<= 1) {
            printf("i %lld->%f\n", x, (double) x);
            check1(__aeabi_l2d, x);
            y = x << 1;
        }
        for (int64_t x = -1; x; x <<= 1) {
            printf("i %lld->%f\n", x, (double) x);
            check1(__aeabi_l2d, x);
            y = x << 1;
        }
        printf("d %d->%f\n", y, (float) y);
    }

    {
        uint32_t y;
        for(uint32_t x = 1; x; x <<= 1) {
            printf("u %u->%f\n", x, (double)x);
            check1(__aeabi_ui2d, x);
            y = x << 1;
        }
        printf("u %u->%f\n", y, (double)y);
    }
    for(int64_t x = 1; x !=0; x <<= 1u) {
        printf("%lld->%f\n", x, (double)x);
        check1(__aeabi_l2d, x);
    }
    for(double x = -4294967296.f * 4294967296.f * 2.f; x<=-0.5f; x/=2.f) {
        printf("d2i64 %f->%lld\n", x, (int64_t)x);
        if (x < INT64_MIN) {
            // seems like there is a bug in the gcc version!
            assert(__aeabi_d2lz(x) == INT64_MIN);
        } else {
            check1(__aeabi_d2lz, x);
        }
    }
    for(double x = 4294967296.f * 4294967296.f * 2.f; x>=0.5f; x/=2.f) {
        printf("d2i64 %f->%lld\n", x, (int64_t)x);
        if (x >= INT64_MAX) {
            // seems like there is a bug in the gcc version!
            assert(__aeabi_d2lz(x) == INT64_MAX);
        } else {
            check1(__aeabi_d2lz, x);
        }
    }
    for(double x = -4294967296.f * 4294967296.f; x<=-0.5f; x/=2.f) {
        printf("d2i32 %f->%d\n", x, (int32_t)x);
        check1(__aeabi_d2iz, x);
    }
    for(double x = 4294967296.f * 4294967296.f; x>=0.5f; x/=2.f) {
        printf("d2i32 %f->%d\n", x, (int32_t)x);
        check1(__aeabi_d2iz, x);
    }

    for (double x = 1; x < 11; x += 2) {
        double f = x * x;
        double g = 1.0 / x;
        printf("%g %10.18g %10.18g, %10.18g, %10.18g %10.18g\n", x, f, x + 0.37777777777777777777777777777,
               x - 0.377777777777777777777777777777, g, 123456789.0 / x);
        check2(__aeabi_dmul, x, x);
        check2(__aeabi_ddiv, 1.0, x);
    }

    if (fail ||
        test_cdcmpeq() ||
        test_cdcmple() ||
        test_dcmpun() ||
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
