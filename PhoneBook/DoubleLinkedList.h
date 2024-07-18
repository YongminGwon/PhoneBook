#pragma once

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
	struct USERDATA* pPrev;
}USERDATA;

extern USERDATA g_HeadNode;
extern USERDATA g_TailNode;

void InitList();
void AddNewNode(int age, char* pszName, char* pszPhone);
int IsEmpty();
void ReleaseList();
int SearchListByName(char* pUser, char* pszName);
void SortListByAge();
void** SearchByIndexAgeRange(int min_age, int max_age, unsigned int* pCnt);