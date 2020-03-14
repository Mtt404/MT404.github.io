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
#define RADIAN(angle) ((angle)*PI / 180.0)//角度到弧度转化
using namespace std;//谭超
#define PI 3.1415926535 //谭超
#define LEN 100
#define ChangeVale2 200
#define ChangeVale3 128
					//几个全局变量，存放读入图像的位图数据、宽、高、颜色表及每像素所占位数(比特) 此处定义全局变量主要为了后面的图像数据访问及图像存储作准备
unsigned char *pBmpBuf;//读入图像数据的指针
int bmpWidth;                  //图像的宽
int bmpHeight;                 //图像的高
RGBQUAD *pColorTable; //颜色表指针
int biBitCount;                  //图像类型 
using namespace cv;

/*说明：给定一个图像文件名及其路径，读图像的位图数据、宽、高、颜色表及每像素位数等数据进内存,存放在相应的全局变量中*/
bool readBmp(char *bmpName)//by  范瑞元 有借鉴书
{
	//二进制读方式打开指定的图像文件
	FILE *fp = fopen(bmpName, "rb");
	if (fp == 0) return 0;


	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);


	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//获取图像宽、高、每像素所占位数等信息
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;

	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;

	//灰度图像有颜色表，且颜色表表项为256
	if (biBitCount == 8) {
		//申请颜色表所需要的空间，读颜色表进内存
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	//pXBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

	//关闭文件
	fclose(fp);

	return 1;
}
/*给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中*/
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable)
{
	//如果位图数据指针为0,则没有数据传入,函数返回
	if (!imgBuf)
		return 0;

	//颜色表大小,以字节为单位,灰度图像颜色表为1024字节,彩色图像颜色表大小为0
	int colorTablesize = 0;
	if (biBitCount == 8)
		colorTablesize = 1024;

	//待存储图像数据每行字节数为4的倍数
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

	//以二进制写的方式打开文件
	FILE *fp = fopen(bmpName, "wb");
	if (fp == 0) return 0;

	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型

							 //bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	//bfOffBits是图像文件前三个部分所需空间之和
	fileHead.bfOffBits = 54 + colorTablesize;

	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	//申请位图信息头结构变量，填写信息头信息
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
	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//如果灰度图像,有颜色表,写入文件 
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);

	//写位图数据进文件
	fwrite(imgBuf, height*lineByte, 1, fp);

	//关闭文件
	fclose(fp);

	return 1;
}
int menu()/*自定义函数实现菜单功能*/
{
	printf("\n");
	printf("\t*************************************************\n");
	printf("\t* 简易图像处理工具☆Spark Photo☆               *\n");
	printf("\t* By Spark 4小组                                *\n");
	printf("\t*************************************************\n");
	printf("\t 1. 灰度处理                                                        \n");
	printf("\t 2. 亮度调整                                                        \n");
	printf("\t 3. 对比度调整                                                     \n");
	printf("\t 4. 图像裁剪                                                        \n");
	printf("\t 5. 怀旧风格                                                        \n");
	printf("\t 6. 图像反色                                                        \n");
	printf("\t 7. 图像旋转                                                        \n");
	printf("\t 8. 镜像处理                                                        \n");
	printf("\t 9. 退出                                                               \n");
	printf("\t Please Choose (1-9):");
	return 1;
}
//亮度调节  by范瑞元
void Lightness()
{
	char readPath[LEN];
	char writePath[LEN];
	printf("请输入待处理图像（BMP格式）文件地址:\n");
	scanf("%s", readPath);/*获取目标文件路径*/
	printf("请输入处理后图像文件地址:\n");
	scanf("%s", writePath);/*获取目标文件路径*/
	float lightness;
	printf("输入你所想要的亮度(-100~100 整数) ：\n");
	scanf("%f", &lightness);
	float x = lightness / 100.0;

	readBmp(readPath);
	// 读入一张图片（原画）    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// 创建一个名为 "原画"窗口    
	namedWindow("原画");
	// 在窗口中显示原画    
	imshow("原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//循环变量,图像的坐标，循环变量，遍历每像素的三个分量
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
	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// 读入一张图片（游戏原画）
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1,1);
	// 创建一个名为 "游戏原画"窗口    
	namedWindow("处理画");
	// 在窗口中显示游戏原画    
	imshow("处理画", img1);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	return;
}
//对比度  by胡敏涛
void Contrast()
{
	char readPath[LEN];
	char writePath[LEN];
	printf("请输入待处理图像（BMP格式）文件地址:\n");
	scanf("%s", readPath);/*获取目标文件路径*/
	printf("请输入处理后图像文件地址:\n");
	scanf("%s", writePath);/*获取目标文件路径*/
	readBmp(readPath);
	
	// 读入一张图片（原画）    
	string imgpath = readPath;
	Mat img = imread(imgpath,1);
	// 创建一个名为 "原画"窗口    
	namedWindow("原画");
	// 在窗口中显示原画    
	imshow("原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//从屏幕获得所需对比度														
	int dbd;
	printf("输入你所想要的对比度(0-100整数) ：\n");
	scanf("%f", &dbd);

	float a;
	a = dbd / 100;
	//循环变量,图像的坐标
	int i, j;
	//循环变量，针对彩色图像，遍历每像素的三个分量
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
	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// 读入一张图片（处理画）
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// 创建一个名为 "处理画"窗口    
	namedWindow("处理画");
	// 在窗口中显示处理画    
	imshow("处理画", img1);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	return;
}

/*功能：真彩色转化成256色灰度图像。  */
void MakegGray()    //灰度变化  by谭超
{
	char readPath[LEN];
	char writePath[LEN];
	printf("请输入待处理图像（BMP格式）文件地址:\n");
	scanf("%s", readPath);/*获取目标文件路径*/
	printf("请输入处理后图像文件地址:\n");
	scanf("%s", writePath);/*获取目标文件路径*/
						  
	FILE *fp = fopen(readPath, "rb");

	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//获取图像宽、高、每像素所占位数等信息
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;

	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;

	//灰度图像有颜色表，且颜色表表项为256
	if (biBitCount == 8) {
		//申请颜色表所需要的空间，读颜色表进内存
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	//申请位图数据所需要的空间，读位图数据进内存
	BYTE* pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);

	int lineSize = biBitCount * bmpWidth / 8;
	int alignBytes = ((bmpWidth * biBitCount + 31) & ~31) / 8L - bmpWidth * biBitCount / 8L;
	// 读入一张图片（原画）    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// 创建一个名为 "原画"窗口    
	namedWindow("原画");
	// 在窗口中显示原画    
	imshow("原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);

	BYTE* p_data;
	p_data = pBmpBuf;//取得原图的数据区指针

	for (int i = 0; i < bmpHeight; i++) // 每行
	{
		for (int j = 0; j < 3 * bmpWidth; j = j + 3)// 每列
		{
			/*BYTE* pbyBlue = p_data++;   //得到蓝色值
			BYTE* pbyGreen = p_data++;  //得到绿色值
			BYTE* pbyRed = p_data++;    //得到红色值
			BYTE r = *pbyRed;
			BYTE g = *pbyGreen;
			BYTE b = *pbyBlue;*/
			//取到原r,g,b中的最大值作为像素三分量值的新值
			int b = *(pBmpBuf + i*lineByte + j);
			int g = *(pBmpBuf + i*lineByte + j + 1);
			int r = *(pBmpBuf + i*lineByte + j + 2);

			int gray = 0.299 * r + 0.587 * g + 0.114 * b;
			*(pBmpBuf + i*lineByte + j) = gray;     //将取到的最大值赋给像素的蓝分量
			*(pBmpBuf + i*lineByte + j + 1) = gray;    //将取到的最大值赋给像素的绿分量
			*(pBmpBuf + i*lineByte + j + 2) = gray;      //将取到的最大值赋给像素的红分量
		}
	}
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// 读入一张图片（处理画）
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// 创建一个名为 "处理画"窗口    
	namedWindow("处理画");
	// 在窗口中显示处理画    
	imshow("处理画", img1);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	return;
}
/*图像的旋转，给定一个旋转角度    by谭超（参考网上资源）*/

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
	//读取文件和Bitmap头信息
	fseek(pFile, 0, SEEK_SET);
	fread(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
	fread(&bmiHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
	//先不支持小于16位的位图
	int bitCount = bmiHeader.biBitCount;
	if (bitCount < 16)
	{
		exit(-1);
	}
	int srcW = bmiHeader.biWidth;
	int srcH = bmiHeader.biHeight;
	//原图像每一行去除偏移量的字节数
	int lineSize = bitCount * srcW / 8;
	//偏移量，windows系统要求每个扫描行按四字节对齐
	int alignBytes = ((bmiHeader.biWidth * bitCount + 31) & ~31) / 8L - bmiHeader.biWidth * bitCount / 8L;
	//原图像缓存
	int srcBufSize = lineSize * srcH;
	BYTE* srcBuf = new BYTE[srcBufSize];

	int i, j;
	//读取文件中数据
	for (i = 0; i < srcH; i++)
	{
		fread(&srcBuf[lineSize * i], lineSize, 1, pFile);
		fseek(pFile, alignBytes, SEEK_CUR);
	}
	// 读入一张图片（原画）    
	string imgpath = srcFile.c_str();
	Mat img = imread(imgpath, 1);
	// 创建一个名为 "原画"窗口    
	namedWindow("原画");
	// 在窗口中显示原画    
	imshow("原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);

	int angle;
	printf("输入你所想要逆时针旋转的角度(0-360整数) ：\n");
	scanf("%d", &angle);

	//以图像中心为原点左上角，右上角，左下角和右下角的坐标,用于计算旋转后的图像的宽和高
	POINT pLT, pRT, pLB, pRB;
	pLT.x = -srcW / 2; pLT.y = srcH / 2;
	pRT.x = srcW / 2; pRT.y = srcH / 2;
	pLB.x = -srcW / 2; pLB.y = -srcH / 2;
	pRB.x = srcW / 2; pRB.y = -srcH / 2;
	//旋转之后的坐标
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
	//旋转后图像宽和高
	int desWidth = max(abs(pRBN.x - pLTN.x), abs(pRTN.x - pLBN.x));
	int desHeight = max(abs(pRBN.y - pLTN.y), abs(pRTN.y - pLBN.y));
	//分配旋转后图像的缓存
	int desBufSize = ((desWidth * bitCount + 31) / 32) * 4 * desHeight;
	BYTE *desBuf = new BYTE[desBufSize];
	//将所有像素都预置为黑色
	memset(desBuf, 0, desBufSize);
	//新图像每一行字节数，带有偏移量
	int desLineSize = ((desWidth * bitCount + 31) / 32) * 4;
	//通过新图像的坐标，计算对应的原图像的坐标
	for (i = 0; i < desHeight; i++)
	{
		for (j = 0; j < desWidth; j++)
		{
			//转换到以图像为中心的坐标系，并进行逆旋转
			int tX = (j - desWidth / 2)*cos(RADIAN(360 - angle)) + (-i + desHeight / 2)*sin(RADIAN(360 - angle));
			int tY = -(j - desWidth / 2)*sin(RADIAN(360 - angle)) + (-i + desHeight / 2)*cos(RADIAN(360 - angle));
			//如果这个坐标不在原图像内，则不赋值
			if (tX > srcW / 2 || tX < -srcW / 2 || tY > srcH / 2 || tY < -srcH / 2)
			{
				continue;
			}
			//再转换到原坐标系下
			int tXN = tX + srcW / 2; int tYN = abs(tY - srcH / 2);
			//值拷贝
			memcpy(&desBuf[i * desLineSize + j * bitCount / 8], &srcBuf[tYN * lineSize + tXN * bitCount / 8], 3);
		}
	}

	//创建目标文件
	HFILE hfile = _lcreat(desFile.c_str(), 0);
	//文件头信息
	BITMAPFILEHEADER nbmfHeader;
	nbmfHeader.bfType = 0x4D42;
	nbmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + desWidth * desHeight * bitCount / 8;
	nbmfHeader.bfReserved1 = 0;
	nbmfHeader.bfReserved2 = 0;
	nbmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//Bitmap头信息
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

	//写入文件头信息
	_lwrite(hfile, (LPCSTR)&nbmfHeader, sizeof(BITMAPFILEHEADER));
	//写入Bitmap头信息
	_lwrite(hfile, (LPCSTR)&bmi, sizeof(BITMAPINFOHEADER));
	//写入图像数据
	_lwrite(hfile, (LPCSTR)desBuf, desBufSize);
	_lclose(hfile);
	// 读入一张图片（处理画）
	string imgpath1 = desFile.c_str();
	Mat img1 = imread(imgpath1, 1);
	// 创建一个名为 "处理画"窗口    
	namedWindow("处理画");
	// 在窗口中显示处理画    
	imshow("处理画", img1);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
}
/*图像反色*/
void Inverse()//by  雷雅迪
{
	char readPath[LEN];
	char writePath[LEN];
	printf("请输入待处理图像（BMP格式）文件地址:\n");
	scanf("%s", readPath);/*获取目标文件路径*/
	printf("请输入处理后图像文件地址:\n");
	scanf("%s", writePath);/*获取目标文件路径*/
	readBmp(readPath);
	// 读入一张图片（原画）    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// 创建一个名为 "原画"窗口    
	namedWindow("原画");
	// 在窗口中显示原画    
	imshow("原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);

	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//循环变量,图像的坐标，循环变量，遍历每像素的三个分量
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
	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// 读入一张图片（处理画）
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// 创建一个名为 "处理画"窗口    
	namedWindow("处理画");
	// 在窗口中显示处理画    
	imshow("处理画", img1);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	return;
}
/*图像的老化，怀旧风格*/
void Older()//by 雷雅迪
{
	char readPath[LEN];
	char writePath[LEN];
	printf("请输入待处理图像（BMP格式）文件地址:\n");
	scanf("%s", readPath);/*获取目标文件路径*/
	printf("请输入处理后图像文件地址:\n");
	scanf("%s", writePath);/*获取目标文件路径*/
	readBmp(readPath);
	// 读入一张图片（原画）    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// 创建一个名为 "原画"窗口    
	namedWindow("原画");
	// 在窗口中显示原画    
	imshow("原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);

	int x;
	printf("请输入老化值:\n");
	scanf("%d", &x);
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//循环变量,图像的坐标，循环变量，遍历每像素的三个分量
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
	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// 读入一张图片（处理画）
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// 创建一个名为 "处理画"窗口    
	namedWindow("处理画");
	// 在窗口中显示处理画    
	imshow("处理画", img1);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	return;
}
/*图像裁剪*/
void cut()//by雷雅迪
{
	char readPath[LEN];
	char writePath[LEN];
	printf("请输入待处理图像（BMP格式）文件地址:\n");
	scanf("%s", readPath);/*获取目标文件路径*/
	printf("请输入处理后图像文件地址:\n");
	scanf("%s", writePath);/*获取目标文件路径*/
	readBmp(readPath);
	// 读入一张图片（原画）    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// 创建一个名为 "原画"窗口    
	namedWindow("原画");
	// 在窗口中显示原画    
	imshow("原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);

	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//获取想要裁剪的坐标值
	float x1, x2, y1, y2;
	int ka, kb, kc, kd;
	printf("输入你所想要的x1(0-100整数) ：\n");
	scanf("%f", &x1);
	printf("输入你所想要的x2(0-100整数) ：\n");
	scanf("%f", &x2);
	printf("输入你所想要的y1(0-100整数) ：\n");
	scanf("%f", &y1);
	printf("输入你所想要的y2(0-100整数) ：\n");
	scanf("%f", &y2);
	//循环变量,图像的坐标，循环变量，遍历每像素的三个分量
	int i, j;
	for (i = 0; i < bmpHeight*(y1 / 100); i++)
	{
		for (j = 0; j < 3 * bmpWidth; j = j + 3)
		{
			for (ka = 0; ka < 3; ka++)//每像素RGB三个分量分别置0才变成黑色
			{
				*(pBmpBuf + i*lineByte + j + ka) = 0;
			}
		}
	}
	for (i = bmpHeight - 1; i >bmpHeight*(y2 / 100); i--)
	{
		for (j = 0; j < 3 * bmpWidth; j = j + 3)
		{
			for (kb = 0; kb < 3; kb++)//每像素RGB三个分量分别置0才变成黑色
			{
				*(pBmpBuf + i*lineByte + j + kb) = 0;
			}
		}
	}
	for (i = 0; i < bmpHeight; i++)
	{
		for (j = 0; j < 3 * bmpWidth*(x1 / 100); j = j + 3)
		{
			for (kc = 0; kc < 3; kc++)//每像素RGB三个分量分别置0才变成黑色
			{
				*(pBmpBuf + i*lineByte + j + kc) = 0;
			}
		}
	}
	for (i = 0; i < bmpHeight; i++)
	{
		for (j = 3 * bmpWidth*(x2 / 100); j <3 * bmpWidth; j = j + 3)
		{
			for (kd = 0; kd < 3; kd++)//每像素RGB三个分量分别置0才变成黑色
			{
				*(pBmpBuf + i*lineByte + j + kd) = 0;
			}
		}
	}

	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	// 读入一张图片（处理画）
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// 创建一个名为 "处理画"窗口    
	namedWindow("处理画");
	// 在窗口中显示处理画    
	imshow("处理画", img1);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);
	return;
}
void mirror()// by 胡敏涛
{

	char readPath[LEN];
	char writePath[LEN];
	printf("请输入待处理图像（BMP格式）文件地址:\n");
	scanf("%s", readPath);/*获取目标文件路径*/
	printf("请输入处理后图像文件地址:\n");
	scanf("%s", writePath);/*获取目标文件路径*/

	readBmp(readPath);
	// 读入一张图片（原画）    
	string imgpath = readPath;
	Mat img = imread(imgpath, 1);
	// 创建一个名为 "原画"窗口    
	namedWindow("原画");
	// 在窗口中显示原画    
	imshow("原画", img);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);

	int height = bmpHeight;
	int width = bmpWidth;
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	int imgSize = lineByte * bmpHeight;

	int i, j, t1, t2, t3;//两个循环变量和三个临时变量
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < (3 * width) / 2; j = j + 3)
		{
			int b = *(pBmpBuf + i*lineByte + j);
			int g = *(pBmpBuf + i*lineByte + j + 1);
			int r = *(pBmpBuf + i*lineByte + j + 2);

			b = t1 = *(pBmpBuf + i*lineByte + (width - 1) * 3 - j); //水平镜像  
			g = t2 = *(pBmpBuf + i*lineByte + (width - 1) * 3 - (j + 1));
			r = t3 = *(pBmpBuf + i*lineByte + (width - 1) * 3 - (j + 2));
			b = *(pBmpBuf + i*lineByte + (width - 1) * 3 - j) = *(pBmpBuf + (i*lineByte) + j); //水平镜像  
			g = *(pBmpBuf + i*lineByte + (width - 1) * 3 - (j + 1)) = *(pBmpBuf + (i*lineByte) + j + 2);
			r = *(pBmpBuf + i*lineByte + (width - 1) * 3 - (j + 2)) = *(pBmpBuf + (i*lineByte) + j + 1);
			b = *(pBmpBuf + (i*lineByte) + j) = t1;
			g = *(pBmpBuf + (i*lineByte) + j + 2) = t2;
			r = *(pBmpBuf + (i*lineByte) + j + 1) = t3;
		}

	}
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

	//释放
	delete[]pColorTable;
	delete[]pBmpBuf;
	
	// 读入一张图片（处理画）
	string imgpath1 = writePath;
	Mat img1 = imread(imgpath1, 1);
	// 创建一个名为 "处理画"窗口    
	namedWindow("处理画");
	// 在窗口中显示处理画    
	imshow("处理画", img1);
	// 等待6000 ms后窗口自动关闭    
	waitKey(6000);


	system("pause");
	return;
}





//循环变量，针对彩色图像，遍历每像素的三个分量

//将图像数据存盘

void main()//主函数
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
			printf("请输入待处理图像（BMP格式）文件地址:\n");
			scanf("%s", readPath);/*获取目标文件路径*/
			printf("请输入处理后图像文件地址:\n");
			scanf("%s", writePath);/*获取目标文件路径*/
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


