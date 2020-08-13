#include<iostream>
#include<string>
using namespace std;

class List;

class LinkNode
{
	friend class List;//������ԪΪ������
private:
	int studentID;//��������
	string studentName;//����
	string studentGender;//�Ա�
	int studentAge;//����
	string studentCategory;//������Ŀ
	LinkNode* link;//ָ����һ�ڵ��ָ��
};

class List
{
public:
	List();//���캯��
	~List();//��������
	void Input(int studentNumber);//���빹������
	void Display()const;//���
	void Insert(int position);//����
	void Delete(int position);//ɾ��
	void Change(int ID);//�޸�
	void Find(int ID)const;//����
private:
	int listLength;//������
	LinkNode* first;//ͷ�ڵ�
};


List::List()
{
	first = new LinkNode;
}

List::~List() 
{
	LinkNode* q;
	while (first->link != nullptr)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	delete first;
}

void List::Input(int studentNumber)
{
	LinkNode* newNode, * last;//�����½ڵ��β���ָ��
	last = first;
	for (int i = 0; i < studentNumber; i++)//��������������������
	{
		newNode = new LinkNode;
		last->link = newNode;
		last = newNode;
		cin >> newNode->studentID >> newNode->studentName >> newNode->studentGender >> newNode->studentAge >> newNode->studentCategory;
	}
	listLength = studentNumber;
}

void List::Display() const
{
	LinkNode* current;
	current = first->link;
	cout <<"����"<< "    "
		<<"����"<< "    "
		<<"�Ա�"<< "    "
		<<"����"<< "    "
		<<"�������"<< "    "
		<< endl;
	while (current != nullptr)//�������
	{
		cout << current->studentID << "       "
			<< current->studentName << "    "
			<< current->studentGender << "       "
			<< current->studentAge << "    "
			<< current->studentCategory << "    "
			<< endl;
		current = current->link;
	}
}

void List::Find(int ID) const
{
	LinkNode* current = first->link;
	while (current != nullptr && current->studentID != ID)
	{
		current = current->link;
	}//���Ҳ����
	if (current != nullptr)
	{
		cout << current->studentID << "       "
			<< current->studentName << "    "
			<< current->studentGender << "       "
			<< current->studentAge << "    "
			<< current->studentCategory << "    "
			<< endl;
	}
	//�Ҳ���
	else
	{
		cout << "�ÿ����Ų�����" << endl;
	}
}


void List::Insert(int position)
{
	if (position > listLength + 1)//λ�ó���
	{
		cout << "��λ�ò�����" << endl;
		return;
	}
	LinkNode* current = first;
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա������Լ��������" << endl;
	LinkNode* newNode = new LinkNode;
	cin >> newNode->studentID >> newNode->studentName >> newNode->studentGender >> newNode->studentAge >> newNode->studentCategory;
	for (int i = 0; i < position - 1; i++)//Ѱ�Ҳ���λ��
	{
		current = current->link;
	}
	newNode->link = current->link;
	current->link = newNode;
	listLength++;
}


void List::Delete(int position)
{
	if (position > listLength)//λ�ò�����
	{
		cout << "��λ�ò�����" << endl;
		return;
	}
	LinkNode* current = first, * temp;
	for (int i = 0; i < position - 1; i++)//�ҵ�λ��
	{
		current = current->link;
	}
	//ɾ������
	temp = current->link;
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
	cout << temp->studentID << "       "
		<< temp->studentName << "    "
		<< temp->studentGender << "       "
		<< temp->studentAge << "    "
		<< temp->studentCategory << "    "
		<< endl;
	current->link = temp->link;
	delete temp;
}


void List::Change(int ID)
{
	LinkNode* current = first->link;
	while (current != nullptr && current->studentID != ID)
	{
		current = current->link;
	}//�ҵ���λ�ò��޸�
	if (current != nullptr)
	{
		cout << "���������뿼���Ŀ��ţ��������Ա������Լ��������" << endl;
		cin >> current->studentID >> current->studentName >> current->studentGender >> current->studentAge >> current->studentCategory;
	}//�Ҳ�����λ��
	else
	{
		cout << "�ÿ����Ų�����" << endl;
	}
}


int main()
{
	int number, p, operation;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	cin >> number;
	while (number <= 0)//������벻�淶
	{
		cout << "������һ����Ȼ��" << endl;
		cout << "�����뿼��������";
		cin >> number;
	}

	cout << "���������뿼���Ŀ��ţ��������Ա������Լ��������" << endl;
	List mylist;
	mylist.Input(number);//��������
	mylist.Display();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	cout << "��ѡ����Ҫ���еĲ���:";
	cin >> operation;
	while (operation != 0)//��֧ѡ��
	{
		if (operation == 1)
		{
			cout << "��������Ҫ����Ŀ���λ�ã�";
			cin >> p;
			mylist.Insert(p);
			mylist.Display();
		}
		if (operation == 2)
		{
			cout << "��������Ҫɾ���Ŀ���λ�ã�";
			cin >> p;
			mylist.Delete(p);
			mylist.Display();
		}
		if (operation == 3)
		{
			cout << "��������Ҫ���ҵĿ������ţ�";
			cin >> p;
			mylist.Find(p);
			mylist.Display();
		}
		if (operation == 4)
		{
			cout << "��������Ҫ�޸ĵĿ������ţ�";
			cin >> p;
			mylist.Change(p);
			mylist.Display();
		}
		if (operation == 5)
		{
			mylist.Display();
		}
		if (operation > 5 || operation < 0)//����ѡ����
		{
			cout << "�����ڸò���" << endl;
		}
		cout << "��ѡ����Ҫ���еĲ���:";
		cin >> operation;
	}
}
