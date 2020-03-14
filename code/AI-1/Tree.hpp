#ifndef _Tree_HPP_
#define _Tree_HPP_

#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include<queue>

//////////////////////////////////////////////////////////////////////
// NOTE: 
//	for the template class, we need to put all the implementation
//	in one file
//
//	Yangang Wang, 2014/08/27, @MSRA
//
//  Modified on 2019/10/1, @SEU
//

#define SAFE_DELETE(p) \
		{\
			if(p) {\
				delete p; \
				p = nullptr;\
			}\
		}

// search method
enum searchMethod
{
	DFS = 0,
	BFS,
	UCS
};

//////////////////////////////////////////////////////////////////////
// tree node
//
template <class T = float>
struct treeNode
{
	treeNode() : m_ptrParent(nullptr) { ; };

	// data 
	// class T should have constructor and operator =
	std::vector<T>		m_data;

	// name of the node
	std::string			m_nodeName;

	// ref index for the node
	int					m_nodeIndex;

	// pointer
	treeNode*				m_ptrParent;
	std::vector<treeNode*>	m_ptrChildren;
};

//////////////////////////////////////////////////////////////////////
// tree structure :: base class
//
template <class T = float>
class  Tree
{
protected:
	typedef treeNode<T> node;

public:
	Tree() : m_ptrRoot(nullptr), m_seMeth(DFS){ ; };
	Tree(const Tree& tree);

	// overload operator =
	virtual Tree& operator=(const Tree& tree);

	virtual ~Tree() 
	{ 
		destroy(m_ptrRoot); 
	};

public:
	// insert Node
	void insert(node* const ptrNode, node* const ptrParent = nullptr);

	// change the search method
	void changeSeachMethod(searchMethod seMeth = DFS) { m_seMeth = seMeth; };

	// get the number of node
	const int	getNodeNum() const;

	// get the number of endsite node
	const int	getEndSiteNodeNum() const;

	// get the node pointer according to the nodeIndex
	node* const getNodePointer(const int nodeIndex);

	// get the node pointer according to the nodeName
	node* const getNodePointer(const char* nodeName);

	// get the node pointer closet to the given data point
	node* const getClosetNodePointer(T* ptrData, const int dataDimension);

	// get the root node pointer
	node* const getRootPointer() const { return m_ptrRoot; };

private:
	void destroy(node* ptr) {
		if (ptr == nullptr) return;
		for (int i = 0; i < (int)ptr->m_ptrChildren.size(); i++)
			destroy(ptr->m_ptrChildren[i]);
		SAFE_DELETE(ptr);
	}

private:
	node* m_ptrRoot;
	searchMethod m_seMeth;
};

//////////////////////////////////////////////////////////////////////
// implementation
//
template<class T>
Tree<T>::Tree(const Tree<T>& tree)
{
	destroy(this->m_ptrRoot);

	// copy the data
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		m_ptrRoot= tree.m_ptrRoot;	
		m_seMeth = DFS;
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	case BFS:
	default:
	{
		// ==============================
		m_ptrRoot = tree.m_ptrRoot;
		m_seMeth = BFS;
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	}
}

template<class T>
Tree<T>& Tree<T>::operator=(const Tree<T>& tree)
{
	destroy(this->m_ptrRoot);

	// copy the data
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		m_ptrRoot = tree.m_ptrRoot;
		m_seMeth = DFS;
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	case BFS:
	default:
	{
		// ==============================
		// fill the code here
		m_ptrRoot = tree.m_ptrRoot;
		m_seMeth = BFS;
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	}

	return *this;
}

template<class T>
void Tree<T>::insert(node* const ptrNode, node* const ptrParent /* = nullptr */)
{
	if (m_ptrRoot != nullptr&&ptrParent == nullptr) {
		std::string errMsg = "Tree<T>::insert_ptrNode: Can not insert node, only one root for the tree structure!";
		throw std::exception(errMsg.c_str());
	}
	else if (m_ptrRoot == nullptr&&ptrParent == nullptr)
		m_ptrRoot = ptrNode;
	else
	{
		ptrParent->m_ptrChildren.push_back(ptrNode);
		
	}
		


	ptrNode->m_ptrParent = ptrParent;
}

template<class T>
typename Tree<T>::node* const Tree<T>::getNodePointer(const int nodeIndex)
{
	if (nodeIndex == -1)
		return nullptr;

	node* ptrNode = nullptr;

	// search the node
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int  it;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		stack<node*> S;
	    S.push(ptrNode);
		while (!S.empty())
		{
			ptrNode = S.top();
			S.pop();

			if (visited[ptrNode->m_nodeIndex]==0)
			{
				// process node
				if (ptrNode->m_nodeIndex == nodeIndex)
				{
					break;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			
			for (it=0;it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					S.push(ptrNode1);
				}
			}
		}
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	case BFS:
	default:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int  it;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		queue<node*> Q;
		Q.push(ptrNode);
		while (!Q.empty())
		{
			ptrNode = Q.front();
			Q.pop();
			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				if (ptrNode->m_nodeIndex == nodeIndex)
				{
					break;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
			    Q.push(ptrNode1);
			}
		}
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	}

	return ptrNode;
}

template<class T>
typename Tree<T>::node* const Tree<T>::getNodePointer(const char* nodeName)
{
	if (strlen(nodeName) == 0) 
		return nullptr;

	node* ptrNode = nullptr;

	// search the node
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int  it;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		stack<node*> S;
		S.push(ptrNode);
		while (!S.empty())
		{
			ptrNode = S.top();
			S.pop();

			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				if (ptrNode->m_nodeName == nodeName)
				{
					break;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					S.push(ptrNode1);
				}
			}
		}
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	case BFS:
	default:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int  it;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		queue<node*> Q;
		Q.push(ptrNode);
		while (!Q.empty())
		{
			ptrNode = Q.front();
			Q.pop();
			if (!visited[ptrNode->m_nodeIndex])
			{
				if (ptrNode->m_nodeName == nodeName)
				{
					break;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					Q.push(ptrNode1);
				}
			}
		}
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	}

	return ptrNode;
}

template<class T>
typename Tree<T>::node* const Tree<T>::getClosetNodePointer(T* ptrData, const int dataDimension)
{
	if (ptrData == nullptr)
		return nullptr;

	node* ptrNode = nullptr;

	// search the node closet to the ptrData
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int  it;
		float distance=100;
		node* ptrNode2;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		stack<node*> S;
		S.push(ptrNode);
		while (!S.empty())
		{
			ptrNode = S.top();
			S.pop();

			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				float distance1 = powf(ptrNode->m_data[0] - ptrData[0], 2) + powf(ptrNode->m_data[1] - ptrData[1], 2) + powf(ptrNode->m_data[2] - ptrData[2], 2);
				if (distance1 < distance)
				{
					distance=distance1;
					ptrNode2 = ptrNode;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					S.push(ptrNode1);
				}
			}
		}
		ptrNode = ptrNode2;		
		//return ptrNode;
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	case BFS:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int  it;
		float distance = 100;
		node* ptrNode2;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		queue<node*> Q;
		Q.push(ptrNode);
		while (!Q.empty())
		{
			ptrNode = Q.front();
			Q.pop();
			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				float distance1 = powf(ptrNode->m_data[0] - ptrData[0], 2) + powf(ptrNode->m_data[1] - ptrData[1], 2) + powf(ptrNode->m_data[2] - ptrData[2], 2);
				if (distance1 < distance)
				{
					distance = distance1;
					ptrNode2 = ptrNode;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					Q.push(ptrNode1);
				}
			}
		}
		ptrNode = ptrNode2;
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	case UCS:
	default:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int follow[50] = { 0 };
		int  it;
		int i=0;//脚标
		int j = 0;//确定层数
		float distance = 100;
		node* ptrNode2;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		queue<node*> Q;
		Q.push(ptrNode);
		while (!Q.empty())
		{
			ptrNode = Q.front();
			Q.pop();
			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				float distance1 = powf(ptrNode->m_data[0] - ptrData[0], 2) + powf(ptrNode->m_data[1] - ptrData[1], 2) + powf(ptrNode->m_data[2] - ptrData[2], 2);
				if (distance1 < distance)
				{
					follow[i] = ptrNode->m_nodeIndex;
					i++;
					distance = distance1;
					ptrNode2 = ptrNode;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					// process node
					float distance1 = powf(ptrNode1->m_data[0] - ptrData[0], 2) + powf(ptrNode1->m_data[1] - ptrData[1], 2) + powf(ptrNode1->m_data[2] - ptrData[2], 2);
					if (distance1 < distance)
					{
						distance = distance1;
						ptrNode2 = ptrNode1;
					}
					visited[ptrNode1->m_nodeIndex] = 1;
					Q.push(ptrNode1);
				}
			}
			follow[i] = (int)ptrNode2->m_nodeIndex;
			i++;
		}
		for (int m = 0; m < i; m++)
		{
			if (follow[m] == ptrNode2->m_nodeIndex)
			{
				j = m;
				break;
			}
		}
		cout << "cost最小路径：";
		for (int m = 0; m <= j; m++)
		{
			cout << follow[m]<<" ";
		}
		cout << endl;
		ptrNode = ptrNode2;
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	}

	return ptrNode;
}

template<class T>
const int Tree<T>::getNodeNum() const
{
	if (m_ptrRoot == nullptr) 
		return 0;

	int nodeNum = 0;
	// search the tree
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		int visited[50] = { 0 };
		int  it;
		node* ptrNode = nullptr;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		stack<node*> S;
		S.push(ptrNode);
		while (!S.empty())
		{
			ptrNode = S.top();
			S.pop();

			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				nodeNum++;
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					S.push(ptrNode1);
				}
			}
		}

		
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	case BFS:
	default:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int  it;
		node* ptrNode = nullptr;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		queue<node*> Q;
		Q.push(ptrNode);
		while (!Q.empty())
		{
			ptrNode = Q.front();
			Q.pop();
			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				nodeNum++;
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					Q.push(ptrNode1);
				}
			}
		}

		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	}

	return nodeNum;
}

template<class T>
const int Tree<T>::getEndSiteNodeNum() const
{
	if (m_ptrRoot == nullptr)
		return 0;

	int endSiteNodeNum = 0;

	// search the tree
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		int visited[50] = { 0 };
		int  it;
		node* ptrNode = nullptr;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		stack<node*> S;
		S.push(ptrNode);
		while (!S.empty())
		{
			ptrNode = S.top();
			S.pop();

			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				if (ptrNode->m_ptrChildren.size() == 0)
				{
					endSiteNodeNum++;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					S.push(ptrNode1);
				}
			}
		}

		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	case BFS:
	default:
	{
		// ==============================
		// fill the code here
		int visited[21] = { 0 };
		int  it;
		node* ptrNode = nullptr;
		if (ptrNode == nullptr)
		{
			ptrNode = m_ptrRoot;
		}
		queue<node*> Q;
		Q.push(ptrNode);
		while (!Q.empty())
		{
			ptrNode = Q.front();
			Q.pop();
			if (visited[ptrNode->m_nodeIndex] == 0)
			{
				// process node
				if (ptrNode->m_ptrChildren.size() == 0)
				{
					endSiteNodeNum++;
				}
				visited[ptrNode->m_nodeIndex] = 1;
			}
			for (it = 0; it <(int)ptrNode->m_ptrChildren.size(); it++)
			{
				node* ptrNode1 = ptrNode->m_ptrChildren[it];
				if (!visited[ptrNode1->m_nodeIndex])
				{
					Q.push(ptrNode1);
				}
			}
		}
		// ==============================
		//
		// Yangang Wang, 2019/10/1, @SEU
		//
	}
	break;
	}

	return endSiteNodeNum;
}

#endif