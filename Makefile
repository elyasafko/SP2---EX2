# elyasafko@gmail.com

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -Werror -Wsign-conversion

# Valgrind settings
VALGRIND_FLAGS := -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Source files
SOURCESDEMO=Graph.cpp Algorithms.cpp 
SOURCESTEST=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp

OBJECTSDEMO=$(subst .cpp,.o,$(SOURCESDEMO))
OBJECTSTEST=$(subst .cpp,.o,$(SOURCESTEST))

.PHONY: all run demo test tidy valgrind clean

all: demo test

run: demo
	./$<

demo: Demo.o $(OBJECTSDEMO)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o $(OBJECTSTEST)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) --checks='*' --warnings-as-errors='*' -fix

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	@rm -f *.o demo test