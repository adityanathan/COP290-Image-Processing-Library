/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//This library can handle only square matrices

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
        // Matrix(Matrix &obj);
        void create_matrix(string path);
        float get(int i, int j);
        void set(float a, int i, int j);
        void delete_matrix();
        int get_max_rows();
        void reflect_matrix();
};

  Matrix::Matrix (int max_row)
  {
    this->max_row = max_row;
    mat = new float *[max_row];

    for (int i = 0; i < max_row; i++)
      {
	        mat[i] = new float[max_row];
      }
  }

Matrix::Matrix (float **obj)
{
    int r = max_row;

    Matrix mat2 (r);

    for (int i = 0; i < r; i++)
      {
      	for (int j = 0; j < r; j++)
      	  {
      	    mat2.set (obj[i][j], i, j);
      	  }
      }
  }

  void Matrix::create_matrix (string path)
  {

    ifstream myFile;
    myFile.open (path);
    string str;
//Will read only till max capacity
    if (myFile.is_open ())
      {
	int i, j;
	for (i = 0; i < max_row; i++)
	  {
	    for (j = 0; j < max_row; j++)
	      {
		getline (myFile, str);
		mat[i][j] = stoi (str);
	      }
	  }
	if (i != max_row || j != max_row)
	  {
	    //raise Exception
	  }
      }
  }

  float Matrix::get (int i, int j)
  {
    return mat[i][j];
  }

  void Matrix::set (float a, int i, int j)
  {
    mat[i][j] = a;
    // cout<<a;
    // cout<<mat[i][j];
  }

  void Matrix::delete_matrix ()
  {
    for (int i = 0; i < max_row; ++i)
      delete[]mat[i];

    delete[]mat;
  }

  int Matrix::get_max_rows ()
  {
    return max_row;
  }

  void Matrix::reflect_matrix ()
  {
    //Reflect about (0,0) to (n,n) diagonal
    float temp;
    // Matrix mat2 (mat);
    for (int i = 0; i < max_row; i++)
    {
       for (int j = i; j < max_row; j++)
       {
           temp = mat[i][j];
           mat[i][j]=mat[j][i];
           mat[j][i]=temp;
       }
     }

     for (int i = 0; i < max_row; i++)
     {
        for (int j = max_row-i-1; j < max_row; j++)
        {
           temp = mat[i][j];
           mat[i][j]=mat[max_row - j-1][max_row - i-1];
           mat[max_row - j-1][max_row - i-1]=temp;
        }
      }
      // return mat2;
    }












    class Convolution
    {
        private:
            Matrix mat;
            Matrix kernel;

        public:
            Convolution(Matrix input_mat, Matrix kernel);
            void pad_matrix(int padding, int max_rows);
            Matrix convolve();

    };

    Convolution::Convolution(Matrix input_mat, Matrix kernel)
    {
        this->mat = input_mat;
        this->kernel = kernel;
    }

    void Convolution::pad_matrix(int padding, int max_rows)
    {
        if(padding>0)
        {
            max_rows = mat.get_max_rows();
            int dim = max_rows+(2*padding);
            int m=dim; int n =dim;
            Matrix A(dim);
            for(int i=0; i<=(dim-1); i++)
            {
                for(int j=1; j<=(dim-1); j++)
                {
                    if(i<padding || i>=(m+padding))
                    {
                        // A[i][j]=0;
                        A.set(0,i,j);
                    }
                    else
                    {
                        if(j<padding || j>=n)
                        {
                            // A[i][j]=0;
                            A.set(0,i,j);
                        }
                        else
                        {
                            // A[i][j]=mat[i-padding][j-padding];
                            A.set(mat.get(i-padding,j-padding),i,j);
                        }
                    }
                }
            }
            mat.delete_matrix();
            mat = A;
        }
    }

    Matrix Convolution::convolve()
    {
        int m = mat.get_max_rows();
        int k = kernel.get_max_rows();
        kernel.reflect_matrix();
        Matrix conv(m+k-1);
        int x,y,i,j,sum;
        for(x=0;x<m-k;x++)
        {
            for(y=0;y<m-k;y++)
            {
                sum=0;
                for(i=x;i<x+k;i++)
                {
                    for(j=y;j<y+k;j++)
                    {
                        sum = sum + kernel.get(i-x,j-y)*mat.get(i,j);
                    }
                }
                conv.set(sum,x,y);
            }
        }
        kernel.reflect_matrix();
        return conv;
    }

int main ()
{
  // cout << "Hello World";
  Matrix a(2);
  a.set(1,0,0);
  a.set(2,0,1);
  a.set(3,1,0);
  a.set(4,1,1);
  cout<<a.get_max_rows()<<endl;
  a.reflect_matrix();
  a.reflect_matrix();
  cout<<a.get(0,0);
  cout<<a.get(0,1)<<endl;
  cout<<a.get(1,0);
  cout<<a.get(1,1);

  return 0;
}

//Your errors are located in Matrix::reflect_matrix()
//Especially around copy constructors
