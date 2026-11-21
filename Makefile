CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = program
SRCS = main.cpp feistel.cpp poly.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp my_file.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)