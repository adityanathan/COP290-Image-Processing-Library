//
//  main.cpp
//  COP_1
//
//  Created by Poorva garg on 12/01/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Vector.h"
#include <cmath>
#include "Matrix.h"
//using namespace std;

Vector read_file(std::string s)
{
    Vector v;
    std::ifstream infile;
    infile.open(s);
    std::string sd;
    float data;
    while(getline(infile, sd))
    {
        data=stof(sd);
        v.push(data);
        //std::cout<<data<<std::endl;
    }
    //std::cout<<"end of file reading"<<std::endl;
    return v;
    
}

Vector sigmoid(Vector v)
{
    Vector ans;
    int size=v.getSize();
    std::cout<<size<<std::endl;
    for(int i=0; i<size; i++)
    {
        //std::cout<<v.get(i)<<std::endl;
        double t1=exp(v.get(i)*(-1));
        double t2=1/(1+t1);
        float t3=(float)(t2);
        ans.push(t3);
        //std::cout<<"oh";
        //std::cout<<t3<<std::endl;
    }
    return ans;
}

Vector softmax(Vector v)
{
    Vector ans;
    Vector mid;
    double sum=0;
    int size=v.getSize();
    for(int i=0; i<size; i++)
    {
        double t1=exp(v.get(i));
        //std::cout<<t1<<std::endl;
        mid.push((float)(t1));
        sum=sum+t1;
    }
    
    for(int i=0; i<size; i++)
    {
        float t2=(float)(mid.get(i)/sum);
        //std::cout<<t2<<std::endl;
        ans.push(t2);
    }
    return ans;
    
}

Matrix tanh(Matrix m)
{
    int n=m.get_max_rows();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            float t1=m.get(i,j);
            double t2=exp(t1);
            double t3=exp(t1*(-1));
            float t4=(float)((t2-t3)/(t2+t3));
            std::cout<<t4<<std::endl;
            m.set(t4,i,j);
        }
    }
    return m;
}

Matrix relu(Matrix m)
{
    int n=m.get_max_rows();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            float t1=m.get(i,j);
            if (t1<0)
            {
                m.set(0,i,j);
            }
        }
    }
    return m;
}

Matrix maxpooling(Matrix m, int width, int stride=1)
{
    int n=m.get_max_rows();
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
    Matrix ans=Matrix(rows);
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<rows; j++)
        {
            float max=m.get(i*stride, j*stride);
            for (int iw=i*stride; iw<i*stride+width; iw++)
            {
                //std::cout<<"iw"<<std::endl;
                for (int jw=j*stride; jw<j*stride+width; jw++)
                {
                    //std::cout<<"iw"<<std::endl;
                    float temp=m.get(iw, jw);
                    if (max<temp)
                    {
                        //std::cout<<temp<<std::endl;
                        max=temp;
                    }
                }
            }
            //std::cout<<max<<std::endl;
            ans.set(max,i,j);
        }
    }
    return ans;
}

Matrix average_pooling(Matrix m, int width, int stride=1)
{
    int n=m.get_max_rows();
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
    Matrix ans=Matrix(rows);
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
                    float temp=m.get(iw, jw);
                    sum=sum+temp;
                }
            }
            //std::cout<<max<<std::endl;
            float average=sum/square;
            ans.set(average,i,j);
        }
    }
    return ans;
    
}

/*int main() {
    // insert code here...
    //Vector v=read_file("afile.txt");
    //Vector ans=sigmoid(v);
    //Vector ans2=softmax(v);
    
    Matrix m=Matrix(5);
    m.set(-1,0,0);
    m.set(2,0,1);
    m.set(3,0,2);
    m.set(4,0,3);
    m.set(-1,0,4);
    m.set(2,1,0);
    m.set(3,1,1);
    m.set(4,1,2);
    m.set(-1,1,3);
    m.set(2,1,4);
    m.set(3,2,0);
    m.set(4,2,1);
    m.set(-1,2,2);
    m.set(2,2,3);
    m.set(3,2,4);
    m.set(4,3,0);
    m.set(-1,3,1);
    m.set(2,3,2);
    m.set(3,3,3);
    m.set(4,3,4);
    m.set(-1,4,0);
    m.set(2,4,1);
    m.set(3,4,2);
    m.set(4,4,3);
    m.set(5,4,4);
    //Matrix t=relu(m);
    
    Matrix ans=average_pooling(m,3,2);
    int n=ans.get_max_rows();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            std::cout<<ans.get(i,j)<<std::endl;
        }
    }
    return 0;
}*/

int main(int argc, char** argv)
{
    std::cout<<"yo"<<std::endl;
    if (argc==2 && *argv[1]=='Y')
    {
        std::cout<<"Hi"<<std::endl;
    }
    
}
