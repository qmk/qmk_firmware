/* Copyright 2017-2019 Nikolaus Wittenstein <nikolaus.wittenstein@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once


/* key matrix size */
#define MATRIX_ROWS 13
#define MATRIX_COLS 4

/*
 * Command/Windows key option
 *
 * If you define this, the thumb enter key becomes the Command/Windows key. There's still an enter key on the right
 * ring finger, so this key is much better utilized as the otherwise nonexistent Command key. I think some newer
 * DataHands let you remap right ring east as Command, but having it on the thumb is nicer. Comment out this define
 * to use the original layout.
 */
#define DATAHAND_THUMB_RETURN_COMMAND
