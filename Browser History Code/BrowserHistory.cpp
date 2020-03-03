#include<iostream>
#include"BrowserHistory.h"
bool BrowserHistory::isEmpty()
{
	return curr_size == 0;
}
bool BrowserHistory::isFull()
{
	return max_size == curr_size;
}
void BrowserHistory::deleteHistory()
{
	delete[] History;
}

	BrowserHistory::BrowserHistory(int N) :max_size(N), curr_size(0)
	{
		History = new HistoryEntry[N];
	}
	BrowserHistory::~BrowserHistory()
	{
		deleteHistory();
	}
	void BrowserHistory::addSite()
	{
		if (isFull())
		{
			std::cerr << "Not possible, History is full";
		}
		else
		{
			std::cin >> History[curr_size];
			curr_size++;
		}
	}
	void BrowserHistory::addSite(const HistoryEntry& other)
	{
		if (isFull())
		{
			std::cerr << "Not possible, History is full";
		}
		else
		{
			History[curr_size] = other;
			curr_size++;
		}
	}
	void BrowserHistory::print()
	{
		for (int i = 0; i < curr_size; i++)
		{
			std::cout << History[i];
		}
	}
	int BrowserHistory::numberOfSitesInMonth(int _month)
	{
		int br = 0;
		for (int i = 0; i < curr_size; i++)
		{
			if (History[i].month == _month)
				br++;
		}
		return br;
	}
	int BrowserHistory::mostActiveMonth()
	{
		int max_month = 1;
		for (int i = 2; i < 12; i++)
		{
			if (numberOfSitesInMonth(i) > numberOfSitesInMonth(max_month))
			{
				max_month = i;
			}
		}
		return max_month;
	}
	void BrowserHistory::deleteLastEntry()
	{
		HistoryEntry* bh = new HistoryEntry[curr_size--];
		for(int i=0;i<curr_size;i++)
		{
			bh[i] = History[i];
		}
		delete[] History;
		History = bh;
	}
	BrowserHistory& BrowserHistory::operator+(const BrowserHistory& second)
	{
		BrowserHistory* bh = new BrowserHistory(this->max_size + second.max_size);
		for (unsigned int i = 0; i < this->curr_size + second.curr_size; i++) {
			if (i < this->curr_size)
			{
				bh->addSite(this->History[i]);
			}

			else {
				bh->addSite(second.History[i - this->curr_size]);
			}
		}

		return *bh;
	};