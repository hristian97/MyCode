#pragma once

class VoteProbability {
public:
	double ProbDemoPositive;
	double ProbDemoNegative;
	double ProbRepPositive;
	double ProbRepNegative;

	VoteProbability()
	{
		ProbDemoPositive=0;
		ProbDemoNegative=0;
		ProbRepPositive=0;
		ProbRepNegative=0;
	};
	VoteProbability(double _ProbDemoPositive, double _ProbDemoNegative,
		double _ProbRepPositive, double _ProbRepNegative) :ProbDemoPositive(_ProbDemoPositive), ProbDemoNegative(_ProbDemoNegative), ProbRepPositive(_ProbRepPositive), ProbRepNegative(_ProbRepNegative) {};
};