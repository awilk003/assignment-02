CXX=g++
CXXFLAGS:=-g -ansi -Wall 
SOURCES=main.cpp and.cpp or.cpp cmd.cpp cmdline.cpp pound.cpp semicolon.cpp
OBJS=$(SOURCES:.cpp=.o)
EXECUTABLE=rshell

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJS)
	rm -f *.gch


