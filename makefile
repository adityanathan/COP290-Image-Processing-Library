output.o : main.cpp
	g++ main.cpp -o output.out

.PHONY : clean

clean :
	rm output.out
