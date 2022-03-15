#ifndef _USER_H_
#define _USER_H_

#include "basic.h"
#include "type.h"

#define DIR_DEFAULT 0
#define DIR_UP      65
#define DIR_DOWN    66
#define DIR_RIGHT   67
#define DIR_LEFT    68

typedef struct _tUSER_
{
    COORD coord;
    TILE  curTile;
    int   userDirection;
} USER, *PUSER;

BOOL CreateUser( void );
BOOL Move( int nDirection );

#endif