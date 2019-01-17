output.o : main.cpp
	g++ -std=c++11 main.cpp -o output.out

.PHONY : clean

clean :
	rm output.out
