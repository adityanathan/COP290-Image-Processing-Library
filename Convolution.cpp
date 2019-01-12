#include "Matrix.h"
#include "Convolution.h"

Convolution::Convolution(Matrix input_mat, Matrix kernel)
{
    this->mat = input_mat;
    this->kernel = kernel;
}

void Convolution::pad_matrix(int padding, int max_rows)
{
    if(padding>0)
    {
        max_rows = mat.get_max_rows();
        int dim = max_rows+(2*padding);
        int m=dim; int n =dim;
        Matrix A(dim);
        for(int i=0; i<=(dim-1); i++)
        {
            for(int j=1; j<=(dim-1); j++)
            {
                if(i<padding || i>=(m+padding))
                {
                    // A[i][j]=0;
                    A.set(0,i,j);
                }
                else
                {
                    if(j<padding || j>=n)
                    {
                        // A[i][j]=0;
                        A.set(0,i,j);
                    }
                    else
                    {
                        // A[i][j]=mat[i-padding][j-padding];
                        A.set(mat.get(i-padding,j-padding),i,j);
                    }
                }
            }
        }
        mat.delete_matrix();
        mat = A;
    }
}

void Convolution::convolve()
{
    int m = mat.get_max_rows();
    int k = kernel.get_max_rows();
    //Matrix reflected_kernel=kernel.reflect_matrix();
    Matrix conv(m+k-1);
    for(int i=0; i<=m+k-2; i++)
    {
        for(int j=0; j<=m+k-2; j++)
        {
            conv.set(0,i,j);
        }
    }
    int x,y,i,j,sum;
    int temp = (k-1)/2;
    
    for(y=k;y<m-k;y++)
    {
        for(x=k;x<m-k;x++)
        {
            sum=0;
            for(i=(-1*temp);i<=temp;i++)
            {
                for(j=(-1*temp);j<=temp;j++)
                {
                    sum = sum + kernel.get(j +1, i + 1)*mat.get(x - j, y - i);
                }
            }
            conv.set(sum,x,y);
        }
    }
}

