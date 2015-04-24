#include "mbed.h"
#include "SDFileSystem.h"
#include "test_env.h"

#if defined(TARGET_KL25Z)
SDFileSystem sd(PTD2, PTD3, PTD1, PTD0, "sd");

#elif defined(TARGET_KL46Z)
SDFileSystem sd(PTD6, PTD7, PTD5, PTD4, "sd");

#elif defined(TARGET_K64F)
SDFileSystem sd(PTE3, PTE1, PTE2, PTE4, "sd");

#elif defined(TARGET_K22F)
SDFileSystem sd(PTD6, PTD7, PTD5, PTD4, "sd");

#elif defined(TARGET_K20D50M)
SDFileSystem sd(PTD2, PTD3, PTD1, PTC2, "sd");

#elif defined(TARGET_nRF51822)
SDFileSystem sd(p12, p13, p15, p14, "sd");

#elif defined(TARGET_NUCLEO_F030R8) || \
      defined(TARGET_NUCLEO_F070RB) || \
      defined(TARGET_NUCLEO_F072RB) || \
      defined(TARGET_NUCLEO_F091RC) || \
      defined(TARGET_NUCLEO_F103RB) || \
      defined(TARGET_NUCLEO_F302R8) || \
      defined(TARGET_NUCLEO_F303RE) || \
      defined(TARGET_NUCLEO_F334R8) || \
      defined(TARGET_NUCLEO_F401RE) || \
      defined(TARGET_NUCLEO_F411RE) || \
      defined(TARGET_NUCLEO_L053R8) || \
      defined(TARGET_NUCLEO_L073RZ) || \
      defined(TARGET_NUCLEO_L152RE)
SDFileSystem sd(D11, D12, D13, D10, "sd");

#elif defined(TARGET_DISCO_F051R8)
SDFileSystem sd(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, "sd");

#elif defined(TARGET_LPC2368)
SDFileSystem sd(p11, p12, p13, p14, "sd");

#elif defined(TARGET_LPC11U68)
SDFileSystem sd(D11, D12, D13, D10, "sd");

#elif defined(TARGET_LPC1549)
SDFileSystem sd(D11, D12, D13, D10, "sd");

#elif defined(TARGET_RZ_A1H)
SDFileSystem sd(P8_5, P8_6, P8_3, P8_4, "sd");

#elif defined(TARGET_LPC11U37H_401)
SDFileSystem sd(SDMOSI, SDMISO, SDSCLK, SDSSEL, "sd");
    
#else
SDFileSystem sd(p11, p12, p13, p14, "sd");
#endif

namespace {
const char *sd_file_path = "/sd/out.txt";
const int DATA_SIZE = 256;
}

int main() {
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(SD File System);
    MBED_HOSTTEST_START("MBED_A12");

    uint8_t data_written[DATA_SIZE] = { 0 };
    bool result = false;

    // Fill data_written buffer with random data
    // Write these data into the file
    bool write_result = false;
    {
        printf("SD: Writing ... ");
        FILE *f = fopen(sd_file_path, "w");
        if (f) {
            for (int i = 0; i < DATA_SIZE; i++) {
                data_written[i] = rand() % 0XFF;
                fprintf(f, "%c", data_written[i]);
            }
            write_result = true;
            fclose(f);
        }
        printf("[%s]\r\n", write_result ? "OK" : "FAIL");
    }

    // Read back the data from the file and store them in data_read
    bool read_result = false;
    {
        printf("SD: Reading data ... ");
        FILE *f = fopen(sd_file_path, "r");
        if (f) {
              read_result = true;
            for (int i = 0; i < DATA_SIZE; i++) {
                uint8_t data = fgetc(f);
                if (data != data_written[i]) {
                    read_result = false;
                    break;
                }
            }
            fclose(f);
        }
        printf("[%s]\r\n", read_result ? "OK" : "FAIL");
    }

    result = write_result && read_result;
    MBED_HOSTTEST_RESULT(result);
}
