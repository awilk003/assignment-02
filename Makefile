CXX=g++
CXXFLAGS:=-g -ansi -Wall -Werror -pedantic 
SOURCES=main.cpp and.cpp or.cpp cmd.cpp cmdline.cpp pound.cpp semicolon.cpp
OBJS=$(SOURCES:.cpp=.o)
EXECUTABLE=rshell

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	mkdir bin
	mv $(OBJECTS) rshell bin

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJS)
	rm -R bin
	rm -f *.gch


