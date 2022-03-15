#include "user.h"
#include "map.h"
#include "type.h"
#include "tile.h"

USER *g_User = NULL;

BOOL CreateUser( void )
{
    if( getMapAddr() == NULL ) {
        ERROR_TRACE("Map Not Create!\n");
        return FALSE;
    }

    g_User = (USER *)malloc(sizeof(USER));

    if( g_User == NULL ) {
        ERROR_TRACE("malloc failed.\n");
        return FALSE;
    }

    g_User->coord.xPos = getMapWidth()  / 2;
    g_User->coord.yPos = getMapHeight() / 2;
    g_User->curTile    = SetMap( g_User->coord, USER_TILE );

    return TRUE;
}

BOOL CheckBorderLine( int nDirection )
{
    switch( nDirection )
    {
    case DIR_UP:
        if( g_User->coord.yPos == 1 ) 
            return TRUE;
        break;
    case DIR_DOWN:
        if( g_User->coord.yPos == getMapHeight() - 2 ) 
            return TRUE;
        break;
    case DIR_RIGHT:
        if( g_User->coord.xPos == getMapWidth() - 2 ) 
            return TRUE;
        break;
    case DIR_LEFT:
        if( g_User->coord.xPos == 1 ) 
            return TRUE;
        break;    
    default:
        break;
    }

    return FALSE;
}

BOOL Move( int nDirection )
{
    if( CheckBorderLine( nDirection ) == TRUE ) {
        setTitleString("Wall Crushed...", 0);
        return FALSE;
    }

    setTitleClean();

    SetMap( g_User->coord, g_User->curTile );

    switch( nDirection )
    {
    case DIR_UP:    g_User->coord.yPos--;   break;
    case DIR_DOWN:  g_User->coord.yPos++;   break;
    case DIR_RIGHT: g_User->coord.xPos++;   break;
    case DIR_LEFT:  g_User->coord.xPos--;   break;    
    default:                                break;
    }

    g_User->curTile = SetMap( g_User->coord, USER_TILE );

    return TRUE;
}