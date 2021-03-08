#include "stdafx.h"
#include "Translator.h"

using namespace std;

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
			output << "Неизвестное слово \"" << line << "\"."
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