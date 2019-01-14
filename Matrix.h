//
//  Matric.cpp
//  COP_1
//
//  Created by Poorva garg on 12/01/19.
//  Copyright © 2019 Poorva garg. All rights reserved.
//
#include <string>
//#include <iostream>
class Matrix
{
private:
    float** mat;
    int max_row;
    int row=0;
    int col=0;
    
public:
    Matrix(int max_row);
    Matrix(float** obj);
    void create_matrix(std::string path);
    float get(int i, int j);
    void set(float a, int i, int j);
    void delete_matrix();
    int get_max_rows();
    Matrix reflect_matrix();
};
