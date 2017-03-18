simulator.out: main.o vector.o city.o
	g++ -ansi -Wall -g -o simulator.out main.o vector.o city.o
main.o:	main.cpp vector.h
	g++ -ansi -Wall -g -c -o main.o main.cpp
vector.o: vector.cpp vector.h city.h
	g++ -ansi -Wall -g -c -o vector.o vector.cpp
city.o: city.cpp city.h
	g++ -ansi -Wall -g -c -o city.o city.cpp
clean:
	rm *.o *.out