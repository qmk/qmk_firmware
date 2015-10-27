#include "mbed.h"
#include "SDFileSystem.h"

void led_blink(PinName led)
{
    DigitalOut myled(led);

    while (1) {
        myled = !myled;
        wait(1.0);
    }
}

void notify_completion(bool success)
{
    if (success)
        printf("{success}\n");
    else
        printf("{failure}\n");

    printf("{end}\n");
    led_blink(success ? LED1 : LED4);
}

#define TEST_STRING   "Hello World!"

FILE *test_open(char *path, const char *mode)
{
    FILE *f;

    f = fopen(path, mode);
    if (f == NULL) {
        printf("Error opening file\n");
        notify_completion(false);
    }

    return f;
}

void test_write(FILE *f, const char *str)
{
    int n = fprintf(f, str);

    if (n != strlen(str)) {
        printf("Error writing file\n");
        notify_completion(false);
    }
}

void test_close(FILE *f)
{
    int rc = fclose(f);

    if (rc != 0) {
        printf("Error closing file\n");
        notify_completion(false);
    }
}

DigitalOut led2(LED2);

int main()
{
#if defined(TARGET_KL25Z)
    SDFileSystem sd(PTD2, PTD3, PTD1, PTD0, "sd");
#elif defined(TARGET_nRF51822)
//SDFileSystem sd(p20, p22, p25, p24, "sd");
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
#elif defined(TARGET_LPC11U37H_401)
    SDFileSystem sd(SDMOSI, SDMISO, SDSCLK, SDSSEL, "sd");
#else
    SDFileSystem sd(p11, p12, p13, p14, "sd");
#endif
    led2 = 1;
    wait(0.5);
    FILE *f;
    char *str = TEST_STRING;
    char *buffer = (char *)malloc(sizeof(unsigned char) * strlen(TEST_STRING));
    int str_len = strlen(TEST_STRING);

    printf("Write files\n");
    char filename[32];
    for (int i = 0; i < 10; i++) {
        sprintf(filename, "/sd/test_%d.txt", i);
        printf("Creating file: %s\n", filename);
        f = test_open(filename, "w");
        led2 = 0;
        test_write(f, str);
        test_close(f);
    }

    printf("List files:\n");
    DIR *d = opendir("/sd");
    if (d == NULL) {
        printf("Error opening directory\n");
        notify_completion(false);
    }

    struct dirent *p;
    while ((p = readdir(d)) != NULL)
        printf("%s\n", p->d_name);
    closedir(d);

    notify_completion(true);
}
