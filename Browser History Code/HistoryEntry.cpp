#include<iostream>
#include"HistoryEntry.h"
HistoryEntry::HistoryEntry() :month(0), URL(nullptr) {};
HistoryEntry::HistoryEntry(int _month, char* _URL) :month(_month)
{
	URL = new char[100];
	strcpy_s(URL, 100, _URL);
}
HistoryEntry::~HistoryEntry()
{
	delete[] URL;
}
HistoryEntry& HistoryEntry::operator=(const HistoryEntry& other)
{
	month = other.month;
	deleteURL();
	URL = nullptr;
	URL = new char[100];
	strcpy_s(URL, 100, other.URL);
	return *this;
}
void HistoryEntry::deleteURL()
{
	delete[] URL;
}