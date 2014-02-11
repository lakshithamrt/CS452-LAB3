run: test.cpp 
	g++ test.cpp  -lglut -lGLU -lGL -lGLEW -g 
	
clean: 
	rm -f *.out *~ run
	
