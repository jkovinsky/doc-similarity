checker: compare.hpp compare.cpp main.cpp
	g++ -std=c++2a -O3 -o checker compare.cpp main.cpp
