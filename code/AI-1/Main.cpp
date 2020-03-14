#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Tree.hpp"

using namespace std;

void printInform(treeNode<>* ptrNode, const int nodeDataDim)
{
	printf("node Index: %d ", ptrNode->m_nodeIndex);
	printf("node Data:");
	for (int i = 0; i < nodeDataDim; i++) {
		printf("%.3f ", ptrNode->m_data[i]);
	}
	printf("\n");
}

void main(int argc, char** argv)
{
	// This is the code for testing the search Tree in
	//
	//  'The first project homework for Artifical Intelligence'
	// 
	// Yangang Wang, 2019/10/1, @SEU
	//

	// initialize the search tree
	Tree<>* ptrTree = new Tree<>();
	

	// read the search tree data
	ifstream infile("joint.txt");
	string line;
	const int nodeDataDim = 3;
	if (infile.is_open()) {
		while (getline(infile, line)) {
			treeNode<>* ptrNode = new treeNode<>();

			// read the data
			stringstream ss(line);
			ss >> ptrNode->m_nodeName;
			ss >> ptrNode->m_nodeIndex;
			ptrNode->m_data.assign(nodeDataDim, 0);
			for (int i = 0; i < nodeDataDim; i++) {
				ss >> ptrNode->m_data[i];
			}
			int parentIndex = -1;
			ss >> parentIndex;
			if (parentIndex < 0) ptrTree->insert(ptrNode);
			else {
				treeNode<>* ptrParent = ptrTree->getNodePointer(parentIndex);
				ptrTree->insert(ptrNode, ptrParent);
			}
		}
		infile.close();
	}

	// Test the method
	float dataPoint[3] = { 0, 0, 0.5 };
	treeNode<>* ptrNode = nullptr;

	// change the search method
	cout << "BFS������"<<endl;
	ptrTree->changeSeachMethod(searchMethod::BFS);
	ptrNode = ptrTree->getNodePointer("joint15");
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getNodePointer(10);
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getClosetNodePointer(dataPoint, nodeDataDim);
	printInform(ptrNode, nodeDataDim);
	cout << "�ܽڵ�����"<<ptrTree->getNodeNum() << endl;
	cout << "��Ե�ڵ�����" << ptrTree->getEndSiteNodeNum() << endl;

	// change the search method
	cout << "DFS������" << endl;
	ptrTree->changeSeachMethod(searchMethod::DFS);
	Tree<>* ptrTree1(ptrTree);
	cout<< "��������:"<<ptrTree1->getNodeNum()<<endl;
	Tree<>* ptrTree2=ptrTree;
	cout<< "���������:"<<ptrTree2->getNodeNum()<<endl;
	ptrNode = ptrTree->getNodePointer("joint15");
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getNodePointer(10);
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getClosetNodePointer(dataPoint, nodeDataDim);
	printInform(ptrNode, nodeDataDim);
	cout << "�ܽڵ�����" << ptrTree->getNodeNum() << endl;
	cout << "��Ե�ڵ�����" << ptrTree->getEndSiteNodeNum() << endl;

	// change the search method
	cout << "UCS������" << endl;
	ptrTree->changeSeachMethod(searchMethod::UCS);
	//ptrNode = ptrTree->getNodePointer("joint15");
	//printInform(ptrNode, nodeDataDim);
	//ptrNode = ptrTree->getNodePointer(10);
	//printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getClosetNodePointer(dataPoint, nodeDataDim);
	printInform(ptrNode, nodeDataDim);
	
	// delete the tree
	delete ptrTree;
	system("pause");
}