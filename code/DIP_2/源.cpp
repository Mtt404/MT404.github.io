#include <iostream>
#include<opencv.hpp>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>
using namespace Eigen;   
using namespace std;
using namespace cv;
int main()

{
	MatrixXf AA=AA.Zero(48, 9);//AX=b中的A矩阵
	MatrixXf K(3, 3),S1(3,3),S2(3,3),R(3,3),M_(3,3);//K矩阵、S1矩阵、S2矩阵、R矩阵、补充的M矩阵
	K << 746.07, 0, 493.94, 0, 743.92, 488.76, 0, 0, 1;//初始化
	M_ << 0.867084, 0.0620832, -10.0761, -0.32521, 1.03748, 147.562, 0, 0, 1;
	VectorXf bb = bb.Zero(48);//AX=b中的b向量
	MatrixXf colPivHouseholderQr1, colPivHouseholderQr2;//解向量
	MatrixXf A(2,16),B(2,16),A3d(3,16),B3d(3,16),K_(3,16),B3D(3,16);//点列
	ifstream infile;
	infile.open("points2d_A.txt");
	double data[3][16] = {0};
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			infile >> data[j][i];
			 A(j, i)= data[j][i];
		}
	}
	infile.close();
	infile.open("points2d_B.txt");
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			infile >> data[j][i];
			B(j, i) = data[j][i];
			bb(i *2 + j) = data[j][i];
		}
	}
	infile.close();
	infile.open("points3d_A.txt");
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			infile >> data[j][i];
			A3d(j, i) = data[j][i];
		}
	}
	infile.close();
	infile.open("points3d_B.txt");
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			infile >> data[j][i];
			B3d(j, i) = data[j][i];
		}
	}
	infile.close();
	for (int i = 0; i < 16; i++)
	{
		AA(i*3, 0) = A(0, i);
		AA(i*3, 1) = A(1, i);
		AA(i * 3, 2) = 1;
		AA(i * 3 + 1, 3) = A(0, i);
		AA(i * 3 + 1, 4) = A(1, i);
		AA(i * 3 + 1, 5) = 1;
		AA(i*3+2,6)= A(0, i);
		AA(i * 3 + 2, 7) = A(1, i);
		AA(i * 3 + 2, 8) = 1;
	}
	K_ = K*A3d;
	for (int i = 0; i < 16; i++)
	{
		bb(i * 3) = K_(0, i);
		bb(i * 3 + 1) = K_(1, i);
		bb(i * 3 + 2) = K_(2, i);
	}
	colPivHouseholderQr1 = AA.colPivHouseholderQr().solve(bb);//解方程
	cout << "The least-squares solution of S1 is:\n"
		<< colPivHouseholderQr1 << endl;
	for (int i = 0; i < 3; i++)//赋值，解向量到矩阵
	{
		S1(i, 0) = colPivHouseholderQr1(i * 3);
		S1(i, 1) = colPivHouseholderQr1(i * 3 + 1);
		S1(i, 2) = colPivHouseholderQr1(i * 3 + 2);
	}
	//cout << A3d << endl << B3d<<endl<<K_;
	for (int i = 0; i < 16; i++)
	{
		AA(i * 3, 0) = B(0, i);
		AA(i * 3, 1) = B(1, i);
		AA(i * 3, 2) = 1;
		AA(i * 3 + 1, 3) = B(0, i);
		AA(i * 3 + 1, 4) = A(1, i);
		AA(i * 3 + 1, 5) = 1;
		AA(i * 3 + 2, 6) = A(0, i);
		AA(i * 3 + 2, 7) = A(1, i);
		AA(i * 3 + 2, 8) = 1;
	}
	K_ = K*B3d;

	for (int i = 0; i < 16; i++)
	{
		bb(i * 3) = K_(0, i);
		bb(i * 3 + 1) = K_(1, i);
		bb(i * 3 + 2) = K_(2, i);
	}
	colPivHouseholderQr2 = AA.colPivHouseholderQr().solve(bb);
	cout << "The least-squares solution of S2 is:\n"
		<< colPivHouseholderQr2 << endl;
	for (int i = 0; i < 3; i++)//赋值，解向量到矩阵
	{
		S2(i, 0) = colPivHouseholderQr2(i * 3);
		S2(i, 1) = colPivHouseholderQr2(i * 3 + 1);
		S2(i, 2) = colPivHouseholderQr2(i * 3 + 2);
	}
	R = K.inverse()*S2*M_*S1.inverse()*K;
	cout <<"R矩阵如下："<<endl<< R<<endl;
	B3D = R*A3d;
	cout << "B3d点列和通过R矩阵变换的B3D点列的对比：" << endl << "B3d:" << endl<<B3d<<endl << "B3D:" << endl << B3D;
	system("pause");
	return 0;
}