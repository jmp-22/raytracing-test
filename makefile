all: clean run display

display:
	./run >> image.ppm

run: Main.o 
	g++ -std=c++11 -Wall -o run Main.o

	
Main.o: Main.cpp raytracer.h interval.h camera.h hittable.h hittable_list.h color.h sphere.h ray.h vec3.h 

	g++ -std=c++11 -Wall -c Main.cpp 
		
	
clean:
	rm -f run *.o *.ppm