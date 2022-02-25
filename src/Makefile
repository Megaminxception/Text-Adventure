
ouput: main.o Room.o
	g++ main.o Room.o -o output -std=c++11

main.o: main.cpp
	g++ -c main.cpp -std=c++11

Room.o: Room.cpp Room.hpp
	g++ -c Room.cpp -std=c++11

clean:
	rm *.o output
