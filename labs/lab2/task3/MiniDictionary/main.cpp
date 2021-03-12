#include "stdafx.h"
#include "DictionarySerialize.h"
#include "Translator.h"

using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	if (argc < 2)
	{
		cout << "Not correct count of arguments.\n"
			 << "Use: task3.exe <dictionary filename>.\n";
		return 1;
	}
	string fname = argv[1];

	auto dictionary = DeserializeDictionary(fname);

	auto userDictionary = UseTranslator(cin, cout, dictionary);

	if (IsUserChangeDictionary(dictionary, userDictionary))
	{
		cout << "Changes have been made to the dictionary. Enter Y or y to save before exiting. \n";
		SaveDictionary(fname, cin, userDictionary) ? cout << "Changes have been saved.\n" : cout << "Changes have not been saved.\n";
	}

	cout << "Goodbye.\n";

	return 0;
}
