#define main original_main
#include "qmk_id.c"
#undef main

#include <stdio.h>

int main() {
    struct testcase {
        char    description[100];
        int     expected_ret;
        size_t  report_size;
        uint8_t report[100];
    };
    struct testcase testcases[] = {
        {"empty input", -EIO, 0, {0}}, {"basic qmk console descriptor", 1, 7, {0x06, 0x31, 0xFF, 0x09, 0x74, 0xA1, 0x01}}, {"different usage page", 0, 7, {0x06, 0x30, 0xFF, 0x09, 0x74, 0xA1, 0x01}}, {"different usage", 0, 7, {0x06, 0x31, 0xFF, 0x09, 0x73, 0xA1, 0x01}}, {"empty long items", 1, 10, {0xFE, 0X00, 0xF0, 0x06, 0x31, 0xFF, 0x09, 0x74, 0xA1, 0x01}}, {"long items", 1, 11, {0xFE, 0X01, 0xF0, 0x00, 0x06, 0x31, 0xFF, 0x09, 0x74, 0xA1, 0x01}},
    };

    int num_testcases = ARRAY_SIZE(testcases);

    printf("1..%d\n", num_testcases);

    int failed = 0;

    for (int i = 0; i < num_testcases; i++) {
        struct testcase tc  = testcases[i];
        int             ret = is_teensy_style_console(tc.report, tc.report_size);

        if (ret == tc.expected_ret) {
            printf("ok %d - %s\n", i + 1, tc.description);
        } else {
            failed++;
            printf("not ok %d - %s\n  result %d != expected %d\n", i + 1, tc.description, ret, tc.expected_ret);
        }
    }

    return failed;
}
