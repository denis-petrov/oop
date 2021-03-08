#include <fstream>
#include <optional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/serialization/map.hpp>
#include <boost/algorithm/string.hpp>

#include <stdio.h>
#include <windows.h>

using namespace std;

const string EXIT = "...";
const string AGREE = "y";


struct Args
{
	std::string dictionaryFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count.\n";
		std::cout << "Usage: task3.exe <dictionary file name>.\n";
		return std::nullopt;
	}
	Args args;
	args.dictionaryFileName = argv[1];

	return args;
}

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

map<string, string> UseTranslator(istream& input, ostream& output, const map<string, string>& dict)
{
	string line;
	map<string, string> tempDict(dict);

	while (getline(input, line))
	{
		boost::algorithm::to_lower(line);
		if (line == EXIT)
		{
			break;
		}
		if (tempDict.count(line))
		{
			output << tempDict[line] << "\n";
		}
		else
		{
			output << "Неизвестное слово \"" << line << "\". "
				   << "Введите перевод или пустую строку для отказа.\n";
			string translate;
			getline(input, translate);
			if (translate.empty())
			{
				output << "Слово \"" << line << "\" проигнорировано.\n";
			}
			else
			{
				tempDict.insert(make_pair(line, translate));
				output << "Слово \"" << line << "\" сохранено в словаре как \"" << translate << "\".\n";
			}
		}
	}

	return tempDict;
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

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}
	
	auto dictionary = DeserializeDictionary(args->dictionaryFileName);

	auto tempDictionaty = UseTranslator(cin, cout, dictionary);

	SaveDictionaty(args->dictionaryFileName, cin, cout, dictionary, tempDictionaty);
	
	return 0;
}
