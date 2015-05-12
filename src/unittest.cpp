#include "unittest.h"

namespace fly2elephant {

void UnitTest::testSuiteExample()
{
	{
		std::wstring fly = L"";
		std::wstring elephant = L"";
		std::list<std::wstring> dictionary;
		std::vector<std::wstring> result;
		UnitTest::test(fly, elephant, dictionary, result, L"Пустые слова");
	}

	{
		std::wstring fly = L"МУХА";
		std::wstring elephant = L"СЛОН";
		std::list<std::wstring> dictionary;
		std::vector<std::wstring> result;
		UnitTest::test(fly, elephant, dictionary, result, L"Пустой словарь");
	}

	{
		std::wstring fly = L"МУХА";
		std::wstring elephant = L"МУХА";
		std::list<std::wstring> dictionary;
		std::vector<std::wstring> result;
		result.push_back(L"МУХА");
		UnitTest::test(fly, elephant, dictionary, result, L"Одинаковые слова");
	}

	{
		std::wstring fly = L"КОТ";
		std::wstring elephant = L"ТОН";
		std::list<std::wstring> dictionary;
		dictionary.push_back(L"КОТ");
		dictionary.push_back(L"ТОН");
		dictionary.push_back(L"НОТА");
		dictionary.push_back(L"КОТЫ");
		dictionary.push_back(L"РОТ");
		dictionary.push_back(L"РОТА");
		dictionary.push_back(L"ТОТ");
		std::vector<std::wstring> result;
		result.push_back(L"КОТ");
		result.push_back(L"ТОТ");
		result.push_back(L"ТОН");
		UnitTest::test(fly, elephant, dictionary, result, L"КОТ-ТОН");
	}

	{
		std::wstring fly = L"КОТ";
		std::wstring elephant = L"КОТЫ";
		std::list<std::wstring> dictionary;
		dictionary.push_back(L"КОТ");
		dictionary.push_back(L"ТОН");
		dictionary.push_back(L"НОТА");
		dictionary.push_back(L"КОТЫ");
		dictionary.push_back(L"РОТ");
		dictionary.push_back(L"РОТА");
		dictionary.push_back(L"ТОТ");
		std::vector<std::wstring> result;
		UnitTest::test(fly, elephant, dictionary, result, L"КОТ-КОТЫ");
	}
}

} // end namespace fly2elephant
