#include<iostream>
#include <fstream>
#include<string>
#include<iomanip>
using namespace std;

struct Course
{
	string id;
	string name;
	string span;
	string semester;
	string premise;
};

class SeqQueue
{
public:
	SeqQueue(int sz = 1000);//构造函数
	~SeqQueue() { delete[] elements; };//析构函数，释放空间
	bool EnQueue(const Course& x);//入队操作
	Course DeQueue();//出队操作
	bool isEmpty()const { return(front == rear) ? true : false; };//判断队列是否为空
	bool isFull()const { return((rear + 1) % maxSize == front) ? true : false; };//判断队列是否为满
private:
	int rear, front;//头指针，尾指针
	Course* elements;
	int maxSize;//最大长度
};


SeqQueue::SeqQueue(int sz) :front(0), rear(0), maxSize(sz)//构造
{
	elements = new Course[maxSize];
}

bool SeqQueue::EnQueue(const Course& x)//入队
{
	if (isFull() == true)
		return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}

Course SeqQueue::DeQueue()//出队
{
	Course x;
	x = elements[front];
	front = (front + 1) % maxSize;
	return x;
}


Course A[100];
int isused[100] = {};
int sem[8][10][5] = {};
int i = 0;
int arr[8];
//打开名为课程的txt文件，
//从中读取出所要排课的内容，判断排课内容是否有前置要求，随后分别存入到Course数组之中。
bool input()//读取文件
{
	ifstream fin("课程.txt",ios::in);
	if (!fin) { 
		cout << "error opening source file." << endl;
		return 0;
	}
	fin >> A[i].id >> A[i].name;
	while (!fin.eof())//处理文件字符串
	{
		fin  >> A[i].span >> A[i].semester;
		fin >> A[i].premise;
		fin >> A[i + 1].id;
		if (A[i + 1].id[0] != 'c')
		{
			A[i+1].name = A[i + 1].id;
			A[i + 1].id = A[i].premise;
			A[i].premise = '\0';
		}
		else
		{
			fin >> A[i + 1].name;
		}
		i++;
	}
}
//该函数所对应的插入内容为，该课程的课时数为3的情况，因此只需要插入一次。所接受的两个参数分别为，所要插入内容的循环开始学期以及读取的课程。
//通过循环，找到课表之上为零的地方，表示空位，在此插入该课程对的课程代号。
void insert1(int a, Course b)//排课算法
{
	int flag = 0;
	for (int k = a; k < 8; k++)
	{
		for (int n = 0; n < 5; n++)
		{
			for (int m = 0; m < 10; m++)
			{
				if (sem[k][m][n] == 0 && (m == 2 || m == 7)&&arr[k]!=0)
				{
					for (int p = 0; p < 3; p++)
					{
						sem[k][m + p][n] = (b.id[1] - 48) * 10 + (b.id[2] - 48);
						isused[(b.id[1] - 48) * 10 + (b.id[2] - 48) - 1] = k + 1;
					}
					arr[k]--;
					flag = 1;
				}
				if (flag == 1)
				{
					break;
				}
			}
			if (flag == 1)
			{
				break;
			}
		}
		if (flag == 1)
		{
			break;
		}
	}
}
//该函数所对应的插入内容为，该课程的课时数为4，5，6的情况，
//因此需要插入两次内容。所接受的六个参数分别为，所要插入内容的循环开始学期以及读取的课程，
//后四位，分别是第一次插入的课程位置，第二次插入的课程位置，以及两次插入时所插入的课时个数。
//通过循环，找到课表之上为零的地方，表示空位，在此插入该课程对的课程代号。
void insert2(int a, Course b, int m1, int m2, int p1, int p2)//排课算法
{
	int flag = 0;
	int r = 0;
	int q = 0;
	for (int k = a; k < 8; k++)
	{
		for (int n = 0; n < 5; n++)
		{
			for (int m = 0; m < 10; m++)
			{
				if (sem[k][m][n] == 0 && (m == m1 || m == m1 + 5) && flag == 0&& arr[k] != 0)
				{
					for (int p = 0; p < p1; p++)
					{
						sem[k][m + p][n] = (b.id[1] - 48) * 10 + (b.id[2] - 48);
						isused[(b.id[1] - 48) * 10 + (b.id[2] - 48) - 1] = k + 1;
					}
					q = n;
					r = m;
					flag++;
				}
				if (sem[k][m][n] == 0 && (m == m2 || m == m2 + 5) && flag == 1 && abs(n - q) >= 2)//必须空两天
				{
					if (isused[(b.id[1] - 48) * 10 + (b.id[2] - 48) - 1] == k + 1)
					{
						for (int p = 0; p < p2; p++)
						{
							sem[k][m + p][n] = (b.id[1] - 48) * 10 + (b.id[2] - 48);
							isused[(b.id[1] - 48) * 10 + (b.id[2] - 48) - 1] = k + 1;
						}
						flag++;
						arr[k]--;
					}
					else//如果被分在了两天之中
					{
						for (int p = 0; p < p1; p++)
						{
							sem[isused[(b.id[1] - 48) * 10 + (b.id[2] - 48) - 1] - 1][r + p][q] = 0;
						}
						isused[(b.id[1] - 48) * 10 + (b.id[2] - 48) - 1] = 0;
						flag--;
						continue;
					}

				}
				if (flag == 2)
				{
					break;
				}
			}
			if (flag == 2)
			{
				break;
			}
		}
		if (flag == 2)
		{
			break;
		}
	}
}
//填充函数所执行的功能为根据课时数的内容，分别调用不同的插入函数。
void blank(int a,char f,Course b)//填充课表
{
	switch (f)
	{
	case '3':
		insert1(a, b);
		break;
	case '4':
		insert2(a, b, 0, 0, 2, 2);
		break;
	case '5':
		insert2(a, b, 2, 0, 3, 2);
		break;
	case '6':
		insert2(a, b, 2, 2, 3, 3);
		break;
	default:
		break;
	}
}
//创建8个文件，将sem数组之中存储的课程信息，
//转化为课程名字放入到课表之中，将课表放入到txt文件之中。
void output()//输出到文件
{
	ofstream fout;
	for (int i = 0; i < 8; i++)
	{
		string str = "第" + to_string(i + 1) + "学期.txt";//创建八个文件
		fout.open(str);
		fout <<setw(17)<<" "<< "周一" << setw(30) << " " << "周二" << setw(30) << " " << "周三" << setw(30) << " " << "周四" << setw(30) << " " << "周五" << setw(30) << " " << endl;
		for (int m = 0; m < 10; m++)
		{
			fout << m;
			for (int n = 0; n < 5; n++)//填充文件
			{
				if (sem[i][m][n] != 0)
				{
					fout << setw(15) << " " << A[sem[i][m][n]-1].name << setw(16 - A[sem[i][m][n]-1].name.size()) << " ";
				}
				else
				{
					fout <<setw(36)<<" ";
				}
			}
			fout << endl;
		}
		fout.close();
	}
}
//创建一个队列，当队列元素不为零时，循环，使用一个辅助数组来记录课程是否已被填入，如果被填入，记录下数组填入的学期。
//如果没有则将其重新放入队列中，这是一个类似广度优先搜素的想法。
int main()
{
	int x, y;
	input();
	int sum = 0;
	int u = 0;
	cout << "输入每学期课程数" << endl;
	for (int h = 0; h < 8; h++)//接受课程数
	{
		cin >> arr[h];
		sum += arr[h];
		
	}
	if (sum != i)
	{
		cout << "课程数不符合";
		exit(1);
	}
	SeqQueue course;
	for (int k = 0; k < i ;k++)
	{
		if (A[k].semester[0]-48 >= 1 && A[k].semester[0]-48 <= 8)
		{
			blank(A[k].semester[0] - 49, A[k].span[0],A[k]);
		}
		else
		{
			course.EnQueue(A[k]);
		}
	}
	while (!course.isEmpty())
	{
		u++;
		if (u >= 500)
		{
			cout << "该课程序列无法构成课表";
			exit(1);
		}
		Course b = course.DeQueue();
		if (b.premise.size() == 1)//判别先修课程
		{
			blank(0, b.span[0], b);
			
		}
		else
		{
			if (b.premise.size() == 3)//判别先修课程
			{
				x = isused[(b.premise[1] - 48) * 10 + (b.premise[2] - 48) - 1];
				if (x != 0)
				{
					blank(x, b.span[0], b);
				
				}
				else//如果先修课未修
				{
					course.EnQueue(b);
					continue;
				}
			}
			else if (b.premise.size() == 6)
			{
				x = isused[(b.premise[1] - 48) * 10 + (b.premise[2] - 48) - 1];
				y = isused[(b.premise[4] - 48) * 10 + (b.premise[5] - 48) - 1];
				if (x != 0 && y != 0)
				{
					blank(x > y ? x:y , b.span[0], b);
				}
				else
				{
				course.EnQueue(b);
				continue;
				}
			}
		}
	}
	output();
	for (int m = 0; m < 8; m++)
	{
		for (int n = 0; n < 10; n++)
		{
			for (int j = 0; j < 5; j++)
			{
				cout << sem[m][n][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}