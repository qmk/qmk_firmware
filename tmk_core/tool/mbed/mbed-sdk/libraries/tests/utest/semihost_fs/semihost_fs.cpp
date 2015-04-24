#include "TestHarness.h"
#include "mbed.h"
#include "semihost_api.h"
#include <stdio.h>

#define FILENAME      "/local/out.txt"
#define TEST_STRING   "Hello World!"

TEST_GROUP(FirstTestGroup)
{

    FILE *test_open(const char *mode) {
        FILE *f = fopen(FILENAME, mode);
        return f;
    }

    bool test_write(FILE *f, char *str, int str_len) {
        int n = fprintf(f, str);
        return (n == str_len) ? true : false;
    }

    bool test_read(FILE *f, char *str, int str_len) {
        int n = fread(str, sizeof(unsigned char), str_len, f);
        return (n == str_len) ? true : false;
    }

    bool test_close(FILE *f) {
        int rc = fclose(f);
        return rc ? true : false;
    }

};

TEST(FirstTestGroup, FirstTest)
{
    CHECK_TEXT(semihost_connected(), "Semihost not connected")

    LocalFileSystem local("local");

    char *str = TEST_STRING;
    char *buffer = (char *)malloc(sizeof(unsigned char) * strlen(TEST_STRING));
    int str_len = strlen(TEST_STRING);

    CHECK_TEXT(buffer != NULL, "Buffer allocation failed");
    CHECK_TEXT(str_len > 0, "Test string is empty (len <= 0)");

    {
        // Perform write / read tests
        FILE *f = NULL;
        // Write
        f = test_open("w");
        CHECK_TEXT(f != NULL, "Error opening file for writing")
        CHECK_TEXT(test_write(f, str, str_len), "Error writing file");
        CHECK_TEXT(test_close(f) != EOF, "Error closing file after write");

        // Read
        f = test_open("r");
        CHECK_TEXT(f != NULL, "Error opening file for reading")
        CHECK_TEXT(test_read(f, buffer, str_len), "Error reading file");
        CHECK_TEXT(test_close(f) != EOF, "Error closing file after read");
    }
    CHECK(strncmp(buffer, str, str_len) == 0);
}
