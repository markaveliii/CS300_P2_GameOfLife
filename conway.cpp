#include <vector>
#include <iostream>
#include <curses.h>
#define DEAD " ";
#define ALIVE "X"
using namespace std;

const int start_x = COLS/2;
const int start_y = LINES/2;

void fill_arr(vector<vector<int>> &);
int pausescrn(vector<vector<int>> &, int &, int &, int &);
int printscrn(vector<vector<int>> &, int, int);


int main(void)
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    int curr_x = 0;
    int curr_y = 0;
    vector<vector<int>> array;
    int key;

    fill_arr(array); 
    key = getch();
    pausescrn(array, key, curr_x, curr_y);
    endwin();

    return 0;
}

void fill_arr(vector<vector<int>> &array)
{
    for(int i = 0; i < LINES; i++)
    {
        vector<int>temp;
        for(int j = 0; j < COLS; j++)
            temp.push_back(0);
        
        array.push_back(temp);
    }
}

int pausescrn(vector<vector<int>> &array, int &key, int &curr_x, int &curr_y)
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
            if(array[curr_y][curr_x] == 0)
                array[curr_y][curr_x] = 1;
            else if(array[curr_y][curr_x] == 1)
                array[curr_y][curr_x] = 0;
            key = 0;
            break;
        }

    flushinp();
    printscrn(array, curr_y, curr_x);
    key = mvgetch(curr_y, curr_x);
    }while(key != (int)'p');

    return key;
}

int printscrn(vector<vector<int>> &array, int c, int r)
{
    for(int i = 0; i < LINES; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(array[i][j] == 1)
                printw("X");
        }
    }
    return 0;
}


