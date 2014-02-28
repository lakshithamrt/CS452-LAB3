run: lab3.cpp 
	g++ lab3.cpp  -lglut -lGLU -lGL -lGLEW -g 
	
clean: 
	rm -f *.out *~ run
	
