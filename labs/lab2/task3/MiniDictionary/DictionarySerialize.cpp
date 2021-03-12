#include "stdafx.h"
#include "DictionarySerialize.h"

using namespace std;

void SerializeDictionary(const string& fname, const map<string, string>& dict)
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

bool SaveDictionary(const string& fname, istream& input, const map<string, string>& userDict)
{
	string userAnswer;
	getline(input, userAnswer);
	boost::algorithm::to_lower(userAnswer);

	if (userAnswer == AGREE)
	{
		SerializeDictionary(fname, userDict);
		return true;
	}
	return false;
}

bool IsUserChangeDictionary(const map<string, string>& dict, const map<string, string>& userDict)
{
	return dict != userDict;
}