# Image Processing Library for COP290


## Subtask 1


### Instructions

In the terminal, enter the following to compile the code:

  `$ export LD_LIBRARY_PATH=/path_to_your_openblas_installation_directory/lib/`

  Example: `$ export LD_LIBRARY_PATH=/opt/OpenBLAS/lib/`

  `$ export MKLROOT=/path_to_your_mkl_installation_directory/intel/mkl/`

  Example: `$ export MKLROOT=~/Frameworks/intel-mkl/mkl/`

  `$ make`

If you wish to delete the compiled code, enter the following:

  `$ make clean`


### Usage

   * To obtain non-linear activations of an input matrix of any size with rectified linear units and tanh functions on individual matrix elements:

      `$ ./output.out relu matrix1.txt number_of_rows`

      `$ ./output.out tanh matrix1.txt number_of_rows`

   * To subsample a square input matrix of any size with max pooling and average pooling functions:

       `$ ./output.out maxpool matrix1.txt number_of_rows width stride`

       `$ ./output.out average_pool matrix1.txt number_of_rows width stride`

   * To convert a vector of random floats to a vector of probabilities with softmax and sigmoid functions:

       `$ ./output.out sigmoid vector.txt`

       `$ ./output.out softmax vector.txt`

   * To obtain convolution of a square input matrix and a square kernel, both matrices of any size and the kernel smaller than the input:

     * With or without input padding to maintain or reduce the size of the input matrix:

      * Using dot products to convolve:

         `$ ./output.out convolve_with_padding input_matrix.txt number_of_rows_of_input_matrix matrix2.txt number_of_rows_of_kernel`

         `$ ./output.out convolve_without_padding input_matrix.txt number_of_rows_of_input_matrix matrix2.txt number_of_rows_of_kernel`

      * Using matrix mulltiplication with mkl to convolve:

         `$ ./output.out convolve_with_padding_matrixmult_with_mkl input_matrix.txt number_of_rows_of_input_matrix matrix2.txt number_of_rows_of_kernel`

         `$ ./output.out convolve_without_padding_matrixmult_with_mkl input_matrix.txt number_of_rows_of_input_matrix matrix2.txt number_of_rows_of_kernel`

       * Using matrix mulltiplication with openBLAS to convolve:

            `$ ./output.out convolve_with_padding_matrixmult_with_openblas input_matrix.txt number_of_rows_of_input_matrix matrix2.txt number_of_rows_of_kernel`

            `$ ./output.out convolve_without_padding_matrixmult_with_openblas input_matrix.txt number_of_rows_of_input_matrix matrix2.txt number_of_rows_of_kernel`

      * Using matrix mulltiplication with pthreads to convolve:

           `$ ./output.out convolve_with_padding_matrixmult_with_pthreads input_matrix.txt number_of_rows_of_input_matrix matrix2.txt number_of_rows_of_kernel`

           `$ ./output.out convolve_without_padding_matrixmult_with_pthreads input_matrix.txt number_of_rows_of_input_matrix matrix2.txt number_of_rows_of_kernel`

### Instructions for input

   * Values have to be representable as 32 bit float

   * Kernel has to have odd dimensions

   * Vectors have to be stored as single values in each line of the input file

   * Matrices have to be stored in column major order in each line of the input file

   * If the arguments for number of rows is lesser than the actual dimensions of the matrix in the input file, then the program will only take the necessary amount of data and omit the rest.

 **Note**: Sample input files have been provided. The output will also be displayed on the terminal and will be given in a text file output.txt in the same format as specified for input: vectors as single values in each line of the output file and matrices in column major order in each line of the output file

 **WARNING**: pthreads implementation is mildly buggy. It occasionally fails to assign values to last 2-3 entries in the matrix.


 Report:
