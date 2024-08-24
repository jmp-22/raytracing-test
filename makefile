all: run

run: Main.o 
	g++ -Wall -o run Main.o

	
Main.o: Main.cpp
	g++ -Wall -c Main.cpp
		
	
clean:
	rm -f td *.o