#include <vector>
#include <iostream>
#include <curses.h>
#define DEAD " "
#define ALIVE "X"
using namespace std;

const int start_x = COLS/2;
const int start_y = LINES/2;

void fill_arr(vector<vector<int>> &);
int pausescrn(vector<vector<int>> &, int &, int &, int &);
int printscrn(vector<vector<int>> &);
int countadj(vector<vector<int>>, int, int);
void updatemtrx(vector<vector<int>> &);

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
    do{
    updatemtrx(array);
    printscrn(array);
    wrefresh(stdscr);
    }while(getch() != (char)'q');

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

    printscrn(array);
    key = mvgetch(curr_y, curr_x);
    }while(key != (int)'p');

    return key;
}

int printscrn(vector<vector<int>> &array)
{
    for(int i = 0; i < LINES; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(array[i][j] == 1)
                mvprintw(i , j, ALIVE);
            else
                mvprintw(i ,j , DEAD);
        }
    }

    wrefresh(stdscr);
    return 0;
}

int countadj(vector<vector<int>> array, int y, int x)
{
    int sum = 0;
    if(array[y-1][x] == 1)
        sum++;
    if(array[y-1][x-1] == 1)
        sum++;
    if(array[y-1][x+1] == 1)
        sum++;
    if(array[y][x+1] == 1)
        sum++; 
    if(array[y][x-1] == 1)
        sum++;
    if(array[y+1][x+1] == 1)
        sum++;
    if(array[y+1][x] == 1)
        sum++;
    if(array[y+1][x-1] == 1)
        sum++;

    return sum;
}

void updatemtrx(vector<vector<int>> &array)
{
    for(int i = 0; i < LINES-1; i++)
    {
        for(int j = 0; j < COLS-1; j++)
        {
            int n;
            if(i == 0 || i == COLS-1 || j == 0 || j == LINES-1)
                n = 0;
            else
                n = countadj(array, i, j);
            if(n < 2)
                array[i][j] = 0;
            if(n > 3)
                array[i][j] = 0;
            if(n == 3)
                array[i][j] = 1;
        }

    }
}
