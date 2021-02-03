#pragma once
#include<random>
#include<math.h>
class City
{
private:
	int x, y;
public:
	City() 
	{
		x = rand() % 100;
		y = rand() % 100;
	}
	int GetX() { return x; }
	int GetY() { return y; }
	double distance(City other)
	{
		return sqrt(pow((this->x - other.GetX()), 2) + pow((this->y - other.GetY()), 2));
	}
	friend std::ostream& operator << (std::ostream& out, const City& c)
	{
		out << c.x << "," << c.y;
		return out;
	}
	City& operator=(const City& second) 
	{
		if (this != &second) {
			this->x = second.x;
			this->y = second.y;
		}
		return *this;
	}
	bool operator==(City& second) 
	{
		if (this->x == second.x && this->y == second.y)
			return true;
		return false;
	}

};