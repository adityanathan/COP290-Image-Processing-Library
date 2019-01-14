//
//  Vector.cpp
//  COP_1
//
//  Created by Poorva garg on 12/01/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//

class Vector
{
    
private:
    int max = 10;
    float* vec;
    int n = 0;
    
public:
    //Constructor
    Vector();
    
    //Setters
    void push(float a);
    
    //Getters
    float get(int i);
    
    int getSize();
    
    
};
