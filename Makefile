CXX=g++
CXXFLAGS:=-g -ansi -Wall -Werror -pedantic 
SOURCES=main.cpp and.cpp or.cpp cmd.cpp cmdline.cpp pound.cpp semicolon.cpp test.cpp in.cpp out.cpp backup.cpp
OBJS=$(patsubst %.cpp,bin/%.o,$(SOURCES))
VPATH=src
EXECUTABLE=bin/rshell

all: bin $(EXECUTABLE)

bin:
	mkdir -p bin

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

bin/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

clean:
	rm -f $(EXECUTABLE) $(OBJS) *.gch
	rm -r bin


