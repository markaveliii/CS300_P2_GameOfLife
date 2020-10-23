#Mark Montes
#CS300
#Game of Life
#Makefile

CPP = g++
CPPFLAGS = -Wall -g -Werror

GOL: conway.cpp
	$(CPP) $(CPPFLAGS) -o conway conway.cpp -lncurses

clean:
	-rm -f conway
