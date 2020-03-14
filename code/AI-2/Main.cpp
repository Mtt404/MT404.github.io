// This is the code for the BNs inference
//
//  'The second project homework for Artifical Intelligence'
// 
// Yangang Wang, 2019/11/22, @SEU
//

#include <fstream>
#include <string>
#include <regex>
#include<iostream>
using namespace std;

void main(int argc, char** argv)
{
	// read the mat
	// the missing element is indicated by -1
	//
	int Mat_missing[100][100];
	{
		ifstream infile("mat_missing.txt");
		if (infile.is_open()) {
			string line;
			regex term(" ");
			int lineIdx = 0;
			while (!infile.eof()) {
				if (lineIdx >= 100) break;
				getline(infile, line);
				sregex_token_iterator it(line.begin(), line.end(), term, -1);
				sregex_token_iterator end;
				for (int i = 0; it != end; it++, i++) {
					string str = *it;
					Mat_missing[lineIdx][i] = atoi(str.c_str());
				}
				lineIdx++;
			}
			infile.close();
		}
	}
	//======================
	// please fill the following code by Bayes Network training and inference
	//
	// Yangang Wang, 2019/11/22, @SEU
	//

	// (1) todo...
	//统计概率
	int Mat_missing2[100][100] = { 0 };
	Mat_missing2[100][100] = Mat_missing[100][100];
	float p[11] = { 0 };
	int N[11] = { 0 };
	int  n = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int m = 0; m < 11; m++)
			{
				if (Mat_missing[i][j] == m)
				{
					N[m]++;
					n++;
					break;
				}
			}
		}
	}
	for (int i = 0; i < 11; i++)
	{
		p[i] = (float)N[i] / n;
	}
	//计算P（x0|x1,x2,x3,x4）x1代表上方，x2代表下方，x3代表左侧，x4代表右侧；
	//先估计P(x1|x0)P(x2|x0)P(x3|x0)P(x4|x0),再根据贝叶斯公式求
	int P1[11][11] = { 0 };
	int P2[11][11] = { 0 };
	int P3[11][11] = { 0 };
	int P4[11][11] = { 0 };
	float P11[11][11] = { 0 };
	float P22[11][11] = { 0 };
	float P33[11][11] = { 0 };
	float P44[11][11] = { 0 };
	int num1[11] = { 0 };
	int num2[11] = { 0 };
	int num3[11] = { 0 };
	int num4[11] = { 0 };
	float PL[11] = { 0 };
	int num_acc = 0;
	int num_lost = 99;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (Mat_missing[i][j] != -1 && i == 0 && j>0 && j<99)//边界
			{
				if (Mat_missing[i + 1][j] != -1)
				{
					P2[Mat_missing[i][j]][Mat_missing[i + 1][j]]++;
				}
				if (Mat_missing[i][j - 1] != -1)
				{
					P3[Mat_missing[i][j]][Mat_missing[i][j - 1]]++;
				}
				if (Mat_missing[i][j + 1] != -1)
				{
					P4[Mat_missing[i][j]][Mat_missing[i][j + 1]]++;
				}
			}
			if (Mat_missing[i][j] != -1 && j == 99 && i>0 && i<99)//边界
			{
				if (Mat_missing[i - 1][j] != -1)
				{
					P1[Mat_missing[i][j]][Mat_missing[i - 1][j]]++;
				}
				if (Mat_missing[i + 1][j] != -1)
				{
					P2[Mat_missing[i][j]][Mat_missing[i + 1][j]]++;
				}
				if (Mat_missing[i][j - 1] != -1)
				{
					P3[Mat_missing[i][j]][Mat_missing[i][j - 1]]++;
				}

			}
			if (Mat_missing[i][j] != -1 && j>0 && j<99 && i>0 && i<99)//内部
			{
				if (Mat_missing[i - 1][j] != -1)
				{
					P1[Mat_missing[i][j]][Mat_missing[i - 1][j]]++;
				}
				if (Mat_missing[i + 1][j] != -1)
				{
					P2[Mat_missing[i][j]][Mat_missing[i + 1][j]]++;
				}
				if (Mat_missing[i][j - 1] != -1)
				{
					P3[Mat_missing[i][j]][Mat_missing[i][j - 1]]++;
				}
				if (Mat_missing[i][j + 1] != -1)
				{
					P4[Mat_missing[i][j]][Mat_missing[i][j + 1]]++;
				}
			}
			if (Mat_missing[i][j] != -1 && j == 0 && i>0 && i<99)//边界
			{
				if (Mat_missing[i - 1][j] != -1)
				{
					P1[Mat_missing[i][j]][Mat_missing[i - 1][j]]++;
				}
				if (Mat_missing[i + 1][j] != -1)
				{
					P2[Mat_missing[i][j]][Mat_missing[i + 1][j]]++;
				}
				if (Mat_missing[i][j + 1] != -1)
				{
					P4[Mat_missing[i][j]][Mat_missing[i][j + 1]]++;
				}
			}
			if (Mat_missing[i][j] != -1 && j>0 && j<99 && i == 99)//边界
			{
				if (Mat_missing[i - 1][j] != -1)
				{
					P1[Mat_missing[i][j]][Mat_missing[i - 1][j]]++;
				}
				if (Mat_missing[i][j - 1] != -1)
				{
					P3[Mat_missing[i][j]][Mat_missing[i][j - 1]]++;
				}
				if (Mat_missing[i][j + 1] != -1)
				{
					P4[Mat_missing[i][j]][Mat_missing[i][j + 1]]++;
				}
			}
			if (Mat_missing[i][j] != -1 && i == 0 && j == 0)//角
			{
				if (Mat_missing[i + 1][j] != -1)
				{
					P2[Mat_missing[i][j]][Mat_missing[i + 1][j]]++;
				}
				if (Mat_missing[i][j + 1] != -1)
				{
					P4[Mat_missing[i][j]][Mat_missing[i][j + 1]]++;
				}
			}
			if (Mat_missing[i][j] != -1 && i == 0 && j == 99)//角
			{
				if (Mat_missing[i + 1][j] != -1)
				{
					P2[Mat_missing[i][j]][Mat_missing[i + 1][j]]++;
				}
				if (Mat_missing[i][j - 1] != -1)
				{
					P3[Mat_missing[i][j]][Mat_missing[i][j - 1]]++;
				}
			}
			if (Mat_missing[i][j] != -1 && i == 99 && j == 0)//角
			{
				if (Mat_missing[i - 1][j] != -1)
				{
					P1[Mat_missing[i][j]][Mat_missing[i - 1][j]]++;
				}
				if (Mat_missing[i][j + 1] != -1)
				{
					P4[Mat_missing[i][j]][Mat_missing[i][j + 1]]++;
				}
			}
			if (Mat_missing[i][j] != -1 && i == 99 && j == 99)//角
			{
				if (Mat_missing[i - 1][j] != -1)
				{
					P1[Mat_missing[i][j]][Mat_missing[i - 1][j]]++;
				}
				if (Mat_missing[i][j - 1] != -1)
				{
					P3[Mat_missing[i][j]][Mat_missing[i][j - 1]]++;
				}
			}
		}
	}
	for (int i = 0; i < 11; i++)//统计总数
	{
		for (int j = 0; j < 11; j++)
		{
			num1[i] += P1[i][j];
			num2[i] += P2[i][j];
			num3[i] += P3[i][j];
			num4[i] += P4[i][j];
		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)//概率表+1是为了防止0.
		{
			int m = 1;
			P11[i][j] = (float)(P1[i][j] + m)  / (num1[i]+11*m);
			P22[i][j] = (float)(P2[i][j] + m)/ (num2[i]+ 11 * m);
			P33[i][j] = (float)(P3[i][j] + m)  / (num3[i]+ 11 * m);
			P44[i][j] = (float)(P4[i][j] + m)/ (num4[i]+ 11 * m);
		}
	}	
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (Mat_missing[i][j] == -1)
			{
				float max1 = 0;
				int maxnum = 0;


				for (int m = 0; m < 11; m++)//迭代max后验概率
				{
					float max = 1;
					if (Mat_missing[i - 1][j] != -1 && i>0)
					{
						max = (max*p[m] * P11[m][Mat_missing[i - 1][j]] / p[Mat_missing[i - 1][j]]);
					}
					if (Mat_missing[i + 1][j] != -1 && i<99)
					{
						max = (max*p[m] * P22[m][Mat_missing[i + 1][j]] / p[Mat_missing[i + 1][j]]);
					}
					if (Mat_missing[i][j - 1] != -1 && j>0)
					{
						max = (10 * max*p[m] * P33[m][Mat_missing[i][j - 1]] / p[Mat_missing[i][j - 1]]);
					}
					if (Mat_missing[i][j + 1] != -1 && j<99)
					{
						max = (10 * max*p[m] * P44[m][Mat_missing[i][j + 1]] / p[Mat_missing[i][j + 1]]);
					}
					PL[m] = max;
					if (m == 0)
					{
						max1 = PL[0];
						num_acc = 1;
					}
					if (PL[m] > max1)
					{
						max1 = PL[m];
						maxnum = m;
					}
				}
				Mat_missing2[i][j] = maxnum;				
			}
		}
	}
	//======================
	// You can compare the result with groudtruth data
	// read the groudtruth data
	int Mat_gd[100][100];
	{
		ifstream infile("mat_groudtruth.txt");
		if (infile.is_open()) {
			string line;
			regex term(" ");
			int lineIdx = 0;
			while (!infile.eof()) {
				if (lineIdx >= 100) break;
				getline(infile, line);
				sregex_token_iterator it(line.begin(), line.end(), term, -1);
				sregex_token_iterator end;
				for (int i = 0; it != end; it++, i++) {
					string str = *it;
					Mat_gd[lineIdx][i] = atoi(str.c_str());
				}
				lineIdx++;
			}
			infile.close();
		}
	}	
	// fill the comparing code here
	//
	// Yangang Wang, 2019/11/22, @SEU
	//

	// (2) todo...
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (Mat_missing[i][j] == -1)
			{
				if (Mat_missing2[i][j] == Mat_gd[i][j])
				{
					num_acc++;
				}
			}
		}
	}
	float acc = (float)(num_acc * 100) / num_lost;
	cout << "正确率为：" << acc << "%" << endl;
	system("pause");

}