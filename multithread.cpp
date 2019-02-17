#include <stdio.h>
#include <vector>
#include <cmath>
#include <pthread.h>
#include<iostream>
#include "functions.h"
using namespace std;

struct C
{
    vector<vector<float> > mat1;
    vector<vector<float> > mat2;
    vector<vector<float> >* ans;
    int start;
    int i;
};

void* matrix_multiply(void* arg)
{
    struct C *foo=(struct C *)arg;
    if(((foo->mat2)).size()==((foo->mat1))[0].size())
    {
        for(int a=(foo->start); a<(foo->i); a++)
        {
            for(int j=0; j<((foo->mat2))[0].size(); j++)
            {
                float sum=0;
                for(int k=0; k<((foo->mat2)).size(); k++)
                {
                    sum=sum+((foo->mat1))[a][k]*((foo->mat2))[k][j];
                }
                (*(foo->ans))[a][j]=sum;
            }
        }
        return 0;
    }
    else
    {
        throw "Matrix Dimensions don't match!";
    }
}

vector<vector< float> > matrix_multiply_with_pthreads(vector<vector<float> > mat1, vector<vector< float> > mat2)
{
    int max_no_threads=4.0;
    int rows=(mat1.size());
    int sub_rows=floor(rows/max_no_threads);
    vector<vector< float> > ans(mat1.size(),vector<float>(mat2[0].size(),0));

    struct C thread_arg[4];
    int no_of_threads=0;



    for(int i=0; i<4; i++)
    {
        if(sub_rows*(i+1)>rows)
        {
            break;
        }
        if(i==3)
            thread_arg[3] ={mat1, mat2, &ans, 0*sub_rows, rows-(i*sub_rows)};
        else
            thread_arg[i] ={mat1, mat2, &ans, i*sub_rows, (i+1)*sub_rows};
        no_of_threads++;
    }



    pthread_t threads[4];

    for(int x=0; x<no_of_threads; x++)
    {
        pthread_create(&threads[x], NULL, matrix_multiply, (void* ) &thread_arg[x]);
    }

    for(int x=0; x<no_of_threads; x++)
    {
        pthread_join(threads[x], NULL);
    }

    return ans;
}

// int main()
// {
//     vector<vector< float> > matA;
//     for (int i=0; i<7; i++)
//     {
//         vector<float> v(5,0);
//         matA.push_back(v);
//     }
//     vector<vector< float> > matB;
//     for (int i=0; i<5; i++)
//     {
//         vector<float> v(5,0);
//         matB.push_back(v);
//     }
//     vector<vector< float> > matC;
//     for (int i=0; i<7; i++)
//     {
//         vector<float> v(5,0);
//         matC.push_back(v);
//     }
//     for (int i = 0; i < 7; i++) {
//         for (int j = 0; j < 5; j++) {
//             matA[i][j] = rand() % 10;
//         }
//     }
//     for (int i = 0; i < 5; i++) {
//         for (int j = 0; j < 5; j++) {
//             matB[i][j] = rand() % 10;
//         }
//     }
//
//     cout << endl
//     << "Matrix A" << endl;
//     for (int i = 0; i < 7; i++) {
//         for (int j = 0; j < 5; j++)
//             cout << matA[i][j] << " ";
//         cout << endl;
//     }
//
//     cout << endl
//     << "Matrix B" << endl;
//     for (int i = 0; i < 5; i++) {
//         for (int j = 0; j < 5; j++)
//             cout << matB[i][j] << " ";
//         cout << endl;
//     }
//
//     matC=matrix_multiply_with_pthreads(matA, matB);
//
//     cout << endl
//     << "Multiplication of A and B" << endl;
//     for (int i = 0; i < 7; i++) {
//         for (int j = 0; j < 5; j++)
//             cout << matC[i][j] << " ";
//         cout << endl;
//     }
//     return 0;
// }
