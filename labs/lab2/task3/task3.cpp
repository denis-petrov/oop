#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <unordered_map>
#include <string>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/serialization/map.hpp>

#include<stdio.h>
#include<windows.h>

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
	ifstream fin(fname, std::ios::binary);
	boost::archive::binary_iarchive iarch(fin);
	iarch >> dict;

	fin.close();
	return dict;
}

void UseDictionary(istream& stream)
{
	unordered_map<string, string> dictionary;

}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	UseDictionary(cin);

	map<string, string> map = { { "hello", "првиет" }, { "bye", "пока" } };

	SerializeDictionary(map, "output");

 	auto newMap = DeserializeDictionary("output");

	std::cout << (map == newMap) << std::endl << map["bye"] << " ура " << newMap["bye"] << std::endl;

    return 0;
}
