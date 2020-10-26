#include <vector>
#include <iostream>
#include <curses.h>
#define DEAD " "
#define ALIVE "X"
using namespace std;

struct cell
{
    int state;
    int nCount;
};
//PROTOTYPES
void fill_arr(vector<vector<struct cell>> &);
int pausescrn(vector<vector<struct cell>> &, int &, int &, int &);
int printscrn(vector<vector<struct cell>> &);
int countadj(vector<vector<struct cell>>, int, int);
void updatemtrx(vector<vector<struct cell>> &);
int playscrn(vector<vector<struct cell>> &);
int set_nCount(vector<vector<struct cell>> &);









int main(void)
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    int curr_x = 0;
    int curr_y = 0;
    vector<vector<struct cell>> array;
    int key;
    fill_arr(array); 
    key = getch();

    do{
        key = pausescrn(array, key, curr_x, curr_y);
        if(key == (int)'p')
            key = playscrn(array);
    }while(key != (int)'q');

    endwin();

    return 0;
}










//FUNCTIONS
void fill_arr(vector<vector<struct cell>> &array)
{
    vector <struct cell> temp;
    for(int i = 0; i < LINES; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            temp.push_back(cell());
        }

        array.push_back(temp);
    }
    for(int i = 0; i < LINES; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            array[i][j].state = 0;
            array[i][j].nCount = 0;
        }
    }
}

int pausescrn(vector<vector<struct cell>> &array, int &key, int &curr_x, int &curr_y)
{
    do
    {
        switch(key)
        {
            case KEY_UP:
            if(curr_y > 0)
                wmove(stdscr, --curr_y, curr_x);
            break;

            case KEY_DOWN: 
            if(curr_y < LINES-1)
                wmove(stdscr, ++curr_y, curr_x);
            break;
            
            case KEY_LEFT:
            if(curr_x > 0)
                wmove(stdscr, curr_y, --curr_x);
            break;
            
            case KEY_RIGHT:
            if(curr_x < COLS-1)
                wmove(stdscr, curr_y, ++curr_x);
            break;

            case (int)'x':
            if(array[curr_y][curr_x].state == 0)
                array[curr_y][curr_x].state = 1;
            else if(array[curr_y][curr_x].state == 1)
                array[curr_y][curr_x].state = 0;
            break;

            case (int)'n':
            updatemtrx(array);
            return 0;
            break;
        }
    wrefresh(stdscr);
    printscrn(array);
    key = mvgetch(curr_y, curr_x);
    }while(key != (int)'p' && key != (int)'q');

    return key;
}

int printscrn(vector<vector<struct cell>> &array)
{
    for(int i = 0; i < LINES; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(array[i][j].state == 1)
                mvprintw(i , j, ALIVE);
            else
                mvprintw(i ,j , DEAD);
        }
    }

    wrefresh(stdscr);
    return 0;
}

int countadj(vector<vector<struct cell>> array, int y, int x)
{
    int sum = 0;
     if(y == 0 || y == LINES-1 || x == 0 || x == COLS-1)
                return 0;
    if(array[y-1][x].state == 1)
        ++sum;
    if(array[y-1][x-1].state == 1)
        ++sum;
    if(array[y-1][x+1].state == 1)
        ++sum;
    if(array[y][x+1].state == 1)
        ++sum; 
    if(array[y][x-1].state == 1)
        ++sum;
    if(array[y+1][x+1].state == 1)
        ++sum;
    if(array[y+1][x].state == 1)
        ++sum;
    if(array[y+1][x-1].state == 1)
        ++sum;
    return sum;
}

void updatemtrx(vector<vector<struct cell>> &array)
{
    set_nCount(array);
    for(int i = 0; i < LINES; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(i == 0 || i == LINES-1 || j == 0 || j == COLS-1)
                array[i][j].state = 0;
            else
            {
            if(array[i][j].state == 0 && array[i][j].nCount == 3)
                array[i][j].state = 1;
            else if(array[i][j].state == 1 && (array[i][j].nCount < 2 || array[i][j].nCount > 3))
                array[i][j].state = 0;
            }
        }

    }
}

int playscrn(vector<vector<struct cell>> &array)
{
    int key;
    do{
       updatemtrx(array);
       printscrn(array);
       wrefresh(stdscr);
       key = getch();
    }while(key != (int)'p' && key != (int)'q');
    return key;
}

int set_nCount(vector<vector<struct cell>> &array)
{
    for(int i = 0; i < LINES; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(i == 0 || i == LINES-1 || j == 0 || j == COLS-1)
                array[i][j].nCount = 0;
            else
                array[i][j].nCount = countadj(array, i, j);
        }
    }
    return 0;
}
