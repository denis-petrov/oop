#include "stdafx.h"
#include "Serialization.h"
#include "Translator.h"

using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	if (argc < 2)
	{
		cout << "Неверное количество аргументов.\n";
		cout << "Используйте: task3.exe <имя файла словаря>.\n";
		return 1;
	}
	string fname = argv[1];

	auto dictionary = DeserializeDictionary(fname);

	auto tempDictionaty = UseTranslator(cin, cout, dictionary);

	SaveDictionaty(fname, cin, cout, dictionary, tempDictionaty);
	
	return 0;
}
