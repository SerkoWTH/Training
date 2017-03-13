// lesson1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
using namespace std;


int naiveSearch(int arr[], int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == key)
			return i;
	}

	return -1;
}

int main()
{
	int arr1[] = { 0, 8, 11, 60, 4, 1, 5, 9 };


	cout << naiveSearch(arr1, 8, 8) << endl;
	cout << naiveSearch(arr1, 8, 5) << endl;

	system("pause");
    return 0;
}

