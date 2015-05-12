#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <list>
#include <vector>
#include <memory>
#include <string>

namespace fly2elephant {

class Converter {
public:
	Converter()
	{}
	Converter(const std::list<std::wstring> &dictionary)
		: m_dictionary(dictionary)
	{}
	void setDictionary(const std::list<std::wstring> &dictionary) { m_dictionary = dictionary; }
	std::vector<std::wstring> DoMagic(const std::wstring &flyWord, const std::wstring &elephantWord);

private:
	std::list<std::wstring> m_dictionary;

private:
	class Word {
	public:
		Word(const std::wstring &word)
			: m_word(word)
		{}
		const std::wstring& value() const { return m_word; }
		void setPrev(const std::shared_ptr<Word> &prev) { m_prev = prev; }
		const std::shared_ptr<Word> &prev() const { return m_prev; }
		std::size_t diffFromWord(const std::wstring &word);

	private:
		std::wstring m_word;
		std::shared_ptr<Word> m_prev;

	};
};

} // end namespace fly2elephant

#endif /* CONVERTER_H_ */

