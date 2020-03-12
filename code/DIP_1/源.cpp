#include <iostream>
#include<opencv.hpp>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>
using namespace Eigen;   
using namespace std;
using namespace cv;
int main()
{
	MatrixXf AA=AA.Zero(32, 6);//AX=b�е�A����,����Ϊ�˷��㣬ֱ��������6�����������
	Mat M;                     //����warpAffine�Ĳ���
	VectorXf bb = bb.Zero(32);//AX=b�е�b����
	MatrixXf x;              //������
	MatrixXf A(2,16),B(2,16);//�洢����
	ifstream infile;         //��ȡ����
	infile.open("points2d_A.txt");
	double data[2][16] = {0};
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
			bb(i * 2 + j) = data[j][i];
		}
	}
	infile.close();
	for (int i = 0; i < 16; i++)        //���ݵ������A����
	{
		AA(i*2, 0) = A(0, i);
		AA(i*2, 1) = A(1, i);
		AA(i * 2, 2) = 1;
		AA(i * 2 + 1, 3) = A(0, i);
		AA(i * 2 + 1, 4) = A(1, i);
		AA(i * 2 + 1, 5) = 1;
	}
	x = AA.jacobiSvd(ComputeThinU | ComputeThinV).solve(bb);//���
	cout << "The least-squares solution is:\n"              //���
		<< x<< endl;
	M = (Mat_<float>(2, 3) << 0.867084, 0.0620832,-10.0761, -0.32521,1.03748, 147.562);//�����ҳ���ֱ����������ֵ���Ǻ��񲻼��ݣ�����˵��û�ҵ�����
	//M = { 0.843308,0.0565015; 0.0229928,1.11922 };
	Mat a= imread("A.png");
	Mat b= imread("A.png");
	warpAffine(a,b, M, b.size(),1);
	for (int i = 0; i < 16; i++)//���
	{
		Point pointInterest1, pointInterest2;//�����㣬���Ի���ͼ����
		pointInterest1.x = A(0, i);//��������ͼ���к�����
		pointInterest1.y = A(1, i);//��������ͼ����������
		pointInterest2.x = B(0, i);//��������ͼ���к�����
		pointInterest2.y = B(1, i);//��������ͼ����������
		circle(b, pointInterest2, 2, Scalar(0, 0, 255));
	}
	imwrite("1.png", b);
	for (int i = 0; i < 16; i++)
	{
		Point pointInterest1, pointInterest2;//�����㣬���Ի���ͼ����
		pointInterest1.x = A(0, i);//��������ͼ���к�����
		pointInterest1.y = A(1, i);//��������ͼ����������
		pointInterest2.x = B(0, i);//��������ͼ���к�����
		pointInterest2.y = B(1, i);//��������ͼ����������
		circle(a, pointInterest1, 2, Scalar(0, 0, 255));
	}
	imwrite("A1.png", a);
	Mat b2= imread("B.png");
	for (int i = 0; i < 16; i++)
	{
		Point pointInterest1, pointInterest2;//�����㣬���Ի���ͼ����
		pointInterest1.x = A(0, i);//��������ͼ���к�����
		pointInterest1.y = A(1, i);//��������ͼ����������
		pointInterest2.x = B(0, i);//��������ͼ���к�����
		pointInterest2.y = B(1, i);//��������ͼ����������
		circle(b2, pointInterest2, 2, Scalar(0, 0, 255));
	}
	imwrite("B1.png", b2);
	imshow("1", a);
	imshow("2",b);
	imshow("3",b2);
	waitKey(0);
	system("pause");
	return 0;
}