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

template <typename T> struct queuecast {
private:
	int cap, head,tail;
	const double CoefCap = 1.5;
	T* data;
	void morecap(){
		cap = (int)(cap * CoefCap);
		data = (T*)realloc(data, cap*sizeof(T));
	}
public:
	queuecast(int cp = 100) {
		head = 0;
		tail = 0;
		cap = cp;
		data = (T*)malloc(cap * sizeof(T));
	}
	bool empty(){
		return head == tail;
	}
	void pop() {
		if (tail != head)
		{
			tail++;
		}
		if (tail * 2 >= cap)
		{
			for (int i = 0; i < head - tail; i++)
			{
				data[i] = data[i + tail];
			}
			head -= tail;
			tail = 0;
		}
	}
	void push(T tmp) {
		data[head] = tmp;
		head++;
		if (head == cap)
			morecap();
	}
	T get() {
		return data[tail];
	}
};
template <typename T> struct queueloop {
private:
	int cap, head, tail;
	const double CoefCap = 1.5;
	T* data;
	void morecap() {
		cap = (int)(cap * CoefCap);
		data = (T*)realloc(data, cap * sizeof(T));
	}
public:
	queueloop(int cp = 100) {
		head = 0;
		tail = 0;
		cap = cp;
		data = (T*)malloc(cap * sizeof(T));
	}
	bool empty() {
		return head == tail;
	}
	void pop() {
		if (tail != head)
		{
			tail++;
			tail %= cap;
		}
	}
	void push(T tmp) {
		data[head] = tmp;
		head++;
		if (head%cap == tail){
			int _1 = cap;
			cap = cap * CoefCap;
			T* tmp= (T*)malloc(cap * sizeof(T));
			for (int i = 0; i < _1; i++)
				tmp[i] = data[(tail + i) % _1];
			data = tmp;
		}
		head %= cap;
	}
	T get() {
		return data[tail];
	}
};
