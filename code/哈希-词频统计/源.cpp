
#include <string> 
#include<iostream>
#include"LinkList.h"
using namespace std;
#define NHASH 83 // ��ö�λ����
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
	cout << "������Ҫ���ҵĵ��ʣ�" << endl;
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
		word.danci[K1++] = w[i1];//�ѵ�ǰ��ĸ��������  
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
	cout << "�������ĵ�·����" << endl;
	cin.getline(a, 50);
	
	fp = fopen(a, "r");//��ȡ�ļ������Ϊ��Ҫ��ȡ���ļ��ľ���·��  

	while (!feof(fp))//feof()����Ƿ�ﵽ�ļ�β��C:\\Users\\think\\Desktop\\English.txt  
	{
		ch = getc(fp);//��ȡ��ǰ�ַ�  
		if (ch == ' ' || ch == 10)
		{//ASCLL����10Ϊ���з���������Ϊ�����ո���������  
			continue;
		}
		if (ch >= 'a'&&ch <= 'z')               //����һ������  
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
				t_word.danci[K++] = ch;//�ѵ�ǰ��ĸ��������  
				ch = getc(fp);
			}

			t_word.danci[K++] = '\0';//������־\0  


			int h = Hash(t_word);
			li[h].Insert(li[h].Length(), t_word);
			
		}
	}


	cout << "�ı������е��ʺ�Ƶ�����£�" << endl;
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


	//����
	cout << "���ң�" << endl;
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
			cout << "�ٴβ��ң�(����1---�ǣ�0---��)" << endl;
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



