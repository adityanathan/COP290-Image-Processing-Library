//
//  Vector.cpp
//  COP_1
//
//  Created by Poorva garg on 12/01/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//

#include "Vector.h"
//#include <iostream>

Vector::Vector()
{
    vec = new float[max];
}

void Vector::push(float a)
{
    //std::cout<<a<<std::endl;
    n++;
    
    if(n>=max)
    {
        max = max * 2;
        float *temp = new float[max];
        for(int i = 0; i < n; i++)
        {
            temp[i] = vec[i];
        }
        delete [] vec;
        vec = temp;
    }
    
    vec[n-1] = a;
}

float Vector::get(int i)
{
    return vec[i];
}

int Vector::getSize()
{
    return n;
}
