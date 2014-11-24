/***************************************************************************
* https://github.com/dhylands/projects/blob/master/lpc/lpc-vector-checksum/lpc-vector-checksum.c
*
*     Copyright (c) 2012 by Dave Hylands
*           All Rights Reserved
*
*	Permission is granted to any individual or institution to use, copy,
*  modify, or redistribute this file so long as it is not sold for profit,
*  and that this copyright notice is retained.
*
***************************************************************************
*
*  This program calculates the vector checksum used in LPC17xx binary
*  images.
*
*  Usage:   lpc-vector-checksum file
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

/***************************************************************************/
/**
*   update_vector_checksum
*  
*   The algorithim is to write the checksum such that the checksum of the
*   first 8 words is equal to zero.
*  
*   The LPC1768 uses little-endian, and this particular routine assumes
*   that it's running on a little-endian architecture.
*/
static int update_vector_checksum( const char *filename )
{
    uint32_t    sum;
    uint32_t    header[8];
    FILE       *fs;
    int         i;

    if (( fs = fopen( filename, "r+b" )) == NULL )
    {
        fprintf( stderr, "Unable to open '%s' for reading/writing (%d): %s\n", 
                 filename, errno, strerror( errno ));
        return 0;
    }

    if ( fread( header, sizeof( header ), 1, fs ) != 1 )
    {
        fprintf( stderr, "Failed to read header from '%s' (perhaps the file is too small?)",
                 filename );
        fclose( fs );
        return 0;
    }

    sum = 0;
    for ( i = 0; i < 7; i++ )
    {
        sum += header[i];
    }
    printf( "sum = 0x%08x, value to write = 0x%08x\n", sum, -sum );

    /* write back the checksum to location 7
     * http://sigalrm.blogspot.jp/2011/10/cortex-m3-exception-vector-checksum.html
     */
    fseek(fs, 0x1c, SEEK_SET);
    sum = -sum;
    fwrite(&sum, 4, 1, fs);

    fclose( fs );

    return 1;
}

/***************************************************************************/
/**
*   main
*/
int main( int argc, char **argv )
{
    int arg;

    if ( argc < 2)
    {
        fprintf( stderr, "Usage: lpc-vector-checksum file ...\n" );
        exit( 1 );
    }

    for ( arg = 1; arg < argc; arg++ )
    {
        update_vector_checksum( argv[ arg ]);
    }

    exit( 0 );
    return 0;
}

