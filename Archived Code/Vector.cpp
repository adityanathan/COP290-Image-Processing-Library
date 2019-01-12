#include "Vector.h"

Vector::Vector()
{
    vec = new float[max];
}

void Vector::push(float a)
{
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
    
    vec[n] = a;
}

float Vector::get(int i)
{
    return vec[i];
}
