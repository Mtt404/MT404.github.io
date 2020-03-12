#define D_SCL_SECURE_NO_WARNIN
#include<string>
#include<iostream>


using namespace std;
int Dijkstra();
void Again1();
void Again2();
int Floyd();
void Choose();
int main()
{
	Choose();
	system("pause");
	return 0;	
}
void Choose()
{
	int t;
	cout << " ��ѡ��Dijkstra����Floyd�㷨������1--Dijkstra������0--Floyd" << endl;
	cin >> t;
	if (t)
	{
		Dijkstra();
	}
	else
	{
		Floyd();
	}
}
int Dijkstra()
{
	cout << "Dijkstra����" << endl;
	int v, v1, v2, v3;
	string a, b;
	cout << "��������㣺�����ߺͼ���վ��A 11ע��ո�" << endl;
	cin >> a >> v;
	if (a != "A"&&a != "B"&&a != "C"&&a != "T")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}

	if ((v<1 || v>18) && a == "C")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}
	if ((v<1 || v>15) && a == "B")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}
	if ((v<1 || v>16) && a == "A")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}
	if ((v<1 || v>6) && a == "T")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}
	cout << "�������յ㣺�����ߺͼ���վ��B 12ע��ո�" << endl;
	cin >> b>>v3;
	if (b != "A"&&b != "B"&&b != "C"&&b != "T")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>18) && b == "C")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}
	if ((v3<1 || v3>15) && b == "B")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}
	if ((v3<1 || v3>16) && b == "A")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}
	if ((v3<1 || v3>6) && b == "T")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again1();
		return 0;
	}
	if (a == "A")
		v1 = v-1;
	if (a == "B")
		v1 = 15+v;
	if (a == "C")
		v1 = 30+v;
	if (a == "T")
		v1 = 48+v;
	if (b == "A")
		v2 = v3 - 1;
	if (b == "B")
		v2 = 15 + v3;
	if (b == "C")
		v2 = 30 + v3;
	if (b == "T")
		v2 = 48 + v3;
	
	int arcs[55][55];//ͼ���ڽӾ���

	for (int i = 0; i < 55; i++)
	{
		for (int j = 0; j < 55; j++)
		{
			if (i == j)
				arcs[i][j] = 0;
			else
				arcs[i][j] = 1000;
		}
	}
	arcs[0][1] = 1;
	arcs[1][0] = 1;
	arcs[1][2] = 1;
	arcs[2][1] = 1;
	arcs[2][49] = 1;

	arcs[3][4] = 1;
	arcs[4][3] = 1;
	arcs[4][5] = 1;
	arcs[5][4] = 1;
	arcs[5][6] = 1;
	arcs[6][5] = 1;
	arcs[6][7] = 1;
	arcs[7][6] = 1;
	arcs[7][50] = 1;
	arcs[8][50] = 1;
	arcs[8][9] = 1;
	arcs[9][8] = 1;
	arcs[9][10] = 1;
	arcs[10][11] = 1;
	arcs[11][51] = 1;
	arcs[12][13] = 1;
	arcs[13][14] = 1;
	arcs[14][52] = 1;
	arcs[16][53] = 1;
	arcs[17][18] = 1;
	arcs[18][19] = 1;
	arcs[19][20] = 1;
	arcs[20][50] = 1;
	for (int i = 21; i < 26; i++)
	{
		int m = i + 1;
		arcs[i][m] = 1;
	}

	arcs[26][51] = 1;
	arcs[27][28] = 1;
	arcs[28][54] = 1;
	arcs[54][29] = 1;
	arcs[29][30] = 1;

	arcs[31][32] = 1;
	arcs[32][33] = 1;
	arcs[33][49] = 1;
	arcs[34][35] = 1;
	arcs[35][49] = 1;
	for (int i = 36; i < 40; i++)
	{
		int m = i + 1;
		arcs[i][m] = 1;
	}
	arcs[40][53] = 1;
	arcs[41][42] = 1;
	arcs[42][43] = 1;
	arcs[43][54] = 1;
	arcs[44][45] = 1;
	arcs[45][52] = 1;
	arcs[46][47] = 1;
	arcs[47][48] = 1;
	arcs[48][31] = 1;
	arcs[31][48] = 1;
	arcs[49][36] = 1;
	arcs[50][8] = 1;
	arcs[50][21] = 1;
	arcs[51][27] = 1;
	arcs[51][12] = 1;
	arcs[52][15] = 1;
	arcs[52][46] = 1;
	arcs[53][17] = 1;
	arcs[53][41] = 1;
	arcs[54][29] = 1;
	arcs[54][44] = 1;

	for (int i = 0; i < 55; i++)
	{
		for (int j = 54; j > i; j--)
		{
			arcs[j][i] = arcs[i][j];
		}
	}
	arcs[49][3] = 1;
	arcs[49][36] = 1;
	arcs[3][49] = 1;
	arcs[36][49] = 1;
	arcs[50][8] = 1;
	arcs[50][21] = 1;
	arcs[8][50] = 1;
	arcs[21][50] = 1;
	arcs[51][27] = 1;
	arcs[51][12] = 1;
	arcs[27][51] = 1;
	arcs[12][51] = 1;
	arcs[52][46] = 1;
	arcs[52][15] = 1;
	arcs[46][52] = 1;
	arcs[15][52] = 1;
	arcs[53][17] = 1;
	arcs[53][41] = 1;
	arcs[17][53] = 1;
	arcs[41][53] = 1;
	arcs[54][44] = 1;
	arcs[54][29] = 1;
	arcs[44][54] = 1;
	arcs[29][54] = 1;
	bool S[55];   //��¼��Դ��V0���յ�Vi�Ƿ��Ѿ�ȷ��Ϊ���·����ȷ���˼�true�������false
	//int Path[55]; //��¼��Դ��V0���յ�Vi�ĵ�ǰ���·�����յ�Vi��ֱ��ǰ��������ţ���V0��Vi֮���б�ǰ��ΪV0����Ϊ-1 
	int D[55];  //��¼Դ�㵽�յ�֮�����·���ĳ��ȣ����ڼ�V1��Vi�ıߵ�Ȩֵ�������Ϊ1000       
	int n = 55;//������
	for (int v = 0; v < n; v++)//n���������γ�ʼ��
	{
		S[v] = false;//S��ʼ��Ϊ�ռ�
		D[v] = arcs[v1][v];//��v1�������յ�����·�����ȳ�ʼ��Ϊ���ϵ�Ȩֵ
		//if (D[v] < 1000)
			//Path[v] = v1;//���v1��v֮���бߣ���v��ǰ����ʼ��Ϊv1
		
			//Path[v] = -1;//���v0��v֮���ޱߣ���v��ǰ����ʼ��Ϊ-1
	}
	S[v1] = true; //��v1����s
	D[v1] = 0;//Դ�㵽Դ���ȨֵΪ0
			  //---------��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ����������·������v�ӵ�S����
	for (int i = 1; i < n; i++)//���ζ�����n-1��������м���
	{
		int min = 1000;
		int v = v1;
		for (int w = 0; w < n; w++)
		{
			if (!S[w] && D[w] < min)
			{//ѡ��һ����ǰ���·�����յ�Ϊv
				v = w;
				min = D[w];
			}
			S[v] = true;//��v�ӵ�s������
			for (int w = 0; w < n; w++)
			{//���´�v0����������V-S�����ж�������·������
				if (!S[w] && (D[v] + arcs[v][w] < D[w]))
				{
					D[w] = D[v] + arcs[v][w];//����D[w]
					
				}
			}
		}
	}
	cout << "Dijkstra��������Ҫ�����ĳ�վ����Ϊ��" << D[v2]+1 << "վ" << endl;
	
	return 0;
	/*Again();*/
}
void Again1()
{
	cout << "Again?(����1=�ǣ�����0=��)" << endl;
	int t;
	cin >> t;
	if (t)
	{
		Dijkstra();
	}
	else
		return;
}
void Again2()
{
	cout << "Again?(����1=�ǣ�����0=��)" << endl;
	int t;
	cin >> t;
	if (t)
	{
		Floyd();
	}
	else
		exit(0);
}
int Floyd()
{
	cout << "Floyd����" << endl;
	int v, v1, v2, v3;
	string a, b;
	cout << "��������㣺�����ߺͼ���վ��A 11ע��ո�" << endl;
	cin >> a >> v;
	if (a != "A"&&a != "B"&&a != "C"&&a != "T")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}

	if ((v<1 || v>18) && a == "C")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if ((v<1 || v>15) && a == "B")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if ((v<1 || v>16) && a == "A")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if ((v<1 || v>6) && a == "T")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	cout << "�������յ㣺�����ߺͼ���վ��B 12ע��ո�" << endl;
	cin >> b >> v3;
	if (b != "A"&&b != "B"&&b != "C"&&b != "T")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>18) && b == "C")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>15) && b == "B")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>16) && b == "A")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>6) && b == "T")
	{
		cout << "��վ�����ڣ�����" << endl;
		Again2();
		return 0;
	}
	if (a == "A")
		v1 = v - 1;
	if (a == "B")
		v1 = 15 + v;
	if (a == "C")
		v1 = 30 + v;
	if (a == "T")
		v1 = 48 + v;
	if (b == "A")
		v2 = v3 - 1;
	if (b == "B")
		v2 = 15 + v3;
	if (b == "C")
		v2 = 30 + v3;
	if (b == "T")
		v2 = 48 + v3;

	int arcs[55][55];//ͼ���ڽӾ���

	for (int i = 0; i < 55; i++)
	{
		for (int j = 0; j < 55; j++)
		{
			if (i == j)
				arcs[i][j] = 0;
			else
				arcs[i][j] = 1000;
		}
	}
	arcs[0][1] = 1;
	arcs[1][0] = 1;
	arcs[1][2] = 1;
	arcs[2][1] = 1;
	arcs[2][49] = 1;
	
	arcs[3][4] = 1;
	arcs[4][3] = 1;
	arcs[4][5] = 1;
	arcs[5][4] = 1;
	arcs[5][6] = 1;
	arcs[6][5] = 1;
	arcs[6][7] = 1;
	arcs[7][6] = 1;
	arcs[7][50] = 1;
	arcs[8][50] = 1;
	arcs[8][9] = 1;
	arcs[9][8] = 1;
	arcs[9][10] = 1;
	arcs[10][11] = 1;
	arcs[11][51] = 1;
	arcs[12][13] = 1;
	arcs[13][14] = 1;
	arcs[14][52] = 1;
	arcs[16][53] = 1;
	arcs[17][18] = 1;
	arcs[18][19] = 1;
	arcs[19][20] = 1;
	arcs[20][50] = 1;
	for (int i = 21; i < 26; i++)
	{
		int m = i + 1;
		arcs[i][m] = 1;
	}

	arcs[26][51] = 1;
	arcs[27][28] = 1;
	arcs[28][54] = 1;
	arcs[54][29] = 1;
	arcs[29][30] = 1;

	arcs[31][32] = 1;
	arcs[32][33] = 1;
	arcs[33][49] = 1;
	arcs[34][35] = 1;
	arcs[35][49] = 1;
	for (int i = 36; i < 40; i++)
	{
		int m = i + 1;
		arcs[i][m] = 1;
	}
	arcs[40][53] = 1;
	arcs[41][42] = 1;
	arcs[42][43] = 1;
	arcs[43][54] = 1;
	arcs[44][45] = 1;
	arcs[45][52] = 1;
	arcs[46][47] = 1;
	arcs[47][48] = 1;
	arcs[48][31] = 1;
	arcs[31][48] = 1;
	arcs[49][36] = 1;
	arcs[50][8] = 1;
	arcs[50][21] = 1;
	arcs[51][27] = 1;
	arcs[51][12] = 1;
	arcs[52][15] = 1;
	arcs[52][46] = 1;
	arcs[53][17] = 1;
	arcs[53][41] = 1;
	arcs[54][29] = 1;
	arcs[54][44] = 1;

	for (int i = 0; i < 55; i++)
	{
		for (int j = 54; j > i; j--)
		{
			arcs[j][i] = arcs[i][j];
		}
	}
	arcs[49][3] = 1;
	arcs[49][36] = 1;
	arcs[3][49] = 1;
	arcs[36][49] = 1;
	arcs[50][8] = 1;
	arcs[50][21] = 1;
	arcs[8][50] = 1;
	arcs[21][50] = 1;
	arcs[51][27] = 1;
	arcs[51][12] = 1;
	arcs[27][51] = 1;
	arcs[12][51] = 1;
	arcs[52][46] = 1;
	arcs[52][15] = 1;
	arcs[46][52] = 1;
	arcs[15][52] = 1;
	arcs[53][17] = 1;
	arcs[53][41] = 1;
	arcs[17][53] = 1;
	arcs[41][53] = 1;
	arcs[54][44] = 1;
	arcs[54][29] = 1;
	arcs[44][54] = 1;
	arcs[29][54] = 1;
	int A[55][55];
	
	int i, j, k, n = 55;
	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
		{
			A[i][j] = arcs[i][j];
			
		}
	for (k = 0; k<n; k++)
	{
		for (i = 0; i<n; i++)
			for (j = 0; j<n; j++)
				if (A[i][j]>(A[i][k] + A[k][j]))
				{
					A[i][j] = A[i][k] + A[k][j];
					
				}
	}
	
	cout << "Floyd��������Ҫ�����ĳ�վ����Ϊ��" << A[v1][v2] + 1 << endl;
	return 0;
}
//void Input()
//{
//	cout << "��������㣺�����ߺͼ���վ��A 11ע��ո�" << endl;
//	cin >> a >> v;
//	if (a != "A"&&a != "B"&&a != "C"&&a != "T")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//
//	if ((v<1 || v>18) && a == "C")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	if ((v<1 || v>15) && a == "B")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	if ((v<1 || v>16) && a == "A")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	if ((v<1 || v>6) && a == "T")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	cout << "�������յ㣺�����ߺͼ���վ��B 12ע��ո�" << endl;
//	cin >> b >> v3;
//	if (b != "A"&&b != "B"&&b != "C"&&b != "T")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	if ((v3<1 || v3>18) && b == "C")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	if ((v3<1 || v3>15) && b == "B")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	if ((v3<1 || v3>16) && b == "A")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	if ((v3<1 || v3>6) && b == "T")
//	{
//		cout << "��վ�����ڣ�����" << endl;
//		Again2();
//	}
//	if (a == "A")
//		v1 = v - 1;
//	if (a == "B")
//		v1 = 15 + v;
//	if (a == "C")
//		v1 = 30 + v;
//	if (a == "T")
//		v1 = 48 + v;
//	if (b == "A")
//		v2 = v3 - 1;
//	if (b == "B")
//		v2 = 15 + v3;
//	if (b == "C")
//		v2 = 30 + v3;
//	if (b == "T")
//		v2 = 48 + v3;
//}