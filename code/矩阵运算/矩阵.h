#pragma once
#include <stdio.h>  
#include <stdlib.h> 
#include<iostream>
using namespace std;
class matrix
{
public:
	int x;
	int y;
	double a[100];

	void set()
	{
		cout << "矩阵几乘几：" << endl;
		cin >> x >> y;

		cout << "请输入值：" << endl;
		
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				cin >> a[i*x + j];
				

			}

			

		}
	}
	matrix()
	{
		x = 2;
		y = 2;
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				a[i*x + j] = 0;


			}
		}
	}
	void add(const  matrix &a1, matrix &b)
	{
		x = a1.x;
		y = a1.y;

		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				a[i*x + j] = a1.a[i*x + j] + b.a[i*x + j];
			}

		}
	}
	void subtract(const  matrix &a1, matrix &b)
	{
		x = a1.x;
		y = a1.y;

		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				a[i*x + j] = a1.a[i*x + j] - b.a[i*x + j];
			}
		}
	}
	void multiply(const  matrix &a1, matrix &b)
	{
		x = a1.x;
		y = b.y;
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				int m = a1.y*i;
				for (int k = j; k < b.y*b.x; k = k + b.x)
				{
					
					a[i*x + j] += b.a[k] * a1.a[m];
					m = m++;

				}



			}
		}
	}
	void show()
	{
		for (int n = 0; n < x*y; n++)
		{
			cout << a[n];
			cout << " ";
			if ((n+1)%x == 0)
				cout << endl;

		}
	}



};