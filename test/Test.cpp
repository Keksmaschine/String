/**
 * @file Test.hpp
 * @date 11.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#include <iostream>
#include "../src/String.hpp"

/**
 * Prints an error message to the standart error stream if a given expression is false.
 * @param	expression		Expression to test
 * @param	errorMessage	Error message to print to the standart error stream
 */
static void dynamic_assert(const bool expression, const char* errorMessage)
{
	if (!expression)
	{
		std::cerr << errorMessage << std::endl;
	}
}

/** 
 * Tests the constructos of the class String.
 */
static void TestConstructors()
{
	// Test default contructors
	AString astring1;
	WString wstring1;

	// Test if length is zero
	dynamic_assert(0 == astring1.length(), "Error, length of astring is not zero after instantiation via the default constructor");
	dynamic_assert(0 == wstring1.length(), "Error, length of wstring is not zero after instantiation via the default constructor");

	// Test if initial capacity is STRING_SSO_BUFFER_CAPACITY
	dynamic_assert(STRING_SSO_BUFFER_CAPACITY == astring1.capacity(), "Error, capacity of astring is not the expected initial capacity after instantiation via the default constructor");
	dynamic_assert(STRING_SSO_BUFFER_CAPACITY == wstring1.capacity(), "Error, capacity of wstring is not the expected initial capacity after instantiation via the default constructor");


	// Test String(size_t initialCapacity) constructor
	AString astring2(321);
	WString wstring2(123);

	// Test if length is zero
	dynamic_assert(0 == astring2.length(), "Error, length of astring is not zero after instantiation via String(size_t initialCapacity) constructor");
	dynamic_assert(0 == wstring2.length(), "Error, length of wstring is not zero after instantiation via String(size_t initialCapacity) constructor");

	// Test if initial capacity is expected
	dynamic_assert(321 == astring2.capacity(), "Error, capacity of astring is not the expected initial capacity after instantiation via String(size_t initialCapacity) constructor");
	dynamic_assert(123 == wstring2.capacity(), "Error, capacity of wstring is not the expected initial capacity after instantiation via String(size_t initialCapacity) constructor");


	// Test c-string contstructor
	char toCopyA[] = "This is a Test";
	AString astring3(toCopyA);
	wchar_t toCopyW[] = L"This is a Test";
	WString wstring3(toCopyW);

	// Test if length is expected
	dynamic_assert(14 == astring3.length(), "Error in the constructor taking a c-string as a parameter");
	dynamic_assert(14 == wstring3.length(), "Error in the constructor taking a c-string as a parameter");

	// Test if initial capacity is STRING_SSO_BUFFER_CAPACITY
	dynamic_assert(STRING_SSO_BUFFER_CAPACITY == astring3.capacity(), "Error, capacity of astring is not the expected initial capacity after instantiation via the constructor taking a c-string as a parameter");
	dynamic_assert(STRING_SSO_BUFFER_CAPACITY == wstring3.capacity(), "Error, capacity of wstring is not the expected initial capacity after instantiation via the constructor taking a c-string as a parameter");

	// Try passing pos and len
	AString astring4(toCopyA, 1, 5);
	WString wstring4(toCopyW, 1, 5);

	// Test is length is expected
	dynamic_assert(5 == astring4.length(), "Error in the constructor taking a c-string as a parameter passing pos and len");
	dynamic_assert(5 == wstring4.length(), "Error in the constructor taking a c-string as a parameter passing pos and len");

	// Try passing initialMaxLength
	AString astring5(toCopyA, 0, 0, 64);
	WString wstring5(toCopyW, 0, 0, 64);

	// Test if capacity is expected
	dynamic_assert(64 == astring5.capacity(), "Error in the constructor taking a c-string as a parameter passing initialMaxLength");
	dynamic_assert(64 == wstring5.capacity(), "Error in the constructor taking a c-string as a parameter passing initialMaxLength");


	// Test copy-constructor
	AString astring6(astring3);
	WString wstring6(wstring3);

	// Test if length is expected
	dynamic_assert(14 == astring6.length(), "Error in the copy-constructor, astring has an unexpected length");
	dynamic_assert(14 == wstring6.length(), "Error in the copy-constructor, wstring has an unexpected length");

	// Test if initial capacity is STRING_SSO_BUFFER_CAPACITY
	dynamic_assert(STRING_SSO_BUFFER_CAPACITY == astring6.capacity(), "Error, capacity of astring is not the expected initial capacity after instantiation via the copy-constructor");
	dynamic_assert(STRING_SSO_BUFFER_CAPACITY == wstring6.capacity(), "Error, capacity of wstring is not the expected initial capacity after instantiation via the copy-constructor");

	// Test copy-constructor passing pos and len
	AString astring7(astring3, 1, 5);
	WString wstring7(wstring3, 1, 5);

	// Test if length is expected
	dynamic_assert(5 == astring7.length(), "Error in the copy-constructor, astring has an unexpected length when passing pos and len");
	dynamic_assert(5 == wstring7.length(), "Error in the copy-constructor, wstring has an unexpected length when passing pos and len");

	// Test if initial capacity is STRING_SSO_BUFFER_CAPACITY
	dynamic_assert(STRING_SSO_BUFFER_CAPACITY == astring7.capacity(), "Error, capacity of astring is not the expected initial capacity after instantiation via the copy-constructor when passing pos and len");
	dynamic_assert(STRING_SSO_BUFFER_CAPACITY == wstring7.capacity(), "Error, capacity of wstring is not the expected initial capacity after instantiation via the copy-constructor when passing pos and len");

	// Test copy-constructor passing pos and len initialMaxLength
	AString astring8(astring3, 1, 5, 64);
	WString wstring8(wstring3, 1, 5, 64);

	// Test if length is expected
	dynamic_assert(5 == astring8.length(), "Error in the copy-constructor, astring has an unexpected length when passing pos, len and initialMaxLength");
	dynamic_assert(5 == wstring8.length(), "Error in the copy-constructor, wstring has an unexpected length when passing pos, len and initialMaxLength");

	// Test if initial capacity is STRING_INITIAL_MAXLENGTH
	dynamic_assert(64 == astring8.capacity(), "Error, capacity of astring is not the expected initial capacity after instantiation via the copy-constructor when passing pos, len and initialMaxLength");
	dynamic_assert(64 == wstring8.capacity(), "Error, capacity of wstring is not the expected initial capacity after instantiation via the copy-constructor when passing pos, len and initialMaxLength");
}

/** 
 * Tests the setLength and setCapacity methods of the class String.
 */
static void TestSetLengthAndSetCapacity()
{
	AString astring1;
	WString wstring1;

	// Test setLength
	astring1.setLength(64);
	wstring1.setLength(64);

	dynamic_assert(64 == astring1.length(), "Error in setLength for AString");
	dynamic_assert(64 == wstring1.length(), "Error in setLength for WString");

	// Test setCapacity
	astring1.setCapacity(64);
	wstring1.setCapacity(64);

	size_t expectedCapacity = STRING_SSO_BUFFER_CAPACITY;
	while (expectedCapacity < 64)
	{
		expectedCapacity = static_cast<size_t>(STRING_BUFFER_GROWTH_FACTOR * expectedCapacity);
	}

	dynamic_assert(expectedCapacity == astring1.capacity(), "Error in setCapacity for AString");
	dynamic_assert(expectedCapacity == wstring1.capacity(), "Error in setCapacity for WString");
}

/** 
 * Tests the copy, compare, operator== and operator!= methods of the class String.
 */
static void TestCopyAndCompareAndOperators()
{
	char textA[] = "This is the text to copy";
	wchar_t textW[] = L"This is the text to copy";

	AString astring1;
	WString wstring1;

	// Test copy method
	astring1.copy(textA);
	wstring1.copy(textW);

	// Test compare and operator== and operator!= with c-strings
	dynamic_assert(astring1 == textA, "Error in copy or compare or operator== method of AString for c-strings");
	dynamic_assert(wstring1 == textW, "Error in copy or compare or operator== method of WString for c-strings");

	char text2A[] = "This is another text";
	wchar_t text2W[] = L"This is another text";

	dynamic_assert(!(astring1 == text2A), "Error in copy or compare or operator== method of AString for c-strings");
	dynamic_assert(!(wstring1 == text2W), "Error in copy or compare or operator== method of WString for c-strings");

	dynamic_assert(astring1 != text2A, "Error in copy or compare or operator!= method of AString for c-strings");
	dynamic_assert(wstring1 != text2W, "Error in copy or compare or operator!= method of WString for c-strings");


	// Test compare and operator== and operator!= with String objects for equal strings
	AString astring2(astring1);
	WString wstring2(wstring1);

	dynamic_assert(astring1 == astring2, "Error in compare or operator== method of AString for String objects");
	dynamic_assert(wstring1 == wstring2, "Error in compare or operator== method of WString for String objects");

	dynamic_assert(!(astring1 != astring2), "Error in compare or operator!= method of AString for String objects");
	dynamic_assert(!(wstring1 != wstring2), "Error in compare or operator!= method of WString for String objects");

	// Test compare and operator== and operator!= with String objects for unequal strings
	AString astring3(text2A);
	WString wstring3(text2W);

	dynamic_assert(astring1 != astring3, "Error, unequal strings are reported to be equal by operator!= in AString for String objects");
	dynamic_assert(wstring1 != wstring3, "Error, unequal strings are reported to be equal by operator!= in WString for String objects");

	dynamic_assert(!(astring1 == astring3), "Error, unequal strings are reported to be equal by operator== in AString for String objects");
	dynamic_assert(!(wstring1 == wstring3), "Error, unequal strings are reported to be equal by operator== in WString for String objects");
}

/** 
 * Tests the append and operator+= methods of the class String.
 */
static void testAppend()
{
	char text1A[] = "text1";
	wchar_t text1W[] = L"text1";
	char text2A[] = "text2";
	wchar_t text2W[] = L"text2";
	char text3A[] = "text1text2";
	wchar_t text3W[] = L"text1text2";

	AString astring1(text1A);
	WString wstring1(text1W);
	AString astring2(text2A);
	WString wstring2(text2W);
	AString astring3(text3A);
	WString wstring3(text3W);

	// Test append and operator+=
	astring1 += astring2;
	wstring1 += wstring2;

	dynamic_assert(astring1 == astring3, "Error in append or operator+= of AString");
	dynamic_assert(wstring1 == wstring3, "Error in append or operator+= of WString");
}

/**
 * Entry point for the test application. Runs all tests.
 * @param	argc	Count of command line parameters
 * @param	argv	Command line parameters
 * @return			Return code of the application
 */
int main(int argc, char* argv[])
{
	TestConstructors();
	TestSetLengthAndSetCapacity();
	TestCopyAndCompareAndOperators();
	testAppend();

	std::cout << "All tests done!" << std::endl;
    return 0;
}
