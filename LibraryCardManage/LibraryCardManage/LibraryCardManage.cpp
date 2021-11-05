#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Date
{
	int Day, Month, Year;
};

struct Card
{
	string Id;
	string StudentId;
	string StudentName;
	Date* From = new Date;
	Date* To = new Date;
	string Role;
};
struct Node
{
	Card* data;
	Node* pNext;
};
struct SingleList
{
	Node* pHead;
};
void Initialize(SingleList*& list)
{
	list = new SingleList;
	list->pHead = NULL;
}

Date* InputDate(string role)
{
	bool isWarning = false;
	Date* result = new Date;
	cout << "Nhap Nam " + role + ":";
	cin >> result->Year;
	cin.ignore();
	do
	{
		if (isWarning)
			cout << "thang phai lon hon 0 va nho hon 12 \n";
		cout << "Nhap Thang " + role + ":";
		cin >> result->Month;
		cin.ignore();
		isWarning = true;
	} while (result->Month <= 0 || result->Month > 12);
	isWarning = false;
	do {
		cout << "Nhap Ngay " + role + ":";
		cin >> result->Day;
		cin.ignore();
		isWarning = true;
	} while (result->Day <= 0 || result->Day > 31);
	return result;
}

Card* InputCard()
{
	Card* card = new Card;
	cout << "Nhap id the: ";
	cin >> card->Id;
	cin.ignore();
	cout << "Nhap MSSV:";
	cin >> card->StudentId;
	cin.ignore();
	cout << "Nhap ho va ten sinh vien:";
	cin >> card->StudentName;
	cin.ignore();
	//cout << "Nhap ho va ten sinh vien:";
	//cin >> card->StudentName;
	//cin.ignore();
	card->From = InputDate("bat dau");
	card->To = InputDate("het han");
	return card;
}
//tao node
Node* CreateNode(Card* sv)
{
	Node* pNode = new Node;
	if (pNode != NULL)
	{
		pNode->data = sv;
		pNode->pNext = NULL;
	}
	else
	{
		cout << "cap phat bo nho that bai!!!";
	}
	return pNode;
}
//them node vao cuoi danh sach
void InsertLast(SingleList*& list, Card* sv)
{
	Node* pNode = CreateNode(sv);
	if (list->pHead == NULL)
	{
		list->pHead = pNode;
	}
	else
	{
		Node* pTmp = list->pHead;

		while (pTmp->pNext != NULL)
		{
			pTmp = pTmp->pNext;
		}
		pTmp->pNext = pNode;
	}
}
//hien thi danh sach
void PrintList(SingleList* list)
{
	Node* pTmp = list->pHead;
	if (pTmp == NULL)
	{
		cout << "Danh sach rong";
		return;
	}
	while (pTmp != NULL)
	{
		Card* sv = pTmp->data;
		cout << sv->Id << "\t" << sv->StudentName << "\t" << sv->From->Year << "/" <<sv->From->Month << "/" << sv->From->Day << "-" << sv->From->Year << "/" << sv->From->Month << "/" << sv->From->Day << "\n";
		pTmp = pTmp->pNext;
	}
}



//sap xep
void SortList(SingleList*& list)
{
	for (Node* pTmp = list->pHead; pTmp != NULL; pTmp = pTmp->pNext)
	{
		for (Node* pTmp2 = pTmp->pNext; pTmp2 != NULL; pTmp2 = pTmp2->pNext)
		{
			Card* svTmp = pTmp->data;
			Card* svTmp2 = pTmp2->data;
			if (svTmp2->Id < svTmp->Id)
			{
				string Id = svTmp->Id;
				string StudentName;
				StudentName = svTmp->StudentName;

				svTmp->Id = svTmp2->Id;
				svTmp->StudentName = svTmp2->StudentName;
				svTmp2->Id = Id;
				svTmp2->StudentName = StudentName;
			}
		}
	}
}
//xoa
void RemoveNode(SingleList*& list, string Id)
{
	Node* pDel = list->pHead;
	if (pDel == NULL)
	{
		cout << "Danh sach rong!";
	}
	else
	{
		Node* pPre = NULL;
		while (pDel != NULL)
		{
			Card* sv = pDel->data;
			if (sv->Id == Id)
				break;
			pPre = pDel;
			pDel = pDel->pNext;
		}
		if (pDel == NULL)
		{
			cout << "khong tim thay MSSV: " << Id;
		}
		else
		{
			if (pDel == list->pHead)
			{
				list->pHead = list->pHead->pNext;
				pDel->pNext = NULL;
				delete pDel;
				pDel = NULL;
			}
			else
			{
				pPre->pNext = pDel->pNext;
				pDel->pNext = NULL;
				delete pDel;
				pDel = NULL;
			}
		}
	}
}
int main(int argc, char** argv) {
	SingleList* list;
	Initialize(list);
	Card* teo = InputCard();
	InsertLast(list, teo);
	Card* ty = InputCard();
	InsertLast(list, ty);
	Card* bin = InputCard();
	InsertLast(list, bin);
	PrintList(list);
	SortList(list);
	cout << "\nSau khi sap xep:\n";
	PrintList(list);
	cout << "\Ban muon xoa sinh vien co MSSV: ";
	string Id;
	cin >> Id;
	RemoveNode(list, Id);
	cout << "\nSau khi xoa:\n";
	PrintList(list);

	cout << "\n---------------------------\n";
}