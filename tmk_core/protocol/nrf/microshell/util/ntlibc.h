/**
 * @file      ntlibc.h
 * @author    Shinichiro Nakamura (CuBeatSystems)
 * ===============================================================
 * MicroShell (Version 0.0.2)
 * Copyright (c) 2016, 2017 Shinichiro Nakamura (CuBeatSystems)
 * ===============================================================
 * The MIT License : https://opensource.org/licenses/MIT
 *
 * Copyright (c) 2016, 2017 Shinichiro Nakamura (CuBeatSystems)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef NTLIBC_H
#define NTLIBC_H

#ifdef __cplusplus
extern "C" {
#endif

int ntlibc_strlen(const char *s);
char *ntlibc_strcpy(char *des, const char *src);
char *ntlibc_strcat(char *des, const char *src);
int ntlibc_strcmp(const char *s1, const char *s2);
int ntlibc_stricmp(const char *s1, const char *s2);
int ntlibc_strncmp(const char *s1, const char *s2, int n);
int ntlibc_isdigit(int c);
int ntlibc_isalpha(int c);
int ntlibc_iscntrl(int c);
int ntlibc_toupper(int c);
int ntlibc_tolower(int c);
int ntlibc_atoi(const char *nptr);
char *ntlibc_strchr(const char *s, int c);
char *ntlibc_utoa(unsigned int value, char *s, int radix);
char *ntlibc_itoa(int value, char *s, int radix);

#ifdef __cplusplus
}
#endif

#endif

