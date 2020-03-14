#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "process.h"
#include "math.h"
#include "Windows.h"
#include <string>
#define RADIAN(angle) ((angle)*PI / 180.0)//�Ƕȵ�����ת��
using namespace std;//̷��
#define PI 3.1415926535 //̷��
#define LEN 100
#define ChangeVale2 200
#define ChangeVale3 128
					//����ȫ�ֱ�������Ŷ���ͼ���λͼ���ݡ����ߡ���ɫ��ÿ������ռλ��(����) �˴�����ȫ�ֱ�����ҪΪ�˺����ͼ�����ݷ��ʼ�ͼ��洢��׼��
unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��
int bmpWidth;                  //ͼ��Ŀ�
int bmpHeight;                 //ͼ��ĸ�
RGBQUAD *pColorTable; //��ɫ��ָ��
int biBitCount;                  //ͼ������ 
using namespace cv;

/*˵��������һ��ͼ���ļ�������·������ͼ���λͼ���ݡ����ߡ���ɫ��ÿ����λ�������ݽ��ڴ�,�������Ӧ��ȫ�ֱ�����*/
bool readBmp(char *bmpName)//by  ����Ԫ �н����
{
	//�����ƶ���ʽ��ָ����ͼ���ļ�
	FILE *fp = fopen(bmpName, "rb");
	if (fp == 0) return 0;


	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);


	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;

	//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;

	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
	if (biBitCount == 8) {
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	//pXBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

	//�ر��ļ�
	fclose(fp);

	return 1;
}
/*����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ���*/
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable)
{
	//���λͼ����ָ��Ϊ0,��û�����ݴ���,��������
	if (!imgBuf)
		return 0;

	//��ɫ���С,���ֽ�Ϊ��λ,�Ҷ�ͼ����ɫ��Ϊ1024�ֽ�,��ɫͼ����ɫ���СΪ0
	int colorTablesize = 0;
	if (biBitCount == 8)
		colorTablesize = 1024;

	//���洢ͼ������ÿ���ֽ���Ϊ4�ı���
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

	//�Զ�����д�ķ�ʽ���ļ�
	FILE *fp = fopen(bmpName, "wb");
	if (fp == 0) return 0;

	//����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp����

							 //bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	//bfOffBits��ͼ���ļ�ǰ������������ռ�֮��
	fileHead.bfOffBits = 54 + colorTablesize;

	//д�ļ�ͷ���ļ�
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	//����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
	BITMAPINFOHEADER head;
	head.biBitCount = biBitCount;
	head.biClrImportant = 0;
	head.biClrUsed = 0;
	head.biCompression = 0;
	head.biHeight = height;
	head.biPlanes = 1;
	head.biSize = 40;
	head.biSizeImage = lineByte*height;
	head.biWidth = width;
	head.biXPelsPerMeter = 0;
	head.biYPelsPerMeter = 0;
	//дλͼ��Ϣͷ���ڴ�
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//����Ҷ�ͼ��,����ɫ��,д���ļ� 
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);

	//дλͼ���ݽ��ļ�
	fwrite(imgBuf, height*lineByte, 1, fp);

	//�ر��ļ�
	fclose(fp);

	return 1;
}
int menu()/*�Զ��庯��ʵ�ֲ˵�����*/
{
	printf("\n");
	printf("\t*************************************************\n");
	printf("\t* ����ͼ�����ߡ�Spark Photo��               *\n");
	printf("\t* By Spark 4С��                                *\n");
	printf("\t*************************************************\n");
	printf("\t 1. �Ҷȴ���                                                        \n");
	printf("\t 2. ���ȵ���                                                        \n");
	printf("\t 3. �Աȶȵ���                                                     \n");
	printf("\t 4. ͼ��ü�                                                        \n");
	printf("\t 5. ���ɷ��                                                        \n");
	printf("\t 6. ͼ��ɫ                                                        \n");
	printf("\t 7. ͼ����ת                                                        \n");
	printf("\t 8. ������                                                        \n");
	printf("\t 9. �˳�                                                               \n");
	printf("\t Please Choose (1-9):");
	return 1;
}
//���ȵ���  by����Ԫ
void Lightness()
{
	char readPath[LEN];
	char writePath[LEN];
	printf("�����������ͼ��BMP��ʽ���ļ���ַ:\n");
	scanf("%s", readPath);/*��ȡĿ���ļ�·��*/
	printf("�����봦���ͼ���ļ���ַ:\n");
	scanf("%s", writePath);/*��ȡĿ���ļ�·��*/
	float lightness;
	printf("����������Ҫ������(-100~100 ����) ��\n");
	scanf("%f", &lightness);
	float x = lightness / 100.0;

	readBmp(readPath);
	// ����һ��ͼƬ��ԭ����    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// ����һ����Ϊ "ԭ��"����    
	namedWindow("ԭ��");
	// �ڴ�������ʾԭ��    
	imshow("ԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//ѭ������,ͼ������꣬ѭ������������ÿ���ص���������
	int i, j;
	for (i = 0; i < bmpHeight; i++) {
		for (j = 0; j < 3 * bmpWidth; j = j + 3) {
			int b = *(pBmpBuf + i*lineByte + j) + ChangeVale2*x ;
			int g = *(pBmpBuf + i*lineByte + j + 1) + ChangeVale2*x ;
			int r = *(pBmpBuf + i*lineByte + j + 2) + ChangeVale2*x ;
			if (b >= 255)
				*(pBmpBuf + i*lineByte + j) = 255;
			else
				if (b <= 0)
					*(pBmpBuf + i*lineByte + j) = 0;
				else
					*(pBmpBuf + i*lineByte + j) = b;
			if (g >= 255)
				*(pBmpBuf + i*lineByte + j + 1) = 255;
			else
				if (g <= 0)
					*(pBmpBuf + i*lineByte + j + 1) = 0;
				else
					*(pBmpBuf + i*lineByte + j + 1) = g;
			if (r >= 255)
				*(pBmpBuf + i*lineByte + j + 2) = 255;
			else
				if (r <= 0)
					*(pBmpBuf + i*lineByte + j + 2) = 0;

				else
					*(pBmpBuf + i*lineByte + j + 2) = r;
		}
	}
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// ����һ��ͼƬ����Ϸԭ����
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1,1);
	// ����һ����Ϊ "��Ϸԭ��"����    
	namedWindow("����");
	// �ڴ�������ʾ��Ϸԭ��    
	imshow("����", img1);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	return;
}
//�Աȶ�  by������
void Contrast()
{
	char readPath[LEN];
	char writePath[LEN];
	printf("�����������ͼ��BMP��ʽ���ļ���ַ:\n");
	scanf("%s", readPath);/*��ȡĿ���ļ�·��*/
	printf("�����봦���ͼ���ļ���ַ:\n");
	scanf("%s", writePath);/*��ȡĿ���ļ�·��*/
	readBmp(readPath);
	
	// ����һ��ͼƬ��ԭ����    
	string imgpath = readPath;
	Mat img = imread(imgpath,1);
	// ����һ����Ϊ "ԭ��"����    
	namedWindow("ԭ��");
	// �ڴ�������ʾԭ��    
	imshow("ԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//����Ļ�������Աȶ�														
	int dbd;
	printf("����������Ҫ�ĶԱȶ�(0-100����) ��\n");
	scanf("%f", &dbd);

	float a;
	a = dbd / 100;
	//ѭ������,ͼ�������
	int i, j;
	//ѭ����������Բ�ɫͼ�񣬱���ÿ���ص���������
	for (i = 0; i < bmpHeight; i++) {
		for (j = 0; j < 3 * bmpWidth; j = j + 3) {
			int b = *(pBmpBuf + i*lineByte + j);
			int g = *(pBmpBuf + i*lineByte + j + 1);
			int r = *(pBmpBuf + i*lineByte + j + 2);

			if (b >= 128)
				b += (a*ChangeVale3);
			else
				b -= (a*ChangeVale3);

			if (g >= 128)
				g += (a*ChangeVale3);
			else
				g -= (a*ChangeVale3);

			if (r >= 128)
				r += (a*ChangeVale3);
			else
				r -= (a*ChangeVale3);

			if (b >= 255)
				*(pBmpBuf + i*lineByte + j) = 255;
			else
				if (b <= 0)
					*(pBmpBuf + i*lineByte + j) = 0;
				else
					*(pBmpBuf + i*lineByte + j) = b;

			if (g >= 255)
				*(pBmpBuf + i*lineByte + j + 1) = 255;
			else
				if (g <= 0)
					*(pBmpBuf + i*lineByte + j + 1) = 0;
				else
					*(pBmpBuf + i*lineByte + j + 1) = g;

			if (r >= 255)
				*(pBmpBuf + i*lineByte + j + 2) = 255;
			else
				if (r <= 0)
					*(pBmpBuf + i*lineByte + j + 2) = 0;
				else
					*(pBmpBuf + i*lineByte + j + 2) = r;
		}
	}
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// ����һ��ͼƬ��������
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// ����һ����Ϊ "����"����    
	namedWindow("����");
	// �ڴ�������ʾ����    
	imshow("����", img1);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	return;
}

/*���ܣ����ɫת����256ɫ�Ҷ�ͼ��  */
void MakegGray()    //�Ҷȱ仯  by̷��
{
	char readPath[LEN];
	char writePath[LEN];
	printf("�����������ͼ��BMP��ʽ���ļ���ַ:\n");
	scanf("%s", readPath);/*��ȡĿ���ļ�·��*/
	printf("�����봦���ͼ���ļ���ַ:\n");
	scanf("%s", writePath);/*��ȡĿ���ļ�·��*/
						  
	FILE *fp = fopen(readPath, "rb");

	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;

	//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;

	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
	if (biBitCount == 8) {
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	BYTE* pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

	int lineSize = biBitCount * bmpWidth / 8;
	int alignBytes = ((bmpWidth * biBitCount + 31) & ~31) / 8L - bmpWidth * biBitCount / 8L;
	// ����һ��ͼƬ��ԭ����    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// ����һ����Ϊ "ԭ��"����    
	namedWindow("ԭ��");
	// �ڴ�������ʾԭ��    
	imshow("ԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);

	BYTE* p_data;
	p_data = pBmpBuf;//ȡ��ԭͼ��������ָ��

	for (int i = 0; i < bmpHeight; i++) // ÿ��
	{
		for (int j = 0; j < 3 * bmpWidth; j = j + 3)// ÿ��
		{
			/*BYTE* pbyBlue = p_data++;   //�õ���ɫֵ
			BYTE* pbyGreen = p_data++;  //�õ���ɫֵ
			BYTE* pbyRed = p_data++;    //�õ���ɫֵ
			BYTE r = *pbyRed;
			BYTE g = *pbyGreen;
			BYTE b = *pbyBlue;*/
			//ȡ��ԭr,g,b�е����ֵ��Ϊ����������ֵ����ֵ
			int b = *(pBmpBuf + i*lineByte + j);
			int g = *(pBmpBuf + i*lineByte + j + 1);
			int r = *(pBmpBuf + i*lineByte + j + 2);

			int gray = 0.299 * r + 0.587 * g + 0.114 * b;
			*(pBmpBuf + i*lineByte + j) = gray;     //��ȡ�������ֵ�������ص�������
			*(pBmpBuf + i*lineByte + j + 1) = gray;    //��ȡ�������ֵ�������ص��̷���
			*(pBmpBuf + i*lineByte + j + 2) = gray;      //��ȡ�������ֵ�������صĺ����
		}
	}
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// ����һ��ͼƬ��������
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// ����һ����Ϊ "����"����    
	namedWindow("����");
	// �ڴ�������ʾ����    
	imshow("����", img1);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	return;
}
/*ͼ�����ת������һ����ת�Ƕ�    by̷�����ο�������Դ��*/

void Rotation(const string& srcFile, const string& desFile)
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;

	FILE *pFile;
	if ((pFile = fopen(srcFile.c_str(), "rb")) == NULL)
	{
		printf("open bmp file error.");
		exit(-1);
	}
	//��ȡ�ļ���Bitmapͷ��Ϣ
	fseek(pFile, 0, SEEK_SET);
	fread(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
	fread(&bmiHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
	//�Ȳ�֧��С��16λ��λͼ
	int bitCount = bmiHeader.biBitCount;
	if (bitCount < 16)
	{
		exit(-1);
	}
	int srcW = bmiHeader.biWidth;
	int srcH = bmiHeader.biHeight;
	//ԭͼ��ÿһ��ȥ��ƫ�������ֽ���
	int lineSize = bitCount * srcW / 8;
	//ƫ������windowsϵͳҪ��ÿ��ɨ���а����ֽڶ���
	int alignBytes = ((bmiHeader.biWidth * bitCount + 31) & ~31) / 8L - bmiHeader.biWidth * bitCount / 8L;
	//ԭͼ�񻺴�
	int srcBufSize = lineSize * srcH;
	BYTE* srcBuf = new BYTE[srcBufSize];

	int i, j;
	//��ȡ�ļ�������
	for (i = 0; i < srcH; i++)
	{
		fread(&srcBuf[lineSize * i], lineSize, 1, pFile);
		fseek(pFile, alignBytes, SEEK_CUR);
	}
	// ����һ��ͼƬ��ԭ����    
	string imgpath = srcFile.c_str();
	Mat img = imread(imgpath, 1);
	// ����һ����Ϊ "ԭ��"����    
	namedWindow("ԭ��");
	// �ڴ�������ʾԭ��    
	imshow("ԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);

	int angle;
	printf("����������Ҫ��ʱ����ת�ĽǶ�(0-360����) ��\n");
	scanf("%d", &angle);

	//��ͼ������Ϊԭ�����Ͻǣ����Ͻǣ����½Ǻ����½ǵ�����,���ڼ�����ת���ͼ��Ŀ�͸�
	POINT pLT, pRT, pLB, pRB;
	pLT.x = -srcW / 2; pLT.y = srcH / 2;
	pRT.x = srcW / 2; pRT.y = srcH / 2;
	pLB.x = -srcW / 2; pLB.y = -srcH / 2;
	pRB.x = srcW / 2; pRB.y = -srcH / 2;
	//��ת֮�������
	POINT pLTN, pRTN, pLBN, pRBN;
	double sina = sin(RADIAN(angle));
	double cosa = cos(RADIAN(angle));
	pLTN.x = pLT.x*cosa + pLT.y*sina;
	pLTN.y = -pLT.x*sina + pLT.y*cosa;
	pRTN.x = pRT.x*cosa + pRT.y*sina;
	pRTN.y = -pRT.x*sina + pRT.y*cosa;
	pLBN.x = pLB.x*cosa + pLB.y*sina;
	pLBN.y = -pLB.x*sina + pLB.y*cosa;
	pRBN.x = pRB.x*cosa + pRB.y*sina;
	pRBN.y = -pRB.x*sina + pRB.y*cosa;
	//��ת��ͼ���͸�
	int desWidth = max(abs(pRBN.x - pLTN.x), abs(pRTN.x - pLBN.x));
	int desHeight = max(abs(pRBN.y - pLTN.y), abs(pRTN.y - pLBN.y));
	//������ת��ͼ��Ļ���
	int desBufSize = ((desWidth * bitCount + 31) / 32) * 4 * desHeight;
	BYTE *desBuf = new BYTE[desBufSize];
	//���������ض�Ԥ��Ϊ��ɫ
	memset(desBuf, 0, desBufSize);
	//��ͼ��ÿһ���ֽ���������ƫ����
	int desLineSize = ((desWidth * bitCount + 31) / 32) * 4;
	//ͨ����ͼ������꣬�����Ӧ��ԭͼ�������
	for (i = 0; i < desHeight; i++)
	{
		for (j = 0; j < desWidth; j++)
		{
			//ת������ͼ��Ϊ���ĵ�����ϵ������������ת
			int tX = (j - desWidth / 2)*cos(RADIAN(360 - angle)) + (-i + desHeight / 2)*sin(RADIAN(360 - angle));
			int tY = -(j - desWidth / 2)*sin(RADIAN(360 - angle)) + (-i + desHeight / 2)*cos(RADIAN(360 - angle));
			//���������겻��ԭͼ���ڣ��򲻸�ֵ
			if (tX > srcW / 2 || tX < -srcW / 2 || tY > srcH / 2 || tY < -srcH / 2)
			{
				continue;
			}
			//��ת����ԭ����ϵ��
			int tXN = tX + srcW / 2; int tYN = abs(tY - srcH / 2);
			//ֵ����
			memcpy(&desBuf[i * desLineSize + j * bitCount / 8], &srcBuf[tYN * lineSize + tXN * bitCount / 8], 3);
		}
	}

	//����Ŀ���ļ�
	HFILE hfile = _lcreat(desFile.c_str(), 0);
	//�ļ�ͷ��Ϣ
	BITMAPFILEHEADER nbmfHeader;
	nbmfHeader.bfType = 0x4D42;
	nbmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + desWidth * desHeight * bitCount / 8;
	nbmfHeader.bfReserved1 = 0;
	nbmfHeader.bfReserved2 = 0;
	nbmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//Bitmapͷ��Ϣ
	BITMAPINFOHEADER   bmi;
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biWidth = desWidth;
	bmi.biHeight = desHeight;
	bmi.biPlanes = 1;
	bmi.biBitCount = bitCount;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;
	bmi.biXPelsPerMeter = 0;
	bmi.biYPelsPerMeter = 0;
	bmi.biClrUsed = 0;
	bmi.biClrImportant = 0;

	//д���ļ�ͷ��Ϣ
	_lwrite(hfile, (LPCSTR)&nbmfHeader, sizeof(BITMAPFILEHEADER));
	//д��Bitmapͷ��Ϣ
	_lwrite(hfile, (LPCSTR)&bmi, sizeof(BITMAPINFOHEADER));
	//д��ͼ������
	_lwrite(hfile, (LPCSTR)desBuf, desBufSize);
	_lclose(hfile);
	// ����һ��ͼƬ��������
	string imgpath1 = desFile.c_str();
	Mat img1 = imread(imgpath1, 1);
	// ����һ����Ϊ "����"����    
	namedWindow("����");
	// �ڴ�������ʾ����    
	imshow("����", img1);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
}
/*ͼ��ɫ*/
void Inverse()//by  ���ŵ�
{
	char readPath[LEN];
	char writePath[LEN];
	printf("�����������ͼ��BMP��ʽ���ļ���ַ:\n");
	scanf("%s", readPath);/*��ȡĿ���ļ�·��*/
	printf("�����봦���ͼ���ļ���ַ:\n");
	scanf("%s", writePath);/*��ȡĿ���ļ�·��*/
	readBmp(readPath);
	// ����һ��ͼƬ��ԭ����    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// ����һ����Ϊ "ԭ��"����    
	namedWindow("ԭ��");
	// �ڴ�������ʾԭ��    
	imshow("ԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);

	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//ѭ������,ͼ������꣬ѭ������������ÿ���ص���������
	int i, j;
	for (i = 0; i < bmpHeight; i++)
	{
		for (j = 0; j < 3 * bmpWidth; j = j + 3)
		{
			int b = *(pBmpBuf + i*lineByte + j);
			int g = *(pBmpBuf + i*lineByte + j + 1);
			int r = *(pBmpBuf + i*lineByte + j + 2);
			int b0 = abs(255 - b);
			int g0 = abs(255 - g);
			int r0 = abs(255 - r);
			*(pBmpBuf + i*lineByte + j) = b0;
			*(pBmpBuf + i*lineByte + j + 1) = g0;
			*(pBmpBuf + i*lineByte + j + 2) = r0;
		}
	}
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// ����һ��ͼƬ��������
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// ����һ����Ϊ "����"����    
	namedWindow("����");
	// �ڴ�������ʾ����    
	imshow("����", img1);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	return;
}
/*ͼ����ϻ������ɷ��*/
void Older()//by ���ŵ�
{
	char readPath[LEN];
	char writePath[LEN];
	printf("�����������ͼ��BMP��ʽ���ļ���ַ:\n");
	scanf("%s", readPath);/*��ȡĿ���ļ�·��*/
	printf("�����봦���ͼ���ļ���ַ:\n");
	scanf("%s", writePath);/*��ȡĿ���ļ�·��*/
	readBmp(readPath);
	// ����һ��ͼƬ��ԭ����    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// ����һ����Ϊ "ԭ��"����    
	namedWindow("ԭ��");
	// �ڴ�������ʾԭ��    
	imshow("ԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);

	int x;
	printf("�������ϻ�ֵ:\n");
	scanf("%d", &x);
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//ѭ������,ͼ������꣬ѭ������������ÿ���ص���������
	int i, j;
	for (i = 0; i < bmpHeight; i++)
	{
		for (j = 0; j < 3 * bmpWidth; j = j + 3)
		{
			int b = *(pBmpBuf + i*lineByte + j);
			int g = *(pBmpBuf + i*lineByte + j + 1);
			int r = *(pBmpBuf + i*lineByte + j + 2);
			int b0 = (b - x - 100);
			int g0 = (g - x - 70);
			int r0 = (r - x - 70);
			*(pBmpBuf + i*lineByte + j) = b0;
			*(pBmpBuf + i*lineByte + j + 1) = g0;
			*(pBmpBuf + i*lineByte + j + 2) = r0;
			if (b0 <= 0)
				*(pBmpBuf + i*lineByte + j) = 0;
			if (g0 <= 0)
				*(pBmpBuf + i*lineByte + j + 1) = 0;
			if (r0 <= 0)
				*(pBmpBuf + i*lineByte + j + 2) = 0;
		}
	}
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// ����һ��ͼƬ��������
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// ����һ����Ϊ "����"����    
	namedWindow("����");
	// �ڴ�������ʾ����    
	imshow("����", img1);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	return;
}
/*ͼ��ü�*/
void cut()//by���ŵ�
{
	char readPath[LEN];
	char writePath[LEN];
	printf("�����������ͼ��BMP��ʽ���ļ���ַ:\n");
	scanf("%s", readPath);/*��ȡĿ���ļ�·��*/
	printf("�����봦���ͼ���ļ���ַ:\n");
	scanf("%s", writePath);/*��ȡĿ���ļ�·��*/
	readBmp(readPath);
	// ����һ��ͼƬ��ԭ����    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// ����һ����Ϊ "ԭ��"����    
	namedWindow("ԭ��");
	// �ڴ�������ʾԭ��    
	imshow("ԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);

	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//��ȡ��Ҫ�ü�������ֵ
	float x1, x2, y1, y2;
	int ka, kb, kc, kd;
	printf("����������Ҫ��x1(0-100����) ��\n");
	scanf("%f", &x1);
	printf("����������Ҫ��x2(0-100����) ��\n");
	scanf("%f", &x2);
	printf("����������Ҫ��y1(0-100����) ��\n");
	scanf("%f", &y1);
	printf("����������Ҫ��y2(0-100����) ��\n");
	scanf("%f", &y2);
	//ѭ������,ͼ������꣬ѭ������������ÿ���ص���������
	int i, j;
	for (i = 0; i < bmpHeight*(y1 / 100); i++)
	{
		for (j = 0; j < 3 * bmpWidth; j = j + 3)
		{
			for (ka = 0; ka < 3; ka++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
			{
				*(pBmpBuf + i*lineByte + j + ka) = 0;
			}
		}
	}
	for (i = bmpHeight - 1; i >bmpHeight*(y2 / 100); i--)
	{
		for (j = 0; j < 3 * bmpWidth; j = j + 3)
		{
			for (kb = 0; kb < 3; kb++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
			{
				*(pBmpBuf + i*lineByte + j + kb) = 0;
			}
		}
	}
	for (i = 0; i < bmpHeight; i++)
	{
		for (j = 0; j < 3 * bmpWidth*(x1 / 100); j = j + 3)
		{
			for (kc = 0; kc < 3; kc++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
			{
				*(pBmpBuf + i*lineByte + j + kc) = 0;
			}
		}
	}
	for (i = 0; i < bmpHeight; i++)
	{
		for (j = 3 * bmpWidth*(x2 / 100); j <3 * bmpWidth; j = j + 3)
		{
			for (kd = 0; kd < 3; kd++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
			{
				*(pBmpBuf + i*lineByte + j + kd) = 0;
			}
		}
	}

	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// ����һ��ͼƬ��������
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// ����һ����Ϊ "����"����    
	namedWindow("����");
	// �ڴ�������ʾ����    
	imshow("����", img1);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);
	return;
}
void mirror()// by ������
{

	char readPath[LEN];
	char writePath[LEN];
	printf("�����������ͼ��BMP��ʽ���ļ���ַ:\n");
	scanf("%s", readPath);/*��ȡĿ���ļ�·��*/
	printf("�����봦���ͼ���ļ���ַ:\n");
	scanf("%s", writePath);/*��ȡĿ���ļ�·��*/

	readBmp(readPath);
	// ����һ��ͼƬ��ԭ����    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// ����һ����Ϊ "ԭ��"����    
	namedWindow("ԭ��");
	// �ڴ�������ʾԭ��    
	imshow("ԭ��", img);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);

	int height = bmpHeight;
	int width = bmpWidth;
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	int imgSize = lineByte * bmpHeight;

	int i, j, t1, t2, t3;//����ѭ��������������ʱ����
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < (3 * width) / 2; j = j + 3)
		{
			int b = *(pBmpBuf + i*lineByte + j);
			int g = *(pBmpBuf + i*lineByte + j + 1);
			int r = *(pBmpBuf + i*lineByte + j + 2);

			b = t1 = *(pBmpBuf + i*lineByte + (width - 1) * 3 - j); //ˮƽ����  
			g = t2 = *(pBmpBuf + i*lineByte + (width - 1) * 3 - (j + 1));
			r = t3 = *(pBmpBuf + i*lineByte + (width - 1) * 3 - (j + 2));
			b = *(pBmpBuf + i*lineByte + (width - 1) * 3 - j) = *(pBmpBuf + (i*lineByte) + j); //ˮƽ����  
			g = *(pBmpBuf + i*lineByte + (width - 1) * 3 - (j + 1)) = *(pBmpBuf + (i*lineByte) + j + 2);
			r = *(pBmpBuf + i*lineByte + (width - 1) * 3 - (j + 2)) = *(pBmpBuf + (i*lineByte) + j + 1);
			b = *(pBmpBuf + (i*lineByte) + j) = t1;
			g = *(pBmpBuf + (i*lineByte) + j + 2) = t2;
			r = *(pBmpBuf + (i*lineByte) + j + 1) = t3;
		}

	}
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

	//�ͷ�
	delete[]pColorTable;
	delete[]pBmpBuf;
	
	// ����һ��ͼƬ��������
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// ����һ����Ϊ "����"����    
	namedWindow("����");
	// �ڴ�������ʾ����    
	imshow("����", img1);
	// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(6000);


	system("pause");
	return;
}





//ѭ����������Բ�ɫͼ�񣬱���ÿ���ص���������

//��ͼ�����ݴ���

void main()//������
{


	while (1)
	{

		int order;
		menu();
		scanf("%d", &order);
		if (order == 7)
		{
			char readPath[LEN];
			char writePath[LEN];
			printf("�����������ͼ��BMP��ʽ���ļ���ַ:\n");
			scanf("%s", readPath);/*��ȡĿ���ļ�·��*/
			printf("�����봦���ͼ���ļ���ַ:\n");
			scanf("%s", writePath);/*��ȡĿ���ļ�·��*/
			string srcFile(readPath);
			string desFile(writePath);
			Rotation(srcFile, desFile);
		}

		switch (order)
		{
		case 1:
			MakegGray();
			break;
		case 2:
			Lightness();
			break;
		case 3:
			Contrast();
			break;
		case 4:
			cut();
			break;
		case 5:
			Older();
			break;
		case 6:
			Inverse();
			break;
		case 7:
			
			break;
		case 8:
			mirror();
			break;
		default: exit(0);//break
		}
		printf("\t Finshed!\n ");
		printf("\t Please press any key to return ");
		getchar();
	}
	system("pause");
	return;
}


