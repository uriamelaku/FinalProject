CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = naive
OBJS = main_naive.o Common.o OutsourceNaive.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

main_naive.o: main_naive.cpp Common.h OutsourceNaive.h
	$(CXX) $(CXXFLAGS) -c main_naive.cpp

Common.o: Common.cpp Common.h
	$(CXX) $(CXXFLAGS) -c Common.cpp

OutsourceNaive.o: OutsourceNaive.cpp OutsourceNaive.h Common.h
	$(CXX) $(CXXFLAGS) -c OutsourceNaive.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

#make
#make run
#make clean
#./naive

#or directly write
#g++ main_naive.cpp Common.cpp OutsourceNaive.cpp -o naive
#./naive

