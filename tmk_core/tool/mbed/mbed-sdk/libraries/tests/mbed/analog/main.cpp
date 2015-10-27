#include "test_env.h"

#if defined(TARGET_K64F) | defined (TARGET_K22F)
AnalogIn in(A0);
AnalogOut out(DAC0_OUT);

#elif defined(TARGET_KL25Z)
AnalogIn in(PTC2);
AnalogOut out(PTE30);

#elif defined(TARGET_KL05Z)
AnalogIn in(PTB11);  // D9
AnalogOut out(PTB1); // D1

#elif defined(TARGET_KL46Z)
AnalogIn in(PTB0);
AnalogOut out(PTE30);

#elif defined(TARGET_LPC1549)
AnalogIn in(A0);
AnalogOut out(D12); //D12 is P0_12, the DAC output pin

// No DAC on these targets:
//TARGET_NUCLEO_F030R8
//TARGET_NUCLEO_F070RB
//TARGET_NUCLEO_F103RB
//TARGET_NUCLEO_F401RE
//TARGET_NUCLEO_F411RE
#elif defined(TARGET_NUCLEO_F072RB) || \
      defined(TARGET_NUCLEO_F091RC) || \
      defined(TARGET_NUCLEO_F302R8) || \
      defined(TARGET_NUCLEO_F303RE) || \
      defined(TARGET_NUCLEO_F334R8) || \
      defined(TARGET_NUCLEO_L053R8) || \
      defined(TARGET_NUCLEO_L073RZ) || \
      defined(TARGET_NUCLEO_L152RE)
AnalogIn in(A0);
AnalogOut out(A2); // DAC output

#elif defined(TARGET_ARCH_MAX)
AnalogIn in(PA_0);
AnalogOut out(PA_4);

#elif defined(TARGET_DISCO_F407VG)
AnalogIn in(PC_5);
AnalogOut out(PA_4);

#elif defined(TARGET_DISCO_F429ZI)
AnalogIn in(PC_3);
AnalogOut out(PA_5);

#elif defined(TARGET_MAX32600MBED)
AnalogIn in(AIN_7P);
AnalogOut out(AOUT_DO);

#else
AnalogIn in(p17);
AnalogOut out(p18);

#endif

#define ERROR_TOLLERANCE    0.05

int main() {
    bool check = true;

    for (float out_value=0.0; out_value<1.1; out_value+=0.1) {
        out.write(out_value);
        wait(0.1);

        float in_value = in.read();
        float diff = fabs(out_value - in_value);
        if (diff > ERROR_TOLLERANCE) {
            check = false;
            printf("ERROR (out:%.4f) - (in:%.4f) = (%.4f)"NL, out_value, in_value, diff);
        } else {
            printf("OK    (out:%.4f) - (in:%.4f) = (%.4f)"NL, out_value, in_value, diff);
        }
    }

    notify_completion(check);
}