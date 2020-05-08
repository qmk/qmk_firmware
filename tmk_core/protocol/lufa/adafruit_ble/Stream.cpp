/*
  Modified from the original Stream.cpp which was released under the GPLv2
  License.

  Copyright (c) 2020 Joshua Rubin
  Copyright (c) 2008 David A. Mellis
  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  parsing functions based on TextFinder library by Michael Margolis
*/

#include "Stream.h"
#include "timer.h"

// protected method to read stream with timeout
int Stream::timedRead() {
    int c;
    _startMillis = timer_read32();
    do {
        c = read();
        if (c >= 0) return c;
    } while (timer_elapsed32(_startMillis) < _timeout);
    return -1;  // -1 indicates timeout
}

// protected method to peek stream with timeout
int Stream::timedPeek() {
    int c;
    _startMillis = timer_read32();
    do {
        c = peek();
        if (c >= 0) return c;
    } while (timer_elapsed32(_startMillis) < _timeout);
    return -1;  // -1 indicates timeout
}

// returns peek of the next digit in the stream or -1 if timeout
// discards non-numeric characters
int Stream::peekNextDigit(LookaheadMode lookahead, bool detectDecimal) {
    int c;
    while (1) {
        c = timedPeek();

        if (c < 0 || c == '-' || (c >= '0' && c <= '9') || (detectDecimal && c == '.')) return c;

        switch (lookahead) {
            case SKIP_NONE:
                return -1;  // Fail code.
            case SKIP_WHITESPACE:
                switch (c) {
                    case ' ':
                    case '\t':
                    case '\r':
                    case '\n':
                        break;
                    default:
                        return -1;  // Fail code.
                }
            case SKIP_ALL:
                break;
        }
        read();  // discard non-numeric
    }
}

// Public Methods
//////////////////////////////////////////////////////////////

void Stream::setTimeout(unsigned long timeout) {  // sets the maximum number of milliseconds to wait
    _timeout = timeout;
}

// find returns true if the target string is found
bool Stream::find(char *target) { return findUntil(target, strlen(target), NULL, 0); }

// reads data from the stream until the target string of given length is found
// returns true if target string is found, false if timed out
bool Stream::find(char *target, size_t length) { return findUntil(target, length, NULL, 0); }

// as find but search ends if the terminator string is found
bool Stream::findUntil(char *target, char *terminator) { return findUntil(target, strlen(target), terminator, strlen(terminator)); }

// reads data from the stream until the target string of the given length is found
// search terminated if the terminator string is found
// returns true if target string is found, false if terminated or timed out
bool Stream::findUntil(char *target, size_t targetLen, char *terminator, size_t termLen) {
    if (terminator == NULL) {
        MultiTarget t[1] = {{target, targetLen, 0}};
        return findMulti(t, 1) == 0 ? true : false;
    } else {
        MultiTarget t[2] = {{target, targetLen, 0}, {terminator, termLen, 0}};
        return findMulti(t, 2) == 0 ? true : false;
    }
}

// returns the first valid (long) integer value from the current position.
// lookahead determines how parseInt looks ahead in the stream.
// See LookaheadMode enumeration at the top of the file.
// Lookahead is terminated by the first character that is not a valid part of an integer.
// Once parsing commences, 'ignore' will be skipped in the stream.
long Stream::parseInt(LookaheadMode lookahead, char ignore) {
    bool isNegative = false;
    long value      = 0;
    int  c;

    c = peekNextDigit(lookahead, false);
    // ignore non numeric leading characters
    if (c < 0) return 0;  // zero returned if timeout

    do {
        if (c == ignore)
            ;  // ignore this character
        else if (c == '-')
            isNegative = true;
        else if (c >= '0' && c <= '9')  // is c a digit?
            value = value * 10 + c - '0';
        read();  // consume the character we got with peek
        c = timedPeek();
    } while ((c >= '0' && c <= '9') || c == ignore);

    if (isNegative) value = -value;
    return value;
}

// as parseInt but returns a floating point value
float Stream::parseFloat(LookaheadMode lookahead, char ignore) {
    bool  isNegative = false;
    bool  isFraction = false;
    long  value      = 0;
    int   c;
    float fraction = 1.0;

    c = peekNextDigit(lookahead, true);
    // ignore non numeric leading characters
    if (c < 0) return 0;  // zero returned if timeout

    do {
        if (c == ignore)
            ;  // ignore
        else if (c == '-')
            isNegative = true;
        else if (c == '.')
            isFraction = true;
        else if (c >= '0' && c <= '9') {  // is c a digit?
            value = value * 10 + c - '0';
            if (isFraction) fraction *= 0.1;
        }
        read();  // consume the character we got with peek
        c = timedPeek();
    } while ((c >= '0' && c <= '9') || (c == '.' && !isFraction) || c == ignore);

    if (isNegative) value = -value;
    if (isFraction)
        return value * fraction;
    else
        return value;
}

// read characters from stream into buffer
// terminates if length characters have been read, or timeout (see setTimeout)
// returns the number of characters placed in the buffer
// the buffer is NOT null terminated.
size_t Stream::readBytes(char *buffer, size_t length) {
    size_t count = 0;
    while (count < length) {
        int c = timedRead();
        if (c < 0) break;
        *buffer++ = (char)c;
        count++;
    }
    return count;
}

// as readBytes with terminator character
// terminates if length characters have been read, timeout, or if the terminator character  detected
// returns the number of characters placed in the buffer (0 means no valid data found)

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length) {
    size_t index = 0;
    while (index < length) {
        int c = timedRead();
        if (c < 0 || c == terminator) break;
        *buffer++ = (char)c;
        index++;
    }
    return index;  // return number of characters, not including null terminator
}

int Stream::findMulti(struct Stream::MultiTarget *targets, int tCount) {
    // any zero length target string automatically matches and would make
    // a mess of the rest of the algorithm.
    for (struct MultiTarget *t = targets; t < targets + tCount; ++t) {
        if (t->len <= 0) return t - targets;
    }

    while (1) {
        int c = timedRead();
        if (c < 0) return -1;

        for (struct MultiTarget *t = targets; t < targets + tCount; ++t) {
            // the simple case is if we match, deal with that first.
            if (c == t->str[t->index]) {
                if (++t->index == t->len)
                    return t - targets;
                else
                    continue;
            }

            // if not we need to walk back and see if we could have matched further
            // down the stream (ie '1112' doesn't match the first position in '11112'
            // but it will match the second position so we can't just reset the current
            // index to 0 when we find a mismatch.
            if (t->index == 0) continue;

            int origIndex = t->index;
            do {
                --t->index;
                // first check if current char works against the new current index
                if (c != t->str[t->index]) continue;

                // if it's the only char then we're good, nothing more to check
                if (t->index == 0) {
                    t->index++;
                    break;
                }

                // otherwise we need to check the rest of the found string
                int    diff = origIndex - t->index;
                size_t i;
                for (i = 0; i < t->index; ++i) {
                    if (t->str[i] != t->str[i + diff]) break;
                }

                // if we successfully got through the previous loop then our current
                // index is good.
                if (i == t->index) {
                    t->index++;
                    break;
                }

                // otherwise we just try the next index
            } while (t->index);
        }
    }
    // unreachable
    return -1;
}
