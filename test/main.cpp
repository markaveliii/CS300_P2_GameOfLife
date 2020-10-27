#include <curses.h>

int main()
{
    initscr();
    WINDOW *nw = newwin(LINES, COLS, 0, 0);
    printw("Hello");
    getch();
    refresh();
    wprintw(nw, "       Hello");
    wrefresh(nw);
    getch();
    endwin();
    return 0;
}
