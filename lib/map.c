#include "map.h"
#include "basic.h"
#include "tile.h"

TILE **g_arrMap     = NULL;

BOOL g_bSetBorder   = TRUE;
BOOL g_bSetTitle    = TRUE;
BOOL g_bSetTail     = TRUE;

int  g_nMapWidth    = 0;
int  g_nMapHeight   = 0;

char **g_strTitle   = NULL;
char **g_strTail    = NULL;

static int getStartHeight( void );
static int getEndHeight( void );

TILE **getMapAddr( void )
{
    return g_arrMap;
}

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

int getMapArea( void )
{
    return g_nMapWidth * g_nMapHeight;
}

void SetBorderOpt( BOOL bOn )
{
    g_bSetBorder = bOn;
}

void SetTitleOpt( BOOL bOn )
{
    g_bSetTitle = bOn;
}

void SetTailOpt( BOOL bOn )
{
    g_bSetTail = bOn;
}

BOOL isUseBorder( void )
{
    return g_bSetBorder;
}

static BOOL CreateStringTable( void )
{
    int i;

    if( g_bSetTitle == TRUE ) {
        g_strTitle = (char **)malloc(sizeof(char *) * (TITLE_HEIGHT));

        if( g_strTitle == NULL ) {
            ERROR_TRACE("malloc failed.\n");
            return FALSE;
        }

        for( i=0; i<TITLE_HEIGHT; i++ ) {
            g_strTitle[i] = (char*)malloc( getMapWidth() );
            if( g_strTitle[i] == NULL ) {
                ERROR_TRACE("malloc failed.\n");
                return FALSE;                
            }
        }
    }

    if( g_bSetTail == TRUE ) {
        g_strTail = (char **)malloc(sizeof(char *) * (TAIL_HEIGHT));

        if( g_strTail == NULL ) {
            ERROR_TRACE("malloc failed.\n");
            return FALSE;
        }

        for( i=0; i<TAIL_HEIGHT; i++ ) {
            g_strTail[i] = (char*)malloc( getMapWidth() );
            if( g_strTail[i] == NULL ) {
                ERROR_TRACE("malloc failed.\n");
                return FALSE;                
            }
        }
    }

    return TRUE;
}

BOOL CreateMap( void )
{
    if( g_arrMap ) {
        TRACE("already exist map.\n");
        return TRUE;
    }

    g_arrMap = (TILE **)malloc(sizeof(TILE *) * DEFAULT_MAP_HEIGHT);

    if( !g_arrMap ) {
        ERROR_TRACE("malloc failed.\n");
        return FALSE;
    }

    for( int i=0; i < DEFAULT_MAP_HEIGHT; i++ ) {
        g_arrMap[i] = (TILE *)malloc(sizeof(TILE) * DEFAULT_MAP_WIDTH);
        if( !g_arrMap[i] ) {
            ERROR_TRACE("malloc failed.\n");
            return FALSE;    
        }
    }

    setMapWidth( DEFAULT_MAP_WIDTH );
    setMapHeight( DEFAULT_MAP_HEIGHT );

    InitMap();

    if( CreateStringTable() == FALSE ) {
        ERROR_TRACE("malloc failed.\n");
        return FALSE;
    }

    gotoxy( setCoord( 0, getEndHeight() ) );
    TRACE("CreateMap Done [ %d x %d ]\n", DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);

    return TRUE;
}

BOOL CreateMapCustomSize( int nWidth, int nHeight )
{
    if( g_arrMap ) {
        TRACE("already exist map.\n");
        return TRUE;
    }

    g_arrMap = (TILE **)malloc(sizeof(TILE *) * nHeight);

    if( !g_arrMap ) {
        ERROR_TRACE("malloc failed.\n");
        return FALSE;
    }

    for( int i=0; i < nHeight; i++ ) {
        g_arrMap[i] = (TILE *)malloc(sizeof(TILE) * nWidth);
        if( !g_arrMap[i] ) {
            ERROR_TRACE("malloc failed.\n");
            return FALSE;    
        }
    }

    setMapWidth( nWidth );
    setMapHeight( nHeight );

    InitMap();

    if( CreateStringTable() == FALSE ) {
        ERROR_TRACE("malloc failed.\n");
        return FALSE;
    }

    gotoxy( setCoord( 0, getEndHeight() ) );
    TRACE("CreateMap Done [ %d x %d ]\n", nWidth, nHeight);

    return TRUE;
}

void DrawMapBorder( void )
{
    SetMap_Row( 0,                HLINE );
    SetMap_Row( getMapHeight()-1, HLINE );
    SetMap_Col( 0,                VLINE );
    SetMap_Col( getMapWidth()-1,  VLINE );

    SetMap( setCoord( 0,               0 ),                UPPER_LEFT_EDGE  );
    SetMap( setCoord( getMapWidth()-1, 0 ),                UPPER_RIGHT_EDGE );
    SetMap( setCoord( 0,               getMapHeight()-1 ), UNDER_LEFT_EDGE  );
    SetMap( setCoord( getMapWidth()-1, getMapHeight()-1 ), UNDER_RIGHT_EDGE );
}

void InitMap( void )
{
    ResetMap();

    if( g_bSetBorder == TRUE ) {
        DrawMapBorder();
    }
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

    if( g_strTitle != NULL ) {
        for( int i=0; i < TITLE_HEIGHT; i++ ) {
            free( g_strTitle[i] );
            g_strTitle[i] = NULL;
        }

        free( g_strTitle );
        g_strTitle = NULL;        
    }

    if( g_strTail != NULL ) {
        for( int i=0; i < TAIL_HEIGHT; i++ ) {
            free( g_strTail[i] );
            g_strTail[i] = NULL;
        }

        free( g_strTail );
        g_strTail = NULL;        
    }

    TRACE("DestroyMap Done\n");
}

void ResetMap( void )
{
    for( int i = 0; i<getMapHeight(); i++ ) {
        for( int j = 0; j<getMapWidth(); j++ ) {
            g_arrMap[i][j] = 0x00;
        }
    }    
}

TILE SetMap( COORD coord, TILE newValue )
{
    if( g_arrMap == NULL ) {
        return -1;
    }

    TILE oldValue = g_arrMap[coord.yPos][coord.xPos];

    g_arrMap[coord.yPos][coord.xPos] = newValue;

    return oldValue;
}

BOOL SetMap_Row( int nRow, TILE newValue )
{
    if( g_arrMap == NULL ) {
        return FALSE;
    }

    for( int i = 0; i<getMapWidth(); i++ ) {
        g_arrMap[nRow][i] = newValue;
    }

    return TRUE;
}

BOOL SetMap_Col( int nCol, TILE newValue )
{
    if( g_arrMap == NULL ) {
        return FALSE;
    }

    for( int i = 0; i<getMapHeight(); i++ ) {
        g_arrMap[i][nCol] = newValue;
    }

    return TRUE;
}

static void DrawTile( TILE value )
{
    switch( value )
    {
    case VLINE:
        printf(" │ ");
        break;
    case HLINE:
        printf("───");
        break;
    case UPPER_RIGHT_EDGE:
        printf("─┐ ");
        break;
    case UPPER_LEFT_EDGE:
        printf(" ┌─");
        break;
    case UNDER_RIGHT_EDGE:
        printf("─┘ ");
        break;
    case UNDER_LEFT_EDGE:
        printf(" └─");
        break;
    case EMPTY_TILE:
        printf("   ");
        break;
    case USER_TILE:
        printf(" ● ");
        break;
    default:
        printf("%2c ", value);
        break;
    }
}

static int _getStartHeight( void )
{
    return (g_bSetTitle) ? TITLE_HEIGHT+1 : 0;
}

static int _getEndHeight( void )
{
    return (g_bSetTitle) ? getMapHeight() + (TITLE_HEIGHT+2) : getMapHeight() + 1;
}

static int getStartHeight( void )
{
    return _getStartHeight();
}

static int getEndHeight( void )
{
    return (g_bSetTail) ? _getEndHeight() + (TAIL_HEIGHT+1) : _getEndHeight();
}

static void DrawEachLine( char* leftEdge, char* middle, char* rightEdge )
{
    printf("%s", leftEdge);
    for(int i=0; i<getMapWidth()-2; i++) {
        printf("%s", middle);
    }
    printf("%s\n", rightEdge);
}

static void DrawSmallLine( char* leftEdge, char* middle, char* rightEdge )
{
    printf("\x1b[1;36m");
    printf("%s", leftEdge);
    for(int i=0; i<(getMapWidth()/2); i++) {
        printf("%s", middle);
    }
    printf("%s\n", rightEdge);
    printf("\x1b[0m");
}

static void DrawTitle( void )
{
    if(g_bSetTitle == FALSE) return;

    gotoxy( setCoord( 0, 0 ) );

    DrawEachLine(" ┌─", "───", "─┐ ");

    for( int i=0; i < TITLE_HEIGHT; i++ ) {
    DrawEachLine(" │ " ,   "   " ,  " │ ");
    }

    DrawEachLine(" ├─", "───" ,"─┤ ");

    gotoxy( setCoord( 0, getEndHeight() ) );
}

static void DrawTail( void )
{
    if(g_bSetTail == FALSE) return;

    gotoxy( setCoord( 0, _getEndHeight()-2 ) );

    DrawEachLine(" ├─", "───" ,"─┤ ");

    for( int i=0; i < TAIL_HEIGHT; i++ ) {
    DrawEachLine(" │ " ,   "   " ,  " │ ");
    }

    DrawEachLine(" └─", "───", "─┘ ");

    gotoxy( setCoord( 0, getEndHeight() ) );    
}

void ShowString( void ) {
    if( g_bSetTitle == TRUE && g_strTitle != NULL ) {
        for( int i=0; i<TITLE_HEIGHT; i++ ) {
            if( g_strTitle[i] != NULL ) {
                gotoxy( setCoord( 2, 1+i ) );
                printf("%s\n", g_strTitle[i]);
            }
        }
    }

    if( g_bSetTail == TRUE && g_strTail != NULL ) {
        for( int i=0; i<TAIL_HEIGHT; i++ ) {
            if( g_strTail[i] != NULL ) {
                gotoxy( setCoord( 2, (_getEndHeight()-1)+i ) );
                printf("%s\n", g_strTail[i]);
            }
        }
    }
    gotoxy( setCoord( 0, getEndHeight() ) );         
}

void ShowMap( void )
{
    gotoxy( setCoord( 0, getStartHeight() ) );
    for( int i = 0; i<getMapHeight(); i++ ) {
        for( int j = 0; j<getMapWidth(); j++ ) {
            DrawTile( g_arrMap[i][j] );
        }
        printf("\n");
    }
    gotoxy( setCoord( 0, getEndHeight() ) );

    DrawTitle();
    DrawTail();
    ShowString();
}

void ShowMapDot( COORD coord, TILE newValue )
{
    SetMap( coord, newValue );

    coord.yPos += getStartHeight();

    gotoxy( coord );
    DrawTile( newValue );

    gotoxy( setCoord( 0, getEndHeight() ) );
}

void setTitleString( char* string, int nIdx )
{
    if( g_bSetTitle == FALSE || g_strTitle == NULL ) return;

    snprintf( g_strTitle[nIdx], getMapWidth(), "%s", string );
}

void setTitleClean( void )
{
    if( g_bSetTitle == FALSE || g_strTitle == NULL ) return;

    for( int i=0; i<TITLE_HEIGHT; i++) {
        gotoxy( setCoord( 2, 1+i ) );

        snprintf( g_strTitle[i], getMapWidth(), " " );

        for( int j=0; j<getMapWidth()-2; j++) {
            printf(" ");
        }
    }

    gotoxy( setCoord( 0, getEndHeight() ) );   
}

void setTailString( char* string, int nIdx )
{
    if( g_bSetTail == FALSE || g_strTail == NULL ) return;

    snprintf( g_strTail[nIdx], getMapWidth(), "%s", string);
}

void setTailClean( void )
{
    if( g_bSetTail == FALSE || g_strTail == NULL ) return;


    for( int i=0; i<TAIL_HEIGHT; i++) {
        gotoxy( setCoord( 2, (_getEndHeight()-1)+i ) );

        snprintf( g_strTail[i], getMapWidth(), " " );

        for( int j=0; j<getMapWidth()-2; j++) {
            printf(" ");
        }
    }

    gotoxy( setCoord( 0, getEndHeight() ) );    
}

void ShowPopupMap( void )
{
    int totalRow = 8;
    int startRow = ( getMapWidth() / 2 ) - 5;
    int startCol = ( getMapHeight() / 2 ) - totalRow/2;

    gotoxy( setCoord( startRow, startCol ) );

    DrawSmallLine(" ┌─", "───", "─┐ ");

    for( int i=1; i < totalRow; i++ ) {
    gotoxy( setCoord( startRow, startCol+i ) );
    DrawSmallLine(" │ " ,   "   " ,  " │ ");
    }
    
    gotoxy( setCoord( startRow, startCol+totalRow-1 ) );
    DrawSmallLine(" └─", "───", "─┘ ");

    gotoxy( setCoord( startRow+1, startCol+1 ) );
    printf("\x1b[1;36mPlease input to Show Title...\n\x1b[0m");

    gotoxy( setCoord( startRow+1, startCol+3 ) );
}
