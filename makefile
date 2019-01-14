output.o : subtask_1.cpp
	g++ subtask_1.cpp -o output.out

.PHONY : clean

clean :
	rm output.out
