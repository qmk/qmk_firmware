/* mbed Microcontroller Library - MemFileSystem
 * Copyright (c) 2008, sford
 */


#ifndef MBED_MEMFILESYSTEM_H
#define MBED_MEMFILESYSTEM_H

#include "FATFileSystem.h"

namespace mbed
{

    class MemFileSystem : public FATFileSystem
    {
    public:
    
        // 2000 sectors, each 512 bytes (malloced as required)
        char *sectors[2000];
    
        MemFileSystem(const char* name) : FATFileSystem(name) {
            memset(sectors, 0, sizeof(sectors));
        }
    
        virtual ~MemFileSystem() {
            for(int i = 0; i < 2000; i++) {
                if(sectors[i]) {
                    free(sectors[i]);
                }
            }
        }
    
        // read a sector in to the buffer, return 0 if ok
        virtual int disk_read(char *buffer, int sector) {
            if(sectors[sector] == 0) {
                // nothing allocated means sector is empty
                memset(buffer, 0, 512);
            } else {
                memcpy(buffer, sectors[sector], 512);
            }
            return 0;
        }
    
        // write a sector from the buffer, return 0 if ok
        virtual int disk_write(const char *buffer, int sector) {
            // if buffer is zero deallocate sector
            char zero[512];
            memset(zero, 0, 512);
            if(memcmp(zero, buffer, 512)==0) {
                if(sectors[sector] != 0) {
                    free(sectors[sector]);
                    sectors[sector] = 0;
                }
                return 0;
            }
            // else allocate a sector if needed, and write
            if(sectors[sector] == 0) {
                char *sec = (char*)malloc(512);
                if(sec==0) {
                    return 1; // out of memory
                }
                sectors[sector] = sec;
            }
            memcpy(sectors[sector], buffer, 512);
            return 0;
        }
    
        // return the number of sectors
        virtual int disk_sectors() {
            return sizeof(sectors)/sizeof(sectors[0]);
        }
    
    };

}

#endif