#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "DoubleLinkedList.h"
#include "ui.h"

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
	int min_age = 0, max_age = 0;
	unsigned int cnt = 0;
	printf("Age From? :");
	scanf_s("%d%*c", &min_age);
	printf("Age To? : ");
	scanf_s("%d%*c", &max_age);

	SortListByAge();

	USERDATA** pList = (USERDATA**)SearchByIndexAgeRange(min_age, max_age, &cnt);
	USERDATA* pTmp = NULL;
	for (unsigned int i = 0; i < cnt; ++i)
	{
		pTmp = (USERDATA*)pList[i];
		printf("%d, %s, %s\n", pTmp->age, pTmp->name, pTmp->phone);
	}
	free(pList);
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