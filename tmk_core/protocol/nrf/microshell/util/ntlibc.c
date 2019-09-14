/**
 * @file      ntlibc.c
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

#include "ntlibc.h"

int ntlibc_strlen(const char *s)
{
    const char *p = s;
    int cnt = 0;
    while (*p) {
        cnt++;
        p++;
    }
    return cnt;
}

char *ntlibc_strcpy(char *des, const char *src)
{
    char *d = des;
    const char *s = src;
    while (*s) {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';
    return des;
}

char *ntlibc_strcat(char *des, const char *src)
{
    char *d = des;
    const char *s = src;
    while (*d) {
        d++;
    }
    while (*s) {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';
    return des;
}

int ntlibc_strcmp(const char *s1, const char *s2)
{
    char *p1 = (char *)s1;
    char *p2 = (char *)s2;
    while (*p1 || *p2) {
        if (*p1 != *p2) {
            return (*p1 < *p2) ? -1 : 1;
        }
        p1++;
        p2++;
    }
    if (*p1 == *p2) {
        return 0;
    } else {
        return (*p1 < *p2) ? -1 : 1;
    }
}

int ntlibc_stricmp(const char *s1, const char *s2)
{
    char *p1 = (char *)s1;
    char *p2 = (char *)s2;
    while (*p1 || *p2) {
        if (ntlibc_toupper(*p1) != ntlibc_toupper(*p2)) {
            return (*p1 < *p2) ? -1 : 1;
        }
        p1++;
        p2++;
    }
    if (*p1 == *p2) {
        return 0;
    } else {
        return (*p1 < *p2) ? -1 : 1;
    }
}

int ntlibc_strncmp(const char *s1, const char *s2, int n)
{
    char *p1 = (char *)s1;
    char *p2 = (char *)s2;
    int len = 0;
    while (*p1 || *p2) {
        if (n <= len) {
            break;
        }
        if (*p1 != *p2) {
            return (*p1 < *p2) ? -1 : 1;
        }
        p1++;
        p2++;
        len++;
    }
    return 0;
}

int ntlibc_isdigit(int c)
{
  if (('0' <= c) && (c <= '9')) {
    return 1;
  }
  return 0;
}

int ntlibc_isalpha(int c)
{
  if (('A' <= c) && (c <= 'Z')) {
    return 1;
  }
  if (('a' <= c) && (c <= 'z')) {
    return 1;
  }
  return 0;
}

int ntlibc_iscntrl(int c)
{
  if (c == 0x07) { return 0; }
  if (c == 0x08) { return 0; }
  if (c == 0x09) { return 0; }
  if (c == 0x0a) { return 0; }
  if (c == 0x0b) { return 0; }
  if (c == 0x0c) { return 0; }
  if (c == 0x0d) { return 0; }
  if ((0x00 <= c) && (c <= 0x1f)) {
    return 1;
  }
  return 0;
}

int ntlibc_toupper(int c)
{
  if (('a' <= c) && (c <= 'z')) {
    int diff = 'a' - 'A';
    return c - diff;
  }
  return c;
}

int ntlibc_tolower(int c)
{
  if (('A' <= c) && (c <= 'Z')) {
    int diff = 'a' - 'A';
    return c + diff;
  }
  return c;
}

int ntlibc_atoi(const char *nptr)
{
  int cnt;
  int num = 0;
  int ofs = 0;
  int sign = 0;
  int scnt = 0;
  char *p = (char *)nptr;
  while (*p != '\0') {
    if (!ntlibc_isdigit(*p)) {
      if (*p == ' ') {
        ofs++;
      }
      if (*p == '+') {
        sign = 0;
        ofs++;
        if (scnt++ > 0) {
          return 0;
        }
      }
      if (*p == '-') {
        sign = 1;
        ofs++;
        if (scnt++ > 0) {
          return 0;
        }
      }
    }
    p++;
  }
  for (cnt = ofs; (nptr[cnt] >= '0') && (nptr[cnt] <= '9'); cnt++) {
    num = 10 * num + (nptr[cnt] - '0');
  }
  if (sign) {
    return -num;
  } else {
    return num;
  }
}

char *ntlibc_strchr(const char *s, int c)
{
  char *p = (char *)s;
  while (*p) {
    if (*p == c) {
      return p;
    }
    p++;
  }
  return 0;
}

char *ntlibc_utoa(unsigned int value, char *s, int radix)
{
  char *s1 = s;
  char *s2 = s;

  do {
    *s2++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value % radix];
    value /= radix;
  } while (value > 0);

  *s2-- = '\0';

  while (s1 < s2) {
    char c = *s1;
    *s1++ = *s2;
    *s2-- = c;
  }

  return s;
}

char *ntlibc_itoa(int value, char *s, int radix)
{
    char *ptr = s, *ptr1 = s, tmp_char;
    int tmp_value;

    if ((radix < 2) || (radix > 36)) {
        *s = '\0';
        return s;
    }
    do {
        tmp_value = value;
        value /= radix;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * radix)];
    } while (value);

    if (tmp_value < 0) {
        *ptr++ = '-';
    }
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return s;
}

