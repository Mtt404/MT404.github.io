#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class Cstack
{
public:
	Cstack();
	void push1(double a);  
	double pop1();  
	void push2(char a);
	void push3(char a);
	char pop2();
	char pop3();
	bool Cstack::oper1Empty();
	char Cstack::gettop2();
	double Cstack::gettop1();
	

	double num[25];
	string oper1;
	string oper2;
	int top1;
	int top2;
	int top3;
};

Cstack::Cstack()
{
	top1 = -1;
	top2 = -1;
	top3 = -1;
	for (int i = 0; i < 25; i++)
	{
		num[i] = 0;
	}
	num[20] = 0;
	oper1 = "0000000000000000";
	oper2 = "0000000000000000";
	
}

void Cstack::push1(double a)
{
	top1++;
	num[top1] = a;
}

double Cstack::pop1()
{
	top1--;
	return num[top1 + 1];
}

char Cstack::pop2()
{
	top2--;
	return oper1[top2 + 1];
}

void Cstack::push2(char a)
{
	top2++;
	oper1[top2] = a;
}
void Cstack::push3(char a)
{
	top3++;
	oper2[top3] = a;
}
char Cstack::pop3()
{
	top3--;
	return oper2[top3 + 1];
}

bool Cstack::oper1Empty()
{
	if (top2 == -1)
	{
		return true;
	}
	else
		return false;
}
char Cstack::gettop2()
{
	return oper1[top2];
}
double Cstack::gettop1()
{
	return num[top1];
}
void conversion();

int main()
{
	Cstack a;
	conversion();

	system("pause");
	return 0;
}

void conversion()
{
	Cstack a,b,c;
	
	string newstr;
	cout << "输入算术式：\n";
	cin >> newstr;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int index = 1;
	int index2 = 1;
	int i = 0;
	for ( i; i < newstr.length(); i += index)
	{
		if (newstr[i] == '0')
		{
			a.num[count2] = -1000;
			count2 ++;
		}
		else if (i == 0 && newstr[i] == '-')
		{
			a.num[0] = -1000;
			count2 ++;
			a.oper1[1] = newstr[0];
			count2 ++;
			

		}
		else if (!(i == 0) && newstr[i] == '-'&& newstr[i - 1] == '(')
		{
			a.num[count2] = -1000;
			count2++;
			a.oper1[count2] = newstr[i];
			count2++;
		}

		else if (newstr[i + 1] == '.')
		{
			double temp = (newstr[i] - 48) + (1.0 / 10)*(newstr[i + 2] - 48);
			a.num[count2]=temp;
			count2 ++;
			i += 2;
		}
		
		else
		{
			if (newstr[i] >= 48 && newstr[i] <= 57)
			{
				index = 1;
				while (newstr[i + index] >= 48 && newstr[i + index] <= 57)
				{
					index++;
				}
			}
			else
			{
				a.oper1[count2]=newstr[i];
				count2++;
				index = 1;
			}

			if (index == 1)
			{
				if (newstr[i] >= 48 && newstr[i] <= 57)
				{
					a.num[count2]=(newstr[i] - 48);
					count2++;
					count1++;
				}

			}
			if (index > 1 && newstr[i] >= 48 && newstr[i] <= 57)
			{
				int temp = 0;
				for (int j = 0; j < index; j++)
				{
					temp += (newstr[i + j] - 48) * pow(10, index - 1 - j);
				}
				a.num[count2]=temp;
				count2++;
				
			}
		}
	}
	for (int i = 0; i < count2; i ++)
	{

		//if ((!b.oper1Empty()) && a.oper1[i] == '-' && (a.num[i - 1] ==0)&& !(a.oper1[i - 1]==')'))
		//{
		//	b.push1(0);
		//	
		//}
		//else if (a.oper1Empty() && a.oper1[i] == '-')/*100+((60-2*3.4)/5)-5*/
		//{
		//	b.push1(0);
		//}
			
		

	    if(a.num[i]> 0)
		{
			b.push1(a.num[i]);
			
		}
		else if (a.num[i] == (-1000))
		{
			b.push1(0);
		}
		else
		{
			
			if (!(i==0)&&(b.oper1Empty() || b.gettop2() == '('))
			{
				b.push2(a.oper1[i]);
				
			}
			else
			{
				if (a.oper1[i] == '(')
				{
					b.push2(a.oper1[i]);
					
				}

				if (a.oper1[i] == '+' || a.oper1[i] == '-')
				{
					if (b.gettop2() == '(')
					{
						b.push2(a.oper1[i]);
						
					}
					else
					{
						while ((!b.oper1Empty()) &&  b.gettop2() != '(')
						{
							b.push3(b.pop2());
							b.push1(-999);
						}
						b.push2(a.oper1[i]);
						
					}
				}

				if (a.oper1[i] == '*' || a.oper1[i] == '/')
				{
					if (b.gettop2() == '(')
					{
						b.push2(a.oper1[i]);
						
					}
					else
					{
						while ((!b.oper1Empty()) && (b.gettop2() == '*' || b.gettop2() == '/'))
						{
							b.push3(b.pop2());
							b.push1(-999);
						}
						b.push2(a.oper1[i]);
						
					}
				}

				if (a.oper1[i] == ')')
				{
					while ((!b.oper1Empty()) && (b.gettop2() != '('))
					{
						b.push3(b.pop2());
						b.push1(-999);
					}
					if ((!b.oper1Empty()) && b.gettop2() == '(')
					{
						char temp = b.pop2();
						count3++;

					}
				}
			}
		}
	}
	while ((!b.oper1Empty()))
	{
		b.push3(b.pop2());
		b.push1(-999);
	}
	int j = 0;
	int k = 0;
	int count4 = count2 - (2 * count3);
	for (int i = 0; i <count4; i++)
	{
		if (!(b.num[i] == (-999)))
		{
			c.push1(b.num[i]);
		}
		else
		{
			
			char operate = b.oper2[j];
			
		
			double temp1 = c.pop1();
			double temp2 = c.pop1();
			
			switch (operate)
			{
			case'+':
				c.push1(temp1 + temp2);
				break;
			case'-':
				if (temp2 - temp1 == 0)
				{
					c.push1(-1000);
				}
				else
				{
					c.push1(temp2 - temp1);
				}


				break;
			case'*':
				c.push1(temp1 * temp2);
				break;
			case'/':
				if (temp1 == (-1000) || temp1 == 0)
				{
					cout << "eroor!" << endl;
					k = 1;
				}

				else
				{
					c.push1(temp2 / temp1);
				}


				break;
			default:
				exit(0);

			}

			j++;
		}

		
		

		
	}

	
	if (k == 0)
	{
		cout << "结果为：\n" << c.pop1() << endl;
	}
	
	
}