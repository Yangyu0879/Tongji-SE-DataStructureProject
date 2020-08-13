#include <iostream>
#include <time.h>
using namespace std;

class Heap//堆
{
public:
	Heap(int size);//构造
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
		cerr << "内存分配失败" << endl;
		exit(1);
	}
	currentSize = 0;
}

Heap::Heap(int* A, int size, long long& swap_times)
{
	heap = new int[size];
	if (heap == NULL) {
		cerr << "内存分配失败" << endl;
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

//比较相邻的元素。如果第一个比第二个大，就交换他们两个。
//对每一对相邻元素做同样的工作，从开始第一对到结尾的最后一对。
//在这一点，最后的元素应该会是最大的数。针对所有的元素重复以上的步骤，除了最后一个。
//持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
void BubbleSort(int* B, int n, long long& compare_times) //冒泡排序,依次交换如冒泡
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
//第一次从R[0]~R[n - 1]中选取最小值，与R[0]交换，第二次从R[1]~R[n - 1]中选取最小值，与R[1]交换，....，
//第i次从R[i - 1]~R[n - 1]中选取最小值，与R[i - 1]交换，.....，
//第n - 1次从R[n - 2]~R[n - 1]中选取最小值，与R[n - 2]交换，
//总共通过n - 1次，得到一个按排序码从小到大排列的有序序列。
void SelectSort(int* B, int n, long long& swap_times) //选择排序，直接选择最小的
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
//当插入第i(i >= 1)时，前面的R[0]，R[1]，……，R[i - 1]已经排好序。
//这时，R[i]的排序码与R[i - 1]，r[i - 2]，…的排序码顺序进行比较，找到插入位置即将R[i]插入，
//原来位置上的元素向后顺移。


void InsertSort(int* B, int n, long long& swap_times) //插入排序，直接插入
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

//先取一个小于n的整数d1作为第一个增量，
//把文件的全部记录分组。所有距离为d1的倍数的记录放在同一个组中。
//先在各组内进行直接插入排序；然后，取第二个增量d2<d1重复上述的分组和排序，
//直至所取的增量 =1( < …<d2<d1)，即所有记录放在同一组中进行直接插入排序为止。

void ShellSort(int* B, int n, long long& swap_times)//希尔排序，gap=gap/3
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

//首先设定一个分界值，通过该分界值将数组分成左右两部分。
//将大于或等于分界值的数据集中到数组右边，小于分界值的数据集中到数组的左边。
//此时，左边部分中各元素都小于或等于分界值，而右边部分中各元素都大于或等于分界值。
//然后，左边和右边的数据可以独立排序。对于左侧的数组数据，又可以取一个分界值，
//将该部分数据分成左右两部分，同样在左边放置较小值，右边放置较大值。
//右侧的数组数据也可以做类似处理。重复上述过程，可以看出，这是一个递归定义。
//通过递归将左侧部分排好序后，再递归排好右侧部分的顺序。当左、右两个部分各数据排序完成后，
//整个数组的排序也就完成了。

void QuickSort(int* B, const int left, const int right, long long& swap_times) //快速排序，分治划分
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

//利用堆的插入，移除，进行排序。
void HeapSort(int* B, int size, long long& swap_times)//堆排序，运用堆结构
{
	Heap maxHeap = Heap(B, size, swap_times);
	for (int i = size - 1; i > 0; i--)
	{
		maxHeap.Swap(0, i);
		swap_times++;
		maxHeap.siftDown(0, i - 1, swap_times);
	}
}
//将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，
//再使子序列段间有序。若将两个有序表合并成一个有序表，称为二路归并。
void Merge(int* L1, int* L2, const int left, const int mid, const int right, long long& compare_times) //归并，二路
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


void MergeSort(int* L1, int* L2, int left, int right, long long& compare_times) //归并排序
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		MergeSort(L1, L2, left, mid, compare_times);
		MergeSort(L1, L2, mid + 1, right, compare_times);
		Merge(L1, L2, left, mid, right, compare_times);
	}
}

//设置若干个桶，依次扫描待排序的记录R[0]，R[1]，…，R[n-1]，
//把关键字在某个范围内的记录全都装入到第k个桶里(分配)，
//然后按序号依次将各非空的桶首尾连接起来(收集)。

void LSDSort(int* B, int size, long long& swap_times)//LSD基数排序
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
//首先建立输出的表格，随后依据输入内容，使用switch，分别进行相应的函数调用。
int main()
{
	cout << "**" << "               " << "排序算法比较" << "               " << "**" << endl;
	cout << "==============================================" << endl;
	cout << "**" << "              " << "1 --- 冒泡排序" << "              " << "**" << endl;
	cout << "**" << "              " << "2 --- 选择排序" << "              " << "**" << endl;
	cout << "**" << "              " << "3 --- 直接插入排序" << "          " << "**" << endl;
	cout << "**" << "              " << "4 --- 希尔排序" << "              " << "**" << endl;
	cout << "**" << "              " << "5 --- 快速排序" << "              " << "**" << endl;
	cout << "**" << "              " << "6 --- 堆排序" << "                " << "**" << endl;
	cout << "**" << "              " << "7 --- 归并排序" << "              " << "**" << endl;
	cout << "**" << "              " << "8 --- 基数排序" << "              " << "**" << endl;
	cout << "==============================================" << endl;
	long num;
	cout << "请输入要产生随机数的个数: ";
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
	start = clock();//分别用各种排序方法进行测试
	BubbleSort(B, num, swap_times);
	stop = clock();
	cout << "冒泡排序所用时间：" << (stop - start) << "ms" << endl;
	cout << "冒泡排序交换次数：" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	SelectSort(B, num, swap_times);
	stop = clock();
	cout << "选择排序所用时间：" << (stop - start) << "ms" << endl;
	cout << "选择排序交换次数：" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	InsertSort(B, num, swap_times);
	stop = clock();
	cout << "直接插入排序所用时间：" << (stop - start) << "ms" << endl;
	cout << "直接插入排序交换次数：" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	ShellSort(B, num, swap_times);
	stop = clock();
	cout << "希尔排序所用时间：" << (stop - start) << "ms" << endl;
	cout << "希尔排序交换次数：" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	QuickSort(B, 0, num - 1, swap_times);
	stop = clock();
	cout << "快速排序所用时间：" << (stop - start) << "ms" << endl;
	cout << "快速排序交换次数：" << swap_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	HeapSort(B, num, swap_times);
	stop = clock();
	cout << "堆排序所用时间：" << (stop - start) << "ms" << endl;
	cout << "堆排序交换次数：" << swap_times << endl;
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
	cout << "归并排序所用时间：" << (stop - start) << "ms" << endl;
	cout << "归并排序比较次数：" << compare_times << endl;
	for (int i = 0; i < num; i++) {
		B[i] = A[i];
	}
	swap_times = 0;
	start = clock();
	LSDSort(B, num, compare_times);
	stop = clock();
	cout << "基数排序所用时间：" << (stop - start) << "ms" << endl;
	cout << "基数排序交换次数：" << swap_times << endl;
	delete[]A;
	delete[]B;
	delete[]C;
	return 0;
}