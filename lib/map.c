#include "map.h"
#include "basic.h"

char **g_arrMap     = NULL;

int g_nMapWidth     = 0;
int g_nMapHeight    = 0;

static void setMapWidth( int nWidth )
{
    g_nMapWidth = nWidth;
}

static void setMapHeight( int nHeight )
{
    g_nMapHeight = nHeight;
}

int getMapWidth( void )
{
    return g_nMapWidth;
}

int getMapHeight( void )
{
    return g_nMapHeight;
}

BOOL CreateMap( void )
{
    if( g_arrMap ) {
        TRACE("already exist map.\n");
        return TRUE;
    }

    g_arrMap = (char **)malloc(sizeof(char *) * DEFAULT_MAP_HEIGHT);

    if( !g_arrMap ) {
        ERROR_TRACE("malloc failed.\n");
        return FALSE;
    }

    for( int i=0; i < DEFAULT_MAP_HEIGHT; i++ ) {
        g_arrMap[i] = (char *)malloc(sizeof(char) * DEFAULT_MAP_WIDTH);
        if( !g_arrMap[i] ) {
            ERROR_TRACE("malloc failed.\n");
            return FALSE;    
        }
    }

    setMapWidth( DEFAULT_MAP_WIDTH );
    setMapHeight( DEFAULT_MAP_HEIGHT );

    TRACE("CreateMap Done [ %d x %d ]\n", DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);

    return TRUE;
}

BOOL CreateMapCustomSize( int nWidth, int nHeight )
{
    if( g_arrMap ) {
        TRACE("already exist map.\n");
        return TRUE;
    }

    g_arrMap = (char **)malloc(sizeof(char *) * nHeight);

    if( !g_arrMap ) {
        ERROR_TRACE("malloc failed.\n");
        return FALSE;
    }

    for( int i=0; i < nHeight; i++ ) {
        g_arrMap[i] = (char *)malloc(sizeof(char) * nWidth);
        if( !g_arrMap[i] ) {
            ERROR_TRACE("malloc failed.\n");
            return FALSE;    
        }
    }

    setMapWidth( nWidth );
    setMapHeight( nHeight );

    TRACE("CreateMap Done [ %d x %d ]\n", nWidth, nHeight);

    return TRUE;
}

void DestroyMap( void )
{
    if( g_arrMap != NULL ) {
        for( int i=0; i < getMapHeight(); i++ ) {
            free( g_arrMap[i] );
            g_arrMap[i] = NULL;
        }

        free( g_arrMap );
        g_arrMap = NULL;
    }

    TRACE("DestroyMap Done\n");
}

void testSet()
{
    int count = 0;
    for( int i = 0; i<getMapHeight(); i++ ) {
        for( int j = 0; j<getMapWidth(); j++ ) {
            g_arrMap[i][j] = count++;
        }
    }
}

void testGet()
{
    for( int i = 0; i<getMapHeight(); i++ ) {
        for( int j = 0; j<getMapWidth(); j++ ) {
            printf("[%2d] ", g_arrMap[i][j]);
        }
        printf("\n");
    }    
}