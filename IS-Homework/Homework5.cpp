#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm> 
#include <ctime>
#include "VoteProbability.h"

using namespace std;



int main()
{		
	srand(time(NULL));
	ifstream file("house-votes-84.data");
	if (!file) {
		cout << "Cannot open input file.\n";
		return 1;
	}

	string str, line;
	vector<vector<string>> Records;
	while (getline(file, line)) {
		vector<string> cols;
		stringstream X(line);
		while (getline(X, str, ',')) {
			cols.push_back(str);
		}
		Records.push_back(cols);
		cols.clear();
	}
	file.close();
	//
	int RepCounts = 0, DemoCounts = 0;
	for (int i = 0; i < Records.size(); i++) {
		if (Records[i][0] == "republican") {
			RepCounts++;
		}
		else {
			DemoCounts++;
		}
	}
	//
	double ProbRep = ((double)RepCounts) / Records.size();
	double ProbDemo = ((double)DemoCounts) / Records.size();
	int testRecordsCount = Records.size() / 10;
	//
	int summary = 0;
	random_shuffle(Records.begin(), Records.end());
	for (int turn = 0; turn < 10; turn++) 
	{
		map<int, VoteProbability> Probabilities;
		vector<vector<string>> testRecords, trainingRecords;
		for (int i = 0; i < Records.size(); i++) 
		{
			if (i > turn * testRecordsCount && i < (turn + 1) * testRecordsCount)
			{
				testRecords.push_back(Records[i]);
			}
			else
			{
				trainingRecords.push_back(Records[i]);
			}
		}
		//Training begins here
		for (int k = 1; k < trainingRecords[0].size(); k++) 
		{
			int DemoPositive=0, DemoNegative=0, RepPositive=0, RepNegative=0;
			int RepCount = 0, DemoCount = 0;

			for (int i = 0; i < trainingRecords.size(); i++) 
			{
					if (trainingRecords[i][0] == "democrat")
					{
						
						if (trainingRecords[i][k] == "y")
						{
							DemoPositive++;
							DemoCount++;
						}
						else if (trainingRecords[i][k] == "n")
						{
							DemoNegative++;
							DemoCount++;
						}
					}
					else
					{
						if (trainingRecords[i][k] == "y")
						{
							RepPositive++;
							RepCount++;
						}
						else if(trainingRecords[i][k] == "n")
						{
							RepNegative++;
							RepCount++;
						}
					}
			}

			double ProbDemoPositive = 0, ProbDemoNegative = 0, ProbRepPositive = 0, ProbRepNegative = 0;

			ProbDemoPositive = ((double)DemoPositive) / DemoCount;
			ProbDemoNegative = ((double)DemoNegative) / DemoCount;
			ProbRepPositive = ((double)RepPositive) / RepCount;
			ProbRepNegative = ((double)RepNegative) / RepCount;

			VoteProbability VotingProbabilities = VoteProbability(ProbDemoPositive, ProbDemoNegative,ProbRepPositive, ProbRepNegative);
			Probabilities.insert(make_pair(k, VotingProbabilities));
		}

		//Training ends test Begins

		int identities = 0;
		//How many we have predicted correctly 
		for (int j = 0; j < testRecords.size(); j++) {
			vector<string> example = testRecords[j];
			double exampleProbDemo = 0, exampleProbRep = 0;
			for (int k = 1; k < example.size(); k++) {
				if (example[k] == "y") {
					exampleProbDemo += log2(Probabilities[k].ProbDemoPositive);
					exampleProbRep += log2(Probabilities[k].ProbRepPositive);
				}
				else if (example[k] == "n") {
					exampleProbDemo += log2(Probabilities[k].ProbDemoNegative);
					exampleProbRep += log2(Probabilities[k].ProbRepNegative);
				}
			}
			exampleProbDemo += log2(ProbDemo);
			exampleProbRep += log2(ProbRep);
			//cout << j + 1 << ":";
			if (exampleProbDemo > exampleProbRep) {
				if (testRecords[j][0] == "democrat") {
					identities++;
				}
				//cout << "The person is democrat." << endl;
			}
			else {
				if (testRecords[j][0] == "republican") {
					identities++;
				}
				//cout << "The person is republican." << endl;
			}
		}
		summary += identities;
		cout << "Accuracy[" << turn + 1 << "] = " << (double)identities / (double)testRecordsCount << endl;
		Probabilities.clear();
		//Test ends
	}

	cout << endl;
	cout << "Summary: " << (double)summary / ((double)testRecordsCount * 10) << endl;
	cout << endl;
	system("pause");
	return 0;
}