
#include <string.h>

#include "debug.h"

#include "bmp_macro_parser.h"
#include "bmp_macro.h"
#include "keycode_str_converter.h"

#define PUT_ESC_SEQ(dst, c) \
    {                       \
        *dst++ = '\\';      \
        *dst++ = c;         \
    }

int32_t bmp_macro_file_stringify(const uint8_t *macro, uint8_t *serialized_text,
                                 uint32_t len) {
    const uint8_t *const start_addr = serialized_text;
    uint8_t *            dst        = serialized_text;
    const uint8_t *      src        = macro;
    uint8_t              macro_id   = 0;

    if (macro[BMP_MACRO_FILE_LEN - 1] != 0) {
        dprintf("[Macro] No valid file\n");
        return -1;
    }

    while (macro_id < BMP_MACRO_COUNT && dst - start_addr < len) {
        switch (*src) {
            case 0x00:
                macro_id++;
                *dst++ = '\n';
                break;
            case 0x01:
                // Tap
                PUT_ESC_SEQ(dst, 'T');
                break;
            case 0x02:
                // Down
                PUT_ESC_SEQ(dst, 'D');
                break;
            case 0x03:
                // Up
                PUT_ESC_SEQ(dst, 'U');
                break;
            case 0x04:
                // not implemented
                break;

            // C lang escape sequence
            case '\n':
                PUT_ESC_SEQ(dst, 'n');
                break;
            case '\t':
                PUT_ESC_SEQ(dst, 't');
                break;
            case '\b':
                PUT_ESC_SEQ(dst, 'b');
                break;
            case '\\':
                PUT_ESC_SEQ(dst, '\\');
                break;
            // BMP escape sequence
            case 0x7F:  // DEL
                PUT_ESC_SEQ(dst, 'd');
                break;
            case 0x1B:  // ESC
                PUT_ESC_SEQ(dst, 'e');
                break;

            case 0x20 ... '\\' - 1:
            case '\\' + 1 ... 0x7E:
                // ascii SPACE to KC_TILD
                *dst++ = *src;
                break;
            default:
                break;
        }

        if (*src >= 0x01 && *src <= 0x03) {
            *dst++     = '(';
            uint8_t kc = *(++src);
            dst += quantum_keycode2str(kc, (char *)dst, len);
            *dst++ = ')';
        }

        src++;
    }

    serialized_text[len - 1] = 0;

    return 0;
}

int32_t bmp_macro_file_parse(uint8_t *macro, const uint8_t *serialized_text,
                             uint32_t len) {
    const uint8_t *src = serialized_text;
    uint8_t *      dst = macro;

    if (serialized_text[len] != '\0') {
        dprintf("[Macro] Parse: string is not terminated\n");
        return -1;
    }

    while (*src != '\0' && (dst - macro) < BMP_MACRO_FILE_LEN - 2) {
        if (*src == '\\') {
            src++;
            switch (*src) {
                case 'n':
                    *dst++ = '\n';
                    break;
                case 't':
                    *dst++ = '\t';
                    break;
                case 'b':
                    *dst++ = '\b';
                    break;
                case '\\':
                    *dst++ = '\\';
                    break;
                case 'd':
                    *dst++ = 0x7F;
                    break;
                case 'e':
                    *dst++ = 0x1B;
                    break;
                case 'T':
                    *dst++ = 0x01;
                    break;
                case 'D':
                    *dst++ = 0x02;
                    break;
                case 'U':
                    *dst++ = 0x03;
                    break;
                default:
                    break;
            }

            switch (*src) {
                case 'T':
                case 'D':
                case 'U': {
                    const uint8_t *close =
                        (const uint8_t *)strchr((const char *)src + 2, ')');

                    if (close == NULL) {
                        dprintf("[Macro] Parse: Closing paren not found\n");
                        return -2;
                    }

                    uint8_t toklen = close - src - 2;
                    *dst++ =
                        str2quantum_keycode((const char *)(src + 2), toklen);
                    src += toklen + 3;
                } break;

                default:
                    src++;
                    break;
            }
        } else if (*src == '\n') {
            *dst++ = '\0';
            src++;
        } else {
            *dst++ = *src++;
        }
    }

    // terminate
    while (dst != &macro[BMP_MACRO_FILE_LEN]) {
        *dst++ = 0;
    }

    return 0;
}
