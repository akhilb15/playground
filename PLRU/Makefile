
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Iplru.h -Ibitvector.h

exec: ./main.cpp ./plru.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f exec
