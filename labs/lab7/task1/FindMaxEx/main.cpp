#include "stdafx.h"
#include "FindMaxEx.h"

using namespace std;

struct Sportsman
{
	string FIO;
	int height;
	int weight;
};

int main()
{
	vector<Sportsman> sportsmans;

	sportsmans.push_back({ "1: Ivan Ivanov", 160, 50 });
	sportsmans.push_back({ "2: Dmitry Sedov", 170, 60 });
	sportsmans.push_back({ "3: Lionel Messi", 180, 70 });
	sportsmans.push_back({ "4: Usain Bolt", 190, 80 });
	sportsmans.push_back({ "5: Michael Jordan", 200, 90 });

	Sportsman resOfMaxVal;

	FindMax(sportsmans, resOfMaxVal, [](Sportsman a, Sportsman b) { return a.height < b.height; });
	cout << "Max of height: " << resOfMaxVal.FIO << "\n";

	FindMax(sportsmans, resOfMaxVal, [](Sportsman a, Sportsman b) { return a.height > b.height; });
	cout << "Min of height: " << resOfMaxVal.FIO << "\n";

	FindMax(sportsmans, resOfMaxVal, [](Sportsman a, Sportsman b) { return a.weight < b.weight; });
	cout << "Max of weight: " << resOfMaxVal.FIO << "\n";

	FindMax(sportsmans, resOfMaxVal, [](Sportsman a, Sportsman b) { return a.weight > b.weight; });
	cout << "Min of weight: " << resOfMaxVal.FIO << "\n";

	return 0;
}