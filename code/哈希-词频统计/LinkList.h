#pragma once
#include <stdio.h>
#include<stdlib.h>
#include <cstring> 
#include<iostream>
using namespace std;
   //
typedef struct node {
	char danci[19];//储存单词 
	int count;
	int zms;
	struct node *next;
}NODE;
class LinkList
{
public:
	NODE *head;

public:
	LinkList() { head = NULL; }
	~LinkList();
	bool clearSqList();
	bool isEmpty() { return head == NULL; }
	int Length();
	bool GetElem(int i,node word);
	bool Insert(int i, node word);
	bool Seek(node word);
};
LinkList::~LinkList()//和清空一样
{
	NODE *p = head;
	while (head)
	{
		p = head;
		head = head->next;
		delete(p);
	}
}
bool LinkList::Seek(node word)
{
	int monitor = 0;
	NODE *p = head;
	while (p)
	{

		for (int m = 0; m < word.zms; m++)
		{

			if (p->danci[m] == word.danci[m])
			{
				monitor += 1;
			}
		}
		if (monitor == word.zms)
		{
			cout << "单词频数为：";
			cout << p->count << endl;
			return true;
		}
		if (!(monitor == word.zms))
		{
			monitor = 0;
			p = p->next;

		}
	}
	monitor = 0;
	cout << "没有这个单词！！" << endl;
	return true;
		
	
}
bool LinkList::clearSqList()//清空函数，和析构一样
{
	NODE *p = head;
	while (head)
	{
		p = head;
		head = head->next;
		delete(p);
	}
	return true;
}
//获取链表长度
int LinkList::Length()
{
	NODE *p = head;
	int len = 0;
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}
bool LinkList::GetElem(int i,node word)//*e是返回的元素
{
	NODE *p = head;
	int j = 0;
	while (p&&j < i)
	{
		p = p->next;
		j++;
	}
	if (p == NULL) return false;
	for (int m = 0; m <p->zms + 1; m++)
	{
		word.danci[m] = p->danci[m];
	}

	word.count = p->count;
	word.zms = p->zms;
	/**e = p->data;*/
	return true;
}

bool LinkList::Insert(int i, node word)
{
	
	
	int j = 0;
   
	int monitor = 0;
   NODE *p = head, *s;
   if (head == NULL)
   {
	   s = (NODE *)new node;
	   for (int m = 0; m < word.zms + 1; m++)
	   {
		   s->danci[m] = word.danci[m];
	   }

	   s->count = 1;
	   s->next = NULL;
	   s->zms = word.zms;
	   head = s;
	   return true;
   }
  
	   
   
   while (p->next)
   {
	   
	   for (int m = 0; m < word.zms; m++)
	   {

		   if (p->danci[m] == word.danci[m])
		   {
			   monitor += 1;
		   }
	   }
	   if (monitor == word.zms)
	   {
		   p->count++;
		   return true;
	   }
	   if (!(monitor == word.zms))
	   {
		   monitor = 0;
		   p = p->next;
		  
	   }
   }
   for (int m = 0; m < word.zms; m++)
   {

	   if (p->danci[m] == word.danci[m])
	   {
		   monitor += 1;
	   }
   }
   if (monitor == word.zms)
   {
	   p->count++;
	   return true;
   }
   else
   {
	   monitor = 0;
	   s = (NODE *)new node;
	   for (int m = 0; m < word.zms + 1; m++)
	   {
		   s->danci[m] = word.danci[m];
	   }

	   s->count = 1;
	   s->next = NULL;
	   s->zms = word.zms;
	   p->next = s;
	   return true;
   }
   
}