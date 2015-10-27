/* dbg.cpp */
/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "dbg.h"

#include "mbed.h"
#include "rtos.h"

#include <cstdio>
#include <cstdarg>

using namespace std;

static Serial debug_pc(USBTX, USBRX);

static char debug_newline[3];

static void debug_lock(bool set)
{
  static Mutex* mtx = new Mutex(); //Singleton runtime initialisation to avoid static initialisation chaos problems
  static bool init = false;
  if(set)
  {
    mtx->lock();
    if(!init)
    {
      strncpy( debug_newline, "\n", 2 );
      printf("[START]\n");
      fflush(stdout);
      init = true;
    }
  }
  else
  {
    mtx->unlock();
  }
}

void debug_init()
{
  debug_lock(true); //Force init
  debug_lock(false);
}

void debug_set_newline(const char* newline)
{
  debug_lock(true);
  strncpy( debug_newline, newline, 2 );
  debug_newline[2] = '\0';
  debug_lock(false);
}

void debug_set_speed(int speed)
{
  debug_pc.baud(speed);
}

void debug(int level, const char* module, int line, const char* fmt, ...)
{
  debug_lock(true);
  switch(level)
  {
  default:
  case 1:
    printf("[ERROR]");
    break;
  case 2:
    printf("[WARN]");
    break;
  case 3:
    printf("[INFO]");
    break;
  case 4:
    printf("[DBG]");
    break;
  }

  printf(" Module %s - Line %d: ", module, line);

  va_list argp;

  va_start(argp, fmt);
  vprintf(fmt, argp);
  va_end(argp);

  printf(debug_newline);

  fflush(stdout);

  debug_lock(false);

}

void debug_error(const char* module, int line, int ret)
{
  debug_lock(true);
  printf("[RC] Module %s - Line %d : Error %d\n", module, line, ret);
  fflush(stdout);
  debug_lock(false);
}

void debug_exact(const char* fmt, ...)
{
  debug_lock(true);
  va_list argp;

  va_start(argp, fmt);
  vprintf(fmt, argp);
  va_end(argp);
  debug_lock(false);
}
