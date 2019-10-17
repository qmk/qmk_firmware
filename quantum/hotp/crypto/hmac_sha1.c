/// Copyright (c) 2015, madwyn <madwyn@gmail.com>
/// Copyright (c) 2005 Olivier Gay <olivier.gay@a3.epfl.ch>
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///
/// * Redistributions of source code must retain the above copyright notice, this
///   list of conditions and the following disclaimer.
///
/// * Redistributions in binary form must reproduce the above copyright notice,
///   this list of conditions and the following disclaimer in the documentation
///   and/or other materials provided with the distribution.
///
/// * Neither the name of mad-hmac nor the names of its
///   contributors may be used to endorse or promote products derived from
///   this software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
/// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
/// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
/// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
/// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "hmac_sha1.h"

#include <string.h>
#include <stdlib.h>

#define IPAD (unsigned char)0x36
#define OPAD (unsigned char)0x5c

/* HMAC-SHA-1 functions */
void sha1(const unsigned char *message, unsigned int len, unsigned char *digest) {
    Sha1Context ctx;
    SHA1_HASH   hash;

    // uint8_t buffer_msg[len];
    uint8_t *buffer_msg = (uint8_t *)malloc(len);
    memcpy(buffer_msg, message, len);

    Sha1Initialise(&ctx);
    Sha1Update(&ctx, buffer_msg, len);
    free(buffer_msg);
    Sha1Finalise(&ctx, &hash);

    memcpy(digest, hash.bytes, SHA1_HASH_SIZE);
}

void hmac_sha1_init(hmac_sha1_ctx *ctx, const unsigned char *key, unsigned int key_size) {
    unsigned int fill;
    unsigned int num;

    const unsigned char *key_used;
    unsigned char key_temp[SHA1_DIGEST_SIZE];
    int i;

    if (key_size == SHA1_BLOCK_SIZE) {
        key_used = key;
        num = SHA1_BLOCK_SIZE;
    } else {
        if (key_size > SHA1_BLOCK_SIZE){
            num = SHA1_DIGEST_SIZE;
            sha1(key, key_size, key_temp);
            key_used = key_temp;
        } else { /* key_size > sha1_BLOCK_SIZE */
            key_used = key;
            num = key_size;
        }
        fill = SHA1_BLOCK_SIZE - num;

        memset(ctx->block_ipad + num, IPAD, fill);
        memset(ctx->block_opad + num, OPAD, fill);
    }

    for (i = 0; i < (int) num; i++) {
        ctx->block_ipad[i] = key_used[i] ^ IPAD;
        ctx->block_opad[i] = key_used[i] ^ OPAD;
    }

    Sha1Initialise(&ctx->ctx_inside);
    Sha1Update(&ctx->ctx_inside, ctx->block_ipad, SHA1_BLOCK_SIZE);

    Sha1Initialise(&ctx->ctx_outside);
    Sha1Update(&ctx->ctx_outside, ctx->block_opad,
            SHA1_BLOCK_SIZE);

    /* for hmac_reinit */
    memcpy(&ctx->ctx_inside_reinit, &ctx->ctx_inside,
            sizeof(Sha1Context));
    memcpy(&ctx->ctx_outside_reinit, &ctx->ctx_outside,
            sizeof(Sha1Context));
}

void hmac_sha1_reinit(hmac_sha1_ctx *ctx) {
    memcpy(&ctx->ctx_inside, &ctx->ctx_inside_reinit,
            sizeof(Sha1Context));
    memcpy(&ctx->ctx_outside, &ctx->ctx_outside_reinit,
            sizeof(Sha1Context));
}

void hmac_sha1_update(hmac_sha1_ctx *ctx, const unsigned char *message,
        unsigned int message_len) {
    Sha1Update(&ctx->ctx_inside, message, message_len);
}

void hmac_sha1_final(hmac_sha1_ctx *ctx, unsigned char *mac,
        unsigned int mac_size) {
    SHA1_HASH digest_inside;
    SHA1_HASH mac_temp;

    Sha1Finalise(&ctx->ctx_inside, &digest_inside);
    Sha1Update(&ctx->ctx_outside, digest_inside.bytes, SHA1_DIGEST_SIZE);
    Sha1Finalise(&ctx->ctx_outside, &mac_temp);
    memcpy(mac, mac_temp.bytes, mac_size);
}

void hmac_sha1(const unsigned char *key,     unsigned int key_size,
               const unsigned char *message, unsigned int message_len,
                     unsigned char *mac,     unsigned     mac_size) {
    hmac_sha1_ctx ctx;

    hmac_sha1_init(&ctx, key, key_size);
    hmac_sha1_update(&ctx, message, message_len);
    hmac_sha1_final(&ctx, mac, mac_size);
}
