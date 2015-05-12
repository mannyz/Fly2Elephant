#ifndef HELPER_H_
#define HELPER_H_

#include <stdexcept>
#include <locale>
#include <string>
#include <fstream>
#include <list>
#include <vector>

namespace fly2elephant {

class BadUsage : public std::runtime_error {
public:
	BadUsage(const std::string& whatUsage)
		: runtime_error(whatUsage)
	{}

};

class FileNotExist : public std::runtime_error {
public:
	FileNotExist(const std::string& whatFile)
		: runtime_error(whatFile)
	{}
};

class Helper {
public:
	static void CheckMainArguments(int argc, char *argv[])
	{
		if (argc != 3) {
			throw BadUsage("Invalid count of arguments");
		}
	}
	static void CookDictionary(const std::string &pathToDic, std::list<std::wstring> &dictionary)
	{
		dictionary.clear();

		std::ifstream dicFile(pathToDic);
		if (!dicFile.is_open()) {
			throw FileNotExist(pathToDic);
		}

		std::string word;
		  while (std::getline(dicFile, word)) {
			std::wstring wWord;
			NormalizeWord(word, wWord);
			dictionary.push_back(wWord);
		}
		dictionary.sort();
		dictionary.unique();
	}
	static void CookWords(const std::string &pathToWords, std::wstring &flyWord, std::wstring &elephantWord)
	{
		flyWord.clear();
		elephantWord.clear();

		std::ifstream wordsFile(pathToWords);
		if (!wordsFile.is_open()) {
			throw FileNotExist(pathToWords);
		}

		std::string word;
		std::getline(wordsFile, word);
		NormalizeWord(word, flyWord);

		std::getline(wordsFile, word);
		NormalizeWord(word, elephantWord);
	}
	static void NormalizeWord(const std::string &word, std::wstring &wWord)
	{
		wWord.clear();
		if (word.empty()) {
			return;
		}
		std::vector<wchar_t> w(word.size());
		wchar_t *wWordCStr = &w[0];
//		::setlocale(LC_CTYPE, "ru_RU.utf8"); // has already set UTF8 locale for converting and towupper
		std::mbstowcs(wWordCStr, word.c_str(), w.size());
		for (wchar_t &wc : w) {
			wc = std::towupper(wc);
		}
		wWord.assign(wWordCStr);
	}

};

} // end namespace fly2elephant

#endif /* HELPER_H_ */
