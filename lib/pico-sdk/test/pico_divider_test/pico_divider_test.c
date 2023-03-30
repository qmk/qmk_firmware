// make test-div64_64.bin && qemu-system-arm -M lm3s6965evb -cpu cortex-m3 -nographic -serial null -monitor null -semihosting -kernel test-div64_64.bin
#include <stdio.h>
#include <math.h>
#include "pico/divider.h"
#include "pico/stdlib.h"

#ifdef TURBO
#include "hardware/vreg.h"
#endif

typedef uint64_t ui64;
typedef int64_t i64;
typedef uint32_t ui32;
typedef int32_t i32;

void test_mulib_divu64u64(ui64*y,ui64*x,ui64*q,ui64*r) {
    *q = divmod_u64u64_rem(*y, *x, r);
}
void test_mulib_divs64s64( i64*y, i64*x, i64*q, i64*r) {
    *q = divmod_s64s64_rem(*y, *x, r);
}

ui32 hwdiv_data[4];

void hwdiv_sim() {
  hwdiv_data[2]=hwdiv_data[0]/hwdiv_data[1];
  hwdiv_data[3]=hwdiv_data[0]%hwdiv_data[1];
//  ostr("HWS: ");
//  o8hex(hwdiv_data[0]); osp();
//  o8hex(hwdiv_data[1]); osp();
//  o8hex(hwdiv_data[2]); osp();
//  o8hex(hwdiv_data[3]); onl();
}

ui64 ntests=0;


#ifdef uart_default
void o1ch(int c) {
    uart_putc(uart_default, c);
}

void ostr(char*p) { while(*p) o1ch(*p++); }
void onl() {ostr("\r\n");}
void osp() {o1ch(' ');}
void ostrnl(char*p) { ostr(p); onl();}
void o1hex(int u) {u&=0x0f; if(u>=10) o1ch(u-10+'A'); else o1ch(u+'0');}
void o2hex(int u) {o1hex(u>> 4); o1hex(u);}
void o4hex(int u) {o2hex(u>> 8); o2hex(u);}
void o8hex(int u) {o4hex(u>>16); o4hex(u);}
void o16hex(ui64 u) {o8hex(u>>32); o8hex(u);}
unsigned int odig(unsigned int*pv,unsigned int d,int zf) {
    char c='0';
    unsigned int v=*pv;
    while(v>=d) v-=d,c++;
    if(zf==1&&c=='0') osp();
    else              o1ch(c),zf=0;
    *pv=v;
    return zf;
}

void odec(int u) {
    unsigned int v=u;
    int zf=1;
    if(u<0) o1ch('-'),v=-v;
    zf=odig(&v,1000000000,zf);
    zf=odig(&v,100000000,zf);
    zf=odig(&v,10000000,zf);
    zf=odig(&v,1000000,zf);
    zf=odig(&v,100000,zf);
    zf=odig(&v,10000,zf);
    zf=odig(&v,1000,zf);
    zf=odig(&v,100,zf);
    zf=odig(&v,10,zf);
    zf=odig(&v,1,0);
}
#endif


int xdigval(int c) {
  if(c>='0'&&c<='9') return c-'0';
  if(c>='A'&&c<='F') return c-'A'+10;
  if(c>='a'&&c<='f') return c-'a'+10;
  return -1;
}

ui64 seed;

ui64 rnd64() {
  if(seed&1) seed=(seed>>1)^0x800000000000000dULL;
  else       seed= seed>>1;
  return seed;
}

unsigned int rnd32() {
  return rnd64();
}

//#define RANDOMISE
//#define rfn "/dev/random"


#ifdef uart_default
void test_divu64u64(ui64 y,ui64 x) {
  ui64 q,r;
  test_mulib_divu64u64(&y,&x,&q,&r);
#if !PICO_ON_DEVICE
  if (!x) return;
#endif
  if(q==y/x&&r==y%x) ;
  else {
    ostr("U ");
    o16hex(y); osp();
    o16hex(x); osp();
    o16hex(q); osp();
    o16hex(r);
    ostr(" : ");
    o16hex(y/x); osp();
    o16hex(y%x); onl();
    }
  ntests++;
}

void test_divs64s64(i64 y,i64 x) {
  i64 q,r;
#if !PICO_ON_DEVICE
  if (y == INT64_MIN) return;
#endif
  test_mulib_divs64s64(&y,&x,&q,&r);
#if !PICO_ON_DEVICE
    if (!x) return;
#endif
  if(q==y/x&&r==y%x) ;
  else {
    ostr("S ");
    o16hex(y); osp();
    o16hex(x); osp();
    o16hex(q); osp();
    o16hex(r);
    ostr(" : ");
    o16hex(y/x); osp();
    o16hex(y%x); onl();
    }
  ntests++;
}


// for all x and y consisting of a single run of 1:s, test a region around (x,y)
void test_special() {
  int i0,j0,i1,j1,dy,dx;
  ui64 y,x;
  for(i0=0;i0<64;i0++) {
    y=0;
    for(i1=i0;i1<65;i1++) {
      for(j0=0;j0<64;j0++) {
        x=0;
        for(j1=j0;j1<65;j1++) {
#define A 2
          for(dy=-A;dy<=A;dy++) {
            for(dx=-A;dx<=A;dx++) {
              test_divu64u64( y+dy, x+dx);
              test_divs64s64( y+dy, x+dx);
              test_divs64s64( y+dy,-x-dx);
              test_divs64s64(-y-dy, x+dx);
              test_divs64s64(-y-dy,-x-dx);
              }
            }
          x|=1ULL<<j1;
          }
        }
      y|=1ULL<<i1;
      }
      odec(i0+1); ostr(" "); odec(i1+1); ostr(" specials\n");
    }
}

void test_random() {
  int i,j;
  ui64 y,x,m;
  for(i=0;;i++) {
    for(j=0;j<200000;j++) {
      m=1ULL<<(rnd32()%48+15); m+=m-1; y=rnd64()&m;
      m=1ULL<<(rnd32()%48+15); m+=m-1; x=rnd64()&m;
      test_divu64u64( y, x);
      test_divs64s64( y, x);
      test_divs64s64( y,-x);
      test_divs64s64(-y, x);
      test_divs64s64(-y,-x);
      }
    odec(i+1); ostr("M\n");
    }
}
#endif

uint32_t __attribute__((naked)) time_32(uint32_t a, uint32_t b, uint32_t (*func)(uint32_t a, uint32_t b)) {
    asm(
        ".syntax unified\n"
        "push {r4, r5, lr}\n"
        "ldr r4, =#0xe000e018\n"
        "ldr r5, [r4]\n"
        "blx r2\n"
        "ldr r0, [r4]\n"
        "subs r5, r0\n"
        "lsls r0, r5, #8\n"
        "asrs r0, #8\n"
        "pop {r4, r5, pc}\n"
    );
}

uint32_t __attribute__((naked)) time_64(uint64_t a, uint64_t b, uint64_t (*func64)(uint64_t a, uint64_t b)) {
    asm(
    ".syntax unified\n"
    "push {r4-r6, lr}\n"
    "ldr r6, [sp, #16]\n"
    "ldr r4, =#0xe000e018\n"
    "ldr r5, [r4]\n"
    "blx r6\n"
    "ldr r0, [r4]\n"
    "subs r5, r0\n"
    "lsls r0, r5, #8\n"
    "asrs r0, #8\n"
    "pop {r4-r6, pc}\n"
    );
}

uint32_t compiler_div_s32(uint32_t a, uint32_t b) {
    return ((int32_t)a) / (int32_t)b;
}

uint32_t pico_div_s32(uint32_t a, uint32_t b) {
    return div_s32s32(a, b);
}

uint32_t compiler_div_u32(uint32_t a, uint32_t b) {
    return a/b;
}

uint32_t pico_div_u32(uint32_t a, uint32_t b) {
    return div_u32u32(a, b);
}

uint64_t compiler_div_s64(uint64_t a, uint64_t b) {
    return ((int64_t)a) / (int64_t)b;
}

uint64_t pico_div_s64(uint64_t a, uint64_t b) {
    return div_s64s64(a, b);
}

uint64_t compiler_div_u64(uint64_t a, uint64_t b) {
    return a/b;
}

uint64_t pico_div_u64(uint64_t a, uint64_t b) {
    return div_u64u64(a, b);
}


void perf_test() {
    *(volatile unsigned int *)0xe000e010=5; // enable SYSTICK at core clock

    for(int bit = 30; bit>=0; bit--) {
        int div = 1u << (31-bit);
        const int N = 1000;
        int tc = 0, tp = 0;
        for (int i = 0; i < N; i++) {
            int a = rnd32();
            int b;
            do {
                b = rnd32() / div;
            } while (b == 0);
            tc += time_32(a, b, compiler_div_s32);
            tp += time_32(a, b, pico_div_s32);
        }
        printf("  S32 %d %f\t%f\n", bit, tc / 1000.0, tp / 1000.0);
    }

    for(int bit = 30; bit>=0; bit--) {
        int div = 1u << (31-bit);
        const int N = 1000;
        int tc = 0, tp = 0;
        for (int i = 0; i < N; i++) {
            int a = rnd32();
            int b;
            do {
                b = rnd32() / div;
            } while (b == 0);
            tc += time_32(a, b, compiler_div_u32);
            tp += time_32(a, b, pico_div_u32);
        }
        printf("  U32 %d %f\t%f\n", bit, tc / 1000.0, tp / 1000.0);
    }

    for(int extra = 0; extra <= 48; extra+=16)
    {
        for(int bit = 62; bit>=0; bit--) {
            int64_t div = 1ull << (62-bit);
            const int N = 1000;
            int tc = 0, tp = 0;
            for (int i = 0; i < N; i++) {
                int64_t a = rnd64() / (1u << extra);
                int64_t b;
                do {
                    b = ((int64_t)rnd64()) / div;
                } while (b == 0);
                tc += time_64(a, b, compiler_div_s64);
                tp += time_64(a, b, pico_div_s64);
            }
            printf("  S64 %d %d %f\t%f\n", extra, bit, tc / 1000.0, tp / 1000.0);
        }

        for(int bit = 62; bit>=0; bit--) {
            int64_t div = 1ull << (62-bit);
            const int N = 1000;
            int tc = 0, tp = 0;
            for (int i = 0; i < N; i++) {
                uint64_t a = rnd64();
                uint64_t b;
                do {
                    b = rnd64() / div;
                } while (b == 0);
                tc += time_64(a, b, compiler_div_u64);
                tp += time_64(a, b, pico_div_u64);
            }
            printf("  U64 %d %d %f\t%f\n", extra, bit, tc / 1000.0, tp / 1000.0);
        }
    }
}

int main() {
#ifndef uart_default
#warning test/pico_divider requires a default uart
#else
#ifdef TURBO
    vreg_set_voltage(VREG_VOLTAGE_MAX);
    set_sys_clock_khz(48000*8, true);
#endif
    setup_default_uart();
#ifdef RANDOMISE
  int u;
  ifh=sys_host(SYS_OPEN,(int)rfn,0,strlen(rfn));
  u=sys_host(SYS_READ,ifh,(int)&seed,sizeof(seed));
  if(u) {ostrnl("Error reading random stream"); return 16;}
  sys_host(SYS_CLOSE,ifh,0,0);
#else
  seed=12233524287791987605ULL;
#endif
  perf_test();
  ostr("begin\n");
  test_divu64u64( 38, 6);
  test_divs64s64( 38, 6);
  test_divs64s64( 38,-6);
  test_divs64s64(-38, 6);
  test_divs64s64(-38,-6);
  test_divu64u64(1234567890123ULL,6);
  test_divu64u64(0x0000000100000000ULL,6);
  test_divu64u64(0xffffffffffffffffULL,6);
  test_special();
  o16hex(ntests);
  ostr(" special tests done; starting random tests\n");
  test_divu64u64(0xf123456789abcdefULL,0x0000000100000000ULL);
  test_divu64u64(0xf123456789abcdefULL,0x00000001ffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x00000003ffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x00000007ffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x0000000fffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x0000001fffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x0000003fffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x0000007fffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x000000ffffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x000001ffffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x000003ffffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x000007ffffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x00000fffffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x00001fffffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x00003fffffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x00007fffffffffffULL);
  test_divu64u64(0xf123456789abcdefULL,0x0000ffffffffffffULL);

  test_random();

  ostr("END\n");
  return 0;
#endif
}

