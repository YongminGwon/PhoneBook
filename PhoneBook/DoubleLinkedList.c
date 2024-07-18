#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DoubleLinkedList.h"

USERDATA g_HeadNode = { 0, "__DummyHead__" };
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

void** SearchByIndexAgeRange(int min_age, int max_age, unsigned int* pCnt)
{
	*pCnt = 0;
	USERDATA* pTmp = g_HeadNode.pNext;

}