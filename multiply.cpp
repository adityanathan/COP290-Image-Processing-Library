//
//  multiply.cpp
//  COP_1
//
//  Created by Poorva garg on 24/01/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <cmath>
#include <pthread.h>
#include<iostream>
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
    //struct C *data = (struct C*) arg;
    //mat1=foo.mat1;
    if(((foo->mat2)).size()==((foo->mat1))[0].size())
    {
        //vector<vector<float> > result(mat1.size(), vector<float>(mat2[1].size(),0));
        for(int a=(foo->start); a<((foo->start)+(foo->i)); a++)
        {
            for(int j=0; j<((foo->mat2)).size(); j++)
            {
                float sum=0;
                for(int k=0; k<((foo->mat2)).size(); k++)
                    sum=sum+((foo->mat1))[a][k]*((foo->mat2))[k][j];
                //cout<<sum<<endl;
                (*(foo->ans))[a][j]=sum;
            }
        }
        return 0;
        //return result;
    }
    else
    {
        throw "Matrix Dimensions don't match!";
    }
}

vector<vector< float> > creating_threads(vector<vector<float> > mat1, vector<vector< float> > mat2)
{
    float no_threads=4.0;
    float rows=(mat1.size());
    int sub_rows=round(rows/no_threads);
    vector<vector< float> > ans;
    //cout<<"4"<<endl;
    for (int i=0; i<mat1.size(); i++)
    {
        vector<float> v(mat2[0].size(),0);
        ans.push_back(v);
    }
    //cout<<"3"<<endl;
    //struct C *thread_arg;
    struct C thread_arg1 ={mat1, mat2, &ans, 0*sub_rows, sub_rows};
    struct C thread_arg2 ={mat1, mat2, &ans, 1*sub_rows, sub_rows};
    struct C thread_arg3 ={mat1, mat2, &ans, 2*sub_rows, sub_rows};
    struct C thread_arg4 ={mat1, mat2, &ans, 3*sub_rows, static_cast<int>(mat1.size()-3*sub_rows)};
    //*thread_arg=C();
    //cout<<"7"<<endl;
    //(*thread_arg->mat1)=mat1;
    //(*thread_arg->mat2)=mat2;
    //(*thread_arg->ans)=ans;
    //cout<<"5"<<endl;
    pthread_t threads[4];
    //cout<<"6"<<endl;
//    for (int n=0; n<no_threads; n++)
//    {
//        cout<<n<<endl;
//        struct C thread_arg ={mat1, mat2, &ans, 0, 0};
//        ((thread_arg).start)=n*sub_rows;
//        ((thread_arg).i)=sub_rows;
    pthread_create(&threads[0], NULL, matrix_multiply, (void* ) &thread_arg1);
    pthread_create(&threads[1], NULL, matrix_multiply, (void* ) &thread_arg2);
    pthread_create(&threads[2], NULL, matrix_multiply, (void* ) &thread_arg3);
    pthread_create(&threads[3], NULL, matrix_multiply, (void* ) &thread_arg4);
        //cout<<"2"<<endl;
    //}
    
    for (int n=0; n<4; n++)
    {
        pthread_join(threads[n], NULL);
        //cout<<"2"<<endl;
    }
    return ans;
    
    
}

int main()
{
    vector<vector< float> > matA;
    for (int i=0; i<5; i++)
    {
        vector<float> v(5,0);
        matA.push_back(v);
    }
    vector<vector< float> > matB;
    for (int i=0; i<5; i++)
    {
        vector<float> v(5,0);
        matB.push_back(v);
    }
    vector<vector< float> > matC;
    for (int i=0; i<5; i++)
    {
        vector<float> v(5,0);
        matC.push_back(v);
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }
    
    cout << endl
    << "Matrix A" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << matA[i][j] << " ";
        cout << endl;
    }
    
    cout << endl
    << "Matrix B" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << matB[i][j] << " ";
        cout << endl;
    }
    
    matC=creating_threads(matA, matB);
    
    cout << endl
    << "Multiplication of A and B" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << matC[i][j] << " ";
        cout << endl;
    }
    return 0;
}






