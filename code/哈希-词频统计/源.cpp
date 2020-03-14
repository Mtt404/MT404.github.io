
#include <string> 
#include<iostream>
#include"LinkList.h"
using namespace std;
#define NHASH 83 // 最好定位质数
int Hash(node word);
void process();
node SeeK();

int main()
{
	process();
	system("pause");
	return 0;
}


int Hash(node word)
{
	
	int key = 0;
	int temp2 = 0;
	for (int j = 0; j < word.zms; j++)
	{
		int temp= word.danci[j];
	    temp2 += temp;
	}
	key = temp2 % 83;
	return key;
}
node SeeK()
{
	cout << "请输入要查找的单词：" << endl;
	char w[19];
	cin.getline(w, 19);

	int K1 = 0;
	node word;
	word.count = 1;
	word.zms = 0;
	int i1 = 0;
	while (w[i1] >= 'a'&&w[i1] <= 'z')
	{
		word.zms++;
		word.danci[K1++] = w[i1];//把当前字母存入数组  
		i1++;
	}

	return word;
}
void process()
{
	node t_word;
	LinkList li[NHASH];
	int K;
	FILE *fp;
	char ch;
	char a[50];
	cout << "请输入文档路径：" << endl;
	cin.getline(a, 50);
	
	fp = fopen(a, "r");//读取文件，需改为你要读取的文件的绝对路径  

	while (!feof(fp))//feof()检测是否达到文件尾部C:\\Users\\think\\Desktop\\English.txt  
	{
		ch = getc(fp);//获取当前字符  
		if (ch == ' ' || ch == 10)
		{//ASCLL码中10为换行符，此条件为遇到空格或火车则跳过  
			continue;
		}
		if (ch >= 'a'&&ch <= 'z')               //发现一个单词  
		{
			K = 0;
			t_word.count = 1;
			t_word.zms = 0;
			int temp = 0;
			while (ch >= 'a'&&ch <= 'z')
			{
				int ch1 = ch;
				temp += ch1;
				t_word.zms++;
				t_word.danci[K++] = ch;//把当前字母存入数组  
				ch = getc(fp);
			}

			t_word.danci[K++] = '\0';//结束标志\0  


			int h = Hash(t_word);
			li[h].Insert(li[h].Length(), t_word);
			
		}
	}


	cout << "文本中所有单词和频率如下：" << endl;
	for (int i = 0; i < NHASH; i++)
	{
		NODE *p = li[i].head;
		while (p)
		{
			for (int n = 0; n <p->zms; n++)
			{
				cout << p->danci[n];
			}
			cout << ":  " << p->count << endl;
			p = p->next;

		}


	}


	//查找
	cout << "查找：" << endl;
	int monitor = 0;
	int t = 0;
	int m = 0;
	node h3;
	node h;
	do 
	{
		if (monitor == 0)
		{
			h3 = SeeK();
			int h2 = Hash(h3);
			li[h2].Seek(h3);
			monitor++;
		}
		else
		{
			t += 1;
			cout << "再次查找？(输入1---是，0---否)" << endl;
			int c;
			cin >> c;
			cin.get();
			if(c)
			{
				h = SeeK();
				int h2 = Hash(h);
				li[h2].Seek(h);
			}
			m += 1;
			if(c==0)
				exit(0);
		}
		
	} while (t == m);

		


	
		
	
	
	

}



