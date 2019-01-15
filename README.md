# Image Processing Library for COP290


## Subtask 1


### Instructions

In the terminal, enter the following to compile the code:

  `make`
  
If you wish to delete the compiled code, enter the following:

  `make clean`


### Usage

   * To obtain non-linear activations of an input matrix of any size with rectified linear units and tanh functions on individual matrix elements:

      `./output.out relu [matrix1.txt] [number_of_rows]`
   
      `./output.out tanh [matrix1.txt] [number_of_rows]`

   * To subsample a square input matrix of any size with max pooling and average pooling functions:
   
       `maxpool [matrix1.txt] [number_of_rows] [width] [stride]`
     
       `average_pool [matrix1.txt] [number_of_rows] [width] [stride]`
   
   * To convert a vector of random floats to a vector of probabilities with softmax and sigmoid functions:
   
       `sigmoid [vector.txt]`
       
       `softmax [vector.txt]`
       
   * To obtain convolution of a square input matrix and a square kernel, both matrices of any size and the kernel smaller than the input:
   
     * With and without input padding to maintain or reduce the size of the input matrix:
      
      * Using dot products to convolve:
   
         `convolve_with_padding [matrix1.txt] [number_of_rows] [matrix2.txt] [number_of_rows]`
          
         `convolve_without_padding [matrix1.txt] [number_of_rows] [matrix2.txt] [number_of_rows]`
          
      * Using matrix mulltiplication to convolve:
          
         `convolve_with_padding_matrixmult [matrix1.txt] [number_of_rows] [matrix2.txt] [number_of_rows]`
          
         `convolve_without_padding_matrixmult [matrix1.txt] [number_of_rows] [matrix2.txt] [number_of_rows]`
  
### Instructions for input
    
   * Values have to be representable as 32 bit float
          
   * Kernel has to have odd dimensions
          
   * Vectors have to be stored as single values in each line of the input file
          
   * Matrices have to be stored in column major order in each line of the input file
