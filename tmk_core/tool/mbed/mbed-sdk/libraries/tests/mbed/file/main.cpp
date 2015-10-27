#include "test_env.h"
#include "semihost_api.h"

Serial pc(USBTX, USBRX);

#define FILENAME      "/local/out.txt"
#define TEST_STRING   "Hello World!"

FILE *test_open(const char *mode) {
    FILE *f = fopen(FILENAME, mode);
    if (f == NULL) {
        printf("Error opening file"NL);
        notify_completion(false);
    }
    return f;
}

void test_write(FILE *f, char *str, int str_len) {
    int n = fprintf(f, str);

    if (n != str_len) {
        printf("Error writing file"NL);
        notify_completion(false);
    }
}

void test_read(FILE *f, char *str, int str_len) {
    int n = fread(str, sizeof(unsigned char), str_len, f);

    if (n != str_len) {
        printf("Error reading file"NL);
        notify_completion(false);
    }
}

void test_close(FILE *f) {
    int rc = fclose(f);

    if (rc != 0) {
        printf("Error closing file"NL);
        notify_completion(false);
    }
}

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(Semihost file system);
    MBED_HOSTTEST_START("MBED_A2");

    pc.printf("Test the Stream class\n");

    printf("connected: %s\n", (semihost_connected()) ? ("Yes") : ("No"));

    char mac[16];
    mbed_mac_address(mac);
    printf("mac address: %02x,%02x,%02x,%02x,%02x,%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    LocalFileSystem local("local");

    FILE *f;
    char *str = TEST_STRING;
    char *buffer = (char *)malloc(sizeof(unsigned char) * strlen(TEST_STRING));
    int str_len = strlen(TEST_STRING);

    // Write
    f = test_open("w");
    test_write(f, str, str_len);
    test_close(f);

    // Read
    f = test_open("r");
    test_read(f, buffer, str_len);
    test_close(f);

    // Check the two strings are equal
    MBED_HOSTTEST_RESULT((strncmp(buffer, str, str_len) == 0));
}
