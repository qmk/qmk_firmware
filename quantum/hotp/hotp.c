/*
 * Copyright (c) 2019 Edward Shin <contact@edwardsh.in>
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <stdint.h>

#include "hotp.h"
#include "crypto/hmac_sha1.h"

#include "tmk_core/common/eeconfig.h"
#include "tmk_core/common/eeprom.h"
#include "quantum.h" // for send_string()

#ifdef HOTP_ENABLE

#ifndef EECONFIG_HOTP
    #error EECONFIG_HOTP not defined in eeconfig.h
#endif

#ifndef HOTP_OUTPUT_DIGITS
    #error HOTP_OUTPUT_DIGITS not defined in config.h
#endif

#ifndef HOTP_SECRET
    #error HOTP_SECRET not defined in config.h
#endif

#ifndef STRINGIFY
    #define STRINGIFY(a) #a
#endif

#ifndef STRINGIFY_EXPANDED
    #define STRINGIFY_EXPANDED(a) STRINGIFY(a)
#endif

#define HOTP_DEBUG (0)
#define HOTP_DEBUG_VERBOSE (HOTP_DEBUG && 0)

#define HOTP_COUNTER_EEPROM_ADDR   ((uint8_t *) EECONFIG_HOTP)
#define HOTP_COUNTER_SIZE_BYTES    (8)

static const char s_hotp_secret[] = HOTP_SECRET;

/// Reads the counter out of EEPROM and returns it as a u64.
static uint64_t read_counter(void) {
    uint64_t counter = 0;
    uint8_t * address = (uint8_t *) HOTP_COUNTER_EEPROM_ADDR;
    for (int i = 0; i < HOTP_COUNTER_SIZE_BYTES; i++) {
      counter = counter << 8;
      counter |= (eeprom_read_byte(address+i) & 0xff);

#if HOTP_DEBUG_VERBOSE
      char debug[50] = {0};
      snprintf(debug, sizeof(debug), "read_counter: %u %u @ %p\n",
               i, (uint8_t) counter&0xff, address+i);
      send_string(debug);
#endif
    }
    return counter;
}

/// Takes the counter and writes it into EEPROM.
static void write_counter(uint64_t counter) {
    uint8_t * address = (uint8_t *) HOTP_COUNTER_EEPROM_ADDR;
    eeprom_write_block(&counter, (void *) address, sizeof(counter));
    for (int i = HOTP_COUNTER_SIZE_BYTES-1; i >= 0; i--) {
#if HOTP_DEBUG_VERBOSE
      char debug[50] = {0};
      snprintf(debug, sizeof(debug), "write_counter: %u %u @ %p\n",
               i, (uint8_t) counter&0xff, address+i);
      send_string(debug);
#endif
      eeprom_update_byte(address+i, counter & 0xff);
      counter = counter >> 8;
    }
}

/// Increments the counter value in EEPROM.
static void increment_counter(void) {
    uint64_t counter = read_counter();
    counter++;
    write_counter(counter);
}

/// Generates an HOTP value, incrementing the counter value.
static void generate_hotp(char * output, size_t output_len) {
    if (!output || output_len < (HOTP_OUTPUT_DIGITS + 1)) {
      return;
    }

    // Get the counter value from EEPROM
    uint64_t counter = read_counter();

#if HOTP_DEBUG
    char debug[100] = {0};
    send_string("secret: ");
    for (int i = 0; i < sizeof(s_hotp_secret); i++) {
      snprintf(debug, sizeof(debug), "%02x", s_hotp_secret[i]);
      send_string(debug);
    }
    send_string("\n");

    char * ctr_a = (char *) &counter;
    snprintf(debug, sizeof(debug),
        "counter: "
        "%02x%02x%02x%02x"
        "%02x%02x%02x%02x (%lu)\n",
        ctr_a[0], ctr_a[1], ctr_a[2], ctr_a[3],
        ctr_a[4], ctr_a[5], ctr_a[6], ctr_a[7],
        (uint32_t) counter);
    send_string(debug);
#endif

    // Generate the HMAC-SHA1 from the counter and secret.
    char hash[20] = {0};
    hmac_sha1((const unsigned char *) s_hotp_secret, sizeof(s_hotp_secret),
              (const unsigned char *) &counter, sizeof(counter),
              (unsigned char *) hash, sizeof(hash));

    // Perform Dynamic Truncation
    // Calculate the offset into the hash to read from.
    // The offset is the last 4 bits of the hash.
    uint8_t offset = hash[19] & 0xf;

#if HOTP_DEBUG
    send_string("hash: ");
    for (int i = 0; i < 20; i++) {
      snprintf(debug, sizeof(debug), "%02x", (unsigned int) hash[i]);
      send_string(debug);
    }
    send_string("\n");

    snprintf(debug, sizeof(debug), "offset: %u\n", offset);
    send_string(debug);

    snprintf(debug, sizeof(debug), "hash[offset]: %02x%02x%02x%02x\n",
             hash[offset], hash[offset+1], hash[offset+2], hash[offset+3]);
    send_string(debug);
#endif

    // Get the binary value by reading 4 bytes from the hash at the given offset.
    // Mask out the highest bit, as per spec.
    uint32_t binary = (((uint32_t) hash[offset + 0] & 0x7f) << 24) |
                      (((uint32_t) hash[offset + 1] & 0xff) << 16) |
                      (((uint32_t) hash[offset + 2] & 0xff) << 8 ) |
                      (((uint32_t) hash[offset + 3] & 0xff) << 0 );

#if HOTP_DEBUG
    snprintf(debug, sizeof(debug), "binary: %lu\n", binary);
    send_string(debug);
#endif

    // Calculate the OTP digits by taking the binary modulo 10^(num_digits).
    uint32_t mod = 1;
    for (int i = 0; i < HOTP_OUTPUT_DIGITS; i++) {
      mod *= 10;
    }

#if HOTP_DEBUG
    snprintf(debug, sizeof(debug), "mod: %lu\n", mod);
    send_string(debug);
#endif

    binary = binary % mod;

    // Format the OTP digits into a string and return them.
    char * format_str = "%0" STRINGIFY_EXPANDED(HOTP_OUTPUT_DIGITS) "lu\n";
    snprintf(output, output_len, format_str, binary);

    increment_counter();
}

/// Send the OTP and increment the counter.
void hotp_send(void) {
    char code[HOTP_OUTPUT_DIGITS+2] = {0};
    generate_hotp(code, sizeof(code));
    send_string(code);
}

#endif // HOTP_ENABLE
