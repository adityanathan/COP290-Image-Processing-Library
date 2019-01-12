#include "Matrix.h"

class Convolution
{
    private:
        Matrix mat;
        Matrix kernel;

    public:
        Convolution(Matrix a, Matrix kernel);
        
        void pad_matrix(int padding, int max_rows);
        void convolve();

};