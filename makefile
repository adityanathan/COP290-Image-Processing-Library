output.o :
	g++ -g -std=c++11 main.cpp cnn.cpp -o output.out

.PHONY : clean

clean :
	rm output.out
