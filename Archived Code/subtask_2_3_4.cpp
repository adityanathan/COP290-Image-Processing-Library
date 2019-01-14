//
//  main.cpp
//  COP_1
//
//  Created by Poorva garg on 12/01/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
// #include "Vector.h"
#include <string>
#include <cmath>
// #include "Matrix.h"
using namespace std;

vector<float> read_file(std::string s)
{
    vector<float> v;
    std::ifstream infile;
    infile.open(s);
    std::string sd;
    float data;
    while(getline(infile, sd))
    {
        data=stof(sd);
        v.push_back(data);
        //std::cout<<data<<std::endl;
    }
    //std::cout<<"end of file reading"<<std::endl;
    return v;

}

vector<float> sigmoid(vector<float> v)
{
    vector<float> ans;
    int size=v.size();
    std::cout<<size<<std::endl;
    for(int i=0; i<size; i++)
    {
        //std::cout<<v.get(i)<<std::endl;
        double t1=exp(v[i]*(-1));
        double t2=1/(1+t1);
        float t3=(float)(t2);
        ans.push_back(t3);
        //std::cout<<"oh";
        //std::cout<<t3<<std::endl;
    }
    return ans;
}

vector<float> softmax(vector<float> v)
{
    vector<float> ans;
    vector<float> mid;
    double sum=0;
    int size=v.size();
    for(int i=0; i<size; i++)
    {
        double t1=exp(v[i]);
        //std::cout<<t1<<std::endl;
        mid.push_back((float)(t1));
        sum=sum+t1;
    }

    for(int i=0; i<size; i++)
    {
        float t2=(float)(mid[i]/sum);
        //std::cout<<t2<<std::endl;
        ans.push_back(t2);
    }
    return ans;

}

vector<vector<float>> tanh(vector<vector<float>> m)
{
    int n=m.size();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            float t1=m[i][j];
            double t2=exp(t1);
            double t3=exp(t1*(-1));
            float t4=(float)((t2-t3)/(t2+t3));
            std::cout<<t4<<std::endl;
            m[i][j]=t4;
        }
    }
    return m;
}

vector<vector<float>> relu(vector<vector<float>> m)
{
    int n=m.size();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            float t1=m[i][j];
            if (t1<0)
            {
                m[i][j]=0;
            }
        }
    }
    return m;
}

vector<vector<float>> maxpooling(vector<vector<float>> m, int width, int stride=1)
{
    int n=m.size();
    float t1=((n-width)%stride);
    if (t1!=0)
    {
        std::cout<<"The stride and width given by you are not an appropriate choice, still the output will be"<<std::endl;
    }

    int rows=0;
    while ((width+rows*stride)<=n)
    {
        rows+=1;
    }
    //std::cout<<rows<<std::endl;
    vector<vector<float>> ans = vector<vector<float>>(rows);
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<rows; j++)
        {
            float max=m[i*stride][j*stride];
            for (int iw=i*stride; iw<i*stride+width; iw++)
            {
                //std::cout<<"iw"<<std::endl;
                for (int jw=j*stride; jw<j*stride+width; jw++)
                {
                    //std::cout<<"iw"<<std::endl;
                    float temp=m[iw][jw];
                    if (max<temp)
                    {
                        //std::cout<<temp<<std::endl;
                        max=temp;
                    }
                }
            }
            //std::cout<<max<<std::endl;
            ans[i][j]=max;
        }
    }
    return ans;
}

vector<vector<float>> average_pooling(vector<vector<float>> m, int width, int stride=1)
{
    int n=m.size();
    float t1=((n-width)%stride);
    if (t1!=0)
    {
        std::cout<<"The stride and width given by you are not an appropriate choice, still the output will be"<<std::endl;
    }
    float square=width*width;
    int rows=0;
    while ((width+rows*stride)<=n)
    {
        rows+=1;
    }
    //std::cout<<rows<<std::endl;
    // Matrix ans=Matrix(rows);
    vector<vector<float>> ans(rows,vector<float>(rows,0));
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<rows; j++)
        {
            float sum=0;
            for (int iw=i*stride; iw<i*stride+width; iw++)
            {
                //std::cout<<"iw"<<std::endl;
                for (int jw=j*stride; jw<j*stride+width; jw++)
                {
                    //std::cout<<"iw"<<std::endl;
                    float temp=m[iw][jw];
                    sum=sum+temp;
                }
            }
            //std::cout<<max<<std::endl;
            float average=sum/square;
            // ans.set(average,i,j);
            ans[i][j]=average;
        }
    }
    return ans;

}

// int main() {
//     // insert code here...
//     //Vector v=read_file("afile.txt");
//     //Vector ans=sigmoid(v);
//     //Vector ans2=softmax(v);
//
//     vector<vector<float>> m(5,vector<float>(5,0));
//     m[0][0]=-1;
//     m[0][1]=2;
//     m[0][2]=3;
//     m[0][3]=4;
//     m[0][4]=-1;
//     m[1][0]=2;
//     m[1][1]=3;
//     m[1][2]=4;
//     m[1][3]=-1;
//     m[1][4]=2;
//     m[2][0]=3;
//     m[2][1]=4;
//     m[2][2]=-1;
//     m[2][3]=2;
//     m[2][4]=3;
//     m[3][0]=4;
//     m[3][1]=-1;
//     m[3][2]=2;
//     m[3][3]=3;
//     m[3][4]=4;
//     m[4][0]=-1;
//     m[4][1]=2;
//     m[4][2]=3;
//     m[4][3]=4;
//     m[4][4]=5;
//     //Matrix t=relu(m);
//
//     vector<vector<float>> ans=average_pooling(m,3,2);
//     int n=ans.size();
//     for(int i=0; i<n; i++)
//     {
//         for(int j=0; j<n; j++)
//         {
//             std::cout<<ans[i][j]<<std::endl;
//         }
//     }
//     return 0;
// }

// int main(int argc, char** argv)
// {
//     std::cout<<"yo"<<std::endl;
//     if (argc==2 && *argv[1]=='Y')
//     {
//         std::cout<<"Hi"<<std::endl;
//     }
//
// }
