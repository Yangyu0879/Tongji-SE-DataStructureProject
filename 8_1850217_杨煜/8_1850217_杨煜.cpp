#include<iostream>
using namespace std;

template<class T, class E>
struct MSTEdgeNode //边节点
{
	int tail, head;
	E key;
	MSTEdgeNode() : tail(-1), head(-1), key(0) {}
	bool operator<= (MSTEdgeNode<T, E>& R) { return key <= R.key; }//重载运算符
	bool operator> (MSTEdgeNode<T, E>& R) { return key > R.key; }
};

template<class T, class E>
class MinSpanTree//最小生成树类
{
public:
	MSTEdgeNode<T, E>* edgevalue;//边结点
	MinSpanTree(int sz = 50 - 1) : maxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode<T, E>[sz];
	}
	bool InsertNode(MSTEdgeNode<T, E>& node)//插入边结点
	{
		if (n == maxSize)//判满
		{
			cerr << "The MinSpanTree is full" << endl;
			return false;
		}
		else
		{
			edgevalue[n] = node;
			n++;
			return true;
		}
	}
protected:
	int maxSize, n;
};


template<class T, class E>
struct Edge
{
	int dest;//指向的顶点
	E cost;//权值
	Edge<T, E>* link;
	Edge() {}
	Edge(T num, E weight)
	{
		dest = num;
		cost = weight;
		link = NULL;
	}
	bool operator!= (Edge<T, E>& R) const
	{
		return (dest != R.dest) ? true : false;
	}
};



template<class T, class E>
struct Vertex
{
	T data;//数据
	Edge<T, E>* adj;//边
};


template<class T, class E>
class Graphlnk
{
public:
	Graphlnk(int sz = 50);//构造函数
	~Graphlnk();//析构函数
	T getValue(int i) //获取权值
	{
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : '0';
	}
	E getWeight(int v1, int v2);//两个节点间的权值
	int getFirstNeighbor(int v);//第一个相邻的顶点
	int getNextNeighbor(int v, int w);//下一个相邻的顶点
	bool addVertexes(int& numCount);//加入节点
	void addEdges();//加入边
	int getnumVertices()//获取节点个数
	{
		return numVertices;
	}
	int getnumEdges()//获取边个数
	{
		return numEdges;
	}
	int getVertexPos(const T vertex)//查找节点位置
	{
		for (int i = 0; i < numVertices; i++)
		{
			if (NodeTable[i].data == vertex)
			{
				return i;
			}
		}
		return -1;
	}
private:
	bool insertEdge(int v1, int v2, E cost);//插入边
	Vertex<T, E>* NodeTable;//图的链表
	int numVertices;//节点个数
	int maxVertices;//最大节点个数
	int numEdges; //边个数
};


//构造函数构造函数接受一个参数，依次开辟节点空间，将每个节点的邻接的指针置为NULL。
template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)
{
	maxVertices = sz;
	numEdges = 0;
	numVertices = 0;
	NodeTable = new Vertex<T, E>[maxVertices];//开辟空间
	for (int i = 0; i < maxVertices; i++)
	{
		NodeTable[i].adj = NULL;//置空
	}
}

//析构函数将节点的所用邻接关系一一清除，最后删去这个存放顶点的数组空间
template<class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
	for (int i = 0; i < numVertices; i++)
	{
		Edge<T, E>* p = NodeTable[i].adj;
		while (p != NULL)//清除链表
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;//删去节点数组
}
//获取输入顶点的首个邻接顶点。如果没有则返回-1。
template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
	if (v != -1) {
		Edge<T, E>* p = NodeTable[v].adj;
		if (p != NULL)
			return p->dest;
	}
	return -1;
}
//接受两个参数，找到当前顶点v的，在w之后的一个顶点。
template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) //获取相邻的下一节点
{
	if (v != -1)
	{
		Edge<T, E>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w)
		{
			p = p->link;
		}
		if (p != NULL && p->link != NULL)
		{
			return p->link->dest;
		}
	}
	return -1;
}

template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)//获取两条边间的权重
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL) {
			return p->cost;
		}
	}
	return 0;
}

//插入一个顶点
template<class T, class E>
bool Graphlnk<T, E>::addVertexes(int& numCount)//添加节点
{
	cout << "请输入顶点的个数：";
	int n;
	cin >> n;
	numCount = n;
	cout << "请输入各个顶点的名称：";
	while (n > 0) {
		char name;
		cin >> name;
		if (numVertices == maxVertices)//如果已满
		{
			return false;
		}
		else
		{
			NodeTable[numVertices].data = name;
			numVertices++;
		}
		n--;
	}
}
//读入所需要插入的边，直到接收到末尾标识符。找到要插入边的节点，随后进行插入边的操作。
template<class T, class E>
void Graphlnk<T, E>::addEdges() //添加边
{
	int loop = 1;
	while (loop)
	{
		cout << "请输入两个顶点及边：";
		char v1, v2;
		int weight;
		cin >> v1 >> v2 >> weight;
		if (v1 == '?' || v2 == '?') //判断终止
		{
			loop = 0;
			break;
		}
		int v1_pos = getVertexPos(v1);
		int v2_pos = getVertexPos(v2);
		if (!insertEdge(v1_pos, v2_pos, weight)) //插入失败
		{
			cerr << "顶点创建失败，请检查后重新输入" << endl;
		}
	}
}

template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)//插入边
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		Edge<T, E>* q;
		Edge<T, E>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)//寻找节点
		{
			p = p->link;
		}
		if (p != NULL)
		{
			return false;
		}
		p = new Edge<T, E>;//两节点间插入边
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return 0;
}


template<class T, class E>//堆结构
class Heap
{
public:
	Heap(int size = DefaultVerticesNum);
	~Heap() { delete[]heap; }
	bool Insert(const MSTEdgeNode<T, E>& x);
	bool Remove(MSTEdgeNode<T, E>& item);
	void siftDown(int start, int end);
	void siftUp(int start);
private:
	MSTEdgeNode<T, E>* heap;
	int currentSize;
	int maxSize;
};

template<class T, class E>
Heap<T, E>::Heap(int size)//构造
{
	if (50 < size)
	{
		maxSize = size;
	}
	else {
		maxSize = 50;
	}
	heap = new MSTEdgeNode<T, E>[maxSize];
	currentSize = 0;
}


template<class T, class E>
void Heap<T, E>::siftDown(int start, int end)//向下调整
{
	MSTEdgeNode<T, E> temp = heap[start];
	int i = start;
	int j = 2 * i + 1;
	while (j <= end)
	{
		if (heap[j] > heap[j + 1] && j < end)
			j++;
		if (temp <= heap[j])
			break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

template<class T, class E>
void Heap<T, E>::siftUp(int start) //向上调整
{
	MSTEdgeNode<T, E> temp = heap[start];
	int j = start;
	int i = (j - 1) / 2;
	while (j > 0)
	{
		if (heap[i] <= temp)
			break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template<class T, class E>
bool Heap<T, E>::Insert(const MSTEdgeNode<T, E>& item)//插入
{
	if (currentSize == maxSize)
	{
		cerr << "The heap is full" << endl;
		return false;
	}
	heap[currentSize] = item;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template<class T, class E>
bool Heap<T, E>::Remove(MSTEdgeNode<T, E>& item) //移除
{

	if (currentSize == 0)
	{
		cout << "The heap is empty" << endl;
		return false;
	}
	item = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}
////将顶点分为两个不重叠的部分。每一轮的迭代中，找到当前割的桥，挑选出其中的最小值。
//随后将顶点加入到生成树的顶点集合之中，不断重复即可得到最小生成树。
template<class T, class E>
void Prim(const T u0, Graphlnk<T, E>& G, MinSpanTree<T, E>& MST) //prim算法的实现，将顶点集合划分为两个，选择跨两个集合的边的最小值，堆优化
{
	MSTEdgeNode<T, E> ed;
	int i, u, v, count;
	int n = G.getnumVertices();
	int m = G.getnumEdges();
	u = G.getVertexPos(u0);
	Heap<T, E> H(m);
	bool* Vmst = new bool[n];//标记数组
	for (int i = 0; i < n; i++)
	{
		Vmst[i] = false;
	}
	Vmst[u] = true;
	count = 1;
	while (count < n) //计数直到n
	{
		v = G.getFirstNeighbor(u);//获取相邻的第一个节点
		while (v != -1)
		{
			if (Vmst[v] == false)
			{
				ed.head = v;
				ed.tail = u;
				ed.key = G.getWeight(u, v);//获取权重
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (!(H.isEmpty()) && count < n) //判空和计数
		{
			H.Remove(ed);
			if (Vmst[ed.head] == false)
			{
				MST.InsertNode(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	}
}

int numVertices = 0;

template<class T, class E>
void Display(Graphlnk<T, E>& G, MinSpanTree<T, E>& MST)
{
	for (int i = 0; i < numVertices - 1; i++)
	{
		char head = G.getValue(MST.edgevalue[i].tail);
		char tail = G.getValue(MST.edgevalue[i].head);
		cout << head << "-<" << MST.edgevalue[i].key << ">->" << tail;
		if (i != numVertices - 2)
		{
			cout << "	";
		}
	}
}

//首先建立表格，随后通过操作码，switch分支，进行相应的操作。

int main()
{
	Graphlnk<char, int> G;//创建实例
	MinSpanTree<char, int> MST;
	string op;
	int loop = 1;
	int flag = 0;
	cout << "**" << "          " << "电网造价模拟系统" << "          " << "**" << endl;//制表
	cout << "========================================" << endl;
	cout << "**" << "         " << "A --- 创建电网顶点" << "         " << "**" << endl;
	cout << "**" << "         " << "B --- 添加电网的边" << "         " << "**" << endl;
	cout << "**" << "         " << "C --- 构造最小生成树" << "       " << "**" << endl;
	cout << "**" << "         " << "D --- 显示最小生成树" << "       " << "**" << endl;
	cout << "**" << "         " << "E --- 退出程序" << "             " << "**" << endl;
	cout << "========================================" << endl;
	while (loop) //主循环
	{
		cout << endl << "请选择操作：";
		cin >> op;
		switch (op[0])
		{
		case 'A':
			if (flag == 1)
			{
				cerr << "已有电网存在，不要重复创建" << endl;
			}
			else
			{
				G.addVertexes(numVertices);
				flag = 1;
			}
			break;
		case 'B':
			if (flag != 1)
			{
				cout << "请先创建电网" << endl;
			}
			else
			{
				G.addEdges();
			}
			break;
		case 'C':
			if (flag != 1)
			{
				cout << "请先创建电网" << endl;
				break;
			}
			cout << "请输入起始顶点：";
			char begin;
			cin >> begin;
			Prim(begin, G, MST);
			cout << "生成Prim最小生成树!" << endl;
			break;
		case 'D':
		{
			if (flag != 1)
			{
				cout << "请先创建电网" << endl;
				break;
			}
			cout << "最小生成树的顶点及边分别为：" << endl;
			Display(G, MST);
			break;
		}
		case 'E':
			loop = 0;
			break;
		default:
			cout << "选项不存在，请重新输入" << endl;
			break;
		}
	}
}