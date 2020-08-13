#include<iostream>
using namespace std;

class List;

class LinkNode
{
	friend class List;//������Ԫ
private:
	int number;//�ڵ�������
	LinkNode* link;//�ڵ����һ��Ԫ��
};


class List
{
public:
	List();//���캯��
	~List();//��������
	bool Construction();//��������
	void Union(List& a, List& b);//�󽻼�����
	void Display();//���
	LinkNode* Gethead();//ȡͷ�ڵ�
private:
	LinkNode* first;//����ͷ�ڵ�
};
//���캯��������һ���յ�ͷ�ڵ���ڽڵ�ĵ�һ��λ��ʹ�������Ϊ��һ����
//������ͷ��������������в��ң������һϵ�еĲ�����ʹ�ó�����Ӽ�ࡣ
List::List()
{
	first = new LinkNode;
}

List::~List()
{

}
//�����������ݴ����ǽ�������У��յ������
//�����������ֵ������һ�������ֵ����ͷĬ��Ϊ0���Ҳ��Ƿ�������ʱ��
//����һ���ڵ�ռ䣬����������������֮�С�����ֹͣ���벢����������Ϣ��
//�����������Ϊ-1ʱ������Ϊ���������������
//���������ɹ�ʱ�����0���ɹ�ʱ���1��
bool List::Construction()
{
	LinkNode* newNode;
	LinkNode* last;
	last = first;
	int n, k = 0;
	cin >> n;
	while (n != -1)
	{
		if (k > n&& k >= 0)//�����ж�
		{
			cout << "��������" << endl;
			return 0;
		}
		k = n;
		newNode = new LinkNode;//�����½ڵ�
		last->link = newNode;
		last = newNode;
		newNode->number = n;
		cin >> n;
	}
	last->link = nullptr;
	return 1;
}
//��������ֵΪ����ͷ�ڵ����һ���ڵ��ַ��
LinkNode* List::Gethead()
{
	return this->first->link;
}
//��Ϊ���Ĺ��ܣ����������Ĳ���Ϊ������������ĵ�ַ��
//���ȣ�ͨ�����û�ȡͷ�ڵ�ĺ����õ���������ͷ�ڵ�ĵ�һ���ڵ�ĵ�ַ������������������������Ҫ������һ��������
//���ʼ�ȽϽڵ㣬�����������û��Ϊ�սڵ㣬��Ƚ����ڵ����ݣ������ȣ���Ѹ�������������������У������������Ƚ��������ݴ�С��
//���a�������ݴ���b����ָ����һ�ڵ㣬��֮��Ȼ��ֱ��������������һ��Ϊ�ա�
void List::Union(List& a, List& b)
{
	LinkNode* current1 = a.Gethead();
	LinkNode* current2 = b.Gethead();
	LinkNode* current3 = first;
	LinkNode* newNode;
	while (current1 != nullptr && current2 != nullptr)
	{
		if (current1->number == current2->number)//������
		{
			newNode = new LinkNode;
			newNode->number = current1->number;
			current3->link = newNode;
			current3 = newNode;
			current1 = current1->link;
			current2 = current2->link;
		}
		else if (current1->number < current2->number)//A��
		{
			current1 = current1->link;
		}
		else if (current1->number > current2->number)//B��
		{
			current2 = current2->link;
		}
	}
	current3->link = nullptr;//ĩβ�����
}

//�ӵ�һ���ڵ㿪ʼ����������ݣ��������Ϊ�գ������NULL����������������ݡ�
void List::Display()
{
	LinkNode* current = this->Gethead();
	if (current == nullptr)//Ϊ�����
	{
		cout << "NULL";
	}
	else//��Ϊ�գ��������
	{
		while (current != nullptr)
		{
			cout << current->number << " ";
			current = current->link;
		}
	}
}
//����������������a,b,c��Ȼ�󹹽�a��b������������ɹ������ȡ�����ĺ��������c�����ݣ��������������Ϣ������ó���
int main()
{
	List a, b, c;
	if (a.Construction() && b.Construction())//�ж��Ƿ�ɹ�����
	{
		c.Union(a, b);
		c.Display();
	}
}