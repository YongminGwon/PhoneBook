#pragma once

typedef enum MY_MENU
{
	EXIT, NEW, SEARCH, SEARCH_RANGE, PRINT, REMOVE
} MY_MENU;

MY_MENU PrintMenu(void);
void AddNewUser();
void SearchByName();
void PrintList();
void SearchByAgeIndex();
void EventLoopRun();