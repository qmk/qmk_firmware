#include "cmsis.h"
#include <sys/types.h>
#include <errno.h>

extern "C" {

struct SCS3Regions {
    unsigned long   Dummy;
    unsigned long*  InitRam;
    unsigned long*  StartRam;
    unsigned long   InitSizeRam;
    unsigned long   ZeroSizeRam;
};

extern unsigned long __cs3_regions;
extern unsigned long __cs3_heap_start;

int  main(void);
void __libc_init_array(void);
void exit(int ErrorCode);

static void *heap_pointer = NULL;

void __cs3_start_c(void) {
    static SCS3Regions* pCS3Regions = (SCS3Regions*)&__cs3_regions;
    unsigned long* pulDest;
    unsigned long* pulSrc;
    unsigned long  ByteCount;
    unsigned long  i;
    
    pulSrc = pCS3Regions->InitRam;
    pulDest = pCS3Regions->StartRam;
    ByteCount = pCS3Regions->InitSizeRam;
    if (pulSrc != pulDest) {
        for(i = 0 ; i < ByteCount ; i += sizeof(unsigned long)) {
            *(pulDest++) = *(pulSrc++);
        }
    } else {
        pulDest = (unsigned long*)(void*)((char*)pulDest + ByteCount);
    }
    
    ByteCount = pCS3Regions->ZeroSizeRam;
    for(i = 0 ; i < ByteCount ; i += sizeof(unsigned long)) {
        *(pulDest++) = 0;
    }
    
    heap_pointer = &__cs3_heap_start;
     __libc_init_array();
    exit(main());
}

int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

void _exit(int status) {
    exit(status);
}

int _getpid(void) {
    return 1;
}

void *_sbrk(unsigned int incr) {
    void *mem;
    
    unsigned int next = ((((unsigned int)heap_pointer + incr) + 7) & ~7);
    if (next > __get_MSP()) {
        mem = NULL;
    } else {
        mem = (void *)heap_pointer;
    }
    heap_pointer = (void *)next;
    
    return mem;
}

}
