#include "矩阵.h"
int main()
{
	matrix a1,b1,c1;
	a1.set();
	b1.set();
	c1.add(a1, b1);
	cout << "加法：" << endl;

	c1.show();
	a1.set();
	b1.set();
	c1.subtract(a1, b1);
	cout << "减法：" << endl;
	c1.show();
	a1.set();
	b1.set();
	c1.multiply(a1, b1);
	cout << "乘法：" << endl;
	c1.show();


	
	system("pause");
	return 0;
}
