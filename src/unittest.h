#ifndef UNITTEST_H_
#define UNITTEST_H_

#include "converter.h"

#include <iostream>

namespace fly2elephant {

class UnitTest {
public:
	static bool test(const std::wstring &flyWord
			, const std::wstring &elephantWord
			, const std::list<std::wstring> &dictionary
			, const std::vector<std::wstring> &etalon
			, const std::wstring &name = L"Some test" )
	{
		Converter converter;
		converter.setDictionary(dictionary);
		std::vector<std::wstring> result;
		result = converter.DoMagic(flyWord, elephantWord);
		std::size_t iStep = 0;
		while (iStep != std::min(etalon.size(), result.size()) && etalon[iStep] == result[iStep]) {
			++iStep;
		}
		if (iStep < std::max(etalon.size(), result.size())) {
			std::wcout << L"Test [" << name << "] is failed on step " << iStep << std::endl;
			std::wcout << L"State of etalon: " << (iStep < etalon.size() ? etalon[iStep] : L"has no word") << std::endl;
			std::wcout << L"State of result: " << (iStep < result.size() ? result[iStep] : L"has no word") << std::endl;
			return false;
		} else {
			std::wcout << L"Test [" << name << "] is successfully passed" << std::endl;
			return true;
		}
	}

	static void testSuiteExample();

};

} // end namespace fly2elephant

#endif /* UNITTEST_H_ */
