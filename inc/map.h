#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>

#include "type.h"

#define DEFAULT_MAP_WIDTH   10
#define DEFAULT_MAP_HEIGHT  10

int  getMapWidth( void );
int  getMapHeight( void );
BOOL CreateMap( void );
BOOL CreateMapCustomSize( int nWidth, int nHeight );
void DestroyMap( void );

void testSet();
void testGet();

#endif