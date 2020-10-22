#include <curses.h>
#define DEAD " ";
#define ALIVE "X"

int main(void)
{
    initscr();
    int array[LINES][COLS];
    
    for(int i = 0; i < LINES; ++i)
    {
        for(int j = 0; j < COLS; ++j)
            array[i][j] = 0;
    }
    mvprintw(3,0,"%d", array[3][0]);
    refresh();
    getch();
    endwin();

    return 0;
}


