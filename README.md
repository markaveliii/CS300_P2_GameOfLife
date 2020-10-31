#Game of Life README

Mark Montes
CS300
Project 2


##Project Purpose
This project was made to replicate John Conway's *Game of Life.*
This game is a cellular automata that follows a few rules. The game takes place in a 2D grid
with cells in between. Each cell can either be in one of two states DEAD or ALIVE.
In each iteration, or generation of the grid, each cells state DIES or SURVIVES depending on these few rules:
1. A cell in the ALIVE state with 1 or less than 1 neighbors DIES.
2. A cell in the ALIVE state with 4 or more neighbors DIES.
3. A cell in the DEAD state with 3 neighbors becomes ALIVE.

##How to Play
This program can toggle between different game state:
-Pause
-Play
-Next Generation
-Quit

To pause or play push **p**
To display the next generation push **n**
To quit the game push **q**
