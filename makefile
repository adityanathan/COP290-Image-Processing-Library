output.o :
	g++ -pthread -std=c++11 multithread.cpp mkl_matrix_mult.cpp openblas_matrix_mult.cpp main.cpp -o output.out -I /opt/OpenBLAS/include/ -L/opt/OpenBLAS/lib -lopenblas \
	-m64 -I${MKLROOT}/include  -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl

.PHONY : clean

clean :
	rm output.out
