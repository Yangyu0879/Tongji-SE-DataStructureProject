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
	SeqQueue(int sz = 1000);//���캯��
	~SeqQueue() { delete[] elements; };//�����������ͷſռ�
	bool EnQueue(const Course& x);//��Ӳ���
	Course DeQueue();//���Ӳ���
	bool isEmpty()const { return(front == rear) ? true : false; };//�ж϶����Ƿ�Ϊ��
	bool isFull()const { return((rear + 1) % maxSize == front) ? true : false; };//�ж϶����Ƿ�Ϊ��
private:
	int rear, front;//ͷָ�룬βָ��
	Course* elements;
	int maxSize;//��󳤶�
};


SeqQueue::SeqQueue(int sz) :front(0), rear(0), maxSize(sz)//����
{
	elements = new Course[maxSize];
}

bool SeqQueue::EnQueue(const Course& x)//���
{
	if (isFull() == true)
		return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}

Course SeqQueue::DeQueue()//����
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
//����Ϊ�γ̵�txt�ļ���
//���ж�ȡ����Ҫ�ſε����ݣ��ж��ſ������Ƿ���ǰ��Ҫ�����ֱ���뵽Course����֮�С�
bool input()//��ȡ�ļ�
{
	ifstream fin("�γ�.txt",ios::in);
	if (!fin) { 
		cout << "error opening source file." << endl;
		return 0;
	}
	fin >> A[i].id >> A[i].name;
	while (!fin.eof())//�����ļ��ַ���
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
//�ú�������Ӧ�Ĳ�������Ϊ���ÿγ̵Ŀ�ʱ��Ϊ3����������ֻ��Ҫ����һ�Ρ������ܵ����������ֱ�Ϊ����Ҫ�������ݵ�ѭ����ʼѧ���Լ���ȡ�Ŀγ̡�
//ͨ��ѭ�����ҵ��α�֮��Ϊ��ĵط�����ʾ��λ���ڴ˲���ÿγ̶ԵĿγ̴��š�
void insert1(int a, Course b)//�ſ��㷨
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
//�ú�������Ӧ�Ĳ�������Ϊ���ÿγ̵Ŀ�ʱ��Ϊ4��5��6�������
//�����Ҫ�����������ݡ������ܵ����������ֱ�Ϊ����Ҫ�������ݵ�ѭ����ʼѧ���Լ���ȡ�Ŀγ̣�
//����λ���ֱ��ǵ�һ�β���Ŀγ�λ�ã��ڶ��β���Ŀγ�λ�ã��Լ����β���ʱ������Ŀ�ʱ������
//ͨ��ѭ�����ҵ��α�֮��Ϊ��ĵط�����ʾ��λ���ڴ˲���ÿγ̶ԵĿγ̴��š�
void insert2(int a, Course b, int m1, int m2, int p1, int p2)//�ſ��㷨
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
				if (sem[k][m][n] == 0 && (m == m2 || m == m2 + 5) && flag == 1 && abs(n - q) >= 2)//���������
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
					else//���������������֮��
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
//��亯����ִ�еĹ���Ϊ���ݿ�ʱ�������ݣ��ֱ���ò�ͬ�Ĳ��뺯����
void blank(int a,char f,Course b)//���α�
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
//����8���ļ�����sem����֮�д洢�Ŀγ���Ϣ��
//ת��Ϊ�γ����ַ��뵽�α�֮�У����α���뵽txt�ļ�֮�С�
void output()//������ļ�
{
	ofstream fout;
	for (int i = 0; i < 8; i++)
	{
		string str = "��" + to_string(i + 1) + "ѧ��.txt";//�����˸��ļ�
		fout.open(str);
		fout <<setw(17)<<" "<< "��һ" << setw(30) << " " << "�ܶ�" << setw(30) << " " << "����" << setw(30) << " " << "����" << setw(30) << " " << "����" << setw(30) << " " << endl;
		for (int m = 0; m < 10; m++)
		{
			fout << m;
			for (int n = 0; n < 5; n++)//����ļ�
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
//����һ�����У�������Ԫ�ز�Ϊ��ʱ��ѭ����ʹ��һ��������������¼�γ��Ƿ��ѱ����룬��������룬��¼�����������ѧ�ڡ�
//���û���������·�������У�����һ�����ƹ���������ص��뷨��
int main()
{
	int x, y;
	input();
	int sum = 0;
	int u = 0;
	cout << "����ÿѧ�ڿγ���" << endl;
	for (int h = 0; h < 8; h++)//���ܿγ���
	{
		cin >> arr[h];
		sum += arr[h];
		
	}
	if (sum != i)
	{
		cout << "�γ���������";
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
			cout << "�ÿγ������޷����ɿα�";
			exit(1);
		}
		Course b = course.DeQueue();
		if (b.premise.size() == 1)//�б����޿γ�
		{
			blank(0, b.span[0], b);
			
		}
		else
		{
			if (b.premise.size() == 3)//�б����޿γ�
			{
				x = isused[(b.premise[1] - 48) * 10 + (b.premise[2] - 48) - 1];
				if (x != 0)
				{
					blank(x, b.span[0], b);
				
				}
				else//������޿�δ��
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