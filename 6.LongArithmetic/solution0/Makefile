CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic 
FILES = lab6.cpp longarif.hpp
NAME = solution

all: example

example:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

clean:
	rm -f *.o $(NAME)