#include <curses.h>

int main(void)
{
    initscr();
    keypad(stdscr, TRUE);
    

    refresh();
    getch();
    endwin();
    return 0;
}
