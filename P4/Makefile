simulator.out: city.o main.o vector.o plane.o
	g++ -Wall -ansi -g -lm -o simulator.out city.o main.o vector.o plane.o 

city.o: city.cpp city.h 
	g++ -Wall -ansi -g -c city.cpp

main.o: main.cpp vector.h 
	g++ -Wall -ansi -g -c main.cpp

vector.o: vector.cpp vector.h city.h 
	g++ -Wall -ansi -g -c vector.cpp

plane.o: plane.cpp plane.h
	g++ -Wall -ansi -g -c plane.cpp

clean:
	rm -f simulator.out city.o main.o vector.o plane.o 
