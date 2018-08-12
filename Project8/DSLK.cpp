#include <iostream>
#include <conio.h>
using namespace std;

struct node
{
	int info;
	node *next;
};

struct list
{
	node *head;
	node *tail;
};

void Swap(node *a, node *b)
{
	int temp = a->info;
	a->info = b->info;
	b->info = temp;
}

node *GetNode(int x)
{
	node *p;
	p = new node;
	if (p == NULL)
	{
		cout << "Khong du bo nho!";
		exit(1);
	}
	p->info = x;
	p->next = NULL;
	return p;
}

void InsertHead(list &l, int x, int &count)
{
	node *p;
	p = GetNode(x);
	if (p == NULL)
	{
		cout << "Khong tao duoc nut!";
		exit(1);
	}
	if (l.head == NULL)
	{
		l.head = l.tail = p;
		count++;
	}
	else {
		p->next = l.head;
		l.head = p;
		count++;
	}
}

void Input(list &l, int x, int &count)
{
	l.head = l.tail = NULL;
	count = 0;
	while (1)
	{
		cout << "Nhap so nguyen, nhap 0 de dung (0/n*): ";
		cin >> x;
		while (x < 0)
		{
			cout << "Nhap sai. Nhap lai (0/n*): ";
			cin >> x;
		}
		if (x == 0)
			return;
		InsertHead(l, x, count);
	}
}

void Output(list &l)
{
	node *p;
	p = l.head;
	while (p != NULL)
	{
		cout << p->info << " ";
		p = p->next;
	}
}

void ReverseList(list &l)
{
	if (l.head == NULL)
		return;
	node *next;
	node *curr = l.head;
	node *prev = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	l.head = prev;
}

void DelHead(list &l)
{
	node *p;
	if (l.head != NULL)
	{
		p = l.head;
		l.head = l.head->next;
		delete p;
		if (l.head == NULL)
			l.tail = NULL;
	}
}

void DelTail(list &l)
{
	ReverseList(l);
	DelHead(l);
	ReverseList(l);
}

void DelPos(list &l, int &count)
{
	if (l.head == NULL)
	{
		cout << "Danh sach rong.";
		return;
	}
	node *p;
	p = l.head;
	node *tprev = p, *tnext = p;
	int pos;
	cout << "Nhap vi tri phan tu can xoa (1-" << count << "): ";
	cin >> pos;
	while (pos > count || pos == 0)
	{
		cout << "Vi tri khong ton tai. Nhap lai (1-" << count << "): ";
		cin >> pos;
	}
	if (pos == 1)
	{
		DelHead(l);
		count--;
		cout << "Danh sach sau khi xoa: ";
		Output(l);
		return;
	}
	if (pos == count)
	{
		DelTail(l);
		count--;
		cout << "Danh sach sau khi xoa: ";
		Output(l);
		return;
	}
	tprev = p;
	p = p->next;
	tnext = p->next;
	for (int i = 2; i <= pos; i++)
	{
		if (i == pos)
			delete p;
		else {
			tprev = p;
			p = p->next;
			tnext = p->next;
		}
	}
	p = tprev;
	p->next = tnext;
	p = p->next;
	l.tail = p;
	count--;
	cout << "Danh sach sau khi xoa: ";
	Output(l);
}

void DelValue(list &l, node *&head)
{
	if (l.head == NULL)
	{
		cout << "Danh sach rong.";
		return;
	}
	node *temp = new node;
	temp->next = head;
	head = temp;
	node *q, *p = head;
	int val, check = 0;
	cout << "Nhap so can xoa: ";
	cin >> val;
	while (p->next != NULL)
	{
		if (p->next->info == val)
		{
			q = p->next;
			p->next = q->next;
			delete q;
			check++;
		}
		if (p->next == NULL)
			break;
		p = p->next;
	}
	head = head->next;
	delete temp;
	if (check == 0)
		cout << "Khong tim thay so can xoa.";
	else {
		cout << "Danh sach sau khi xoa: ";
		Output(l);
	}
}

void ListSelectionSort(list &l)
{
	if (l.head == NULL)
	{
		cout << "Danh sach rong.";
		return;
	}
	node *min;
	node *p, *q;
	p = l.head;
	while (p != l.tail)
	{
		min = p; q = p->next;
		while (q != NULL)
		{
			if (q->info < min->info)
				min = q;
			q = q->next;
		}
		Swap(min, p);
		p = p->next;
	}
	cout << "Danh sach sau khi sap xep tang dan: ";
	Output(l);
}

void Insert(list &l, int &count)
{
	node *p, *q, *temp;
	int x, pos, check = 1;
	cout << "Nhap so: ";
	cin >> x;
	cout << "Nhap vi tri can chen (1-" << count + 1 << "): ";
	cin >> pos;
	while (pos > count + 1 || pos < 1)
	{
		cout << "Vi tri khong hop le. Nhap lai (1-" << count + 1 << "): ";
		cin >> pos;
	}
	if (pos == 1)
		InsertHead(l, x, count);
	else {
		q = GetNode(x);
		p = l.head;
		while (check != pos - 1)
		{
			if (p == NULL)
				break;
			else {
				p = p->next;
				check++;
			}
		}
		temp = p->next;
		p->next = q;
		p = p->next;
		p->next = temp;
		count++;
	}
}

void Split(list &l, list &l1, list &l2)
{
	l1.head = l1.tail = NULL;
	l2.head = l2.tail = NULL;
	node* p;
	p = l.head;
	int count1 = 0, count2 = 0, k;
	while (p != NULL)
	{
		k = p->info;
		if (k % 2 == 0)
			InsertHead(l1, k, count1);
		else
			InsertHead(l2, k, count2);
		p = p->next;
	}
	l.head = l.tail = NULL;
}

void Menu()
{
	cout << "=============================================== MENU ===============================================";
	cout << "\n1. Nhap, xuat danh sach so nguyen";
	cout << "\n2. Dao nguoc danh sach";
	cout << "\n3. Xoa mot phan tu tai vi tri thu k trong danh sach";
	cout << "\n4. Xoa phan tu co gia tri x trong danh sach";
	cout << "\n5. Sap xep danh sach tang dan theo nhieu cach";
	cout << "\n6. Chen mot phan tu co gia tri x vao vi tri thu k cua danh sach";
	cout << "\n7. Tach danh sach thanh 2 danh sach: mot danh sach chua toan so chan, mot danh sach chua toan so le";
	cout << "\n\n0. Thoat";
}

void Process(list &l, list &l1, list &l2, int x, int &count)
{
	int sel;
	cout << "\n\nChon cong viec (0-7): ";
	cin >> sel;
	while (sel < 0 || sel > 7)
	{
		cout << "Nhap sai. Vui long nhap lai (0-7): ";
		cin >> sel;
	}
	switch (sel)
	{
	case 0:
		exit(1);
	case 1:
		cout << endl;
		Input(l, x, count);
		cout << "Cac so da nhap: ";
		Output(l);
		cout << "\n\n";
		system("pause");
		break;
	case 2:
		cout << endl;
		ReverseList(l);
		cout << "Danh sach dao nguoc: ";
		Output(l);
		cout << "\n\n";
		system("pause");
		break;
	case 3:
		cout << endl;
		DelPos(l, count);
		cout << "\n\n";
		system("pause");
		break;
	case 4:
		cout << endl;
		DelValue(l, l.head);
		cout << "\n\n";
		system("pause");
		break;
	case 5:
		cout << endl;
		ListSelectionSort(l);
		cout << "\n\n";
		system("pause");
		break;
	case 6:
		cout << endl;
		Insert(l, count);
		cout << "Danh sach sau khi chen: ";
		Output(l);
		cout << "\n\n";
		system("pause");
		break;
	case 7:
		cout << endl;
		Split(l, l1, l2);
		cout << "Danh sach so chan: ";
		Output(l1);
		cout << "\nDanh sach so le: ";
		Output(l2);
		cout << "\n\n";
		system("pause");
		break;
	}
}

void main()
{
	list l, l1, l2;
	l.head = l.tail = NULL;
	l1.head = l1.tail = NULL;
	l2.head = l2.tail = NULL;
	int x = NULL, count = 0;
	while (1)
	{
		system("cls");
		Menu();
		Process(l, l1, l2, x, count);
	}
}

/*for (node *p = head; p->next != NULL; p = p->next)
if (p->next->info == val)
{
q = p->next;
p->next = q->next;
delete q;
check++;
}*/
