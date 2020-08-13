#include<iostream>
using namespace std;

class SeqQueue
{
public:
	SeqQueue(int sz = 1000);//构造函数
	~SeqQueue() { delete[] elements; };//析构函数，释放空间
	bool EnQueue(const int& x);//入队操作
	int DeQueue();//出队操作
	bool isEmpty()const { return(front == rear) ? true : false; };//判断队列是否为空
	bool isFull()const { return((rear + 1) % maxSize == front) ? true : false; };//判断队列是否为满
private:
	int rear, front;//头指针，尾指针
	int* elements;
	int maxSize;//最大长度
};
//构造函数开辟了一个默认长度为100的数组空间，以存放队列数据，其余头尾指针默认为零。

SeqQueue::SeqQueue(int sz) :front(0), rear(0), maxSize(sz)
{
	elements = new int[maxSize];
}
//入队函数接受的参数为要入队的元素。判断队列是否已满，如果已满，则插入失败。
//否则队尾元素置为参数，队尾加一模最大元素个数。
bool SeqQueue::EnQueue(const int& x)//入队操作
{
	if (isFull() == true)//如果为满
		return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}
//出队函数不接受任何参数。判断队列是否已空，如果已空，则删除失败。
//返回函数为头节点，头节点加1模最大元素个数。
int SeqQueue::DeQueue()//出队操作
{
	int x;
	if (isEmpty() == true)//如果为空
		return false;
	x = elements[front];
	front = (front + 1) % maxSize;
	return x;
}
//首先申明两个队列a，b。输入银行业务的顾客数，按奇偶分别进入两个栈之中。
//然后，按照a出栈两个，b出栈一个的顺序，出栈。当某个栈为空时，输出另一个栈的内容。
int main()
{
	int n, k,x;
	SeqQueue a, b;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> k;
		if (k % 2 == 1)//输入
		{
			a.EnQueue(k);
		}
		else
		{
			b.EnQueue(k);
		}
	}
	while (!a.isEmpty() && !b.isEmpty())//依次交替出队
	{
		x = a.DeQueue();
		if (x)
		{
			cout << x << " ";
		}
		x = a.DeQueue();
		if (x)
		{
			cout << x << " ";
		}
		x = b.DeQueue();
		if (x)
		{
			cout << x << " ";
		}
	}
	while (!a.isEmpty())//将剩余的输出
	{
		cout << a.DeQueue() << " ";
	}
	while (!b.isEmpty())
	{
		cout << b.DeQueue() << " ";
	}
	return 0;
}
