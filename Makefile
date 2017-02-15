CXX=g++
CXXFLAGS:=-g -ansi -Wall 
CXXFLAGS += -I/path/to/boost/include
LDPATH += -L/path/to/boost/lib
SOURCES=main.cpp and.cpp or.cpp cmd.cpp cmdline.cpp pound.cpp semicolon.cpp
OBJS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@
	
main.o: main.cpp
	$(CXX) -c main.cpp

clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJS)

