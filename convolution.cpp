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
  if(mat2.size()==mat1[0].size())
  {
    vector<vector<int>> result(mat1.size(), vector<int>(mat2[1].size(),0));
    for(int i=0;i<mat1.size();i++)
  	{
  		for(int j=0;j<mat2[1].size();j++)
  		{
  			for(int k=0;k<mat2.size();k++)
  				result[i][j]=result[i][j]+(mat1[i][k]*mat2[k][j]);
  	  }
    }
    return result;
  }
  else
  {
    //Throw Exception
    cout<<"Matrix Dimensions don't match!"<<endl;
  }
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

  // for(int i = 0; i<padded_kernel.size(); i++)
  // {
  //   for(int j=0; j<padded_kernel[0].size(); j++)
  //   {
  //     cout<<padded_kernel[i][j]<<" ";
  //   }
  //   cout<<endl;
  // }
  // cout<<endl;

  vector<vector<vector<int>>> h(dim,vector<vector<int>>(dim,vector<int>(m,0)));

  for(int z=0; z<dim; z++)
  {
    vector<int> a = padded_kernel[z];
    int i=0;
    for(int y=0; y<m; y++)
    {
      for (int x = i; x < dim; x++)
      {
        h[z][x][y]=a[x-i];
      }
      i++;
    }
  }
  // for(int a=0; a<h.size();a++)
  // {
  //   for(int i = 0; i<h[0].size(); i++)
  //   {
  //     for(int j=0; j<h[0][0].size(); j++)
  //     {
  //       cout<<h[a][i][j]<<" ";
  //     }
  //     cout<<endl;
  //   }
  //   cout<<endl;
  // }
  // cout<<endl;

  vector<vector<int>> h_2d(dim*dim, vector<int>(m*m,0));
  int b=0;
  for(int i=0; i<dim*dim; i+=dim)
  {
    b=i/dim;
    for(int j=0;j<m*m; j+=m)
    {
      if(b<0)
      {
        b=dim-1;
      }
      for(int p=i;p<i+dim;p++)
      {
        for(int l=j;l<j+m;l++)
        {
          h_2d[p][l]=h[b][p-i][l-j];
        }
      }
      b--;
    }
  }

  // for(int i = 0; i<h_2d.size(); i++)
  // {
  //   for(int j=0; j<h_2d[0].size(); j++)
  //   {
  //     cout<<h_2d[i][j]<<" ";
  //   }
  //   cout<<endl;
  // }
  // cout<<endl;
  vector<vector<int>> resized_input(m*m,vector<int>(1,0));
  int p=0;
  for(int i=0; i<m; i++)
  {
    for(int j=0; j<m; j++)
    {
      resized_input[p][0]=matrix[i][j];
      p++;
    }
  }

  // for(int i = 0; i<resized_input.size(); i++)
  // {
  //   for(int j=0; j<resized_input[0].size(); j++)
  //   {
  //     cout<<resized_input[i][j]<<" ";
  //   }
  //   cout<<endl;
  // }
  // cout<<endl;

  vector<vector<int>> output = matrix_multiply(h_2d, resized_input);



  vector<vector<int>> resized_output(m+k-1,vector<int>(m+k-1));

  p=0;
  for(int i=0;i<m+k-1;i++)
  {
    for(int j=0;j<m+k-1;j++)
    {
      resized_output[i][j]=output[p][0];
      p++;
      // cout<<resized_output[i][j]<<" ";
    }
    // cout<<endl;
  }
  // cout<<endl;
  vector<vector<int>> trimmed_output(m-k+1, vector<int>(m-k+1,0));
  for(int i=k-1;i<m;i++)
  {
    for(int j=k-1;j<m;j++)
    {
      trimmed_output[i-k+1][j-k+1]=resized_output[i][j];
    }
  }
  return trimmed_output;
}


int main()
{
  vector < vector <int> > Mat(3, std::vector<int>(3, 0));
  vector < vector <int> > input(5, std::vector<int>(5, 0));
  int t=0;
  cout<<"kernel"<<endl;
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
  cout<<"input_matrix"<<endl;
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
  cout<<"padded input matrix"<<endl;
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
  cout<<"reflected kernel"<<endl;
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
  cout<<"normal convolution by sliding window"<<endl;
  for(int i=0; i<3; i++)
  {
    for(int j=0;j<3;j++)
    {
      cout<<Mat3[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  Mat3 = convolve(padded,Mat);
  cout<<"normal convolution by sliding window with padding"<<endl;
  for(int i=0; i<5; i++)
  {
    for(int j=0;j<5;j++)
    {
      cout<<Mat3[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  vector<vector<int>> Mat7=toeplitz_convolve(input,Mat);
  cout<<"toeplitz convolution by sliding window"<<endl;
  for(int i=0; i<Mat7.size(); i++)
  {
    for(int j=0;j<Mat7[0].size();j++)
    {
      cout<<Mat7[i][j]<<" ";
    }
    cout<<endl;
  }

  return 0;
}
