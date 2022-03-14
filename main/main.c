#include "key.h"
#include "map.h"
#include "basic.h"

#define MAX_TEST 5

// Example
int main()
{
    int count = 0;
    int insert_key = 0;

    CreateMap();
    CreateMapCustomSize(5, 5);

    testSet();
    testGet();

    while( count < MAX_TEST ) {
        // ascii 문자열 숫자값 return : 'a' -> 97, 'b' -> 98, '1' -> 49
        insert_key = key();

        switch(insert_key)
        {
        case KEY_UP:
            printf("KEY_UP\n");
            break;

        case KEY_DOWN:
            printf("KEY_DOWN\n");
            break;

        case KEY_RIGHT:
            printf("KEY_RIGHT\n");
            break;

        case KEY_LEFT:
            printf("KEY_LEFT\n");
            break;

        case KEY_ENTER:
            printf("KEY_ENTER\n");
            break;

        case KEY_SPACEBAR:
            printf("KEY_SPACEBAR\n");
            break;

        case KEY_ESC:
            printf("KEY_ESC\n");
            break;

        default:
            // insert_key == 2 아님! (아스키값이므로 char값 비교)
            if( insert_key == '2' ) {
                printf("2가 입력되었습니다.\n");
                break;
            }

            else if( insert_key == 'x' ) {
                printf("x 키가 입력되었습니다.\n");
                break;
            }

            else{
                printf("[ %c ]\n", insert_key);
                break;
            }
        }
        count++;
    }

    DestroyMap();

    return 0;
}