#pragma once
#include<iostream>
#include"HistoryEntry.h"
class BrowserHistory
{
private:
	HistoryEntry* History;
	int max_size;
	int curr_size;
	bool isEmpty();
	bool isFull();
	void deleteHistory();
public:
	BrowserHistory(int N);
	~BrowserHistory();
	void addSite();
	void addSite(const HistoryEntry& other);
	void print();
	int numberOfSitesInMonth(int _month);
	int mostActiveMonth();
	void deleteLastEntry();
	BrowserHistory& operator+(const BrowserHistory& second);
};
