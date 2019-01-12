#include "Matrix.h"
#include <string>
#include <fstream>
//This library can handle only square matrices
Matrix::Matrix(int max_row)
{
    this->max_row = max_row;
    mat = new float*[max_row];

    for(int i = 0; i < max_row; i++)
    {
        mat[i] = new float[max_row];
    }
}

Matrix::Matrix(float** obj)
{
    int r=max_row;

    Matrix mat2(r);

    for(int i = 0; i < r; i++)
    {
        for(int j=0; j<r; j++)
        {
            mat2.set(obj[i][j],i,j);
        }
    }
}

// Matrix::Matrix(Matrix &obj)
// {
//     int r=obj.get_max_rows();

//     Matrix mat2(r);

//     for(int i = 0; i < r; i++)
//     {
//         for(int j=0; j<r; j++)
//         {
//             mat2.set(obj.get(i,j),i,j);
//         }
//     }
// }

// void Matrix::push(float a)
// {
//     if(row==max_row)
//     {
//         col++; row=0;
//         if(col>=max_col)
//         {
//             max_col=max_col*2;
//             float** temp = new float*[max_row];

//             for(int i = 0; i < max_row; i++)
//                 temp[i] = new float[max_col];
            
//             for(int i=0;i<max_row; i++)
//             {
//                 for(int j=0; j<col; j++)
//                 {
//                     temp[i][j]=mat[i][j];
//                 }
//             }

//             for(int i = 0; i < max_row; ++i)
//                 delete [] mat[i];

//             for(int i = 0; i < max_row; i++)
//                 mat[i] = temp[i];
//         }
//         mat[row][col] = a;
//     }
// }

void Matrix::create_matrix(string path)
{

    ifstream myFile;
    myFile.open(path);
    string str;
//Will read only till max capacity
    if (myFile.is_open()) 
    {
        int i,j;
        for(i=0; i<max_row; i++)
        {
            for(j=0; j<max_row; j++)
            {
                getline(myFile,str);
                mat[i][j]=stoi(str);
            }
        }
        if(i!=max_row || j!=max_row)
        {
            //raise Exception
        }
    }
}

float Matrix::get(int i, int j)
{
    return mat[i][j];
}

void Matrix::set(float a, int i, int j)
{
    mat[i][j] = a;
}

void Matrix::delete_matrix()
{
    for(int i = 0; i < max_row; ++i)
        delete [] mat[i];

    delete[] mat;
}

int Matrix::get_max_rows()
{
    return max_row;
}

Matrix Matrix::reflect_matrix()
{
    //Reflect about (0,0) to (n,n) diagonal
    float temp;
    Matrix mat2(mat);
    for(int i=0; i< max_row; i++)
    {
        for(int j=0; j<max_row; j++)
        {
            if(i!=j)
            {
                temp = mat2.get(i,j);
                mat2.set(mat2.get(j,i),i,j);
                mat2.set(temp,j,i);
            }
        }
    }

    for(int i=0; i< max_row; i++)
    {
        for(int j=0; j<max_row; j++)
        {
            if(i!=j)
            {
                temp = mat2.get(i,j);
                mat2.set(mat2.get(max_row-j,max_row-i),i,j);
                mat2.set(temp,max_row-j,max_row-i);
            }
        }
    }
}