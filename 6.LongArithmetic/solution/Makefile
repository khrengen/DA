CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic 
FILES = newmenu.cpp newlong.cpp
NAME = solution

all: example

example:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

clean:
	rm -f *.o $(NAME)