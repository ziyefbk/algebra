#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

int minus_one_pow(int times){
    return (times%2)?-1:1;
}

Matrix ad_matrix(Matrix a,int i,int j){
    int n = a.cols;
    if(n==1)
    {
        return create_matrix(0,0);
    }
    else{
        Matrix m_ = create_matrix(n-1,n-1);
                int x = 0,y = 0;
                for(int l = 0;l<n;l++)
                {
                    y = 0;
                    if(l==i) continue;
                    for(int m = 0;m<n;m++)
                    {
                        if(m==j) continue;
                        m_.data[x][y] = a.data[l][m];
                        y++;
                    }
                    x++;
                }
        return m_;
    }
}


Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    if(a.cols!=b.cols||a.rows!=b.rows)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    int cols = a.cols,rows = a.rows;
    Matrix m = create_matrix(rows,cols);
    for(int i = 0;i<rows;i++)
    {
        for(int j = 0;j<cols;j++)
        {
            m.data[i][j] = a.data[i][j]+b.data[i][j];
        }
    }
    return m;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo
    if(a.cols!=b.cols||a.rows!=b.rows)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    int cols = a.cols,rows = a.rows;
    Matrix m = create_matrix(rows,cols);
    for(int i = 0;i<rows;i++)
    {
        for(int j = 0;j<cols;j++)
        {
            m.data[i][j] = a.data[i][j]-b.data[i][j];
        }
    }
    return m;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    // ToDo
    if(a.cols!=b.rows)
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    int rows = a.rows,cols = b.cols,p = a.cols;
    Matrix m = create_matrix(rows,cols);
    for(int i = 0;i<rows;i++)
    {
        for(int j = 0;j<cols;j++)
        {
            m.data[i][j] = 0;
            for(int k = 0;k<p;k++)
            {
                m.data[i][j]+=a.data[i][k]*b.data[k][j];
            }
        }
    }
    return m;
}

Matrix scale_matrix(Matrix a, double k)
{
    // ToDo
    int rows = a.rows,cols = a.cols;
    Matrix m = create_matrix(rows,cols);
    for(int i = 0;i<rows;i++)
    {
        for(int j = 0;j<cols;j++)
        {
            m.data[i][j] = a.data[i][j]*k;
        }
    }
    return m;
}

Matrix transpose_matrix(Matrix a)
{
    // ToDo
    int rows = a.rows,cols = a.cols;
    Matrix m = create_matrix(cols,rows);
    for(int i = 0;i<rows;i++)
    {
        for(int j = 0;j<cols;j++)
        {
            m.data[j][i] = a.data[i][j];
        }
    }
    return m;
}

double det_matrix(Matrix a)
{
    // ToDo
    double det = 0;
    if(a.cols!=a.rows){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    int n = a.cols;
    if(n==1)
    {
        return a.data[0][0];
    }
    else if(n==2)
    {
        return a.data[0][0]*a.data[1][1]-a.data[0][1]*a.data[1][0];
    }
    else{
        for(int i = 0;i<n;i++)
        {
            Matrix m_ = ad_matrix(a,0,i);
            //print_matrix(m_);
            //printf("%d %d %f\n",0,i,minus_one_pow(i)*a.data[0][i]*det_matrix(m_));
            det+=minus_one_pow(i)*a.data[0][i]*det_matrix(m_);
        }
    }
    return det;
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    if(det_matrix(a)==0||a.cols!=a.rows)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    double det = det_matrix(a);
    int n = a.cols;
    Matrix m = create_matrix(n,n);
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            m.data[i][j] = minus_one_pow(i+j)*det_matrix(ad_matrix(a,j,i))/det;
        }
    }
    return m;
    //create_matrix();
}

int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}

double trace_matrix(Matrix a)
{
    // ToDo
    if(a.cols!=a.rows)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    double trace = 0;
    int n = a.cols;
    for(int i = 0;i<n;i++)
    {
        trace+=a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}