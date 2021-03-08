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
			output << "����������� ����� \"" << line << "\"."
				   << "������� ������� ��� ������ ������ ��� ������.\n";
			string translate;
			getline(input, translate);
			if (translate.empty())
			{
				output << "����� \"" << line << "\" ���������������.\n";
			}
			else
			{
				tempDict.insert(make_pair(line, translate));
				output << "����� \"" << line << "\" ��������� � ������� ��� \"" << translate << "\".\n";
			}
		}
	}

	return tempDict;
}