#include "����.h"
int main()
{
	matrix a1,b1,c1;
	a1.set();
	b1.set();
	c1.add(a1, b1);
	cout << "�ӷ���" << endl;

	c1.show();
	a1.set();
	b1.set();
	c1.subtract(a1, b1);
	cout << "������" << endl;
	c1.show();
	a1.set();
	b1.set();
	c1.multiply(a1, b1);
	cout << "�˷���" << endl;
	c1.show();


	
	system("pause");
	return 0;
}
