// #include<iostream>
#include "mkl.h"
#include "functions.h"
#include <vector>
using namespace std;

vector<vector<float> > matrix_multiply_with_mkl(vector<vector<float> > mat1, vector<vector<float> > mat2)
{
    float *A, *B, *C;
    A = new float[mat1.size() * mat1[0].size()];
    B = new float[mat2.size() * mat2[0].size()];
    C = new float[mat1.size() * mat2[0].size()];
    int k=0;
    for (int i = 0; i < mat1.size(); i++)
    {
        for (int j = 0; j < mat1[0].size(); j++)
        {
            A[k++]=mat1[i][j];
        }
    }
    k=0;
    for (int i = 0; i < mat2.size(); i++)
    {
        for (int j = 0; j < mat2[0].size(); j++)
        {
            B[k++]=mat2[i][j];
        }
    }
    k=0;
    for (int i = 0; i < mat1.size(); i++)
    {
        for (int j = 0; j < mat2[0].size(); j++)
        {
            C[k++]=0;
        }
    }

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
        mat1.size(),  mat2[0].size(),  mat2.size(), 1.0, A,mat1[0].size(),
        B, mat2[0].size(), 0.0, C, mat2[0].size());

    vector<vector<float> > result(mat1.size(), vector<float>(mat2[1].size(),0));
    k=0;
    for (int i = 0; i < mat1.size(); i++)
    {
        for (int j = 0; j < mat2[0].size(); j++)
        {
            result[i][j]=C[k++];
        }
    }
    return result;
}


// int main()
// {
//     vector<vector<float> > mat1(3,vector<float>(3));
//     vector<vector<float> > mat2(3,vector<float>(3));
//     for(int i=0; i<3; i++)
//     {
//         for(int j=0; j<3; j++)
//         {
//             mat1[i][j]=i;
//             mat2[i][j]=i;
//             cout<<mat1[i][j]<<" ";
//         }
//         cout<<endl;
//     }
//     cout<<endl;
//     vector<vector<float> > mat3 = matrix_multiply_with_mkl_or_openBLAS(mat1,mat2);
//
//     for(int i=0; i<3; i++)
//     {
//         for(int j=0; j<3; j++)
//             cout<<mat3[i][j]<<" ";
//         cout<<endl;
//     }
//     cout<<endl;
//
// }
//pthreads
