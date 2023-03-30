/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_TEST_H
#define _PICO_TEST_H

#include "pico.h"

/* Various macros to help with test harnesses

Note: really need to change the returns to exit()
but not sure that is implemented yet.
*/

#define PICOTEST_MODULE_NAME(n,d) const char *picotest_module=n; const char *picotest_description=d; int picotest_error_code;

#define PICOTEST_START() printf("Starting Picotest for %s\n", picotest_description);

#define PICOTEST_START_SECTION(NAME) if (1) {const char *picotest_section_name=NAME; picotest_error_code = 0;

#define PICOTEST_END_SECTION() if (picotest_error_code != 0) {                                      \
                                    printf("Module %s: Section %s : Failed test\n", picotest_module, picotest_section_name);\
                                    return -1;                                                      \
                                    } else                                                          \
                                    printf("Module %s: Section %s : Passed\n", picotest_module, picotest_section_name); \
                               }

#define PICOTEST_CHECK(COND, MESSAGE) if (!(COND)) {                                               \
                                        printf("Module %s: %s\n", picotest_module, MESSAGE);       \
                                        picotest_error_code = -1;                                   \
                                    }
#define PICOTEST_CHECK_CHANNEL(CHANNEL, COND, MESSAGE) if (!(COND)) {                              \
                                        printf("Module %s, channel %d: %s\n", picotest_module, CHANNEL, MESSAGE);  \
                                        picotest_error_code = -1;                                   \
                                    }

#define PICOTEST_CHECK_AND_ABORT(COND, MESSAGE) if (!(COND)) {                                     \
                                        printf("Module %s: %s\n", picotest_module, MESSAGE);       \
                                        return -1;                                                  \
                                    }

#define PICOTEST_CHECK_CHANNEL_AND_ABORT(CHANNEL, COND, MESSAGE) if (!(COND)) {                    \
                                        printf("Module %s, channel %d: %s\n", picotest_module, CHANNEL, MESSAGE);  \
                                        return -1;                                                  \
                                    }

#define PICOTEST_ABORT_IF_FAILED()  if (picotest_error_code != 0) {                                 \
                                        printf("Module %s: Aborting\n", picotest_module);           \
                                        return -1;                                                  \
                                    }

#define PICOTEST_END_TEST()       if (picotest_error_code != 0)                                     \
                                      {printf("%s: Failed\n", picotest_description); return -1;}  \
                                  else                                                              \
                                      {printf("%s: Success\n", picotest_description); return 0;}


#endif