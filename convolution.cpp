#include<string>
#include<iostream>
#include<vector>
using namespace std;


vector<vector<int>> reflect_kernel(vector<vector<int>> kernel)
{
  int temp;
  vector<vector<int>> reflected_kernel = kernel;
  int rows = kernel.size();
  for(int i=0;i<rows;i++)
  {
    for(int j=i;j<rows;j++)
    {
      temp = reflected_kernel[i][j];
      reflected_kernel[i][j]=reflected_kernel[j][i];
      reflected_kernel[j][i]=temp;
    }
  }

  for(int i=0; i<rows;i++)
  {
    for(int j=rows - i - 1;j<rows;j++)
    {
      temp = reflected_kernel[i][j];
      reflected_kernel[i][j] = reflected_kernel[rows - j - 1][rows - i - 1];
      reflected_kernel[rows - j-1][rows - i-1] = temp;
    }
  }

  return reflected_kernel;
}

vector<vector<int>> convolve(vector<vector<int>> matrix, vector<vector<int>> kernel)
{
  vector<vector<int>> reflected_kernel = reflect_kernel(kernel);
  int m = matrix.size();
  int k = kernel.size();
  vector < vector <int> > convoluted_matrix(m-k+1, std::vector<int>(m-k+1, 0));

  int x, y, i, j, sum;

  for(x=0;x<m-k+1;x++)
  {
    for(y=0;y<m-k+1;y++)
    {
      sum=0;
      for(i=x;i<x+k;i++)
      {
        for(j=y;j<y+k;j++)
        {
          sum = sum + reflected_kernel[i-x][j-y]*matrix[i][j];
        }
      }
      convoluted_matrix[x][y]=sum;
    }
  }
  return convoluted_matrix;
}

vector<vector<int>> padding(vector<vector<int>> matrix, int pad)
{
  int m = matrix.size();
  int dim = m+(2*pad);
  vector < vector <int> > padded_matrix(dim, std::vector<int>(dim, 0));

  for(int i=0; i<dim; i++)
  {
    for(int j=0; j<dim; j++)
    {
      if((i>=pad && i<=pad+m-1) && (j>=pad && j<=pad+m-1))
      {
        padded_matrix[i][j]=matrix[i-pad][j-pad];
      }
    }
  }
  return padded_matrix;
}

vector<vector<int>> matrix_multiply(vector<vector<int>> mat1, vector<vector<int>> mat2)
{
  vector<vector<int>> result(mat1.size(), vector<int>(mat2[1].size(),0));
  for(int i=0;i<mat1.size();i++)
	{
		for(int j=0;j<mat2[1].size();j++)
		{
			for(int k=0;k<n;++k)
				result[i][j]=result[i][j]+(result[i][k]*result[k][j]);
	  }
  }
  return result;
}

vector < vector <int> > toeplitz_convolve(vector<vector<int>> matrix, vector<vector<int>> kernel)
{
  int m = matrix.size();
  int k = kernel.size();
  int dim = m+k-1;
  vector<vector<int>> padded_kernel(dim, vector<int>(dim,0));

  for(int i = 0; i<k; i++)
  {
    for(int j=0; j<k; j++)
    {
      padded_kernel[i][j]=kernel[i][j];
    }
  }
  vector<<vector<vector<int>>> h(dim,vector<vector<int>>(dim,vector<int>(m,0)));

  for(int z=0; z<dim; z++)
  {
    vector<int> a = padded_kernel[i];
    for(int y=0; y<m; y++)
    {
      int i=0;
      for (int x = i; x < dim; x++)
      {
        h[z][x][y]=a[x-i];
        i++;
      }
    }
  }

  vector<vector<int>> h_2d(dim*dim, vector<int>(m*m,0));
  for(i=0; i<dim*dim; i+=dim)
  {
    for(j=0;j<m*m; j+=m)
    {
      if(b<0)
      {
        b=dim-1;
      }
      for(int k=i;k<i+dim;k++)
      {
        for(int l=j;l<j+m;l++)
        {
          h_2d[k][l]=h[b][k-i][l-j];
        }
      }
      b--;
    }
  }

  vector<int> resized_input(m*m,0);
  k=0;
  for(i=0; i<m; i++)
  {
    for(j=0; j<m; j++)
    {
      resized_input[k]=matrix[i][j];
      k++;
    }
  }

  vector<vector<int>> output = matrix_multiply(h_2d, resized_input);

  


  }
}


int main()
{
  vector < vector <int> > Mat(3, std::vector<int>(3, 0));
  vector < vector <int> > input(5, std::vector<int>(5, 0));
  int t=0;
  for(int i=0; i<3; i++)
  {
    for(int j=0;j<3;j++)
    {
      Mat[i][j]=t++;
      cout<<t-1;
    }
    cout<<endl;
  }
  cout<<endl;
  t=0;
  for(int i=0; i<5; i++)
  {
    for(int j=0;j<5;j++)
    {
      input[i][j]=t++;
      cout<<t-1;
    }
    cout<<endl;
  }
  cout<<endl;

  vector<vector<int>> padded = padding(input, 1);
  for(int i=0; i<7; i++)
  {
    for(int j=0;j<7;j++)
    {
      cout<<padded[i][j];
    }
    cout<<endl;
  }
  cout<<endl;

  vector < vector <int> > Mat2 = reflect_kernel(Mat);
  for(int i=0; i<3; i++)
  {
    for(int j=0;j<3;j++)
    {
      cout<<Mat2[i][j];
    }
    cout<<endl;
  }
  cout<<endl;
  vector < vector <int> > Mat3 = convolve(input,Mat);

  for(int i=0; i<3; i++)
  {
    for(int j=0;j<3;j++)
    {
      cout<<Mat3[i][j]<<" ";
    }
    cout<<endl;
  }

  Mat3 = convolve(padded,Mat);

  for(int i=0; i<5; i++)
  {
    for(int j=0;j<5;j++)
    {
      cout<<Mat3[i][j]<<" ";
    }
    cout<<endl;
  }

  return 0;
}
