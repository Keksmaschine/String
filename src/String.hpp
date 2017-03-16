/**
 * @file String.hpp
 * @date 11.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#ifndef STRING_HPP
#define STRING_HPP


// For memcpy
#include <cstring>


// Size of the SSO buffer in characters excluding the terminating 0
#define STRING_SSO_BUFFER_CAPACITY 15
// Growth factor of the dynamically allocated buffer
#define STRING_BUFFER_GROWTH_FACTOR 1.5f


/**
 * @class String
 * String class using small-string-optimization and a dynamically growing internal buffer.
 * It provides basic string manipulation functionality.
 */
template<class TChar>
class String
{
private:
	/**
	 * Calculates the length of a c-string.
	 * @param	str	C-string to calculate the length for
	 * @return		Length of the c-string
	 */
	static size_t cstr_length(const TChar* str);

	/**
	 * Copies a zero-terminated c-string.
	 * @param	dst	Destination c-string
	 * @param	src	Source c-string
	 * @return		Count of copied characters
	 */
	static size_t cstr_copy(TChar* dst, const TChar* src);

	/**
	 * Copies a c-string.
	 * @param	dst	Destination c-string
	 * @param	src	Source c-string
	 * @pos			Position from where to copy in src
	 * @length		Length of the string to copy
	 * @return		Count of copied characters
	 */
	static size_t cstr_copy(TChar* dst, const TChar* src, size_t pos, size_t length);

	/**
	 * Compares two c-strings to each other.
	 * @param	str1	First string for the comparision
	 * @param	str2	Second string for the comparision
	 * @return			0 if both strings are equal, otherwise non-zero
	 */
	static int cstr_compare(const TChar* str1, const TChar* str2);
	

	// Size of the allocated buffer in characters without terminating 0
	size_t m_capacity;
	// Length of the string in characters without terminating 0
	size_t m_length;

	// Buffer for the string
	union {
		// Stack SSO buffer
		TChar m_ssoBuffer[STRING_SSO_BUFFER_CAPACITY + 1];
		// Dynamically allocated buffer
		TChar* m_buffer;
	};

	/**
	 * Checks if the instance of the class uses the dynamically allocated buffer.
	 * @return	true if the instance uses the dynamically allocated buffer, otherwise false
	 */
	bool usesDynamicBuffer() const;

	/**
	 * Calculates the new capacity to grow from a given minimal capacity using a growth factor.
	 * @param	minCapacity	Minimum capacity the instance of the class must have
	 * @return				New capacity to grow calculated using the growth factor
	 */
	size_t calcNewCapacity(size_t minCapacity) const;

public:
	/**
	 * Default constructor for instances of the class String. Constructs an empty instance.
	 */
	String();

	/**
	 * Constructor which ensures the newly instanciated object has a buffer allocated for at
	 * least initialMaxLength characters.
	 * @param	initialCapacity	Initial capacity of the buffer for string of the instance in characters
	 */
	String(size_t initialCapacity);
	
	/**
	 * Constructor which creates an instance of the class String from a given c-string.
	 * @param	other				C-string to copy
	 * @param	pos					Position from where to start copying
	 * @param	len					Count of characters to copy
	 * @param	initialCapacity		Initial capacity of the buffer for the string of the instance in characters
	 */
	String(const TChar* other, size_t pos = 0, size_t len = 0, size_t initialCapacity = 0);

	/**
	 * Copy-constructor. Creates an instance of the class String from another String.
	 * @param	other				String to copy
	 * @param	pos					Position from where to start copying
	 * @param	len					Count of characters to copy
	 * @param	initialCapacity		Initial capacity of the buffer for the string of the instance in characters
	 */
	String(const String<TChar>& other, size_t pos = 0, size_t len = 0, size_t initialCapacity = 0);
	
	/**
	 * Destructor for instances of the class String.
	 */
	virtual ~String();

	/**
	 * Clears the stored string of the instance and copies a c-string to the internal buffer.
	 * @param	source	C-string to copy to the internal buffer
	 * @param	pos		Position from where to copy
	 * @param	len		Length of the c-string to copy in characters
	 */
	void copy(const TChar* source, size_t pos = 0, size_t len = 0);

	/**
	 * Clears the stored string of the instance and copies a string of another String instance to the internal buffer.
	 * @param	source	String to copy to the internal buffer
	 * @param	pos		Position from where to copy
	 * @param	len		Length of the string to copy in characters
	 */
	void copy(const String<TChar>& source, size_t pos = 0, size_t len = 0);

	/**
	 * Returns a constant pointer to the internal string buffer.
	 * @return	Pointer to the internal string buffer
	 */
	const TChar* c_str() const;

	/**
	 * Returns a pointer to the internal string buffer.
	 * @return	Pointer to the internal string buffer
	 */
	TChar* data() const;

	/**
	 * Returns the length of the string.
	 * @return	Length of the string
	 */
	size_t length() const;

	/**
	 * Calculates, updates and returns the length of the string. This method provides a functionality to correct the
	 * value of the member variable m_length after the internal string was manipulated using the data() method.
	 * @return	Length of the string
	 */
	size_t calcLength();
	
	/**
	 * Sets the length of the string. This method provides a functionality to correct the value of the member variable
	 * m_length after the internal string was manipulated using the data() method.
	 * @param	length	New length of the String instance
	 */
	void setLength(size_t length);

	/**
	 * Returns the capacity of the internal buffer in characters.
	 * @return	Capacity of the buffer in characters
	 */
	size_t capacity() const;
	
	/**
	 * Updates the capacity of the buffer for at least minLength characters. The method dynamically allocates buffer for
	 * this task if required.
	 * @param	minLength	New minimum capacity of the instance in characters
	 */
	void setCapacity(size_t minLength);

	/**
	 * Appends a c-string to the end of the string stored in the instance.
	 * @param	other	C-string to append
	 * @param	pos		Position from where to copy
	 * @param	len		Count of characters to copy from other
	 */
	void append(const TChar* other, size_t pos = 0, size_t len = 0);

	/**
	 * Appends one String to another.
	 * @param	other	String to append
	 * @param	pos		Position from where to copy
	 * @param	len		Count of characters to copy from other
	 */
	void append(const String<TChar>& other, size_t pos = 0, size_t len = 0);

	/**
	 * Compares the stored string of the instance to a c-string.
	 * @param	other	C-string to compare to
	 * @return			0 if both strings are equal, otherwise non-zero
	 */
	int compare(const TChar* other) const;

	/**
	 * Assign operator. Sets the string of the instance to the string of a c-string.
	 * @param	other	C-string to copy
	 * @return			Reference to the instance
	 */
	String<TChar>& operator=(const TChar* other);

	/**
	 * Assign operator. Sets the string of the instance to the string of another String instance.
	 * @param	other	String to copy
	 * @return			Reference to the instance
	 */
	String<TChar>& operator=(const String<TChar>& other);

	/**
	 * Add-to operator. Appends a c-string to the string of the instance.
	 * @param	other	C-string to append
	 * @return			Reference to the instance
	 */
	String<TChar>& operator+=(const TChar* other);

	/**
	 * Add-to operator. Appends a string to the string of the instance.
	 * @param	other	String to append
	 * @return			Reference to the instance
	 */
	String<TChar>& operator+=(const String<TChar>& other);

	/**
	 * Equal operator. Checks if a c-string is equal to the stored string of the instance.
	 * @param	other	C-string to compare to
	 * @return			true if both strings are equal, otherwise false
	 */
	bool operator==(const TChar* other) const;

	/**
	 * Equal operator. Checks if another instance of the String class has the same length and contains the same stored
	 * string.
	 * @param	other	String instance to compare to
	 * @return			true if both strings are equal, otherwise false
	 */
	bool operator==(const String<TChar>& other) const;

	/**
	 * Unequal operator. Checks if a c-string is unequal to the stored string of the instance.
	 * @param	other	C-string to compare to
	 * @return			true if both strings are unequal, otherwise false
	 */
	bool operator!=(const TChar* other) const;

	/**
	 * Unequal operator. Checks if another instance of the String class has a different length and contains a
	 * different stored string.
	 * @param	other	String instance to compare to
	 * @return			true if both strings are unequal, otherwise false
	 */
	bool operator!=(const String<TChar>& other) const;
};


// Include String class implementation
#include "String.tpp"


// Typedef frequently used string classes
typedef String<char> AString;
typedef String<wchar_t> WString;


#endif // #ifndef STRING_HPP
