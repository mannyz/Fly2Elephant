#include "converter.h"
#include <deque>

namespace fly2elephant {

std::vector<std::wstring> Converter::DoMagic(const std::wstring &flyWord, const std::wstring &elephantWord)
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
	std::size_t flyLength = flyWord.length();
	dictionary.remove_if([flyLength](const std::wstring &w)->bool {
		return w.length() != flyLength;
	});

	std::deque<std::shared_ptr<Word>> intermediateWords;
	std::shared_ptr<Word> word = std::make_shared<Word>(flyWord);
	intermediateWords.push_back(word);
	while (!intermediateWords.empty()) {
		word = intermediateWords.front();
		intermediateWords.pop_front();

		if (word->value() == elephantWord) {
			intermediateWords.clear();
			dictionary.clear();
			break;
		}

		auto it = dictionary.begin();
		while (it != dictionary.end()) {
			auto diff = word->diffFromWord(*it);
			if (diff == 1) {
				intermediateWords.push_back(std::make_shared<Word>(*it));
				intermediateWords.back()->setPrev(word);
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

std::size_t Converter::Word::diffFromWord(const std::wstring &word)
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

} // end namespace fly2elephant
