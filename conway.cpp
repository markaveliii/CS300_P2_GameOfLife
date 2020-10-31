//INCLUDES AND DEFINES
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <curses.h>
#define DEAD " "
#define ALIVE "X"
#define QUIT (int)'q'
#define PAUSEorPLAY (int) 'p'
#define NEXT (int)'n'

const float FPS_RATE = 0.5;

using namespace std;


//PROTOTYPES
void fill_arr(vector<vector<int>> &);
int pausescrn(vector<vector<int>> &, int &, int &, int &);
int printscrn(vector<vector<int>> &);
int countadj(vector<vector<int>>, int, int);
void updatemtrx(vector<vector<int>> &);
int playscrn(vector<vector<int>> &);


//MAIN FUNCTION
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

    do{
        key = pausescrn(array, key, curr_x, curr_y);
        if(key == PAUSEorPLAY)
            key = playscrn(array);
    }while(key != QUIT && key == PAUSEorPLAY);

    endwin();

    return 0;
}


//FUNCTION DEFINITIONS
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
    nodelay(stdscr, FALSE);

    //KEYSTROKE OPTIONS
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

            case NEXT:
            updatemtrx(array);
            break;
        }

    printscrn(array);
    key = mvgetch(curr_y, curr_x);
    curs_set(1);
    }while(key != PAUSEorPLAY && key != QUIT);
    return key;
}

//PRINT EVERY LINE ITERITIVELY.
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

    return 0;
}

//COUNTS ADJACENT LIVE NEIGHBORS
int countadj(vector<vector<int>> array, int y, int x)
{
    int sum = 0;
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
            sum += array[i+y][j+x];
    }
    sum -= array[y][x];
    return sum;
}

void updatemtrx(vector<vector<int>> &array)
{
    curs_set(0);
    vector<vector<int>> newgen;
    for(int i = 0; i < LINES; i++)
    {
        vector<int>temp;
        for(int j = 0; j < COLS; j++)
        {
            int n;
            if(i == 0 || i == LINES-1 || j == 0 || j == COLS-1)
                temp.push_back(0);
            else
            {
                n = countadj(array, i, j);

                //CONWAY GAME OF LIFE RULEZZZ
                if(array[i][j] == 0 && n == 3)
                    temp.push_back(1);
                else if(array[i][j] == 1 && (n > 3 ||n < 2) )
                    temp.push_back(0);
                else
                    temp.push_back(array[i][j]);
            }
        }
        newgen.push_back(temp);

    }
    array = newgen;
}

int playscrn(vector<vector<int>> &array)
{
    nodelay(stdscr, TRUE);
    int key;
    do{
        curs_set(0);
        updatemtrx(array);
        //CALCULATES AND DELAYS SCREEN FRAMES
        int seconds = 1000 * FPS_RATE;
        this_thread::sleep_for(chrono::milliseconds(seconds));
        printscrn(array);
        key = getch();

    }while(key != PAUSEorPLAY && key != QUIT);
    return key;
}


