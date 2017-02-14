CXX=g++
CXXFLAGS:=-g -ansi -Wall 
SOURCES=main.cpp add.cpp or.cpp cmd.cpp cmdline.cpp pound.cpp semicolon.cpp
OBJS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@
clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJS)

