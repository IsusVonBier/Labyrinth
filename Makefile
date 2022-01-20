# define the C compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS = -Iinclude -Llib -std=c++17 -g -Wall

# define any directories containing header files other than /usr/include
CPPFLAGS = -w -lSDL2main -lSDL2 -lSDL2_image # -lSDL2_ttf
WINFLAGS = -w -Wl,-subsystem,console -IC:\msys64\mingw64\x86_64-w64-mingw32\include\SDL2 -LC:\msys64\mingw64\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread # subsystem ? windows : console

#define the directive for object files
OBJDIR = ./obj
SRCDIR = ./src
BINDIR = ./bin

# define the C source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# define the C object files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# define the executable file
BIN=$(BINDIR)/main

all: $(BIN)
	@echo "Program compiled"

$(BIN): $(OBJS)
	@echo "Compiling: " $@
	$(CXX) $(CXXFLAGS) $(OBJS) $(CPPFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling: " $@
	$(CXX) $(CXXFLAGS) -c $< $(CPPFLAGS) -o $@

win:
	$(CXX) $(CXXFLAGS) $(SRCS) $(WINFLAGS) -o $(BIN)


clean:
	$(RM) $(OBJDIR)/*.o *~ $(BIN)
