#include<iostream>
using namespace std;

template<class E>
class Heap
{
public:
	Heap(int sz = 100000);//���캯��
	~Heap() { delete[]heap; }//��������
	bool Insert(const E& x);//����
	E Remove();//�Ƴ��ڵ�
	bool IsEmpty()const//�п�
	{
		return(currentSize == 0) ? true : false;
	}
	bool IsFull()const//����
	{
		return(currentSize == maxSize) ? true : false;
	}
	int getSize()const { return currentSize; }//���ضѴ�С
private:
	E* heap;//ָ��ѵ�ָ��
	int currentSize;//��ǰ��С
	int maxSize;//����С
	void siftDown(int start, int m);//���»�������
	void siftUp(int start);//���ϻ���������
};
//���캯�����캯������һ��Ĭ�ϵĲ���100000��
//��������ռ䣬��ǰ�ĶѵĴ�С��Ϊ0�����캯��������ɡ�
template<class E>
Heap<E>::Heap(int sz)//���캯��
{
	maxSize = (100000 < sz) ? sz : 100000;
	heap = new E[maxSize];
	currentSize = 0;
}
//�»������������ܵ���λ�ú��յ�Ĳ�������jΪi���ӽڵ����jС��m��
//ͬʱj����j+1����������ֵܽڵ㡣
//��i���������µ�����ֱ������m����i��������С��j���ڵ����ݡ�
template<class E>
void Heap<E>::siftDown(int start, int m)//���µ�������
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]>heap[j + 1])//�ж��ӽڵ�
		{
			j++;
		}
		if (temp <= heap[j])
			break;
		else
		{
			heap[i] = heap[j];//����λ��
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}
//���ϵ����������ܵ���λ�ò�����
//��jΪi���ӽڵ����j����0������е�������i�е��������ϵ�����
//ֱ��������ڵ����i��������С��j���ڵ�����
template<class E>
void Heap<E>::siftUp(int start)//���ϵ���
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
	heap[j] = temp;//����λ��
}
//���뺯�����ܵĲ���Ϊ��Ҫ��������ݣ��ڵ�ǰ����һ��λ�ô����룬�������λ�ÿ�ʼ���ϵ�����
template<class E>
bool Heap<E>::Insert(const E& x)//����
{
	heap[currentSize] = x;
	siftUp(currentSize);//���ϵ���
	currentSize++;
	return true;
}
//����ջ�ĸ��ڵ������ʹ�����һ���ӽڵ������档ͬʱ���д�0��ʼ�����λ�õ����µ�����
template<class E>
E Heap<E>::Remove()//�Ƴ�
{
	E x = heap[0];
	heap[0] = heap[--currentSize];
	siftDown(0, currentSize - 1);//���µ���
	return x;
}
//��������һ����С�ѣ�����������ִ������У�
//�Ӷ��ж����������������֮���ڷ��룬������Եó���Сֵ��
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
		pque.Insert(k);//��������
	}
	if (flag == 0)
	{
		if (n == 1)
		{
			cout << pque.Remove();
		}
		else
		{
			while (pque.getSize() > 1)//�����ݳ���ֱ��ʣһ��
			{
				int a, b;
				a = pque.Remove();//��������Ԫ�����
				b = pque.Remove();
				ans += a + b;
				pque.Insert(a + b);
			}
			cout << ans;
		}
	}
	else
	{
		cout << "���󣬳��Ȳ���Ϊ��";
	}
}