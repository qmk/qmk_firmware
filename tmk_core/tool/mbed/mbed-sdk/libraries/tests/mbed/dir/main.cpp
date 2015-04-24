#include "mbed.h"

void led_blink(PinName led) {
    DigitalOut myled(led);
    while (1) {
        myled = !myled;
        wait(1.0);
    }
}

void notify_completion(bool success) {
    if (success) {
        printf("{success}\n");
    } else {
        printf("{failure}\n");
    }

    printf("{end}\n");
    led_blink(success ? LED1 : LED4);
}

#define TEST_STRING   "Hello World!"

FILE* test_open(char* path, const char* mode) {
    FILE *f;
    f = fopen(path, mode);
    if (f == NULL) {
        printf("Error opening file\n");
        notify_completion(false);
    }

    return f;
}

void test_write(FILE* f, const char* str) {
    int n = fprintf(f, str);
    if (n != strlen(str)) {
        printf("Error writing file\n");
        notify_completion(false);
    }
}

void test_close(FILE* f) {
    int rc = fclose(f);
    if (rc != 0) {
        printf("Error closing file\n");
        notify_completion(false);
    }
}

int main() {
    LocalFileSystem local("local");

    FILE *f;
    char* str = TEST_STRING;
    char* buffer = (char*) malloc(sizeof(unsigned char)*strlen(TEST_STRING));
    int str_len = strlen(TEST_STRING);

    printf("Write files\n");
    char filename[32];
    for (int i=0; i<10; i++) {
        sprintf(filename, "/local/test_%d.txt", i);
        printf("Creating file: %s\n", filename);
        f = test_open(filename, "w");
        test_write(f, str);
        test_close(f);
    }

    printf("List files:\n");
    DIR *d = opendir("/local");
    struct dirent *p;
    while((p = readdir(d)) != NULL) {
        printf("%s\n", p->d_name);
    }
    closedir(d);

    notify_completion(true);
}
