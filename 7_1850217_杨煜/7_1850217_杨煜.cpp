#include<iostream>
using namespace std;

template<class E>
class Heap
{
public:
	Heap(int sz = 100000);//构造函数
	~Heap() { delete[]heap; }//析构函数
	bool Insert(const E& x);//插入
	E Remove();//移除节点
	bool IsEmpty()const//判空
	{
		return(currentSize == 0) ? true : false;
	}
	bool IsFull()const//判满
	{
		return(currentSize == maxSize) ? true : false;
	}
	int getSize()const { return currentSize; }//返回堆大小
private:
	E* heap;//指向堆的指针
	int currentSize;//当前大小
	int maxSize;//最大大小
	void siftDown(int start, int m);//向下滑动调整
	void siftUp(int start);//向上滑动调整。
};
//构造函数构造函数接受一个默认的参数100000，
//开辟数组空间，当前的堆的大小置为0，构造函数依此完成。
template<class E>
Heap<E>::Heap(int sz)//构造函数
{
	maxSize = (100000 < sz) ? sz : 100000;
	heap = new E[maxSize];
	currentSize = 0;
}
//下滑调整函数接受调整位置和终点的参数。置j为i的子节点如果j小于m，
//同时j大于j+1则调整至其兄弟节点。
//将i的内容向下调整，直到到达m或者i所在内容小于j所在的内容。
template<class E>
void Heap<E>::siftDown(int start, int m)//向下调整函数
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]>heap[j + 1])//判断子节点
		{
			j++;
		}
		if (temp <= heap[j])
			break;
		else
		{
			heap[i] = heap[j];//交换位置
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}
//向上调整函数接受调整位置参数。
//置j为i的子节点如果j大于0，则进行调整，将i中的内容向上调整，
//直到到达根节点或者i所在内容小于j所在的内容
template<class E>
void Heap<E>::siftUp(int start)//向上调整
{
	int j = start, i = (j - 1) / 2;
	E temp = heap[j];
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
	heap[j] = temp;//交换位置
}
//插入函数接受的参数为所要插入的内容，在当前的下一个位置处插入，最后从这个位置开始向上调整。
template<class E>
bool Heap<E>::Insert(const E& x)//插入
{
	heap[currentSize] = x;
	siftUp(currentSize);//向上调整
	currentSize++;
	return true;
}
//将堆栈的根节点输出并使用最后一个子节点来代替。同时进行从0开始到最后位置的向下调整。
template<class E>
E Heap<E>::Remove()//移除
{
	E x = heap[0];
	heap[0] = heap[--currentSize];
	siftDown(0, currentSize - 1);//向下调整
	return x;
}
//首先申明一个最小堆，将读入的数字存放入堆中，
//从堆中读出两个数将其相加之后在放入，最后便可以得出最小值。
int main()
{
	Heap<int> pque;
	int n, k;
	int flag = 0;
	int ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> k;
		if (k < 0)
		{
			flag = 1;
		}
		pque.Insert(k);//读入内容
	}
	if (flag == 0)
	{
		if (n == 1)
		{
			cout << pque.Remove();
		}
		else
		{
			while (pque.getSize() > 1)//将内容出列直到剩一个
			{
				int a, b;
				a = pque.Remove();//出列两个元素相加
				b = pque.Remove();
				ans += a + b;
				pque.Insert(a + b);
			}
			cout << ans;
		}
	}
	else
	{
		cout << "错误，长度不能为负";
	}
}