SOURCES=$(wildcard src/*.cpp)
OBJS=$(SOURCES:.cpp=.o)

# compiler options : add debug information in debug mode
# optimize speed in release mode
ifneq (,$(findstring debug,$(MAKECMDGOALS)))
	CFLAGS=-g
else
	CFLAGS=-O2
endif

# linker options for different operating systems
# Linux/BSD
ifeq ($(shell sh -c 'uname -s'),Linux)
	LIBFLAGS=-L. -ltcod -ltcodxx -Wl,-rpath=.
# macOS
else ifeq ($(shell sh -c 'uname -s'),Darwin)
	LIBFLAGS=-L. -ltcod -ltcodxx
# Windows
else
	LIBFLAGS=-Llib -ltcod-mingw-debug -static-libgcc -static-libstdc++ -mwindows
endif

## debug     : build with debugging information
debug : cyberpunk

## release   : build for release
release : cyberpunk

# intermediate target
cyberpunk : $(OBJS)
	g++ $(OBJS) -o cyberpunk -Wall $(LIBFLAGS) $(CFLAGS)

# intermediate target
src/main.hpp.gch : src/*.hpp
	g++ src/main.hpp -Iinclude -Wall

# intermediate target
src/%.o : src/%.cpp src/main.hpp.gch
	g++ $< -c -o $@ -Iinclude -Wall $(CFLAGS)

## clean     : clean auto-generated files
clean :
	rm -f src/main.hpp.gch $(OBJS)

help : makefile
	@sed -n 's/^##//p' $<