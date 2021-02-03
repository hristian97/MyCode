#pragma once
#include"City.h"
#include<vector>
#include<chrono>
class Road
{
private:
	int Size;
	double distance;
	std::vector<City> cities;
public:
	Road()
	{
		Size = 0;
		distance = 0;
		cities.clear();
	}
	Road(int _size)
	{
		Size = _size;
		distance = 0;
		cities.resize(_size);
	}
	Road(std::vector<City> _cities)
	{
		Size = _cities.size();
		this->cities = _cities;
		Recalculate();
		
	}
	Road(const Road& copy)
	{
		Size = copy.Size;
		distance = copy.distance;
		cities = copy.cities;
	}
	void Shuffle()
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(cities.begin(), cities.end(), std::default_random_engine(seed));
		Recalculate();
		
	}
	double GetDistance() { return distance; }
	int GetSize() { return Size; }
	void Recalculate()
	{
		distance = 0;
		for (int i = 0; i < Size-1; i++)
		{
			distance+= cities[i].distance(cities[i + 1]);
		}
	}
	void AddCity(City city)
	{
		Size++;
		cities.push_back(city);
		Recalculate();
	}
	friend std::ostream& operator<<(std::ostream& output, const Road& r) {
		for (int i = 0; i < r.Size; i++) {
			output << r.cities[i]<< " ";
		}
		output << "distance: " << r.distance << std::endl;
		return output;
	}
	void Mutation()
	{
		int pos1 = rand() % Size;
		int pos2 = rand() % Size;
		City Temp=cities[pos1];
		cities[pos1] = cities[pos2];
		cities[pos2] = Temp;
		Recalculate();
	}
	Road Child(Road mother)
	{
		Road little;
		int pos1 = rand() % Size;
		int pos2 = rand() % Size;
		if (pos1 > pos2)
		{
			std::swap(pos1, pos2);
		}
		int br2 = 0;
		for (int i = pos1; i < pos2; i++)
		{
			for (int j = 0; j < Size- br2; j++)
			{
				if (mother.cities[j] == cities[i])
				{
					mother.cities.erase(mother.cities.begin() + j);
					br2++;
					break;
				}
			}
		}
		int br = 0;
		for (int i = 0; i < Size; i++)
		{
			if (i >= pos1 && i<=pos2)
			{
				little.AddCity(cities[i]);
			}
			else
			{
				little.AddCity(mother.cities[br]);
				br++;
			}
		}
		return little;
	}
	bool operator <(const Road& road) const
	{
		return (distance < road.distance);
	}
};
