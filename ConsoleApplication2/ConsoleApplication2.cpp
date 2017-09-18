#include "stdafx.h"
#include <iostream>
#include <locale>

#include "CLinkedList.h"

using namespace std;

CLinkedList<int> g_LinkedList;

int main()
{
	setlocale(LC_ALL, "");

	//cout << L"개수 : " << g_LinkedList.size() << endl;
	wprintf(L"개수 : %d\n", g_LinkedList.size());

	g_LinkedList.push_back(1);
	g_LinkedList.push_back(2);
	g_LinkedList.push_back(3);
	g_LinkedList.push_back(4);
	g_LinkedList.push_back(5);

	CLinkedList<int>::Iterator iter = g_LinkedList.begin();

	//cout << L"begin : " << *iter << endl;
	wprintf(L"%d\n", *iter);
	iter++;
	wprintf(L"%d\n", *iter);
	iter++;
	wprintf(L"%d\n", *iter);
	iter++;
	wprintf(L"%d\n", *iter);
	iter++;
	wprintf(L"%d\n", *iter);
	iter--;
	wprintf(L"%d\n", *iter);
	iter--;
	wprintf(L"%d\n", *iter);

	//g_LinkedList.clear();

	iter = g_LinkedList.erase(iter);

	wprintf(L"\n-------------------------------------------------\n\n");

	auto NowIter = g_LinkedList.begin();
	auto EndIter = g_LinkedList.end();

	while (NowIter != EndIter)
	{
		wprintf(L"%d\n", *NowIter);
		NowIter++;
	}

	wprintf(L"개수 : %d\n", g_LinkedList.size());

    return 0;
}