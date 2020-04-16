#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<string>
#include<stdio.h>
#include<list>
using namespace std;
template<typename T> struct queuelist {
private:
	list<T> lst;
public:
	void push(T tmp) {
		lst.push_back(tmp);
	}
	T get() {
		return lst.front();
	}
	void pop() {
		lst.pop_front();
	}
	bool empty() {
		return lst.empty();
	}
};
