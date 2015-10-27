#include "test_env.h"

/* Timer/Match Register    Pinout Options

CT16B0/MR0  p5 (P0_9)
CT16B0/MR1  p6 (P0_8)
CT16B0/MR2  p34 (P1_15)

CT16B1/MR0  p36 (P0_21)
CT16B1/MR1  p20 (P0_22) and p14 (P1_23)

CT32B0/MR0  p25 (P1_24)
CT32B0/MR1  p26 (P1_25) and USBTX (P0_19)
CT32B0/MR2  p10 (P1_26)
 */

float value = 0.75;

int main() {
#if defined(TARGET_FF_ARDUINO)
    PwmOut pwm(D9);

    pwm.period_ms(10);
    pwm.write(value);

    float result = floor(pwm.read() * 100 + 0.5) / 100; // round it to 0.xx
    printf("Initialize PWM on pin D9 with duty cycle: %.2f\n", result);

    notify_completion(result == value ? true : false);

#elif defined(TARGET_LPC1768) || defined(TARGET_LPC2368) || defined(TARGET_LPC11U24) || defined(TARGET_LPC4088)
    PwmOut pwm_p25(p25);
    PwmOut pwm_p26(p26);

    pwm_p25.write(0.75);
    pwm_p26.write(0.50);

    printf("Initialize PWM on pin 25 with duty cycle: %.2f\n", pwm_p25.read());
    printf("Initialize PWM on pin 26 with duty cycle: %.2f\n", pwm_p26.read());

#elif defined(TARGET_LPC1114)
    PwmOut pwm_dp24(dp24); // P0_1
    PwmOut pwm_dp18(dp18); // P1_9

    pwm_dp24.write(0.75);
    pwm_dp18.write(0.50);

    printf("Initialize PWM on pin 24 with duty cycle: %.2f\n", pwm_dp24.read());
    printf("Initialize PWM on pin 18 with duty cycle: %.2f\n", pwm_dp18.read());

#elif defined(TARGET_nRF51822)
    PwmOut pwm_p24(p24);
    PwmOut pwm_p25(p25);

    pwm_p24.write(0.75);
    pwm_p25.write(0.50);

    printf("Initialize PWM on pin 24 with duty cycle: %.2f\n", pwm_p24.read());
    printf("Initialize PWM on pin 25 with duty cycle: %.2f\n", pwm_p25.read());

#elif defined(TARGET_DISCO_F100RB)
    PwmOut pwm_1(PB_3);
    PwmOut pwm_2(PB_4);

    pwm_1.write(0.75);
    pwm_2.write(0.50);

    printf("Initialize PWM on pin PB_3 with duty cycle: %.2f\n", pwm_1.read());
    printf("Initialize PWM on pin PB_4 with duty cycle: %.2f\n", pwm_2.read());
#elif defined(TARGET_DISCO_F051R8)
    PwmOut pwm_1(PA_7);
    PwmOut pwm_2(PC_7);

    pwm_1.write(0.75);
    pwm_2.write(0.50);

    printf("Initialize PWM on pin PA_7 with duty cycle: %.2f\n", pwm_1.read());
    printf("Initialize PWM on pin PC_7 with duty cycle: %.2f\n", pwm_2.read());
#elif defined(TARGET_DISCO_F303VC)
    PwmOut pwm_1(PA_8);
    PwmOut pwm_2(PA_9);

    pwm_1.write(0.75);
    pwm_2.write(0.50);

    printf("Initialize PWM on pin PA_7 with duty cycle: %.2f\n", pwm_1.read());
    printf("Initialize PWM on pin PC_7 with duty cycle: %.2f\n", pwm_2.read());
#elif defined(TARGET_MAXWSNENV)
    PwmOut pwm_1(TP2);
    PwmOut pwm_2(TP4);

    pwm_1.write(0.75);
    pwm_2.write(0.50);

    printf("Initialize PWM on pin TP2 with duty cycle: %.2f\n", pwm_1.read());
    printf("Initialize PWM on pin TP4 with duty cycle: %.2f\n", pwm_2.read());
#elif defined(TARGET_DISCO_F407VG)
    PwmOut pwm_1(PD_12);
    PwmOut pwm_2(PD_13);

    pwm_1.write(value);
    pwm_2.write(0.50);
    
    float result = floor(pwm_1.read() * 100 + 0.5) / 100; // round it to 0.xx

    printf("Initialize PWM on pin PD_12 with duty cycle: %.2f\n", result);
    printf("Initialize PWM on pin PD_13 with duty cycle: %.2f\n", pwm_2.read());

    notify_completion(result == value ? true : false);
#elif defined(TARGET_DISCO_F429ZI)
    PwmOut pwm_1(PA_0);

    pwm_1.write(value);
    
    float result = floor(pwm_1.read() * 100 + 0.5) / 100; // round it to 0.xx

    printf("Initialize PWM on pin PD_12 with duty cycle: %.2f\n", result);

    notify_completion(result == value ? true : false);
#elif defined(TARGET_MTS_MDOT_F405RG)
    PwmOut pwm_1(PA_0);

    pwm_1.write(value);
    
    float result = floor(pwm_1.read() * 100 + 0.5) / 100; // round it to 0.xx

    printf("Initialize PWM on pin PD_12 with duty cycle: %.2f\n", result);

    notify_completion(result == value ? true : false);
#elif defined(TARGET_MTS_DRAGONFLY_F411RE)
    PwmOut pwm_1(PA_0);

    pwm_1.write(value);
    
    float result = floor(pwm_1.read() * 100 + 0.5) / 100; // round it to 0.xx

    printf("Initialize PWM on pin PD_12 with duty cycle: %.2f\n", result);

    notify_completion(result == value ? true : false);
#elif defined(TARGET_MTS_MDOT_F411RE)
    PwmOut pwm_1(PA_0);

    pwm_1.write(value);
    
    float result = floor(pwm_1.read() * 100 + 0.5) / 100; // round it to 0.xx

    printf("Initialize PWM on pin PD_12 with duty cycle: %.2f\n", result);

    notify_completion(result == value ? true : false);
#elif defined(TARGET_UBLOX_C029)
    PwmOut pwm_1(PA_0);

    pwm_1.write(value);
    
    float result = floor(pwm_1.read() * 100 + 0.5) / 100; // round it to 0.xx

    printf("Initialize PWM on pin PD_12 with duty cycle: %.2f\n", result);

    notify_completion(result == value ? true : false);
#elif defined(TARGET_MAX32600MBED)
    PwmOut pwm_1(P1_2);
    PwmOut pwm_2(P1_3);

    pwm_1.write(0.75);
    pwm_2.write(0.50);

    printf("Initialize PWM on pin P1.2 with duty cycle: %.2f\n", pwm_1.read());
    printf("Initialize PWM on pin P1.3 with duty cycle: %.2f\n", pwm_2.read());
#else
#error This test is not supported on this target.
#endif

    notify_completion(true);
}
