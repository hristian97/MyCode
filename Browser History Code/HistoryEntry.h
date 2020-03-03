#pragma once

struct HistoryEntry
{
	int month;
	char* URL;
	HistoryEntry();
	HistoryEntry(int _month, char* _URL);
	~HistoryEntry();
	HistoryEntry& operator=(const HistoryEntry& other);
	void deleteURL();
	friend std::ostream& operator<<(std::ostream& out, const HistoryEntry& other)
	{
		out << "month: " << other.month << std::endl;
		if (other.URL == nullptr)
			out << "URL does not exist" << std::endl;
		else
		{
			out << "URL: " << other.URL << std::endl;
		}
		return out;
	};
	friend std::istream& operator >> (std::istream& in, HistoryEntry& other)
	{
		std::cout << "Enter month: ";
		in >> other.month;
		other.deleteURL();
		other.URL = new char[100];
		std::cout << "Enter URL: ";
		in >> other.URL;
		return in;
	}
};
