#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <memory>
#include <deque>
#include <locale>
#include <codecvt>

class BadUsage : public std::exception {
public:
	BadUsage(const std::string& whatUsage)
		: exception(whatUsage.c_str())
	{

	}
};

class FileNotExist : public std::exception {
public:
	FileNotExist(const std::string& whatFile)
		: exception(whatFile.c_str())
	{

	}
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

		std::wifstream dicFile(pathToDic);
		if (!dicFile.is_open()) {
			std::string badFile(pathToDic.begin(), pathToDic.end());
			throw FileNotExist(badFile);
		}

		std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
		dicFile.imbue(loc);
		std::wstring word;
		while (std::getline(dicFile, word)) {
			for (wchar_t &wc : word) {
				wc = std::toupper(wc, loc);
			}
			dictionary.push_back(word);
		}
		dictionary.sort();
		dictionary.unique();
	}

	static void CookWords(const std::string &pathToWords, std::wstring &flyWord, std::wstring &elephantWord)
	{
		flyWord.clear();
		elephantWord.clear();
		
		std::wifstream wordsFile(pathToWords);
		if (!wordsFile.is_open()) {
			std::string badFile(pathToWords.begin(), pathToWords.end());
			throw FileNotExist(badFile);
		}

		std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
		wordsFile.imbue(loc);
		std::getline(wordsFile, flyWord);
		for (wchar_t &wc : flyWord) {
			wc = std::toupper(wc, loc);
		}
		std::getline(wordsFile, elephantWord);
		for (wchar_t &wc : elephantWord) {
			wc = std::toupper(wc, loc);
		}
	}

};


class Fly2Elephant {
public:
	Fly2Elephant(const std::list<std::wstring> &dictionary)
		: m_dictionary(dictionary)
	{

	}

	void setDictionary(const std::list<std::wstring> &dictionary)
	{
		m_dictionary = dictionary;
	}
	
	std::vector<std::wstring> DoMagic(const std::wstring &flyWord, const std::wstring &elephantWord)
	{
		std::vector<std::wstring> result;

		if (flyWord.empty() || elephantWord.empty()) {
			return result;
		}
		
		if (flyWord.length() != elephantWord.length()) {
			return result;
		}

		if (flyWord == elephantWord) {
			result.push_back(elephantWord);
			return result;
		}

		std::list<std::wstring> dictionary = m_dictionary;
		std::deque<std::shared_ptr<Word>> wordsDeq;
		std::shared_ptr<Word> word = std::make_shared<Word>(flyWord);
		wordsDeq.push_back(word);
		while (!wordsDeq.empty()) {
			word = wordsDeq.front();
			wordsDeq.pop_front();

			if (word->value() == elephantWord) {
				wordsDeq.clear();
				dictionary.clear();
				break;
			}

			auto it = dictionary.begin();
			while (it != dictionary.end()) {
				auto diff = word->diffFromWord(*it);
				if (diff == 1) {
					wordsDeq.push_back(std::make_shared<Word>(*it));
					wordsDeq.back()->setPrev(word);
					dictionary.erase(it++);
					continue;
				}
				++it;
			}
		}

		if (word->value() == elephantWord) {
			std::list<std::wstring> reverseResult;
			while (word) {
				reverseResult.push_back(word->value());
				word = word->prev();
			}
			result.assign(reverseResult.rbegin(), reverseResult.rend());
		}

		return result;
	}

private:
	std::list<std::wstring> m_dictionary;

private:
	class Word {
	public:
		Word(const std::wstring &word)
			: m_word(word)
		{

		}
		const std::wstring& value() const
		{
			return m_word;
		}
		void setPrev(const std::shared_ptr<Word> &prev)
		{
			m_prev = prev;
		}
		const std::shared_ptr<Word> &prev() const
		{
			return m_prev;
		}

		std::wstring::size_type diffFromWord(const std::wstring &word)
		{
			if (m_word == word) {
				return 0;
			}

			if (m_word.length() != word.length()) {
				return std::max(m_word.length(), word.length());
			}

			std::wstring::size_type diffChars(0);
			for (std::wstring::size_type i = 0; i != m_word.size(); ++i) {
				if (m_word[i] != word[i]) {
					++diffChars;
				}
			}
			return diffChars;
		}


	private:
		std::wstring m_word;
		std::shared_ptr<Word> m_prev;

	};
};

int main(int argc, char *argv[])
try {
	setlocale(LC_ALL, "");

	Helper::CheckMainArguments(argc, argv);

	std::wstring fly;
	std::wstring elephant;
	//Helper::CookWords("words.txt", fly, elephant);
	Helper::CookWords(argv[1], fly, elephant);

	std::list<std::wstring> dictionary;
	//Helper::CookDictionary("dic.txt", dictionary);
	Helper::CookDictionary(argv[2], dictionary);

	//std::wcout << "fly = " << fly << std::endl;
	//std::wcout << "elephant = " << elephant << std::endl;

	Fly2Elephant fly2Elephant(dictionary);
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
	std::cerr << "\t" << argv[0] << " [pathToWords][pathToDic]" << std::endl;
	std::cerr << "where:" << std::endl;
	std::cerr << "[pathToWords] is full path to the file with source and target words" << std::endl;
	std::cerr << "[pathToDic] is full path to the file with Dictionary" << std::endl;
}
catch (const FileNotExist& e) {
	std::cerr << "Program ended with an error: file " << e.what() << " is not exist" << std::endl;
	std::cerr << "Please, check correctnes of file path " << std::endl;
}
