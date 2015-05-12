#include <iostream>

#include "converter.h"
#include "helper.h"
using namespace fly2elephant;

int main(int argc, char *argv[])
try {
	::setlocale(LC_CTYPE, "ru_RU.utf8");

	Helper::CheckMainArguments(argc, argv);

	std::wstring fly;
	std::wstring elephant;
	Helper::CookWords(argv[1], fly, elephant);

	std::list<std::wstring> dictionary;
	Helper::CookDictionary(argv[2], dictionary);

	Converter fly2Elephant(dictionary);
	std::vector<std::wstring> result;
	result = fly2Elephant.DoMagic(fly, elephant);
	for (std::wstring &word : result) {
		std::wcout << word << std::endl;
	}

	return 0;
}
catch (const BadUsage& e) {
	std::cerr << "Program ended with an error: " << e.what() << std::endl;
	std::cerr << "Error in program usage. The correct usage is:" << std::endl;
	std::cerr << "\t" << argv[0] << " [pathToWords] [pathToDic]" << std::endl;
	std::cerr << "where:" << std::endl;
	std::cerr << "[pathToWords] is full path to the file with source and target words" << std::endl;
	std::cerr << "[pathToDic] is full path to the file with Dictionary" << std::endl;
}
catch (const FileNotExist& e) {
	std::cerr << "Program ended with an error: file \"" << e.what() << "\" is not exist" << std::endl;
	std::cerr << "Please, check correctness of file path " << std::endl;
}
