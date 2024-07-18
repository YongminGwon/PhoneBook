#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
	InitList();
	InitDummyData();
	EventLoopRun();
	ReleaseList();
	return 0;
}