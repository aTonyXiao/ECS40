simulator.out: city.o main.o plane.o airport.o
	g++ -Wall -ansi -o simulator.out city.o main.o plane.o airport.o

city.o: city.cpp city.h 
	g++ -Wall -ansi -c city.cpp

airport.o: airport.cpp airport.h city.h
	g++ -Wall -ansi -c airport.cpp

main.o: main.cpp list.h list.cpp airport.h airport.cpp plane.h city.h 
	g++ -Wall -ansi -c main.cpp

plane.o: plane.cpp plane.h
	g++ -Wall -ansi -c plane.cpp

clean:
	rm -f simulator.out city.o main.o plane.o 
