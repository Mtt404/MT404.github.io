#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
template<class T>
class Cstack
{
public:
	Cstack();
	void push1(T a);
	double pop1();
	void push2(char a);
	void push3(char a);
	char pop2();
	char pop3();
	bool Cstack::oper1Empty();
	char Cstack::gettop2();
	double Cstack::gettop1();


	T num[25];
	string oper1;
	string oper2;
	int top1;
	int top2;
	int top3;
};
template<class T>
Cstack<T>::Cstack()
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
template<class T>
void Cstack<T>::push1(T a)
{
	top1++;
	num[top1] = a;
}
template<class T>
double Cstack<T>::pop1()
{
	top1--;
	return num[top1 + 1];
}
template<class T>
char Cstack<T>::pop2()
{
	top2--;
	return oper1[top2 + 1];
}
template<class T>
void Cstack<T>::push2(char a)
{
	top2++;
	oper1[top2] = a;
}
template<class T>
void Cstack<T>::push3(char a)
{
	top3++;
	oper2[top3] = a;
}
template<class T>
char Cstack<T>::pop3()
{
	top3--;
	return oper2[top3 + 1];
}
template<class T>
bool Cstack<T>::oper1Empty()
{
	if (top2 == -1)
	{
		return true;
	}
	else
		return false;
}
template<class T>
char Cstack<T>::gettop2()
{
	return oper1[top2];
}
template<class T>
double Cstack<T>::gettop1()
{
	return T num[top1];
}
void conversion();

int main()
{
	Cstack<double> a;
	conversion();

	system("pause");
	return 0;
}

void conversion()
{
	Cstack<double>a, b, c;

	string newstr;
	cout << "输入算术式：\n";
	cin >> newstr;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int index = 1;
	int index2 = 1;
	int i = 0;
	for (i; i < newstr.length(); i += index)
	{
		if (newstr[i] == '0')
		{
			a.num[count2] = -1000;
			count2++;
		}
		else if (i == 0 && newstr[i] == '-')
		{
			a.num[0] = -1000;
			count2++;
			a.oper1[1] = newstr[0];
			count2++;


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
			a.num[count2] = temp;
			count2++;
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
				a.oper1[count2] = newstr[i];
				count2++;
				index = 1;
			}

			if (index == 1)
			{
				if (newstr[i] >= 48 && newstr[i] <= 57)
				{
					a.num[count2] = (newstr[i] - 48);
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
				a.num[count2] = temp;
				count2++;

			}
		}
	}
	for (int i = 0; i < count2; i++)
	{
		if (a.num[i]> 0)
		{
			b.push1(a.num[i]);

		}
		else if (a.num[i] == (-1000))
		{
			b.push1(0);
		}
		else
		{

			if (!(i == 0) && (b.oper1Empty() || b.gettop2() == '('))
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
						while ((!b.oper1Empty()) && b.gettop2() != '(')
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