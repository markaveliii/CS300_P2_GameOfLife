#Mark Montes
#CS300
#Game of Life
#Makefile

CPP = gcc
CPPFLAGS = -Wall -g -Werror

GOL: GOL.cpp
	$(CPP) $(CPPFLAGS) -o GOL GOL.cpp -lncurses

clean:
	-rm -f GOL
