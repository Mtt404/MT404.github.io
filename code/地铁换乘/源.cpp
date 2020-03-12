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
	cout << " 请选择Dijkstra还是Floyd算法，输入1--Dijkstra，输入0--Floyd" << endl;
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
	cout << "Dijkstra法：" << endl;
	int v, v1, v2, v3;
	string a, b;
	cout << "请输入起点：几号线和几号站如A 11注意空格" << endl;
	cin >> a >> v;
	if (a != "A"&&a != "B"&&a != "C"&&a != "T")
	{
		cout << "此站不存在，请检查" << endl;
		Again1();
		return 0;
	}

	if ((v<1 || v>18) && a == "C")
	{
		cout << "此站不存在，请检查" << endl;
		Again1();
		return 0;
	}
	if ((v<1 || v>15) && a == "B")
	{
		cout << "此站不存在，请检查" << endl;
		Again1();
		return 0;
	}
	if ((v<1 || v>16) && a == "A")
	{
		cout << "此站不存在，请检查" << endl;
		Again1();
		return 0;
	}
	if ((v<1 || v>6) && a == "T")
	{
		cout << "此站不存在，请检查" << endl;
		Again1();
		return 0;
	}
	cout << "请输入终点：几号线和几号站如B 12注意空格" << endl;
	cin >> b>>v3;
	if (b != "A"&&b != "B"&&b != "C"&&b != "T")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>18) && b == "C")
	{
		cout << "此站不存在，请检查" << endl;
		Again1();
		return 0;
	}
	if ((v3<1 || v3>15) && b == "B")
	{
		cout << "此站不存在，请检查" << endl;
		Again1();
		return 0;
	}
	if ((v3<1 || v3>16) && b == "A")
	{
		cout << "此站不存在，请检查" << endl;
		Again1();
		return 0;
	}
	if ((v3<1 || v3>6) && b == "T")
	{
		cout << "此站不存在，请检查" << endl;
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
	
	int arcs[55][55];//图的邻接矩
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
	arcs[2][49] = 1
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
	bool S[55];   //记录从源点V0到终点Vi是否已经确定为最短路径，确定了记true，否则记false
	//int Path[55]; //记录从源点V0到终点Vi的当前最短路径上终点Vi的直接前驱顶点序号，若V0到Vi之间有边前驱为V0否则为-1 
	int D[55];  //记录源点到终点之间最短路径的长度，存在记V1到Vi的边的权值，否则记为1000       
	int n = 55;//顶点数
	for (int v = 0; v < n; v++)//n个顶点依次初始化
	{
		S[v] = false;//S初始化为空集
		D[v] = arcs[v1][v];//将v1到各个终点的最短路径长度初始化为边上的权值
		//if (D[v] < 1000)
			//Path[v] = v1;//如果v1和v之间有边，则将v的前驱初始化为v1
		
			//Path[v] = -1;//如果v0和v之间无边，则将v的前驱初始化为-1
	}
	S[v1] = true; //将v1加入s
	D[v1] = 0;//源点到源点的权值为0
			  //---------初始化结束，开始主循环，每次求得v0到某个顶点的最短路径，将v加到S数组
	for (int i = 1; i < n; i++)//依次对其余n-1个顶点进行计算
	{
		int min = 1000;
		int v = v1;
		for (int w = 0; w < n; w++)
		{
			if (!S[w] && D[w] < min)
			{//选择一条当前最短路径，终点为v
				v = w;
				min = D[w];
			}
			S[v] = true;//将v加到s集合中
			for (int w = 0; w < n; w++)
			{//更新从v0出发到集合V-S上所有顶点的最短路径长度
				if (!S[w] && (D[v] + arcs[v][w] < D[w]))
				{
					D[w] = D[v] + arcs[v][w];//更新D[w]
					
				}
			}
		}
	}
	cout << "Dijkstra法最少需要经过的车站数量为：" << D[v2]+1 << "站" << endl;
	
	return 0;
	/*Again();*/
}
void Again1()
{
	cout << "Again?(输入1=是，输入0=否)" << endl;
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
	cout << "Again?(输入1=是，输入0=否)" << endl;
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
	cout << "Floyd法：" << endl;
	int v, v1, v2, v3;
	string a, b;
	cout << "请输入起点：几号线和几号站如A 11注意空格" << endl;
	cin >> a >> v;
	if (a != "A"&&a != "B"&&a != "C"&&a != "T")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}

	if ((v<1 || v>18) && a == "C")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	if ((v<1 || v>15) && a == "B")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	if ((v<1 || v>16) && a == "A")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	if ((v<1 || v>6) && a == "T")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	cout << "请输入终点：几号线和几号站如B 12注意空格" << endl;
	cin >> b >> v3;
	if (b != "A"&&b != "B"&&b != "C"&&b != "T")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>18) && b == "C")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>15) && b == "B")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>16) && b == "A")
	{
		cout << "此站不存在，请检查" << endl;
		Again2();
		return 0;
	}
	if ((v3<1 || v3>6) && b == "T")
	{
		cout << "此站不存在，请检查" << endl;
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

	int arcs[55][55];//图的邻接矩阵

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
	
	cout << "Floyd法最少需要经过的车站数量为：" << A[v1][v2] + 1 << endl;
	return 0;
	
}
