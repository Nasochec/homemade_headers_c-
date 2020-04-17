#pragma once
#include<Windows.h>
#include<stdio.h> 
#include<math.h> 
#include<string> 
#include<string.h> 
#include<iostream>
#include<vector> 
#include<set> 
#include<algorithm>
#include<functional>
#include<utility>
#include<iomanip>
#include<time.h> 
#include<queue>  
#include<map> 
#include<stack>
#include<limits.h> 
template <typename T>
struct stek {
private:
	int cap, size;
	T* data;
	void morecap() {
		cap = (int)(cap * 1.5);
		realloc(data, cap);
	}
public:
	stek(int cp = 100) {
		size = 0;
		cap = cp;
		data = (T*)malloc(100 * sizeof(T));
	}
	void push(T tmp)
	{
		if (size >= cap)
			morecap();
		data[size] = tmp;
		size++;
	}
	void pop() {
		if (!empty())
			size--;
	}
	T top() {
		if (!empty())
			return data[size - 1];
		return data[0];
	}
	bool empty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
};
