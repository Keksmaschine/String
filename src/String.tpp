/**
 * @file String.tpp
 * @date 11.03.2017
 * @author Christian Hülsmann (christian_huelsmann@gmx.de)
 */

#ifndef STRING_HPP
#error STRING_HPP undefined
#endif

template<class TChar>
size_t String<TChar>::cstr_length(const TChar* str)
{
	size_t length = 0;
	if (str)
	{
		while (str[length] != static_cast<TChar>(0))
		{
			length++;
		}
	}
	return length;
}

template<class TChar>
size_t String<TChar>::cstr_copy(TChar* dst, const TChar* src)
{
	size_t length = 0;
	if (dst && src)
	{
		while (src[length] != static_cast<TChar>(0))
		{
			dst[length] = src[length];
			length++;
		}
		dst[length] = static_cast<TChar>(0);
	}
	return length;
}

template<class TChar>
size_t String<TChar>::cstr_copy(TChar* dst, const TChar* src, size_t pos, size_t length)
{
	if (dst && src)
	{
		src += pos;
		if (!length)
		{
			return cstr_copy(dst, src);
		}
		memcpy(dst, src, length * sizeof(TChar));
		dst[length] = static_cast<TChar>(0);
		return length;
	}
	return 0;
}

template<class TChar>
int String<TChar>::cstr_compare(const TChar* str1, const TChar* str2)
{
	if (str1 && str2)
	{
		while (*(str1) && *(str2) && *(str1) == *(str2))
		{
			str1 = str1 + 1;
			str2 = str2 + 1;
		}
		return(*(str1)-*(str2));
	}
	return 0;
}



template<class TChar>
bool String<TChar>::usesDynamicBuffer() const
{
	return m_capacity > STRING_SSO_BUFFER_CAPACITY;
}

template<class TChar>
size_t String<TChar>::calcNewCapacity(size_t minCapacity) const
{
	size_t newCapacity = m_capacity;
	while (newCapacity < minCapacity)
	{
		newCapacity = static_cast<size_t>(STRING_BUFFER_GROWTH_FACTOR * newCapacity);
	}
	return newCapacity;
}

template<class TChar>
String<TChar>::String()
	: m_capacity(STRING_SSO_BUFFER_CAPACITY), m_length(0)
{
	// Nothing to do yet
}

template<class TChar>
String<TChar>::String(size_t initialCapacity)
	: m_capacity(STRING_SSO_BUFFER_CAPACITY), m_length(0)
{
	// Update capacity if required
	if (initialCapacity > m_capacity)
	{
		// Set capacity to initialCapacity
		m_buffer = new TChar[initialCapacity + 1];
		m_capacity = initialCapacity;
	}
}

template<class TChar>
String<TChar>::String(const TChar* other, size_t pos, size_t len, size_t initialCapacity)
	: m_capacity(STRING_SSO_BUFFER_CAPACITY), m_length(0)
{
	// Update capacity if required
	if (initialCapacity > m_capacity)
	{
		// Set capacity to initialCapacity
		m_buffer = new TChar[initialCapacity + 1];
		m_capacity = initialCapacity;
	}

	// Copy source string
	copy(other, pos, len);
}

template<class TChar>
String<TChar>::String(const String<TChar>& other, size_t pos, size_t len, size_t initialCapacity)
	: m_capacity(STRING_SSO_BUFFER_CAPACITY), m_length(0)
{
	// Update capacity if required
	if (initialCapacity > m_capacity)
	{
		// Set capacity to initialCapacity
		m_buffer = new TChar[initialCapacity + 1];
		m_capacity = initialCapacity;
	}

	// Copy source string
	copy(other, pos, len);
}

template<class TChar>
String<TChar>::~String()
{
	if (usesDynamicBuffer())
	{
		delete[] m_buffer;
	}
}

template<class TChar>
void String<TChar>::copy(const TChar* source, size_t pos, size_t len)
{
	source += pos;
	if (!len)
	{
		len = cstr_length(source);
	}

	if (len > m_capacity)
	{
		// DO NOT use setCapacity here! No need to copy the existing string
		if (usesDynamicBuffer())
		{
			delete[] m_buffer;
		}
		size_t newCapacity = calcNewCapacity(len);
		m_buffer = new TChar[newCapacity + 1];
		m_capacity = newCapacity;
	}

	// Copy source string to the buffer and update the length
	cstr_copy(data(), source, 0, len);
	m_length = len;
}

template<class TChar>
void String<TChar>::copy(const String<TChar>& source, size_t pos, size_t len)
{
	if (!len)
	{
		len = source.length() - pos;
	}
	copy(source.c_str(), pos, len);
}

template<class TChar>
inline const TChar* String<TChar>::c_str() const
{
	return usesDynamicBuffer() ? m_buffer : m_ssoBuffer;
}

template<class TChar>
TChar* String<TChar>::data() const
{
	return const_cast<TChar*>(c_str());
}

template<class TChar>
size_t String<TChar>::length() const
{
	return m_length;
}

template<class TChar>
size_t String<TChar>::calcLength()
{
	m_length = cstr_length(c_str());
	return m_length;
}

template<class TChar>
void String<TChar>::setLength(size_t length)
{
	m_length = length;
}

template<class TChar>
size_t String<TChar>::capacity() const
{
	return m_capacity;
}

template<class TChar>
void String<TChar>::setCapacity(size_t minLength)
{
	if (minLength > m_capacity)
	{
		size_t newCapacity = calcNewCapacity(minLength);
		TChar* newBuffer = new TChar[newCapacity + 1];
		if (m_length)
		{
			// Copy the string to the new buffer
			cstr_copy(newBuffer, c_str(), 0, m_length);
		}
		if (usesDynamicBuffer())
		{
			// Deallocate old buffer
			delete[] m_buffer;
		}
		// Update m_buffer and m_capacity member variables
		m_buffer = newBuffer;
		m_capacity = newCapacity;
	}
}

template<class TChar>
void String<TChar>::append(const TChar* other, size_t pos, size_t len)
{
	if (other)
	{
		other += pos;
		if (!len)
		{
			len = cstr_length(other);
		}

		// Update capacity if required
		setCapacity(m_length + len);

		// Copy other to the end of the current string
		cstr_copy(data() + m_length, other, 0, len);
		m_length += len;
	}
}

template<class TChar>
void String<TChar>::append(const String<TChar>& other, size_t pos, size_t len)
{
	if (!len)
	{
		len = other.length() - pos;
	}
	append(other.c_str(), pos, len);
}

template<class TChar>
int String<TChar>::compare(const TChar* other) const
{
	return cstr_compare(c_str(), other);
}

template<class TChar>
String<TChar>& String<TChar>::operator=(const TChar* other)
{
	copy(other);
	return *this;
}

template<class TChar>
String<TChar>& String<TChar>::operator=(const String<TChar>& other)
{
	if (this != &other)
	{
		copy(other);
	}
	return *this;
}

template<class TChar>
String<TChar>& String<TChar>::operator+=(const TChar* other)
{
	append(other);
	return *this;
}

template<class TChar>
String<TChar>& String<TChar>::operator+=(const String<TChar>& other)
{
	append(other);
	return *this;
}

template<class TChar>
bool String<TChar>::operator==(const TChar* other) const
{
	return 0 == compare(other);
}

template<class TChar>
bool String<TChar>::operator==(const String<TChar>& other) const
{
	if (this == &other)
	{
		return true;
	}
	if (other.length() != m_length)
	{
		return false;
	}
	return 0 == compare(other.c_str());
}

template<class TChar>
bool String<TChar>::operator!=(const TChar* other) const
{
	return 0 != compare(other);
}

template<class TChar>
bool String<TChar>::operator!=(const String<TChar>& other) const
{
	if (this == &other)
	{
		return false;
	}
	if (other.length() != m_length)
	{
		return true;
	}
	return 0 != compare(other.c_str());
}
