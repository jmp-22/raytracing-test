all: clean run display

display:
	./run >> image.ppm

run: Main.o 
	g++ -std=c++11 -Wall -o run Main.o

	
Main.o: Main.cpp vec3.h color.h
	g++ -std=c++11 -Wall -c Main.cpp
		
	
clean:
	rm -f run *.o *.ppm