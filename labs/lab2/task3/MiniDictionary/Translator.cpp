#include "stdafx.h"
#include "Translator.h"

using namespace std;

map<string, string> UseTranslator(istream& input, ostream& output, const map<string, string>& dict)
{
	string line;
	string lineInLowerCase;

	map<string, string> userDict(dict);

	while (getline(input, line))
	{
		lineInLowerCase = line;
		boost::algorithm::to_lower(lineInLowerCase);
		
		if (line == EXIT)
		{
			break;
		}
		if (userDict.count(lineInLowerCase))
		{
			output << userDict[lineInLowerCase] << "\n";
		}
		else
		{
			output << "Unknown word \"" << line << "\". "
				   << "Enter a translation or an empty line to refuse.\n";

			string translate = AddTransateToDictionry(input, userDict, lineInLowerCase);
			translate.empty() ? output << "The word \"" << line << "\" was ignored.\n" :
				output << "The word \"" << line << "\" was saved in dictionary as \"" << translate << "\".\n";
		}
	}

	return userDict;
}

std::string AddTransateToDictionry(istream& input, map<string, string>& userDict, const string& lineInLowerCase)
{
	string translate;
	getline(input, translate);
	if (!translate.empty())
	{
		userDict.insert(make_pair(lineInLowerCase, translate));
	}
	return translate;
}
