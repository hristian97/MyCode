
#include <iostream>
#include"Roads.h"

using namespace std;
void Print(vector<Road> TSP)
{
    for (int i = 0; i < TSP.size(); i++)
    {
        cout << TSP[i] << endl;
    }
}
void Generation(vector<Road> TSP, int generation)
{
    switch (generation)
    {
    case 10:
        cout << "10th Generation:" << endl;
        Print(TSP);
        break;
    case 12:
        cout << "12th Generation:" << endl;
        Print(TSP);
        break;
    case 14:
        cout << "14th Generation:" << endl;
        Print(TSP);
        break;
    case 16:
        cout << "16th Generation:" << endl;
        Print(TSP);
        break;
    }

}
int main()
{
    srand(time(NULL));
    int N;
    int MutationChance = 30;
    cin >> N;
    vector<City> cities;
    vector<Road> TSP;
    for (int i = 0; i < N; i++)
    {
        cities.push_back(City());
    }
    Road Path(cities);
    for (int i = 0; i < N; i++)
    {
        TSP.push_back(Path);
        Path.Shuffle();
    }
    sort(TSP.begin(), TSP.end());
    int counter = 0;
    while (counter < 3*N)
    {
        for (int i = 0; i < N; i++)
        {
            int pos1 = rand() % N;
            int pos2 = rand() % N;
            int Mutate = rand() % 100;
            Road Child(TSP[pos1].Child(TSP[pos2]));
            if (Mutate > MutationChance)
            {
                Child.Mutation();
            }
            TSP.push_back(Child);
        }
        sort(TSP.begin(), TSP.end());
        TSP.resize(TSP.size() / 2);
        Generation(TSP, counter);
        counter++;
    }
    cout << "Last Generation:" << endl;
    Print(TSP);
    return 0;
}
