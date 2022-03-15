#ifndef _BASIC_H_
#define _BASIC_H_

#include <stdio.h>

#define DEBUG

#define ERROR_TRACE(x) printf("[ %s -> %s ( %d Line ) ] %s", __FILE__, __func__, __LINE__, (x))

#ifdef DEBUG
    #define TRACE(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define TRACE(fmt, ...)
#endif

typedef struct _tCOORD_
{
    int xPos;
    int yPos;
} COORD, *PCOORD;

COORD setCoord( int xPos, int yPos );
void  gotoxy( COORD coord );

#endif