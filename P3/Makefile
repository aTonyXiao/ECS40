simulator.out : city.o main.o vector.o  
	g++ -ansi -Wall -g -o simulator.out city.o main.o vector.o  

city.o : city.cpp city.h 
	g++ -ansi -Wall -g -c -lm city.cpp

main.o : main.cpp vector.h 
	g++ -ansi -Wall -g -c main.cpp

vector.o : vector.cpp vector.h 
	g++ -ansi -Wall -g -c vector.cpp

clean : 
	rm -f simulator.out city.o  main.o  vector.o   
