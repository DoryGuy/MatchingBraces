
CXX=g++-14
CXX_VERSION=c++23
OPTIMIZE_FLAG=-O3
DEBUG_FLAG=-g
WARNING_FLAGS=-Wall -Wextra -Wconversion
INCLUDE_FLAGS=-I/usr/local/include -I/usr/local/Cellar/boost/1.83.0/include
CXXFLAGS=-std=$(CXX_VERSION) $(OPTIMIZE_FLAG) $(WARNING_FLAGS) $(INCLUDE_FLAGS) $(DEBUG_FLAG)
INCLUDE_DIR=/usr/local/include
LIB_DIR=/usr/local/lib
RM=rm


# Define a pattern rule that compiles every .cpp file into a .o file
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

LIBRARIES=

# The build target
TARGET = test_program.exe

all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o  -L$(LIB_DIR) $(LIBRARIES)

clean:
	$(RM) *.o $(TARGET)

ctags:
	ctags --c++-kinds=+p --fields=+iaS --extras=+q --language-force=C++ *.cpp
