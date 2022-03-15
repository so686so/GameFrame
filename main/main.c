#include "key.h"
#include "map.h"
#include "basic.h"
#include "tile.h"
#include "user.h"

#define MAX_TEST 5

BOOL g_bTitle_n_Tail_onoff = TRUE;
BOOL g_bPopup = FALSE;

static char *translate( int nDirection ) {
        switch(nDirection)
        {
        case KEY_UP:        return "↑";
        case KEY_DOWN:      return "↓";
        case KEY_RIGHT:     return "→";
        case KEY_LEFT:      return "←";
        default:            return "??";
        }
}

// Example
int main()
{
    int insert_key = 0;
    BOOL isEnd = FALSE;

    char tailMsg[DEFAULT_MAP_WIDTH] = {0x00,};
    char msg[DEFAULT_MAP_WIDTH] = {0x00};

    system("clear");

    CreateMap();

    for( int i=1; i<DEFAULT_MAP_WIDTH-1; i++ ) {
        ShowMapDot(setCoord(i, i), 'A'+(i-1));
    }

    CreateUser();
    ShowMap();

    while( isEnd == FALSE ) {
        insert_key = key();

        switch(insert_key)
        {
        case KEY_UP:
        case KEY_DOWN:
        case KEY_RIGHT:
        case KEY_LEFT:
            if( g_bPopup == TRUE ) break;

            Move( insert_key );

            memset( tailMsg, 0x00, DEFAULT_MAP_WIDTH );
            snprintf( tailMsg, DEFAULT_MAP_WIDTH, "Move Direction : %s", translate(insert_key));

            setTailString( tailMsg, 0 );

            ShowMap();
            break;

        case KEY_SPACEBAR:
            if( g_bPopup == TRUE ) break;

            g_bTitle_n_Tail_onoff = !g_bTitle_n_Tail_onoff;
            SetTitleOpt( g_bTitle_n_Tail_onoff );
            SetTailOpt( g_bTitle_n_Tail_onoff );
            system("clear");
            ShowMap();
            break;

        case KEY_ESC:
            printf("Program QUIT.\n");
            isEnd = TRUE;
            break;

        case KEY_ENTER:
            if( g_bPopup == FALSE ) {
                g_bPopup = TRUE;

                ShowPopupMap();

                printf("Input Here : ");
                fgets(msg, DEFAULT_MAP_WIDTH, stdin);
                fflush(stdin);

                setTitleString(msg, 0);

                system("clear");
                ShowMap();
            }
            g_bPopup = FALSE;
            break;

        default:
            break;
        }
    }

    DestroyMap();

    return 0;
}