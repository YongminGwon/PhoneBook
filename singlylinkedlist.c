// Linked List

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
}USERDATA;

USERDATA HeadNode = { 0, "__DummyHead__"};

void PrintList()
{
	USERDATA* p_ForPrint = HeadNode.pNext;
	while (p_ForPrint != NULL)
	{
		printf("[%p] %d %s %s [%p]\n", p_ForPrint, p_ForPrint->age, p_ForPrint->name, p_ForPrint->phone, p_ForPrint->pNext);
		p_ForPrint = p_ForPrint->pNext;
	}
	putchar('\n');
}

void AddNewNode(int age, char* pszName, char* pszPhone)
{
	USERDATA* p_NewNode = (USERDATA*)malloc(sizeof(USERDATA));
	p_NewNode->age = age;
	strcpy_s(p_NewNode->name, sizeof(p_NewNode->name), pszName);
	strcpy_s(p_NewNode->phone, sizeof(p_NewNode->phone), pszPhone);
	p_NewNode->pNext = NULL;
	USERDATA* p_Tmp = &HeadNode;
	while (p_Tmp->pNext != NULL)
	{
		p_Tmp = p_Tmp->pNext;
	}
	p_Tmp->pNext = p_NewNode;
}


void InitDummyData()
{
	AddNewNode(25, "Alice", "555-1234");
	AddNewNode(30, "Bob", "555-5678");
	AddNewNode(35, "Charlie", "555-9876");
}

void ReleaseList()
{
	USERDATA* pTmp = HeadNode.pNext;
	USERDATA* pDelete;
	while (pTmp != NULL)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		printf("Delete : %d, %s, %s \n", pDelete->age, pDelete->name, pDelete->phone);
		free(pDelete);
	}
	HeadNode.pNext = NULL;
}

int main()
{
	InitDummyData();
	PrintList();
	ReleaseList();
	return 0;
}