CXX = g++ -std=c++17
CXXFLAGS = -I/usr/include
LDFLAGS = -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system

TARGET = main
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(TARGET) $(OBJ)