#pragma once
#ifndef _DEQUESTACK_H_
#define _DEQUESTACK_H_
#include<string>
#include<deque>
#include<iterator>

using namespace std;

template<typename T>
class DequeStack {
public:
	DequeStack() = default;
	void push_back(T &str) { deq.push_back(str); }
	bool empty() { return deq.empty(); }
	auto begin() { return deq.begin(); }
	auto end() { return deq.end(); }
	T& front() { return deq.front(); }
	T& back() { return deq.back(); }
	T pop_front() {
		T temp = deq.front();
		if (!empty())
			deq.pop_front();
		return temp;
	}
	T pop_back() {
		T temp = deq.back();
		if (!empty())
			deq.pop_back();
		return temp;
	}
private:
	deque<T>deq;
};


#endif   //_DEQUESTACK_H_
