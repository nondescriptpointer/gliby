MAIN = main
SHAREDPATH = /home/ego/projects/personal/gliby/src/
SHAREDINCPATH = /home/ego/projects/personal/gliby/include/
CC = g++
INCDIRS = -I$(SHAREDINCPATH)
CXXFLAGS = $(COMPILERFLAGS) -O3 -march=native -pipe -std=c++0x -Wall -Wextra -Wshadow -g $(INCDIRS)
CFLAGS = -g $(INCDIRS)
LIBS = -lglut -lGL -lGLU -lGLEW -lboost_system -lboost_filesystem

prog: $(MAIN)

$(MAIN).o : $(MAIN).cpp

lib/%.o : $(SHAREDPATH)%.cpp
	$(CC) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $<
$(MAIN) : $(MAIN).o lib/Math3D.o
	$(CC) -o $(MAIN) $^ $(LIBS)

.PHONE: clean
clean:
	rm -f lib/*.o
	rm -f *.o
