#include "stdafx.h"
#include "Serialization.h"

using namespace std;

void SerializeDictionary(const map<string, string>& dict, const string& fname)
{
	ofstream fout(fname, ios::binary);
	boost::archive::binary_oarchive oarch(fout);
	oarch << dict;
	fout.close();
}

map<string, string> DeserializeDictionary(const string& fname)
{
	map<string, string> dict;
	std::ifstream fin(fname, ios::binary);
	if (!fin)
	{
		fin.close();
		return dict;
	}

	boost::archive::binary_iarchive iarch(fin);
	iarch >> dict;

	fin.close();
	return dict;
}

void SaveDictionaty(const string& fname, istream& input, ostream& output, const map<string, string>& dict, const map<string, string>& tempDict)
{
	if (dict != tempDict)
	{
		output << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";

		string line;
		getline(input, line);
		boost::algorithm::to_lower(line);

		if (line == AGREE)
		{
			SerializeDictionary(tempDict, fname);
			output << "Изменения сохранены.\n";
		}
		else
		{
			output << "Изменения не сохранены.\n";
		}
	}
	output << "До свидания.\n";
}