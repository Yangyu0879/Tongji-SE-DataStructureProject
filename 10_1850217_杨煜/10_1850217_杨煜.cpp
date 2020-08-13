#include <iostream>
#include <time.h>
using namespace std;

class Heap//��
{
public:
	Heap(int size);//����
	Heap(int* A, int size, long long& swap_times);
	~Heap() { delete[]heap; }
	void siftDown(int start, int end, long long& swap_times);
	void print();
	void Swap(int m, int n);
private:
	int* heap;
	int currentSize;
};

Heap::Heap(int size)
{
	heap = new int[size];
	if (heap == NULL) {
		cerr << "�ڴ����ʧ��" << endl;
		exit(1);
	}
	currentSize = 0;
}

Heap::Heap(int* A, int size, long long& swap_times)
{
	heap = new int[size];
	if (heap == NULL) {
		cerr << "�ڴ����ʧ��" << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		heap[i] = A[i];
	}
	currentSize = size;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0) {
		siftDown(currentPos, currentSize - 1, swap_times);
		currentPos--;
	}
}


void Heap::siftDown(int start, int end, long long& swap_times)
{
	int temp = heap[start];
	int i = start;
	int j = 2 * i + 1;
	while (j <= end) {
		swap_times++;
		if (heap[j] < heap[j + 1] && j < end)
			j++;
		swap_times++;
		if (temp >= heap[j])
			break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}


void Heap::Swap(int m, int n)
{
	int temp = heap[m];
	heap[m] = heap[n];
	heap[n] = temp;
}

void Heap::print()
{
	for (int i = 0; i < currentSize; i++)
	{
		cout << heap[i] << ' ';
	}
}

//�Ƚ����ڵ�Ԫ�ء������һ���ȵڶ����󣬾ͽ�������������
//��ÿһ������Ԫ����ͬ���Ĺ������ӿ�ʼ��һ�Ե���β�����һ�ԡ�
//����һ�㣬����Ԫ��Ӧ�û�����������������е�Ԫ���ظ����ϵĲ��裬�������һ����
//����ÿ�ζ�Խ��Խ�ٵ�Ԫ���ظ�����Ĳ��裬ֱ��û���κ�һ��������Ҫ�Ƚϡ�
void BubbleSort(int* B, int n, long long& compare_times) //ð������,���ν�����ð��
{
	int temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			compare_times++;
			if (B[j] > B[j + 1]) {
				temp = B[j];
				B[j] = B[j + 1];
				B[j + 1] = temp;
			}
		}
	}
}
//��һ�δ�R[0]~R[n - 1]��ѡȡ��Сֵ����R[0]�������ڶ��δ�R[1]~R[n - 1]��ѡȡ��Сֵ����R[1]������....��
//��i�δ�R[i - 1]~R[n - 1]��ѡȡ��Сֵ����R[i - 1]������.....��
//��n - 1�δ�R[n - 2]~R[n - 1]��ѡȡ��Сֵ����R[n - 2]������
//�ܹ�ͨ��n - 1�Σ��õ�һ�����������С�������е��������С�
void SelectSort(int* B, int n, long long& swap_times) //ѡ������ֱ��ѡ����С��
{
	for (int i = 0; i < n; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (B[j] < B[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(B[i], B[min]);
			swap_times++;
		}
	}
}
//�������i(i >= 1)ʱ��ǰ���R[0]��R[1]��������R[i - 1]�Ѿ��ź���
//��ʱ��R[i]����������R[i - 1]��r[i - 2]������������˳����бȽϣ��ҵ�����λ�ü���R[i]���룬
//ԭ��λ���ϵ�Ԫ�����˳�ơ�


void InsertSort(int* B, int n, long long& swap_times) //��������ֱ�Ӳ���
{
	int temp;
	for (int i = 1; i < n; i++)
	{
		if (B[i] < B[i - 1])
		{
			temp = B[i];
			int j = i - 1;
			do
			{
				B[j + 1] = B[j];
				swap_times++;
				j--;
			} while (j >= 0 && temp < B[j]);
			B[j + 1] = temp;
			swap_times++;
		}
	}
}

//��ȡһ��С��n������d1��Ϊ��һ��������
//���ļ���ȫ����¼���顣���о���Ϊd1�ı����ļ�¼����ͬһ�����С�
//���ڸ����ڽ���ֱ�Ӳ�������Ȼ��ȡ�ڶ�������d2<d1�ظ������ķ��������
//ֱ����ȡ������ =1( < ��<d2<d1)�������м�¼����ͬһ���н���ֱ�Ӳ�������Ϊֹ��

void ShellSort(int* B, int n, long long& swap_times)//ϣ������gap=gap/3
{
	int gap;
	for (gap = n / 2; gap > 1; gap = gap / 3 + 1)
	{
		for (int i = 0; i < gap; i++)
		{
			for (int j = i + gap; j < n; j = j + gap)
			{
				if (B[j] < B[j - gap])
				{
					int temp = B[j];
					int k = j - gap;
					while (k >= 0 && B[k] > temp)
					{
						B[k + gap] = B[k];
						swap_times++;
						k = k - gap;
					}
					B[k + gap] = temp;
					swap_times++;
				}
			}
		}
	}
}

//�����趨һ���ֽ�ֵ��ͨ���÷ֽ�ֵ������ֳ����������֡�
//�����ڻ���ڷֽ�ֵ�����ݼ��е������ұߣ�С�ڷֽ�ֵ�����ݼ��е��������ߡ�
//��ʱ����߲����и�Ԫ�ض�С�ڻ���ڷֽ�ֵ�����ұ߲����и�Ԫ�ض����ڻ���ڷֽ�ֵ��
//Ȼ����ߺ��ұߵ����ݿ��Զ������򡣶��������������ݣ��ֿ���ȡһ���ֽ�ֵ��
//���ò������ݷֳ����������֣�ͬ������߷��ý�Сֵ���ұ߷��ýϴ�ֵ��
//�Ҳ����������Ҳ���������ƴ����ظ��������̣����Կ���������һ���ݹ鶨�塣
//ͨ���ݹ齫��ಿ���ź�����ٵݹ��ź��Ҳಿ�ֵ�˳�򡣵������������ָ�����������ɺ�
//�������������Ҳ������ˡ�

void QuickSort(int* B, const int left, const int right, long long& swap_times) //�������򣬷��λ���
{

	if (left < right)
	{
		int pivotPos = left;
		int pivot = B[left];
		for (int i = left + 1; i <= right; i++)
		{
			swap_times++;
			if (B[i] < pivot)
			{
				pivotPos++;
				if (pivotPos != i)
				{
					swap(B[pivotPos], B[i]);

				}
			}
		}
		B[left] = B[pivotPos];
		B[pivotPos] = pivot;
		QuickSort(B, left, pivotPos - 1, swap_times);
		QuickSort(B, pivotPos + 1, right, swap_times);
	}
}

//���öѵĲ��룬�Ƴ�����������
void HeapSort(int* B, int size, long long& swap_times)//���������öѽṹ
{
	Heap maxHeap = Heap(B, size, swap_times);
	for (int i = size - 1; i > 0; i--)
	{
		maxHeap.Swap(0, i);
		swap_times++;
		maxHeap.siftDown(0, i - 1, swap_times);
	}
}
//��������������кϲ����õ���ȫ��������У�����ʹÿ������������
//��ʹ�����жμ������������������ϲ���һ���������Ϊ��·�鲢��
void Merge(int* L1, int* L2, const int left, const int mid, const int right, long long& compare_times) //�鲢����·
{
	for (int i = left; i <= right; i++)
	{
		L2[i] = L1[i];
	}
	int s1 = left;
	int s2 = mid + 1;
	int t = left;
	while (s1 <= mid && s2 <= right)
	{
		compare_times++;
		if (L2[s1] <= L2[s2])
		{
			L1[t++] = L2[s1++];
		}
		else
		{
			L1[t++] = L2[s2++];
		}
	}
	while (s1 <= mid)
	{
		compare_times++;
		L1[t++] = L2[s1++];
	}
	while (s2 <= right)
	{
		compare_times++;
		L1[t++] = L2[s2++];
	}
}


void MergeSort(int* L1, int* L2, int left, int right, long long& compare_times) //�鲢����
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		MergeSort(L1, L2, left, mid, compare_times);
		MergeSort(L1, L2, mid + 1, right, compare_times);
		Merge(L1, L2, left, mid, right, compare_times);
	}
}

//�������ɸ�Ͱ������ɨ�������ļ�¼R[0]��R[1]������R[n-1]��
//�ѹؼ�����ĳ����Χ�ڵļ�¼ȫ��װ�뵽��k��Ͱ��(����)��
//Ȼ��������ν����ǿյ�Ͱ��β��������(�ռ�)��

void LSDSort(int* B, int size, long long& swap_times)//LSD��������
{
	int d = 5;
	int* temp = new int[size];
	int count[10];
	int radix = 1;
	for (int i = 1; i <= d; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			count[j] = 0;
		}
		for (int j = 0; j < size; j++)
		{
			int k = (B[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++)
		{
			count[j] = count[j - 1] + count[j];
		}
		for (int j = size - 1; j >= 0; j--)
		{
			int k = (B[j] / radix) % 10;
			temp[count[k] - 1] = B[j];
			count[k]--;
		}
		for (int j = 0; j < size; j++)
		{
			B[j] = temp[j];
		}
		radix *= 10;
	}
}
//���Ƚ�������ı����������������ݣ�ʹ��switch���ֱ������Ӧ�ĺ������á�
int main()
{
	cout << "**" << "               " << "�����㷨�Ƚ�" << "               " << "**" << endl;
	cout << "==============================================" << endl;
	cout << "**" << "              " << "1 --- ð������" << "              " << "**" << endl;
	cout << "**" << "              " << "2 --- ѡ������" << "              " << "**" << endl;
	cout << "**" << "              " << "3 --- ֱ�Ӳ�������" << "          " << "**" << endl;
	cout << "**" << "              " << "4 --- ϣ������" << "              " << "**" << endl;
	cout << "**" << "              " << "5 --- ��������" << "              " << "**" << endl;
	cout << "**" << "              " << "6 --- ������" << "                " << "**" << endl;
	cout << "**" << "              " << "7 --- �鲢����" << "              " << "**" << endl;
	cout << "**" << "              " << "8 --- ��������" << "              " << "**" << endl;
	cout << "==============================================" << endl;
	long num;
	cout << "������Ҫ����������ĸ���: ";
	cin >> num;
	srand((unsigned)time(NULL));
	int* A = new int[num];
	int* B = new int[num];
	int* C = new int[num];
	for (int i = 0; i < num; i++)
	{
		int item = rand();
		A[i] = item;
	}
	long long swap_times, compare_times;
	long start, stop;
	for (int i = 0; i < num; i++)
	{
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();//�ֱ��ø������򷽷����в���
	BubbleSort(B, num, swap_times);
	stop = clock();
	cout << "ð����������ʱ�䣺" << (stop - start) << "ms" << endl;
	cout << "ð�����򽻻�������" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	SelectSort(B, num, swap_times);
	stop = clock();
	cout << "ѡ����������ʱ�䣺" << (stop - start) << "ms" << endl;
	cout << "ѡ�����򽻻�������" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	InsertSort(B, num, swap_times);
	stop = clock();
	cout << "ֱ�Ӳ�����������ʱ�䣺" << (stop - start) << "ms" << endl;
	cout << "ֱ�Ӳ������򽻻�������" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	ShellSort(B, num, swap_times);
	stop = clock();
	cout << "ϣ����������ʱ�䣺" << (stop - start) << "ms" << endl;
	cout << "ϣ�����򽻻�������" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	QuickSort(B, 0, num - 1, swap_times);
	stop = clock();
	cout << "������������ʱ�䣺" << (stop - start) << "ms" << endl;
	cout << "�������򽻻�������" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	HeapSort(B, num, swap_times);
	stop = clock();
	cout << "����������ʱ�䣺" << (stop - start) << "ms" << endl;
	cout << "�����򽻻�������" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	for (int i = 0; i < num; i++) {
		C[i] = A[i];
	}
	compare_times = 0;
	start = clock();
	MergeSort(B, C, 0, num - 1, compare_times);
	stop = clock();
	cout << "�鲢��������ʱ�䣺" << (stop - start) << "ms" << endl;
	cout << "�鲢����Ƚϴ�����" << compare_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	LSDSort(B, num, compare_times);
	stop = clock();
	cout << "������������ʱ�䣺" << (stop - start) << "ms" << endl;
	cout << "�������򽻻�������" << swap_times << endl;
	delete[]A;
	delete[]B;
	delete[]C;
	return 0;
}