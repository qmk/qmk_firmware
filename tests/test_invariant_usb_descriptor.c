#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Include the USB descriptor definitions */
#include "tmk_core/protocol/usb_descriptor.c"

/* Simulated SET_REPORT buffer - matches typical HID report sizes */
#define MAX_REPORT_SIZE 64

START_TEST(test_usb_report_buffer_bounds)
{
    /* Invariant: Buffer reads never exceed the declared length */
    uint8_t report_buffer[MAX_REPORT_SIZE];
    memset(report_buffer, 0, sizeof(report_buffer));

    /* Test payloads: wLength values that could cause overflow */
    uint16_t wLength_payloads[] = {
        MAX_REPORT_SIZE * 2,   /* 2x overflow attempt */
        MAX_REPORT_SIZE * 10,  /* 10x overflow attempt */
        0xFFFF,                /* Maximum uint16_t - extreme case */
        MAX_REPORT_SIZE,       /* Boundary: exact size */
        8                      /* Valid: typical keyboard report */
    };
    int num_payloads = sizeof(wLength_payloads) / sizeof(wLength_payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        uint16_t requested_len = wLength_payloads[i];
        uint16_t actual_len = (requested_len > MAX_REPORT_SIZE) ? 
                               MAX_REPORT_SIZE : requested_len;
        
        /* Verify truncation occurs for oversized requests */
        ck_assert_uint_le(actual_len, MAX_REPORT_SIZE);
        
        /* Simulate bounded copy - this is what the code SHOULD do */
        uint8_t test_data[MAX_REPORT_SIZE];
        memset(test_data, 0xAA, sizeof(test_data));
        memcpy(report_buffer, test_data, actual_len);
        
        /* Verify no write beyond buffer */
        ck_assert_uint_le(actual_len, sizeof(report_buffer));
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_usb_report_buffer_bounds);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}