#include "basic.h"
#include "type.h"

void gotoxy( COORD coord )
{
    printf("\033[%d;%df",coord.yPos+1, coord.xPos*TILE_WIDTH);
}

COORD setCoord( int xPos, int yPos )
{
    COORD coord = { xPos, yPos };

    return coord;
}