#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

// Todo :: Search Range Remove , Remove , 

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
	struct USERDATA* pPrev;
}USERDATA;

USERDATA g_HeadNode = {0, "__DummyHead__"};
USERDATA g_TailNode = { 0, "__DummyTail__" };

void InitList()
{
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
}

void AddNewNode(int age, char* pszName, char* pszPhone)
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	pNewNode->age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	
	USERDATA* pPrevNode = g_TailNode.pPrev;
	pPrevNode->pNext = pNewNode;
	pNewNode->pPrev = pPrevNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;
}

int IsEmpty()
{
	if (g_HeadNode.pNext == &g_TailNode)
		return 1;
	return 0;
}

void ReleaseList()
{
	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;
	while (pTmp != &g_TailNode)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;
		printf("Delete: [%p] %d, %s, %s [%p]\n", pDelete,
			pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);
		free(pDelete);
	}
	InitList();
}

int SearchListByName(char* pUser, char* pszName)
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		if (strcmp(pTmp->name, pszName) == 0)
		{
			memcpy(pUser, pTmp, sizeof(USERDATA));
			return 1;
		}
		pTmp = pTmp->pNext;
	}
	return 0;
}

void SortListByAge()
{
	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != &g_TailNode)
	{
		USERDATA* pCmp = pTmp->pNext;
		while (pCmp != &g_TailNode)
		{
			if (pTmp->age > pCmp->age)
			{
				int tmp_age = 0;
				tmp_age = pTmp->age;
				pTmp->age = pCmp->age;
				pCmp->age = tmp_age;
			}
			pCmp = pCmp->pNext;
		}
		pTmp = pTmp->pNext;
	}
}

void** SearchByAgeRange(int min_age, int max_age, int* cnt)
{

}

// UI Code
typedef enum MY_MENU
{
	EXIT, NEW, SEARCH, SEARCH_RANGE, PRINT, REMOVE
} MY_MENU;

MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;

	system("cls");
	printf("[1]New\t[2]Search\t[3]Search age\t[4]Print\t[5]Remove\t[0]Exit\n");
	scanf_s("%d%*c", &input);
	return input;
}

void AddNewUser()
{
	int age = 0;
	char name[32] = { 0 };
	char phone[32] = { 0 };

	printf("age: ");
	scanf_s("%d%*c", &age);
	printf("name: ");
	gets_s(name, sizeof(name));
	printf("phone: ");
	gets_s(phone, sizeof(phone));

	AddNewNode(age, name, phone);
}

void SearchByName()
{
	char name[32] = { 0 };
	printf("Who do you want to find?\n");
	gets_s(name, sizeof(name));
	USERDATA user = { 0 };
	if (SearchListByName(&user, name) > 0)
		printf("Found: %d, %s, %s\n", user.age, user.name, user.phone);
	else
		puts("Not found");
	_getch();
}

void PrintList()
{
	if (IsEmpty())
	{
		printf("Empty List\n");
		return;
	}
	USERDATA* pForPrint = g_HeadNode.pNext;
	while (pForPrint != &g_TailNode)
	{
		printf("[%p] %d %s %s [%p]\n", pForPrint, pForPrint->age, pForPrint->name, pForPrint->phone, pForPrint->pNext);
		pForPrint = pForPrint->pNext;
	}
	_getch();
}

void SearchByAgeIndex()
{
	if (IsEmpty())
	{
		printf("Empty List\n");
		return;
	}
	int min_age = 0, max_age = 0, cnt = 0;
	printf("Age From? :");
	scanf_s("%d%*c", &min_age);
	printf("Age To? : ");
	scanf_s("%d%*c", &max_age);
	
	SortListByAge();

	PrintList();
	void** pResult = SearchByAgeRange(min_age, max_age, &cnt);
	USERDATA* pTmp = NULL;
	for (int i = 0; i < cnt; ++i)
	{
		pTmp = (USERDATA*)pResult[i];
		printf("%d, %s, %s\n", pTmp->age, pTmp->name, pTmp->phone);
	}
	
	free(pResult);
	_getch();
}


void EventLoopRun()
{
	MY_MENU menu = 0;
	while ((menu = PrintMenu()) != 0)
	{
		switch (menu)
		{
		case NEW:
			AddNewUser();
			break;

		case SEARCH:
			SearchByName();
			break;
		
		case SEARCH_RANGE:
			SearchByAgeIndex();
			break;

		case PRINT:
			PrintList();
			break;

		/*case REMOVE:
			SearchByNameToRemove();
			break;*/

		default:
			break;
		}
	}
	puts("End Of Event Loop");
}

// Test Code

void InitDummyData()
{
	AddNewNode(1, "Ramsey", "010-1234-0000");
	AddNewNode(5, "Wilshire", "010-2345-1111");
	AddNewNode(2, "Fabregas", "010-5432-2222");
	AddNewNode(3, "Ozil", "010-3456-3333");
	AddNewNode(4, "Arteta", "010-4567-4444");
}

int main()
{
	InitList();
	InitDummyData();
	EventLoopRun();
	ReleaseList();
	return 0;
}