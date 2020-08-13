#include<iostream>
using namespace std;

class SeqQueue
{
public:
	SeqQueue(int sz = 1000);//���캯��
	~SeqQueue() { delete[] elements; };//�����������ͷſռ�
	bool EnQueue(const int& x);//��Ӳ���
	int DeQueue();//���Ӳ���
	bool isEmpty()const { return(front == rear) ? true : false; };//�ж϶����Ƿ�Ϊ��
	bool isFull()const { return((rear + 1) % maxSize == front) ? true : false; };//�ж϶����Ƿ�Ϊ��
private:
	int rear, front;//ͷָ�룬βָ��
	int* elements;
	int maxSize;//��󳤶�
};
//���캯��������һ��Ĭ�ϳ���Ϊ100������ռ䣬�Դ�Ŷ������ݣ�����ͷβָ��Ĭ��Ϊ�㡣

SeqQueue::SeqQueue(int sz) :front(0), rear(0), maxSize(sz)
{
	elements = new int[maxSize];
}
//��Ӻ������ܵĲ���ΪҪ��ӵ�Ԫ�ء��ж϶����Ƿ���������������������ʧ�ܡ�
//�����βԪ����Ϊ��������β��һģ���Ԫ�ظ�����
bool SeqQueue::EnQueue(const int& x)//��Ӳ���
{
	if (isFull() == true)//���Ϊ��
		return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}
//���Ӻ����������κβ������ж϶����Ƿ��ѿգ�����ѿգ���ɾ��ʧ�ܡ�
//���غ���Ϊͷ�ڵ㣬ͷ�ڵ��1ģ���Ԫ�ظ�����
int SeqQueue::DeQueue()//���Ӳ���
{
	int x;
	if (isEmpty() == true)//���Ϊ��
		return false;
	x = elements[front];
	front = (front + 1) % maxSize;
	return x;
}
//����������������a��b����������ҵ��Ĺ˿���������ż�ֱ��������ջ֮�С�
//Ȼ�󣬰���a��ջ������b��ջһ����˳�򣬳�ջ����ĳ��ջΪ��ʱ�������һ��ջ�����ݡ�
int main()
{
	int n, k,x;
	SeqQueue a, b;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> k;
		if (k % 2 == 1)//����
		{
			a.EnQueue(k);
		}
		else
		{
			b.EnQueue(k);
		}
	}
	while (!a.isEmpty() && !b.isEmpty())//���ν������
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
	while (!a.isEmpty())//��ʣ������
	{
		cout << a.DeQueue() << " ";
	}
	while (!b.isEmpty())
	{
		cout << b.DeQueue() << " ";
	}
	return 0;
}
