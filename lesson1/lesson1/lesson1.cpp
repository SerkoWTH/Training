
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;


template <class T>
ostream& operator << (ostream& o, const vector<T>& v) {
	o << "[";
	for (auto& x : v) {
		o << x << ", ";
	}
	return o << "]";
}

template <class TFunc, class TResult, class TParam1>
void test(TResult expect, TFunc f, TParam1 p1) {
	auto got = f(p1);
	if (got != expect) {
		cerr << "failed: " << expect << " != " << got << endl;
	}
}

template <class TFunc, class TResult, class TParam1, class TParam2>
void test(TResult expect, TFunc f, TParam1 p1, TParam2 p2) {
	auto got = f(p1, p2);
	if (got != expect) {
		cerr << "failed: f(" << p1 << ", " << p2 << ") = "
			<< got << " != " << expect << endl;
	}
}

template <class TFunc, class TResult, class TParam1, class TParam2, class TParam3, class TParam4>
void test(TResult expect, TFunc f, TParam1 p1, TParam2 p2, TParam3 p3, TParam4 p4) {
	auto got = f(p1, p2, p3, p4);
	cout << " f(" << p1 << ", " << p2 << ", " << p3 << ", " << p4 << ")" << endl;
	if (got == expect) {
		cerr << "SUCSESS: " << got << " == " << expect << endl;
	}
	else
	{
		cerr << "FAILED: " << got << " != " << expect << endl;
	}
	cout << endl;
}

int search_0(int v[], size_t size, int key) {
	for (size_t i = 0; i < size; ++i) {
		if (v[i] == key) {
			return i;
		}
	}

	return -1;
}

int search_1(int v[], size_t size, int key) {
	v[size] = key;

	int i = 0;
	while (v[i] != key) { ++i; }

	if (i != size) {
		return i;
	}

	return -1;
}

int search_2(const std::vector<int>& v, int key) {
	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i] == key) {
			return i;
		}
	}

	return -1;
}

/*int search_3(std::vector<int>& v, int key) {
v.push_back(key);
int i = 0;
while (v[i] != key) {
++i;
}
v.pop_back();
if (i != v.size()) {
return i;
}
return -1;
}*/

void test_search() {

	typedef std::vector<int> Array;

	auto search = search_2;

	auto key = 8;
	// key not exists in array
	test(-1, search, Array(), key); // degerate
	test(-1, search, Array({ key - 1 }), key); // trivial
	test(-1, search, Array({ key - 1, key + 1 }), key); // trivial2
	test(-1, search, Array({ 1,2,3,4,5,7 }), key); // general
	test(-1, search, Array({ 9,10,11,12 }), key); // general
	test(-1, search, Array({ 4,1,2,7,10 }), key); // general
												  // key exists in array
												  // non appliable // degerate
	test(0, search, Array({ key }), key); // trivial
	test(0, search, Array({ key, key + 1 }), key); // trivial2
	test(1, search, Array({ key - 1, key }), key); // trivial2
	test(8, search, Array({ 0,1,2,3,4,5,6,7,key }), key); // general
	test(0, search, Array({ key, 9,10,11,12 }), key); // general
	test(2, search, Array({ 4,1,key,7,10 }), key); // general                

												   //test(0, search, Array({ key,1,key,7,10 }), key); // general                
												   //test(2, search, Array({ 2,1,key,7,key }), key); // general                
}


int binary_search_helper
(
	const  vector<int>& v,
	size_t begin,
	size_t end,
	int key
)
{
	assert(std::is_sorted(v.begin(), v.end()));
	if (begin < end)
	{

		// [b, e) = [b, m) U [m] U [m, e)
		size_t m = (begin + end) / 2;
		assert((m - begin) + (end - m) == (end - begin));
		if (key < v[m]) {
			return binary_search_helper(v, begin, m, key);
		}
		else if (v[m] < key) {
			return binary_search_helper(v, m + 1, end, key);
		}
		else {
			return m;
		}
	}

	return -1;
}

int binary_search
(
	const  vector<int>& v,
	int key
)
{
	assert(std::is_sorted(v.begin(), v.end()));

	size_t begin = 0;
	size_t end = v.size();

	while (begin < end)
	{
		// [b, e) = [b, m) U [m] U [m, e)
		size_t m = begin + (end - begin) / 2;
		if (key < v[m]) {
			end = m;
		}
		else if (v[m] < key) {
			begin = m + 1;
		}
		else {
			return m;
		}
	}

	return -1;
}

void test_binary_search()
{
	typedef std::vector<int> Array;

	int key = 8;

	// key not exists in array
	cout << " ----- key not exists in array ----- " << endl << endl;
	test(-1, binary_search_helper, Array(), 0, 0, key); // degerate
	test(-1, binary_search_helper, Array({ key - 1 }), 0, 0, key); // trivial
	test(-1, binary_search_helper, Array({ key - 1, key + 1 }), 0, 0, key); // trivial2
	test(-1, binary_search_helper, Array({ 1, 2, 3, 4, 5, 7 }), 0, 6, key); // general
	test(-1, binary_search_helper, Array({ 9, 10, 11, 12 }), 0, 4, key); // general
	test(-1, binary_search_helper, Array({ 1, 2, 4, 7, 10 }), 0, 5, key); // general

	// key exists in array
	cout << " ----- key exists in array ----- " << endl << endl;
	// non appliable // degerate
	test(0, binary_search_helper, Array({ key }), 0, 1, key); // trivial
	test(0, binary_search_helper, Array({ key, key + 1 }), 0, 2, key); // trivial2
	test(1, binary_search_helper, Array({ key - 1, key }), 0, 2, key); // trivial3
	test(8, binary_search_helper, Array({ 0, 1, 2, 3, 4, 5, 6, 7, key }), 0, 9, key); // general
	test(0, binary_search_helper, Array({ key, 9, 10, 11, 12 }), 0, 5, key); // general
	test(3, binary_search_helper, Array({ 1, 4, 7, key, 10 }), 0, 5, key); // general

	// key exists in array
	cout << " ----- other ----- " << endl << endl;
	test(-1, binary_search_helper, Array({ 5, 6, 7 }), 0, 1, key); // trivial

	//vector<int> arr({ 0, 1, 3, 5, 9, 11, 15, 20, 22 });
	//test(1, binary_search_helper, arr, 0, 9, 1);
}


int* lower_bound(int* begin, int* end, int key)
{
	int* b = begin;
	int* e = end;
	int* m;

	while (e - b > 1)
	{
		m = b + (e - b) / 2;
		if (key < *m)
			e = m;
		else
			b = m;
	}

	return b;
}
int* binary_search_lb(int* begin, int* end, int key)
{
	int* first = lower_bound(begin, end, key);
	//dreturn 


	/*
	return (_First != _Last && !_Pred(_Val, *_First));
	*/
}
void test_binary_search_lb()
{



	//binary_search
	/***/
	//int tmp0[] = { 1, 4, 8, 8, 8, 10 };
	//lower_bound(tmp0, tmp0 + 5, 8);
	int tmp1[] = { 1, 4, 7, 8, 10 };
	lower_bound(tmp1, tmp1 + 5, 8);
	int tmp2[] = { 1, 4, 7, 8, 10, 11 };
	lower_bound(tmp2, tmp2 + 6, 8);
	/***/




	typedef std::vector<int> Array;
	//auto search = [](const vector<int>)

	int key = 8;

	/*
	// key not exists in array
	cout << " ----- key not exists in array ----- " << endl << endl;
	test(-1, binary_search_helper, Array(), 0, 0, key); // degerate
	test(-1, binary_search_helper, Array({ key - 1 }), 0, 0, key); // trivial
	test(-1, binary_search_helper, Array({ key - 1, key + 1 }), 0, 0, key); // trivial2
	test(-1, binary_search_helper, Array({ 1, 2, 3, 4, 5, 7 }), 0, 6, key); // general
	test(-1, binary_search_helper, Array({ 9, 10, 11, 12 }), 0, 4, key); // general
	test(-1, binary_search_helper, Array({ 1, 2, 4, 7, 10 }), 0, 5, key); // general

																		  // key exists in array
	cout << " ----- key exists in array ----- " << endl << endl;
	// non appliable // degerate
	test(0, binary_search_helper, Array({ key }), 0, 1, key); // trivial
	test(0, binary_search_helper, Array({ key, key + 1 }), 0, 2, key); // trivial2
	test(1, binary_search_helper, Array({ key - 1, key }), 0, 2, key); // trivial3
	test(8, binary_search_helper, Array({ 0, 1, 2, 3, 4, 5, 6, 7, key }), 0, 9, key); // general
	test(0, binary_search_helper, Array({ key, 9, 10, 11, 12 }), 0, 5, key); // general
	test(3, binary_search_helper, Array({ 1, 4, 7, key, 10 }), 0, 5, key); // general
	*/
}

int main(int argc, char const *argv[])
{
	//test_search();
	//test_binary_search();
	test_binary_search_lb();

	system("pause");
	return 0;
}
