#include<string>
#include<iostream>
#include<vector>
#include <fstream>
#include <cmath>
#include<string.h>
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////
//Poorva's code
vector<float> read_file(std::string s)
{
    try
    {
        vector<float> v;
        std::ifstream infile;
        infile.open(s);
        if(!infile)
        {
            throw "Error in file opening, kindly check the path of the file given";
        }
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
    catch (std::invalid_argument)
    {
        //cout<<"ha"<<endl;
        throw "Either the data in your file is not valid or you have given a larger number of rows.";
    }
    catch (const char* msg)
    {
        //cout<<msg<<endl;
        throw msg;
    }
}

vector<float> sigmoid(vector<float> v)
{
    vector<float> ans;
    int size=static_cast<int>(v.size());
    //std::cout<<size<<std::endl;
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
    int size=static_cast<int>(v.size());
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

vector<vector<float> > tanh(vector<vector<float> > m)
{
    int n=static_cast<int>(m.size());
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            float t1=m[i][j];
            double t2=exp(t1);
            double t3=exp(t1*(-1));
            float t4=(float)((t2-t3)/(t2+t3));
            //std::cout<<t4<<std::endl;
            m[i][j]=t4;
        }
    }
    return m;
}

vector<vector<float> > relu(vector<vector<float> > m)
{
    int n=static_cast<int>(m.size());
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

vector<vector<float> > maxpooling(vector<vector<float> > m, int width, int stride=1)
{
    int n=static_cast<int>(m.size());
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
    vector<vector<float> > ans;
    for (int i=0; i<rows; i++)
    {
        vector<float> v(rows,0);
        ans.push_back(v);
    }
    //std::cout<<rows<<std::endl;
    //vector<vector<float> > ans = vector<vector<float> >(rows);
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

vector<vector<float> > average_pooling(vector<vector<float> > m, int width, int stride=1)
{
    int n=static_cast<int>(m.size());
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
    vector<vector<float> > ans(rows,vector<float>(rows,0));
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

/////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//Aditya's Code

vector<vector<float> > reflect_kernel(vector<vector<float> > kernel)
{
    float temp;
    vector<vector<float> > reflected_kernel = kernel;
    int rows = static_cast<int>(kernel.size());
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

vector<vector<float> > convolve(vector<vector<float> > matrix, vector<vector<float> > kernel)
{
    vector<vector<float> > reflected_kernel = reflect_kernel(kernel);
    int m =static_cast<int>( matrix.size());
    int k = static_cast<int>(kernel.size());
    vector < vector <float> > convoluted_matrix(m-k+1, std::vector<float>(m-k+1, 0));

    int x, y, i, j;
    float sum;

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

vector<vector<float> > padding(vector<vector<float> > matrix, int pad)
{
    int m = static_cast<int>(matrix.size());
    int dim = m+(2*pad);
    vector < vector <float> > padded_matrix(dim, std::vector<float>(dim, 0));

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

vector<vector<float> > matrix_multiply(vector<vector<float> > mat1, vector<vector<float> > mat2)
{
    if(mat2.size()==mat1[0].size())
    {
        vector<vector<float> > result(mat1.size(), vector<float>(mat2[1].size(),0));
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
        throw "Matrix Dimensions don't match!";
        //return mat1;
    }
}

vector < vector <float> > toeplitz_convolve(vector<vector<float> > matrix, vector<vector<float> > kernel)
{
    int m = static_cast<int>(matrix.size());
    int k = static_cast<int>(kernel.size());
    int dim = m+k-1;
    vector<vector<float> > padded_kernel(dim, vector<float>(dim,0));

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

    vector<vector<vector<float> > > h(dim,vector<vector<float> >(dim,vector<float>(m,0)));

    for(int z=0; z<dim; z++)
    {
        vector<float> a = padded_kernel[z];
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

    vector<vector<float> > h_2d(dim*dim, vector<float>(m*m,0));
    int b=0;//Poorva-I don't know if it is to be made float or not
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
    vector<vector<float> > resized_input(m*m,vector<float>(1,0));
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

    vector<vector<float> > output = matrix_multiply(h_2d, resized_input);



    vector<vector<float> > resized_output(m+k-1,vector<float>(m+k-1));

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
    vector<vector<float> > trimmed_output(m-k+1, vector<float>(m-k+1,0));
    for(int i=k-1;i<m;i++)
    {
        for(int j=k-1;j<m;j++)
        {
            trimmed_output[i-k+1][j-k+1]=resized_output[i][j];
        }
    }
    return trimmed_output;
}

vector<vector<float> > read_matrix(string s, int rows)
{
    try {
        ifstream infile;
        infile.open (s);
        string str;
        if (!infile)
        {
            throw "The file can't be opened, kindly check the path";
        }
        vector<vector<float> > mat;
        for (int i=0; i<rows; i++)
        {
            vector<float> v(rows,0);
            mat.push_back(v);
        }
        float data;
        //cout<<3<<endl;
        //Will read only till max capacity
        //while(getline(infile, str))
        //{
        for (int i=0; i<rows;i++)
        {
            for (int j=0; j<rows; j++)
            {
                getline(infile, str);
                data=stof(str);
                mat[j][i]=data;
                //std::cout<<data<<std::endl;
            }
        }
        //std::cout<<data<<std::endl;
        //}
        return mat;
    } catch (std::invalid_argument) {
        throw "The data in the file provided by you is not valid";
    } catch (const char* msg)
    {
        throw msg;
    }

}
//////////////////////////////////////////////////////////////////////////////////

/*int main()
{
    vector < vector <float> > Mat(3, std::vector<float>(3, 0));
    vector < vector <float> > input(5, std::vector<float>(5, 0));
    int t=0;//Poorva-I don't know if it is to be converted to float or not
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
            cout<<t-1<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    vector<vector<float> > padded = padding(input, 1);
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

    vector < vector <float> > Mat2 = reflect_kernel(Mat);
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
    vector < vector <float> > Mat3 = convolve(input,Mat);
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
    vector<vector<float> > Mat7=toeplitz_convolve(input,Mat);
    vector<vector<float> > Mat8=toeplitz_convolve(padded, Mat);
    cout<<"toeplitz convolution by sliding window"<<endl;
    for(int i=0; i<Mat8.size(); i++)
    {
        for(int j=0;j<Mat8[0].size();j++)
        {
            cout<<Mat8[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    /////////////////////
    // insert code here...
    //Vector v=read_file("afile.txt");
    //Vector ans=sigmoid(v);
    //Vector ans2=softmax(v);

    vector<vector<float> > m(5,vector<float>(5,0));
    m[0][0]=-1;
    m[0][1]=2;
    m[0][2]=3;
    m[0][3]=4;
    m[0][4]=-1;
    m[1][0]=2;
    m[1][1]=3;
    m[1][2]=4;
    m[1][3]=-1;
    m[1][4]=2;
    m[2][0]=3;
    m[2][1]=4;
    m[2][2]=-1;
    m[2][3]=2;
    m[2][4]=3;
    m[3][0]=4;
    m[3][1]=-1;
    m[3][2]=2;
    m[3][3]=3;
    m[3][4]=4;
    m[4][0]=-1;
    m[4][1]=2;
    m[4][2]=3;
    m[4][3]=4;
    m[4][4]=5;
    //Matrix t=relu(m);
    read_file("afile.txt");
    vector<vector<float> > ans=read_matrix("afile.txt", 3);
    //int n=static_cast<int>(ans.size());
    //std::cout<<n<<std::endl;
    for(int i=0; i<3; i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    //////////////////////

    return 0;
}*/

int main(int argc, char *argv[])
{
    try {
        if (argc==3)
        {
            if (strcmp(argv[1], "sigmoid")==0)
            {
                vector<float> input=read_file(argv[2]);
                vector<float> ans=sigmoid(input);
                int n=static_cast<int>(ans.size());
                for(int i=0; i<n; i++)
                {
                    cout<<ans[i]<<endl;
                }
                cout<<endl;
            }
            else if (strcmp(argv[1], "softmax")==0)
            {
                vector<float> input=read_file(argv[2]);
                vector<float> ans=softmax(input);
                int n=static_cast<int>(ans.size());
                for(int i=0; i<n; i++)
                {
                    cout<<ans[i]<<endl;
                }
                cout<<endl;
            }
            else
            {
                throw "Your function call is invalid, maybe you wanted to call softmax or sigmoid ?";
            }
        }
        else if (argc==4)
        {
            if (strcmp(argv[1], "relu")==0)
            {
                int rows=stoi(argv[3]);
                vector<vector<float> > input=read_matrix(argv[2], rows);
                //cout<<argv[2]<<endl;
                vector<vector<float> > ans=relu(input);
                for(int i=0; i<rows; i++)
                {
                    for(int j=0;j<rows;j++)
                    {
                        cout<<input[i][j]<<" ";
                    }
                    cout<<endl;
                }
            }
            else if(strcmp(argv[1], "tanh")==0)
            {
                int rows=stoi(argv[3]);
                vector<vector<float> > input=read_matrix(argv[2], rows);
                vector<vector<float> > ans=tanh(input);
                for(int i=0; i<rows; i++)
                {
                    for(int j=0;j<rows;j++)
                    {
                        cout<<ans[i][j]<<" ";
                    }
                    cout<<endl;
                }
            }
            else
            {
                throw "Your function call is invalid, maybe you wanted to call relu or tanh ?";
            }
        }
        else if (argc==6)
        {
            if (strcmp(argv[1], "maxpool")==0)
            {
                int rows=stoi(argv[3]);
                int width=stoi(argv[4]);
                int stride=stoi(argv[5]);
                vector<vector<float> > input=read_matrix(argv[2], rows);
                vector<vector<float> > ans=maxpooling(input, width, stride);
                int ans_rows=static_cast<int>(ans.size());
                for(int i=0; i<ans_rows; i++)
                {
                    for(int j=0;j<ans_rows;j++)
                    {
                        cout<<ans[i][j]<<" ";
                    }
                    cout<<endl;
                }
            }
            else if (strcmp(argv[1], "average_pool")==0)
            {
                int rows=stoi(argv[3]);
                int width=stoi(argv[4]);
                int stride=stoi(argv[5]);
                vector<vector<float> > input= read_matrix(argv[2], rows);
                vector<vector<float> > ans= average_pooling(input, width, stride);
                int ans_rows=static_cast<int>(ans.size());
                for(int i=0; i<ans_rows; i++)
                {
                    for(int j=0;j<ans_rows;j++)
                    {
                        cout<<ans[i][j]<<" ";
                    }
                    cout<<endl;
                }
            }
            else if (strcmp(argv[1], "convolve_without_padding")==0)
            {
                int m_rows=static_cast<int>(stoi(argv[3]));
                int k_rows=static_cast<int>(stoi(argv[5]));
                if (m_rows>=k_rows)
                {
                    vector<vector<float> > input= read_matrix(argv[2], m_rows);
                    vector<vector<float> > kernel=read_matrix(argv[4], k_rows);
                    vector<vector<float> > ans=convolve(input, kernel);
                    int ans_rows=static_cast<int>(ans.size());
                    for(int i=0; i<ans_rows; i++)
                    {
                        for(int j=0;j<ans_rows;j++)
                        {
                            cout<<ans[i][j]<<" ";
                        }
                        cout<<endl;
                    }
                }
                else
                {
                    throw "The kernel matrix should be smaller than input matrix.";
                }
            }
            else if (strcmp(argv[1], "convolve_with_padding")==0)
            {
                int m_rows=static_cast<int>(stoi(argv[3]));
                int k_rows=static_cast<int>(stoi(argv[5]));
                if (m_rows>=k_rows)
                {
                    if (k_rows%2==1)
                    {
                        vector<vector<float> > input=read_matrix(argv[2], m_rows);
                        vector<vector<float> > kernel=read_matrix(argv[4], k_rows);
                        int pad=(k_rows-1)/2;
                        vector<vector<float> > padded_input=padding(input, pad);
                        vector<vector<float> > ans=convolve(padded_input, kernel);
                        int ans_rows=static_cast<int>(ans.size());
                        for(int i=0; i<ans_rows; i++)
                        {
                            for(int j=0;j<ans_rows;j++)
                            {
                                cout<<ans[i][j]<<" ";
                            }
                            cout<<endl;
                        }
                    }
                    else
                    {
                        throw "If kernel contains odd rows, padding is not possible.";
                    }
                }
                else
                {
                    throw "The kernel matrix should be smaller than input matrix.";
                }
            }
            else if (strcmp(argv[1], "convolve_with_padding_matrixmult")==0)
            {
                int m_rows=static_cast<int>(stoi(argv[3]));
                int k_rows=static_cast<int>(stoi(argv[5]));
                if (m_rows>=k_rows)
                {
                    if (k_rows%2==1)
                    {
                        vector<vector<float> > input=read_matrix(argv[2], m_rows);
                        vector<vector<float> > kernel=read_matrix(argv[4], k_rows);
                        int pad=(k_rows-1)/2;
                        vector<vector<float> > padded_input=padding(input, pad);
                        vector<vector<float> > ans=toeplitz_convolve(padded_input, kernel);
                        int ans_rows=static_cast<int>(ans.size());
                        for(int i=0; i<ans_rows; i++)
                        {
                            for(int j=0;j<ans_rows;j++)
                            {
                                cout<<ans[i][j]<<" ";
                            }
                            cout<<endl;
                        }
                    }
                    else
                    {
                        throw "If kernel contains odd rows, padding is not possible.";
                    }
                }
                else
                {
                    throw "The kernel matrix should be smalller than input matrix.";
                }

            }
            else if (strcmp(argv[1], "convolve_without_padding_matrixmult")==0)
            {
                int m_rows=static_cast<int>(stoi(argv[3]));
                int k_rows=static_cast<int>(stoi(argv[5]));
                if (m_rows>=k_rows)
                {
                    vector<vector<float> > input= read_matrix(argv[2], m_rows);
                    vector<vector<float> > kernel=read_matrix(argv[4], k_rows);
                    vector<vector<float> > ans=toeplitz_convolve(input, kernel);
                    int ans_rows=static_cast<int>(ans.size());
                    for(int i=0; i<ans_rows; i++)
                    {
                        for(int j=0;j<ans_rows;j++)
                        {
                            cout<<ans[i][j]<<" ";
                        }
                        cout<<endl;
                    }
                }
                else
                {
                    throw "The kernel matrix should be smaller than input matrix.";
                }
            }
            else
            {
                throw "Your function call is invalid, maybe you wanted to call subsampling or convolution related functions";
            }
        }
        else
        {
            throw "The number of arguments you have given is inappropriate";
        }
    } catch (std::invalid_argument) {
        cout<<"You have given some invalid arguments"<<endl;
        cout<<"Please refer to README for further help"<<endl;
    } catch (const char* msg)
    {
        cout<<msg<<endl;
        cout<<"Please refer to README for further help"<<endl;
    }
    catch (...)
    {
        cout<<"Thera is something wrong with the arguments you have provided or the files you are using to input matrices/vectors"<<endl;
        cout<<"Please refer to README for further help"<<endl;
    }
    return 0;
}
